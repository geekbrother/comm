#pragma once

#include <grpcpp/grpcpp.h>
#include <string>

namespace comm {
namespace network {

template <class Request, class Response>
class ReactorBase : public grpc::ServerBidiReactor<Request, Response> {
  Request request;
  Response response;
  bool finished = false;

  void finish(grpc::Status status = grpc::Status::OK);

public:
  ReactorBase();

  void OnDone() override;
  void OnReadDone(bool ok) override;
  void OnWriteDone(bool ok) override;

  virtual grpc::Status handleRequest(Request request, Response *response) = 0;
};

template <class Request, class Response>
void ReactorBase<Request, Response>::finish(grpc::Status status) {
  if (this->finished) {
    return;
  }
  this->finished = true;
  this->Finish(status);
}

template <class Request, class Response>
ReactorBase<Request, Response>::ReactorBase() {
  this->StartRead(&this->request);
}

template <class Request, class Response>
void ReactorBase<Request, Response>::OnDone() {
  if (!this->finished) {
    throw std::runtime_error(
        "trying to delete the reactor without finishing the connection "
        "properly");
  }
  delete this;
}

template <class Request, class Response>
void ReactorBase<Request, Response>::OnReadDone(bool ok) {
  if (!ok) {
    this->finish(grpc::Status(grpc::StatusCode::INTERNAL, "reading error"));
    return;
  }
  try {
    grpc::Status status = this->handleRequest(this->request, &this->response);
    if (status.ok()) {
      this->finish(status);
      return;
    }
    this->StartWrite(&this->response);
  } catch (std::runtime_error &e) {
    this->finish(grpc::Status(grpc::StatusCode::INTERNAL, e.what()));
  }
}

template <class Request, class Response>
void ReactorBase<Request, Response>::OnWriteDone(bool ok) {
  if (!ok) {
    gpr_log(GPR_ERROR, "Server write failed");
    return;
  }
  this->StartRead(&this->request);
}

} // namespace network
} // namespace comm
