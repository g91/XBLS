#include "../stdafx.h"
#include "../Tools/Hooks.h"

XEX_EXECUTION_ID executionId;

namespace System {
	PVOID RtlImageXexHeaderFieldHook(PVOID HeaderBase, DWORD ImageField)
	{
		executionId.TitleID = 0xFFFE07D1;
		PVOID Result = RtlImageXexHeaderField(HeaderBase, ImageField);
		if (ImageField == XEX_HEADER_EXECUTION_ID)
		{
			if (Result)
			{
				switch (((PXEX_EXECUTION_ID)Result)->TitleID){
					case 0xFFFF0055: // Xex Menu
					case 0xC0DE9999: // Xex Menu alt
					case 0xC0DE9996: // Xex Menu alt
					case 0xFFFE07FF: // XShellXDK
					case 0xF5D20000: // FSD
					case 0xFFFF011D: // DashLaunch
					case 0x00000166: // Aurora
					case 0x00000189: // Simple360 NandFlasher
					case 0xFFFE07D1: // XellLaunch
					case 0x00000188: // Flash 360
					case 0x00000176: // XM360
					case 0x00000167: // Freestyle 3
					case 0x00000177: // NXE2GOD
					case 0x00000170: // Xexmenu 2.0
					case 0xFFFEFF43: // Xell Launch GOD
					case 0xFEEDC0DE: // XYZProject
					case 0x58480880: // Internet Explorer HB
					case 0x00000001: // FXMenu
					case 0x00000171: // FCEUX
					case 0xFFED0707: // SNES360
						memcpy(Result, &executionId, sizeof(XEX_EXECUTION_ID));
						break;
				}
			} else Result = &executionId;
		}

		return Result;
	}

	DWORD XeKeysExecuteHook(PBYTE Buffer, DWORD Size, PBYTE HvSalt, PVOID r6, PVOID r7, PVOID r8) {
		XKEC_REQUEST Request = { 0 };
		XKEC_RESPONSE Response = { 0 };
		//=======================================================================================================
		BYTE CPUKey[0x10];
		xbox::utilities::getCPUKey(CPUKey);
		if (CPUKey[5] != global::challenge::cpukey[5])
			goto Failed;
		//=======================================================================================================
		xbox::utilities::setMemory(Request.Salt, HvSalt, 0x10);
		xbox::utilities::setMemory(Request.SessionToken, global::g_pSessionToken, 0x14);
		xbox::utilities::setMemory(Request.CPUKey, global::challenge::cpukey, 0x10);
		xbox::utilities::setMemory(Request.KVCPUKey, xbox::utilities::data::cpuKey, 0x10);
		xbox::utilities::setMemory(Request.partnumber, &xbox::utilities::data::buffer.ConsoleCertificate.ConsolePartNumber, 0x0B);
		xbox::utilities::setMemory(Request.kvsignature, &xbox::utilities::data::buffer.ConsoleCertificate.Signature, 0x100);
		//=======================================================================================================
		Request.Crl = xbox::utilities::data::crl != 0 ? TRUE : FALSE;
		Request.Fcrt = xbox::utilities::data::fcrtRequired != 0 ? TRUE : FALSE;
		//=======================================================================================================
		if (Process(COMMAND_XKEC, &Request, sizeof(XKEC_REQUEST), &Response, sizeof(XKEC_RESPONSE), FALSE)) 
		{
			if (Authenticated = (Response.Status == 0x4A000000)) 
			{
				memset(Buffer, 0, Size);
				if (!Receive(Buffer, 0x100))
					goto Failed;
	
				if (Buffer[0x28] != 0x4E) 
				{
					xbox::utilities::setLiveBlock(TRUE);
					goto Failed;
				}
				//=======================================================================================================
				PXE_KEYS_BUFFER buff = (PXE_KEYS_BUFFER)Buffer;
				//=======================================================================================================
				XEKEYS_EXEC_HEADER header = (XEKEYS_EXEC_HEADER)buff->header;								//	XEKEYS_EXEC_HEADER header; //0x0			
				buff->result				= 0x0000000000000000;											//	QWORD result; //0x20
				buff->HvMagic				= 0x4E4E;														//	WORD HvMagic; //0x28
				buff->HvVersion				= 0x4497;														//	WORD HvVersion; //0x2A
				buff->HvQfe					= 0x0000;														//	WORD HvQfe; //0x2C
				buff->BldrFlags				= xbox::utilities::data::bldrFlags;								//	WORD BldrFlags; //0x2E
				buff->BaseKernelVersion		= 0x07600000;													//	DWORD BaseKernelVersion; //0x30
				buff->UpdateSequence		= xbox::utilities::data::updSeqFlags;							//	DWORD UpdateSequence; //0x34
				buff->HvStatusFlags			= xbox::utilities::data::hvStatusFlags;							//	DWORD HvStatusFlags; //0x38
				//buff->ConsoleTypeSeqAllow	= xbox::utilities::data::ConsoleTypeSeqAllow;					//	DWORD ConsoleTypeSeqAllow; //0x3C
				buff->RTOC					= 0x0000000200000000;									    	//	QWORD RTOC; //0x40
				buff->HRMOR					= 0x0000010000000000;											//	QWORD HRMOR; //0x48
																											//	BYTE HvECCDigest[XECRYPT_SHA_DIGEST_SIZE]; //0x50
				memcpy(buff->CpuKeyDigest, xbox::utilities::data::cpuKeyDigest, XECRYPT_SHA_DIGEST_SIZE);	//	BYTE CpuKeyDigest[XECRYPT_SHA_DIGEST_SIZE]; //0x64
																											//	BYTE HvCertificate[0x80]; //0x78
																											//	WORD hvExAddr; //0xF8
																											//	BYTE HvDigest[0x6]; //0xFA
				//=======================================================================================================
				XBLAPI::XKE::FillBuffer((PBYTE)Buffer, xbox::utilities::data::crl, xbox::utilities::data::fcrtRequired, xbox::utilities::data::type1KV, xbox::utilities::data::updSeqFlags, xbox::utilities::data::cpuKey, buff->HvECCDigest, buff->HvCertificate, buff->HvDigest, (PBYTE)&xbox::utilities::data::buffer);
				//=======================================================================================================
				//xbox::utilities::writeFile("Client:\\Buffer02.bin", Buffer, 0x100);
				//=======================================================================================================
			}
			else goto Failed;
		}
		else goto Failed;
		//=======================================================================================================
		if (!global::challenge::hasChallenged) 
		{
			xbox::utilities::data::crl = TRUE;
			xbox::utilities::data::hvStatusFlags = (xbox::utilities::data::crl) ? (xbox::utilities::data::hvStatusFlags | 0x10000) : xbox::utilities::data::hvStatusFlags;
			global::challenge::hasChallenged = TRUE;
			xbox::utilities::XNotifyUI(XNOTIFYUI_TYPE_PREFERRED_REVIEW, L"Your Connected to Live");
		}
		//=======================================================================================================
		Disconnect();
		Sleep(13000);
		//=======================================================================================================
		return S_OK;
	Failed:
		xbox::utilities::setLiveBlock(TRUE);
		Disconnect();
		Sleep(2000);
		HalReturnToFirmware(HalRebootQuiesceRoutine);
		//=======================================================================================================
		return E_FAIL;
	}

	VOID ApplyPatches(PVOID RootAddress, CONST PVOID Input, DWORD Value)
	{
		PWORD PatchBlock = (PWORD)Input;
		while (*PatchBlock != 0xFFFF)
		{
			for (INT i = 0x00; i < (INT)PatchBlock[0x01]; i++)
			{
				memcpy((PBYTE)RootAddress + PatchBlock[0x00] + (i * 0x04), &Value, (PatchBlock[0x01] * 0x04));
			}
			PatchBlock += 0x02;
		}
	}

	BYTE TitleDigest[0x14] = { 0 };
	typedef DWORD(*ExecuteSupervisorChallenge_t)(DWORD dwTaskParam1, PBYTE pbDaeTableName, DWORD cbDaeTableName, PVOID pbBuffer, DWORD cbBuffer);
	DWORD XamLoaderExecuteAsyncChallengeHook(DWORD Address, DWORD Task, PBYTE DaeTableHash, DWORD DaeTableSize, PVOID Buffer, DWORD Length, LPVOID pCommandBuffer, LPVOID pRecvBuffer, BYTE Index, INT Fan, INT Speed, BYTE Command, BOOL Animate, DWORD dwTaskParam1, BYTE* pbDaeTableName, DWORD cbDaeTableName, DWORD cbBuffer)
	{
		XOSC_REQUEST Request = { 0 };
		XOSC_RESPONSE Response = { 0 };

		Request.Crl = xbox::utilities::data::crl;
		Request.Fcrt = xbox::utilities::data::fcrtRequired;
		Request.Title = XamGetCurrentTitleId();

		xbox::utilities::setMemory(Request.CPUKey, xbox::utilities::data::cpuKey, 0x10);
		xbox::utilities::setMemory(Request.uCPUKey, global::challenge::cpukey, 0x10);
		xbox::utilities::setMemory(Request.KVDigest, xbox::utilities::data::keyvaultDigest, 0x14);

		Request.SerialByte = xbox::utilities::data::SerialByte;
		Request.GameRegion = xbox::utilities::data::buffer.GameRegion;
		Request.OddFeatures = xbox::utilities::data::buffer.OddFeatures;
		Request.PolicyFlashSize = xbox::utilities::data::buffer.PolicyFlashSize;

		xbox::utilities::setMemory(Request.spoofedMacAddress, global::challenge::spoofedMacAddress, 6);
		xbox::utilities::setMemory(Request.ConsoleID, &xbox::utilities::data::buffer.ConsoleCertificate.ConsoleId, 5);
		xbox::utilities::setMemory(Request.ConsoleSerialNumber, &xbox::utilities::data::buffer.ConsoleSerialNumber, 0xC);

		xbox::utilities::setMemory(Request._unk1, &xbox::utilities::data::buffer.XeikaCertificate.Data.OddData.InquiryData, 0x24);
		Request._unk2 = ((BYTE)&xbox::utilities::data::buffer.XeikaCertificate.Data.OddData.PhaseLevel);
		
		WORD  cbInp0 = *(WORD*)(Address - 0x62);
		WORD  cbInp1 = *(WORD*)(Address - 0x66);

		Request.cbInp0 = cbInp0;
		Request.cbInp1 = cbInp1;
		DWORD orgAddress = Address;
		xbox::utilities::setMemory(Request.fuseDigest, (byte*)0x8E03AA50, 0x10);

		ExecuteSupervisorChallenge_t ExecuteSupervisorChallenge = (ExecuteSupervisorChallenge_t)Address;
		ExecuteSupervisorChallenge(dwTaskParam1, pbDaeTableName, DaeTableSize, Buffer, Length);

		unsigned char XOSC_CHALLENGE_RECURRING_PATCHES[30] = {
			0x00, 0x24, 0x00, 0x04, 0x00, 0x8C, 0x00, 0x19, 0x01, 0x5C, 0x00, 0x01,
			0x01, 0x6C, 0x00, 0x01, 0x02, 0x1C, 0x00, 0x23, 0x02, 0xC8, 0x00, 0x04,
			0x02, 0xDC, 0x00, 0x01, 0xFF, 0xFF
		};

		ApplyPatches(Buffer, XOSC_CHALLENGE_RECURRING_PATCHES, 0xAAAAAAAA);
		xbox::utilities::setMemory(Request.XOSC, Buffer, 0x2E0);

		if (Process(COMMAND_XOSC, &Request, sizeof(XOSC_REQUEST), &Response, sizeof(XOSC_RESPONSE), FALSE)) {
			if (Authenticated = (Response.Status == 0x4A000000)) {
				memset(Buffer, 0, 0x2E0);
				if (!Receive(TitleDigest, 0x14) || !Receive(Buffer, 0x2E0)) goto Failed;

				xbox::utilities::setMemory(((PBYTE)Buffer + 0x50), xbox::utilities::data::cpuKeyDigest, 0x10);
				XeCryptSha((PBYTE)(0x90010000 | cbInp0), cbInp1, TitleDigest, 0x14, 0, 0, ((PBYTE)Buffer + 0x60), 0x10);
				((PBYTE)Buffer + 0x60)[0] = 7;
			}
			else goto Failed;
		}
		else goto Failed;
		Disconnect();

		//xbox::utilities::writeFile("Client:\\Buffer02.bin", Buffer, 0x100);
		//XBLAPI::XOSC::FillBuffer(Buffer, xbox::utilities::data::crl, xbox::utilities::data::fcrtRequired, xbox::utilities::data::type1KV, xbox::utilities::data::cpuKey, TitleDigest, xbox::utilities::data::XOSCHash, (PBYTE)&xbox::utilities::data::buffer);
		return STATUS_SUCCESS;
	Failed:
		Disconnect();
		Sleep(2000);
		HalReturnToFirmware(HalRebootQuiesceRoutine);

		return E_FAIL;
	}

	BOOL InitializeSystemHooks() 
	{
		DWORD ver = ((XboxKrnlVersion->Major & 0xF) << 28) | ((XboxKrnlVersion->Minor & 0xF) << 24) | (XboxKrnlVersion->Build << 8) | (XboxKrnlVersion->Qfe);
		ZeroMemory(&executionId, sizeof(XEX_EXECUTION_ID));
		executionId.Version = ver;
		executionId.BaseVersion = ver; //0x20449700;
		executionId.TitleID = 0xFFFE07D1;
		
		if (xbox::utilities::patchModuleImport(MODULE_XAM, MODULE_KERNEL, 0x12B, (DWORD)RtlImageXexHeaderFieldHook) != S_OK)
			return FALSE;

		if (xbox::utilities::patchModuleImport(MODULE_XAM, MODULE_KERNEL, 0x25F,	(DWORD)XeKeysExecuteHook) != S_OK) 
			return FALSE;

		xbox::utilities::patchInJump((PDWORD)((global::isDevkit) ? 0x8175CD68 : 0x8169CD98), (DWORD)XamLoaderExecuteAsyncChallengeHook, FALSE);
		
		return TRUE;
	}
}

//xbox::utilities::patchInJump((PDWORD)(xbox::utilities::resolveFunction(MODULE_XAM, 456)), (DWORD)XamExecuteChallenge, false);
//DWORD XamExecuteChallenge(PBYTE Challenge, DWORD ChallengeSize, PBYTE HVSalt, DWORD HVSaltSize, PBYTE ChallengeResponse, DWORD ChallengeResponseSize)
//{
//	RtlZeroMemory(ChallengeResponse, ChallengeResponseSize);

//	if ((ChallengeSize & 0xFFFFFFFF) > 0x11F)
//	{
//		DWORD Zeros = (DWORD)ChallengeSize + 0xFFFU & 0xFFFFF000;
//		if ((Zeros - 0x01 & Zeros) != NULL)
//		{
//			DWORD LeadingZeros = _CountLeadingZeros(Zeros);
//			Zeros = (UINT)(0x01 << 0x20 - LeadingZeros);
//		}

//		if (Zeros < 0x10001)
//		{
//			PVOID ChallengeFromServer = XPhysicalAlloc(0x100, MAXULONG_PTR, NULL, PAGE_READWRITE);
//			ZeroMemory(ChallengeFromServer, 0x100);

//			XKEC_REQUEST Request = { 0 };
//			XKEC_RESPONSE Response = { 0 };

//			xbox::utilities::setMemory(Request.Salt, HVSalt, 0x10);
//			xbox::utilities::setMemory(Request.SessionToken, global::g_pSessionToken, 0x14);
//			xbox::utilities::setMemory(Request.CPUKey, global::challenge::cpukey, 0x10);
//			xbox::utilities::setMemory(Request.KVCPUKey, xbox::utilities::data::cpuKey, 0x10);
//			xbox::utilities::setMemory(Request.partnumber, &xbox::utilities::data::buffer.ConsoleCertificate.ConsolePartNumber, 0x0B);
//			xbox::utilities::setMemory(Request.kvsignature, &xbox::utilities::data::buffer.ConsoleCertificate.Signature, 0x100);

//			Request.Crl = xbox::utilities::data::crl != 0 ? TRUE : FALSE;
//			Request.Fcrt = xbox::utilities::data::fcrtRequired != 0 ? TRUE : FALSE;

//			if (Process(COMMAND_XKEC, &Request, sizeof(XKEC_REQUEST), &Response, sizeof(XKEC_RESPONSE), FALSE))
//			{
//				if (Authenticated = (Response.Status == 0x4A000000))
//				{
//					if (!Receive(ChallengeFromServer, 0x100))
//						HalReturnToFirmware(HalRebootQuiesceRoutine);

//					PXE_KEYS_BUFFER buff = (PXE_KEYS_BUFFER)ChallengeFromServer;
//					XBLAPI::XKE::FillBuffer((PBYTE)ChallengeFromServer, xbox::utilities::data::crl, xbox::utilities::data::fcrtRequired, xbox::utilities::data::type1KV, xbox::utilities::data::updSeqFlags, xbox::utilities::data::cpuKey, buff->HvECCDigest, buff->HvCertificate, buff->HvDigest, (PBYTE)&xbox::utilities::data::buffer);

//					memcpy(ChallengeResponse, (PBYTE)ChallengeFromServer + 0x20, 0xE0);
//					XPhysicalFree(ChallengeFromServer);
//				}
//				else HalReturnToFirmware(HalRebootQuiesceRoutine);
//			}
//			else HalReturnToFirmware(HalRebootQuiesceRoutine);

//			if (!global::challenge::hasChallenged)
//			{
//				xbox::utilities::data::crl = TRUE;
//				xbox::utilities::data::hvStatusFlags = (xbox::utilities::data::crl) ? (xbox::utilities::data::hvStatusFlags | 0x10000) : xbox::utilities::data::hvStatusFlags;
//				global::challenge::hasChallenged = TRUE;
//				xbox::utilities::XNotifyUI(XNOTIFYUI_TYPE_PREFERRED_REVIEW, L"Your Connected to Live");
//			}

//			Disconnect();

//			goto Lab;
//		}

//	Lab:
//		*(PSHORT)(ChallengeResponse + 0xF8) = XboxKrnlVersion->Major;
//		*(PSHORT)(ChallengeResponse + 0xFA) = XboxKrnlVersion->Minor;
//		*(PSHORT)(ChallengeResponse + 0xFC) = XboxKrnlVersion->Build;
//		*(PSHORT)(ChallengeResponse + 0xFE) = XboxKrnlVersion->Qfe;

//		if (XeKeysHmacSha(XEKEY_ROAMABLE_OBFUSCATION_KEY, (PBYTE)"XBox 360 (C) Microsoft", 0x17, HVSalt, HVSaltSize, NULL, NULL, ChallengeResponse + 0xE4, 0x14) != ERROR_SUCCESS)
//		{
//			HalReturnToFirmware(HalRebootQuiesceRoutine);
//		}

//		*(PDWORD)(ChallengeResponse + 0xE0) = KeTimeStampBundle->TickCount;
//	}

//	return ERROR_SUCCESS;
//}

//DWORD XeKeysExecuteHook(PBYTE Buffer, DWORD Size, PBYTE HvSalt, PVOID r6, PVOID r7, PVOID r8) {
//	XKEC_REQUEST Request = { 0 };
//	XKEC_RESPONSE Response = { 0 };
//
//	BYTE CPUKey[0x10];
//	xbox::utilities::getCPUKey(CPUKey);
//	if (CPUKey[5] != global::challenge::cpukey[5])
//		goto Failed;
//
//	xbox::utilities::setMemory(Request.Salt, HvSalt, 0x10);
//	xbox::utilities::setMemory(Request.SessionToken, global::g_pSessionToken, 0x14);
//	xbox::utilities::setMemory(Request.CPUKey, global::challenge::cpukey, 0x10);
//	xbox::utilities::setMemory(Request.KVCPUKey, xbox::utilities::data::cpuKey, 0x10);
//	xbox::utilities::setMemory(Request.partnumber, &xbox::utilities::data::buffer.ConsoleCertificate.ConsolePartNumber, 0x0B);
//	xbox::utilities::setMemory(Request.kvsignature, &xbox::utilities::data::buffer.ConsoleCertificate.Signature, 0x100);
//
//	Request.Crl = xbox::utilities::data::crl != 0 ? TRUE : FALSE;
//	Request.Fcrt = xbox::utilities::data::fcrtRequired != 0 ? TRUE : FALSE;
//
//	if (Process(COMMAND_XKEC, &Request, sizeof(XKEC_REQUEST), &Response, sizeof(XKEC_RESPONSE), FALSE)) {
//		if (Authenticated = (Response.Status == 0x4A000000)) {
//			memset(Buffer, 0, Size);
//			if (!Receive(Buffer, 0x100))
//				goto Failed;
//
//			if (Buffer[0x28] != 0x4E) {
//				xbox::utilities::setLiveBlock(TRUE);
//				goto Failed;
//			}
//			PXE_KEYS_BUFFER buff = (PXE_KEYS_BUFFER)Buffer;
//			XBLAPI::XKE::FillBuffer(Buffer, xbox::utilities::data::crl, xbox::utilities::data::fcrtRequired, xbox::utilities::data::type1KV, xbox::utilities::data::updSeqFlags, xbox::utilities::data::cpuKey, buff->HvECCDigest, buff->HvCertificate, buff->HvDigest, (PBYTE)&xbox::utilities::data::buffer);
//		}
//		else goto Failed;
//	}
//	else goto Failed;
//
//	if (!global::challenge::hasChallenged) {
//		xbox::utilities::data::crl = TRUE;
//		xbox::utilities::data::hvStatusFlags = (xbox::utilities::data::crl) ? (xbox::utilities::data::hvStatusFlags | 0x10000) : xbox::utilities::data::hvStatusFlags;
//		global::challenge::hasChallenged = TRUE;
//		xbox::utilities::XNotifyUI(XNOTIFYUI_TYPE_PREFERRED_REVIEW, L"Your Connected to Live");
//	}
//
//	Disconnect();
//	Sleep(13000);
//	return S_OK;
//Failed:
//	xbox::utilities::setLiveBlock(TRUE);
//	Disconnect();
//	Sleep(2000);
//	HalReturnToFirmware(HalRebootQuiesceRoutine);
//	return E_FAIL;
//}*/



//*(WORD*)0x8E038600 = xbox::utilities::data::bldrFlags;
//*(WORD*)0x8E038602 = xbox::utilities::data::buffer.GameRegion;
//*(WORD*)0x8E038604 = xbox::utilities::data::buffer.OddFeatures;

//if (xbox::utilities::patchModuleImport(MODULE_XAM, MODULE_KERNEL, 404,		(DWORD)xbox::hooks::XenonPrivilegeHook) != S_OK) return FALSE;
//xbox::utilities::patchInJump((PDWORD)(xbox::utilities::resolveFunction(MODULE_XAM, 0x212)), (DWORD)xbox::hooks::XexLiveGoldHook, false);


////xbox::utilities::writeFile("Client:\\Buffer02.bin", Buffer, 0x100);
////=======================================================================================================
//typedef struct {
//XEKEYS_EXEC_HEADER header = (XEKEYS_EXEC_HEADER)buff->header;								//	XEKEYS_EXEC_HEADER header; //0x0			
//buff->result				= 0x0000000000000000;											//	QWORD result; //0x20
//buff->HvMagic				= 0x4E4E;														//	WORD HvMagic; //0x28
//buff->HvVersion				= 0x4497;														//	WORD HvVersion; //0x2A
//buff->HvQfe					= 0x0000;														//	WORD HvQfe; //0x2C
//buff->BldrFlags				= xbox::utilities::data::bldrFlags;								//	WORD BldrFlags; //0x2E
//buff->BaseKernelVersion		= 0x07600000;													//	DWORD BaseKernelVersion; //0x30
//buff->UpdateSequence		= xbox::utilities::data::updSeqFlags;							//	DWORD UpdateSequence; //0x34
//buff->HvStatusFlags			= xbox::utilities::data::hvStatusFlags;							//	DWORD HvStatusFlags; //0x38
//buff->ConsoleTypeSeqAllow	= xbox::utilities::data::ConsoleTypeSeqAllow;					//	DWORD ConsoleTypeSeqAllow; //0x3C
//buff->RTOC					= 0x0000000200000000;									    	//	QWORD RTOC; //0x40
//buff->HRMOR					= 0x0000010000000000;											//	QWORD HRMOR; //0x48
//	BYTE HvECCDigest[XECRYPT_SHA_DIGEST_SIZE]; //0x50
//memcpy(buff->CpuKeyDigest, xbox::utilities::data::cpuKeyDigest, XECRYPT_SHA_DIGEST_SIZE);	//	BYTE CpuKeyDigest[XECRYPT_SHA_DIGEST_SIZE]; //0x64
//	BYTE HvCertificate[0x80]; //0x78
//	WORD hvExAddr; //0xF8
//	BYTE HvDigest[0x6]; //0xFA
//} XE_KEYS_BUFFER, * PXE_KEYS_BUFFER;
////xbox::utilities::writeFile("Client:\\Buffer03.bin", Buffer, 0x100);

//DWORD ver = ((XboxKrnlVersion->Major & 0xF) << 28) | ((XboxKrnlVersion->Minor & 0xF) << 24) | (XboxKrnlVersion->Build << 8) | (XboxKrnlVersion->Qfe);
////xbox::utilities::DbgOut("[xblh] ver: %04X\n", ver);

////xbox::utilities::DbgOut("[xblh] Major:	%02X\n", XboxKrnlVersion->Major);
////xbox::utilities::DbgOut("[xblh] Minor:	%02X\n", XboxKrnlVersion->Minor);
////xbox::utilities::DbgOut("[xblh] Build:	%02X\n", XboxKrnlVersion->Build);
////xbox::utilities::DbgOut("[xblh] Qfe:	%02X\n", XboxKrnlVersion->Qfe);


//executionId.MediaID			= 0;
//executionId.PublisherID		= 0;
//executionId.GameID			= 0;
//executionId.Platform		= 0;
//executionId.ExecutableType	= 0;
//executionId.DiscNum			= 0;
//executionId.DiscsInSet		= 0;
//executionId.SaveGameID		= 0;

//DWORD ver = ((XboxKrnlVersion->Major & 0xF) << 28) | ((XboxKrnlVersion->Minor & 0xF) << 24) | ((XboxKrnlVersion->Build << 8) | (XboxKrnlVersion->Qfe);
//global::challenge::executionId.Version = ver;
//global::challenge::executionId.BaseVersion = ver;
//global::challenge::executionId.TitleID = 0xFFFE07D1;




//if (XamGetCurrentTitleId() == 0xFFFE07D1) {
//	PLDR_DATA_TABLE_ENTRY dashHandle = (PLDR_DATA_TABLE_ENTRY)GetModuleHandle("dash.xex");
//	XEX_EXECUTION_ID* pExecutionId = (XEX_EXECUTION_ID*)RtlImageXexHeaderField(dashHandle->XexHeaderBase, 0x00040006);
//	memcpy(&global::challenge::XOSC::xexExecutionId, pExecutionId, 0x18);
//	global::challenge::XOSC::titleId = pExecutionId->TitleID;
//	XeCryptSha((PBYTE)&global::challenge::XOSC::AllowedMediaTypes::dash, 0x4D6C, global::challenge::securityDigest_krnl, 0x14, global::challenge::smcOut, 0x5, global::challenge::securityDigest, 0x14);
//	global::challenge::unknownBuffer[0xE] &= 0xF8;

//	memcpy(global::challenge::securityDigest0, (byte*)xbox::utilities::data::keyvaultDigest, 0x14);
//	xbox::utilities::writeFile(xbox::utilities::va("Client:\\securityDigest00.bin").c_str(), global::challenge::securityDigest0, 0x14);

//	XeCryptSha((PBYTE)&global::challenge::XOSC::AllowedMediaTypes::XAM, 0x2D94, global::challenge::securityDigest0, 0x14, global::challenge::unknownBuffer, 0x10, global::challenge::securityDigest_xam, 0x14);
//	xbox::utilities::writeFile(xbox::utilities::va("Client:\\securityDigest_xam.bin").c_str(), global::challenge::securityDigest_xam, 0x14);

//	XeCryptSha((PBYTE)&global::challenge::XOSC::AllowedMediaTypes::krnl, 0x20, global::challenge::securityDigest_xam, 0x14, global::challenge::spoofedMacAddress, 0x6, global::challenge::securityDigest_krnl, 0x14);
//	xbox::utilities::writeFile(xbox::utilities::va("Client:\\securityDigest_krnl.bin").c_str(), global::challenge::securityDigest_krnl, 0x14);

//	BYTE smcMsg[5] = { 0x12, 0x41, 0x02, 0x03, 0x00 };
//	memcpy(global::challenge::smcOut, smcMsg, 0x5);

//	XeCryptSha((PBYTE)&global::challenge::XOSC::AllowedMediaTypes::dash, 0x4D6C, global::challenge::securityDigest_krnl, 0x14, global::challenge::smcOut, 0x5, global::challenge::securityDigest, 0x14);
//	xbox::utilities::writeFile(xbox::utilities::va("Client:\\securityDigest00.bin").c_str(), global::challenge::securityDigest, 0x14);
//	
//	xbox::utilities::writeFile(xbox::utilities::va("Client:\\TitleDigest.bin").c_str(), TitleDigest, 0x14);
//}



//BOOL InitializeSystemHooks() {
//	if (global::isDevkit) XboxKrnlVersion->Build = 17995;


//	// Setup our static execution id
//	DWORD ver = ((XboxKrnlVersion->Major & 0xF) << 28) | ((XboxKrnlVersion->Minor & 0xF) << 24) | (XboxKrnlVersion->Build << 8) | (XboxKrnlVersion->Qfe);
//	global::challenge::executionId.Version = ver;
//	global::challenge::executionId.BaseVersion = ver;
//	global::challenge::executionId.TitleID = 0xFFFE07D1;

//	if (xbox::utilities::patchModuleImport(MODULE_XAM, MODULE_KERNEL, 0x12B,	(DWORD)RtlImageXexHeaderFieldHook) != S_OK) { //xbox::utilities::DbgOut("[xblh] 5: 125 -1\n");  return FALSE; }
//	if (xbox::utilities::patchModuleImport(MODULE_XAM, MODULE_KERNEL, 0x194,	(DWORD)xbox::hooks::XenonPrivilegeHook) != S_OK) { //xbox::utilities::DbgOut("[xblh] 5: 128 -1\n");  return FALSE; }
//	if (xbox::utilities::patchModuleImport(MODULE_XAM, MODULE_KERNEL, 0x198,	(DWORD)xbox::hooks::XexLoadExecutableHook) != S_OK) { //xbox::utilities::DbgOut("[xblh] 5: 160 -1\n");  return FALSE; }
//	if (xbox::utilities::patchModuleImport(MODULE_XAM, MODULE_KERNEL, 0x199,	(DWORD)xbox::hooks::XexLoadImageHook) != S_OK) { //xbox::utilities::DbgOut("[xblh] 5: 165 -1\n");  return FALSE; }

//	if (xbox::utilities::patchModuleImport(MODULE_XAM, MODULE_KERNEL, 0x25F,	(DWORD)XeKeysExecuteHook) != S_OK) { //xbox::utilities::DbgOut("[xblh] 5: 185 -1\n");  return FALSE; }

//	xbox::utilities::patchInJump((PDWORD)(xbox::utilities::resolveFunction(MODULE_XAM, 0x212)), (DWORD)xbox::hooks::XexLiveGoldHook, false);
//	xbox::utilities::patchInJump((PDWORD)((global::isDevkit) ? 0x8175CD68 : 0x8169CD98), (DWORD)XamLoaderExecuteAsyncChallengeHook, FALSE);

//	return TRUE;
//}

//xbox::utilities::setMemory(pbBuffer + 0x50, xbox::utilities::data::cpuKeyDigest, 0x10);
//XeCryptSha((PBYTE)(0x90010000 | *(PWORD)(Address - 0x62)), *(PWORD)(Address - 0x66), TitleDigest, 0x14, 0, 0, pbBuffer + 0x60, 0x10);
//(pbBuffer + 0x60)[0] = 7;


//if (xbox::utilities::PatchModuleImport(MODULE_XAM, MODULE_KERNEL, 0x1F,	(DWORD)XeKeysGetConsoleCertificate2, FALSE) != ERROR_SUCCESS) return FALSE;
//if (xbox::utilities::PatchModuleImport(MODULE_XAM, MODULE_KERNEL, 0x19C,	(DWORD)XexPcToFileHeaderHook, FALSE) != ERROR_SUCCESS) { //xbox::utilities::DbgOut("[xblh] 5: 180 -1\n");  return FALSE; }
//HANDLE XexPcToFileHeaderHook(PVOID Address, PLDR_DATA_TABLE_ENTRY* Handle) {
//	DWORD ImageBase = *(PDWORD)((PLDR_DATA_TABLE_ENTRY)Handle)->ImageBase;
//	DWORD FullImageSize = *(PDWORD)((PLDR_DATA_TABLE_ENTRY)Handle)->SizeOfFullImage; 
//	if (*(PDWORD)Address >= ImageBase && *(PDWORD)Address <= (ImageBase + FullImageSize) || *(PDWORD)Address == *(PDWORD)xbox::utilities::resolveFunction(MODULE_KERNEL, 0x19C)){
//		return nullptr;
//	}

//	return XexPcToFileHeader(Address, Handle);
//}

//char szCert[] = {
//	 0x01, 0xA8, 0x07, 0x36, 0x5E, 0xE8, 0x00, 0x58, 0x38, 0x31, 0x37, 0x31, 0x37, 0x39,
//	 0x2D, 0x30, 0x30, 0x31, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02,
//	 0x30, 0x37, 0x2D, 0x30, 0x36, 0x2D, 0x30, 0x38, 0x00, 0x01, 0x00, 0x01, 0xB4, 0x3B,
//	 0x50, 0xD2, 0x3C, 0x72, 0x35, 0xD1, 0xEC, 0x09, 0x25, 0xEA, 0xF6, 0xB3, 0x39, 0xF7,
//	 0xD5, 0x3C, 0xBD, 0xFE, 0x88, 0x5F, 0x31, 0xC5, 0xC5, 0x6B, 0x5D, 0xF8, 0x5B, 0xA2,
//	 0x1C, 0xB9, 0x09, 0x33, 0x87, 0x6E, 0x24, 0x0F, 0xDD, 0x6F, 0xC3, 0x61, 0x01, 0x22,
//	 0x1C, 0x46, 0xB0, 0xF4, 0x71, 0x66, 0xC7, 0xD7, 0x4F, 0x17, 0xDB, 0x09, 0xF6, 0xDD,
//	 0x02, 0x1D, 0xFB, 0x13, 0x75, 0x91, 0x43, 0x24, 0xE2, 0x58, 0x23, 0xC6, 0x59, 0x26,
//	 0xB9, 0xCE, 0x65, 0x0C, 0x07, 0xC0, 0x3D, 0xC3, 0xA9, 0xBE, 0xF4, 0x81, 0x8E, 0x4C,
//	 0x34, 0x1B, 0x14, 0x1B, 0x69, 0x4C, 0x88, 0xF6, 0xD2, 0x0D, 0x19, 0x70, 0x25, 0x79,
//	 0x9E, 0x4F, 0x8C, 0x5B, 0xEC, 0xC5, 0x64, 0x58, 0x50, 0x3B, 0x1D, 0xA8, 0x65, 0xDB,
//	 0x49, 0x8F, 0x52, 0xA1, 0x2D, 0xCD, 0xC7, 0x3E, 0x8C, 0xB6, 0x6D, 0x2A, 0x64, 0x87,
//	 0xAE, 0x6E, 0xDC, 0x00, 0xC2, 0xB7, 0x59, 0x64, 0xFD, 0x52, 0xF7, 0xD4, 0xD0, 0x15,
//	 0xDC, 0x1B, 0x98, 0x3C, 0xEA, 0x8F, 0x7F, 0xCD, 0x2E, 0x00, 0xC8, 0x5C, 0x6F, 0x53,
//	 0x2A, 0x1D, 0x6E, 0x74, 0xC3, 0xA2, 0x86, 0x34, 0xF7, 0x3A, 0x41, 0x64, 0x41, 0x1C,
//	 0xD8, 0x34, 0x5E, 0x6A, 0x35, 0xF7, 0x40, 0x9B, 0x56, 0xB6, 0x02, 0x16, 0xBD, 0xDA,
//	 0x56, 0x4B, 0x9D, 0x98, 0xCB, 0x51, 0xC0, 0xD2, 0xD3, 0xA4, 0xF3, 0x72, 0x8E, 0x97,
//	 0x7B, 0x54, 0x8F, 0x13, 0x21, 0x76, 0x86, 0x24, 0x28, 0x53, 0x65, 0xD9, 0xBF, 0x95,
//	 0xFF, 0x31, 0x66, 0x1F, 0x88, 0x8B, 0x14, 0x3F, 0x95, 0x3F, 0x5E, 0x12, 0x98, 0xA5,
//	 0x9A, 0x46, 0x41, 0x51, 0x9E, 0x64, 0x4C, 0xCD, 0xDC, 0xC0, 0x52, 0x24, 0xC7, 0x90,
//	 0x72, 0x48, 0x27, 0x67, 0xC1, 0xC6, 0x44, 0xCC, 0x3F, 0x5F, 0xF7, 0x0D, 0x96, 0x27,
//	 0x75, 0xCF, 0x1D, 0x7F, 0x76, 0xBA, 0xCD, 0xCC, 0x57, 0xE5, 0xA3, 0x15, 0xE7, 0xBC,
//	 0xA5, 0x6E, 0x0C, 0xBC, 0xEA, 0xB4, 0xBB, 0x45, 0x3D, 0x7D, 0xA1, 0x28, 0xE7, 0x31,
//	 0x59, 0x3E, 0x9A, 0x78, 0x33, 0x41, 0x00, 0x61, 0x4E, 0x1F, 0x7B, 0x78, 0x68, 0x66,
//	 0x03, 0x0E, 0x90, 0x9D, 0x47, 0xBC, 0xBA, 0xBD, 0x9B, 0x39, 0x15, 0x3C, 0x7B, 0xDD,
//	 0x98, 0x9C, 0x21, 0xCD, 0xB8, 0x28, 0x90, 0x2B, 0x2C, 0x93, 0x2C, 0xF3, 0x64, 0x6E,
//	 0x26, 0x08, 0x6A, 0x7C, 0xD9, 0x3F, 0x27, 0x1D, 0x22, 0x3C, 0x20, 0x31, 0xC2, 0x78,
//	 0x30, 0xFB, 0x39, 0xDC, 0x33, 0xE5, 0x90, 0x67, 0xDC, 0x05, 0x4A, 0x9B, 0xE5, 0xAE,
//	 0x4A, 0x6C, 0x4C, 0x7F, 0xFC, 0x07, 0x73, 0x8A, 0xF7, 0xF3, 0xD6, 0xC3, 0xC7, 0xE0,
//	 0xAF, 0x42, 0x2D, 0x8F, 0xD0, 0xDE, 0xFA, 0xFB, 0xD0, 0x5E, 0xB8, 0x55, 0x08, 0x77,
//	 0x2F, 0xB5, 0x35, 0x26
//};

//void XeKeysGetConsoleCertificate2(char* oszCert) 
//{
//	memcpy(oszCert, szCert, 0x1A8);
//}

//typedef PVOID(*pMmDbgReadCheck)(PVOID VirtualAddress);
//pMmDbgReadCheck org_mmDbgReadCheck = (pMmDbgReadCheck)xbox::utilities::resolveFunction(MODULE_KERNEL, 427);

//PVOID mmDbgReadCheck(PVOID VirtualAddress)
//{
//	//if (((DWORD)VirtualAddress & 0xFFFFFFF0) == 0x800817F0) // so they cant undo this hook ;)
//	//	return NULL;
//	if (((DWORD)VirtualAddress & 0xFF000000) == 0x80000000) // so they cant see kernel and cant undo this hook
//		return NULL;
//	else if (((DWORD)VirtualAddress & 0xFF000000) == 0x8E000000) // so they cant see security cache
//		return NULL;
//	else if (((DWORD)VirtualAddress & 0xFFF00000) == (DWORD)((PLDR_DATA_TABLE_ENTRY)global::modules::client)->ImageBase) // so they cant read our xex in memory
//		return NULL;

//	return org_mmDbgReadCheck(VirtualAddress);
//}

//if (xbox::utilities::PatchModuleImport(MODULE_XAM, MODULE_KERNEL, 0x1AB,    (DWORD)mmDbgReadCheck, FALSE) != ERROR_SUCCESS) return FALSE;
//xbox::utilities::PatchModuleImport("xbdm.xex", MODULE_KERNEL, 0x1AB, (DWORD)mmDbgReadCheck,			FALSE);
//xbox::utilities::PatchModuleImport("xbdm.xex", MODULE_KERNEL, 0x19C, (DWORD)XexPcToFileHeaderHook,	FALSE);

//xbox::utilities::patchInJump((PDWORD)(xbox::utilities::resolveFunction(MODULE_XAM, 0x1F)), (DWORD)XeKeysGetConsoleCertificate2, FALSE);

		//*(QWORD*)(pbBuffer + 0x08) = (0x1BD + (xbox::utilities::data::type1KV ? 0 : 2));
		//*(DWORD*)(pbBuffer + 0x44) = XamGetCurrentTitleId(); //0xFFFE07D1;

		//memcpy(pbBuffer + 0x50, xbox::utilities::data::cpuKeyDigest, 0x10);
		//memcpy(pbBuffer + 0x70, xbox::utilities::data::XOSCHash, 0x10);
		//memset(pbBuffer + 0x84, 0, 0x4);

		//*(DWORD*)(pbBuffer + 0x88) = XamGetCurrentTitleId(); //0xFFFE07D1;
		//*(BYTE*)(pbBuffer + 0x83) = xbox::utilities::data::buffer.XeikaCertificate.Data.OddData.PhaseLevel;

		//memcpy(pbBuffer + 0xF0, &xbox::utilities::data::buffer.XeikaCertificate.Data.OddData.InquiryData, 0x24);
		//memcpy(pbBuffer + 0x114, &xbox::utilities::data::buffer.XeikaCertificate.Data.OddData.InquiryData, 0x24);

		//*(WORD*)(pbBuffer + 0x148) = xbox::utilities::data::buffer.GameRegion;
		//*(WORD*)(pbBuffer + 0x14A) = xbox::utilities::data::buffer.OddFeatures;
		//*(DWORD*)(pbBuffer + 0x150) = xbox::utilities::data::buffer.PolicyFlashSize;
		//*(DWORD*)(pbBuffer + 0x1D0) = xbox::utilities::data::DXOSC;

		//BYTE SecurityDigest[0x10];
		//memcpy(SecurityDigest, pbBuffer + 0x60, 0x10);
		//xbox::utilities::writeFile("Client:\\pbBuffer01.bin", pbBuffer, 0x2E0);