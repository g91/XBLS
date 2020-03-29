#include "stdafx.h"
#include <direct.h>

namespace xbox  
{
	namespace Cleaning 
	{
		VOID setHV0(BYTE* HV, QWORD qAddress, DWORD Address, DWORD Size) 
		{
			BYTE* Data = (BYTE*)XPhysicalAlloc(Size, MAXULONG_PTR, NULL, PAGE_READWRITE);
			memset(Data, 0, Size);
			memcpy(Data, HV + Address, Size);
			xbox::Hvx::HvPokeBytes(qAddress + Address, Data, Size);
			XPhysicalFree(Data);
		}

		VOID cleaningHV(BYTE* SystemHV, BYTE* CleanHV)
		{
			setHV0(CleanHV,		0x8000010000000000, 0x00, 0xFFFF);
			setHV0(SystemHV,	0x8000010000000000, 0x00, 0x20);

			//setHV0(CleanHV,	0x8000010000000000, 0x34, 0x40);
			//setHV0(CleanHV,	0x8000010000000000, 0x40, 0x30);
			//setHV0(SystemHV,	0x8000010000000000, 0x54, 0x10);
			//setHV0(SystemHV,	0x8000010000000000, 0x77, 0x02);
			//setHV0(CleanHV,	0x8000010000000000, 0x78, 0xFF88);


			setHV0(SystemHV,	0x8000010200000000, 0x10000, 0x04);
			setHV0(SystemHV,	0x8000010200000000, 0x10020, 0xA0);

			setHV0(CleanHV,		0x8000010200000000, 0x100C0, 0x40);
			setHV0(SystemHV,	0x8000010200000000, 0x10100, 0x30);
			setHV0(SystemHV,	0x8000010200000000, 0x16390, 0x04); 
			setHV0(SystemHV,	0x8000010200000000, 0x16620, 0x01);
			setHV0(SystemHV,	0x8000010200000000, 0x16640, 0x14);

			setHV0(CleanHV,		0x8000010200000000, 0x10350, 0x30);

			setHV0(CleanHV, 0x8000010200000000, 0x15E00, 0x80);
			setHV0(CleanHV, 0x8000010200000000, 0x15FD0, 0x04);
			setHV0(CleanHV, 0x8000010200000000, 0x16280, 0x40);
			setHV0(CleanHV, 0x8000010200000000, 0x162A0, 0x16);
			setHV0(CleanHV, 0x8000010200000000, 0x16EA0, 0x60);
			setHV0(CleanHV, 0x8000010200000000, 0x169DE, 0x01);
			setHV0(CleanHV, 0x8000010200000000, 0x16A37, 0x01);

			setHV0(SystemHV, 0x8000010200000000, 0x16710, 0x10);
			setHV0(SystemHV, 0x8000010200000000, 0x16980, 0x102);
			setHV0(SystemHV, 0x8000010200000000, 0x16B90, 0x10);
			setHV0(SystemHV, 0x8000010200000000, 0x16E98, 0x04);

			setHV0(CleanHV, 0x8000010400000000, 0x20000, 0xFFFF);
			setHV0(CleanHV, 0x8000010600000000, 0x30000, 0xFFFF);
		}
		
		VOID DirtyHV(BYTE* SystemHV)
		{
			setHV0(SystemHV, 0x8000010000000000, 0x00000, 0xFFFF);
			setHV0(SystemHV, 0x8000010200000000, 0x10000, 0xFFFF);
			setHV0(SystemHV, 0x8000010400000000, 0x20000, 0xFFFF);
			setHV0(SystemHV, 0x8000010600000000, 0x30000, 0xFFFF);
		}
		
		VOID LOGGER(XE_KEYS_BUFFER2* Buffer, int i)
		{
			xbox::utilities::DbgOut(" - HvMagic 0x%02X%02X						(%i)\n", Buffer->HvMagic[0], Buffer->HvMagic[1], i);
			xbox::utilities::DbgOut(" - HvVersion 0x%02X%02X					(%i)\n", Buffer->HvVersion[0], Buffer->HvVersion[1], i);
			xbox::utilities::DbgOut(" - HvQfe 0x%02X%02X						(%i)\n", Buffer->HvQfe[0], Buffer->HvQfe[1], i);
			xbox::utilities::DbgOut(" - BldrFlags 0x%02X%02X					(%i)\n", Buffer->BldrFlags0[0], Buffer->BldrFlags0[1], i);
			xbox::utilities::DbgOut(" - BaseKernelVersion 0x%02X%02X%02X%02X	(%i)\n", Buffer->BaseKernelVersion[0], Buffer->BaseKernelVersion[1], Buffer->BaseKernelVersion[2], Buffer->BaseKernelVersion[3], i);
			xbox::utilities::DbgOut(" - UpdateSequence 0x%02X%02X%02X%02X		(%i)\n", Buffer->UpdateSequence[0], Buffer->UpdateSequence[1], Buffer->UpdateSequence[2], Buffer->UpdateSequence[3], i);
			xbox::utilities::DbgOut(" - HvStatusFlags 0x%02X%02X%02X%02X		(%i)\n", Buffer->HvStatusFlags[0], Buffer->HvStatusFlags[1], Buffer->HvStatusFlags[2], Buffer->HvStatusFlags[3], i);
			xbox::utilities::DbgOut(" - ConsoleTypeSeqAllow 0x%02X%02X%02X%02X	(%i)\n", Buffer->ConsoleTypeSeqAllow[0], Buffer->ConsoleTypeSeqAllow[1], Buffer->ConsoleTypeSeqAllow[2], Buffer->ConsoleTypeSeqAllow[3], i);
			xbox::utilities::DbgOut(" - HvECCDigest %02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X (%i) \n", Buffer->HvECCDigest[0], Buffer->HvECCDigest[1], Buffer->HvECCDigest[2], Buffer->HvECCDigest[3], Buffer->HvECCDigest[4], Buffer->HvECCDigest[5], Buffer->HvECCDigest[6], Buffer->HvECCDigest[7], Buffer->HvECCDigest[8], Buffer->HvECCDigest[9], Buffer->HvECCDigest[10], Buffer->HvECCDigest[11], Buffer->HvECCDigest[12], Buffer->HvECCDigest[13], Buffer->HvECCDigest[14], Buffer->HvECCDigest[15], i);
			xbox::utilities::DbgOut(" - hvExAddr 0x%02X%02X						(%i)\n", Buffer->hvExAddr[0], Buffer->hvExAddr[1], i);
			xbox::utilities::DbgOut(" - HvDigest %02X%02X%02X%02X%02X%02X		(%i)\n", Buffer->HvDigest[0], Buffer->HvDigest[1], Buffer->HvDigest[2], Buffer->HvDigest[3], Buffer->HvDigest[4], Buffer->HvDigest[5], Buffer->HvDigest[6], i);
		}
		
		VOID DumpSRAM(char* file) 
		{
			xbox::utilities::DbgOut("DumpSRAM: %s\n", file);
			PBYTE pCache2 = (PBYTE)XPhysicalAlloc(0x1000, MAXULONG_PTR, 0, PAGE_READWRITE);
			memset(pCache2, 0, 0x1000);
			xbox::Hvx::HvPeekBytes(0x8000020000010000, pCache2, 0x1000);
			xbox::utilities::writeFile(file, pCache2, 0x1000);
			XPhysicalFree(pCache2);
		}
		
		VOID DumpHV(char* file) 
		{
			xbox::utilities::DbgOut("DumpHV: %s_DEC.bin\n", file);

			BYTE* LiveHV = (BYTE*)XPhysicalAlloc(0x40000, MAXULONG_PTR, NULL, PAGE_READWRITE);
			memset(LiveHV, 0, 0x40000);
			xbox::Hvx::HvPeekBytes(0, LiveHV, 0xFFFF);
			xbox::Hvx::HvPeekBytes(0x0000010200010000, LiveHV + 0x10000, 0xFFFF);
			xbox::Hvx::HvPeekBytes(0x0000010400020000, LiveHV + 0x20000, 0xFFFF);
			xbox::Hvx::HvPeekBytes(0x0000010600030000, LiveHV + 0x30000, 0xFFFF);
			xbox::utilities::writeFile(xbox::utilities::va("%s_DEC.bin", file).c_str(), LiveHV, 0x40000);
			XPhysicalFree(LiveHV);

			xbox::utilities::DbgOut("DumpHV: %s_ENC.bin\n", file);
			PBYTE pbHVPage0 = (PBYTE)XPhysicalAlloc(0x40000, MAXULONG_PTR, 0, PAGE_READWRITE);
			memcpy(pbHVPage0, (PVOID)0x80000000, 0x40000);
			xbox::utilities::writeFile(xbox::utilities::va("%s_ENC.bin", file).c_str(), pbHVPage0, 0x40000);
			XPhysicalFree(pbHVPage0);
		}
		
		VOID DumpKeys(char* file) 
		{
			PBYTE Keys = (PBYTE)XPhysicalAlloc(0x30, MAXULONG_PTR, 0, PAGE_READWRITE);
			memset(Keys, 0, 0x30);
			xbox::Hvx::HvPeekBytes(0x0000000200010100, Keys, 0x30);
			memcpy(Keys, Keys, 0x30);
			xbox::utilities::writeFile(file, Keys, 0x30);
		}
		
		extern "C"
		{
			VOID* MmAllocatePhysicalMemoryEx(DWORD dwFlags, DWORD dwSize, DWORD flProtect, PVOID ulPhysicalAddress, DWORD r7, DWORD ulAlignment);
			DWORD MmFreePhysicalMemory(DWORD r3, PVOID r4);

			DWORD NtAllocateVirtualMemory(DWORD *r3, DWORD *r4, DWORD r5, DWORD r6, DWORD r7);
			DWORD NtFreeVirtualMemory(DWORD *r3, DWORD r4, DWORD r5);
		}

		NTSTATUS XamExecuteChallenge2(PBYTE challenge, DWORD chalPageSize, PBYTE salt, DWORD saltSize, PVOID chalResp, DWORD respSize) {
			NTSTATUS retStatus = STATUS_SUCCESS;
			PVOID challengeLocation, hvSaltLocation;

			memset(chalResp, 0, respSize);

			if (chalPageSize >= 0x120) {
				DWORD challengeLength = ((chalPageSize + 0xFFF) & 0xFFFFF000);

				if (((challengeLength - 1) & challengeLength) != 0) {
					challengeLength = _CountLeadingZeros(challengeLength);

					if (challengeLength > 0x1000)
						retStatus = 1;
				}

				hvSaltLocation = MmAllocatePhysicalMemoryEx(2, 0x1000, PAGE_READWRITE, 0, -1, 0x1000);
				challengeLocation = MmAllocatePhysicalMemoryEx(2, challengeLength, (MEM_LARGE_PAGES | PAGE_READWRITE), 0, -1, challengeLength);

				if (challengeLocation == 0)
					retStatus = 2;

				memcpy(challengeLocation, challenge, chalPageSize);

				if (hvSaltLocation != 0) {
					memset(hvSaltLocation, 0, 0x1000);
					memcpy(hvSaltLocation, salt, (saltSize < 0x100 ? saltSize : 0x1000));

					DWORD hvSaltAddress = ((DWORD)MmGetPhysicalAddress(hvSaltLocation) & 0xFFFFFFFF);
					retStatus = XeKeysExecute(challengeLocation, challengeLength, (PVOID)hvSaltAddress, (QWORD*)XboxKrnlVersion, 0, 0);

					if (retStatus >= S_OK)
						memcpy(chalResp, (PVOID)((DWORD)challengeLocation + 0x20), 0x100);
				}
			}

			DWORD hmacResult = XeKeysHmacSha(
				XEKEY_ROAMABLE_OBFUSCATION_KEY,
				(PBYTE)"XBox 360 (C) Microsoft",
				0x17,
				salt,
				saltSize,
				0,
				0,
				(PBYTE)((DWORD)chalResp + 0xE4),
				((DWORD)chalResp + 0xF8)
			);

			*(DWORD*)(DWORD)chalResp = !NT_SUCCESS(retStatus) ? retStatus : hmacResult;
			*(DWORD*)((DWORD)chalResp + 0xE0) = KeTimeStampBundle->TickCount;

			if (challengeLocation != 0)
				MmFreePhysicalMemory(2, challengeLocation);

			if (hvSaltLocation != 0)
				MmFreePhysicalMemory(2, hvSaltLocation);

			return retStatus;
		}


		BYTE SystemHV[0x40000];
		VOID Go_Clean_HV()
		{
			memset(SystemHV, 0, 0x40000);
			xbox::Hvx::HvPeekBytes(0x8000010000000000, SystemHV, 0xFFFF);
			xbox::Hvx::HvPeekBytes(0x8000010200010000, SystemHV + 0x10000, 0xFFFF);
			xbox::Hvx::HvPeekBytes(0x8000010400020000, SystemHV + 0x20000, 0xFFFF);
			xbox::Hvx::HvPeekBytes(0x8000010600030000, SystemHV + 0x30000, 0xFFFF);

			MemoryBuffer mbHV;
			xbox::utilities::readFile("GAME:\\HV-base.bin", mbHV);
			BYTE* CleanHV = (BYTE*)XPhysicalAlloc(mbHV.GetDataLength(), MAXULONG_PTR, NULL, PAGE_READWRITE);
			memset(CleanHV, 0, mbHV.GetDataLength());
			memcpy(CleanHV, mbHV.GetData(), mbHV.GetDataLength());

			MemoryBuffer mbSalts;
			xbox::utilities::readFile("GAME:\\salts.bin", mbSalts);
			BYTE* all_Salts = (BYTE*)XPhysicalAlloc(mbSalts.GetDataLength(), MAXULONG_PTR, NULL, PAGE_READWRITE);
			memset(all_Salts, 0, mbSalts.GetDataLength());
			memcpy(all_Salts, mbSalts.GetData(), mbSalts.GetDataLength());

			MemoryBuffer mbCh;
			xbox::utilities::readFile("GAME:\\challenge.bin", mbCh);
			DWORD Size = mbCh.GetDataLength();
			BYTE* challenge = (BYTE*)XPhysicalAlloc(Size, MAXULONG_PTR, NULL, PAGE_READWRITE);
			memset(challenge, 0, Size);
			memcpy(challenge, mbCh.GetData(), Size);

			xbox::utilities::DbgOut("Domo correct data dumper v1.5 for 17559!!\n");
			xbox::utilities::DbgOut("system has been set up for usage!!\n");
			xbox::utilities::DbgOut("starting data dumping!!\n");

			xbox::utilities::DbgOut("\r\n");
			xbox::utilities::DbgOut("Dumped default Certificate not clean!!\n");
			xbox::utilities::DbgOut(" - for research purposes only\n");
			xbox::utilities::DbgOut(" - do not use\n");
			xbox::utilities::DbgOut("\r\n");
			xbox::utilities::DbgOut("starting process of dumping challenges  Build: 0x%X%X Major: 0x%X%X Minor: 0x%X%X Qfe: 0x%X%X \n", XboxKrnlVersion->Build, XboxKrnlVersion->Major, XboxKrnlVersion->Minor, XboxKrnlVersion->Qfe);

			cleaningHV(SystemHV, CleanHV);

			mkdir(xbox::utilities::va("GAME:\\dump").c_str());
			int j = 0;
			for(int p = 0; p  <= 255; p++)
			{
				if(!xbox::utilities::fileExists(xbox::utilities::va("GAME:\\dump\\%i", p).c_str()))
				{
					mkdir(xbox::utilities::va("GAME:\\dump\\%i", p).c_str());
					mkdir(xbox::utilities::va("GAME:\\dump\\%i\\xke", p).c_str());
					mkdir(xbox::utilities::va("GAME:\\dump\\%i\\MySalts", p).c_str());
					mkdir(xbox::utilities::va("GAME:\\dump\\%i\\ECCSalt", p).c_str());
					mkdir(xbox::utilities::va("GAME:\\dump\\%i\\Salts", p).c_str());
					
					DumpHV((char*)xbox::utilities::va("GAME:\\dump\\%i\\HV", p).c_str());
					DumpSRAM((char*)xbox::utilities::va("GAME:\\dump\\%i\\Cache.bin", p).c_str());
					DumpKeys((char*)xbox::utilities::va("GAME:\\dump\\%i\\Keys.bin", p).c_str());

					j = p;
					p = 999;
				}
			}
			
			for (int i = 0; i <= 255; i++)
			{
				xbox::utilities::DbgOut("start Dumping (%i) # %i\n", i, j);

				BYTE pSalt[0x10];
				memset(pSalt, 0, 0x10);
				PBYTE Salt = all_Salts + (0x10 * i);
				memcpy(pSalt, Salt, 0x10);

				BYTE* Buffer0 = (BYTE*)XPhysicalAlloc(0x100, MAXULONG_PTR, NULL, PAGE_READWRITE);
				memset(Buffer0, 0, 0x100);

				xbox::utilities::DbgOut(" - call   XamExecuteChallenge (%i)\n", i);
				xbox::utilities::DbgOut(" - HVSalt 0x%X%X%X%X%X%X%X%X%X%X%X%X%X%X%X%X\n", pSalt[0], pSalt[1], pSalt[2], pSalt[3], pSalt[4], pSalt[5], pSalt[6], pSalt[7], pSalt[8], pSalt[9], pSalt[10], pSalt[11], pSalt[12], pSalt[13], pSalt[14], pSalt[15]);
				XamExecuteChallenge2((PBYTE)challenge, 0x000003F8, (PBYTE)pSalt, 0x00000010, Buffer0, 0x00000100);

				BYTE ECCSalt[0x02];
				xbox::Hvx::HvPeekBytes(0x800002000001F810LL, ECCSalt, 0x02);
				xbox::utilities::DbgOut(" - ECCSalt 0x%X%X (%i)\n", ECCSalt[0], ECCSalt[1]);
				xbox::utilities::writeFile(xbox::utilities::va("GAME:\\dump\\%i\\ECCSalt\\0x%X%X%X%X%X%X%X%X%X%X%X%X%X%X%X%X.bin", j, pSalt[0], pSalt[1], pSalt[2], pSalt[3], pSalt[4], pSalt[5], pSalt[6], pSalt[7], pSalt[8], pSalt[9], pSalt[10], pSalt[11], pSalt[12], pSalt[13], pSalt[14], pSalt[15]).c_str(), ECCSalt, 0x02);

				BYTE* Buffer2 = (BYTE*)XPhysicalAlloc(0x100, MAXULONG_PTR, NULL, PAGE_READWRITE);
				memset(Buffer2, 0, 0x100);
				memcpy(Buffer2 + 0x20, Buffer0, 0xE0);
				XPhysicalFree(Buffer0);

				xbox::utilities::writeFile(xbox::utilities::va("GAME:\\dump\\%i\\xke\\0x%X%X%X%X%X%X%X%X%X%X%X%X%X%X%X%X.bin", j,  pSalt[0], pSalt[1], pSalt[2], pSalt[3], pSalt[4], pSalt[5], pSalt[6], pSalt[7], pSalt[8], pSalt[9], pSalt[10], pSalt[11], pSalt[12], pSalt[13], pSalt[14], pSalt[15]).c_str(), Buffer2, 0x100);
				xbox::utilities::DbgOut(" - File Dumped xke File (%i)\n", i);

				XE_KEYS_BUFFER2* Buffer = (XE_KEYS_BUFFER2*)((PBYTE)Buffer2);
				LOGGER(Buffer, i);

				PBYTE DUMP = (PBYTE)XPhysicalAlloc(0x70, MAXULONG_PTR, NULL, PAGE_READWRITE);
				memset(DUMP, 0, 0x70);

				memcpy(DUMP, pSalt, 0x10);
				memset(DUMP + 0x10, 0, 0x10);
				memset(DUMP + 0x20, 0, 0x10);
				memcpy(DUMP + 0x20, ECCSalt, 0x02);
				memset(DUMP + 0x30, 0, 0x10);
				memcpy(DUMP + 0x30, Buffer->hvExAddr, 0x02);
				memcpy(DUMP + 0x3A, Buffer->HvDigest, 0x06);
				memcpy(DUMP + 0x50, Buffer->HvECCDigest, 0x14);

				xbox::utilities::writeFile(xbox::utilities::va("GAME:\\dump\\%i\\MySalts\\0x%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X.bin", j, pSalt[0], pSalt[1], pSalt[2], pSalt[3], pSalt[4], pSalt[5], pSalt[6], pSalt[7], pSalt[8], pSalt[9], pSalt[10], pSalt[11], pSalt[12], pSalt[13], pSalt[14], pSalt[15]).c_str(), DUMP, 0x70);

				PBYTE DUMP2 = (PBYTE)XPhysicalAlloc(0x30, MAXULONG_PTR, NULL, PAGE_READWRITE);
				memset(DUMP2, 0, 0x30);

				memcpy(DUMP2, pSalt, 0x10);
				memcpy(DUMP2 + 0x10, Buffer->HvECCDigest,	0x14);
				memcpy(DUMP2 + 0x24, Buffer->hvExAddr,		0x02);
				memcpy(DUMP2 + 0x26, Buffer->HvDigest,		0x06);

				xbox::utilities::writeFile(xbox::utilities::va("GAME:\\dump\\%i\\Salts\\%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X.bin", j, pSalt[0], pSalt[1], pSalt[2], pSalt[3], pSalt[4], pSalt[5], pSalt[6], pSalt[7], pSalt[8], pSalt[9], pSalt[10], pSalt[11], pSalt[12], pSalt[13], pSalt[14], pSalt[15]).c_str(), DUMP2, 0x30);

				XPhysicalFree(Buffer2);
				XPhysicalFree(DUMP);
				XPhysicalFree(DUMP2);
				Sleep(100);
				xbox::utilities::DbgOut(" - Done (%i)\n", i);
			}

			DirtyHV(SystemHV);
		}

		PBYTE CallXamExecuteChallenge(PBYTE pSalt)
		{
			MemoryBuffer mbHV;
			xbox::utilities::readFile("GAME:\\HV-base.bin", mbHV);
			BYTE* CleanHV = (BYTE*)XPhysicalAlloc(mbHV.GetDataLength(), MAXULONG_PTR, NULL, PAGE_READWRITE);
			memset(CleanHV, 0, mbHV.GetDataLength());
			memcpy(CleanHV, mbHV.GetData(), mbHV.GetDataLength());

			MemoryBuffer mbCh;
			xbox::utilities::readFile("GAME:\\challenge.bin", mbCh);
			DWORD Size = mbCh.GetDataLength();
			BYTE* challenge = (BYTE*)XPhysicalAlloc(Size, MAXULONG_PTR, NULL, PAGE_READWRITE);
			memset(challenge, 0, Size);
			memcpy(challenge, mbCh.GetData(), Size);

			cleaningHV(SystemHV, CleanHV);

			BYTE* Buffer0 = (BYTE*)XPhysicalAlloc(0x100, MAXULONG_PTR, NULL, PAGE_READWRITE);
			memset(Buffer0, 0, 0x100);

			xbox::utilities::DbgOut(" - call   XamExecuteChallenge\n");
			xbox::utilities::DbgOut(" - HVSalt 0x%X%X%X%X%X%X%X%X%X%X%X%X%X%X%X%X\n", pSalt[0], pSalt[1], pSalt[2], pSalt[3], pSalt[4], pSalt[5], pSalt[6], pSalt[7], pSalt[8], pSalt[9], pSalt[10], pSalt[11], pSalt[12], pSalt[13], pSalt[14], pSalt[15]);
			XamExecuteChallenge2((PBYTE)challenge, 0x000003F8, pSalt, 0x00000010, Buffer0, 0x00000100);
			DirtyHV(SystemHV);

			BYTE Buffer[0x100];
			memcpy(Buffer, Buffer0, 0x100);
			free(Buffer0);

			return Buffer;
		}
	}
}