#pragma once

namespace xbox  
{
	namespace Cleaning 
	{
		typedef struct {
			BYTE header[0x20]; //0x0
			BYTE result[0x08]; //0x20
			BYTE HvMagic[0x02]; //0x28
			BYTE HvVersion[0x02]; //0x2A
			BYTE HvQfe[0x02]; //0x2C
			BYTE BldrFlags0[0x02]; //0x2E
			BYTE BaseKernelVersion[0x04]; //0x30
			BYTE UpdateSequence[0x04]; //0x34
			BYTE HvStatusFlags[0x04]; //0x38
			BYTE ConsoleTypeSeqAllow[0x04]; //0x3C
			BYTE RTOC[0x08]; //0x40
			BYTE HRMOR[0x08]; //0x48
			BYTE HvECCDigest[0x14]; //0x50
			BYTE CpuKeyDigest[0x14]; //0x64
			BYTE HvCertificate[0x80]; //0x78
			BYTE hvExAddr[0x02]; //0xF8
			BYTE HvDigest[0x06]; //0xFA
		} XE_KEYS_BUFFER2, * PXE_KEYS_BUFFER2;

		VOID setHV0(BYTE* HV, QWORD qAddress, DWORD Address, DWORD Size) ;
		VOID cleaningHV(BYTE* SystemHV, BYTE* CleanHV);
		VOID DirtyHV(BYTE* SystemHV);
		VOID LOGGER(XE_KEYS_BUFFER2* Buffer, int i);

		VOID DumpSRAM(char* file) ;
		VOID DumpHV(char* file); 
		VOID DumpKeys(char* file);

		PBYTE CallXamExecuteChallenge(PBYTE pSalt);
		VOID Go_Clean_HV();
	}
}