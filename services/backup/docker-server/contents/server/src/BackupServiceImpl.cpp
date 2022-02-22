#include "BackupServiceImpl.h"

#include "AuthenticationManager.h"
#include "ReactorBase.h"

#include <aws/core/Aws.h>

namespace comm {
namespace network {

BackupServiceImpl::BackupServiceImpl() {
  Aws::InitAPI({});
}

BackupServiceImpl::~BackupServiceImpl() {
  Aws::ShutdownAPI({});
}

grpc::ServerBidiReactor<
    backup::CreateNewBackupRequest,
    backup::CreateNewBackupResponse> *
BackupServiceImpl::CreateNewBackup(grpc::CallbackServerContext *context) {
  class CreateNewBackupReactor : public ReactorBase<
                                     backup::CreateNewBackupRequest,
                                     backup::CreateNewBackupResponse> {
    auth::AuthenticationManager authenticationManager;

  public:
    std::unique_ptr<grpc::Status> handleRequest(
        backup::CreateNewBackupRequest request,
        backup::CreateNewBackupResponse *response) override {
      if (this->authenticationManager.getState() !=
              auth::AuthenticationState::SUCCESS &&
          !request.has_authenticationrequestdata()) {
        return std::make_unique<grpc::Status>(
            grpc::StatusCode::INTERNAL,
            "authentication has not been finished properly");
      }
      if (this->authenticationManager.getState() ==
          auth::AuthenticationState::FAIL) {
        return std::make_unique<grpc::Status>(
            grpc::StatusCode::INTERNAL, "authentication failure");
      }
      if (this->authenticationManager.getState() !=
          auth::AuthenticationState::SUCCESS) {
        backup::FullAuthenticationResponseData authResponse =
            this->authenticationManager.processRequest(
                request.authenticationrequestdata());
        // warning: core dumps possible, in such a case, try making the response
        // a member of CreateNewBackupReactor class
        response->set_allocated_authenticationresponsedata(&authResponse);
        return nullptr;
      }
      // TODO handle request
      return std::make_unique<grpc::Status>(
          grpc::StatusCode::UNIMPLEMENTED, "unimplemented");
    }
  };

  return new CreateNewBackupReactor();
}

grpc::ServerBidiReactor<backup::SendLogRequest, google::protobuf::Empty> *
BackupServiceImpl::SendLog(grpc::CallbackServerContext *context) {
  class SendLogReactor
      : public ReactorBase<backup::SendLogRequest, google::protobuf::Empty> {
  public:
    std::unique_ptr<grpc::Status> handleRequest(
        backup::SendLogRequest request,
        google::protobuf::Empty *response) override {
      // TODO handle request
      return std::make_unique<grpc::Status>(
          grpc::StatusCode::UNIMPLEMENTED, "unimplemented");
    }
  };

  return new SendLogReactor();
}

grpc::ServerBidiReactor<
    backup::RecoverBackupKeyRequest,
    backup::RecoverBackupKeyResponse> *
BackupServiceImpl::RecoverBackupKey(grpc::CallbackServerContext *context) {
  class RecoverBackupKeyReactor : public ReactorBase<
                                      backup::RecoverBackupKeyRequest,
                                      backup::RecoverBackupKeyResponse> {
  public:
    std::unique_ptr<grpc::Status> handleRequest(
        backup::RecoverBackupKeyRequest request,
        backup::RecoverBackupKeyResponse *response) override {
      // TODO handle request
      return std::make_unique<grpc::Status>(
          grpc::StatusCode::UNIMPLEMENTED, "unimplemented");
    }
  };

  return new RecoverBackupKeyReactor();
}

grpc::ServerBidiReactor<backup::PullBackupRequest, backup::PullBackupResponse> *
BackupServiceImpl::PullBackup(grpc::CallbackServerContext *context) {
  class PullBackupReactor : public ReactorBase<
                                backup::PullBackupRequest,
                                backup::PullBackupResponse> {
  public:
    std::unique_ptr<grpc::Status> handleRequest(
        backup::PullBackupRequest request,
        backup::PullBackupResponse *response) override {
      // TODO handle request
      return std::make_unique<grpc::Status>(
          grpc::StatusCode::UNIMPLEMENTED, "unimplemented");
    }
  };

  return new PullBackupReactor();
}

} // namespace network
} // namespace comm
