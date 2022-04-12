#include "Tools.h"
#include "Constants.h"

#include <gtest/gtest.h>

#include <string>

using namespace comm::network;

class ToolsTest : public testing::Test {};

TEST_F(ToolsTest, TestOperationsOnGenerateRandomString) {
  const std::size_t length = 32;
  const std::string generated = tools::generateRandomString(length);
  EXPECT_EQ(generated.length(), length)
      << "Generated random string \"" << generated << "\" length "
      << generated.length() << " is not equal to " << length;
}

TEST_F(ToolsTest, TestOperationsOnValidateDeviceIDValid) {
  const std::string validDeviceID =
      "mobile:" + tools::generateRandomString(DEVICEID_CHAR_LENGTH);
  EXPECT_EQ(tools::validateDeviceID(validDeviceID), true)
      << "Valid generated deviceID \"" << validDeviceID
      << "\" is invalid by the function";
}

TEST_F(ToolsTest, TestOperationsOnValidateDeviceIDInvalid) {
  const std::string invalidDeviceIDPrefix =
      "invalid-" + tools::generateRandomString(DEVICEID_CHAR_LENGTH);
  EXPECT_EQ(tools::validateDeviceID(invalidDeviceIDPrefix), false)
      << "Invalid prefix generated deviceID \"" << invalidDeviceIDPrefix
      << "\" is valid by the function";
  const std::string invalidDeviceIDSuffix =
      "mobile:" + tools::generateRandomString(DEVICEID_CHAR_LENGTH - 1);
  EXPECT_EQ(tools::validateDeviceID(invalidDeviceIDSuffix), false)
      << "Invalid suffix generated deviceID \"" << invalidDeviceIDSuffix
      << "\" is valid by the function";
}

TEST_F(ToolsTest, TestOperationsOnValidateSessionIDValid) {
  const std::string validSessionID = tools::generateUUID();
  EXPECT_EQ(tools::validateSessionID(validSessionID), true)
      << "Valid generated sessionID \"" << validSessionID
      << "\" is invalid by the function";
}

TEST_F(ToolsTest, TestOperationsOnValidateSessionIDInvalid) {
  const std::string invalidSessionID = tools::generateRandomString(32);
  EXPECT_EQ(tools::validateSessionID(invalidSessionID), false)
      << "Invalid generated sessionID \"" << invalidSessionID
      << "\" is valid by the function";
}
