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

  void finish(grpc::Status status = grpc::Status::OK) {
    if (this->finished) {
      return;
    }
    this->finished = true;
    this->Finish(status);
  }

public:
  ReactorBase() {
    this->StartRead(&this->request);
  }

  void OnDone() override {
    GPR_ASSERT(this->finished);
    delete this;
  }

  void OnReadDone(bool ok) override {
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

  void OnWriteDone(bool ok) override {
    if (!ok) {
      gpr_log(GPR_ERROR, "Server write failed");
      return;
    }
    this->StartRead(&this->request);
  }

  virtual grpc::Status handleRequest(Request request, Response *response) = 0;
};

} // namespace network
} // namespace comm
