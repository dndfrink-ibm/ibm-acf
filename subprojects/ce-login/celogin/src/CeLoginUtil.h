#include "CeLoginAsnV1.h"
#include "JsmnUtils.h"

#include <CeLogin.h>
#include <openssl/obj_mac.h>
#include <openssl/sha.h>
#include <openssl/evp.h>
#include <vector>

#ifndef _CELOGINUTIL_H
#define _CELOGINUTIL_H

namespace CeLogin
{
extern const char* FrameworkEc_P10_Dev;
extern const char* FrameworkEc_P10_Service;

enum
{
    // The ACF, Digest, and DigestLength should use the same algorithms
    CeLogin_Acf_NID = NID_sha512WithRSAEncryption, // Used in ASN.1
    CeLogin_Digest_NID = NID_sha512, // Used for OpenSSL RSA sign/verify routine
    CeLogin_DigestLength = SHA512_DIGEST_LENGTH,

    CeLogin_MaxHashedAuthCodeLength = 256,
    CeLogin_MaxHashedAuthCodeSaltLength = 128,

    CeLogin_MaxNumberOfJsonTokens = 128, // somewhat arbitrary right now
};

CeLoginRc getCeLoginRcFromJsmnRc(const JsmnUtils::JsmnUtilRc jsmnRc);

CeLoginRc getBinaryFromHex(const char* hexStringParm,
                           const uint64_t hexStringLengthParm,
                           uint8_t* binaryParm, const uint64_t binarySizeParm,
                           uint64_t& binaryLengthParm);

CeLoginRc getDateFromString(const char* dateStringParm,
                            const uint64_t dateStringLengthParm,
                            CeLogin_Date& dateParm);

CeLoginRc getAsn1Time(const CeLogin_Date& dateParm, ASN1_TIME* timeParm);

CeLoginRc decodeAndVerifySignature(const uint8_t* accessControlFileParm,
                                   const uint64_t accessControlFileLengthParm,
                                   const uint8_t* publicKeyParm,
                                   uint64_t publicKeyLengthParm,
                                   CELoginSequenceV1*& decodedAsnParm);

CeLoginRc decodeAndVerifyAcf(const uint8_t* accessControlFileParm,
                             const uint64_t accessControlFileLengthParm,
                             const uint8_t* publicKeyParm,
                             uint64_t publicKeyLengthParm,
                             CELoginSequenceV1*& decodedAsnParm);

CeLoginRc createDigest(const uint8_t* inputDataParm,
                       const uint64_t inputDataLengthParm,
                       uint8_t* outputHashParm,
                       const uint64_t outputHashSizeParm);

CeLoginRc createPasswordHash(const char* inputDataParm,
                             const uint64_t inputDataLengthParm,
                             const uint8_t* inputSaltParm,
                             const uint64_t inputSaltLengthParm,
                             const uint64_t iterationsParm,
                             uint8_t* outputHashParm,
                             const uint64_t outputHashSizeParm,
                             const uint64_t requestedOutputLengthParm);

CeLoginRc getUnsignedIntegerFromString(const char* stringParm,
                                       const uint64_t stringLengthParm,
                                       uint64_t& integerParm);

CeLoginRc
    getServiceAuthorityFromFrameworkEc(const char* frameworkEcParm,
                                       const uint64_t frameworkEcLengthParm,
                                       ServiceAuthority& authParm);

CeLoginRc verifySignature(EVP_PKEY* publicKeyParm, const EVP_MD* mdTypeParm, 
                          const uint8_t* signatureParm, size_t signatureLengthParm,
                          const uint8_t* digestParm, size_t digestLengthParm);

CeLoginRc createSignature(EVP_PKEY* privateKeyParm, const EVP_MD* mdParm,
                          const std::vector<uint8_t>& digestParm,
                          std::vector<uint8_t>& generatedSignatureParm,
                          size_t& signatureSizeParm);
}; // namespace CeLogin

#endif
