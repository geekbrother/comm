#include "AmqpManager.h"

namespace comm {
namespace network {

std::unique_ptr<AMQP::TcpChannel> AmqpChannel;
static std::atomic<bool> AmqpReady;

void AMQPConnect() {
  std::cout << "[AMQP] Connecting to " << AMQP_URI << std::endl;
  boost::asio::io_service BoostIOservice(AMQP_CLIENT_THREADS);
  AMQP::LibBoostAsioHandler AMQPhandler(BoostIOservice);
  AMQP::TcpConnection connection(&AMQPhandler, AMQP::Address(AMQP_URI));
  AmqpChannel = std::make_unique<AMQP::TcpChannel>(&connection);

  AmqpChannel->onError([&connection](const char *message) {
    std::cout << "[AMQP] Channel error: " << message << std::endl;
    // TODO: I think we need to exit here
  });

  AMQP::Table arguments;
  // commented out since it did not compile...
  // arguments["x-message-ttl"] = AMQP_MESSAGE_TTL;
  // TODO: Maybe we shoud create the exclusive queue instead of regular.
  // AmqpChannel->declareQueue(TUNNELBROKER_ID, AMQP::durable, arguments)
  //     .onSuccess([&connection](
  //                    const std::string &name,
  //                    uint32_t messagecount,
  //                    uint32_t consumercount) {
  //       std::cout << "[AMQP] Queue: " << name << " created." << std::endl;
  //       AmqpReady = true;
  //       AmqpChannel
  //           ->consume(TUNNELBROKER_ID)
  //           .onReceived([&](const AMQP::Message &message,
  //                           uint64_t deliveryTag,
  //                           bool redelivered) {
  //             // TODO: Parse and push the message to the DeliveryBroker.
  //           })
  //           .onError([](const char *message) {
  //             std::cout << "[AMQP] Error on consume message: " << message
  //                       << std::endl;
  //           });
  //     })
  //     .onError([&](const char *message) {
  //       std::cout << "[AMQP] Queue decraration error." << std::endl;
  //       // TODO: I think we need to exit here
  //     });
  // BoostIOservice.run();
}

bool AMQPSend(std::string payload) {
  if (AmqpReady) {
    AmqpChannel->publish("", TUNNELBROKER_ID, payload);
  } else {
    std::cout << "[AMQP] Send error: AMQP channel not ready." << std::endl;
  }
}

} // namespace network
} // namespace comm
