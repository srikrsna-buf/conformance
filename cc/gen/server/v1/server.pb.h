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
// source: server/v1/server.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_server_2fv1_2fserver_2eproto_2epb_2eh
#define GOOGLE_PROTOBUF_INCLUDED_server_2fv1_2fserver_2eproto_2epb_2eh

#include <limits>
#include <string>
#include <type_traits>

#include "google/protobuf/port_def.inc"
#if PROTOBUF_VERSION < 4023000
#error "This file was generated by a newer version of protoc which is"
#error "incompatible with your Protocol Buffer headers. Please update"
#error "your headers."
#endif  // PROTOBUF_VERSION

#if 4023004 < PROTOBUF_MIN_PROTOC_VERSION
#error "This file was generated by an older version of protoc which is"
#error "incompatible with your Protocol Buffer headers. Please"
#error "regenerate this file with a newer version of protoc."
#endif  // PROTOBUF_MIN_PROTOC_VERSION
#include "google/protobuf/port_undef.inc"
#include "google/protobuf/io/coded_stream.h"
#include "google/protobuf/arena.h"
#include "google/protobuf/arenastring.h"
#include "google/protobuf/generated_message_util.h"
#include "google/protobuf/metadata_lite.h"
#include "google/protobuf/generated_message_reflection.h"
#include "google/protobuf/message.h"
#include "google/protobuf/repeated_field.h"  // IWYU pragma: export
#include "google/protobuf/extension_set.h"  // IWYU pragma: export
#include "google/protobuf/generated_enum_reflection.h"
#include "google/protobuf/unknown_field_set.h"
// @@protoc_insertion_point(includes)

// Must be included last.
#include "google/protobuf/port_def.inc"

#define PROTOBUF_INTERNAL_EXPORT_server_2fv1_2fserver_2eproto

PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_server_2fv1_2fserver_2eproto {
  static const ::uint32_t offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable
    descriptor_table_server_2fv1_2fserver_2eproto;
namespace server {
namespace v1 {
class HTTPVersion;
struct HTTPVersionDefaultTypeInternal;
extern HTTPVersionDefaultTypeInternal _HTTPVersion_default_instance_;
class ProtocolSupport;
struct ProtocolSupportDefaultTypeInternal;
extern ProtocolSupportDefaultTypeInternal _ProtocolSupport_default_instance_;
class ServerMetadata;
struct ServerMetadataDefaultTypeInternal;
extern ServerMetadataDefaultTypeInternal _ServerMetadata_default_instance_;
}  // namespace v1
}  // namespace server
PROTOBUF_NAMESPACE_OPEN
template <>
::server::v1::HTTPVersion* Arena::CreateMaybeMessage<::server::v1::HTTPVersion>(Arena*);
template <>
::server::v1::ProtocolSupport* Arena::CreateMaybeMessage<::server::v1::ProtocolSupport>(Arena*);
template <>
::server::v1::ServerMetadata* Arena::CreateMaybeMessage<::server::v1::ServerMetadata>(Arena*);
PROTOBUF_NAMESPACE_CLOSE

namespace server {
namespace v1 {
enum Protocol : int {
  PROTOCOL_UNSPECIFIED = 0,
  PROTOCOL_GRPC = 1,
  PROTOCOL_GRPC_WEB = 2,
  Protocol_INT_MIN_SENTINEL_DO_NOT_USE_ =
      std::numeric_limits<::int32_t>::min(),
  Protocol_INT_MAX_SENTINEL_DO_NOT_USE_ =
      std::numeric_limits<::int32_t>::max(),
};

bool Protocol_IsValid(int value);
constexpr Protocol Protocol_MIN = static_cast<Protocol>(0);
constexpr Protocol Protocol_MAX = static_cast<Protocol>(2);
constexpr int Protocol_ARRAYSIZE = 2 + 1;
const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor*
Protocol_descriptor();
template <typename T>
const std::string& Protocol_Name(T value) {
  static_assert(std::is_same<T, Protocol>::value ||
                    std::is_integral<T>::value,
                "Incorrect type passed to Protocol_Name().");
  return Protocol_Name(static_cast<Protocol>(value));
}
template <>
inline const std::string& Protocol_Name(Protocol value) {
  return ::PROTOBUF_NAMESPACE_ID::internal::NameOfDenseEnum<Protocol_descriptor,
                                                 0, 2>(
      static_cast<int>(value));
}
inline bool Protocol_Parse(absl::string_view name, Protocol* value) {
  return ::PROTOBUF_NAMESPACE_ID::internal::ParseNamedEnum<Protocol>(
      Protocol_descriptor(), name, value);
}

// ===================================================================


// -------------------------------------------------------------------

class ServerMetadata final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:server.v1.ServerMetadata) */ {
 public:
  inline ServerMetadata() : ServerMetadata(nullptr) {}
  ~ServerMetadata() override;
  template<typename = void>
  explicit PROTOBUF_CONSTEXPR ServerMetadata(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  ServerMetadata(const ServerMetadata& from);
  ServerMetadata(ServerMetadata&& from) noexcept
    : ServerMetadata() {
    *this = ::std::move(from);
  }

  inline ServerMetadata& operator=(const ServerMetadata& from) {
    CopyFrom(from);
    return *this;
  }
  inline ServerMetadata& operator=(ServerMetadata&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  inline const ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance);
  }
  inline ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const ServerMetadata& default_instance() {
    return *internal_default_instance();
  }
  static inline const ServerMetadata* internal_default_instance() {
    return reinterpret_cast<const ServerMetadata*>(
               &_ServerMetadata_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(ServerMetadata& a, ServerMetadata& b) {
    a.Swap(&b);
  }
  inline void Swap(ServerMetadata* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(ServerMetadata* other) {
    if (other == this) return;
    ABSL_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  ServerMetadata* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<ServerMetadata>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const ServerMetadata& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom( const ServerMetadata& from) {
    ServerMetadata::MergeImpl(*this, from);
  }
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  ::size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::uint8_t* _InternalSerialize(
      ::uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(ServerMetadata* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::absl::string_view FullMessageName() {
    return "server.v1.ServerMetadata";
  }
  protected:
  explicit ServerMetadata(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kProtocolsFieldNumber = 2,
    kHostFieldNumber = 1,
  };
  // repeated .server.v1.ProtocolSupport protocols = 2 [json_name = "protocols"];
  int protocols_size() const;
  private:
  int _internal_protocols_size() const;

  public:
  void clear_protocols() ;
  ::server::v1::ProtocolSupport* mutable_protocols(int index);
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::server::v1::ProtocolSupport >*
      mutable_protocols();
  private:
  const ::server::v1::ProtocolSupport& _internal_protocols(int index) const;
  ::server::v1::ProtocolSupport* _internal_add_protocols();
  const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField<::server::v1::ProtocolSupport>& _internal_protocols() const;
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField<::server::v1::ProtocolSupport>* _internal_mutable_protocols();
  public:
  const ::server::v1::ProtocolSupport& protocols(int index) const;
  ::server::v1::ProtocolSupport* add_protocols();
  const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::server::v1::ProtocolSupport >&
      protocols() const;
  // string host = 1 [json_name = "host"];
  void clear_host() ;
  const std::string& host() const;




  template <typename Arg_ = const std::string&, typename... Args_>
  void set_host(Arg_&& arg, Args_... args);
  std::string* mutable_host();
  PROTOBUF_NODISCARD std::string* release_host();
  void set_allocated_host(std::string* ptr);

  private:
  const std::string& _internal_host() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_host(
      const std::string& value);
  std::string* _internal_mutable_host();

  public:
  // @@protoc_insertion_point(class_scope:server.v1.ServerMetadata)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
    ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::server::v1::ProtocolSupport > protocols_;
    ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr host_;
    mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_server_2fv1_2fserver_2eproto;
};// -------------------------------------------------------------------

class ProtocolSupport final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:server.v1.ProtocolSupport) */ {
 public:
  inline ProtocolSupport() : ProtocolSupport(nullptr) {}
  ~ProtocolSupport() override;
  template<typename = void>
  explicit PROTOBUF_CONSTEXPR ProtocolSupport(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  ProtocolSupport(const ProtocolSupport& from);
  ProtocolSupport(ProtocolSupport&& from) noexcept
    : ProtocolSupport() {
    *this = ::std::move(from);
  }

  inline ProtocolSupport& operator=(const ProtocolSupport& from) {
    CopyFrom(from);
    return *this;
  }
  inline ProtocolSupport& operator=(ProtocolSupport&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  inline const ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance);
  }
  inline ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const ProtocolSupport& default_instance() {
    return *internal_default_instance();
  }
  static inline const ProtocolSupport* internal_default_instance() {
    return reinterpret_cast<const ProtocolSupport*>(
               &_ProtocolSupport_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  friend void swap(ProtocolSupport& a, ProtocolSupport& b) {
    a.Swap(&b);
  }
  inline void Swap(ProtocolSupport* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(ProtocolSupport* other) {
    if (other == this) return;
    ABSL_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  ProtocolSupport* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<ProtocolSupport>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const ProtocolSupport& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom( const ProtocolSupport& from) {
    ProtocolSupport::MergeImpl(*this, from);
  }
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  ::size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::uint8_t* _InternalSerialize(
      ::uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(ProtocolSupport* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::absl::string_view FullMessageName() {
    return "server.v1.ProtocolSupport";
  }
  protected:
  explicit ProtocolSupport(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kHttpVersionsFieldNumber = 2,
    kPortFieldNumber = 3,
    kProtocolFieldNumber = 1,
  };
  // repeated .server.v1.HTTPVersion http_versions = 2 [json_name = "httpVersions"];
  int http_versions_size() const;
  private:
  int _internal_http_versions_size() const;

  public:
  void clear_http_versions() ;
  ::server::v1::HTTPVersion* mutable_http_versions(int index);
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::server::v1::HTTPVersion >*
      mutable_http_versions();
  private:
  const ::server::v1::HTTPVersion& _internal_http_versions(int index) const;
  ::server::v1::HTTPVersion* _internal_add_http_versions();
  const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField<::server::v1::HTTPVersion>& _internal_http_versions() const;
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField<::server::v1::HTTPVersion>* _internal_mutable_http_versions();
  public:
  const ::server::v1::HTTPVersion& http_versions(int index) const;
  ::server::v1::HTTPVersion* add_http_versions();
  const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::server::v1::HTTPVersion >&
      http_versions() const;
  // string port = 3 [json_name = "port"];
  void clear_port() ;
  const std::string& port() const;




  template <typename Arg_ = const std::string&, typename... Args_>
  void set_port(Arg_&& arg, Args_... args);
  std::string* mutable_port();
  PROTOBUF_NODISCARD std::string* release_port();
  void set_allocated_port(std::string* ptr);

  private:
  const std::string& _internal_port() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_port(
      const std::string& value);
  std::string* _internal_mutable_port();

  public:
  // .server.v1.Protocol protocol = 1 [json_name = "protocol"];
  void clear_protocol() ;
  ::server::v1::Protocol protocol() const;
  void set_protocol(::server::v1::Protocol value);

  private:
  ::server::v1::Protocol _internal_protocol() const;
  void _internal_set_protocol(::server::v1::Protocol value);

  public:
  // @@protoc_insertion_point(class_scope:server.v1.ProtocolSupport)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
    ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::server::v1::HTTPVersion > http_versions_;
    ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr port_;
    int protocol_;
    mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_server_2fv1_2fserver_2eproto;
};// -------------------------------------------------------------------

class HTTPVersion final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:server.v1.HTTPVersion) */ {
 public:
  inline HTTPVersion() : HTTPVersion(nullptr) {}
  ~HTTPVersion() override;
  template<typename = void>
  explicit PROTOBUF_CONSTEXPR HTTPVersion(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  HTTPVersion(const HTTPVersion& from);
  HTTPVersion(HTTPVersion&& from) noexcept
    : HTTPVersion() {
    *this = ::std::move(from);
  }

  inline HTTPVersion& operator=(const HTTPVersion& from) {
    CopyFrom(from);
    return *this;
  }
  inline HTTPVersion& operator=(HTTPVersion&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  inline const ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance);
  }
  inline ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const HTTPVersion& default_instance() {
    return *internal_default_instance();
  }
  static inline const HTTPVersion* internal_default_instance() {
    return reinterpret_cast<const HTTPVersion*>(
               &_HTTPVersion_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    2;

  friend void swap(HTTPVersion& a, HTTPVersion& b) {
    a.Swap(&b);
  }
  inline void Swap(HTTPVersion* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(HTTPVersion* other) {
    if (other == this) return;
    ABSL_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  HTTPVersion* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<HTTPVersion>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const HTTPVersion& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom( const HTTPVersion& from) {
    HTTPVersion::MergeImpl(*this, from);
  }
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  ::size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::uint8_t* _InternalSerialize(
      ::uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(HTTPVersion* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::absl::string_view FullMessageName() {
    return "server.v1.HTTPVersion";
  }
  protected:
  explicit HTTPVersion(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kMajorFieldNumber = 1,
    kMinorFieldNumber = 2,
  };
  // int32 major = 1 [json_name = "major"];
  void clear_major() ;
  ::int32_t major() const;
  void set_major(::int32_t value);

  private:
  ::int32_t _internal_major() const;
  void _internal_set_major(::int32_t value);

  public:
  // int32 minor = 2 [json_name = "minor"];
  void clear_minor() ;
  ::int32_t minor() const;
  void set_minor(::int32_t value);

  private:
  ::int32_t _internal_minor() const;
  void _internal_set_minor(::int32_t value);

  public:
  // @@protoc_insertion_point(class_scope:server.v1.HTTPVersion)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
    ::int32_t major_;
    ::int32_t minor_;
    mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_server_2fv1_2fserver_2eproto;
};

// ===================================================================




// ===================================================================


#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// -------------------------------------------------------------------

// ServerMetadata

// string host = 1 [json_name = "host"];
inline void ServerMetadata::clear_host() {
  _impl_.host_.ClearToEmpty();
}
inline const std::string& ServerMetadata::host() const {
  // @@protoc_insertion_point(field_get:server.v1.ServerMetadata.host)
  return _internal_host();
}
template <typename Arg_, typename... Args_>
inline PROTOBUF_ALWAYS_INLINE void ServerMetadata::set_host(Arg_&& arg,
                                                     Args_... args) {
  ;
  _impl_.host_.Set(static_cast<Arg_&&>(arg), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:server.v1.ServerMetadata.host)
}
inline std::string* ServerMetadata::mutable_host() {
  std::string* _s = _internal_mutable_host();
  // @@protoc_insertion_point(field_mutable:server.v1.ServerMetadata.host)
  return _s;
}
inline const std::string& ServerMetadata::_internal_host() const {
  return _impl_.host_.Get();
}
inline void ServerMetadata::_internal_set_host(const std::string& value) {
  ;


  _impl_.host_.Set(value, GetArenaForAllocation());
}
inline std::string* ServerMetadata::_internal_mutable_host() {
  ;
  return _impl_.host_.Mutable( GetArenaForAllocation());
}
inline std::string* ServerMetadata::release_host() {
  // @@protoc_insertion_point(field_release:server.v1.ServerMetadata.host)
  return _impl_.host_.Release();
}
inline void ServerMetadata::set_allocated_host(std::string* value) {
  _impl_.host_.SetAllocated(value, GetArenaForAllocation());
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
        if (_impl_.host_.IsDefault()) {
          _impl_.host_.Set("", GetArenaForAllocation());
        }
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:server.v1.ServerMetadata.host)
}

// repeated .server.v1.ProtocolSupport protocols = 2 [json_name = "protocols"];
inline int ServerMetadata::_internal_protocols_size() const {
  return _impl_.protocols_.size();
}
inline int ServerMetadata::protocols_size() const {
  return _internal_protocols_size();
}
inline void ServerMetadata::clear_protocols() {
  _internal_mutable_protocols()->Clear();
}
inline ::server::v1::ProtocolSupport* ServerMetadata::mutable_protocols(int index) {
  // @@protoc_insertion_point(field_mutable:server.v1.ServerMetadata.protocols)
  return _internal_mutable_protocols()->Mutable(index);
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::server::v1::ProtocolSupport >*
ServerMetadata::mutable_protocols() {
  // @@protoc_insertion_point(field_mutable_list:server.v1.ServerMetadata.protocols)
  return _internal_mutable_protocols();
}
inline const ::server::v1::ProtocolSupport& ServerMetadata::_internal_protocols(int index) const {
  return _internal_protocols().Get(index);
}
inline const ::server::v1::ProtocolSupport& ServerMetadata::protocols(int index) const {
  // @@protoc_insertion_point(field_get:server.v1.ServerMetadata.protocols)
  return _internal_protocols(index);
}
inline ::server::v1::ProtocolSupport* ServerMetadata::_internal_add_protocols() {
  return _internal_mutable_protocols()->Add();
}
inline ::server::v1::ProtocolSupport* ServerMetadata::add_protocols() {
  ::server::v1::ProtocolSupport* _add = _internal_add_protocols();
  // @@protoc_insertion_point(field_add:server.v1.ServerMetadata.protocols)
  return _add;
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::server::v1::ProtocolSupport >&
ServerMetadata::protocols() const {
  // @@protoc_insertion_point(field_list:server.v1.ServerMetadata.protocols)
  return _internal_protocols();
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField<::server::v1::ProtocolSupport>&
ServerMetadata::_internal_protocols() const {
  return _impl_.protocols_;
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField<::server::v1::ProtocolSupport>*
ServerMetadata::_internal_mutable_protocols() {
  return &_impl_.protocols_;
}

// -------------------------------------------------------------------

// ProtocolSupport

// .server.v1.Protocol protocol = 1 [json_name = "protocol"];
inline void ProtocolSupport::clear_protocol() {
  _impl_.protocol_ = 0;
}
inline ::server::v1::Protocol ProtocolSupport::protocol() const {
  // @@protoc_insertion_point(field_get:server.v1.ProtocolSupport.protocol)
  return _internal_protocol();
}
inline void ProtocolSupport::set_protocol(::server::v1::Protocol value) {
   _internal_set_protocol(value);
  // @@protoc_insertion_point(field_set:server.v1.ProtocolSupport.protocol)
}
inline ::server::v1::Protocol ProtocolSupport::_internal_protocol() const {
  return static_cast<::server::v1::Protocol>(_impl_.protocol_);
}
inline void ProtocolSupport::_internal_set_protocol(::server::v1::Protocol value) {
  ;
  _impl_.protocol_ = value;
}

// repeated .server.v1.HTTPVersion http_versions = 2 [json_name = "httpVersions"];
inline int ProtocolSupport::_internal_http_versions_size() const {
  return _impl_.http_versions_.size();
}
inline int ProtocolSupport::http_versions_size() const {
  return _internal_http_versions_size();
}
inline void ProtocolSupport::clear_http_versions() {
  _internal_mutable_http_versions()->Clear();
}
inline ::server::v1::HTTPVersion* ProtocolSupport::mutable_http_versions(int index) {
  // @@protoc_insertion_point(field_mutable:server.v1.ProtocolSupport.http_versions)
  return _internal_mutable_http_versions()->Mutable(index);
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::server::v1::HTTPVersion >*
ProtocolSupport::mutable_http_versions() {
  // @@protoc_insertion_point(field_mutable_list:server.v1.ProtocolSupport.http_versions)
  return _internal_mutable_http_versions();
}
inline const ::server::v1::HTTPVersion& ProtocolSupport::_internal_http_versions(int index) const {
  return _internal_http_versions().Get(index);
}
inline const ::server::v1::HTTPVersion& ProtocolSupport::http_versions(int index) const {
  // @@protoc_insertion_point(field_get:server.v1.ProtocolSupport.http_versions)
  return _internal_http_versions(index);
}
inline ::server::v1::HTTPVersion* ProtocolSupport::_internal_add_http_versions() {
  return _internal_mutable_http_versions()->Add();
}
inline ::server::v1::HTTPVersion* ProtocolSupport::add_http_versions() {
  ::server::v1::HTTPVersion* _add = _internal_add_http_versions();
  // @@protoc_insertion_point(field_add:server.v1.ProtocolSupport.http_versions)
  return _add;
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::server::v1::HTTPVersion >&
ProtocolSupport::http_versions() const {
  // @@protoc_insertion_point(field_list:server.v1.ProtocolSupport.http_versions)
  return _internal_http_versions();
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField<::server::v1::HTTPVersion>&
ProtocolSupport::_internal_http_versions() const {
  return _impl_.http_versions_;
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField<::server::v1::HTTPVersion>*
ProtocolSupport::_internal_mutable_http_versions() {
  return &_impl_.http_versions_;
}

// string port = 3 [json_name = "port"];
inline void ProtocolSupport::clear_port() {
  _impl_.port_.ClearToEmpty();
}
inline const std::string& ProtocolSupport::port() const {
  // @@protoc_insertion_point(field_get:server.v1.ProtocolSupport.port)
  return _internal_port();
}
template <typename Arg_, typename... Args_>
inline PROTOBUF_ALWAYS_INLINE void ProtocolSupport::set_port(Arg_&& arg,
                                                     Args_... args) {
  ;
  _impl_.port_.Set(static_cast<Arg_&&>(arg), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:server.v1.ProtocolSupport.port)
}
inline std::string* ProtocolSupport::mutable_port() {
  std::string* _s = _internal_mutable_port();
  // @@protoc_insertion_point(field_mutable:server.v1.ProtocolSupport.port)
  return _s;
}
inline const std::string& ProtocolSupport::_internal_port() const {
  return _impl_.port_.Get();
}
inline void ProtocolSupport::_internal_set_port(const std::string& value) {
  ;


  _impl_.port_.Set(value, GetArenaForAllocation());
}
inline std::string* ProtocolSupport::_internal_mutable_port() {
  ;
  return _impl_.port_.Mutable( GetArenaForAllocation());
}
inline std::string* ProtocolSupport::release_port() {
  // @@protoc_insertion_point(field_release:server.v1.ProtocolSupport.port)
  return _impl_.port_.Release();
}
inline void ProtocolSupport::set_allocated_port(std::string* value) {
  _impl_.port_.SetAllocated(value, GetArenaForAllocation());
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
        if (_impl_.port_.IsDefault()) {
          _impl_.port_.Set("", GetArenaForAllocation());
        }
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:server.v1.ProtocolSupport.port)
}

// -------------------------------------------------------------------

// HTTPVersion

// int32 major = 1 [json_name = "major"];
inline void HTTPVersion::clear_major() {
  _impl_.major_ = 0;
}
inline ::int32_t HTTPVersion::major() const {
  // @@protoc_insertion_point(field_get:server.v1.HTTPVersion.major)
  return _internal_major();
}
inline void HTTPVersion::set_major(::int32_t value) {
  _internal_set_major(value);
  // @@protoc_insertion_point(field_set:server.v1.HTTPVersion.major)
}
inline ::int32_t HTTPVersion::_internal_major() const {
  return _impl_.major_;
}
inline void HTTPVersion::_internal_set_major(::int32_t value) {
  ;
  _impl_.major_ = value;
}

// int32 minor = 2 [json_name = "minor"];
inline void HTTPVersion::clear_minor() {
  _impl_.minor_ = 0;
}
inline ::int32_t HTTPVersion::minor() const {
  // @@protoc_insertion_point(field_get:server.v1.HTTPVersion.minor)
  return _internal_minor();
}
inline void HTTPVersion::set_minor(::int32_t value) {
  _internal_set_minor(value);
  // @@protoc_insertion_point(field_set:server.v1.HTTPVersion.minor)
}
inline ::int32_t HTTPVersion::_internal_minor() const {
  return _impl_.minor_;
}
inline void HTTPVersion::_internal_set_minor(::int32_t value) {
  ;
  _impl_.minor_ = value;
}

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)
}  // namespace v1
}  // namespace server


PROTOBUF_NAMESPACE_OPEN

template <>
struct is_proto_enum<::server::v1::Protocol> : std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor<::server::v1::Protocol>() {
  return ::server::v1::Protocol_descriptor();
}

PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)

#include "google/protobuf/port_undef.inc"

#endif  // GOOGLE_PROTOBUF_INCLUDED_server_2fv1_2fserver_2eproto_2epb_2eh
