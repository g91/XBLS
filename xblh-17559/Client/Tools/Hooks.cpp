#include "../stdafx.h"

//Detour<HRESULT>* XuiPNGTextureLoaderDetour = new Detour<HRESULT>;
//CXamShutdownNavButton btnXeOnlineMenu;


typedef enum _XPRIVILEGE_TYPE_NEW
{
	_XPRIVILEGE_ADD_FRIEND = 255, // Add Friends

	// Sessions
	_XPRIVILEGE_MULTIPLAYER_SESSIONS = 254,
	_XPRIVILEGE_MULTIPLAYER_ENABLED_BY_TIER = 253,

	// Communications
	_XPRIVILEGE_COMMUNICATIONS = 252,
	_XPRIVILEGE_COMMUNICATIONS_FRIENDS_ONLY = 251,

	_XPRIVILEGE_VIDEO_MESSAGING_SEND = 250, // sending video messages is restricted by tier and needs a second bit

	// Profile
	_XPRIVILEGE_PROFILE_VIEWING = 249,
	_XPRIVILEGE_PROFILE_VIEWING_FRIENDS_ONLY = 248,

	// Viewing of User Created Content
	_XPRIVILEGE_USER_CREATED_CONTENT = 247,
	_XPRIVILEGE_USER_CREATED_CONTENT_FRIENDS_ONLY = 246,

	_XPRIVILEGE_PURCHASE_CONTENT = 245, // Premium Content Purchases

	// Presence
	_XPRIVILEGE_PRESENCE = 244,
	_XPRIVILEGE_PRESENCE_FRIENDS_ONLY = 243,

	_XPRIVILEGE_XBOX1_LIVE_ACCESS = 242, // Xbox1 Live Access

	_XPRIVILEGE_CROSS_PLATFORM_MULTIPLAYER = 241, // Cross platform gameplay (PCs <-> Consoles)

	_XPRIVILEGE_CROSS_PLATFORM_SYSTEM_COMMUNICATION = 240, // Cross platform system communication (PCs <-> Consoles)

	_XPRIVILEGE_PREVIOUS_LIVE_PROTOCOLS = 239, // Only users on consoles flagged for selective updates will have this

	_XPRIVILEGE_TRADE_CONTENT = 238, // Player-to-player trading

	_XPRIVILEGE_MUSIC_EXPLICIT_CONTENT = 237, // explicit content

	_XPRIVILEGE_TESTER_ACCESS = 236, // Ability to test beta Live features - on (allow) | off (disallow)

	// Video Communications
	_XPRIVILEGE_VIDEO_COMMUNICATIONS = 235,
	_XPRIVILEGE_VIDEO_COMMUNICATIONS_FRIENDS_ONLY = 234,

	_XPRIVILEGE_SHARE_WLID_WITH_FRIENDS = 233, // Discoverability - let XBL-Friends send me a WL-Buddy request - on (allow) | off (disallow)

	_XPRIVILEGE_SHARE_GAMERTAG_WITH_BUDDIES = 232, // Discoverability - let WL-Buddies send me an XBL-Friend request - on (allow) | off (disallow)

	_XPRIVILEGE_METRO_ACCESS = 231, // on (allow) | off (disallow)

	_XPRIVILEGE_SHARE_FRIENDS_LIST = 230, // on (allow) | off (disallow)

	_XPRIVILEGE_SHARE_FRIENDS_LIST_FRIENDS_ONLY = 229, // on (allow) | off (disallow)

	_XPRIVILEGE_PASSPORT_SWITCHING = 228, // Allow passport switching - on (allow) | off (disallow)

	_XPRIVILEGE_BILLING_SWITCHING = 227, // Allow user to manage their payment instruments - on (allow) | off (disallow)

	_XPRIVILEGE_MULTIPLAYER_DEDICATED_SERVER = 226, // Use of dedicated servers for multiplayer games (mainly PCs) - on (allow) | off (disallow)

	_XPRIVILEGE_USER_GRADUATION = 225, // user has a child account and is eligible to graduate - on (allow) | off (disallow)

	_XPRIVILEGE_PREMIUM_VIDEO = 224, // access to media apps, now obsolete - on (allow) | off (disallow)

	_XPRIVILEGE_PRIMETIME = 223, // access to Xbox Live Primetime (Server-Backed Games) - on (allow) | off (disallow)

	_XPRIVILEGE_CONTENT_AUTHOR = 222, // user can publish content to their console - on (allow) | off (disallow)

	_XPRIVILEGE_PII_ACCESS = 221, // user can query user PII - on (allow) | off (disallow)

	_XPRIVILEGE_SOCIAL_NETWORK_SHARING = 220, // user can change their social network discoverability - on (allow) | off (disallow)

	_XPRIVILEGE_SUBSCRIPTION_TITLE = 219, // user has subscription title privilege - true | false

	_XPRIVILEGE_SUBSCRIPTION_CONTENT = 218, // user has subscription content privilege - true | false

	_XPRIVILEGE_PURCHASE_CONTENT_REQUIRES_PIN = 217, // purchase privilege can be onbtained with pin - true | false

	_XPRIVILEGE_PASSPORT_SWITCHING_REQUIRES_PIN = 216, // passport switching can be obtained with pin - true | false

	_XPRIVILEGE_BILLING_SWITCHING_REQUIRES_PIN = 215, // billing switching can be obtain with pin - true | false

	_XPRIVILEGE_PREMIUM_CONTENT = 214, // user is entitled to premium content - true | false

	_XPRIVILEGE_FAMILY = 213, // user is entitled to family subscription functionality (family center) - true | false

	_XPRIVILEGE_UNSAFE_PROGRAMMING = 212, // unsafe or family programming for the user - on (regular programming) | off (family programming)

	_XPRIVILEGE_SHARE_CONTENT = 211, // user is allowed to upload content to external providers - on (allow) | off (disallow)

	_XPRIVILEGE_SUPPORT_OVERRIDE = 210, // used by customer support personnel to override default behaviour - on (allow) | off (disallow)

	_XPRIVILEGE_CLOUD_SAVED_GAMES = 209, // user is allowed to save games in cloud storage - on (allow) | off (disallow)
} XPRIVILEGE_TYPE_NEW;

extern HANDLE hXam;
namespace xbox {
	namespace hooks {
		VOID __cdecl APCWorker(void* Arg1, void* Arg2, void* Arg3)
		{
			if (Arg2) {
				((LPOVERLAPPED_COMPLETION_ROUTINE)Arg2)((DWORD)Arg3, 0, (LPOVERLAPPED)Arg1);
			}
		}

		DWORD XSecurityCreateProcessHook(DWORD dwHardwareThread) {
			return ERROR_SUCCESS;
		}

		VOID XSecurityCloseProcessHook() {}
		DWORD XSecurityVerifyHook(DWORD dwMilliseconds, LPOVERLAPPED lpOverlapped, LPOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine) {
			if (lpCompletionRoutine) {
				NtQueueApcThread((HANDLE)-2, (PIO_APC_ROUTINE)APCWorker, lpOverlapped, (PIO_STATUS_BLOCK)lpCompletionRoutine, 0);
			}
			return ERROR_SUCCESS;
		}

		DWORD XSecurityGetFailureInfoHook(PXSECURITY_FAILURE_INFORMATION pFailureInformation) {
			if (pFailureInformation->dwSize != 0x18) 
				return ERROR_NOT_ENOUGH_MEMORY;

			pFailureInformation->dwBlocksChecked = 0;
			pFailureInformation->dwFailedReads = 0;
			pFailureInformation->dwFailedHashes = 0;
			pFailureInformation->dwTotalBlocks = 0;
			pFailureInformation->fComplete = TRUE;
			return ERROR_SUCCESS;
		}

		DWORD XexGetProcedureAddressHook(HANDLE hand, DWORD dwOrdinal, PVOID* pvAddress) {
			if (hand == global::modules::xam) {
				switch (dwOrdinal) {
				case 0x9BB:
					*pvAddress = XSecurityCreateProcessHook;
					return 0;
				case 0x9BC:
					*pvAddress = XSecurityCloseProcessHook;
					return 0;
				case 0x9BD:
					*pvAddress = XSecurityVerifyHook;
					return 0;
				case 0x9BE:
					*pvAddress = XSecurityGetFailureInfoHook;
					return 0;
				}
			}
			return XexGetProcedureAddress(hand, dwOrdinal, pvAddress);
		}

		static DWORD lastTitleID = 0;
		DWORD XexGetModuleHandleHook(PSZ moduleName, PHANDLE hand)
		{
			if (moduleName != NULL) // <-- BO2 throws us a null module name to cause a crash, kinda cute
			{
				char buff[4];
				memcpy(buff, moduleName, 4);
				if (memcmp(buff, "xbdm", 4) == 0) {
					*hand = 0;
					return 0xC0000225; // Module not found
				}
			}

			return XexGetModuleHandle(moduleName, hand);
		}

		QWORD RandomMachineID;
		BYTE RandomMacAddress[6];
		char RandomConsoleSerialNumber[12];
		char RandomConsoleID[12];

		char GenerateRandomNumericalCharacter()
		{
			// Create our character array
			char Characters[10] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };

			// Get our random number from 0-9
			DWORD dwRandom = rand() % 9;

			// Return our random number as a character
			return Characters[dwRandom];
		}

		VOID GenerateRandomValues(PLDR_DATA_TABLE_ENTRY ModuleHandle)
		{
			// Generate random machine id
			BYTE* MachineID = (BYTE*)XPhysicalAlloc(8, MAXULONG_PTR, NULL, PAGE_READWRITE);
			if (MachineID == NULL){
				//xbox::utilities::log("error allocating buffer!");
				HalReturnToFirmware(HalResetSMCRoutine);
			}
			MachineID[0] = 0xFA;
			MachineID[1] = 0x00;
			MachineID[2] = 0x00;
			MachineID[3] = 0x00;
			XeCryptRandom((BYTE*)(MachineID + 4), 4);
			xbox::utilities::setMemory(&RandomMachineID, MachineID, 8);
			XPhysicalFree(MachineID);

			// Generate random mac address
			if ((XboxHardwareInfo->Flags & 0xF0000000) > 0x40000000) {
				RandomMacAddress[0] = 0x7C;
				RandomMacAddress[1] = 0xED;
				RandomMacAddress[2] = 0x8D;
			}
			else {
				RandomMacAddress[0] = 0x00;
				RandomMacAddress[1] = 0x22;
				RandomMacAddress[2] = 0x48;
			}
			XeCryptRandom((BYTE*)(RandomMacAddress + 3), 3);

			// Use this to randomize MI
			BYTE* RandomBytes = (BYTE*)XPhysicalAlloc(16, MAXULONG_PTR, NULL, PAGE_READWRITE);
			if (RandomBytes == NULL)
			{
				//xbox::utilities::log("error allocating buffer!\n");
				HalReturnToFirmware(HalResetSMCRoutine);
			}
			XeCryptRandom(RandomBytes, 16);
			xbox::utilities::setMemory((LPVOID)xbox::utilities::getModuleImportCallAddress(ModuleHandle, MODULE_XAM, 0x2D9), RandomBytes, 16); // XamShowDirtyDiscErrorUI 
			XPhysicalFree(RandomBytes);

			// Generate random console serial number
			for (int i = 0; i < 12; i++)
			{
				RandomConsoleSerialNumber[i] = GenerateRandomNumericalCharacter();
			}

			// Generate random console id
			for (int i = 0; i < 12; i++)
			{
				RandomConsoleID[i] = GenerateRandomNumericalCharacter();
			}
		}

		DWORD NetDll_XNetXnAddrToMachineIdHook(XNCALLER_TYPE xnc, const XNADDR* pxnaddr, QWORD* pqwMachineId) {
			*pqwMachineId = RandomMachineID;
			//DbgPrint("NetDll_XNetXnAddrToMachineIdHook spoofed."); would crash on Ghosts
			return ERROR_SUCCESS;
		}

		DWORD NetDll_XNetGetTitleXnAddrHook(XNCALLER_TYPE xnc, XNADDR* pxna) {
			DWORD retVal = NetDll_XNetGetTitleXnAddr(XNCALLER_TITLE, pxna);

			XNADDR ourAddr;
			XNetGetTitleXnAddr(&ourAddr);
			if (memcmp(&ourAddr, pxna, sizeof(XNADDR) == 0)) {
				xbox::utilities::setMemory((BYTE*)pxna->abEnet, RandomMacAddress, 6);
			}
			return retVal;
		}

		DWORD XeKeysGetConsoleIDHook(PBYTE databuffer, char* szBuffer) {
			if (databuffer != 0) xbox::utilities::setMemory(databuffer, RandomConsoleID, 0xC);
			if (szBuffer != 0) xbox::utilities::setMemory(szBuffer, RandomConsoleID, 0xC);
			return ERROR_SUCCESS;
		}

		DWORD XeKeysGetKeyHook(WORD KeyId, PVOID KeyBuffer, PDWORD KeyLength) {
			if (KeyId == 0x14) {
				xbox::utilities::setMemory(KeyBuffer, RandomConsoleSerialNumber, 0xC);
				return ERROR_SUCCESS;
			}

			return XeKeysGetKey(KeyId, KeyBuffer, KeyLength);
		}

		NTSTATUS XexLoadExecutableHook(PCHAR Name, PHANDLE Handle, DWORD TypeFlags, DWORD Version) {
			HANDLE Module = 0;
			NTSTATUS Result = XexLoadExecutable(Name, &Module, TypeFlags, Version);
			if (Handle != 0) *Handle = Module;
			if (NT_SUCCESS(Result)) InitializeGameHooks((PLDR_DATA_TABLE_ENTRY)*XexExecutableModuleHandle);
			return Result;
		}

		NTSTATUS XexLoadImageHook(CONST PCHAR Name, DWORD TypeFlags, DWORD Version, PHANDLE Handle) {
			HANDLE Module = 0;
			NTSTATUS Result = XexLoadImage(Name, TypeFlags, Version, &Module);
			if (Handle != 0) *Handle = Module;
			if (NT_SUCCESS(Result)) InitializeGameHooks((PLDR_DATA_TABLE_ENTRY)Module);
			return Result;
		}

		//BOOL XenonPrivilegeHook(XEXPRIVS Privilege)
		//{
		//	XEXPRIVS Privileges[0x04] = { XEX_PRIVILEGE_INSECURE_SOCKETS, XEX_PRIVILEGE_TITLE_INSECURE_UTILITYDRIVE, XEX_PRIVILEGE_ALLOW_BACKGROUND_DOWNLOAD, XEX_PRIVILEGE_GAMEVOICE_REQUIRED_UI };
		//	for (INT i = 0x00; i < ARRAYSIZE(Privileges); i++){
		//		if (Privilege == Privileges[i]){
		//			return TRUE;
		//		}
		//	}
		//	return XexCheckExecutablePrivilege(Privilege);
		//}

		BOOL XenonPrivilegeHook(XEXPRIVS Privilege) 
		{
			if (Privilege == XEX_PRIVILEGE_INSECURE_SOCKETS) 
				return TRUE;

			if (Privilege == XEX_PRIVILEGE_TITLE_INSECURE_UTILITYDRIVE)
				return TRUE;

			if (Privilege == XEX_PRIVILEGE_ALLOW_BACKGROUND_DOWNLOAD)
				return TRUE;

			if (Privilege == XEX_PRIVILEGE_GAMEVOICE_REQUIRED_UI)
				return TRUE;

			return XexCheckExecutablePrivilege(Privilege);
		}

		bool Signin1 = false;
		XUID myXuid;
		DWORD XamContentCreateEnumerator2(DWORD dwUserIndex, XCONTENTDEVICEID DeviceID, DWORD dwContentType, DWORD dwContentFlags, DWORD cItem, PDWORD pcbBuffer, PHANDLE phEnum) 
		{

			return XContentCreateEnumerator(dwUserIndex, DeviceID, dwContentType, dwContentFlags, cItem, pcbBuffer, phEnum);
		}
		
		DWORD XamUserGetSigninInfo2(DWORD dwUserIndex, DWORD dwFlags, PXUSER_SIGNIN_INFO pSigninInfo)
		{

			return XamUserGetSigninInfo(dwUserIndex, dwFlags, pSigninInfo);
		}
		
		DWORD XamUserGetSigninState2(DWORD dwUserIndex){

			return XamUserGetSigninState(dwUserIndex); // not signed in
		}
		
		typedef BYTE (*dXamUserGetMembershipTierFromXUID)(XUID xuid);
		dXamUserGetMembershipTierFromXUID XamUserGetMembershipTierFromXUID = (dXamUserGetMembershipTierFromXUID)xbox::utilities::resolveFunction("xam.xex", 535);

		BYTE HookXamUserGetMembershipTierFromXUID(XUID xuid) 
		{
			BYTE rat = XamUserGetMembershipTierFromXUID(xuid);

			return rat;
		}

		typedef BYTE(*dXamUserGetMembershipTier)(XUID xuid);
		dXamUserGetMembershipTier XamUserGetMembershipTier = (dXamUserGetMembershipTier)xbox::utilities::resolveFunction("xam.xex", 539);

		BYTE HookXamUserGetMembershipTier(DWORD dwUserIndex) 
		{
			BYTE rat = XamUserGetMembershipTier(dwUserIndex);
			if (XamUserGetSigninState(dwUserIndex) == eXUserSigninState_SignedInToLive){
				xbox::utilities::DbgOut("[xblh] XamUserGetMembershipTier rat 0x%X\n", rat);
			}

			return rat;
		}

		DWORD XexLiveGoldHook(DWORD dwUserIndex, XPRIVILEGE_TYPE PrivilegeType, PBOOL pfResult)
		{
			//if(PrivilegeType != _XPRIVILEGE_COMMUNICATIONS) xbox::utilities::log("XamUserCheckPrivilege: userIndex=%X, privType=%X", dwUserIndex, PrivilegeType);
			if (XamUserGetSigninState(dwUserIndex) == eXUserSigninState_SignedInToLive)
			{
				switch (PrivilegeType)
				{
				case _XPRIVILEGE_ADD_FRIEND:
				case _XPRIVILEGE_MULTIPLAYER_SESSIONS:
				case _XPRIVILEGE_MULTIPLAYER_ENABLED_BY_TIER:
				case _XPRIVILEGE_COMMUNICATIONS:
				case _XPRIVILEGE_COMMUNICATIONS_FRIENDS_ONLY:
				case _XPRIVILEGE_VIDEO_MESSAGING_SEND:
				case _XPRIVILEGE_PROFILE_VIEWING:
				case _XPRIVILEGE_PROFILE_VIEWING_FRIENDS_ONLY:
				case _XPRIVILEGE_USER_CREATED_CONTENT:
				case _XPRIVILEGE_USER_CREATED_CONTENT_FRIENDS_ONLY:
				case _XPRIVILEGE_PURCHASE_CONTENT:
				case _XPRIVILEGE_PRESENCE:
				case _XPRIVILEGE_PRESENCE_FRIENDS_ONLY:
				case _XPRIVILEGE_XBOX1_LIVE_ACCESS:
				case _XPRIVILEGE_CROSS_PLATFORM_SYSTEM_COMMUNICATION:
				case _XPRIVILEGE_TRADE_CONTENT:
				case _XPRIVILEGE_MUSIC_EXPLICIT_CONTENT:
				case _XPRIVILEGE_VIDEO_COMMUNICATIONS_FRIENDS_ONLY:
				case _XPRIVILEGE_METRO_ACCESS:
				case _XPRIVILEGE_SHARE_FRIENDS_LIST:
				case _XPRIVILEGE_SHARE_FRIENDS_LIST_FRIENDS_ONLY:
				case _XPRIVILEGE_PASSPORT_SWITCHING:
				case _XPRIVILEGE_BILLING_SWITCHING:
				case _XPRIVILEGE_MULTIPLAYER_DEDICATED_SERVER:
				case _XPRIVILEGE_PREMIUM_VIDEO:
				case _XPRIVILEGE_PRIMETIME:
				case _XPRIVILEGE_SOCIAL_NETWORK_SHARING:
				case _XPRIVILEGE_TESTER_ACCESS:
				{
					*pfResult = TRUE;
					return ERROR_SUCCESS;
				}
				default: break;
				}
			}
			return XamUserCheckPrivilege(dwUserIndex, PrivilegeType, pfResult);
		}

		bool NullHeader = TRUE;
		VOID __declspec(naked) XHTTPConnectStub(...) {
			__asm
			{
				li r3, 1
				nop
				nop
				nop
				nop
				nop
				nop
				blr
			}
		}

		VOID __declspec(naked) XHTTPOpenRequestUsingMemoryStub(...) {
			__asm
			{
				li r3, 2
				nop
				nop
				nop
				nop
				nop
				nop
				blr
			}
		}

		VOID XHTTPOpenRequestUsingMemoryHook(SOCKET hConnect, const CHAR* pcszVerb, const CHAR* pcszObjectName, const CHAR* pcszVersion, const CHAR* pcszReferrer, const CHAR** ppReserved, DWORD dwFlags) {
			////xbox::utilities::DbgOut("%s\n", pcszObjectName);

			if (strncmp(pcszObjectName + 0x15, "dashhome.xml", 0xC) == 0) 
				pcszObjectName = "/assets/dashhome.xml", NullHeader = TRUE;

			if (strncmp(pcszObjectName + 0x15, "exl-HELP-on-360.xml", 0x13) == 0) 
				pcszObjectName = "/assets/exl-HELP-on-360.xml", NullHeader = TRUE;

			if (strncmp(pcszObjectName + 0x15, "exl-GamesMarketplace.xml", 0x18) == 0) 
				pcszObjectName = "/assets/exl-GamesMarketplace.xml", NullHeader = TRUE;

			if (strncmp(pcszObjectName + 0x15, "DashVideoMP-London.xml", 0x16) == 0) 
				pcszObjectName = "/assets/DashVideoMp-London.xml", NullHeader = TRUE;

			XHTTPOpenRequestUsingMemoryStub(hConnect, pcszVerb, pcszObjectName, pcszVersion, pcszReferrer, ppReserved, dwFlags);
		}

		VOID __declspec(naked) XHTTPSendRequestStub(...) {
			__asm
			{
				li r3, 3
				nop
				nop
				nop
				nop
				nop
				nop
				blr
			}
		}

		VOID XHTTPSendRequestHook(SOCKET hRequest, const CHAR* pcszHeaders, DWORD dwHeadersLength, const VOID* lpOptional, DWORD dwOptionalLength, DWORD dwTotalLength, DWORD_PTR dwContext) {
			if (NullHeader) pcszHeaders = NULL;
			XHTTPSendRequestStub(hRequest, pcszHeaders, dwHeadersLength, lpOptional, dwOptionalLength, dwTotalLength, dwContext);
			NullHeader = FALSE;
		}

		VOID __declspec(naked) XuiLoadVisualFromBinaryStub(...) {
			__asm
			{
				li r3, 4
				nop
				nop
				nop
				nop
				nop
				nop
				blr
			}
		}

		//VOID XuiLoadVisualFromBinaryHook(PWCHAR r3, PWCHAR r4) {
		//	XuiLoadVisualFromBinaryStub(r3, r4);
		//	//printf("010 Open: %ls\n", r3);
		//}

		VOID XHTTPHOOK() {
			//xbox::utilities::hookFunctionStart((PDWORD)0x921E8FB8, (PDWORD)XuiLoadVisualFromBinaryStub, (DWORD)XuiLoadVisualFromBinaryHook);//old 92247DC0
			xbox::utilities::hookFunctionStart((PDWORD)0x92247B60, (PDWORD)xbox::hooks::XHTTPOpenRequestUsingMemoryStub, (DWORD)xbox::hooks::XHTTPOpenRequestUsingMemoryHook);//old 92247DC0
			xbox::utilities::hookFunctionStart((PDWORD)0x92247BB8, (PDWORD)xbox::hooks::XHTTPSendRequestStub, (DWORD)xbox::hooks::XHTTPSendRequestHook);//old 92247E18
		}

		PVOID NetDll_XHttpConnectHook(XNCALLER_TYPE CallerType, PVOID Session, CONST PCHAR ServerName, WORD ServerPort, DWORD Flags)
		{
			////xbox::utilities::DbgOut("[xblh]	URL: %s", ServerName);
			if (strcmp(ServerName, "manifest.xboxlive.com") == 0) {
				strcpy(ServerName, "xbox.xbls.us");
				ServerPort = 0x50;
				Flags = 0x01;
			}

			return  NetDll_XHttpConnect(CallerType, Session, ServerName, ServerPort, Flags);
		}
	}
}


//if(dwUserIndex == 0) {
//	//pSigninInfo->xuid = myXuid;
//	//pSigninInfo->dwInfoFlags = XUSER_INFO_FLAG_LIVE_ENABLED;

////	if(XamGetCurrentTitleId() == 0x584E07D1) {
//		//pSigninInfo->UserSigninState = XUSER_SIGNIN_STATE::eXUserSigninState_SignedInToLive;
////	}
////	else
//	//	pSigninInfo->UserSigninState = XUSER_SIGNIN_STATE::eXUserSigninState_SignedInLocally;
//	//pSigninInfo->dwGuestNumber = 0;
//	//pSigninInfo->dwSponsorUserIndex = 0;
//	
//	//strcpy(pSigninInfo->szUserName, "Haruhi Suzumiya");
//	//strcpy(pSigninInfo->szUserName, "Mikuru Asahina");
//	
//	return ERROR_SUCCESS;
//}
////XamUserGetMembershipTierFromXUID	816DACA8	535
//xbox::utilities::patchInJump((PDWORD)0x816DACA8, (DWORD)HookXamUserGetMembershipTierFromXUID, FALSE);
//
////XamUserGetMembershipTier	816DAC48	539
//xbox::utilities::patchInJump((PDWORD)0x816DAC48, (DWORD)HookXamUserGetMembershipTier, FALSE);

//if (strcmp(ServerName, "marketplace-xb.xboxlive.com") == 0) {
//	strcpy(ServerName, "marketplace-xb.xbls.us");
//	ServerPort = 0x50;
//	Flags = 0x01;
//}

//if (strcmp(ServerName, "manifest.xboxlive.com") == 0) {
//	strcpy(ServerName, "xbox.xbls.us");
//	ServerPort = 0x50;
//	Flags = 0x01;
//}

//if (strcmp(ServerName, "eds.xboxlive.com") == 0) {
//	strcpy(ServerName, "eds.xbls.us");
//	ServerPort = 0x50;
//	Flags = 0x01;
//}

//if (strcmp(ServerName, "marketplace-xb.xboxlive.com") == 0) {
//	strcpy(ServerName, "marketplace-xb.xbls.us");
//	ServerPort = 0x50;
//	Flags = 0x01;
//}

//if (strcmp(ServerName, "compass.xboxlive.com") == 0) {
//	strcpy(ServerName, "compass.xbls.us");
//	//ServerPort = 0x50;
//	//Flags = 0x01;
//}