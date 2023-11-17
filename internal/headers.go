// Copyright 2023 The Connect Authors
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

package internal

import (
	"net/http"

	v2 "connectrpc.com/conformance/internal/gen/proto/go/connectrpc/conformance/v2"
)

// AddHeaders adds all header values in src to dest.
func AddHeaders(
	src []*v2.Header,
	dest http.Header,
) {
	for _, header := range src {
		for _, val := range header.Value {
			dest.Add(header.Name, val)
		}
	}
}

// ConvertToProtoHeader converts HTTP headers to a slice of proto Headers.
func ConvertToProtoHeader(
	src http.Header,
) []*v2.Header {
	headerInfo := make([]*v2.Header, 0, len(src))
	for key, value := range src {
		hdr := &v2.Header{
			Name:  key,
			Value: value,
		}
		headerInfo = append(headerInfo, hdr)
	}
	return headerInfo
}