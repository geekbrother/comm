#include "CryptoTools.h"

#include <cryptopp/cryptlib.h>
#include <cryptopp/filters.h>
#include <cryptopp/hex.h>
#include <cryptopp/modes.h>
#include <cryptopp/osrng.h>
#include <cryptopp/pssr.h>
#include <cryptopp/rsa.h>
#include <cryptopp/whrlpool.h>

#include <iostream>

namespace comm {
namespace network {

bool RsaVerifyString(
    const std::string &aPublicKeyStrHex,
    const std::string &aMessage,
    const std::string &aSignatureStrHex) {
  using Verifier =
      CryptoPP::RSASS<CryptoPP::PSSR, CryptoPP::Whirlpool>::Verifier;
  CryptoPP::RSA::PublicKey publicKey;
  publicKey.Load(
      CryptoPP::StringSource(aPublicKeyStrHex, true, new CryptoPP::HexDecoder())
          .Ref());
  std::string decodedSignature;
  CryptoPP::StringSource ss(
      aSignatureStrHex,
      true,
      new CryptoPP::HexDecoder(new CryptoPP::StringSink(decodedSignature)));
  bool result = false;
  Verifier verifier(publicKey);
  CryptoPP::StringSource ss2(
      decodedSignature + aMessage,
      true,
      new CryptoPP::SignatureVerificationFilter(
          verifier,
          new CryptoPP::ArraySink((CryptoPP::byte *)&result, sizeof(result))));
  return result;
}

} // namespace network
} // namespace comm
