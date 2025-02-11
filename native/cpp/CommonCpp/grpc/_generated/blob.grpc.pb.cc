// @generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: blob.proto

#include "blob.pb.h"
#include "blob.grpc.pb.h"

#include <functional>
#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/impl/codegen/channel_interface.h>
#include <grpcpp/impl/codegen/client_unary_call.h>
#include <grpcpp/impl/codegen/client_callback.h>
#include <grpcpp/impl/codegen/message_allocator.h>
#include <grpcpp/impl/codegen/method_handler.h>
#include <grpcpp/impl/codegen/rpc_service_method.h>
#include <grpcpp/impl/codegen/server_callback.h>
#include <grpcpp/impl/codegen/server_callback_handlers.h>
#include <grpcpp/impl/codegen/server_context.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/sync_stream.h>
namespace blob {

static const char* BlobService_method_names[] = {
  "/blob.BlobService/Put",
  "/blob.BlobService/Get",
  "/blob.BlobService/Remove",
};

std::unique_ptr< BlobService::Stub> BlobService::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< BlobService::Stub> stub(new BlobService::Stub(channel, options));
  return stub;
}

BlobService::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options)
  : channel_(channel), rpcmethod_Put_(BlobService_method_names[0], options.suffix_for_stats(),::grpc::internal::RpcMethod::BIDI_STREAMING, channel)
  , rpcmethod_Get_(BlobService_method_names[1], options.suffix_for_stats(),::grpc::internal::RpcMethod::SERVER_STREAMING, channel)
  , rpcmethod_Remove_(BlobService_method_names[2], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::ClientReaderWriter< ::blob::PutRequest, ::blob::PutResponse>* BlobService::Stub::PutRaw(::grpc::ClientContext* context) {
  return ::grpc::internal::ClientReaderWriterFactory< ::blob::PutRequest, ::blob::PutResponse>::Create(channel_.get(), rpcmethod_Put_, context);
}

void BlobService::Stub::async::Put(::grpc::ClientContext* context, ::grpc::ClientBidiReactor< ::blob::PutRequest,::blob::PutResponse>* reactor) {
  ::grpc::internal::ClientCallbackReaderWriterFactory< ::blob::PutRequest,::blob::PutResponse>::Create(stub_->channel_.get(), stub_->rpcmethod_Put_, context, reactor);
}

::grpc::ClientAsyncReaderWriter< ::blob::PutRequest, ::blob::PutResponse>* BlobService::Stub::AsyncPutRaw(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq, void* tag) {
  return ::grpc::internal::ClientAsyncReaderWriterFactory< ::blob::PutRequest, ::blob::PutResponse>::Create(channel_.get(), cq, rpcmethod_Put_, context, true, tag);
}

::grpc::ClientAsyncReaderWriter< ::blob::PutRequest, ::blob::PutResponse>* BlobService::Stub::PrepareAsyncPutRaw(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncReaderWriterFactory< ::blob::PutRequest, ::blob::PutResponse>::Create(channel_.get(), cq, rpcmethod_Put_, context, false, nullptr);
}

::grpc::ClientReader< ::blob::GetResponse>* BlobService::Stub::GetRaw(::grpc::ClientContext* context, const ::blob::GetRequest& request) {
  return ::grpc::internal::ClientReaderFactory< ::blob::GetResponse>::Create(channel_.get(), rpcmethod_Get_, context, request);
}

void BlobService::Stub::async::Get(::grpc::ClientContext* context, const ::blob::GetRequest* request, ::grpc::ClientReadReactor< ::blob::GetResponse>* reactor) {
  ::grpc::internal::ClientCallbackReaderFactory< ::blob::GetResponse>::Create(stub_->channel_.get(), stub_->rpcmethod_Get_, context, request, reactor);
}

::grpc::ClientAsyncReader< ::blob::GetResponse>* BlobService::Stub::AsyncGetRaw(::grpc::ClientContext* context, const ::blob::GetRequest& request, ::grpc::CompletionQueue* cq, void* tag) {
  return ::grpc::internal::ClientAsyncReaderFactory< ::blob::GetResponse>::Create(channel_.get(), cq, rpcmethod_Get_, context, request, true, tag);
}

::grpc::ClientAsyncReader< ::blob::GetResponse>* BlobService::Stub::PrepareAsyncGetRaw(::grpc::ClientContext* context, const ::blob::GetRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncReaderFactory< ::blob::GetResponse>::Create(channel_.get(), cq, rpcmethod_Get_, context, request, false, nullptr);
}

::grpc::Status BlobService::Stub::Remove(::grpc::ClientContext* context, const ::blob::RemoveRequest& request, ::google::protobuf::Empty* response) {
  return ::grpc::internal::BlockingUnaryCall< ::blob::RemoveRequest, ::google::protobuf::Empty, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_Remove_, context, request, response);
}

void BlobService::Stub::async::Remove(::grpc::ClientContext* context, const ::blob::RemoveRequest* request, ::google::protobuf::Empty* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::blob::RemoveRequest, ::google::protobuf::Empty, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_Remove_, context, request, response, std::move(f));
}

void BlobService::Stub::async::Remove(::grpc::ClientContext* context, const ::blob::RemoveRequest* request, ::google::protobuf::Empty* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_Remove_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::google::protobuf::Empty>* BlobService::Stub::PrepareAsyncRemoveRaw(::grpc::ClientContext* context, const ::blob::RemoveRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::google::protobuf::Empty, ::blob::RemoveRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_Remove_, context, request);
}

::grpc::ClientAsyncResponseReader< ::google::protobuf::Empty>* BlobService::Stub::AsyncRemoveRaw(::grpc::ClientContext* context, const ::blob::RemoveRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncRemoveRaw(context, request, cq);
  result->StartCall();
  return result;
}

BlobService::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      BlobService_method_names[0],
      ::grpc::internal::RpcMethod::BIDI_STREAMING,
      new ::grpc::internal::BidiStreamingHandler< BlobService::Service, ::blob::PutRequest, ::blob::PutResponse>(
          [](BlobService::Service* service,
             ::grpc::ServerContext* ctx,
             ::grpc::ServerReaderWriter<::blob::PutResponse,
             ::blob::PutRequest>* stream) {
               return service->Put(ctx, stream);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      BlobService_method_names[1],
      ::grpc::internal::RpcMethod::SERVER_STREAMING,
      new ::grpc::internal::ServerStreamingHandler< BlobService::Service, ::blob::GetRequest, ::blob::GetResponse>(
          [](BlobService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::blob::GetRequest* req,
             ::grpc::ServerWriter<::blob::GetResponse>* writer) {
               return service->Get(ctx, req, writer);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      BlobService_method_names[2],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< BlobService::Service, ::blob::RemoveRequest, ::google::protobuf::Empty, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](BlobService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::blob::RemoveRequest* req,
             ::google::protobuf::Empty* resp) {
               return service->Remove(ctx, req, resp);
             }, this)));
}

BlobService::Service::~Service() {
}

::grpc::Status BlobService::Service::Put(::grpc::ServerContext* context, ::grpc::ServerReaderWriter< ::blob::PutResponse, ::blob::PutRequest>* stream) {
  (void) context;
  (void) stream;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status BlobService::Service::Get(::grpc::ServerContext* context, const ::blob::GetRequest* request, ::grpc::ServerWriter< ::blob::GetResponse>* writer) {
  (void) context;
  (void) request;
  (void) writer;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status BlobService::Service::Remove(::grpc::ServerContext* context, const ::blob::RemoveRequest* request, ::google::protobuf::Empty* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace blob

