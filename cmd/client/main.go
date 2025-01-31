// Copyright 2022-2023 The Connect Authors
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

package main

import (
	"context"
	"crypto/tls"
	"crypto/x509"
	"errors"
	"fmt"
	"log"
	"net"
	"net/http"
	"net/url"
	"os"

	"connectrpc.com/conformance/internal/console"
	conformanceconnect "connectrpc.com/conformance/internal/gen/proto/connect/connectrpc/conformance/v1/conformancev1connect"
	conformance "connectrpc.com/conformance/internal/gen/proto/go/connectrpc/conformance/v1"
	"connectrpc.com/conformance/internal/interop/interopconnect"
	"connectrpc.com/conformance/internal/interop/interopgrpc"
	"connectrpc.com/connect"
	"github.com/quic-go/quic-go/http3"
	"github.com/spf13/cobra"
	"golang.org/x/net/http2"
	"google.golang.org/grpc"
	"google.golang.org/grpc/credentials"
	"google.golang.org/grpc/credentials/insecure"
	"google.golang.org/grpc/encoding/gzip"
)

const (
	hostFlagName           = "host"
	portFlagName           = "port"
	implementationFlagName = "implementation"
	insecureFlagName       = "insecure"
	certFlagName           = "cert"
	keyFlagName            = "key"
)

const (
	connectH1        = "connect-h1"
	connectH2        = "connect-h2"
	connectH3        = "connect-h3"
	connectGRPCH1    = "connect-grpc-h1"
	connectGRPCH2    = "connect-grpc-h2"
	connectGRPCWebH1 = "connect-grpc-web-h1"
	connectGRPCWebH2 = "connect-grpc-web-h2"
	connectGRPCWebH3 = "connect-grpc-web-h3"
	grpcGo           = "grpc-go"
)

type flags struct {
	host           string
	port           string
	implementation string
	insecure       bool
	certFile       string
	keyFile        string
}

func main() {
	flagset := &flags{}
	rootCmd := &cobra.Command{
		Use:   "client",
		Short: "Starts a grpc or connect client, based on implementation",
		PreRunE: func(cmd *cobra.Command, args []string) error {
			insecure, _ := cmd.Flags().GetBool(insecureFlagName)
			certFile, _ := cmd.Flags().GetString(certFlagName)
			keyFile, _ := cmd.Flags().GetString(keyFlagName)
			implementation, _ := cmd.Flags().GetString("implementation")
			if insecure {
				if implementation == connectGRPCWebH3 || implementation == connectH3 {
					return errors.New("HTTP/3 implementations cannot be insecure. Either change the implementation or remove the insecure flag and provide a cert and key")
				}
			} else {
				if certFile == "" || keyFile == "" {
					return errors.New("either a 'cert' and 'key' combination or 'insecure' must be specified")
				}
			}
			return nil
		},
		Run: func(cmd *cobra.Command, args []string) {
			run(flagset)
		},
	}
	if err := bind(rootCmd, flagset); err != nil {
		os.Exit(1)
	}
	_ = rootCmd.Execute()
}

func bind(cmd *cobra.Command, flags *flags) error {
	cmd.Flags().StringVar(&flags.host, hostFlagName, "127.0.0.1", "the host name of the test server")
	cmd.Flags().StringVar(&flags.port, portFlagName, "", "the port of the test server")
	cmd.Flags().StringVarP(
		&flags.implementation,
		implementationFlagName,
		"i",
		"",
		fmt.Sprintf(
			"the client implementation tested, accepted values are %q, %q, %q, %q, %q, %q, %q, %q, or %q",
			connectH1,
			connectH2,
			connectH3,
			connectGRPCH1,
			connectGRPCH2,
			connectGRPCWebH1,
			connectGRPCWebH2,
			connectGRPCWebH3,
			grpcGo,
		),
	)
	cmd.Flags().StringVar(&flags.certFile, certFlagName, "", "path to the TLS cert file")
	cmd.Flags().StringVar(&flags.keyFile, keyFlagName, "", "path to the TLS key file")
	cmd.Flags().BoolVar(&flags.insecure, insecureFlagName, false, "whether to use cleartext with the client (not permitted with HTTP/3 implementations)")
	for _, requiredFlag := range []string{portFlagName, implementationFlagName} {
		if err := cmd.MarkFlagRequired(requiredFlag); err != nil {
			return err
		}
	}
	cmd.MarkFlagsMutuallyExclusive(insecureFlagName, certFlagName)
	cmd.MarkFlagsMutuallyExclusive(insecureFlagName, keyFlagName)
	return nil
}

func run(flags *flags) {
	// tests for grpc client
	if flags.implementation == grpcGo {
		var transportCredentials credentials.TransportCredentials
		if !flags.insecure {
			transportCredentials = credentials.NewTLS(newTLSConfig(flags.certFile, flags.keyFile))
		} else {
			transportCredentials = insecure.NewCredentials()
		}
		clientConn, err := grpc.Dial(
			net.JoinHostPort(flags.host, flags.port),
			grpc.WithTransportCredentials(transportCredentials),
		)
		if err != nil {
			log.Fatalf("failed grpc dial: %v", err)
		}
		unresolvableClientConn, err := grpc.Dial(
			"unresolvable-host.some.domain",
			grpc.WithTransportCredentials(transportCredentials),
		)
		if err != nil {
			log.Fatalf("failed grpc dial: %v", err)
		}
		defer clientConn.Close()
		defer unresolvableClientConn.Close()

		testGrpc(clientConn, unresolvableClientConn)
		return
	}

	// tests for connect clients
	var scheme string
	if flags.insecure {
		scheme = "http://"
	} else {
		scheme = "https://"
	}
	serverURL, err := url.ParseRequestURI(scheme + net.JoinHostPort(flags.host, flags.port))
	if err != nil {
		log.Fatalf("invalid url: %s", scheme+net.JoinHostPort(flags.host, flags.port))
	}
	// create transport base on HTTP protocol of the implementation
	var transport http.RoundTripper
	switch flags.implementation {
	case connectH1, connectGRPCH1, connectGRPCWebH1:
		h1Transport := &http.Transport{}
		if !flags.insecure {
			h1Transport.TLSClientConfig = newTLSConfig(flags.certFile, flags.keyFile)
		}
		transport = h1Transport
	case connectGRPCH2, connectH2, connectGRPCWebH2:
		h2Transport := &http2.Transport{}
		if flags.insecure {
			h2Transport.AllowHTTP = true
			h2Transport.DialTLSContext = func(ctx context.Context, network, addr string, cfg *tls.Config) (net.Conn, error) {
				return net.Dial(network, addr)
			}
		} else {
			h2Transport.TLSClientConfig = newTLSConfig(flags.certFile, flags.keyFile)
		}
		transport = h2Transport
	case connectH3, connectGRPCWebH3:
		transport = &http3.RoundTripper{
			TLSClientConfig: newTLSConfig(flags.certFile, flags.keyFile),
		}
	default:
		log.Fatalf(`the --implementation or -i flag is invalid"`)
	}
	transport = &interopconnect.TrailerInterceptor{Transport: transport}
	// create client options base on protocol of the implementation
	clientOptions := []connect.ClientOption{connect.WithHTTPGet()}
	switch flags.implementation {
	case connectGRPCH1, connectGRPCH2:
		clientOptions = append(clientOptions, connect.WithGRPC())
	case connectGRPCWebH1, connectGRPCWebH2, connectGRPCWebH3:
		clientOptions = append(clientOptions, connect.WithGRPCWeb())
	}
	// create test clients using the transport and client options
	uncompressedClient := conformanceconnect.NewTestServiceClient(
		&http.Client{Transport: transport},
		serverURL.String(),
		clientOptions...,
	)
	unresolvableClient := conformanceconnect.NewTestServiceClient(
		&http.Client{Transport: transport},
		"https://unresolvable-host.some.domain",
		clientOptions...,
	)
	unimplementedClient := conformanceconnect.NewUnimplementedServiceClient(
		&http.Client{Transport: transport},
		serverURL.String(),
		clientOptions...,
	)
	// add compress options to create compressed client
	clientOptions = append(clientOptions, connect.WithSendGzip())
	compressedClient := conformanceconnect.NewTestServiceClient(
		&http.Client{Transport: transport},
		serverURL.String(),
		clientOptions...,
	)

	// run tests base on the implementation
	switch flags.implementation {
	// We skipped those client and bidi streaming tests for http 1 test
	case connectH1, connectGRPCH1, connectGRPCWebH1:
		usesTrailers := flags.implementation == connectGRPCH1
		for _, client := range []conformanceconnect.TestServiceClient{uncompressedClient, compressedClient} {
			testConnectUnary(client, usesTrailers)
			testConnectServerStreaming(client, usesTrailers)
		}
		testConnectSpecialClients(unresolvableClient, unimplementedClient)
	case connectH2, connectGRPCH2, connectGRPCWebH2:
		usesTrailers := flags.implementation == connectGRPCH2
		for _, client := range []conformanceconnect.TestServiceClient{uncompressedClient, compressedClient} {
			testConnectUnary(client, usesTrailers)
			testConnectServerStreaming(client, usesTrailers)
			testConnectClientStreaming(client)
			testConnectBidiStreaming(client, usesTrailers)
			interopconnect.DoTimeoutOnSleepingServer(console.NewTB(), client)
		}
		testConnectSpecialClients(unresolvableClient, unimplementedClient)
	case connectH3:
		for _, client := range []conformanceconnect.TestServiceClient{uncompressedClient, compressedClient} {
			testConnectUnary(client, false)
			testConnectServerStreaming(client, false)
			testConnectClientStreaming(client)
			testConnectBidiStreaming(client, false)
			// skipped the DoTimeoutOnSleepingServer test as quic-go wrapped the context error,
			// see https://github.com/quic-go/quic-go/blob/6fbc6d951a4005d7d9d086118e1572b9e8ff9851/http3/client.go#L276-L283
		}
		testConnectSpecialClients(unresolvableClient, unimplementedClient)
	case connectGRPCWebH3:
		for _, client := range []conformanceconnect.TestServiceClient{uncompressedClient, compressedClient} {
			// For tests that depend on trailers, we only run them for HTTP2, since the HTTP3 client
			// does not yet have trailers support https://github.com/quic-go/quic-go/issues/2266
			// Once trailer support is available, they will be reenabled.
			interopconnect.DoEmptyUnaryCall(console.NewTB(), client)
			interopconnect.DoLargeUnaryCall(console.NewTB(), client)
			interopconnect.DoClientStreaming(console.NewTB(), client)
			interopconnect.DoServerStreaming(console.NewTB(), client)
			interopconnect.DoPingPong(console.NewTB(), client)
		}
	}
}

func testConnectUnary(client conformanceconnect.TestServiceClient, usesTrailers bool) {
	interopconnect.DoEmptyUnaryCall(console.NewTB(), client)
	interopconnect.DoCacheableUnaryCall(console.NewTB(), client)
	interopconnect.DoLargeUnaryCall(console.NewTB(), client)
	interopconnect.DoCustomMetadataUnary(console.NewTB(), client, usesTrailers)
	interopconnect.DoDuplicatedCustomMetadataUnary(console.NewTB(), client, usesTrailers)
	interopconnect.DoStatusCodeAndMessageUnary(console.NewTB(), client)
	interopconnect.DoSpecialStatusMessage(console.NewTB(), client)
	interopconnect.DoUnimplementedMethod(console.NewTB(), client)
	interopconnect.DoFailWithNonASCIIError(console.NewTB(), client)
}

func testConnectServerStreaming(client conformanceconnect.TestServiceClient, usesTrailers bool) {
	interopconnect.DoServerStreaming(console.NewTB(), client)
	interopconnect.DoCustomMetadataServerStreaming(console.NewTB(), client, usesTrailers)
	interopconnect.DoDuplicatedCustomMetadataServerStreaming(console.NewTB(), client, usesTrailers)
	interopconnect.DoUnimplementedServerStreamingMethod(console.NewTB(), client)
	interopconnect.DoFailServerStreamingWithNonASCIIError(console.NewTB(), client)
	interopconnect.DoFailServerStreamingAfterResponse(console.NewTB(), client)
}

func testConnectClientStreaming(client conformanceconnect.TestServiceClient) {
	interopconnect.DoClientStreaming(console.NewTB(), client)
	interopconnect.DoCancelAfterBegin(console.NewTB(), client)
}

func testConnectBidiStreaming(client conformanceconnect.TestServiceClient, usesTrailers bool) {
	interopconnect.DoPingPong(console.NewTB(), client)
	interopconnect.DoEmptyStream(console.NewTB(), client)
	interopconnect.DoCancelAfterFirstResponse(console.NewTB(), client)
	interopconnect.DoCustomMetadataFullDuplex(console.NewTB(), client, usesTrailers)
	interopconnect.DoDuplicatedCustomMetadataFullDuplex(console.NewTB(), client, usesTrailers)
	interopconnect.DoStatusCodeAndMessageFullDuplex(console.NewTB(), client)
}

func testConnectSpecialClients(
	unresolvableClient conformanceconnect.TestServiceClient,
	unimplementedClient conformanceconnect.UnimplementedServiceClient,
) {
	interopconnect.DoUnresolvableHost(console.NewTB(), unresolvableClient)
	interopconnect.DoUnimplementedService(console.NewTB(), unimplementedClient)
	interopconnect.DoUnimplementedServerStreamingService(console.NewTB(), unimplementedClient)
}

func testGrpc(clientConn *grpc.ClientConn, unresolvableClientConn *grpc.ClientConn) {
	client := conformance.NewTestServiceClient(clientConn)
	unresolvableClient := conformance.NewTestServiceClient(unresolvableClientConn)
	for _, args := range [][]grpc.CallOption{
		nil,
		{grpc.UseCompressor(gzip.Name)},
	} {
		interopgrpc.DoEmptyUnaryCall(console.NewTB(), client, args...)
		interopgrpc.DoLargeUnaryCall(console.NewTB(), client, args...)
		interopgrpc.DoClientStreaming(console.NewTB(), client, args...)
		interopgrpc.DoServerStreaming(console.NewTB(), client, args...)
		interopgrpc.DoPingPong(console.NewTB(), client, args...)
		interopgrpc.DoEmptyStream(console.NewTB(), client, args...)
		interopgrpc.DoTimeoutOnSleepingServer(console.NewTB(), client, args...)
		interopgrpc.DoCancelAfterBegin(console.NewTB(), client, args...)
		interopgrpc.DoCancelAfterFirstResponse(console.NewTB(), client, args...)
		interopgrpc.DoCustomMetadata(console.NewTB(), client, args...)
		interopgrpc.DoStatusCodeAndMessage(console.NewTB(), client, args...)
		interopgrpc.DoSpecialStatusMessage(console.NewTB(), client, args...)
		interopgrpc.DoUnimplementedMethod(console.NewTB(), clientConn, args...)
		interopgrpc.DoUnimplementedServerStreamingMethod(console.NewTB(), client, args...)
		interopgrpc.DoFailWithNonASCIIError(console.NewTB(), client, args...)
		interopgrpc.DoFailServerStreamingWithNonASCIIError(console.NewTB(), client, args...)
		interopgrpc.DoFailServerStreamingAfterResponse(console.NewTB(), client, args...)
	}
	interopgrpc.DoUnimplementedService(console.NewTB(), conformance.NewUnimplementedServiceClient(clientConn))
	interopgrpc.DoUnimplementedServerStreamingService(console.NewTB(), conformance.NewUnimplementedServiceClient(clientConn))
	interopgrpc.DoUnresolvableHost(console.NewTB(), unresolvableClient)
}

func newTLSConfig(certFile, keyFile string) *tls.Config {
	cert, err := tls.LoadX509KeyPair(certFile, keyFile)
	if err != nil {
		log.Fatalf("Error creating x509 keypair from client cert file %s and client key file %s", certFile, keyFile)
	}
	caCert, err := os.ReadFile("cert/ConformanceCA.crt")
	if err != nil {
		log.Fatalf("Error opening cert file")
	}
	caCertPool := x509.NewCertPool()
	caCertPool.AppendCertsFromPEM(caCert)
	return &tls.Config{
		MinVersion:   tls.VersionTLS12,
		Certificates: []tls.Certificate{cert},
		RootCAs:      caCertPool,
	}
}
