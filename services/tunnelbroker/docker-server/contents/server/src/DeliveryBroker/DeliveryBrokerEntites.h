#pragma once

#include <string.h>
#include <mutex>
#include <unordered_map>
#include <vector>

struct DeliveryBrokerMessageStruct {
  std::string fromDeviceID;
  std::string payload;
  std::vector<std::string> blobHashes;
};

typedef std::
    unordered_map<std::string, std::vector<DeliveryBrokerMessageStruct>>
        DeliveryBrokerHashmapType;
