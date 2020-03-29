// 
// This enables use of the XeCrypt functions as used in the Xbox360 kernel.
// This consists of all of the kernel exports from 345 to 402.
// 
// Using this header in your Xbox360 source code allows you to import
// access to these various functions from the Xbox360 kernel.
// This means you can call these functions in your source code
// without needing to link any extra libraries.
// 
// Using this header in your PC source code allows you to import
// access to these various functions from the XeCrypt library.
// This means you can call these functions in your source code
// by just linking in the XeCrypt library.
// 
// Note: "_XBOX" should be defined in order to use these on the Xbox360.
// An Xbox360 project created in Visual Studio defines this by default for you.
// Leave it undefined to use them on the pc.
// 
// xorloser - july 2006
// 
// ====================================================================
// 
//	"This product includes software developed by the OpenSSL Project
//	for use in the OpenSSL Toolkit. (http://www.openssl.org/)"
// 
//	"This product includes cryptographic software written by
//	Eric Young (eay@cryptsoft.com)"
// 
// ====================================================================
// 


// uncomment this for use in Xbox360 projects
// (not required if used in an Xbox360 project created in Visual Studio)
//#define _XBOX

// uncomment this to compile for big endian systems eg xbox360 and macs
//#define _XE_CRYPT_BIG_ENDIAN

// if compiling for the xbox360, big endian should be defined
#ifdef _XBOX
#ifndef _XE_CRYPT_BIG_ENDIAN
#define _XE_CRYPT_BIG_ENDIAN
#endif // _XE_CRYPT_BIG_ENDIAN
#endif // _XBOX

#include "types.h"
#include "KernelDefines.h"

#ifndef _XE_CRYPT_H_
#define _XE_CRYPT_H_
#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern "C" {
#endif

// flags to signify encryption or decryption
enum XeCryptFlag {
	XE_CRYPT_DEC = 0,
	XE_CRYPT_ENC = 1
};

// sizes of blocks and hashes
#define XE_CRYPT_MD5_HASH_SIZE		 16
#define XE_CRYPT_SHA_HASH_SIZE		 20
#define XE_CRYPT_AES_BLOCK_SIZE		 16
#define XE_CRYPT_DES_BLOCK_SIZE		  8
#define XE_CRYPT_RC4_KEY_SIZE		256
#define XE_CRYPT_HMAC_KEY_SIZE		 64


// 
// xbox360 specific type defs
// 
#ifdef _XBOX

typedef struct {
	u32 keys[88];		// not sure about the layout, but size is right
} XeAesContext;

typedef struct {
	u32 keys[16][2];	// not sure about the layout, but size is right
} XeDesContext;

typedef struct {
	XeDesContext ctx[3];// the 3 contexts required for triple-des crypting
} XeDes3Context;

typedef struct {
	u32 i[2];			// number of _bits_ handled mod 2^64
	u32 buf[4];			// scratch buffer
	u8  in[64];			// input buffer
	u8  digest[16];		// actual digest after MD5Final call
	u32 FinishFlag;
} XeMd5Context;

typedef struct {
	u8 m[256];			// state table
	u8 x;				// index into table
	u8 y;				// index into table
} XeRc4Context;

typedef struct {
	u32 FinishFlag;
	u8  HashVal[20];
	u32 state[5];		// state (ABCDE)
	u32 count[2];		// number of bytes, msb first
	u8  buffer[64];		// input buffer
} XeShaContext;

typedef struct {
	XeShaContext ctx[2];
} XeHmacShaContext;

typedef struct {
	XeMd5Context ctx[2];
} XeHmacMd5Context;

#endif // _XBOX


// 
// pc specific type defs
// 
#ifndef _XBOX

typedef struct {
	u32 erk[4 * (14+1)];// encryption round keys
	s32 enr;			// number of encryption rounds
	u32 drk[4 * (14+1)];// decryption round keys
	s32 dnr;			// number of decryption rounds
} XeAesContext;

typedef struct {
	union
	{
	u8 cblock[8];
	u32 deslong[2];
	} ks[16];
} XeDesContext;

typedef struct {
	XeDesContext ctx[3];// the 3 contexts required for triple-des crypting
} XeDes3Context;

typedef struct {
	u32 A,B,C,D;
	u32 Nl,Nh;
	u32 data[16];
	u32 num;
} XeMd5Context;

typedef struct {
	u32 x,y;
	u32 data[256];
} XeRc4Context;

typedef struct {
	u32 h0,h1,h2,h3,h4;
	u32 Nl,Nh;
	u32 data[16];
	u32 num;
} XeShaContext;

typedef struct {
	XeShaContext ctx[2];
} XeHmacShaContext;

typedef struct {
	XeMd5Context ctx[2];
} XeHmacMd5Context;

#endif // undef(_XBOX)

// rsa key
typedef struct {
	s32	modulusSize;		// size of modulus in 8byte units
	s32	exponent;			// public key exponent
	u32 res[2];				// 0 (padding)
	u64	modulus[0x20];		// Big endian style
	u8	privateData[640];	// Private Key
} XeRsaKey;



// 
//  A E S    F U N C T I O N S 
// 

// export 345
// sets up the aes context with expanded forms of the key
// 
// args:	context for aes crypting
//			128bit key to expand for use with future crypting
void XeCryptAesKey(XeAesContext* ctx, const u8* key);

// export 346
// aes crypt performed using "Electronic Code Book"
// this independently crypts a single 128 bit block.
// 
// args:	context for aes crypting
//			input data to be crypted (128bits)
//			output to store crypted data into (128bits)
//			flag for whether to encrypt or decrypt (XE_CRYPT_???)
void XeCryptAesEcb(const XeAesContext* ctx, const u8* input, u8* output, XeCryptFlag encFlag);

// export 347
// aes crypt performed using "Cipher Block Chaining".
// this chains together successive crypt blocks for a more secure result.
// ivec is a 128 bit initialisation vector for the chaining, this
// gets updated to the next initialisation vector before returning.
// 
// args:	context for aes crypting
//			input data to be crypted
//			length of input data to be crypted in bytes
//			output to store crypted data into
//			128bit initialisation vector
//			flag for whether to encrypt or decrypt (XE_CRYPT_???)
void XeCryptAesCbc(const XeAesContext* ctx, const u8* input, s32 size, u8* output, u8* ivec, XeCryptFlag encFlag);




// 
//  B N    F U N C T I O N S 
// 


// export 348
// checks if big number has an equal base
// 
// args:	big number to check
//			table of data
// retruns:	TRUE if equal base
//			FALSE if base isnt equal
bool XeCryptBnDwLeDhEqualBase(const u64* bigNum, const u64* table);

// export 349
// checks if big number has an invalid base
// 
// args:	big number to check
//			table of data
// retruns:	TRUE if an invalid base
//			FALSE if base is valid
bool XeCryptBnDwLeDhInvalBase(const u64* bigNum, const u64* table);

// export 350
// ??
// 
// args:	big number to get mod-exp of (optional, can be null)
//			exponent (in big number format)
//			ouput for result of mod-exp (in big number format)
//			table of data
// returns:	TRUE if successful
//			FALSE if error
bool XeCryptBnDwLeDhModExp(const u64* bigNumInput, const u64* bnExponent, u64* bigNumOutput, const u64* table);

// export 351
// copies u32 blocks of data between buffers
// 
// args:	source of data
//			destination for data
//			size of data in u32 blocks
void XeCryptBnDw_Copy(const u32* input, u32* output, s32 size);

// export 352
// swaps endian of data in u32 blocks
// 
// args:	source of data to swap
//			destination for swapped data
//			number of u32 blocks to swap
void XeCryptBnDw_SwapLeBe(const u32* input, u32* output, s32 size);

// export 353
// zeros data in u32 blocks
// 
// args:	data to zero
//			number of u32 blocks to zero
void XeCryptBnDw_Zero(u32* data, s32 size);

// export 354
// formats a buffer with PKCS1 for signing sha digests
// 
// args:	input digest to apply format to
//			some kind of format flag
//			output for formatted data
//			size of output data (max 512 bytes)
void XeCryptBnDwLePkcs1Format(const u8* digest, s32 flag, u8* output, s32 size);

// export 355
// verifies the PKCS1 signing of an sha digest
// 
// args:	digest to verify
//			signature of digest
//			size of digest signature to verify
// returns:	TRUE if successfully verified
//			FALSE if error verifying
bool XeCryptBnDwLePkcs1Verify(const u8* hash, const u8* sig, s32 size);

// export 356
// returns:	TRUE if successful
//			FALSE if error
bool XeCryptBnQwBeSigCreate(u64* output, const u8* hash, const u8* salt, const XeRsaKey* key);

// export 357
void XeCryptBnQwBeSigFormat(u8* output, const u8* hash, const u8* salt);

// export 358
// returns:	TRUE if successful
//			FALSE if error
bool XeCryptBnQwBeSigVerify(u64* sig, const u8* hash, const u8* salt, const XeRsaKey* key);

// export 359
// 
// args:	big number output for result of mod-exp
//			big number input to get mod-exp of
//			big number of exponent
//			big number of modulus
//			size of big number buffers (in u64 units)
// returns:	TRUE if successful
//			FALSE if error
bool XeCryptBnQwNeModExp(u64* bnOutput, const u64* bnInput, const u64* bnExponent, const u64* bnModulus, s32 size);

// export 360
// (basically encrypts data with parts of the rsa private key)
// 
// args:	output data (encrypted data)
//			input data  (unencrypted data)
//			private key - P
//			private key - Q
//			private key - DP
//			private key - DQ
//			private key - CR (chinese remainder)
//			size
// returns:	TRUE if successful
//			FALSE if error
bool XeCryptBnQwNeModExpRoot(u64* bnOutput, const u64* bnInput, const u64* P, const u64* Q, const u64* DP, const u64* DQ, const u64* CR, s32 size);

// export 361
// ??
// 
// args:	number to calculate mod inverse of ?
// returns:	calculated value
u64 XeCryptBnQwNeModInv(u64 num);

// export 362
void XeCryptBnQwNeModMul(const u64* bnNum1, const u64* bnNum2, u64* bnOutput, u64 mod_inv, const u64* bnModulus, s32 bigNumSize);

// export 363
// THIS HAS NOT BEEN REVERSED YET!
// 
// returns:	TRUE if successful
//			FALSE if error
bool XeCryptBnQwNeRsaKeyGen(s32 arg0, u32 arg1, u8* arg2, u8* arg3);

// export 364
// ??
// 
// returns:	TRUE if successful
//			FALSE if error
bool XeCryptBnQwNeRsaPrvCrypt(const u64* input, u64* output, const XeRsaKey* key);

// export 365
// crypt data with public key
// 
// args:	input data to crypt 
//			ouput for crypted data
//			public key to crypt with
// returns:	TRUE if successful
//			FALSE if error
bool XeCryptBnQwNeRsaPubCrypt(const u64* input, u64* output, const XeRsaKey* key);

// export 366
// copy data between buffers
// 
// args:	source of data
//			destination for data
//			number of u64 blocks to copy
void XeCryptBnQw_Copy(const u64* input, u64* output, s32 size);

// export 367
// swap u32 blocks around inside of u64 blocks
// 
// args:	input buffer of u32 blocks to swap
//			ouput buffer for swapped u32 blocks
//			number of u32 blocks
void XeCryptBnQw_SwapDwQw(const u64* input, u64* output, s32 size);

// export 368
// swap endian on u64 blocks
// 
// args:	input buffer of u64 blocks to swap
//			ouput buffer for swapped u64 blocks
//			number of u64 blocks
void XeCryptBnQw_SwapDwQwLeBe(const u64* input, u64* output, s32 size);

// export 369
// swap endian on u64 blocks
// 
// args:	input buffer of u64 blocks to swap
//			ouput buffer for swapped u64 blocks
//			number of u64 blocks
void XeCryptBnQw_SwapLeBe(const u64* input, u64* output, s32 size);

// export 370
// zeros memory
// 
// args:	buffer to zero
//			size of buffer to zero (in u64 blocks)
void XeCryptBnQw_Zero(u64* buffer, s32 size);




// export 371
// 
// args:	table1 (2 * 32 bit blocks)
//			table2 (2 * 32 bit blocks)
//			input data
//			size of input data in 32bit blocks
//			output for mac result (2 * 32 bit blocks)
void XeCryptChainAndSumMac(const u32* table1, const u32* table2, const u32* input, s32 inputSize, u32* output);




// 
//  D E S    F U N C T I O N S 
// 


// export 372
// alters the DES parity of data to make it have an odd parity.
// the output buffer can be the same as the input buffer.
// (this is usually used on a 64 bit key)
// 
// args:	input data to alter parity of
//			length of data to alter in bytes
//			output for data with altered parity
void XeCryptDesParity(const u8* input, s32 len, u8* output);

// export 373
// sets up the des context with expanded forms of the key
// 
// args:	context for des crypting
//			64bit key to expand for use with future crypting
void XeCryptDesKey(XeDesContext* ctx, const u8* key);

// export 374
// des crypt performed using "Electronic Code Book"
// this independently crypts a single 64 bit block.
// 
// args:	context for des crypting
//			input data to be crypted
//			output to store crypted data into
//			flag for whether to encrypt or decrypt (XE_CRYPT_???)
void XeCryptDesEcb(const XeDesContext* ctx, const u8* input, u8* output, XeCryptFlag encFlag);

// export 375
// des crypt performed using "Cipher Block Chaining".
// this chains together successive crypt blocks for a more secure result.
// ivec is a 64 bit initialisation vector for the chaining, this
// gets updated to the next initialisation vector before returning.
// 
// args:	context for des crypting
//			input data to be crypted
//			length of input data to be crypted in bytes
//			output to store crypted data into
//			64bit initialisation vector
//			flag for whether to encrypt or decrypt (XE_CRYPT_???)
void XeCryptDesCbc(const XeDesContext* ctx, const u8* input, s32 size, u8* output, u8* ivec, XeCryptFlag encFlag);

// export 376
// sets up the triple-des context with expanded forms of the key
// 
// args:	context for triple-des crypting
//			3 64bit keys to expand for use with future crypting
void XeCryptDes3Key(XeDes3Context* ctx, const u8* key);

// export 377
// triple-des crypt performed using "Electronic Code Book".
// this independently crypts a single 64 bit block.
// 
// args:	context for triple-des crypting
//			input data to be crypted
//			output to store crypted data into
//			flag for whether to encrypt or decrypt (XE_CRYPT_???)
void XeCryptDes3Ecb(const XeDes3Context* ctx, const u8* input, u8* output, XeCryptFlag encFlag);

// export 378
// triple-des crypt performed using "Cipher Block Chaining".
// this chains together successive crypt blocks for a more secure result.
// ivec is a 64 bit initialisation vector for the chaining, this
// gets updated to the next initialisation vector before returning.
// 
// args:	context for triple-des crypting
//			input data to be crypted
//			length of input data to be crypted in bytes
//			output to store crypted data into
//			64bit initialisation vector
//			flag for whether to encrypt or decrypt (XE_CRYPT_???)
void XeCryptDes3Cbc(XeDes3Context* ctx, const u8* input, s32 size, u8* output, u8* ivec, XeCryptFlag encFlag);




// 
//  H M A C - M D 5    F U N C T I O N S 
// 


// export 379
// sets up the md5 hmac context with the given key
// 
// args:	context for hmac-md5 crypting
//			variable length key used for crypting
//			size of key in bytes (max-length 64 bytes)
void XeCryptHmacMd5Init(XeHmacMd5Context* ctx, const u8* key, s32 keySize);

// export 380
// perform a hash over a variable block of data
// this hash is combined with the previously calculated hashes in the context
// 
// args:	context for hmac-md5 crypting
//			input data to hash over
//			size of input data in bytes
void XeCryptHmacMd5Update(XeHmacMd5Context* ctx, const u8* input, s32 inputSize);

// export 381
// gets the resultant hmac-md5 hash over all the previous data blocks inputted
// 
// args:	context for hmac-md5 crypting
//			buffer to get hash into
//			size of hash data to retrieve in bytes
void XeCryptHmacMd5Final(XeHmacMd5Context* ctx, u8* digest, s32 digestSize);

// export 382
// compute a hmac-md5 over given data using a given key
// designating an input size of 0 means that that particular
// input data block will be skipped.
// 
// args:	variable length key used for crypting
//			size of key in bytes (max-length 64 bytes)
//			input data 1 for hashing over
//			size of input data 1 in bytes
//			input data 2 for hashing over
//			size of input data 2 in bytes
//			input data 3 for hashing over
//			size of input data 3 in bytes
//			buffer to output computed hash to
//			size of hash to output in bytes
void XeCryptHmacMd5(
		const u8* key, s32 keySize,
		const u8* input1, s32 input1Size,
		const u8* input2, s32 input2Size,
		const u8* input3, s32 input3Size,
		u8* digest, s32 digestSize);




// 
//  H M A C - S H A 1    F U N C T I O N S 
// 


// export 383
// sets up the sha1 hmac context with the given key
// 
// args:	context for hmac-sha1 crypting
//			variable length key used for crypting
//			size of key in bytes (max-length 64 bytes)
void XeCryptHmacShaInit(XeHmacShaContext* ctx, const u8* key, s32 keySize);

// export 384
// perform a hash over a variable block of data
// this hash is combined with the previously calculated hashes in the context
// 
// args:	context for hmac-sha1 crypting
//			input data to hash over
//			size of input data in bytes
void XeCryptHmacShaUpdate(XeHmacShaContext* ctx, const u8* input, s32 inputSize);

// export 385
// gets the resultant hmac-sha1 hash over all the previous data blocks inputted
// 
// args:	context for hmac-sha1 crypting
//			buffer to get hash into
//			size of hash data to retrieve in bytes
void XeCryptHmacShaFinal(XeHmacShaContext* ctx, u8* digest, s32 digestSize);

// export 386
// compute a hmac-sha1 over given data using a given key
// designating an input size of 0 means that that particular
// input data block will be skipped.
// 
// args:	variable length key used for crypting
//			size of key in bytes (max-length 64 bytes)
//			input data 1 for hashing over
//			size of input data 1 in bytes
//			input data 2 for hashing over
//			size of input data 2 in bytes
//			input data 3 for hashing over
//			size of input data 3 in bytes
//			buffer to output computed hash to
//			size of hash to output in bytes
void XeCryptHmacSha(
		const u8* key, s32 keySize,
		const u8* input1, s32 input1Size,
		const u8* input2, s32 input2Size,
		const u8* input3, s32 input3Size,
		u8* digest, s32 digestSize);

// export 387
// computes a hmac-sha1 over given data using a given key
// and the compares the resultant hash to the given hash.
// the function then returns the result of the comparison.
// designating an input size of 0 means that that particular
// input data block will be skipped.
// the hash size compare against should be 20 bytes.
// 
// args:	variable length key used for crypting
//			size of key in bytes (max-length 64 bytes)
//			input data 1 for hashing over
//			size of input data 1 in bytes
//			input data 2 for hashing over
//			size of input data 2 in bytes
//			input data 3 for hashing over
//			size of input data 3 in bytes
//			pre-existing hash to compare against
//			size of hash to compare against in bytes
// returns:	TRUE if sucessfully verified
//			FALSE if error verifying
bool XeCryptHmacShaVerify(
		const u8* key, s32 keySize,
		const u8* input1, s32 input1Size,
		const u8* input2, s32 input2Size,
		const u8* input3, s32 input3Size,
		const u8* digest, s32 digestSize);




// 
//  M D 5    F U N C T I O N S 
// 


// export 388
// sets up the md5 context to prepare it for use
// 
// args:	context for md5 hashing
void XeCryptMd5Init(XeMd5Context* ctx);

// export 389
// perform a hash over a variable block of data
// this hash is combined with the previously calculated hashes in the context
// 
// args:	context for md5 hashing
//			input data to be hashed
//			size of data to perform hash over in bytes
void XeCryptMd5Update(XeMd5Context* ctx, const u8* input, s32 inputSize);

// export 390
// gets the resultant md5 hash over all the previous data blocks inputted
// 
// args:	context for md5 hashing
//			buffer to get hash into
//			size of hash data to retrieve in bytes
void XeCryptMd5Final(XeMd5Context* ctx, u8* digest, s32 digestSize);

// export 391
// perform md5 over up to 3 buffers and returns the result
// the buffers are optional, use a size of 0 to not use that buffer
// 
// args:	input buffer 1
//			size of input buffer 1 in bytes
//			input buffer 2
//			size of input buffer 2 in bytes
//			input buffer 3
//			size of input buffer 3 in bytes
//			buffer to get hash into
//			size of hash data to retrieve in bytes
void XeCryptMd5(const u8* buff1, s32 buff1Size,
				const u8* buff2, s32 buff2Size,
				const u8* buff3, s32 buff3Size,
				u8* digest, s32 digestSize);




// export 392
// 
// args:	some kind of table? (8 bytes of data)
//			some kind of table? (8 bytes of data)
//			8 bytes of input data
//			buffer to output 8 bytes of result data into
void XeCryptParveEcb(const u8* data1, const u8* data2, const u8* input, u8* output);

// export 393
// 
// args:	some kind of table?
//			some kind of table?
//			initialisation vector (8 bytes of data)
//			input data to calculate parve over
//			size of input data in bytes
//			buffer to output 8 bytes of result data into
void XeCryptParveCbcMac(const u8* table1, const u8* table2, const u8* ivec, const u8* data, s32 size, u8* output);

// export 394
// generate random data
// 
// args:	buffer to load generated data into
//			size of random data to get in bytes
void XeCryptRandom(u8* data, s32 dataSize);




// 
//  R C 4    F U N C T I O N S 
// 


// export 395
// sets up the rc4 context with the key data
// 
// args:	context for rc4 crypting
//			rc4 key
//			size of rc4 key in bytes
void XeCryptRc4Key(XeRc4Context* ctx, const u8* key, s32 keySize);

// export 396
// rc4 encrypts data with previously setup context
// 
// args:	context for rc4 crypting
//			data to be crypted
//			size of data to be crypted in bytes
void XeCryptRc4Ecb(XeRc4Context* ctx, u8* data, s32 dataSize);

// export 397
// rc4 encrypts data with given key
// 
// args:	rc4 key to crypt data with
//			size of key in bytes
//			data to be crypted
//			size of data to be crypted in bytes
void XeCryptRc4(const u8* key, s32 keySize, u8* data, s32 dataSize);




// 
//  S H A 1    F U N C T I O N S 
// 


// export 398
void XeCryptRotSumSha(const u8* input1, s32 input1Size,
					  const u8* input2, s32 input2Size,
					  u8* digest, s32 digestSize);

// export 399
// sets up the sha context to prepare it for use
// 
// args:	context for sha hashing
void XeCryptShaInit(XeShaContext* ctx);

// export 400
// perform a hash over a variable block of data
// this hash is combined with the previously calculated hashes in the context
// 
// args:	context for sha hashing
//			input data to be hashed
//			size of data to perform hash over in bytes
void XeCryptShaUpdate(XeShaContext* ctx, const u8* input, s32 inputSize);

// export 401
// gets the resultant sha hash over all the previous data blocks inputted
// 
// args:	context for sha hashing
//			buffer to get hash into
//			size of hash data to retrieve in bytes
void XeCryptShaFinal(XeShaContext* ctx, u8* digest, s32 digestSize);

// export 402
// perform sha1 over up to 3 buffers and returns the result
// the buffers are optional, use a size of 0 to not use that buffer
// 
// args:	input buffer 1
//			size of input buffer 1 in bytes
//			input buffer 2
//			size of input buffer 2 in bytes
//			input buffer 3
//			size of input buffer 3 in bytes
//			buffer to get hash into
//			size of hash data to retrieve in bytes
void XeCryptSha(const u8* buff1, s32 buff1Size,
				const u8* buff2, s32 buff2Size,
				const u8* buff3, s32 buff3Size,
				u8* digest, s32 digestSize);


#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif
#endif // _XE_CRYPT_H_

