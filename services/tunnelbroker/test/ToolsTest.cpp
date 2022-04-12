#include "Tools.h"
#include "Constants.h"

#include <gtest/gtest.h>

#include <string>

using namespace comm::network;

class ToolsTest : public testing::Test {};

TEST(ToolsTest, GeneratedRandomStringHasValidLength) {
  const std::size_t length = 32;
  const std::string generated = tools::generateRandomString(length);
  EXPECT_EQ(generated.length(), length)
      << "Generated random string \"" << generated << "\" length "
      << generated.length() << " is not equal to " << length;
}

TEST(ToolsTest, ValidateDeviceIDReturnTrueOnStaticValidDeviceID) {
  const std::string validDeviceID =
      "mobile:EMQNoQ7b2ueEmQ4QsevRWlXxFCNt055y20T1PHdoYAQRt0S6TLzZWNM6XSvdWqxm";
  EXPECT_EQ(tools::validateDeviceID(validDeviceID), true)
      << "Valid deviceID \"" << validDeviceID
      << "\" is invalid by the function";
}

TEST(ToolsTest, ValidateDeviceIDReturnTrueOnGeneratedValidDeviceID) {
  const std::string validDeviceID =
      "mobile:" + tools::generateRandomString(DEVICEID_CHAR_LENGTH);
  EXPECT_EQ(tools::validateDeviceID(validDeviceID), true)
      << "Valid generated deviceID \"" << validDeviceID
      << "\" is invalid by the function";
}

TEST(ToolsTest, ValidateDeviceIDReturnFalseOnInvalidDeviceIDPrefix) {
  const std::string invalidDeviceIDPrefix =
      "invalid-"
      "EMQNoQ7b2ueEmQ4QsevRWlXxFCNt055y20T1PHdoYAQRt0S6TLzZWNM6XSvdWqxm";
  EXPECT_EQ(tools::validateDeviceID(invalidDeviceIDPrefix), false)
      << "Invalid prefix deviceID \"" << invalidDeviceIDPrefix
      << "\" is valid by the function";
}

TEST(ToolsTest, ValidateDeviceIDReturnFalseOnInvalidDeviceIDSuffix) {
  const std::string invalidDeviceIDSuffix =
      "mobile:tQNoQ7b2ueEmQ4QsevRWlXxFCNt055y20T1PHdoYAQRt0S6TLzZWNM6XSvdWqxm";
  EXPECT_EQ(tools::validateDeviceID(invalidDeviceIDSuffix), false)
      << "Invalid suffix deviceID \"" << invalidDeviceIDSuffix
      << "\" is valid by the function";
}

TEST(ToolsTest, ValidateSessionIDReturnTrueOnValidStaticSessionID) {
  const std::string validSessionID = "bc0c1aa2-bf09-11ec-9d64-0242ac120002";
  EXPECT_EQ(tools::validateSessionID(validSessionID), true)
      << "Valid sessionID \"" << validSessionID
      << "\" is invalid by the function";
}

TEST(ToolsTest, ValidateSessionIDReturnTrueOnValidGeneratedSessionID) {
  const std::string validSessionID = tools::generateUUID();
  EXPECT_EQ(tools::validateSessionID(validSessionID), true)
      << "Valid generated sessionID \"" << validSessionID
      << "\" is invalid by the function";
}

TEST(ToolsTest, ValidateSessionIDReturnFalseOnInvalidSessionID) {
  const std::string invalidSessionID = "bc0c1aa29bf09-11ec-9d64-0242ac120002";
  EXPECT_EQ(tools::validateSessionID(invalidSessionID), false)
      << "Invalid sessionID \"" << invalidSessionID
      << "\" is valid by the function";
}
