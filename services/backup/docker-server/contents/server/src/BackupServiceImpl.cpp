#include "BackupServiceImpl.h"

#include "PakeAuthenticationHandler.h"
#include "ReactorBase.h"
#include "WalletAuthenticationHandler.h"

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
  public:
    backup::CreateNewBackupResponse
    handleRequest(backup::CreateNewBackupRequest request) override {
      throw EndConnectionError();
      // TODO handle request
      // backup::CreateNewBackupResponse response;
      // return response;
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
