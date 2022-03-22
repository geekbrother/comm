#pragma once

#include "ServerBidiReactorBase.h"
#include "ServiceBlobClient.h"
#include "Tools.h"

#include "../_generated/backup.grpc.pb.h"
#include "../_generated/backup.pb.h"

#include <condition_variable>
#include <iostream>
#include <memory>
#include <mutex>
#include <string>

#include <chrono>
#include <thread>

namespace comm {
namespace network {
namespace reactor {

class CreateNewBackupReactor : public ServerBidiReactorBase<
                                   backup::CreateNewBackupRequest,
                                   backup::CreateNewBackupResponse> {
  enum class State {
    KEY_ENTROPY = 1,
    DATA_HASH = 2,
    DATA_CHUNKS = 3,
  };

  State state = State::KEY_ENTROPY;
  std::string keyEntropy;
  std::string dataHash;
  std::string backupID;
  std::shared_ptr<reactor::BlobPutClientReactor> putReactor;
  ServiceBlobClient blobClient;
  std::mutex blobPutClientReactorMutex;
  std::condition_variable waitingForBlobClientCV;
  std::mutex waitingForBlobClientCVMutex;

  std::string generateBackupID();

public:
  std::unique_ptr<grpc::Status> handleRequest(
      backup::CreateNewBackupRequest request,
      backup::CreateNewBackupResponse *response) override;
  void doneCallback();

  virtual ~CreateNewBackupReactor() {
    std::cout << "[CNR] DTOR" << std::endl;
  }
};

std::string CreateNewBackupReactor::generateBackupID() {
  // mock
  return generateRandomString();
}

std::unique_ptr<grpc::Status> CreateNewBackupReactor::handleRequest(
    backup::CreateNewBackupRequest request,
    backup::CreateNewBackupResponse *response) {
  // we make sure that the blob client's state is flushed to the main memory
  // as there may be multiple threads from the pool taking over here
  const std::lock_guard<std::mutex> lock(this->blobPutClientReactorMutex);
  std::cout << "[CNR] here handle request" << std::endl;
  switch (this->state) {
    case State::KEY_ENTROPY: {
      if (!request.has_keyentropy()) {
        throw std::runtime_error(
            "backup key entropy expected but not received");
      }
      std::cout << "[CNR] here handle request key entropy" << std::endl;
      this->keyEntropy = request.keyentropy();
      this->state = State::DATA_HASH;
      return nullptr;
    }
    case State::DATA_HASH: {
      if (!request.has_newcompactionhash()) {
        throw std::runtime_error("data hash expected but not received");
      }
      this->dataHash = request.newcompactionhash();
      this->state = State::DATA_CHUNKS;

      // TODO confirm - holder may be a backup id
      this->backupID = this->generateBackupID();
      this->putReactor = std::make_shared<reactor::BlobPutClientReactor>(
          this->backupID, this->dataHash, &this->waitingForBlobClientCV);
      this->blobClient.put(this->putReactor);
      return nullptr;
    }
    case State::DATA_CHUNKS: {
      std::cout << "[CNR] here handle request data chunk "
                << request.newcompactionchunk().size() << std::endl;
      std::cout << "[CNR] here enqueueing data chunk" << std::endl;

      this->putReactor->scheduleSendingDataChunk(
          *request.mutable_newcompactionchunk());

      return nullptr;
    }
  }
  throw std::runtime_error("new backup - invalid state");
}

void CreateNewBackupReactor::doneCallback() {
  const std::lock_guard<std::mutex> lock(this->blobPutClientReactorMutex);
  std::cout << "[CNR] create new backup done " << this->status.error_code()
            << "/" << this->status.error_message() << std::endl;
  std::cout << "[CNR] enqueueing empty chunk to end blob upload" << std::endl;
  std::string emptyString = "";
  this->putReactor->scheduleSendingDataChunk(emptyString);
  std::cout << "[CNR] waiting for the blob client to complete" << std::endl;
  std::unique_lock<std::mutex> lock2(this->waitingForBlobClientCVMutex);
  this->waitingForBlobClientCV.wait(lock2);
  std::cout << "[CNR] the blob client to completed, CNR can exit gracefully"
            << std::endl;
}

} // namespace reactor
} // namespace network
} // namespace comm
