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

// This is the test server implementation from the grpc-go interop test_utils.go file,
// https://github.com/grpc/grpc-go/blob/master/interop/test_utils.go

/*
 *
 * Copyright 2014 gRPC authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

package interopgrpc

import (
	"context"
	"errors"
	"fmt"
	"io"
	"time"

	conformance "connectrpc.com/conformance/internal/gen/proto/go/connectrpc/conformance/v1"
	"connectrpc.com/conformance/internal/interop"
	"google.golang.org/grpc"
	"google.golang.org/grpc/codes"
	"google.golang.org/grpc/metadata"
	"google.golang.org/grpc/status"
	"google.golang.org/protobuf/types/known/emptypb"
)

// NewTestServer creates a test server for test service.
func NewTestServer() conformance.TestServiceServer {
	return &testServer{}
}

type testServer struct {
	conformance.UnimplementedTestServiceServer
}

func (s *testServer) EmptyCall(ctx context.Context, in *emptypb.Empty) (*emptypb.Empty, error) {
	return new(emptypb.Empty), nil
}

func serverNewPayload(payloadType conformance.PayloadType, size int32) (*conformance.Payload, error) {
	if size < 0 {
		return nil, fmt.Errorf("requested a response with invalid length %d", size)
	}
	body := make([]byte, size)
	switch payloadType {
	case conformance.PayloadType_COMPRESSABLE:
	default:
		return nil, fmt.Errorf("unsupported payload type: %d", payloadType)
	}
	return &conformance.Payload{
		Type: payloadType,
		Body: body,
	}, nil
}

func createMetadataPairs(metadataKey string, metadata []string) []string {
	metadataPairs := make([]string, len(metadata)*2)
	for i, metadataValue := range metadata {
		metadataPairs[i*2] = metadataKey
		metadataPairs[i*2+1] = metadataValue
	}
	return metadataPairs
}

func (s *testServer) UnaryCall(ctx context.Context, req *conformance.SimpleRequest) (*conformance.SimpleResponse, error) {
	responseStatus := req.GetResponseStatus()
	var header, trailer metadata.MD
	if data, ok := metadata.FromIncomingContext(ctx); ok {
		if leadingMetadata, ok := data[leadingMetadataKey]; ok {
			metadataPairs := createMetadataPairs(leadingMetadataKey, leadingMetadata)
			header = metadata.Pairs(metadataPairs...)
		}
		if trailingMetadata, ok := data[trailingMetadataKey]; ok {
			trailingMetadataPairs := createMetadataPairs(trailingMetadataKey, trailingMetadata)
			trailer = metadata.Pairs(trailingMetadataPairs...)
		}
	}
	header = metadata.Join(header, metadata.Pairs("Request-Protocol", "grpc"))
	if header != nil {
		if err := grpc.SendHeader(ctx, header); err != nil {
			return nil, err
		}
	}
	if trailer != nil {
		if err := grpc.SetTrailer(ctx, trailer); err != nil {
			return nil, err
		}
	}
	if responseStatus != nil && responseStatus.Code != 0 {
		return nil, status.Error(codes.Code(responseStatus.Code), responseStatus.Message)
	}
	pl, err := serverNewPayload(req.GetResponseType(), req.GetResponseSize())
	if err != nil {
		return nil, err
	}
	return &conformance.SimpleResponse{
		Payload: pl,
	}, nil
}

func (s *testServer) CacheableUnaryCall(ctx context.Context, request *conformance.SimpleRequest) (*conformance.SimpleResponse, error) {
	return s.UnaryCall(ctx, request)
}

// FailUnaryCall is an additional RPC added for conformance.
func (s *testServer) FailUnaryCall(ctx context.Context, in *conformance.SimpleRequest) (*conformance.SimpleResponse, error) {
	errStatus := status.New(codes.ResourceExhausted, interop.NonASCIIErrMsg)
	errStatus, err := errStatus.WithDetails(interop.ErrorDetail)
	if err != nil {
		return nil, status.Error(codes.Internal, "error when adding error details")
	}
	return nil, errStatus.Err()
}

func (s *testServer) StreamingOutputCall(args *conformance.StreamingOutputCallRequest, stream conformance.TestService_StreamingOutputCallServer) error {
	responseStatus := args.GetResponseStatus()
	if data, ok := metadata.FromIncomingContext(stream.Context()); ok {
		if leadingMetadata, ok := data[leadingMetadataKey]; ok {
			var metadataPairs []string
			for _, metadataValue := range leadingMetadata {
				metadataPairs = append(metadataPairs, leadingMetadataKey)
				metadataPairs = append(metadataPairs, metadataValue)
			}
			header := metadata.Pairs(metadataPairs...)
			if err := stream.SendHeader(header); err != nil {
				return err
			}
		}
		if trailingMetadata, ok := data[trailingMetadataKey]; ok {
			var trailingMetadataPairs []string
			for _, trailingMetadataValue := range trailingMetadata {
				trailingMetadataPairs = append(trailingMetadataPairs, trailingMetadataKey)
				trailingMetadataPairs = append(trailingMetadataPairs, trailingMetadataValue)
			}
			trailer := metadata.Pairs(trailingMetadataPairs...)
			stream.SetTrailer(trailer)
		}
	}
	cs := args.GetResponseParameters()
	for _, responseParameter := range cs {
		if us := responseParameter.GetIntervalUs(); us > 0 {
			time.Sleep(time.Duration(us) * time.Microsecond)
		}
		// Checking if the context is canceled or deadline exceeded, in a real world usage it will
		// make more sense to put this checking before the expensive works (i.e. the time.Sleep above),
		// but in order to simulate a network latency issue, we put the context checking here.
		if err := stream.Context().Err(); err != nil {
			return err
		}
		pl, err := serverNewPayload(args.GetResponseType(), responseParameter.GetSize())
		if err != nil {
			return err
		}
		if err := stream.Send(&conformance.StreamingOutputCallResponse{
			Payload: pl,
		}); err != nil {
			return err
		}
	}
	if responseStatus != nil && responseStatus.Code != 0 {
		return status.Error(codes.Code(responseStatus.Code), responseStatus.Message)
	}
	return nil
}

func (s *testServer) FailStreamingOutputCall(args *conformance.StreamingOutputCallRequest, stream conformance.TestService_FailStreamingOutputCallServer) error {
	cs := args.GetResponseParameters()
	for _, responseParameter := range cs {
		if us := responseParameter.GetIntervalUs(); us > 0 {
			time.Sleep(time.Duration(us) * time.Microsecond)
		}
		// Checking if the context is canceled or deadline exceeded, in a real world usage it will
		// make more sense to put this checking before the expensive works (i.e. the time.Sleep above),
		// but in order to simulate a network latency issue, we put the context checking here.
		if err := stream.Context().Err(); err != nil {
			return err
		}
		pl, err := serverNewPayload(args.GetResponseType(), responseParameter.GetSize())
		if err != nil {
			return err
		}
		if err := stream.Send(&conformance.StreamingOutputCallResponse{
			Payload: pl,
		}); err != nil {
			return err
		}
	}
	errStatus := status.New(codes.ResourceExhausted, interop.NonASCIIErrMsg)
	errStatus, err := errStatus.WithDetails(interop.ErrorDetail)
	if err != nil {
		return status.Error(codes.Internal, "error when adding error details")
	}
	return errStatus.Err()
}

func (s *testServer) StreamingInputCall(stream conformance.TestService_StreamingInputCallServer) error {
	var sum int
	for {
		req, err := stream.Recv()
		if errors.Is(err, io.EOF) {
			return stream.SendAndClose(&conformance.StreamingInputCallResponse{
				AggregatedPayloadSize: int32(sum),
			})
		}
		if err != nil {
			return err
		}
		if err := stream.Context().Err(); err != nil {
			return err
		}
		p := req.GetPayload().GetBody()
		sum += len(p)
	}
}

func (s *testServer) FullDuplexCall(stream conformance.TestService_FullDuplexCallServer) error {
	if data, ok := metadata.FromIncomingContext(stream.Context()); ok {
		if leadingMetadata, ok := data[leadingMetadataKey]; ok {
			var metadataPairs []string
			for _, metadataValue := range leadingMetadata {
				metadataPairs = append(metadataPairs, leadingMetadataKey)
				metadataPairs = append(metadataPairs, metadataValue)
			}
			header := metadata.Pairs(metadataPairs...)
			if err := stream.SendHeader(header); err != nil {
				return err
			}
		}
		if trailingMetadata, ok := data[trailingMetadataKey]; ok {
			var trailingMetadataPairs []string
			for _, trailingMetadataValue := range trailingMetadata {
				trailingMetadataPairs = append(trailingMetadataPairs, trailingMetadataKey)
				trailingMetadataPairs = append(trailingMetadataPairs, trailingMetadataValue)
			}
			trailer := metadata.Pairs(trailingMetadataPairs...)
			stream.SetTrailer(trailer)
		}
	}
	for {
		if err := stream.Context().Err(); err != nil {
			return err
		}
		req, err := stream.Recv()
		if errors.Is(err, io.EOF) {
			// read done.
			return nil
		}
		if err != nil {
			return err
		}
		st := req.GetResponseStatus()
		if st != nil && st.Code != 0 {
			return status.Error(codes.Code(st.Code), st.Message)
		}
		cs := req.GetResponseParameters()
		for _, c := range cs {
			if us := c.GetIntervalUs(); us > 0 {
				time.Sleep(time.Duration(us) * time.Microsecond)
			}
			pl, err := serverNewPayload(req.GetResponseType(), c.GetSize())
			if err != nil {
				return err
			}
			if err := stream.Send(&conformance.StreamingOutputCallResponse{
				Payload: pl,
			}); err != nil {
				return err
			}
		}
	}
}

func (s *testServer) HalfDuplexCall(stream conformance.TestService_HalfDuplexCallServer) error {
	var msgBuf []*conformance.StreamingOutputCallRequest
	for {
		if err := stream.Context().Err(); err != nil {
			return err
		}
		req, err := stream.Recv()
		if errors.Is(err, io.EOF) {
			// read done.
			break
		}
		if err != nil {
			return err
		}
		msgBuf = append(msgBuf, req)
	}
	for _, msg := range msgBuf {
		cs := msg.GetResponseParameters()
		for _, c := range cs {
			if us := c.GetIntervalUs(); us > 0 {
				time.Sleep(time.Duration(us) * time.Microsecond)
			}
			pl, err := serverNewPayload(msg.GetResponseType(), c.GetSize())
			if err != nil {
				return err
			}
			if err := stream.Send(&conformance.StreamingOutputCallResponse{
				Payload: pl,
			}); err != nil {
				return err
			}
		}
	}
	return nil
}
