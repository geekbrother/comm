#include "CryptoTools.h"

#include <cryptopp/base64.h>
#include <cryptopp/cryptlib.h>
#include <cryptopp/filters.h>
#include <cryptopp/modes.h>
#include <cryptopp/pssr.h>
#include <cryptopp/rsa.h>
#include <cryptopp/whrlpool.h>

#include <memory>

#include <iostream>

namespace comm {
namespace network {
namespace crypto {

bool rsaVerifyString(
    const std::string &publicKeyBase64,
    const std::string &message,
    const std::string &signatureBase64) {
  bool result = false;
  using Verifier =
      CryptoPP::RSASS<CryptoPP::PSSR, CryptoPP::Whirlpool>::Verifier;
  std::unique_ptr<CryptoPP::Base64Decoder> base64Dec =
      std::make_unique<CryptoPP::Base64Decoder>();
  CryptoPP::RSA::PublicKey publicKey;
  publicKey.Load(
      CryptoPP::StringSource(publicKeyBase64, true, &(*base64Dec)).Ref());
  std::string decodedSignature;

  std::unique_ptr<CryptoPP::StringSink> strSing =
      std::make_unique<CryptoPP::StringSink>(decodedSignature);
  base64Dec.reset(new CryptoPP::Base64Decoder(&(*strSing)));
  CryptoPP::StringSource decodedSignatureSource(
      signatureBase64, true, &(*base64Dec));

  Verifier verifier(publicKey);
  std::unique_ptr<CryptoPP::ArraySink> arrSink =
      std::make_unique<CryptoPP::ArraySink>(
          (CryptoPP::byte *)&result, sizeof(result));
  std::unique_ptr<CryptoPP::SignatureVerificationFilter> verificationFilter =
      std::make_unique<CryptoPP::SignatureVerificationFilter>(
          verifier, &(*arrSink));
  CryptoPP::StringSource signatureVerificationSource(
      decodedSignature + message, true, &(*verificationFilter));

  return result;
}

} // namespace crypto
} // namespace network
} // namespace comm
