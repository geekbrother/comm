#include "AmqpManager.h"
namespace comm {
namespace network {

std::unique_ptr<AMQP::TcpChannel> AmqpChannel;
static std::atomic<bool> AmqpReady;

void AMQPConnect() {

  std::cout << "AMQP: Connecting to " << AMQP_URI << std::endl;

  // Make a connection and channel
  boost::asio::io_service BoostIOservice(AMQP_CLIENT_THREADS);
  AMQP::LibBoostAsioHandler AMQPhandler(BoostIOservice);
  AMQP::TcpConnection connection(&AMQPhandler, AMQP::Address(AMQP_URI));
  AmqpChannel = std::make_unique<AMQP::TcpChannel>(&connection);

  AmqpChannel->onError([&connection](const char *message) {
    std::cout << "AMQP: Channel error: " << message << std::endl;
  });

  // Create a queue for the current tunnelbroker instance by it's ID
  AMQP::Table arguments;
  arguments["x-message-ttl"] = AMQP_MESSAGE_TTL;
  arguments["x-expires"] = AMQP_QUEUE_TTL;
  AmqpChannel->declareQueue(TUNNELBROKER_ID, AMQP::durable, arguments)
      .onSuccess([&connection](
                     const std::string &name,
                     uint32_t messagecount,
                     uint32_t consumercount) {
        std::cout << "AMQP: Queue " << name << "created" << std::endl;
        AmqpReady = true;
        AmqpChannel
            ->consume(TUNNELBROKER_ID)
            // Recieved the message from the queue
            .onReceived([&](const AMQP::Message &message,
                            uint64_t deliveryTag,
                            bool redelivered) {
              AMQP::Table headers = message.headers();
              const std::string payload(message.body());
              const std::string toDeviceID(headers[AMQP_HEADER_TO_DEVICEID]);
              const std::string fromDeviceID(
                  headers[AMQP_HEADER_FROM_DEVICEID]);
              DeliveryBrokerPush(toDeviceID, fromDeviceID, payload);
            })
            .onError([](const char *message) {
              std::cout << "AMQP: Error on message consume:  " << message
                        << std::endl;
            });
      })
      .onError([&](const char *message) {
        std::cout << "AMQP: Queue declaration error." << std::endl;
      });
  BoostIOservice.run();
}

bool AMQPSend(
    std::string toDeviceID,
    std::string fromDeviceID,
    std::string payload) {
  if (AmqpReady) {
    try {
      AMQP::Envelope env(payload.c_str(), payload.size());
      AMQP::Table headers;
      headers[AMQP_HEADER_FROM_DEVICEID] = fromDeviceID;
      headers[AMQP_HEADER_TO_DEVICEID] = toDeviceID;
      // Set delivery mode to durable
      env.setDeliveryMode(2);
      env.setHeaders(std::move(headers));
      AmqpChannel->publish("", TUNNELBROKER_ID, env);
    } catch (std::runtime_error &e) {
      std::cout << "AMQP: Error while publishing message:  " << e.what()
                << std::endl;
    }
  } else {
    std::cout << "AMQP: Message send error: channel not ready." << std::endl;
  }
}

} // namespace network
} // namespace comm
