// ---------------------------------------------------------------------------------------
// xecrypt.h
//
// Copyright (C) Microsoft Corporation
// ---------------------------------------------------------------------------------------

#ifndef _XECRYPT_H_
#define _XECRYPT_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned __int64 QWORD;
#define XECRYPTAPI __stdcall

// ---------------------------------------------------------------------------------------
// DES Cipher
//
// These functions implement symmetric encryption and decryption with the DES cipher.
//
// The DES block size is 8 bytes and the DES key size is 8 bytes.
//
// XeCryptDesKey initializes an XECRYPT_DES_STATE structure from a DES key.
//
// XeCryptDesEcb encrypts or decrypts a single DES block.
//
// XeCryptDesCbc encrypts or decrypts a contiguous series of blocks using cipher block
// chaining.  On input the pbFeed parameter is the initialization vector.  On output the
// pbFeed parameter is filled with the final ciphertext block.
// ---------------------------------------------------------------------------------------

typedef struct {
    unsigned long       keytab[16][2];
} XECRYPT_DES_STATE;

#define XECRYPT_DES_BLOCK_SIZE      (8)
#define XECRYPT_DES_KEY_SIZE        (8)

void  XECRYPTAPI XeCryptDesParity(const BYTE * pbInp, DWORD cbInp, BYTE * pbOut);

void  XECRYPTAPI XeCryptDesKey(XECRYPT_DES_STATE * pDesState, const BYTE * pbKey);
void  XECRYPTAPI XeCryptDesEcb(const XECRYPT_DES_STATE * pDesState, const BYTE * pbInp, BYTE * pbOut, BOOL fEncrypt);
void  XECRYPTAPI XeCryptDesCbc(const XECRYPT_DES_STATE * pDesState, const BYTE * pbInp, DWORD cbInp, BYTE * pbOut, BYTE * pbFeed, BOOL fEncrypt);

// ---------------------------------------------------------------------------------------
// DES3 Cipher
//
// These functions implement symmetric encryption and decryption with the DES3 cipher.
//
// The DES3 block size is 8 bytes and the DES3 key size is 24 bytes.
//
// XeCryptDes3Key initializes an XECRYPT_DES3_STATE structure from a DES3 key.
//
// XeCryptDes3Ecb encrypts or decrypts a single DES block.
//
// XeCryptDes3Cbc encrypts or decrypts a contiguous series of blocks using cipher block
// chaining.  On input the pbFeed parameter is the initialization vector.  On output the
// pbFeed parameter is filled with the final ciphertext block.
// ---------------------------------------------------------------------------------------

typedef struct {
    XECRYPT_DES_STATE   aDesState[3];
} XECRYPT_DES3_STATE;

#define XECRYPT_DES3_KEY_SIZE       (24)

void  XECRYPTAPI XeCryptDes3Key(XECRYPT_DES3_STATE * pDes3State, const BYTE * pbKey);
void  XECRYPTAPI XeCryptDes3Ecb(const XECRYPT_DES3_STATE * pDes3State, const BYTE * pbInp, BYTE * pbOut, BOOL fEncrypt);
void  XECRYPTAPI XeCryptDes3Cbc(const XECRYPT_DES3_STATE * pDes3State, const BYTE * pbInp, DWORD cbInp, BYTE * pbOut, BYTE * pbFeed, BOOL fEncrypt);

// ---------------------------------------------------------------------------------------
// AES Cipher
//
// These functions implement symmetric encryption and decryption with the AES cipher.
//
// The AES block size is 16 bytes and the AES key size is 16 bytes.
//
// XeCryptAesKey initializes an XECRYPT_AES_STATE structure from an AES key.
//
// XeCryptAesEcb encrypts or decrypts a single AES block.
//
// XeCryptAesCbc encrypts or decrypts a contiguous series of blocks using cipher block
// chaining.  On input the pbFeed parameter is the initialization vector.  On output the
// pbFeed parameter is filled with the final ciphertext block.
// ---------------------------------------------------------------------------------------

typedef struct {
    BYTE                keytabenc[11][4][4];
    BYTE                keytabdec[11][4][4];
} XECRYPT_AES_STATE;

#define XECRYPT_AES_BLOCK_SIZE      (16)
#define XECRYPT_AES_KEY_SIZE        (16)

void  XECRYPTAPI XeCryptAesKey(XECRYPT_AES_STATE * pAesState, const BYTE * pbKey);
void  XECRYPTAPI XeCryptAesEcb(const XECRYPT_AES_STATE * pAesState, const BYTE * pbInp, BYTE * pbOut, BOOL fEncrypt);
void  XECRYPTAPI XeCryptAesCbc(const XECRYPT_AES_STATE * pAesState, const BYTE * pbInp, DWORD cbInp, BYTE * pbOut, BYTE * pbFeed, BOOL fEncrypt);

// ---------------------------------------------------------------------------------------
// RC4 Stream Cipher
//
// These functions implement the RC4 stream cipher.
//
// The RC4 key size can be anywhere from zero to 256 bytes long.
//
// XeCryptRc4Key initializes an XECRYPT_RC4_STATE from an RC4 key.
//
// XeCryptRc4Ecb encrypts or decrypts a stream of bytes.
//
// XeCryptRc4 combines both of the previous functions for convenience.
// ---------------------------------------------------------------------------------------

typedef struct {
    BYTE                S[256];
    BYTE                i,j;
} XECRYPT_RC4_STATE;

void  XECRYPTAPI XeCryptRc4Key(XECRYPT_RC4_STATE * pRc4State, const BYTE * pbKey, DWORD cbKey);
void  XECRYPTAPI XeCryptRc4Ecb(XECRYPT_RC4_STATE * pRc4State, BYTE * pbInpOut, DWORD cbInpOut);
void  XECRYPTAPI XeCryptRc4(const BYTE * pbKey, DWORD cbKey, BYTE * pbInpOut, DWORD cbInpOut);

// ---------------------------------------------------------------------------------------
// SHA
//
// These functions implement the SHA-1 one-way hash algorithm.  The result of the hash of
// any number of bytes is a digest of 20 bytes.
//
// XeCryptShaInit initializes an XECRYPT_SHA_STATE structure.
//
// Next, for each block of bytes that are to be hashed, call XeCryptShaUpdate.  There is
// no limit to the size of the block, and it doesn't matter how the blocks are divided.
//
// Finally, call XeCryptShaFinal to compute the digest.  Note that after calling this
// function the digest is available in the "state".  The cbOut parameter can be less
// than 20 if only a prefix of the resulting digest is needed.  It can be zero if the
// resulting digest will be read directly from the state structure.
//
// For convenience, all of these operations are combined by a single call to XeCryptSha.
// ---------------------------------------------------------------------------------------

typedef struct {
    DWORD               count;
    DWORD               state[5];
    BYTE                buffer[64];
} XECRYPT_SHA_STATE;

#define XECRYPT_SHA_DIGEST_SIZE     (20)

void  XECRYPTAPI XeCryptShaInit(XECRYPT_SHA_STATE * pShaState);
void  XECRYPTAPI XeCryptShaUpdate(XECRYPT_SHA_STATE * pShaState, const BYTE * pbInp, DWORD cbInp);
void  XECRYPTAPI XeCryptShaFinal(XECRYPT_SHA_STATE * pShaState, BYTE * pbOut, DWORD cbOut);
void  XECRYPTAPI XeCryptSha(const BYTE * pbInp1, DWORD cbInp1, const BYTE * pbInp2, DWORD cbInp2, const BYTE * pbInp3, DWORD cbInp3, BYTE * pbOut, DWORD cbOut);
void  XECRYPTAPI XeCryptRotSumSha(const BYTE * pbInp1, DWORD cbInp1, const BYTE * pbInp2, DWORD cbInp2, BYTE * pbOut, DWORD cbOut);

// ---------------------------------------------------------------------------------------
// HMAC-SHA
//
// These functions implement the keyed HMAC-SHA-1 algorithm.  The result is a digest of
// 20 bytes.
//
// First, initialize an XECRYPT_HMACSHA_STATE structure by calling XeCryptHmacShaInit with
// a key of up to 64 bytes.
//
// Next, for each block of bytes that are to be hashed, call XeCryptHmacShaUpdate.  There
// is no limit to the size of the block, and it doesn't matter how the blocks are divided.
//
// Finally, call XeCryptHmacShaFinal to compute the digest.  The cbOut parameter can be
// less than 20 if only a prefix of the resulting digest is needed.
//
// For convenience, all of these operations are combined by a single call to XeCryptSha.
// 
// The XeCryptHmacShaVerify function computes the digest just like a single call to
// XeCryptHmacSha, then compares the resulting digest to the expected digest passed in
// through the pbVer/cbVer arguments.  Note that cbVer can be less than 20 if only a
// prefix of the resulting digest should be compared.  The result is TRUE if the
// computed and expected digests match, and FALSE otherwise.
// ---------------------------------------------------------------------------------------

typedef struct {
    XECRYPT_SHA_STATE   ShaState[2];
} XECRYPT_HMACSHA_STATE;

void  XECRYPTAPI XeCryptHmacShaInit(XECRYPT_HMACSHA_STATE * pHmacShaState, const BYTE * pbKey, DWORD cbKey);
void  XECRYPTAPI XeCryptHmacShaUpdate(XECRYPT_HMACSHA_STATE * pHmacShaState, const BYTE * pbInp, DWORD cbInp);
void  XECRYPTAPI XeCryptHmacShaFinal(XECRYPT_HMACSHA_STATE * pHmacShaState, BYTE * pbOut, DWORD cbOut);
void  XECRYPTAPI XeCryptHmacSha(const BYTE * pbKey, DWORD cbKey, const BYTE * pbInp1, DWORD cbInp1, const BYTE * pbInp2, DWORD cbInp2, const BYTE * pbInp3, DWORD cbInp3, BYTE * pbOut, DWORD cbOut);
BOOL  XECRYPTAPI XeCryptHmacShaVerify(const BYTE * pbKey, DWORD cbKey, const BYTE * pbInp1, DWORD cbInp1, const BYTE * pbInp2, DWORD cbInp2, const BYTE * pbInp3, DWORD cbInp3, const BYTE * pbVer, DWORD cbVer);

// ---------------------------------------------------------------------------------------
// MD5
//
// These functions implement the MD5 one-way hash algorithm.  The result of the hash of
// any number of bytes is a digest of 16 bytes.
//
// First, initialize an XECRYPT_MD5_STATE structure by calling XeCryptMd5Init.
//
// Next, for each block of bytes that are to be hashed, call XeCryptMd5Update.  There is
// no limit to the size of the block, and it doesn't matter how the blocks are divided.
//
// Finally, call XeCryptMd5Final to compute the digest.  Note that after calling this
// function the digest is available in the "state".  The cbOut parameter can be less
// than 16 if only a prefix of the resulting digest is needed.  It can be zero if the
// resulting digest will be read directly from the state structure.
//
// For convenience, all of these operations are combined by a single call to XeCryptMd5.
// ---------------------------------------------------------------------------------------

typedef struct {
    DWORD               count;
    DWORD               buf[4];
    BYTE                in[64];
} XECRYPT_MD5_STATE;

#define XECRYPT_MD5_DIGEST_SIZE     (16)

void  XECRYPTAPI XeCryptMd5Init(XECRYPT_MD5_STATE * pMd5State);
void  XECRYPTAPI XeCryptMd5Update(XECRYPT_MD5_STATE * pMd5State, const BYTE * pbInp, DWORD cbInp);
void  XECRYPTAPI XeCryptMd5Final(XECRYPT_MD5_STATE * pMd5State, BYTE * pbOut, DWORD cbOut);
void  XECRYPTAPI XeCryptMd5(const BYTE * pbInp1, DWORD cbInp1, const BYTE * pbInp2, DWORD cbInp2, const BYTE * pbInp3, DWORD cbInp3, BYTE * pbOut, DWORD cbOut);

// ---------------------------------------------------------------------------------------
// HMAC-MD5
//
// These functions implement the keyed HMAC-MD5 algorithm.  The result is a digest of
// 16 bytes.
//
// First, initialize an XECRYPT_HMACMD5_STATE structure by calling XeCryptHmacMd5Init with
// a key of up to 64 bytes.
//
// Next, for each block of bytes that are to be hashed, call XeCryptHmacMd5Update.  There
// is no limit to the size of the block, and it doesn't matter how the blocks are divided.
//
// Finally, call XeCryptHmacMd5Final to compute the digest.  The cbOut parameter can be
// less than 20 if only a prefix of the resulting digest is needed.
//
// For convenience, all of these operations are combined by a single call to XeCryptMd5.
// ---------------------------------------------------------------------------------------

typedef struct {
    XECRYPT_MD5_STATE   Md5State[2];
} XECRYPT_HMACMD5_STATE;

void  XECRYPTAPI XeCryptHmacMd5Init(XECRYPT_HMACMD5_STATE * pHmacMd5State, const BYTE * pbKey, DWORD cbKey);
void  XECRYPTAPI XeCryptHmacMd5Update(XECRYPT_HMACMD5_STATE * pHmacMd5State, const BYTE * pbInp, DWORD cbInp);
void  XECRYPTAPI XeCryptHmacMd5Final(XECRYPT_HMACMD5_STATE * pHmacMd5State, BYTE * pbOut, DWORD cbOut);
void  XECRYPTAPI XeCryptHmacMd5(const BYTE * pbKey, DWORD cbKey, const BYTE * pbInp1, DWORD cbInp1, const BYTE * pbInp2, DWORD cbInp2, const BYTE * pbInp3, DWORD cbInp3, BYTE * pbOut, DWORD cbOut);

// ---------------------------------------------------------------------------------------
// Big Number Representations
// 
// Multiple precision numbers are arranged as an array of digits, with the least
// significant digit coming first ("little-endian digit ordering"), regardless
// of the word size or byte ordering of the digit itself.
//
// A single digit is either a DWORD (4 bytes) or a QWORD (8 bytes).  A bignum that
// consists of a series of DWORD digits is tagged "BnDw", whereas a bignum that
// consists of a series of QWORD digits is tagged "BnQw".  A bignum function
// is tagged with one of these two to specify the digit size it expects, and it
// takes a length parameter that specifies the number of digits in the number.
//
// Consider a 8-byte number written in radix 256 notation.  Here R=256.
//
//     b7*(R^7)+b6*(R^6)+b5*(R^5)+b4*(R^5)+b3*(R^3)+b2*(R^2)+b1*(R^1)+b0*(R^0)
//
// A BnDw bignum consists of a series of DWORD digits.  The DWORD can be encoded
// in either little-endian or big-endian byte ordering.  Thus there are two
// possible formats for these digits.
//
//     DwLe     [b0 b1 b2 b3][b4 b5 b6 b7]
//     DwBe     [b3 b2 b1 b0][b7 b6 b5 b4]
//
// A BnQw bignum consists of a series of QWORD digits.  The QWORD can be encoded
// in either little-endian or big-endian byte ordering.  Thus there are two
// possible formats for these digits.
//
//     QwLe     [b0 b1 b2 b3 b4 b5 b6 b7]
//     QwBe     [b7 b6 b5 b4 b3 b2 b1 b0]
//
// A particular platform has a natural byte order (Le or Be).  We use the tag Ne
// to mean the natural byte order.
//
// Most low level bignum routines require inputs that are in QwNe format.  That
// is, QWORD digits in natural byte order for the platform.  They take an array
// of QWORD digits and a count of digits.  The caller is responsible for converting
// the bignum into the expected format.
//
// A full complement of conversion functions is available.  The BnDw functions
// will convert a bignum made up of a series of DWORD digits between DwLe, DwBe,
// and DwNe formats.  The BnQw functions will convert a bignum made up of a series
// of QWORD digits between QwLe, QwBe, and QwNe formats.  The BnQw functions can
// also convert between BnDw and BnQw bignum formats, but since the length parameter
// specifies the number of QWORD digits, the BnDw bignum must contain an even number
// of DWORD digits.
//
// When a bignum is to be stored or used on multiple platforms, the application
// must choose a concrete representation for the number.  In the case of digital
// signatures, we choose to store them in QwBe format.  This was chosen to match
// the natural word size and byte ordering of the Xenon console, so that the
// signature checking code would be as small and fast as possible on that platform.
// ---------------------------------------------------------------------------------------

void  XECRYPTAPI XeCryptBnDw_Zero(DWORD * pdw, DWORD cdw);
void  XECRYPTAPI XeCryptBnDw_Copy(const DWORD * pdwInp, DWORD * pdwOut, DWORD cdw);
void  XECRYPTAPI XeCryptBnDw_SwapLeBe(const DWORD * pdwInp, DWORD * pdwOut, DWORD cdw);

void  XECRYPTAPI XeCryptBnQw_Zero(QWORD * pqw, DWORD cqw);
void  XECRYPTAPI XeCryptBnQw_Copy(const QWORD * pqwInp, QWORD * pqwOut, DWORD cqw);
void  XECRYPTAPI XeCryptBnQw_SwapLeBe(const QWORD * pqwInp, QWORD * pqwOut, DWORD cqw);
void  XECRYPTAPI XeCryptBnQw_SwapDwQw(const QWORD * pqwInp, QWORD * pqwOut, DWORD cqw);
void  XECRYPTAPI XeCryptBnQw_SwapDwQwLeBe(const QWORD * pqwInp, QWORD * pqwOut, DWORD cqw);

#define XeCryptBnDw_DwLeToDwLe      XeCryptBnDw_Copy
#define XeCryptBnDw_DwLeToDwBe      XeCryptBnDw_SwapLeBe
#define XeCryptBnDw_DwBeToDwLe      XeCryptBnDw_SwapLeBe
#define XeCryptBnDw_DwBeToDwBe      XeCryptBnDw_Copy

#define XeCryptBnQw_DwLeToDwLe      XeCryptBnQw_Copy
#define XeCryptBnQw_DwLeToDwBe      XeCryptBnQw_SwapLeBe
#define XeCryptBnQw_DwLeToQwLe      XeCryptBnQw_Copy
#define XeCryptBnQw_DwLeToQwBe      XeCryptBnQw_SwapDwQwLeBe

#define XeCryptBnQw_DwBeToDwLe      XeCryptBnQw_SwapLeBe
#define XeCryptBnQw_DwBeToDwBe      XeCryptBnQw_Copy
#define XeCryptBnQw_DwBeToQwLe      XeCryptBnQw_SwapLeBe
#define XeCryptBnQw_DwBeToQwBe      XeCryptBnQw_SwapDwQw

#define XeCryptBnQw_QwLeToDwLe      XeCryptBnQw_Copy
#define XeCryptBnQw_QwLeToDwBe      XeCryptBnQw_SwapLeBe
#define XeCryptBnQw_QwLeToQwLe      XeCryptBnQw_Copy
#define XeCryptBnQw_QwLeToQwBe      XeCryptBnQw_SwapDwQwLeBe

#define XeCryptBnQw_QwBeToDwLe      XeCryptBnQw_SwapDwQwLeBe
#define XeCryptBnQw_QwBeToDwBe      XeCryptBnQw_SwapDwQw
#define XeCryptBnQw_QwBeToQwLe      XeCryptBnQw_SwapDwQwLeBe
#define XeCryptBnQw_QwBeToQwBe      XeCryptBnQw_Copy

#ifdef _M_PPCBE

#define XeCryptBnDw_DwLeToDwNe      XeCryptBnDw_DwLeToDwBe
#define XeCryptBnDw_DwBeToDwNe      XeCryptBnDw_DwBeToDwBe
#define XeCryptBnDw_DwNeToDwLe      XeCryptBnDw_DwBeToDwLe
#define XeCryptBnDw_DwNeToDwBe      XeCryptBnDw_DwBeToDwBe

#define XeCryptBnQw_DwLeToDwNe      XeCryptBnQw_DwLeToDwBe
#define XeCryptBnQw_DwLeToQwNe      XeCryptBnQw_DwLeToQwBe
#define XeCryptBnQw_DwBeToDwNe      XeCryptBnQw_DwBeToDwBe
#define XeCryptBnQw_DwBeToQwNe      XeCryptBnQw_DwBeToQwBe

#define XeCryptBnQw_QwLeToDwNe      XeCryptBnQw_QwLeToDwBe
#define XeCryptBnQw_QwLeToQwNe      XeCryptBnQw_QwLeToQwBe
#define XeCryptBnQw_QwBeToDwNe      XeCryptBnQw_QwBeToDwBe
#define XeCryptBnQw_QwBeToQwNe      XeCryptBnQw_QwBeToQwBe

#define XeCryptBnQw_DwNeToDwLe      XeCryptBnQw_DwBeToDwLe 
#define XeCryptBnQw_DwNeToDwBe      XeCryptBnQw_DwBeToDwBe 
#define XeCryptBnQw_DwNeToQwLe      XeCryptBnQw_DwBeToQwLe 
#define XeCryptBnQw_DwNeToQwBe      XeCryptBnQw_DwBeToQwBe 

#define XeCryptBnQw_QwNeToDwLe      XeCryptBnQw_QwBeToDwLe 
#define XeCryptBnQw_QwNeToDwBe      XeCryptBnQw_QwBeToDwBe 
#define XeCryptBnQw_QwNeToQwLe      XeCryptBnQw_QwBeToQwLe 
#define XeCryptBnQw_QwNeToQwBe      XeCryptBnQw_QwBeToQwBe 

#else

#define XeCryptBnDw_DwLeToDwNe      XeCryptBnDw_DwLeToDwLe
#define XeCryptBnDw_DwBeToDwNe      XeCryptBnDw_DwBeToDwLe
#define XeCryptBnDw_DwNeToDwLe      XeCryptBnDw_DwLeToDwLe
#define XeCryptBnDw_DwNeToDwBe      XeCryptBnDw_DwLeToDwBe

#define XeCryptBnQw_DwLeToDwNe      XeCryptBnQw_DwLeToDwLe
#define XeCryptBnQw_DwLeToQwNe      XeCryptBnQw_DwLeToQwLe
#define XeCryptBnQw_DwBeToDwNe      XeCryptBnQw_DwBeToDwLe
#define XeCryptBnQw_DwBeToQwNe      XeCryptBnQw_DwBeToQwLe

#define XeCryptBnQw_QwLeToDwNe      XeCryptBnQw_QwLeToDwLe
#define XeCryptBnQw_QwLeToQwNe      XeCryptBnQw_QwLeToQwLe
#define XeCryptBnQw_QwBeToDwNe      XeCryptBnQw_QwBeToDwLe
#define XeCryptBnQw_QwBeToQwNe      XeCryptBnQw_QwBeToQwLe

#define XeCryptBnQw_DwNeToDwLe      XeCryptBnQw_DwLeToDwLe 
#define XeCryptBnQw_DwNeToDwBe      XeCryptBnQw_DwLeToDwBe 
#define XeCryptBnQw_DwNeToQwLe      XeCryptBnQw_DwLeToQwLe 
#define XeCryptBnQw_DwNeToQwBe      XeCryptBnQw_DwLeToQwBe 

#define XeCryptBnQw_QwNeToDwLe      XeCryptBnQw_QwLeToDwLe 
#define XeCryptBnQw_QwNeToDwBe      XeCryptBnQw_QwLeToDwBe 
#define XeCryptBnQw_QwNeToQwLe      XeCryptBnQw_QwLeToQwLe 
#define XeCryptBnQw_QwNeToQwBe      XeCryptBnQw_QwLeToQwBe 

#endif

// ---------------------------------------------------------------------------------------
// XeCryptBnQwNeCompare
//
// This function compares two multiple precision numbers in BnQwNe format and returns:
//
//    -1 if aqwA[] < aqwB[]
//     0 if aqwA[] = aqwB[]
//    +1 if aqwA[] > aqwB[]
// ---------------------------------------------------------------------------------------

int     XECRYPTAPI XeCryptBnQwNeCompare(const QWORD * pqwA, const QWORD * pqwB, DWORD cqw);

// ---------------------------------------------------------------------------------------
// XeCryptBnQwNeModInv
//
// This function computes the 2-adic inverse of a QWORD (mod 2^64).
// ---------------------------------------------------------------------------------------

QWORD   XECRYPTAPI XeCryptBnQwNeModInv(QWORD qw);

// ---------------------------------------------------------------------------------------
// XeCryptBnQwNeModMul
//
// This function performs Montgomery multiplication.
//
// All numbers must be in BnQwNe format and have cqw digits.
//
// The result of this function is:
//
//             aqwA[] * aqwB[]     
//    aqwC[] = --------------- MOD aqwM[]
//                2^(cqw*64)
// ---------------------------------------------------------------------------------------

void    XECRYPTAPI XeCryptBnQwNeModMul(const QWORD * pqwA, const QWORD * pqwB, QWORD * pqwC, QWORD qwMI, const QWORD * pqwM, DWORD cqw);

// ---------------------------------------------------------------------------------------
// XeCryptBnQwNeModExp
//
// This function performs modular exponentiation.
//
// All numbers must be in BnQwNe format and have cqw digits.
//
// The result of this function is:
//
//    aqwA[] = (aqwB[] ^ aqwC[]) MOD aqwM[]
//
// This function returns FALSE if there was not enough memory to allocate storage for
// intermediate results, or if one or more of the inputs is invalid (such as zero modulus),
// otherwise TRUE is returned.
// ---------------------------------------------------------------------------------------

BOOL    XECRYPTAPI XeCryptBnQwNeModExp(QWORD * pqwA, const QWORD * pqwB, const QWORD * pqwC, const QWORD * pqwM, DWORD cqw);

// ---------------------------------------------------------------------------------------
// XeCryptBnQwNeModExpRoot
//
// This function performs modular exponentiation to an exponent and modulus given by its
// prime factors and coefficients.  This is a support routine for exponentiating to a
// private RSA key.  It is more efficient than exponentiating to the private exponent
// directly, but the result is otherwise the same.
//
// All numbers must be in BnQwNe format.  The pqwA and pqwB numbers have cqw * 2 digits.
// All of the other numbers have cqw digits.
//
// The result of this function is:
//
//    aqwA[] = (aqwB[] ^ aqwC[]) MOD aqwM[]
//
// where aqwC[] and aqwM[] are implicitly provided by their constituent parts.
//
// This function returns FALSE if there was not enough memory to allocate storage for
// intermediate results, or if one or more of the inputs is invalid (such as a zero modulus),
// otherwise TRUE is returned.
// ---------------------------------------------------------------------------------------

BOOL    XECRYPTAPI XeCryptBnQwNeModExpRoot(QWORD * pqwA, const QWORD * pqwB, const QWORD * pqwPP, const QWORD * pqwQQ, const QWORD * pqwDP, const QWORD * pqwDQ, const QWORD * pqwCR, DWORD cqw);

// ---------------------------------------------------------------------------------------
// XeCryptBnQwNeRsaPubCrypt
// XeCryptBnQwNeRsaPrvCrypt
//
// These functions performs modular exponentiation of a message to the public or private
// exponent of the given RSA key.
//
// The aqwA[] parameter must be in BnQwNe format and have cqw digits.  It's value must
// be less than the modulus.
//
// The result of this function is:
//
//     aqwB[] = (aqwA[] ^ dwPubExp) MOD aqwM[]    (XeCryptBnQwNeRsaPubCrypt)
//     aqwB[] = (aqwA[] ^ aqwPrvExp[]) MOD aqwM[] (XeCryptBnQwNeRsaPrvCrypt)
// ---------------------------------------------------------------------------------------

typedef struct {
    DWORD           cqw;                // Number of QWORD digits in modulus
    DWORD           dwPubExp;           // Public exponent
    QWORD           qwReserved;         // Reserved (was qwMI)
//  QWORD           aqwM[cqw];          // [BnQwNe] Modulus
//  QWORD           aqwP[cqw/2];        // [BnQwNe] Private prime P
//  QWORD           aqwQ[cqw/2];        // [BnQwNe] Private prime Q
//  QWORD           aqwDP[cqw/2];       // [BnQwNe] Private exponent P
//  QWORD           aqwDQ[cqw/2];       // [BnQwNe] Private exponent Q
//  QWORD           aqwCR[cqw/2];       // [BnQwNe] Private coefficient
} XECRYPT_RSA;

typedef struct {
    XECRYPT_RSA     Rsa;                // Common header
    QWORD           aqwM[16];           // [BnQwNe] Modulus
} XECRYPT_RSAPUB_1024;

typedef struct {
    XECRYPT_RSA     Rsa;                // Common header
    QWORD           aqwM[24];           // [BnQwNe] Modulus
} XECRYPT_RSAPUB_1536;

typedef struct {
    XECRYPT_RSA     Rsa;                // Common header
    QWORD           aqwM[32];           // [BnQwNe] Modulus
} XECRYPT_RSAPUB_2048;

typedef struct {
    XECRYPT_RSA     Rsa;                // Common header
    QWORD           aqwM[64];           // [BnQwNe] Modulus
} XECRYPT_RSAPUB_4096;

typedef struct {
    XECRYPT_RSA     Rsa;                // Common header
    QWORD           aqwM[16];           // [BnQwNe] Modulus
    QWORD           aqwP[8];            // [BnQwNe] Private prime P
    QWORD           aqwQ[8];            // [BnQwNe] Private prime Q
    QWORD           aqwDP[8];           // [BnQwNe] Private exponent P
    QWORD           aqwDQ[8];           // [BnQwNe] Private exponent Q
    QWORD           aqwCR[8];           // [BnQwNe] Private coefficient
} XECRYPT_RSAPRV_1024;

typedef struct {
    XECRYPT_RSA     Rsa;                // Common header
    QWORD           aqwM[24];           // [BnQwNe] Modulus
    QWORD           aqwP[12];           // [BnQwNe] Private prime P
    QWORD           aqwQ[12];           // [BnQwNe] Private prime Q
    QWORD           aqwDP[12];          // [BnQwNe] Private exponent P
    QWORD           aqwDQ[12];          // [BnQwNe] Private exponent Q
    QWORD           aqwCR[12];          // [BnQwNe] Private coefficient
} XECRYPT_RSAPRV_1536;

typedef struct {
    XECRYPT_RSA     Rsa;                // Common header
    QWORD           aqwM[32];           // [BnQwNe] Modulus
    QWORD           aqwP[16];           // [BnQwNe] Private prime P
    QWORD           aqwQ[16];           // [BnQwNe] Private prime Q
    QWORD           aqwDP[16];          // [BnQwNe] Private exponent P
    QWORD           aqwDQ[16];          // [BnQwNe] Private exponent Q
    QWORD           aqwCR[16];          // [BnQwNe] Private coefficient
} XECRYPT_RSAPRV_2048;

typedef struct {
    XECRYPT_RSA     Rsa;                // Common header
    QWORD           aqwM[64];           // [BnQwNe] Modulus
    QWORD           aqwP[32];           // [BnQwNe] Private prime P
    QWORD           aqwQ[32];           // [BnQwNe] Private prime Q
    QWORD           aqwDP[32];          // [BnQwNe] Private exponent P
    QWORD           aqwDQ[32];          // [BnQwNe] Private exponent Q
    QWORD           aqwCR[32];          // [BnQwNe] Private coefficient
} XECRYPT_RSAPRV_4096;

BOOL  XECRYPTAPI XeCryptBnQwNeRsaPubCrypt(const QWORD * pqwA, QWORD * pqwB, const XECRYPT_RSA * pRsa);
BOOL  XECRYPTAPI XeCryptBnQwNeRsaPrvCrypt(const QWORD * pqwA, QWORD * pqwB, const XECRYPT_RSA * pRsa);

// ---------------------------------------------------------------------------------------
// XeCryptBnQwNeRsaKeyGen
//
// This function generates a random RSA key pair.
//
// The cbits parameter specifies the number of bits in the modulus.  It must be a multiple
// of 128, and must be between 512 and 4096.
//
// The dwPubExp parameter specifies the public exponent. 
//
// The pRsaPub and pRsaPrv parameters must point to XECRYPT_RSA structures that are large
// enough to hold the public and private keys requested.  The public key structure needs
// to be at least sizeof(XECRYPT_RSA) + (cbits / 8) bytes big.  The private key structure
// needs to be at least sizeof(XECRYPT_RSA) + (((cbits / 2) * 7) / 8) bytes big.
// ---------------------------------------------------------------------------------------

BOOL  XECRYPTAPI XeCryptBnQwNeRsaKeyGen(DWORD cbits, DWORD dwPubExp, XECRYPT_RSA * pRsaPub, XECRYPT_RSA * pRsaPrv);

// ---------------------------------------------------------------------------------------
// XeCryptBnQwBeSigFormat
// XeCryptBnQwBeSigCreate
// XeCryptBnQwBeSigVerify
//
// These functions format, create, and verify digital signatures using an RSA key pair.
//
// The size of the RSA key must be 2048 bits and the public exponent must be 3 or 65537.
// The size of a digital signature is 256 bytes.  The signature is represented as a bignum
// in BnQwBe format.  This allows for processing digital signatures on platforms with
// different byte orders.
//
// The XeCryptBnQwBeSigFormat function takes a 20 byte hash and a 10 byte fixed salt value
// and generates a digital signature using the PKCS #1 v2.1 RSASSA-PSS algorithm.  The
// hash function is SHA and the MGF function is RC4.  The resulting digital signature
// is stored in the XECRYPT_SIG structure.
//
// The XeCryptBnQwBeSigCreate function takes a 20 byte hash and a 10 byte fixed salt
// value, generates a digital signature, and then pre-compensates it by multiplying the
// signature by a scale factor derived from the modulus in the public key.  This
// pre-compensation is used to simplify verification later.
//
// The XeCryptQwBeSigVerify function takes an encrypted digital signature, a 20 byte hash
// a 10 byte fixed salt value, and an RSA public key.  It returns TRUE if the digital
// signature, when decrypted with the RSA public key, matches the result of formatting
// a digital signature with the 20 byte hash and 10 byte salt value, and FALSE otherwise.
// ---------------------------------------------------------------------------------------

typedef struct {                        // [BnQwBe]
    QWORD           aqwPad[28];         // Padding
    BYTE            bOne;               // 0x01
    BYTE            abSalt[10];         // Salt
    BYTE            abHash[20];         // Hash
    BYTE            bEnd;               // 0xBC
} XECRYPT_SIG;

void  XECRYPTAPI XeCryptBnQwBeSigFormat(XECRYPT_SIG * pSig, const BYTE * pbHash, const BYTE * pbSalt);
BOOL  XECRYPTAPI XeCryptBnQwBeSigCreate(XECRYPT_SIG * pSig, const BYTE * pbHash, const BYTE * pbSalt, const XECRYPT_RSA * pRsa);
BOOL  XECRYPTAPI XeCryptBnQwBeSigVerify(XECRYPT_SIG * pSig, const BYTE * pbHash, const BYTE * pbSalt, const XECRYPT_RSA * pRsa);

// ---------------------------------------------------------------------------------------
// XeCryptBnDwLePkcs1Format
// XeCryptBnDwLePkcs1Verify
//
// These functions format and verify a SHA digest in PKCS#1 format and BnDwLe bignum
// representation.  This format matches what was used on Xbox 1 and what is normally
// produced by nCipher devices.
//
// The pbHash argument specifies the digest to format or verify.
//
// When formatting, the dwType argument selects one of three encoding formats, as follows.
//
//   0: [HashReversed][140400051A02030E2B05060930213000][FF ... FF][0100]
//   1: [HashReversed][14041A02030E2B050607301F3000][FF ... FF][0100]
//  >1: [HashReversed][00][FF ... FF][0100]
//
// On Xbox 1, signatures would always be encoded using format 0, but any of these formats
// were accepted by the verification routine.  We follow the same rules when calling
// XeCryptBnDwLePkcs1Verify.
//
// The pbSig argument specifies the buffer to place the formatted signature, or the buffer
// containing the signature to verify.
//
// The cbSig argument specifies the size of the signature buffer.  It should be equal to
// the number of bytes in the RSA key modulus.  For example, if this siguature is used
// with an RSA key whose modulus is 1024 bits, you would specify 128 for this argument.
// ---------------------------------------------------------------------------------------

void  XECRYPTAPI XeCryptBnDwLePkcs1Format(const BYTE * pbHash, DWORD dwType, BYTE * pbSig, DWORD cbSig);
BOOL  XECRYPTAPI XeCryptBnDwLePkcs1Verify(const BYTE * pbHash, const BYTE * pbSig, DWORD cbSig);

// ---------------------------------------------------------------------------------------
// XeCryptBnDwLeDhModExp
//
// These functions perform Diffie-Hellman modular exponentiation.
//
// The inputs and outputs are in BnDwLe format for compatibility with legacy applications.
// Note, however, that the XECRYPT_DH structure is always BnQwNe format.
//
// The pDh argument can be NULL in any of these functions, in which case the standard
// 768-bit Oakley Group 1 constants will be used.
//
// The XeCryptBnDwLeDhModExp function performs modular exponentiation.  The pdwA argument
// specifies the base to be exponentiated.  If it is NULL, then the generator in the
// XECRYPT_DH structure is used as the base.
//
// The pdwB argument specifies the exponent.
//
// The result is stored in the pdwC argument.
//
//    aqwC[] = ((pqwA ? pqwA[] : pDh->aqwG[]) ^ aqwB[]) MOD pDh->aqwM[]
//
// The XeCryptBnDwLeDhInvalBase function returns TRUE if the pdwA argument is an invalid
// base for exponentiation.  A valid base is 1 < aqwA[] < (aqwM[]-1).
//
// The XeCryptBnDwLeDhEqualBase function returns TRUE if the pdwA argument is equal to
// the pDh->aqwG[].
// ---------------------------------------------------------------------------------------

typedef struct {
    DWORD           cqw;                // Number of QWORD digits in modulus
    DWORD           dwReserved;         // Reserved
//  QWORD           aqwM[cqw];          // [BnQwNe] Modulus
//  QWORD           aqwG[cqw];          // [BnQwNe] Generator
} XECRYPT_DH;

typedef struct {
    XECRYPT_DH      Dh;                 // Common header
    QWORD           aqwM[12];           // [BnQwNe] Modulus
    QWORD           aqwG[12];           // [BnQwNe] Generator
} XECRYPT_DH_768;

typedef struct {
    XECRYPT_DH      Dh;                 // Common header
    QWORD           aqwM[16];           // [BnQwNe] Modulus
    QWORD           aqwB[16];           // [BnQwNe] Generator
} XECRYPT_DH_1024;

BOOL    XECRYPTAPI XeCryptBnDwLeDhModExp(const DWORD * pdwA, const DWORD * pdwB, DWORD * pdwC, const XECRYPT_DH * pDh);
BOOL    XECRYPTAPI XeCryptBnDwLeDhInvalBase(const DWORD * pdwA, const XECRYPT_DH * pDh);
BOOL    XECRYPTAPI XeCryptBnDwLeDhEqualBase(const DWORD * pdwA, const XECRYPT_DH * pDh);

// ---------------------------------------------------------------------------------------
// XeCryptBnQwNeEcSigVerify
//
// This function uses eliptic curve exponentiation to verify a digital signature.
//
// The pEcPub argument specifies the public key to use when verifying the signature.
//
// The pbMsg argument is the same sequence of bytes that was used when the signature
// was generated.
//
// The cbMsg argument specifies the number of byte in pbMsg.
//
// The pbSig argument is the sequence of bytes that make up the signature.  The size of
// this signature is defined by the sum of the cbitR, cbitS, and cbitA fields of the
// public key, rounded up to the next byte.
//
// If the public key fails to verify the supplied signature, FALSE is returned.  If the
// public key successfully verifies the signature, then the sequence number that was
// encoded in the signature is returned in the pqwSeq out argument.  The number of bits
// in the sequence number is given by the cbitN field of the public key.
// ---------------------------------------------------------------------------------------

typedef struct {
    DWORD           cqw;                // Number of QWORD digits in modulus
    BYTE            cbitR;              // This many bits of signature form R
    BYTE            cbitS;              // This many bits of signature form S (after R)
    BYTE            cbitA;              // This many bits of signature form A (after S)
    BYTE            cbitN;              // This many bits of sequence number are returned
//  QWORD           aqwM[cqw];          // [BnQwNe] Modulus
//  QWORD           aqwC[cqw*2];        // [BnQwNe] Curve
//  QWORD           aqwG[cqw*2];        // [BnQwNe] Generator
//  QWORD           aqwGX[cqw*2];       // [BnQwNe] Generator ^ X (private exponent)
} XECRYPT_ECPUB;

typedef struct {
    XECRYPT_ECPUB   EcPub;              // Common header
    QWORD           aqwM[8];            // [BnQwNe] Modulus
    QWORD           aqwC[16];           // [BnQwNe] Curve
    QWORD           aqwG[16];           // [BnQwNe] Generator
    QWORD           aqwGP[16];          // [BnQwNe] Generator ^ X (private exponent)
} XECRYPT_ECPUB_512;

BOOL    XECRYPTAPI XeCryptBnQwNeEcSigVerify(const XECRYPT_ECPUB * pEcPub, const BYTE * pbMsg, DWORD cbMsg, const BYTE * pbSig, QWORD * pqwSeq);

// ---------------------------------------------------------------------------------------
// XeCryptRandom
//
// This function generates a series of cryptographically strong random bits.
// ---------------------------------------------------------------------------------------

void    XECRYPTAPI XeCryptRandom(BYTE * pb, DWORD cb);

// ---------------------------------------------------------------------------------------
// Parve Cipher
//
// These functions implement symmetric encryption and CBC MAC generation using the Parve
// cipher.  There is no support for symmetric decryption.
//
// The Parve block size is 8 bytes and the key size is 8 bytes.
//
// XeCryptParveEcb encrypts a single Parve block with the given key and the given Sbox.
// The pbKey parameter points to an 8 byte key.  The pbSbox parameter points to a 256 
// "private key" array.  The pbInp parameter points to the 8 bytes to be encrypted.  The
// pbOut parameter points to a location to store the encrypted 8 bytes.  The pbInp and
// pbOut parameters can point to the same location.
//
// XeCryptParveCbcMac computes an 8 byte MAC from a contiguous series of Parve blocks
// using cipher block chaining.  The pbKey parameter specifies the key to use.  The
// pbSbox parameter points to a 256 "private key" array.  The pbIv argument specifies the
// 8 byte initialization vector to use.  The pbOut parameter specifies the location to
// store the 8 byte MAC result.
// ---------------------------------------------------------------------------------------

#define XECRYPT_PARVE_BLOCK_SIZE    (8)
#define XECRYPT_PARVE_KEY_SIZE      (8)
#define XECRYPT_PARVE_SBOX_SIZE     (256)
#define XECRYPT_PARVE_MAC_SIZE      (8)

void    XECRYPTAPI XeCryptParveEcb(const BYTE * pbKey, const BYTE * pbSbox, const BYTE * pbInp, BYTE * pbOut);
void    XECRYPTAPI XeCryptParveCbcMac(const BYTE * pbKey, const BYTE * pbSbox, const BYTE * pbIv, const BYTE * pbInp, DWORD cbInp, BYTE * pbOut);

// ---------------------------------------------------------------------------------------
// XeCryptChainAndSumMac
//
// This function implements the Chain & Sum MAC algorithm.
//
// The pdwCD parameter points to a pair of DWORD values that will be used as the C and D
// constants of the algorithm.
//
// The pdwAB parameter points to a pair of DWORD values that will be used as the A and B
// constants of the algorithm.
//
// The pdwInp parameter points to a series of DWORD values to be consumed as input to
// the algorithm.  The cdwInp parameter specifies the number of DWORD values in this
// array.  It must be a multiple of two, as the input is consumed in pairs.  If it is
// an odd number, it will be truncated.
//
// The pdwOut parameter points to a location in which a pair of DWORD results are stored.
// ---------------------------------------------------------------------------------------

void    XECRYPTAPI XeCryptChainAndSumMac(const DWORD * pdwCD, const DWORD * pdwAB, const DWORD * pdwInp, DWORD cdwInp, DWORD * pdwOut);

#ifdef __cplusplus
};
#endif

#endif
