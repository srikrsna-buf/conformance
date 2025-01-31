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

package interopconnect

import (
	"context"
	"errors"
	"fmt"
	"io"
	"time"

	conformanceconnect "connectrpc.com/conformance/internal/gen/proto/connect/connectrpc/conformance/v1/conformancev1connect"
	conformance "connectrpc.com/conformance/internal/gen/proto/go/connectrpc/conformance/v1"
	"connectrpc.com/conformance/internal/interop"
	"connectrpc.com/connect"
	"google.golang.org/protobuf/types/known/emptypb"
)

// NewTestServiceHandler returns a new TestServiceHandler.
func NewTestServiceHandler() conformanceconnect.TestServiceHandler {
	return &testServer{}
}

type testServer struct {
	conformanceconnect.UnimplementedTestServiceHandler
}

func (s *testServer) CacheableUnaryCall(ctx context.Context, request *connect.Request[conformance.SimpleRequest]) (*connect.Response[conformance.SimpleResponse], error) {
	response, err := s.UnaryCall(ctx, request)
	if response != nil {
		if request.Peer().Query.Has("message") {
			response.Header().Set("Get-Request", "true")
		}
	}
	return response, err
}

func (s *testServer) EmptyCall(ctx context.Context, request *connect.Request[emptypb.Empty]) (*connect.Response[emptypb.Empty], error) {
	return connect.NewResponse(new(emptypb.Empty)), nil
}

func (s *testServer) UnaryCall(ctx context.Context, request *connect.Request[conformance.SimpleRequest]) (*connect.Response[conformance.SimpleResponse], error) {
	if status := request.Msg.GetResponseStatus(); status != nil && status.Code != 0 {
		return nil, connect.NewError(connect.Code(status.Code), errors.New(status.Message))
	}
	payload, err := newServerPayload(request.Msg.GetResponseType(), request.Msg.GetResponseSize())
	if err != nil {
		return nil, err
	}
	response := connect.NewResponse(
		&conformance.SimpleResponse{
			Payload: payload,
		},
	)
	if leadingMetadata := request.Header().Values(leadingMetadataKey); len(leadingMetadata) != 0 {
		for _, value := range leadingMetadata {
			response.Header().Add(leadingMetadataKey, value)
		}
	}
	if trailingMetadata := request.Header().Values(trailingMetadataKey); len(trailingMetadata) != 0 {
		for _, value := range trailingMetadata {
			decodedTrailingMetadata, err := connect.DecodeBinaryHeader(value)
			if err != nil {
				return nil, err
			}
			response.Trailer().Add(trailingMetadataKey, connect.EncodeBinaryHeader(decodedTrailingMetadata))
		}
	}
	response.Header().Set("Request-Protocol", request.Peer().Protocol)
	return response, nil
}

func (s *testServer) FailUnaryCall(ctx context.Context, request *connect.Request[conformance.SimpleRequest]) (*connect.Response[conformance.SimpleResponse], error) {
	err := connect.NewError(connect.CodeResourceExhausted, errors.New(interop.NonASCIIErrMsg))
	detail, detailErr := connect.NewErrorDetail(interop.ErrorDetail)
	if detailErr != nil {
		return nil, connect.NewError(connect.CodeInternal, errors.New("error when creating error details"))
	}
	err.AddDetail(detail)
	return nil, err
}

func (s *testServer) StreamingOutputCall(ctx context.Context, request *connect.Request[conformance.StreamingOutputCallRequest], stream *connect.ServerStream[conformance.StreamingOutputCallResponse]) error {
	if leadingMetadata := request.Header().Values(leadingMetadataKey); len(leadingMetadata) != 0 {
		for _, value := range leadingMetadata {
			stream.ResponseHeader().Add(leadingMetadataKey, value)
		}
	}
	if trailingMetadata := request.Header().Values(trailingMetadataKey); len(trailingMetadata) != 0 {
		for _, value := range trailingMetadata {
			decodedTrailingMetadata, err := connect.DecodeBinaryHeader(value)
			if err != nil {
				return err
			}
			stream.ResponseTrailer().Add(trailingMetadataKey, connect.EncodeBinaryHeader(decodedTrailingMetadata))
		}
	}
	for _, param := range request.Msg.GetResponseParameters() {
		if us := param.GetIntervalUs(); us > 0 {
			time.Sleep(time.Duration(us) * time.Microsecond)
		}
		// Checking if the context is canceled or deadline exceeded, in a real world usage it will
		// make more sense to put this checking before the expensive works (i.e. the time.Sleep above),
		// but in order to simulate a network latency issue, we put the context checking here.
		if err := ctx.Err(); err != nil {
			return err
		}
		payload, err := newServerPayload(request.Msg.GetResponseType(), param.GetSize())
		if err != nil {
			return err
		}
		if err := stream.Send(&conformance.StreamingOutputCallResponse{
			Payload: payload,
		}); err != nil {
			return err
		}
	}
	if status := request.Msg.GetResponseStatus(); status != nil && status.Code != 0 {
		return connect.NewError(connect.Code(status.Code), errors.New(status.Message))
	}
	return nil
}

func (s *testServer) FailStreamingOutputCall(ctx context.Context, request *connect.Request[conformance.StreamingOutputCallRequest], stream *connect.ServerStream[conformance.StreamingOutputCallResponse]) error {
	for _, param := range request.Msg.GetResponseParameters() {
		if us := param.GetIntervalUs(); us > 0 {
			time.Sleep(time.Duration(us) * time.Microsecond)
		}
		// Checking if the context is canceled or deadline exceeded, in a real world usage it will
		// make more sense to put this checking before the expensive works (i.e. the time.Sleep above),
		// but in order to simulate a network latency issue, we put the context checking here.
		if err := ctx.Err(); err != nil {
			return err
		}
		payload, err := newServerPayload(request.Msg.GetResponseType(), param.GetSize())
		if err != nil {
			return err
		}
		if err := stream.Send(&conformance.StreamingOutputCallResponse{
			Payload: payload,
		}); err != nil {
			return err
		}
	}
	err := connect.NewError(connect.CodeResourceExhausted, errors.New(interop.NonASCIIErrMsg))
	detail, detailErr := connect.NewErrorDetail(interop.ErrorDetail)
	if detailErr != nil {
		return connect.NewError(connect.CodeInternal, errors.New("error when creating error details"))
	}
	err.AddDetail(detail)
	return err
}

func (s *testServer) StreamingInputCall(ctx context.Context, stream *connect.ClientStream[conformance.StreamingInputCallRequest]) (*connect.Response[conformance.StreamingInputCallResponse], error) {
	var sum int
	for stream.Receive() {
		if err := ctx.Err(); err != nil {
			return nil, err
		}
		p := stream.Msg().GetPayload().GetBody()
		sum += len(p)
	}
	if err := stream.Err(); err != nil {
		return nil, err
	}
	return connect.NewResponse(
		&conformance.StreamingInputCallResponse{
			AggregatedPayloadSize: int32(sum),
		},
	), nil
}

func (s *testServer) FullDuplexCall(ctx context.Context, stream *connect.BidiStream[conformance.StreamingOutputCallRequest, conformance.StreamingOutputCallResponse]) error {
	if leadingMetadata := stream.RequestHeader().Values(leadingMetadataKey); len(leadingMetadata) != 0 {
		for _, value := range leadingMetadata {
			stream.ResponseHeader().Add(leadingMetadataKey, value)
		}
	}
	if trailingMetadata := stream.RequestHeader().Values(trailingMetadataKey); len(trailingMetadata) != 0 {
		for _, value := range trailingMetadata {
			decodedTrailingMetadata, err := connect.DecodeBinaryHeader(value)
			if err != nil {
				return err
			}
			stream.ResponseTrailer().Add(trailingMetadataKey, connect.EncodeBinaryHeader(decodedTrailingMetadata))
		}
	}
	for {
		if err := ctx.Err(); err != nil {
			return err
		}
		request, err := stream.Receive()
		if errors.Is(err, io.EOF) {
			// read done.
			return nil
		} else if err != nil {
			return err
		}
		st := request.GetResponseStatus()
		if st != nil && st.Code != 0 {
			return connect.NewError(connect.Code(st.Code), errors.New(st.Message))
		}
		cs := request.GetResponseParameters()
		for _, c := range cs {
			if us := c.GetIntervalUs(); us > 0 {
				time.Sleep(time.Duration(us) * time.Microsecond)
			}
			payload, err := newServerPayload(request.GetResponseType(), c.GetSize())
			if err != nil {
				return err
			}
			if err := stream.Send(&conformance.StreamingOutputCallResponse{
				Payload: payload,
			}); err != nil {
				return err
			}
		}
	}
}

func (s *testServer) HalfDuplexCall(ctx context.Context, stream *connect.BidiStream[conformance.StreamingOutputCallRequest, conformance.StreamingOutputCallResponse]) error {
	var msgBuf []*conformance.StreamingOutputCallRequest
	for {
		if err := ctx.Err(); err != nil {
			return err
		}
		request, err := stream.Receive()
		if errors.Is(err, io.EOF) {
			// read done.
			break
		}
		if err != nil {
			return err
		}
		msgBuf = append(msgBuf, request)
	}
	for _, msg := range msgBuf {
		cs := msg.GetResponseParameters()
		for _, c := range cs {
			if us := c.GetIntervalUs(); us > 0 {
				time.Sleep(time.Duration(us) * time.Microsecond)
			}
			payload, err := newServerPayload(msg.GetResponseType(), c.GetSize())
			if err != nil {
				return err
			}
			if err := stream.Send(&conformance.StreamingOutputCallResponse{
				Payload: payload,
			}); err != nil {
				return err
			}
		}
	}
	return nil
}

func newServerPayload(payloadType conformance.PayloadType, size int32) (*conformance.Payload, error) {
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
