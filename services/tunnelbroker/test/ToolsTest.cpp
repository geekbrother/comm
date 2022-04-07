#include "Tools.h"
#include "Constants.h"

#include <gtest/gtest.h>

#include <string>

using namespace comm::network;

class ToolsTest : public testing::Test {};

TEST_F(ToolsTest, TestOperationsOnGenerateRandomString) {
  const std::size_t length = 32;
  const std::string generated = tools::generateRandomString(length);
  EXPECT_EQ(generated.length(), length);
}

TEST_F(ToolsTest, TestOperationsOnValidateDeviceID) {
  const std::string validDeviceID =
      "mobile:" + tools::generateRandomString(DEVICEID_CHAR_LENGTH);
  const std::string invalidDeviceID =
      "invalid-" + tools::generateRandomString(DEVICEID_CHAR_LENGTH);
  EXPECT_EQ(tools::validateDeviceID(validDeviceID), true);
  EXPECT_EQ(tools::validateDeviceID(invalidDeviceID), false);
}

TEST_F(ToolsTest, TestOperationsOnValidateSessionID) {
  const std::string validSessionID = tools::generateUUID();
  const std::string invalidSessionID = tools::generateRandomString(32);
  EXPECT_EQ(tools::validateSessionID(validSessionID), true);
  EXPECT_EQ(tools::validateSessionID(invalidSessionID), false);
}
