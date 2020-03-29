#pragma once

#include <xtl.h>
#include <stdio.h>

typedef struct {
	XEKEYS_EXEC_HEADER header; //0x0
	QWORD result; //0x20
	WORD HvMagic; //0x28
	WORD HvVersion; //0x2A
	WORD HvQfe; //0x2C
	WORD BldrFlags; //0x2E
	DWORD BaseKernelVersion; //0x30
	DWORD UpdateSequence; //0x34
	DWORD HvStatusFlags; //0x38
	DWORD ConsoleTypeSeqAllow; //0x3C
	QWORD RTOC; //0x40
	QWORD HRMOR; //0x48
	BYTE HvECCDigest[XECRYPT_SHA_DIGEST_SIZE]; //0x50
	BYTE CpuKeyDigest[XECRYPT_SHA_DIGEST_SIZE]; //0x64
	BYTE HvCertificate[0x80]; //0x78
	WORD hvExAddr; //0xF8
	BYTE HvDigest[0x6]; //0xFA
} XE_KEYS_BUFFER, * PXE_KEYS_BUFFER;
C_ASSERT(sizeof(XE_KEYS_BUFFER) == 0x100);


namespace global {
	namespace challenge {
		extern PVOID cleanhvv;
		extern PVOID bufferAddress;
		extern DWORD bufferSize;
		extern BOOL hasChallenged;
		extern XEX_EXECUTION_ID executionId;
		extern XECRYPT_SHA_STATE xShaCurrentXex;
		extern BYTE spoofedMacAddress[];
		extern BYTE cpukey[];
	}
}