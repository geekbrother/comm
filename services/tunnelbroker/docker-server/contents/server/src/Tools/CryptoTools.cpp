#include "CryptoTools.h"

#include <cryptopp/base64.h>
#include <cryptopp/cryptlib.h>
#include <cryptopp/filters.h>
#include <cryptopp/modes.h>
#include <cryptopp/pssr.h>
#include <cryptopp/rsa.h>
#include <cryptopp/whrlpool.h>

#include <iostream>

namespace comm {
namespace network {
namespace crypto {

bool rsaVerifyString(
    const std::string &publicKeyBase64,
    const std::string &message,
    const std::string &signatureBase64) {
  bool result;
  CryptoPP::Base64Decoder *base64Dec = new CryptoPP::Base64Decoder();

  CryptoPP::RSA::PublicKey publicKey;
  publicKey.Load(
      CryptoPP::StringSource(publicKeyBase64, true, base64Dec).Ref());

  std::string decodedSignature;
  CryptoPP::StringSource ss1(
      signatureBase64,
      true,
      new CryptoPP::Base64Decoder(new CryptoPP::StringSink(decodedSignature)));

  CryptoPP::RSASS<CryptoPP::PSS, CryptoPP::SHA256>::Verifier verifierSha256(
      publicKey);
  result = verifierSha256.VerifyMessage(
      reinterpret_cast<const unsigned char *>(message.c_str()),
      message.length(),
      reinterpret_cast<const unsigned char *>(decodedSignature.c_str()),
      decodedSignature.length());
  return result;
}

} // namespace crypto
} // namespace network
} // namespace comm
