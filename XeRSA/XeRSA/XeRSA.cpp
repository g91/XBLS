#include "stdafx.h"

//typedef union _SECENG_FAULT_ISOLATION {
//	QWORD AsULONGLONG; // 0x0 sz:0x8
//	struct {
//		QWORD IntegrityViolation : 1; // 0x0 bfo:0x63
//		QWORD Reserved1 : 63; // 0x0 bfo:0x0
//	}AsBits;
//} SECENG_FAULT_ISOLATION, *PSECENG_FAULT_ISOLATION;

CONST BYTE ChalKey[] = {
	0x00, 0x00, 0x00, 0x10, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x04, 0xD0, 0x55, 0x50, 0x79, 0x19, 0x95, 0x27,
	0x78, 0x89, 0x97, 0x08, 0xDE, 0x24, 0xD1, 0xED, 0xB1, 0xEA, 0xE5, 0x48,
	0xAC, 0x1A, 0xC3, 0xC8, 0x29, 0x45, 0xB0, 0x16, 0x9B, 0xEF, 0x78, 0x8F,
	0xEF, 0x26, 0x9D, 0x54, 0x59, 0x95, 0x2D, 0x25, 0xA5, 0xAC, 0xA3, 0xA6,
	0x94, 0x45, 0xE5, 0x42, 0x2E, 0x39, 0x88, 0x0C, 0x3C, 0xAE, 0xEB, 0xFD,
	0x53, 0x3A, 0xE9, 0x70, 0x43, 0xEA, 0xD1, 0xD1, 0x78, 0xCE, 0xED, 0x1C,
	0xE5, 0xFD, 0x0F, 0x80, 0x94, 0x6F, 0x4F, 0xFF, 0xAD, 0x45, 0x88, 0xCF,
	0x22, 0x4C, 0x56, 0xDE, 0x03, 0xE2, 0x46, 0x2F, 0x19, 0xB8, 0x2C, 0xD0,
	0xD7, 0xE9, 0x64, 0xB2, 0x68, 0x0C, 0x40, 0xF5, 0x4F, 0xDA, 0x80, 0x8F,
	0x71, 0xA9, 0x64, 0xA4, 0x15, 0x53, 0x6E, 0x2B, 0x49, 0x44, 0x55, 0xCB,
	0x05, 0x17, 0x3F, 0x66, 0xE1, 0x32, 0x2F, 0x1D, 0xE9, 0x2A, 0xD6, 0x4B
};


#define ROTL64(data, bits) ((data << (bits & 0x3F)) | data >> 64-(bits & 0x3F))
#define ROTR64(data, bits) ((data >> (bits & 0x3F)) | data << 64-(bits & 0x3F))
#define ROTL16(data, bits) ((((data & 0xFFFF) << (bits & 0xF)) | (data & 0xFFFF) >> 16-(bits & 0xF)) & 0xFFFF)
#define ROTR16(data, bits) ((((data & 0xFFFF) >> (bits & 0xF)) | (data & 0xFFFF) << 16-(bits & 0xF)) & 0xFFFF)
#define ROTL8(data, bits) ((((data & 0xFF) << (bits & 7)) | (data & 0xFF) >> 16-(bits & 7)) & 0xFF)
#define ROTR8(data, bits) ((((data & 0xFF) >> (bits & 7)) | (data & 0xFF) << 16-(bits & 7)) & 0xFF)

#define CRC_TYPE_IBM		0
#define CRC_TYPE_CCITT		1
// TODO: figure out if the normal polynomials are being used or if theyre derived from keys?
#define POLYNOMIAL_IBM		0xAAAA
#define POLYNOMIAL_CCITT	0
// TODO: figure out if normal seeds are being used or if theyre derived from keys?
#define CRC_IBM_SEED		0xFFFF
#define CRC_CCITT_SEED		0


void RadioComputeWhitening_IBM(PBYTE pbBuf, DWORD cbBuf) {
	BYTE WhiteningKeyMSB = 1;
	BYTE WhiteningKeyLSB = 0xFF;
	BYTE WhiteningKeyMSBPrevious = 0;

	for (int i = 0; i < cbBuf; i++)
	{
		pbBuf[i] ^= WhiteningKeyLSB;

		for (int j = 0; j < 8; j++)
		{
			WhiteningKeyMSBPrevious = WhiteningKeyMSB;
			WhiteningKeyMSB = (WhiteningKeyLSB & 1) ^ ((WhiteningKeyLSB >> 5) & 1);
			WhiteningKeyLSB = ((WhiteningKeyLSB >> 1) & 0xFF) | ((WhiteningKeyMSBPrevious << 7) & 0x80);
		}
	}
}


WORD ComputeCRC(WORD wCRC, BYTE bData, WORD wPoly) {
	for (int i = 0; i < 8; i++)
	{
		wCRC ^= bData;
		if (wCRC & 0x8000)
		{
			wCRC <<= 1;
			wCRC ^= wPoly;
		}
		else
			wCRC <<= 1;
	}

	return wCRC;
}

WORD RadioComputeCRC(PBYTE pbBuf, DWORD cbBuf, DWORD crcType = NULL) {
	WORD wPoly = 0;
	WORD wCRC = 0;
	if (crcType == CRC_TYPE_IBM) {
		wPoly = POLYNOMIAL_IBM;
		wCRC = CRC_IBM_SEED;
	}
	else
	{
		wPoly = POLYNOMIAL_CCITT;
		wCRC = CRC_CCITT_SEED;
	}

	for (int i = 0; i < cbBuf; i++)
		wCRC = ComputeCRC(wCRC, pbBuf[i], wPoly);

	if (crcType != CRC_TYPE_IBM)
		wCRC = (~wCRC) & 0xFFFF;

	return wCRC;
}

int crc16(PBYTE addr, int num, int crc) {

	for (int i = 0; i < num; i++)               /* Step through bytes in memory */
	{
		crc = crc ^ (addr[i] << 8);      /* Fetch byte from memory, XOR into CRC top byte*/
		for (int j = 0; j<8; j++)              /* Prepare to rotate 8 bits */
		{
			crc = crc << 1;                /* rotate */
			if (crc & 0x10000)             /* bit 15 was set (now bit 16)... */
				crc = (crc ^ POLYNOMIAL_IBM) & 0xFFFF; /* XOR with XMODEM polynomic */
													   /* and ensure CRC remains 16-bit value */
		}                              /* Loop for 8 bits */
	}                                /* Loop until num=0 */
	return(crc);                     /* Return updated CRC */
}

// assumes Buffer is 128 bytes in length
#define SoCHash SoCHashBy16

// SoC Hashing words (no key)
WORD SoCHashBy16(PVOID Buffer) {
	WORD wHash = 0;
	BYTE rotl = 15;
	for (int i = 0; i < 16; i++) {
		QWORD qwData = ROTR64(((QWORD*)Buffer)[i], i + 1);
		//QWORD qwData = ROTL64(((QWORD*)Buffer)[i], rotl);
		for (int j = 0; j < 4; j++)
			wHash ^= ((PWORD)&qwData)[j];
		rotl--;
	}
	return wHash;
}

// SoC Hashing words (no key)
WORD SoCHashBy16A(PVOID Buffer) {
	WORD wHash = 0;
	BYTE rotl = 15;
	for (int i = 0; i < 16; i++) {
		QWORD qwData = ((QWORD*)Buffer)[i];
		for (int j = 0; j < 4; j++)
		{
			WORD wData = ((PWORD)&qwData)[j];
			wData = ROTR16(wData, i + 1);
			wHash ^= wData;
		}
		rotl--;
	}
	return wHash;
}

// SoC Hashing bytes (no key)
WORD SoCHashBy8(PVOID Buffer) {
	WORD wHash = 0;
	BYTE rotl = 15;
	for (int i = 0; i < 16; i++) {
		QWORD qwData = ROTR64(((QWORD*)Buffer)[i], i+1);
		for (int j = 0; j < 8; j++)
			((PBYTE)&wHash)[j & 1] ^= ((PBYTE)&qwData)[j];
		rotl--;
	}
	return wHash;
}

WORD SoCHashTestA(PVOID Buffer, PVOID Key, BOOL dwLog = 1) {
	WORD wHash = 0;
	WORD wHashData = 0;
	WORD wHashKey = 0;
	BYTE rotl = 15;

	QWORD pqwKey[2] = { ((QWORD*)Key)[0], ((QWORD*)Key)[1] };
	//QWORD qwKey = (ROTL64(pqwKey[0], 1)) ^ pqwKey[1];

	for (int i = 0; i < 16; i++) {
		wHashKey = 0;
		wHashData = 0;
		WORD wTmp = 0;

		QWORD qwData = ((QWORD*)Buffer)[i];
		//qwData = ROTR64(qwData, i+1);

		QWORD qwKey = pqwKey[i & 1];
		//qwKey = ROTR64(qwKey, i+1);

		qwData ^= qwKey;

		for (int j = 0; j < 4; j++)
		{
			WORD wData = ((PWORD)&qwData)[j];
			wData = ROTR16(wData, i + 1);
			wHashData ^= wData;

			WORD wKey = ((PWORD)&qwKey)[j];
			wKey = ROTR16(wKey, i + 1);
			wHashKey ^= wKey;

			//wHashData ^= wKey;

			if(dwLog)
				printf("[%d,%d] Data: %04X, Hash: %04X || Key: %04X, Hash: %04X\n", i, j, wData, wHashData, wKey, wHashKey);

			//wHash ^= wKey;
		}
		rotl--;

		//wHash ^= wHashKey;
		wHash ^= (wHashData);
		//wHash ^= wHashKey;
		if(dwLog)
			printf("[%d] Hash: %04X\n", i, wHash);
	}
	return (wHash);
}

// this is the best progress so far, but theres something wrong
// im pretty sure they do something on the final loop of the inner loop or outer loop
// maybe a final xor?

WORD SoCHashTest(PVOID Buffer, PVOID Key, DWORD dwFlags = 0)
{
	BOOL dwLog = dwFlags & 1;
	BOOL dwSwap = dwFlags & 2;

	WORD wHash = 0;
	WORD wHashData = 0;
	WORD wHashKey = 0;
	BYTE rotl = 15;
	QWORD pqwKey[2] = { ((QWORD*)Key)[0], ((QWORD*)Key)[1] };
	//QWORD qwKey = (ROTL64(pqwKey[0], 1)) ^ pqwKey[1];

	QWORD pqwData[16] = { 0 };
	for (int i = 0; i < 16; i++)
	{
		if (dwSwap)
			pqwData[i] = _byteswap_uint64(((QWORD*)Buffer)[i]);
		else
			pqwData[i] = ((QWORD*)Buffer)[i];
	}

	for (int i = 0; i < 16; i++)
	{
		//wHashKey = 0;
		wHashData = 0;
		WORD wTmp = 0;

		QWORD qwData = pqwData[i];
		qwData = ROTR64(qwData, i + 1);

		QWORD qwKey = pqwKey[i & 1];
		qwKey = ROTL64(qwKey, i + 1);

		//qwData ^= qwKey;
		for (int j = 0; j < 4; j++)
		{
			WORD wData = ((PWORD)&qwData)[j];
			//wData = ROTR16(wData, i + 1);

			WORD wKey = ((PWORD)&qwKey)[j];
			//wKey = ROTL16(wKey, i + 1);

			wData ^= wKey;
			wHashData ^= wData;
			wHashKey ^= wKey;

			//wHashData ^= wHashKey;

			if (dwLog)
				printf("[%d,%d] Data: %04X, Hash: %04X || Key: %04X, Hash: %04X\n", i, j, wData, wHashData, wKey, wHashKey);
		}
		rotl--;

		//wHash ^= wHashKey;
		wHash ^= (wHashData);
		wHash ^= wHashKey;

		if (dwLog)
			printf("[%d] Hash: %04X\n", i, wHash);
	}
	return (wHash);
}


VOID ReverseData(PBYTE pbData, DWORD cbData) {
	DWORD dwMidpoint = cbData >> 1;
	DWORD dwReverseCounter = 0;
	PBYTE pbPtr = pbData;

	if (dwMidpoint) {
		while (dwReverseCounter < dwMidpoint) {
			DWORD i = (cbData - dwReverseCounter) - 1 & 0xFFFFFFFF;

			BYTE b1 = *pbPtr;
			BYTE b2 = pbData[i];
			*pbPtr = b2;
			pbData[i] = b1;

			dwReverseCounter++;
			pbPtr++;
		}
	}
}

VOID HvSetupShaSaltedHash(PBYTE Buffer1, DWORD Size1, PBYTE Buffer2, DWORD Size2) {
	DWORD i = 0;
	for (DWORD s = 0; s < Size2; s += 0x14)
	{
		DWORD subsize = (s + 0x14 > Size2) ? Size2 - s : 0x14;
		BYTE tmp[0x14];
		BYTE tmpint[] = { 0, 0, 0, i };

		XeShaContext sha;
		XeCryptShaInit(&sha);
		XeCryptShaUpdate(&sha, Buffer1, Size1);
		XeCryptShaUpdate(&sha, tmpint, 4);
		XeCryptShaFinal(&sha, tmp, 0x14);

		for (DWORD l = 0; l < subsize; l++)
			Buffer2[s + l] ^= tmp[l];


		i++;
	}
}


//void HvSetupShaSaltedHash(PBYTE Buffer1, DWORD Size1, PBYTE Buffer2, DWORD Size2) {
//  uint uVar1;
//  byte *pbVar2;
//  int in_r2;
//  undefined8 uVar3;
//  QWORD uVar4;
//  uint uVar6;
//  QWORD lVar5;
//  qword back_chain;
//  dword local_c0;
//  word local_b0;
//  word local_50;
//  dword local_3c;
//  
//  uVar3 = __Save_R12_27_thru_31();
//  uVar1 = *(uint *)(in_r2 + 0x10000);
//  while ((Size2 & 0xffffffff) != 0) {
//	XeShaContext sha;
//    XeCryptShaInit(&sha);
//    XeCryptShaUpdate(&sha, Buffer1,  Size1);
//    XeCryptShaUpdate(&sha, &local_c0,4);
//    XeCryptShaFinal(&sha, &local_50, 0x14);
//
//    uVar6 = 0x14;
//    if ((Size2 & 0xffffffff) < 0x15) {
//      uVar6 = (uint)Size2;
//    }
//
//    if (uVar6 != 0) {
//      uVar4 = (QWORD)uVar6;
//      lVar5 = Buffer2;
//      do {
//        pbVar2 = (byte *)lVar5;
//        uVar4 = uVar4 - 1;
//        *pbVar2 = pbVar2[(int)((int)&local_50 - (int)Buffer2)] ^ *pbVar2;
//        lVar5 = lVar5 + 1;
//      } while ((uVar4 & 0xffffffff) != 0);
//    }
//    Size2 = Size2 - (QWORD)uVar6;
//    Buffer2 = (QWORD)uVar6 + Buffer2;
//  }
//
//  FUN_00000204((QWORD)uVar1);
//  return;
//}

void HvSetupMemEncryptionKey(PBYTE Key, PBYTE clientSession, PBYTE buffer) {
	BYTE HvData[0x14]		= { 0xDA, 0x39, 0xA3, 0xEE, 0x5E, 0x6B, 0x4B, 0x0D, 0x32, 0x55, 0xBF, 0xEF, 0x95, 0x60, 0x18, 0x90, 0xAF, 0xD8, 0x07, 0x09 };
	BYTE signature[0x80]	= { 0x00 };

	signature[0]	= 0;
	memcpy((signature + 1),		clientSession, 0x14);
	memcpy((signature + 0x15),	HvData, 0x14);
	memset((signature + 0x29),	0,		0x26);

	signature[0x4F] = 1;
	memcpy((signature + 0x50), Key, 0x30);

	//Buffer.BlockCopy(HvSetupShaSaltedHash(RandomData, 20, buffer3, 0x6b), 0, dst, 0x15, 0x1b);
	HvSetupShaSaltedHash(clientSession, 0x14, (signature + 0x15), 0x6B);

	//Buffer.BlockCopy(HvSetupShaSaltedHash(buffer3, 0x6b, RandomData, 20), 0, dst, 1, 20);
	HvSetupShaSaltedHash((signature + 0x15), 0x6B, clientSession, 0x14);
	memcpy(buffer, signature, 0x80);
}

EXTERN_C{

	__declspec(dllexport) void RSAEncryptSignature(PBYTE Input, PBYTE buffer) {
		byte signature[0x80];
		memcpy(signature, Input, 0x80);

		ReverseData(signature, 0x80);
		XeCryptBnQw_SwapDwQwLeBe((const u64*)signature, (u64*)signature, 0x10);
		if (XeCryptBnQwNeRsaPubCrypt((const u64*)signature, (u64*)signature, (XeRsaKey*)ChalKey)) {
			XeCryptBnQw_SwapDwQwLeBe((const u64*)signature, (u64*)signature, 0x10);
			memcpy(buffer, signature, 0x80);
		}else{
			printf("XeCryptBnQwNeRsaPubCrypt FAILED!\n");
			memset(buffer, 0x0, 0x80);
		}
	}

	__declspec(dllexport) void ComputeRSAOutput(PBYTE Key, PBYTE clientSession, PBYTE buffer){
		BYTE RsaFinal[0x80];
		BYTE RsaData[0x80]; 
		BYTE shaSalt[0x14]	= { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, clientSession[04], clientSession[02] };
		memset(RsaFinal, 0x00, 0x80); 

		HvSetupMemEncryptionKey(Key, shaSalt, RsaData);
		RSAEncryptSignature(RsaData, RsaFinal);
		memcpy(buffer, RsaFinal, 0x80);
	}

	//generate HV security hash generated on SOC memory hash
	__declspec(dllexport) void ECC_Chal(PBYTE Hypervisor, PBYTE HV_ENC, PBYTE SoC, PBYTE checksum, PBYTE buffer){
		BYTE OutHash[0x14] = { 0x00 };

		XeShaContext sha;
		XeCryptShaInit(&sha);
		XeCryptShaUpdate(&sha, checksum,				0x02);
		XeCryptShaUpdate(&sha, Hypervisor	+ 0x34, 	0xC);
		XeCryptShaUpdate(&sha, Hypervisor	+ 0x40, 	0x30);
		XeCryptShaUpdate(&sha, Hypervisor	+ 0xF0, 	0x4);
		XeCryptShaUpdate(&sha, Hypervisor	+ 0xF8, 	0x8);
		XeCryptShaUpdate(&sha, SoC 			+ 0x2, 		0x3FE);
		XeCryptShaUpdate(&sha, HV_ENC 		+ 0x100C0, 	0x40);
		XeCryptShaUpdate(&sha, HV_ENC 		+ 0x10350, 	0x30);
		XeCryptShaUpdate(&sha, SoC 			+ 0x40E, 	0x17C);
		XeCryptShaUpdate(&sha, HV_ENC 		+ 0x16280,	0x40);
		XeCryptShaUpdate(&sha, HV_ENC 		+ 0x16EA0, 	0x60);
		XeCryptShaUpdate(&sha, SoC 			+ 0x5BC, 	0x244);
		XeCryptShaUpdate(&sha, SoC 			+ 0x800, 	0x400);
		XeCryptShaUpdate(&sha, SoC 			+ 0xC00, 	0x400);
		XeCryptShaFinal(&sha,  OutHash,					0x14);

		memcpy(buffer, OutHash, 0x14);
	}

	//generate HV security hash generated on SOC memory hash
	__declspec(dllexport) void HV_Chal(PBYTE Hypervisor, PBYTE checksum, PBYTE buffer){
		BYTE OutHash[0x14] = { 0x00 };

		XeShaContext sha;
		XeCryptShaInit(&sha);
		XeCryptShaUpdate(&sha, checksum,			 0x10);
		XeCryptShaUpdate(&sha, Hypervisor + 0x34,	 0x40);
		XeCryptShaUpdate(&sha, Hypervisor + 0x78,	 0xFF88);
		XeCryptShaUpdate(&sha, Hypervisor + 0x100C0, 0x40);
		XeCryptShaUpdate(&sha, Hypervisor + 0x10350, 0x5F70);
		XeCryptShaUpdate(&sha, Hypervisor + 0x16EA0, 0x9160);
		XeCryptShaUpdate(&sha, Hypervisor + 0x20000, 0xFFFF);
		XeCryptShaUpdate(&sha, Hypervisor + 0x30000, 0xFFFF);
		XeCryptShaFinal(&sha,  OutHash,				 0x14);

		memcpy(buffer, OutHash, 0x14);
	}
}


typedef struct _HV_IMAGE_INFO { 
	BYTE Signature[0x100]; // 0x0 sz:0x100
	DWORD InfoSize; // 0x100 sz:0x4
	DWORD ImageFlags; // 0x104 sz:0x4
	DWORD LoadAddress; // 0x108 sz:0x4
	BYTE ImageHash[0x14]; // 0x10C sz:0x14
	DWORD ImportTableCount; // 0x120 sz:0x4
	BYTE ImportDigest[0x14]; // 0x124 sz:0x14
	BYTE MediaID[0x10]; // 0x138 sz:0x10
	BYTE ImageKey[0x10]; // 0x148 sz:0x10
	DWORD ExportTableAddress; // 0x158 sz:0x4
	BYTE HeaderHash[0x14]; // 0x15C sz:0x14
	DWORD GameRegion; // 0x170 sz:0x4
} HV_IMAGE_INFO, *PHV_IMAGE_INFO; // size 372

typedef struct _XEX_SECURITY_INFO { 
	DWORD Size; // 0x0 sz:0x4
	DWORD ImageSize; // 0x4 sz:0x4
	HV_IMAGE_INFO ImageInfo; // 0x8 sz:0x174
	DWORD AllowedMediaTypes; // 0x17C sz:0x4
	DWORD PageDescriptorCount; // 0x180 sz:0x4
} XEX_SECURITY_INFO, *PXEX_SECURITY_INFO; // size 388

typedef struct _IMAGE_XEX_HEADER { 
	DWORD Magic; // 0x0 sz:0x4
	DWORD ModuleFlags; // 0x4 sz:0x4
	DWORD SizeOfHeaders; // 0x8 sz:0x4
	DWORD SizeOfDiscardableHeaders; // 0xC sz:0x4
	DWORD SecurityInfo; // 0x10 sz:0x4
	DWORD HeaderDirectoryEntryCount; // 0x14 sz:0x4
} IMAGE_XEX_HEADER, *PIMAGE_XEX_HEADER; // size 24

typedef struct _LDR_DATA_TABLE_ENTRY { 
	LIST_ENTRY InLoadOrderLinks;  // 0x0 sz:0x8
	LIST_ENTRY InClosureOrderLinks;  // 0x8 sz:0x8
	LIST_ENTRY InInitializationOrderLinks; // 0x10 sz:0x8
	PVOID NtHeadersBase; // 0x18 sz:0x4
	PVOID ImageBase; // 0x1C sz:0x4
	DWORD SizeOfNtImage; // 0x20 sz:0x4
	UNICODE_STRING FullDllName; // 0x24 sz:0x8
	UNICODE_STRING BaseDllName; // 0x2C sz:0x8
	DWORD Flags; // 0x34 sz:0x4
	DWORD SizeOfFullImage; // 0x38 sz:0x4
	PVOID EntryPoint; // 0x3C sz:0x4
	WORD LoadCount; // 0x40 sz:0x2
	WORD ModuleIndex; // 0x42 sz:0x2
	PVOID DllBaseOriginal; // 0x44 sz:0x4
	DWORD CheckSum; // 0x48 sz:0x4
	DWORD ModuleLoadFlags; // 0x4C sz:0x4
	DWORD TimeDateStamp; // 0x50 sz:0x4
	PVOID LoadedImports; // 0x54 sz:0x4
	PVOID XexHeaderBase; // 0x58 sz:0x4
	union{
		STRING LoadFileName; // 0x5C sz:0x8
		struct {
			PVOID ClosureRoot; // 0x5C sz:0x4 LDR_DATA_TABLE_ENTRY
			PVOID TraversalParent; // 0x60 sz:0x4 LDR_DATA_TABLE_ENTRY
		} asEntry;
	} inf;
} LDR_DATA_TABLE_ENTRY, *PLDR_DATA_TABLE_ENTRY; // size 100

void main(void)
{
	BYTE pbData[0x04] = { 0x11, 0x22, 0x33, 0x44 };
	ReverseData(pbData, 0x04);
    printf("pbData: 0x%X %X %X %X!\n", pbData[0], pbData[1], pbData[2], pbData[3]);

	byte HvSalt[0x08];
	WORD tmp = 0x01BB;

    BYTE Payload[0x3F0] = { NULL /* Payload? */};
    BYTE HVSalt[0x10] = { NULL };

    QWORD unk = (QWORD)(Payload + 0x3E0);
    *(PWORD)(Payload + 0xD8) = (WORD)((unk >> 0x10) & 0xFFFF);

    BYTE Block[0x80];
    for (INT i = 0x00; i < 0x08; i++)
    {
        memcpy(Block + (i * 0x10), HVSalt, 0x10);
        memcpy(Block + (i * 0x10) + 0x08, HVSalt + 0x08, 0x08);
    }
    //__dcbst(Payload + 0x3E0);
	//(Block >> 6 & 0x3ff | 0xf800) + 0x8000020000010000, 2);



	PLDR_DATA_TABLE_ENTRY hCurrTitle = (PLDR_DATA_TABLE_ENTRY)0;
	IMAGE_XEX_HEADER* currModuleHeader = (IMAGE_XEX_HEADER*)(hCurrTitle->XexHeaderBase);
	if (currModuleHeader) {
		XEX_SECURITY_INFO* securityInfo = (XEX_SECURITY_INFO*)(currModuleHeader->SecurityInfo);
		int size = ((currModuleHeader->SizeOfHeaders - (DWORD)&securityInfo->AllowedMediaTypes) + (int)currModuleHeader);
		
		
		
		
		//xbox::utilities::writeFile("Client:\\FFFE07D1.bin", (PBYTE)&securityInfo->AllowedMediaTypes, size);
	}


	getchar();
	return;
}