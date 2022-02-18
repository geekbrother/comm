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
    crypto::AuthenticationManager authenticationManager;

  public:
    backup::CreateNewBackupResponse
    handleRequest(backup::CreateNewBackupRequest request) override {
      backup::CreateNewBackupResponse response;
      if (this->authenticationManager.getState() !=
              crypto::AuthenticationState::SUCCESS &&
          !request.has_authenticationrequestdata()) {
        throw std::runtime_error(
            "authentication has not been finished properly");
      }
      if (this->authenticationManager.getState() ==
          crypto::AuthenticationState::FAIL) {
        throw std::runtime_error("authentication failure");
      }
      if (this->authenticationManager.getState() !=
          crypto::AuthenticationState::SUCCESS) {
        backup::FullAuthenticationResponseData authResponse =
            this->authenticationManager.processRequest(
                request.authenticationrequestdata());
        // warning: core dumps possible, in such a case, try making the response
        // a member of CreateNewBackupReactor class
        response.set_allocated_authenticationresponsedata(&authResponse);
        return response;
      }
      // auth successful - receive compaction
      std::string compactionDataChunk = request.newcompactionchunk();
      std::cout << "receive compaction " << compactionDataChunk.size()
                << std::endl;
      //...
      throw EndConnectionError();
    }
  };

  return new CreateNewBackupReactor();
}

grpc::ServerBidiReactor<backup::SendLogRequest, google::protobuf::Empty> *
BackupServiceImpl::SendLog(grpc::CallbackServerContext *context) {
  class SendLogReactor
      : public ReactorBase<backup::SendLogRequest, google::protobuf::Empty> {
  public:
    google::protobuf::Empty
    handleRequest(backup::SendLogRequest request) override {
      throw EndConnectionError();
      // TODO handle request
      return google::protobuf::Empty();
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
    backup::RecoverBackupKeyResponse
    handleRequest(backup::RecoverBackupKeyRequest request) override {
      throw EndConnectionError();
      // TODO handle request
      // backup::RecoverBackupKeyResponse response;
      // return response;
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
    backup::PullBackupResponse
    handleRequest(backup::PullBackupRequest request) override {
      throw EndConnectionError();
      // TODO handle request
      // backup::PullBackupResponse response;
      // return response;
    }
  };

  return new PullBackupReactor();
}

} // namespace network
} // namespace comm
