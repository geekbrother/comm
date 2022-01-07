// @generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: tunnelbroker.proto

#include "tunnelbroker.pb.h"
#include "tunnelbroker.grpc.pb.h"

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
namespace tunnelbroker {

static const char* TunnelBrokerService_method_names[] = {
  "/tunnelbroker.TunnelBrokerService/CheckIfPrimaryDeviceOnline",
  "/tunnelbroker.TunnelBrokerService/BecomeNewPrimaryDevice",
  "/tunnelbroker.TunnelBrokerService/SendPong",
};

std::unique_ptr< TunnelBrokerService::Stub> TunnelBrokerService::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< TunnelBrokerService::Stub> stub(new TunnelBrokerService::Stub(channel, options));
  return stub;
}

TunnelBrokerService::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options)
  : channel_(channel), rpcmethod_CheckIfPrimaryDeviceOnline_(TunnelBrokerService_method_names[0], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_BecomeNewPrimaryDevice_(TunnelBrokerService_method_names[1], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_SendPong_(TunnelBrokerService_method_names[2], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status TunnelBrokerService::Stub::CheckIfPrimaryDeviceOnline(::grpc::ClientContext* context, const ::tunnelbroker::CheckRequest& request, ::tunnelbroker::CheckResponse* response) {
  return ::grpc::internal::BlockingUnaryCall< ::tunnelbroker::CheckRequest, ::tunnelbroker::CheckResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_CheckIfPrimaryDeviceOnline_, context, request, response);
}

void TunnelBrokerService::Stub::async::CheckIfPrimaryDeviceOnline(::grpc::ClientContext* context, const ::tunnelbroker::CheckRequest* request, ::tunnelbroker::CheckResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::tunnelbroker::CheckRequest, ::tunnelbroker::CheckResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_CheckIfPrimaryDeviceOnline_, context, request, response, std::move(f));
}

void TunnelBrokerService::Stub::async::CheckIfPrimaryDeviceOnline(::grpc::ClientContext* context, const ::tunnelbroker::CheckRequest* request, ::tunnelbroker::CheckResponse* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_CheckIfPrimaryDeviceOnline_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::tunnelbroker::CheckResponse>* TunnelBrokerService::Stub::PrepareAsyncCheckIfPrimaryDeviceOnlineRaw(::grpc::ClientContext* context, const ::tunnelbroker::CheckRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::tunnelbroker::CheckResponse, ::tunnelbroker::CheckRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_CheckIfPrimaryDeviceOnline_, context, request);
}

::grpc::ClientAsyncResponseReader< ::tunnelbroker::CheckResponse>* TunnelBrokerService::Stub::AsyncCheckIfPrimaryDeviceOnlineRaw(::grpc::ClientContext* context, const ::tunnelbroker::CheckRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncCheckIfPrimaryDeviceOnlineRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status TunnelBrokerService::Stub::BecomeNewPrimaryDevice(::grpc::ClientContext* context, const ::tunnelbroker::NewPrimaryRequest& request, ::tunnelbroker::NewPrimaryResponse* response) {
  return ::grpc::internal::BlockingUnaryCall< ::tunnelbroker::NewPrimaryRequest, ::tunnelbroker::NewPrimaryResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_BecomeNewPrimaryDevice_, context, request, response);
}

void TunnelBrokerService::Stub::async::BecomeNewPrimaryDevice(::grpc::ClientContext* context, const ::tunnelbroker::NewPrimaryRequest* request, ::tunnelbroker::NewPrimaryResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::tunnelbroker::NewPrimaryRequest, ::tunnelbroker::NewPrimaryResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_BecomeNewPrimaryDevice_, context, request, response, std::move(f));
}

void TunnelBrokerService::Stub::async::BecomeNewPrimaryDevice(::grpc::ClientContext* context, const ::tunnelbroker::NewPrimaryRequest* request, ::tunnelbroker::NewPrimaryResponse* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_BecomeNewPrimaryDevice_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::tunnelbroker::NewPrimaryResponse>* TunnelBrokerService::Stub::PrepareAsyncBecomeNewPrimaryDeviceRaw(::grpc::ClientContext* context, const ::tunnelbroker::NewPrimaryRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::tunnelbroker::NewPrimaryResponse, ::tunnelbroker::NewPrimaryRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_BecomeNewPrimaryDevice_, context, request);
}

::grpc::ClientAsyncResponseReader< ::tunnelbroker::NewPrimaryResponse>* TunnelBrokerService::Stub::AsyncBecomeNewPrimaryDeviceRaw(::grpc::ClientContext* context, const ::tunnelbroker::NewPrimaryRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncBecomeNewPrimaryDeviceRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status TunnelBrokerService::Stub::SendPong(::grpc::ClientContext* context, const ::tunnelbroker::PongRequest& request, ::google::protobuf::Empty* response) {
  return ::grpc::internal::BlockingUnaryCall< ::tunnelbroker::PongRequest, ::google::protobuf::Empty, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_SendPong_, context, request, response);
}

void TunnelBrokerService::Stub::async::SendPong(::grpc::ClientContext* context, const ::tunnelbroker::PongRequest* request, ::google::protobuf::Empty* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::tunnelbroker::PongRequest, ::google::protobuf::Empty, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_SendPong_, context, request, response, std::move(f));
}

void TunnelBrokerService::Stub::async::SendPong(::grpc::ClientContext* context, const ::tunnelbroker::PongRequest* request, ::google::protobuf::Empty* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_SendPong_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::google::protobuf::Empty>* TunnelBrokerService::Stub::PrepareAsyncSendPongRaw(::grpc::ClientContext* context, const ::tunnelbroker::PongRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::google::protobuf::Empty, ::tunnelbroker::PongRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_SendPong_, context, request);
}

::grpc::ClientAsyncResponseReader< ::google::protobuf::Empty>* TunnelBrokerService::Stub::AsyncSendPongRaw(::grpc::ClientContext* context, const ::tunnelbroker::PongRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncSendPongRaw(context, request, cq);
  result->StartCall();
  return result;
}

TunnelBrokerService::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      TunnelBrokerService_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< TunnelBrokerService::Service, ::tunnelbroker::CheckRequest, ::tunnelbroker::CheckResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](TunnelBrokerService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::tunnelbroker::CheckRequest* req,
             ::tunnelbroker::CheckResponse* resp) {
               return service->CheckIfPrimaryDeviceOnline(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      TunnelBrokerService_method_names[1],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< TunnelBrokerService::Service, ::tunnelbroker::NewPrimaryRequest, ::tunnelbroker::NewPrimaryResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](TunnelBrokerService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::tunnelbroker::NewPrimaryRequest* req,
             ::tunnelbroker::NewPrimaryResponse* resp) {
               return service->BecomeNewPrimaryDevice(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      TunnelBrokerService_method_names[2],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< TunnelBrokerService::Service, ::tunnelbroker::PongRequest, ::google::protobuf::Empty, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](TunnelBrokerService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::tunnelbroker::PongRequest* req,
             ::google::protobuf::Empty* resp) {
               return service->SendPong(ctx, req, resp);
             }, this)));
}

TunnelBrokerService::Service::~Service() {
}

::grpc::Status TunnelBrokerService::Service::CheckIfPrimaryDeviceOnline(::grpc::ServerContext* context, const ::tunnelbroker::CheckRequest* request, ::tunnelbroker::CheckResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status TunnelBrokerService::Service::BecomeNewPrimaryDevice(::grpc::ServerContext* context, const ::tunnelbroker::NewPrimaryRequest* request, ::tunnelbroker::NewPrimaryResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status TunnelBrokerService::Service::SendPong(::grpc::ServerContext* context, const ::tunnelbroker::PongRequest* request, ::google::protobuf::Empty* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


static const char* TunnelbrokerService_method_names[] = {
  "/tunnelbroker.TunnelbrokerService/SessionSignature",
  "/tunnelbroker.TunnelbrokerService/NewSession",
  "/tunnelbroker.TunnelbrokerService/Send",
  "/tunnelbroker.TunnelbrokerService/Get",
};

std::unique_ptr< TunnelbrokerService::Stub> TunnelbrokerService::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< TunnelbrokerService::Stub> stub(new TunnelbrokerService::Stub(channel, options));
  return stub;
}

TunnelbrokerService::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options)
  : channel_(channel), rpcmethod_SessionSignature_(TunnelbrokerService_method_names[0], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_NewSession_(TunnelbrokerService_method_names[1], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_Send_(TunnelbrokerService_method_names[2], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_Get_(TunnelbrokerService_method_names[3], options.suffix_for_stats(),::grpc::internal::RpcMethod::SERVER_STREAMING, channel)
  {}

::grpc::Status TunnelbrokerService::Stub::SessionSignature(::grpc::ClientContext* context, const ::tunnelbroker::SessionSignatureRequest& request, ::tunnelbroker::SessionSignatureResponse* response) {
  return ::grpc::internal::BlockingUnaryCall< ::tunnelbroker::SessionSignatureRequest, ::tunnelbroker::SessionSignatureResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_SessionSignature_, context, request, response);
}

void TunnelbrokerService::Stub::async::SessionSignature(::grpc::ClientContext* context, const ::tunnelbroker::SessionSignatureRequest* request, ::tunnelbroker::SessionSignatureResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::tunnelbroker::SessionSignatureRequest, ::tunnelbroker::SessionSignatureResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_SessionSignature_, context, request, response, std::move(f));
}

void TunnelbrokerService::Stub::async::SessionSignature(::grpc::ClientContext* context, const ::tunnelbroker::SessionSignatureRequest* request, ::tunnelbroker::SessionSignatureResponse* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_SessionSignature_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::tunnelbroker::SessionSignatureResponse>* TunnelbrokerService::Stub::PrepareAsyncSessionSignatureRaw(::grpc::ClientContext* context, const ::tunnelbroker::SessionSignatureRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::tunnelbroker::SessionSignatureResponse, ::tunnelbroker::SessionSignatureRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_SessionSignature_, context, request);
}

::grpc::ClientAsyncResponseReader< ::tunnelbroker::SessionSignatureResponse>* TunnelbrokerService::Stub::AsyncSessionSignatureRaw(::grpc::ClientContext* context, const ::tunnelbroker::SessionSignatureRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncSessionSignatureRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status TunnelbrokerService::Stub::NewSession(::grpc::ClientContext* context, const ::tunnelbroker::NewSessionRequest& request, ::tunnelbroker::NewSessionResponse* response) {
  return ::grpc::internal::BlockingUnaryCall< ::tunnelbroker::NewSessionRequest, ::tunnelbroker::NewSessionResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_NewSession_, context, request, response);
}

void TunnelbrokerService::Stub::async::NewSession(::grpc::ClientContext* context, const ::tunnelbroker::NewSessionRequest* request, ::tunnelbroker::NewSessionResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::tunnelbroker::NewSessionRequest, ::tunnelbroker::NewSessionResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_NewSession_, context, request, response, std::move(f));
}

void TunnelbrokerService::Stub::async::NewSession(::grpc::ClientContext* context, const ::tunnelbroker::NewSessionRequest* request, ::tunnelbroker::NewSessionResponse* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_NewSession_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::tunnelbroker::NewSessionResponse>* TunnelbrokerService::Stub::PrepareAsyncNewSessionRaw(::grpc::ClientContext* context, const ::tunnelbroker::NewSessionRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::tunnelbroker::NewSessionResponse, ::tunnelbroker::NewSessionRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_NewSession_, context, request);
}

::grpc::ClientAsyncResponseReader< ::tunnelbroker::NewSessionResponse>* TunnelbrokerService::Stub::AsyncNewSessionRaw(::grpc::ClientContext* context, const ::tunnelbroker::NewSessionRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncNewSessionRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status TunnelbrokerService::Stub::Send(::grpc::ClientContext* context, const ::tunnelbroker::SendRequest& request, ::google::protobuf::Empty* response) {
  return ::grpc::internal::BlockingUnaryCall< ::tunnelbroker::SendRequest, ::google::protobuf::Empty, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_Send_, context, request, response);
}

void TunnelbrokerService::Stub::async::Send(::grpc::ClientContext* context, const ::tunnelbroker::SendRequest* request, ::google::protobuf::Empty* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::tunnelbroker::SendRequest, ::google::protobuf::Empty, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_Send_, context, request, response, std::move(f));
}

void TunnelbrokerService::Stub::async::Send(::grpc::ClientContext* context, const ::tunnelbroker::SendRequest* request, ::google::protobuf::Empty* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_Send_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::google::protobuf::Empty>* TunnelbrokerService::Stub::PrepareAsyncSendRaw(::grpc::ClientContext* context, const ::tunnelbroker::SendRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::google::protobuf::Empty, ::tunnelbroker::SendRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_Send_, context, request);
}

::grpc::ClientAsyncResponseReader< ::google::protobuf::Empty>* TunnelbrokerService::Stub::AsyncSendRaw(::grpc::ClientContext* context, const ::tunnelbroker::SendRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncSendRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::ClientReader< ::tunnelbroker::GetResponse>* TunnelbrokerService::Stub::GetRaw(::grpc::ClientContext* context, const ::tunnelbroker::GetRequest& request) {
  return ::grpc::internal::ClientReaderFactory< ::tunnelbroker::GetResponse>::Create(channel_.get(), rpcmethod_Get_, context, request);
}

void TunnelbrokerService::Stub::async::Get(::grpc::ClientContext* context, const ::tunnelbroker::GetRequest* request, ::grpc::ClientReadReactor< ::tunnelbroker::GetResponse>* reactor) {
  ::grpc::internal::ClientCallbackReaderFactory< ::tunnelbroker::GetResponse>::Create(stub_->channel_.get(), stub_->rpcmethod_Get_, context, request, reactor);
}

::grpc::ClientAsyncReader< ::tunnelbroker::GetResponse>* TunnelbrokerService::Stub::AsyncGetRaw(::grpc::ClientContext* context, const ::tunnelbroker::GetRequest& request, ::grpc::CompletionQueue* cq, void* tag) {
  return ::grpc::internal::ClientAsyncReaderFactory< ::tunnelbroker::GetResponse>::Create(channel_.get(), cq, rpcmethod_Get_, context, request, true, tag);
}

::grpc::ClientAsyncReader< ::tunnelbroker::GetResponse>* TunnelbrokerService::Stub::PrepareAsyncGetRaw(::grpc::ClientContext* context, const ::tunnelbroker::GetRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncReaderFactory< ::tunnelbroker::GetResponse>::Create(channel_.get(), cq, rpcmethod_Get_, context, request, false, nullptr);
}

TunnelbrokerService::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      TunnelbrokerService_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< TunnelbrokerService::Service, ::tunnelbroker::SessionSignatureRequest, ::tunnelbroker::SessionSignatureResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](TunnelbrokerService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::tunnelbroker::SessionSignatureRequest* req,
             ::tunnelbroker::SessionSignatureResponse* resp) {
               return service->SessionSignature(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      TunnelbrokerService_method_names[1],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< TunnelbrokerService::Service, ::tunnelbroker::NewSessionRequest, ::tunnelbroker::NewSessionResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](TunnelbrokerService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::tunnelbroker::NewSessionRequest* req,
             ::tunnelbroker::NewSessionResponse* resp) {
               return service->NewSession(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      TunnelbrokerService_method_names[2],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< TunnelbrokerService::Service, ::tunnelbroker::SendRequest, ::google::protobuf::Empty, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](TunnelbrokerService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::tunnelbroker::SendRequest* req,
             ::google::protobuf::Empty* resp) {
               return service->Send(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      TunnelbrokerService_method_names[3],
      ::grpc::internal::RpcMethod::SERVER_STREAMING,
      new ::grpc::internal::ServerStreamingHandler< TunnelbrokerService::Service, ::tunnelbroker::GetRequest, ::tunnelbroker::GetResponse>(
          [](TunnelbrokerService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::tunnelbroker::GetRequest* req,
             ::grpc::ServerWriter<::tunnelbroker::GetResponse>* writer) {
               return service->Get(ctx, req, writer);
             }, this)));
}

TunnelbrokerService::Service::~Service() {
}

::grpc::Status TunnelbrokerService::Service::SessionSignature(::grpc::ServerContext* context, const ::tunnelbroker::SessionSignatureRequest* request, ::tunnelbroker::SessionSignatureResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status TunnelbrokerService::Service::NewSession(::grpc::ServerContext* context, const ::tunnelbroker::NewSessionRequest* request, ::tunnelbroker::NewSessionResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status TunnelbrokerService::Service::Send(::grpc::ServerContext* context, const ::tunnelbroker::SendRequest* request, ::google::protobuf::Empty* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status TunnelbrokerService::Service::Get(::grpc::ServerContext* context, const ::tunnelbroker::GetRequest* request, ::grpc::ServerWriter< ::tunnelbroker::GetResponse>* writer) {
  (void) context;
  (void) request;
  (void) writer;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace tunnelbroker

