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
  std::unique_ptr<CryptoPP::Base64Decoder> base64Dec =
      std::make_unique<CryptoPP::Base64Decoder>();
  CryptoPP::RSA::PublicKey publicKey;

  try {
    publicKey.Load(
        CryptoPP::StringSource(publicKeyBase64, true, &(*base64Dec)).Ref());
    std::string decodedSignature;
    std::unique_ptr<CryptoPP::StringSink> decodedSignatureString =
        std::make_unique<CryptoPP::StringSink>(decodedSignature);

    CryptoPP::StringSource signatureString(
        signatureBase64,
        true,
        &(*std::make_unique<CryptoPP::Base64Decoder>(
            &(*decodedSignatureString))));

    CryptoPP::RSASS<CryptoPP::PSS, CryptoPP::SHA256>::Verifier verifierSha256(
        publicKey);
    result = verifierSha256.VerifyMessage(
        reinterpret_cast<const unsigned char *>(message.c_str()),
        message.length(),
        reinterpret_cast<const unsigned char *>(decodedSignature.c_str()),
        decodedSignature.length());
    return result;
  } catch (const std::exception &e) {
    std::cout << "CryptoTools: "
              << "Got an exception " << e.what() << std::endl;
    return false;
  } catch (const std::runtime_error &e) {
    std::cout << "CryptoTools: "
              << "Runtime error " << e.what() << std::endl;
    return false;
  }
}

} // namespace crypto
} // namespace network
} // namespace comm
