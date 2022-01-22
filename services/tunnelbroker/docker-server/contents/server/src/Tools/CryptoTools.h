#pragma once

#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/rsa.h>

#include <iostream>

namespace comm {
namespace network {

size_t calcDecodeLength(const char *b64input);
void Base64Decode(
    const char *b64message,
    unsigned char **buffer,
    size_t *length);
RSA *createPublicRSA(std::string key);
bool RSAVerifySignature(
    RSA *rsa,
    unsigned char *MsgHash,
    size_t MsgHashLen,
    const char *Msg,
    size_t MsgLen,
    bool *Authentic);
bool verifySignature(
    std::string publicKey,
    std::string plainText,
    char *signatureBase64);

} // namespace network
} // namespace comm
