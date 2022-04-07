#include <grpcpp/grpcpp.h>

namespace comm {
namespace network {
namespace reactor {

template <class Request, class Response>
class ClientBidiReactorBase
    : public grpc::ClientBidiReactor<Request, Response> {
  std::shared_ptr<Response> response = nullptr;
  bool done = false;
  bool initialized = 0;

protected:
  Request request;
  grpc::Status status;

public:
  grpc::ClientContext context;

  void nextWrite();
  void terminate(const grpc::Status &status);
  bool isDone();
  void OnWriteDone(bool ok) override;
  void OnReadDone(bool ok) override;
  void OnDone(const grpc::Status &status) override;

  virtual std::unique_ptr<grpc::Status> prepareRequest(
      Request &request,
      std::shared_ptr<Response> previousResponse) = 0;
  virtual void doneCallback(){};
  virtual void terminateCallback(){};
};

template <class Request, class Response>
void ClientBidiReactorBase<Request, Response>::nextWrite() {
  this->request = Request();
  std::unique_ptr<grpc::Status> status =
      this->prepareRequest(this->request, this->response);
  if (status != nullptr) {
    this->terminate(*status);
    return;
  }
  this->StartWrite(&this->request);
  if (!this->initialized) {
    this->StartCall();
    this->initialized = true;
  }
}

template <class Request, class Response>
void ClientBidiReactorBase<Request, Response>::terminate(
    const grpc::Status &status) {
  this->status = status;
  if (!this->status.ok()) {
    std::cout << "error: " << this->status.error_message() << std::endl;
  }
  if (this->done) {
    std::cout << "Terminate function was called multiple times, which should "
                 "never happen. Please investigate!"
              << std::endl;
    return;
  }
  this->terminateCallback();
  this->StartWritesDone();
  this->done = true;
}

template <class Request, class Response>
bool ClientBidiReactorBase<Request, Response>::isDone() {
  return this->done;
}

template <class Request, class Response>
void ClientBidiReactorBase<Request, Response>::OnWriteDone(bool ok) {
  if (this->response == nullptr) {
    this->response = std::make_shared<Response>();
  }
  this->StartRead(&(*this->response));
}

template <class Request, class Response>
void ClientBidiReactorBase<Request, Response>::OnReadDone(bool ok) {
  if (!ok) {
    // Ending a connection on the other side results in the `ok` flag being set
    // to false. It makes it impossible to detect a failure based just on the
    // flag. We should manually check if the data we received is valid
    this->terminate(grpc::Status::OK);
    return;
  }
  this->nextWrite();
}

template <class Request, class Response>
void ClientBidiReactorBase<Request, Response>::OnDone(
    const grpc::Status &status) {
  this->terminate(status);
  this->doneCallback();
}

} // namespace reactor
} // namespace network
} // namespace comm
