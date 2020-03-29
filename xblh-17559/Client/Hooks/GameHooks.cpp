#include "../stdafx.h"
#include "../Tools/Utilities.h"
#include "../Tools/Hooks.h"
#include "GameHooks.h"
#include <xbdm.h>
#include <time.h> 

extern SOCKET servSock;
extern TDxSocket* TDxSocketc;
extern BOOL DashLoaded;


DWORD nop = 0x60000000;
DWORD other = 0x38600001;
BYTE Color2[0x04] = { 0xFF, 0x66, 0x00, 0x66 };//purple
BYTE Background[0x04] = { 0xFF, 0x39, 0x39, 0x39 };//background Colors

void* HandleExists(const char* OriginalPE)
{
	PLDR_DATA_TABLE_ENTRY DataTableEntry = (PLDR_DATA_TABLE_ENTRY)GetModuleHandleA("xboxkrnl.exe");
	PXEX_HEADER_STRING String;
	DataTableEntry = (PLDR_DATA_TABLE_ENTRY)DataTableEntry->InLoadOrderLinks.Flink;
	while (DataTableEntry != 0)
	{
		String = (PXEX_HEADER_STRING)RtlImageXexHeaderField(DataTableEntry->XexHeaderBase, 0x183FF);
		if ((String != 0) && (String->Data[0] != 0))
		{
			if (stricmp((char*)String->Data, OriginalPE) == 0)
			{
				return (void*)DataTableEntry;
			}
		}
		DataTableEntry = (PLDR_DATA_TABLE_ENTRY)DataTableEntry->InLoadOrderLinks.Flink;
	}
	return ((void*)-1);
}

void WriteToResource(const char* OriginalPE, char* Section, unsigned long Offset, unsigned char* Bytes)
{
	if (HandleExists(OriginalPE) != ((void*)-1))
	{
		void* SectionData = 0;
		unsigned long SectionSize = 0;
		if (XGetModuleSection(HandleExists(OriginalPE), Section, &SectionData, &SectionSize))
		{
			unsigned long Address = (unsigned long)SectionData + Offset;
			memcpy((void*)Address, Bytes, sizeof(unsigned long));
		}
	}
}
//
BYTE ARGB[0x04] = { 0xFF, 0x66, 0x00, 0x66 };
bool InitializedCheats = false;
VOID InitializeGameHooks(PLDR_DATA_TABLE_ENTRY ModuleHandle) {
	if (wcscmp(ModuleHandle->BaseDllName.Buffer, L"dash.xex") == 0) 
	{
		xbox::utilities::DbgOut("[xblh] dash loaded \n");
		DashLoaded = TRUE;

		xbox::utilities::patchModuleImport(ModuleHandle, MODULE_XAM, 205, (DWORD)xbox::hooks::NetDll_XHttpConnectHook);
		xbox::hooks::XHTTPHOOK();

		if (global::seting::UseSetDashUI == TRUE) {
			xbox::System::patching::SetDashUI();
			WriteToResource("dash.exe", "dashuisk", 0x7828, ARGB);
		}
	} else if (wcscmp(ModuleHandle->BaseDllName.Buffer, L"xshell.xex") == 0)
		DashLoaded = TRUE;

	if (DashLoaded) {
		xbox::utilities::patchModuleImport(ModuleHandle, MODULE_KERNEL, 407, (DWORD)xbox::hooks::XexGetProcedureAddressHook);
		xbox::utilities::patchModuleImport(ModuleHandle, MODULE_KERNEL, 408, (DWORD)xbox::hooks::XexLoadExecutableHook);
		xbox::utilities::patchModuleImport(ModuleHandle, MODULE_KERNEL, 409, (DWORD)xbox::hooks::XexLoadImageHook);
		xbox::utilities::patchModuleImport(ModuleHandle, MODULE_KERNEL, 404, (DWORD)xbox::hooks::XenonPrivilegeHook);

		xbox::utilities::patchModuleImport(ModuleHandle, MODULE_XAM, 530, (DWORD)xbox::hooks::XexLiveGoldHook);
		xbox::utilities::patchModuleImport(ModuleHandle, MODULE_XAM, 535, (DWORD)xbox::hooks::HookXamUserGetMembershipTierFromXUID);
		xbox::utilities::patchModuleImport(ModuleHandle, MODULE_XAM, 539, (DWORD)xbox::hooks::HookXamUserGetMembershipTier);
		
		xbox::utilities::patchModuleImport(ModuleHandle, MODULE_XAM, 604, (DWORD)xbox::hooks::XamContentCreateEnumerator2);
		xbox::utilities::patchModuleImport(ModuleHandle, MODULE_XAM, 551, (DWORD)xbox::hooks::XamUserGetSigninInfo2);


		if (wcscmp(ModuleHandle->BaseDllName.Buffer, L"hud.xex") == 0) {
			//xbox::utilities::DbgOut("[xblh] HUD loaded \n");
			//xbox::System::patching::SetHUDUI();
		}
		else if (wcscmp(ModuleHandle->BaseDllName.Buffer, L"dash.social.lex") == 0) {
			//xbox::utilities::DbgOut("[xblh] dash.socia.lex loaded \n");
			if (global::seting::UseSetDashUI == TRUE) {
				/* Social Online*/
				xbox::utilities::ComparePointerWrite(0x9AFC4876, 0xFF660066);
			}
		}
		else if (wcscmp(ModuleHandle->BaseDllName.Buffer, L"dash.mp.contentexplorer.lex") == 0) {
			//xbox::utilities::DbgOut("[xblh] dash.mp.contentexplorer.lex loaded \n");
			if (global::seting::UseSetDashUI == TRUE) {
				/*Purchase Games Buttons*/
				xbox::utilities::ComparePointerWrite(0x9B111169, 0xFF660066);
				xbox::utilities::ComparePointerWrite(0x9B11CBB8, 0xFF660066);
				xbox::utilities::ComparePointerWrite(0x9B11DFCF, 0xFF660066);
				xbox::utilities::ComparePointerWrite(0x9B11F133, 0xFF660066);
				xbox::utilities::ComparePointerWrite(0x9B11F31A, 0xFF660066);
				xbox::utilities::ComparePointerWrite(0x9B120CF0, 0xFF660066);
				xbox::utilities::ComparePointerWrite(0x9B120F1C, 0xFF660066);
				xbox::utilities::ComparePointerWrite(0x9B121556, 0xFF660066);
				xbox::utilities::ComparePointerWrite(0x9B1224FA, 0xFF660066);
				xbox::utilities::ComparePointerWrite(0x9B12271F, 0xFF660066);
				xbox::utilities::ComparePointerWrite(0x9B1243C7, 0xFF660066);
				xbox::utilities::ComparePointerWrite(0x9B124609, 0xFF660066);
			}
		}

		XEX_EXECUTION_ID* pExecutionId = (XEX_EXECUTION_ID*)RtlImageXexHeaderField(ModuleHandle->XexHeaderBase, 0x00040006);
		if (pExecutionId != 0) {
			DWORD TitleID = pExecutionId->TitleID;
			DWORD dwVersion = (pExecutionId->Version >> 8) & 0xFF;
			xbox::utilities::DbgOut("[xblh] %S loaded TitleID: %04X dwVersion: %04X\n", ModuleHandle->BaseDllName.Buffer, TitleID, dwVersion);

			if (TitleID == HomeGTAV && dwVersion != 0) 
			{
				xbox::utilities::ComparePointerWrite(0x82C8B3B0, 0x60000000);
				xbox::utilities::ComparePointerWrite(0x838BFFF8, 0x60000000);
			}
			else if (TitleID == HomeBO2 && dwVersion != 0)
			{

				if (global::seting::UseBYPASSBO2) {
					//xbox::utilities::XNotifyUI(XNOTIFYUI_TYPE_PREFERRED_REVIEW, L"[XBLH] Bo2!!!");
					xbox::utilities::DbgOut("[xblh] Bo2 loaded TitleID: %04X dwVersion: %04X\n", ModuleHandle->BaseDllName.Buffer, TitleID, dwVersion);

					xbox::hooks::GenerateRandomValues(ModuleHandle);

					//// Apply our bypass
					//xbox::utilities::patchModuleImport(ModuleHandle, MODULE_XAM, 64, (DWORD)xbox::hooks::NetDll_XNetXnAddrToMachineIdHook);
					//xbox::utilities::patchModuleImport(ModuleHandle, MODULE_XAM, 73, (DWORD)xbox::hooks::NetDll_XNetGetTitleXnAddrHook);
					//xbox::utilities::patchModuleImport(ModuleHandle, MODULE_KERNEL, 405, (DWORD)xbox::hooks::XexGetModuleHandleHook);
					//xbox::utilities::patchModuleImport(ModuleHandle, MODULE_KERNEL, 580, (DWORD)xbox::hooks::XeKeysGetKeyHook);
					//xbox::utilities::patchModuleImport(ModuleHandle, MODULE_KERNEL, 582, (DWORD)xbox::hooks::XeKeysGetConsoleIDHook);

					if (wcscmp(ModuleHandle->BaseDllName.Buffer, L"default.xex") == 0) {
						xbox::utilities::ComparePointerWrite(0x824A7CB8, 0x60000000); // Disables CRC32_Split hash // Bypass 2 - Unbannable for 2 weeks and counting // spPatch4BO2
						xbox::utilities::ComparePointerWrite(0x82320F60, 0x38600000); // xbdm check
					}
					else if (wcscmp(ModuleHandle->BaseDllName.Buffer, L"default_mp.xex") == 0) {
						if (global::isDevkit)
							xbox::utilities::ComparePointerWrite(0x8228CF80, 0x48000018); // Didn't need to hide this, but it would have stuck out like a sore thumb that we were doing something fishy //mpPatch4BO2
						xbox::utilities::ComparePointerWrite(0x823C1D70, 0x38600000); // xbdm check
						xbox::utilities::ComparePointerWrite(0x8259A65C, 0x60000000); // Disables CRC32_Split hash // mpPatch5BO2
						*(int*)0x8259A65C = 0x60000000;
						*(int*)0x82497EB0 = 0x60000000;
						*(int*)0x825BEA7C = 0x60000000;
						*(int*)0x825C6070 = 0x60000000;
						*(int*)0x824E0DEC = 0x3940331C;
						*(int*)0x82409118 = 0x3900331C;
						*(int*)0x823E3ADC = 0x39400000;
						*(int*)0x823E3E78 = 0x39600000;
					}
				}
			}
			else if (TitleID == 0x415608FC && dwVersion != 0)
			{
				//xbox::utilities::XNotifyUI(XNOTIFYUI_TYPE_PREFERRED_REVIEW, L"[XBLH] GHOSTS!!!");
				xbox::utilities::DbgOut("[xblh] GHOSTS loaded TitleID: %04X dwVersion: %04X\n", ModuleHandle->BaseDllName.Buffer, TitleID, dwVersion);

				// Generate our values
				xbox::hooks::GenerateRandomValues(ModuleHandle);

				if (wcscmp(ModuleHandle->BaseDllName.Buffer, L"default.xex") == 0)
				{
					//xbox::utilities::patchModuleImport(ModuleHandle, MODULE_KERNEL, 405, (DWORD)xbox::hooks::XexGetModuleHandleHook);

					xbox::utilities::setMemory((LPVOID)0x8251174C, 0x48000010);
					xbox::utilities::setMemory((LPVOID)0x82511714, 0x38600000);
					xbox::utilities::setMemory((LPVOID)0x82511720, 0x39600001);
				}
				else if (wcscmp(ModuleHandle->BaseDllName.Buffer, L"default_mp.xex") == 0)
				{
					// This is specific to multiplayer
					xbox::utilities::setMemory((PVOID)0x826276CC, 0x38600000); // disable xbdm flag

					xbox::utilities::setMemory((PVOID)0x82627614, 0x39200009); //mpPatch1Ghosts
					xbox::utilities::setMemory((PVOID)0x8262767C, 0x48000010); //mpPatch2Ghosts
					xbox::utilities::setMemory((PVOID)0x82627628, 0x38600000); //mpPatch3Ghosts
					xbox::utilities::setMemory((PVOID)0x82627634, 0x39600001); //mpPatch4Ghosts

					xbox::utilities::setMemory((PVOID)0x82627684, 0x38600002);
					xbox::utilities::setMemory((PVOID)0x826276D4, 0x48000010);

					*(PBYTE)(0x8259175C + 0x03) = 0x00; //Prevent blacklist in console details

					BYTE test[8] = { 0x89, 0x21, 0x00, 0x50, 0x61, 0x49, 0x00, 0x00 };
					xbox::utilities::setMemory((PVOID)0x82627684, test, 0x08);
					xbox::utilities::setMemory((PVOID)0x826276DC, test, 0x08);
				}
			}
			else if (TitleID == HomeBO3 && dwVersion != 0)
			{
				if (global::seting::UseBYPASSBO3) {

					xbox::utilities::XNotifyUI(XNOTIFYUI_TYPE_PREFERRED_REVIEW, L"[XBLH] Bo3!!!");

					// Generate our values
					xbox::hooks::GenerateRandomValues(ModuleHandle);

					// Apply our bypasses
					xbox::utilities::patchModuleImport(ModuleHandle, MODULE_XAM, 64, (DWORD)xbox::hooks::NetDll_XNetXnAddrToMachineIdHook);
					xbox::utilities::patchModuleImport(ModuleHandle, MODULE_XAM, 73, (DWORD)xbox::hooks::NetDll_XNetGetTitleXnAddrHook);
					xbox::utilities::patchModuleImport(ModuleHandle, MODULE_KERNEL, 405, (DWORD)xbox::hooks::XexGetModuleHandleHook);
					xbox::utilities::patchModuleImport(ModuleHandle, MODULE_KERNEL, 580, (DWORD)xbox::hooks::XeKeysGetKeyHook);
					xbox::utilities::patchModuleImport(ModuleHandle, MODULE_KERNEL, 582, (DWORD)xbox::hooks::XeKeysGetConsoleIDHook);

					if (wcscmp(ModuleHandle->BaseDllName.Buffer, L"default.xex") == 0) {
						xbox::utilities::setMemory((LPVOID)0x8253A5F8, 0x39600000);
						xbox::utilities::setMemory((LPVOID)0x8253A614, 0x48000010);
						xbox::utilities::setMemory((LPVOID)0x8253A60C, 0x38600000);
						xbox::utilities::setMemory((LPVOID)0x8253A618, 0x39600001);
					}
					else if (wcscmp(ModuleHandle->BaseDllName.Buffer, L"default_zm.xex") == 0) {
						xbox::utilities::setMemory((LPVOID)0x82539848, 0x48000010);
						xbox::utilities::setMemory((LPVOID)0x82539840, 0x60000000);
						xbox::utilities::setMemory((LPVOID)0x8253984C, 0x39600001);
					}

					BOOL isSingleplayer = wcscmp(ModuleHandle->BaseDllName.Buffer, L"default.xex") == 0;
					if (isSingleplayer) {
						xbox::utilities::setMemory((LPVOID)0x8253A53C, 0x38600000); // this is really multiplayer but whatever
					}
					else {
						xbox::utilities::setMemory((LPVOID)0x82539774, 0x38600000);
						*(__int64*)0x82332018 = 0x386000014E800020; // TU7/8
					}
				}
			}
		}
	}
}





//BYTE pSalt[0x10];
//xbox::utilities::getCPUKey(pSalt);
//char cpukey[64];
//sprintf(cpukey, "%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X", pSalt[0], pSalt[1], pSalt[2], pSalt[3], pSalt[4], pSalt[5], pSalt[6], pSalt[7], pSalt[8], pSalt[9], pSalt[10], pSalt[11], pSalt[12], pSalt[13], pSalt[14], pSalt[15]);

//CHAR Gamertag[0x10];
//XUSER_SIGNIN_INFO XUserSigninInfo = { 0 };
//if (NT_SUCCESS(XamUserGetSigninInfo(0, 0, &XUserSigninInfo)))
//	memcpy(Gamertag, XUserSigninInfo.szUserName, 0x10);

//TDxSocketc->mysend(servSock, "updatehello|%s|%i|%s", Gamertag, TitleID, cpukey);

//IMAGE_XEX_HEADER* currModuleHeader = (IMAGE_XEX_HEADER*)(ModuleHandle->XexHeaderBase);
//if (currModuleHeader) {
//	XEX_SECURITY_INFO* securityInfo = (XEX_SECURITY_INFO*)(currModuleHeader->SecurityInfo);
//	int size = ((currModuleHeader->SizeOfHeaders - (DWORD)&securityInfo->AllowedMediaTypes) + (int)currModuleHeader);
//	xbox::utilities::writeFile("Client:\\FFFE07D1.bin", (PBYTE)&securityInfo->AllowedMediaTypes, size);
//}
//

//

//LoadAddresses();
//BO2::Hooks::Load_Menu();
//xbox::utilities::patchModuleImport(ModuleHandle, MODULE_KERNEL, 405, (DWORD)XexGetModuleHandleHookGhosts);
//xbox::utilities::notify(L"XeOnline - Ghosts Rekt", 10000);
//GHOST::Hooks::Load_Menu();

//xbox::utilities::patchModuleImport(ModuleHandle, MODULE_KERNEL, 404, (DWORD)xbox::hooks::XenonPrivilegeHook2);

//if (pExecutionId->TitleID != 0xFFFE07D1) {
//	PLDR_DATA_TABLE_ENTRY ldat = (PLDR_DATA_TABLE_ENTRY)ModuleHandle;
//	PIMAGE_XEX_HEADER xhead = (PIMAGE_XEX_HEADER)ldat->XexHeaderBase;

//	BYTE* btmp = (BYTE*)(xhead->SecurityInfo + 0x17C);
//	DWORD arg1len = xhead->SizeOfHeaders - ((DWORD)btmp - (DWORD)xhead); // header size - offset into header
//	XeCryptShaInit(&global::challenge::xShaCurrentXex);
//	XeCryptShaUpdate(&global::challenge::xShaCurrentXex, btmp, arg1len);
//}


//ApplyPatchData(PATCH_DATA_KXAM_MSPOINTS_RETAIL, 64);
//ApplyPatchData(PATCH_DATA_MPPURCHASE_MSPOINTS_RETAIL, 0x1C);	
//BYTE data1[28]	= { 0x38, 0x80, 0x00, 0x05, 0x80, 0x63, 0x00, 0x1C, 0x90, 0x83, 0x00, 0x04, 0x38, 0x80, 0x05, 0x39, 0x90, 0x83, 0x00, 0x08, 0x38, 0x60, 0x00, 0x00, 0x4E, 0x80, 0x00, 0x20 };
//BYTE data2[4]	= { 0x60, 0x00, 0x00, 0x00 };
//BYTE data3[4]	= { 0x48, 0x00, 0x00, 0xC8 };
//BYTE data4[4]	= { 0x39, 0x60, 0x00, 0x00 };

//xbox::utilities::setMemory((PVOID)0x8168A678, data1, 28);// In Xam.xex  
//xbox::utilities::setMemory((PVOID)0x818E9E3C, data2, 4);//  In Xam.xex                  
//xbox::utilities::setMemory((PVOID)0x818EA174, data3, 4);//  In Xam.xex                
//xbox::utilities::setMemory((PVOID)0x818EE95C, data4, 4);//  In Guide.MP.Purchase.xex
//xbox::utilities::setMemory((PVOID)0x9015C108, data2, 4);//  In Guide.MP.Purchase.xex


//	else if (TitleID == HomeCOD_AW) {
	//		// Generate our values
	//		xbox::hooks::GenerateRandomValues(ModuleHandle);

	//		// Apply our bypasses
	//		//xbox::utilities::patchModuleImport(ModuleHandle, MODULE_XAM, 64, (DWORD)NetDll_XNetXnAddrToMachineIdHook);
	//		//xbox::utilities::patchModuleImport(ModuleHandle, MODULE_XAM, 73, (DWORD)NetDll_XNetGetTitleXnAddrHook);
	//		xbox::utilities::patchModuleImport(ModuleHandle, MODULE_KERNEL, 405, (DWORD)xbox::hooks::XexGetModuleHandleHook);
	//		xbox::utilities::patchModuleImport(ModuleHandle, MODULE_KERNEL, 580, (DWORD)xbox::hooks::XeKeysGetKeyHook);
	//		xbox::utilities::patchModuleImport(ModuleHandle, MODULE_KERNEL, 582, (DWORD)xbox::hooks::XeKeysGetConsoleIDHook);

	//		if (wcscmp(ModuleHandle->BaseDllName.Buffer, L"default.xex") == 0) {
	//			xbox::utilities::setMemory((PVOID)0x825891DC, 0x48000010); //spPatch1AW
	//			xbox::utilities::setMemory((PVOID)0x825891A4, 0x60000000); //spPatch2AW
	//			xbox::utilities::setMemory((PVOID)0x825891B0, 0x39600001); //spPatch3AW
	//		} else if (wcscmp(ModuleHandle->BaseDllName.Buffer, L"default_mp.xex") == 0) {
	//			xbox::utilities::setMemory((PVOID)0x822CA0AC, 0x39600000); //mpPatch1AW
	//			xbox::utilities::setMemory((PVOID)0x822CA0F4, 0x48000010); //mpPatch2AW
	//			xbox::utilities::setMemory((PVOID)0x822CA0C0, 0x38600000); //mpPatch3AW
	//			xbox::utilities::setMemory((PVOID)0x822CA0CC, 0x39600001); //mpPatch4AW
	//		}

	//		BOOL isSingleplayer = wcscmp(ModuleHandle->BaseDllName.Buffer, L"default.xex") == 0;
	//		if (isSingleplayer) {
	//			xbox::utilities::setMemory((PVOID)0x8258922C, 0x38600000);
	//			return;
	//		} else {
	//			xbox::utilities::setMemory((PVOID)0x822CA184, 0x38600000);
	//			Sleep(1000);
	//			*(long long*)0x822CA190 = 0x8921005060000000;
	//			*(int*)0x822CA18C = 0x48000010;
	//			*(int*)0x822CA184 = 0x38600000;
	//			*(int*)0x822CA0EC = 0x3920331C;
	//			*(PBYTE)0x8233B0E7 = 0x00;
	//			Sleep(500);
	//			*(PDWORD)0x826476A0 = 0x60000000;
	//			*(PDWORD)(0x826476A0 + 4) = 0x39600000;
	//			*(PDWORD)0x8260659C = 0x38C00005;
	//			*(PDWORD)0x82626F6C = 0x38C0000F;
	//			*(PDWORD)0x8262FB0C = 0x60000000;
	//			*(PDWORD)0x82648CEC = 0x60000000;
	//			*(PBYTE)(0x826352A4 + 3) = 1;
	//			*(DWORD*)0x826352A8 = 0x3B200001;
	//			return;
	//		}
	//		return;

	//	//else if (TitleID == HomeGTAV) {
	//	//	xbox::utilities::XNotifyUI(XNOTIFYUI_TYPE_PREFERRED_REVIEW, L"[XBLH] GTAV!!!");
	//	// 
	//	//	ZeroMemory((PVOID)0x8204DF70, 0x0B);
	//	//	*(LPSTR*)0x820093A4 = "succ";
	//	//	*(BYTE*)0x82CF782B = 1;
	//	//	*(int*)0x827D2164 = 0x60000000; // NOP Breakpoint
	//	//	*(int*)0x82D5C960 = 0x60000000; // Vehicle creation bypass
	//	//	*(int*)0x82D1E0BC = 0x60000000;// object bypass
	//	//	*(INT*)0x83288A30 = 0x48000104; //Bypass Script
	//	//	*(long long int*)0x838B60F4 = 0x00000422F6D6AA59; //Script bypass
	//	//	*(int*)0x82FDB57C = 0x3FC0022C; //Script bypass
	//	//	*(int*)0x82FDB580 = 0x63DEC800; //Script bypass
	//	//	*(int*)0x82FDB584 = 0x93DD0018; //Script bypass
	//	//	*(int*)0x82FDB588 = 0x3C60838B; //Script bypass
	//	//	*(int*)0x82FDB58c = 0x606360F4; //Script bypass
	//	//	*(int*)0x82FDB590 = 0xE8630000; //Script bypass
	//	//	*(int*)0x82FDB594 = 0x907D001C; //Script bypass
	//	//	return;
	//	//}