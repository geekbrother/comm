#include "CommCoreModule.h"
#include "DatabaseManager.h"

#include <folly/Optional.h>

#include <ReactCommon/TurboModuleUtils.h>

namespace comm {

using namespace facebook::react;

jsi::Value CommCoreModule::getDraft(jsi::Runtime &rt, const jsi::String &key) {
  std::string keyStr = key.utf8(rt);
  return createPromiseAsJSIValue(
      rt, [=](jsi::Runtime &innerRt, std::shared_ptr<Promise> promise) {
        taskType job = [=, &innerRt]() {
          std::string error;
          std::string draftStr;
          try {
            draftStr = DatabaseManager::getQueryExecutor().getDraft(keyStr);
          } catch (std::system_error &e) {
            error = e.what();
          }
          this->jsInvoker_->invokeAsync([=, &innerRt]() {
            if (error.size()) {
              promise->reject(error);
              return;
            }
            jsi::String draft = jsi::String::createFromUtf8(innerRt, draftStr);
            promise->resolve(std::move(draft));
          });
        };
        this->databaseThread.scheduleTask(job);
      });
}

jsi::Value
CommCoreModule::updateDraft(jsi::Runtime &rt, const jsi::Object &draft) {
  std::string keyStr = draft.getProperty(rt, "key").asString(rt).utf8(rt);
  std::string textStr = draft.getProperty(rt, "text").asString(rt).utf8(rt);
  return createPromiseAsJSIValue(
      rt, [=](jsi::Runtime &innerRt, std::shared_ptr<Promise> promise) {
        taskType job = [=, &innerRt]() {
          std::string error;
          try {
            DatabaseManager::getQueryExecutor().updateDraft(keyStr, textStr);
          } catch (std::system_error &e) {
            error = e.what();
          }
          this->jsInvoker_->invokeAsync([=, &innerRt]() {
            if (error.size()) {
              promise->reject(error);
            } else {
              promise->resolve(true);
            }
          });
        };
        this->databaseThread.scheduleTask(job);
      });
}

jsi::Value CommCoreModule::moveDraft(
    jsi::Runtime &rt,
    const jsi::String &oldKey,
    const jsi::String &newKey) {
  std::string oldKeyStr = oldKey.utf8(rt);
  std::string newKeyStr = newKey.utf8(rt);

  return createPromiseAsJSIValue(
      rt, [=](jsi::Runtime &innerRt, std::shared_ptr<Promise> promise) {
        taskType job = [=, &innerRt]() {
          std::string error;
          bool result = false;
          try {
            result = DatabaseManager::getQueryExecutor().moveDraft(
                oldKeyStr, newKeyStr);
          } catch (std::system_error &e) {
            error = e.what();
          }
          this->jsInvoker_->invokeAsync([=, &innerRt]() {
            if (error.size()) {
              promise->reject(error);
            } else {
              promise->resolve(result);
            }
          });
        };
        this->databaseThread.scheduleTask(job);
      });
}

jsi::Value CommCoreModule::getAllDrafts(jsi::Runtime &rt) {
  return createPromiseAsJSIValue(
      rt, [=](jsi::Runtime &innerRt, std::shared_ptr<Promise> promise) {
        taskType job = [=, &innerRt]() {
          std::string error;
          std::vector<Draft> draftsVector;
          size_t numDrafts;
          try {
            draftsVector = DatabaseManager::getQueryExecutor().getAllDrafts();
            numDrafts = count_if(
                draftsVector.begin(), draftsVector.end(), [](Draft draft) {
                  return !draft.text.empty();
                });
          } catch (std::system_error &e) {
            error = e.what();
          }
          this->jsInvoker_->invokeAsync([=, &innerRt]() {
            if (error.size()) {
              promise->reject(error);
              return;
            }
            jsi::Array jsiDrafts = jsi::Array(innerRt, numDrafts);

            size_t writeIndex = 0;
            for (Draft draft : draftsVector) {
              if (draft.text.empty()) {
                continue;
              }
              auto jsiDraft = jsi::Object(innerRt);
              jsiDraft.setProperty(innerRt, "key", draft.key);
              jsiDraft.setProperty(innerRt, "text", draft.text);
              jsiDrafts.setValueAtIndex(innerRt, writeIndex++, jsiDraft);
            }
            promise->resolve(std::move(jsiDrafts));
          });
        };
        this->databaseThread.scheduleTask(job);
      });
}

jsi::Value CommCoreModule::removeAllDrafts(jsi::Runtime &rt) {
  return createPromiseAsJSIValue(
      rt, [=](jsi::Runtime &innerRt, std::shared_ptr<Promise> promise) {
        taskType job = [=, &innerRt]() {
          std::string error;
          try {
            DatabaseManager::getQueryExecutor().removeAllDrafts();
          } catch (std::system_error &e) {
            error = e.what();
          }
          this->jsInvoker_->invokeAsync([=, &innerRt]() {
            if (error.size()) {
              promise->reject(error);
              return;
            }
            promise->resolve(jsi::Value::undefined());
          });
        };
        this->databaseThread.scheduleTask(job);
      });
}

jsi::Value CommCoreModule::removeAllMessages(jsi::Runtime &rt) {
  return createPromiseAsJSIValue(
      rt, [=](jsi::Runtime &innerRt, std::shared_ptr<Promise> promise) {
        taskType job = [=, &innerRt]() {
          std::string error;
          try {
            DatabaseManager::getQueryExecutor().removeAllMessages();
          } catch (std::system_error &e) {
            error = e.what();
          }
          this->jsInvoker_->invokeAsync([=, &innerRt]() {
            if (error.size()) {
              promise->reject(error);
              return;
            }
            promise->resolve(jsi::Value::undefined());
          });
        };
        this->databaseThread.scheduleTask(job);
      });
}

jsi::Value CommCoreModule::getAllMessages(jsi::Runtime &rt) {
  return createPromiseAsJSIValue(
      rt, [=](jsi::Runtime &innerRt, std::shared_ptr<Promise> promise) {
        taskType job = [=, &innerRt]() {
          std::string error;
          std::vector<Message> messagesVector;
          size_t numMessages;
          try {
            messagesVector =
                DatabaseManager::getQueryExecutor().getAllMessages();
            numMessages = messagesVector.size();
          } catch (std::system_error &e) {
            error = e.what();
          }
          this->jsInvoker_->invokeAsync([=, &innerRt]() {
            if (error.size()) {
              promise->reject(error);
              return;
            }
            jsi::Array jsiMessages = jsi::Array(innerRt, numMessages);
            size_t writeIndex = 0;
            for (Message message : messagesVector) {
              auto jsiMessage = jsi::Object(innerRt);
              jsiMessage.setProperty(innerRt, "id", std::to_string(message.id));
              jsiMessage.setProperty(
                  innerRt, "thread", std::to_string(message.thread));
              jsiMessage.setProperty(
                  innerRt, "user", std::to_string(message.user));
              jsiMessage.setProperty(
                  innerRt, "type", std::to_string(message.type));
              jsiMessage.setProperty(
                  innerRt, "future_type", std::to_string(message.future_type));
              jsiMessage.setProperty(innerRt, "content", message.content);
              jsiMessage.setProperty(
                  innerRt, "time", std::to_string(message.time));
              jsiMessages.setValueAtIndex(innerRt, writeIndex++, jsiMessage);
            }
            promise->resolve(std::move(jsiMessages));
          });
        };
        this->databaseThread.scheduleTask(job);
      });
}

#define REMOVE_OPERATION "remove"
#define REPLACE_OPERATION "replace"
#define REMOVE_MSGS_FOR_THREADS_OPERATION "remove_messages_for_threads"

jsi::Value CommCoreModule::processMessageStoreOperations(
    jsi::Runtime &rt,
    const jsi::Array &operations) {

  std::vector<int> removed_msg_ids;
  std::vector<Message> replaced_msgs;
  std::vector<int> threads_to_remove_msgs_from;

  for (auto idx = 0; idx < operations.size(rt); idx++) {
    auto op = operations.getValueAtIndex(rt, idx).asObject(rt);
    auto op_type = op.getProperty(rt, "type").asString(rt).utf8(rt);

    if (op_type == REMOVE_OPERATION) {
      auto payload_obj = op.getProperty(rt, "payload").asObject(rt);
      auto msg_ids =
          payload_obj.getProperty(rt, "ids").asObject(rt).asArray(rt);
      for (auto msg_idx = 0; msg_idx < msg_ids.size(rt); msg_idx++) {
        removed_msg_ids.push_back(std::stoi(
            msg_ids.getValueAtIndex(rt, msg_idx).asString(rt).utf8(rt)));
      }

    } else if (op_type == REMOVE_MSGS_FOR_THREADS_OPERATION) {
      auto payload_obj = op.getProperty(rt, "payload").asObject(rt);
      auto thread_ids =
          payload_obj.getProperty(rt, "threadIDs").asObject(rt).asArray(rt);
      for (auto thread_idx = 0; thread_idx < thread_ids.size(rt);
           thread_idx++) {
        threads_to_remove_msgs_from.push_back(std::stoi(
            thread_ids.getValueAtIndex(rt, thread_idx).asString(rt).utf8(rt)));
      }
    } else if (op_type == REPLACE_OPERATION) {
      auto msg_obj = op.getProperty(rt, "payload").asObject(rt);

      auto id = std::stoi(msg_obj.getProperty(rt, "id").asString(rt).utf8(rt));
      auto thread =
          std::stoi(msg_obj.getProperty(rt, "thread").asString(rt).utf8(rt));
      auto user =
          std::stoi(msg_obj.getProperty(rt, "user").asString(rt).utf8(rt));
      auto type =
          std::stoi(msg_obj.getProperty(rt, "type").asString(rt).utf8(rt));
      auto future_type = std::stoi(
          msg_obj.getProperty(rt, "future_type").asString(rt).utf8(rt));
      auto content = msg_obj.getProperty(rt, "content").asString(rt).utf8(rt);
      auto time =
          std::stoi(msg_obj.getProperty(rt, "time").asString(rt).utf8(rt));
      Message message = {id, thread, user, type, future_type, content, time};
      replaced_msgs.push_back(message);
    }
  }

  return createPromiseAsJSIValue(
      rt, [=](jsi::Runtime &innerRt, std::shared_ptr<Promise> promise) {
        taskType job = [=, &innerRt]() {
          std::string error;
          try {
            DatabaseManager::getQueryExecutor().removeMessages(removed_msg_ids);
            for (const auto &msg : replaced_msgs) {
              DatabaseManager::getQueryExecutor().replaceMessage(msg);
            }
            DatabaseManager::getQueryExecutor().removeMessagesForThreads(
                threads_to_remove_msgs_from);
          } catch (std::system_error &e) {
            error = e.what();
          }
          this->jsInvoker_->invokeAsync([=, &innerRt]() {
            if (error.size()) {
              promise->reject(error);
            } else {
              promise->resolve(jsi::Value::undefined());
            }
          });
        };
        this->databaseThread.scheduleTask(job);
      });
}

jsi::Value CommCoreModule::initializeCryptoAccount(
    jsi::Runtime &rt,
    const jsi::String &userId) {
  std::string userIdStr = userId.utf8(rt);
  folly::Optional<std::string> storedSecretKey =
      this->secureStore.get(this->secureStoreAccountDataKey);
  if (!storedSecretKey.hasValue()) {
    storedSecretKey = crypto::Tools::getInstance().generateRandomString(64);
    this->secureStore.set(
        this->secureStoreAccountDataKey, storedSecretKey.value());
  }

  return createPromiseAsJSIValue(
      rt, [=](jsi::Runtime &innerRt, std::shared_ptr<Promise> promise) {
        this->databaseThread.scheduleTask([=, &innerRt]() {
          crypto::Persist persist;
          std::string error;
          try {
            folly::Optional<std::string> accountData =
                DatabaseManager::getQueryExecutor().getOlmPersistAccountData();
            if (accountData.hasValue()) {
              persist.account =
                  crypto::OlmBuffer(accountData->begin(), accountData->end());
              // handle sessions data
              std::vector<OlmPersistSession> sessionsData =
                  DatabaseManager::getQueryExecutor()
                      .getOlmPersistSessionsData();
              for (OlmPersistSession &sessionsDataItem : sessionsData) {
                crypto::OlmBuffer sessionDataBuffer(
                    sessionsDataItem.session_data.begin(),
                    sessionsDataItem.session_data.end());
                persist.sessions.insert(std::make_pair(
                    sessionsDataItem.target_user_id, sessionDataBuffer));
              }
            }
          } catch (std::system_error &e) {
            error = e.what();
          }

          this->cryptoThread.scheduleTask([=, &innerRt]() {
            std::string error;
            this->cryptoModule.reset(new crypto::CryptoModule(
                userIdStr, storedSecretKey.value(), persist));
            if (persist.isEmpty()) {
              crypto::Persist newPersist =
                  this->cryptoModule->storeAsB64(storedSecretKey.value());
              this->databaseThread.scheduleTask([=, &innerRt]() {
                std::string error;
                try {
                  DatabaseManager::getQueryExecutor().storeOlmPersistData(
                      newPersist);
                } catch (std::system_error &e) {
                  error = e.what();
                }
                this->jsInvoker_->invokeAsync([=, &innerRt]() {
                  if (error.size()) {
                    promise->reject(error);
                    return;
                  }
                  promise->resolve(jsi::Value::undefined());
                });
              });

            } else {
              this->cryptoModule->restoreFromB64(
                  storedSecretKey.value(), persist);
              this->jsInvoker_->invokeAsync([=, &innerRt]() {
                if (error.size()) {
                  promise->reject(error);
                  return;
                }
                promise->resolve(jsi::Value::undefined());
              });
            }
          });
        });
      });
}

jsi::Value
CommCoreModule::getUserPublicKey(jsi::Runtime &rt, const jsi::String &userId) {
  std::string userIdStr = userId.utf8(rt);
  return createPromiseAsJSIValue(
      rt, [=](jsi::Runtime &innerRt, std::shared_ptr<Promise> promise) {
        taskType job = [=, &innerRt]() {
          std::string error;
          std::string result;
          if (this->cryptoModule == nullptr) {
            error = "user has not been initialized";
          } else {
            result = this->cryptoModule->getIdentityKeys();
          }
          this->jsInvoker_->invokeAsync([=, &innerRt]() {
            if (error.size()) {
              promise->reject(error);
              return;
            }
            promise->resolve(jsi::String::createFromUtf8(innerRt, result));
          });
        };
        this->cryptoThread.scheduleTask(job);
      });
}

jsi::Value CommCoreModule::getUserOneTimeKeys(
    jsi::Runtime &rt,
    const jsi::String &userId) {
  std::string userIdStr = userId.utf8(rt);
  return createPromiseAsJSIValue(
      rt, [=](jsi::Runtime &innerRt, std::shared_ptr<Promise> promise) {
        taskType job = [=, &innerRt]() {
          std::string error;
          std::string result;
          if (this->cryptoModule == nullptr) {
            error = "user has not been initialized";
          } else {
            result = this->cryptoModule->getOneTimeKeys();
          }
          this->jsInvoker_->invokeAsync([=, &innerRt]() {
            if (error.size()) {
              promise->reject(error);
              return;
            }
            promise->resolve(jsi::String::createFromUtf8(innerRt, result));
          });
        };
        this->cryptoThread.scheduleTask(job);
      });
}

CommCoreModule::CommCoreModule(
    std::shared_ptr<facebook::react::CallInvoker> jsInvoker)
    : facebook::react::CommCoreModuleSchemaCxxSpecJSI(jsInvoker),
      databaseThread("database"),
      cryptoThread("crypto"){};

} // namespace comm
