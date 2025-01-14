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

// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: connectrpc/conformance/v1/test.proto

#include "connectrpc/conformance/v1/test.pb.h"

#include <algorithm>
#include "google/protobuf/io/coded_stream.h"
#include "google/protobuf/extension_set.h"
#include "google/protobuf/wire_format_lite.h"
#include "google/protobuf/descriptor.h"
#include "google/protobuf/generated_message_reflection.h"
#include "google/protobuf/reflection_ops.h"
#include "google/protobuf/wire_format.h"
// @@protoc_insertion_point(includes)

// Must be included last.
#include "google/protobuf/port_def.inc"
PROTOBUF_PRAGMA_INIT_SEG
namespace _pb = ::PROTOBUF_NAMESPACE_ID;
namespace _pbi = ::PROTOBUF_NAMESPACE_ID::internal;
namespace connectrpc {
namespace conformance {
namespace v1 {
}  // namespace v1
}  // namespace conformance
}  // namespace connectrpc
static constexpr const ::_pb::EnumDescriptor**
    file_level_enum_descriptors_connectrpc_2fconformance_2fv1_2ftest_2eproto = nullptr;
static constexpr const ::_pb::ServiceDescriptor**
    file_level_service_descriptors_connectrpc_2fconformance_2fv1_2ftest_2eproto = nullptr;
const ::uint32_t TableStruct_connectrpc_2fconformance_2fv1_2ftest_2eproto::offsets[1] = {};
static constexpr ::_pbi::MigrationSchema* schemas = nullptr;
static constexpr ::_pb::Message* const* file_default_instances = nullptr;
const char descriptor_table_protodef_connectrpc_2fconformance_2fv1_2ftest_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
    "\n$connectrpc/conformance/v1/test.proto\022\031"
    "connectrpc.conformance.v1\032(connectrpc/co"
    "nformance/v1/messages.proto\032\033google/prot"
    "obuf/empty.proto2\305\t\n\013TestService\022;\n\tEmpt"
    "yCall\022\026.google.protobuf.Empty\032\026.google.p"
    "rotobuf.Empty\022`\n\tUnaryCall\022(.connectrpc."
    "conformance.v1.SimpleRequest\032).connectrp"
    "c.conformance.v1.SimpleResponse\022d\n\rFailU"
    "naryCall\022(.connectrpc.conformance.v1.Sim"
    "pleRequest\032).connectrpc.conformance.v1.S"
    "impleResponse\022n\n\022CacheableUnaryCall\022(.co"
    "nnectrpc.conformance.v1.SimpleRequest\032)."
    "connectrpc.conformance.v1.SimpleResponse"
    "\"\003\220\002\001\022\206\001\n\023StreamingOutputCall\0225.connectr"
    "pc.conformance.v1.StreamingOutputCallReq"
    "uest\0326.connectrpc.conformance.v1.Streami"
    "ngOutputCallResponse0\001\022\212\001\n\027FailStreaming"
    "OutputCall\0225.connectrpc.conformance.v1.S"
    "treamingOutputCallRequest\0326.connectrpc.c"
    "onformance.v1.StreamingOutputCallRespons"
    "e0\001\022\203\001\n\022StreamingInputCall\0224.connectrpc."
    "conformance.v1.StreamingInputCallRequest"
    "\0325.connectrpc.conformance.v1.StreamingIn"
    "putCallResponse(\001\022\203\001\n\016FullDuplexCall\0225.c"
    "onnectrpc.conformance.v1.StreamingOutput"
    "CallRequest\0326.connectrpc.conformance.v1."
    "StreamingOutputCallResponse(\0010\001\022\203\001\n\016Half"
    "DuplexCall\0225.connectrpc.conformance.v1.S"
    "treamingOutputCallRequest\0326.connectrpc.c"
    "onformance.v1.StreamingOutputCallRespons"
    "e(\0010\001\022C\n\021UnimplementedCall\022\026.google.prot"
    "obuf.Empty\032\026.google.protobuf.Empty\022T\n Un"
    "implementedStreamingOutputCall\022\026.google."
    "protobuf.Empty\032\026.google.protobuf.Empty0\001"
    "2\261\001\n\024UnimplementedService\022C\n\021Unimplement"
    "edCall\022\026.google.protobuf.Empty\032\026.google."
    "protobuf.Empty\022T\n UnimplementedStreaming"
    "OutputCall\022\026.google.protobuf.Empty\032\026.goo"
    "gle.protobuf.Empty0\0012\251\001\n\020ReconnectServic"
    "e\022K\n\005Start\022*.connectrpc.conformance.v1.R"
    "econnectParams\032\026.google.protobuf.Empty\022H"
    "\n\004Stop\022\026.google.protobuf.Empty\032(.connect"
    "rpc.conformance.v1.ReconnectInfo2\272\002\n\030Loa"
    "dBalancerStatsService\022}\n\016GetClientStats\022"
    "3.connectrpc.conformance.v1.LoadBalancer"
    "StatsRequest\0324.connectrpc.conformance.v1"
    ".LoadBalancerStatsResponse\"\000\022\236\001\n\031GetClie"
    "ntAccumulatedStats\022>.connectrpc.conforma"
    "nce.v1.LoadBalancerAccumulatedStatsReque"
    "st\032\?.connectrpc.conformance.v1.LoadBalan"
    "cerAccumulatedStatsResponse\"\0002\227\001\n\026XdsUpd"
    "ateHealthService\022<\n\nSetServing\022\026.google."
    "protobuf.Empty\032\026.google.protobuf.Empty\022\?"
    "\n\rSetNotServing\022\026.google.protobuf.Empty\032"
    "\026.google.protobuf.Empty2\225\001\n\037XdsUpdateCli"
    "entConfigureService\022r\n\tConfigure\0221.conne"
    "ctrpc.conformance.v1.ClientConfigureRequ"
    "est\0322.connectrpc.conformance.v1.ClientCo"
    "nfigureResponseB\212\002\n\035com.connectrpc.confo"
    "rmance.v1B\tTestProtoP\001ZXconnectrpc.com/c"
    "onformance/internal/gen/proto/go/connect"
    "rpc/conformance/v1;conformancev1\242\002\003CCX\252\002"
    "\031Connectrpc.Conformance.V1\312\002\031Connectrpc\\"
    "Conformance\\V1\342\002%Connectrpc\\Conformance\\"
    "V1\\GPBMetadata\352\002\033Connectrpc::Conformance"
    "::V1b\006proto3"
};
static const ::_pbi::DescriptorTable* const descriptor_table_connectrpc_2fconformance_2fv1_2ftest_2eproto_deps[2] =
    {
        &::descriptor_table_connectrpc_2fconformance_2fv1_2fmessages_2eproto,
        &::descriptor_table_google_2fprotobuf_2fempty_2eproto,
};
static ::absl::once_flag descriptor_table_connectrpc_2fconformance_2fv1_2ftest_2eproto_once;
const ::_pbi::DescriptorTable descriptor_table_connectrpc_2fconformance_2fv1_2ftest_2eproto = {
    false,
    false,
    2612,
    descriptor_table_protodef_connectrpc_2fconformance_2fv1_2ftest_2eproto,
    "connectrpc/conformance/v1/test.proto",
    &descriptor_table_connectrpc_2fconformance_2fv1_2ftest_2eproto_once,
    descriptor_table_connectrpc_2fconformance_2fv1_2ftest_2eproto_deps,
    2,
    0,
    schemas,
    file_default_instances,
    TableStruct_connectrpc_2fconformance_2fv1_2ftest_2eproto::offsets,
    nullptr,
    file_level_enum_descriptors_connectrpc_2fconformance_2fv1_2ftest_2eproto,
    file_level_service_descriptors_connectrpc_2fconformance_2fv1_2ftest_2eproto,
};

// This function exists to be marked as weak.
// It can significantly speed up compilation by breaking up LLVM's SCC
// in the .pb.cc translation units. Large translation units see a
// reduction of more than 35% of walltime for optimized builds. Without
// the weak attribute all the messages in the file, including all the
// vtables and everything they use become part of the same SCC through
// a cycle like:
// GetMetadata -> descriptor table -> default instances ->
//   vtables -> GetMetadata
// By adding a weak function here we break the connection from the
// individual vtables back into the descriptor table.
PROTOBUF_ATTRIBUTE_WEAK const ::_pbi::DescriptorTable* descriptor_table_connectrpc_2fconformance_2fv1_2ftest_2eproto_getter() {
  return &descriptor_table_connectrpc_2fconformance_2fv1_2ftest_2eproto;
}
// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY2
static ::_pbi::AddDescriptorsRunner dynamic_init_dummy_connectrpc_2fconformance_2fv1_2ftest_2eproto(&descriptor_table_connectrpc_2fconformance_2fv1_2ftest_2eproto);
namespace connectrpc {
namespace conformance {
namespace v1 {
// @@protoc_insertion_point(namespace_scope)
}  // namespace v1
}  // namespace conformance
}  // namespace connectrpc
PROTOBUF_NAMESPACE_OPEN
PROTOBUF_NAMESPACE_CLOSE
// @@protoc_insertion_point(global_scope)
#include "google/protobuf/port_undef.inc"
