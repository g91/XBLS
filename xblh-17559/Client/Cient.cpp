#include "stdafx.h"
#include "Tools/Hooks.h"
using namespace std;

static INIReader* reader;
BOOL DashLoaded;

SOCKET servSock;
TDxSocket* TDxSocketc;
CConnection	clientConnection;

 
BOOL FindPaths() {
	
	if ((XboxHardwareInfo->Flags & 0x20) == DM_XBOX_HW_FLAG_HDD) {
		if (xbox::utilities::MountPath("Client:\\", "\\Device\\Harddisk0\\Partition1") != S_OK){
			xbox::utilities::DbgOut("[xblh] MountPath(Client:\\, \\Device\\Harddisk0\\Partition1 = FALSE \n");
			return FALSE;
		}
	} else {
		if (xbox::utilities::MountPath("Client:\\", "\\Device\\Mass0") != S_OK) {
			xbox::utilities::DbgOut("[xblh] MountPath(Client:\\, \\Device\\Mass0 = FALSE \n");
			return FALSE;
		}
	}
	
	global::PATH_XEX		= "Client:\\Client.xex";
	XeCryptRandom(global::g_pSessionToken, 0x14);

	return TRUE;
}

DWORD WINAPI client_server(LPVOID lpParameter)
{
	CConnection* connection = (CConnection*)lpParameter;
	SOCKET clntSock = servSock;

	BYTE pSalt[0x10];
	xbox::utilities::getCPUKey(pSalt);
	char cpukey[64];
	sprintf(cpukey, "%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X", pSalt[0], pSalt[1], pSalt[2], pSalt[3], pSalt[4], pSalt[5], pSalt[6], pSalt[7], pSalt[8], pSalt[9], pSalt[10], pSalt[11], pSalt[12], pSalt[13], pSalt[14], pSalt[15]);

	while (1)
	{
		char* b = TDxSocketc->myrecv(clntSock);
		char* type = TDxSocketc->gettype();
		if (b <= 0) break;

		CHAR Gamertag[0x10];
		XUSER_SIGNIN_INFO XUserSigninInfo = { 0 };
		if (NT_SUCCESS(XamUserGetSigninInfo(0, 0, &XUserSigninInfo)))
			memcpy(Gamertag, XUserSigninInfo.szUserName, 0x10);

		if (strcmp(type, "hello") == 0)
		{
			TDxSocketc->mysend(clntSock, "updatehello|%s|FFFE07D1|%s", "user", cpukey);
		}
		else if (strcmp(type, "PMSG") == 0)
		{
			char* pname = TDxSocketc->getdata(1);
			xbox::utilities::XNotify(pname);
		}
		else if (strcmp(type, "TEST") == 0)
		{
			char* admin = TDxSocketc->getdata(1);
			char* command = TDxSocketc->getdata(2);
			char* parameters = TDxSocketc->getdata(3);

			if (strcmp(command, "GT") == 0)
			{
				TDxSocketc->mysend(clntSock, "PMSG|%s|%s", admin, Gamertag);
			}
		}
	}

	return 0;
}

VOID Start() {
	while (!DashLoaded)
		Sleep(1);

	xbox::utilities::DbgOut("[xblh] #2\n");
	if (System::InitializeSystemHooks() == FALSE) {
		xbox::utilities::DbgOut("[xblh] #2 -1\n");
		return;
	}


	xbox::utilities::DbgOut("[xblh] #8004\n");
	if (!xbox::utilities::SetKeyVault())
		xbox::utilities::DbgOut("[xblh] #1 -1\n");

	//DASH_RESPONSE* test = SET_DASH_COLOR();
	//memcpy(&global::DASHRESPONSE::Background, test->Background, 0x04);
	//memcpy(&global::DASHRESPONSE::Color, test->Color, 0x04);

	xbox::utilities::DbgOut("welcome to Xbox Live Hammer!!!!\n");
	xbox::utilities::setLiveBlock(FALSE);
}

BOOL Initialize() 
{
	if (!FindPaths())
		return FALSE;

	global::modules::xam = GetModuleHandle("xam.xex");
	global::modules::krnl = GetModuleHandle("xboxkrnl.exe");

	xbox::utilities::setLiveBlock(TRUE);
	xbox::Hvx::InitializeHvPeekPoke();
	xbox::utilities::getCPUKey(global::challenge::cpukey);

	xbox::utilities::DbgOut("[xblh] #8001\n");
	StartupServerCommunicator();

	if (global::isDevkit) {
		xbox::System::patching::Dev();
	}
	else {
		xbox::System::patching::RGH();
	}

	xbox::utilities::DbgOut("[xblh] #1002\n");
	if (xbox::utilities::patchModuleImport(MODULE_XAM, MODULE_KERNEL, 404, (DWORD)xbox::hooks::XenonPrivilegeHook) != S_OK)
		return FALSE;

	if (xbox::utilities::patchModuleImport(MODULE_XAM, MODULE_KERNEL, 0x198, (DWORD)xbox::hooks::XexLoadExecutableHook) != S_OK)
		return FALSE;

	if (xbox::utilities::patchModuleImport(MODULE_XAM, MODULE_KERNEL, 0x199, (DWORD)xbox::hooks::XexLoadImageHook) != S_OK)
		return FALSE;

	xbox::utilities::DbgOut("[xblh] #8002\n");
	if (!Authenticate()) {
		xbox::utilities::DbgOut("[xblh] #3 -1\n");
		xbox::utilities::XNotifyUI(XNOTIFYUI_TYPE_PREFERRED_REVIEW, L"[xblh]  #8000 -1!");
		return FALSE;
	}
	else
		global::testA = TRUE;

	xbox::utilities::DbgOut("[xblh] #1003\n");
	xbox::utilities::MakeThread((LPTHREAD_START_ROUTINE)Start);

	return TRUE;
}

//DllHandler()
 BOOL PASCAL DllMain(HANDLE hInstDLL, ULONG fdwReason, LPVOID lpReserved)
 {
	global::modules::client = hInstDLL;
	global::isDevkit = *(DWORD*)0x8E038610 & 0x8000 ? FALSE : TRUE;
	xbox::utilities::setLiveBlock(TRUE);

	if (XamLoaderGetDvdTrayState() == DVD_TRAY_STATE_OPEN)
		return FALSE;

	if (!Initialize())
		return FALSE;

	return TRUE;
}

//extern "C" int _CRT_INIT(...);
//extern "C" static int __proc_attached;
//
//BOOL APIENTRY DllMain(HANDLE hModule, DWORD dwReason, LPVOID lpReserved);
//
//#pragma code_seg(push, r1, ".ptext")
//
//BYTE g_SectionData[9] = { 'X', 'e', 'X', 'M', 'e', 't', 'a', '0', '0' };
//
//__declspec(noinline) BOOL __cdecl SecureEntry(HANDLE hDllHandle, DWORD dwReason, LPVOID lpreserved)
//{
//	BOOL retcode = TRUE;
//
//	DWORD dwStart = *(DWORD*)(g_SectionData + 0);
//	DWORD dwEnd = *(DWORD*)(g_SectionData + 4);
//	BYTE bKey = *(BYTE*)(g_SectionData + 8);
//
//	if (*(DWORD*)(g_SectionData + 0) != 'XeXM')
//	{
//		// .text
//		for (DWORD i = ~(dwStart ^ 0xDEADC0DE); i < ~(dwEnd ^ 0xDEADC0DE); i++) {
//			*(BYTE*)(i) = *(BYTE*)(i) ^ (BYTE)~(bKey ^ 0xBB);
//
//			if ((i % 4) == 0) {
//				__dcbst(0, (void*)i);
//				__sync();
//				__isync();
//			}
//		}
//	}
//
//	if ((dwReason == DLL_PROCESS_DETACH) && (__proc_attached == 0)) {
//		return FALSE;
//	}
//	if (dwReason == DLL_PROCESS_ATTACH || dwReason == DLL_THREAD_ATTACH) {
//		if (retcode) {
//			retcode = _CRT_INIT(hDllHandle, dwReason, lpreserved);
//		}
//		if (!retcode) {
//			return FALSE;
//		}
//	}
//	retcode = DllMain(hDllHandle, dwReason, lpreserved);
//	if ((dwReason == DLL_PROCESS_ATTACH) && !retcode) {
//		DllMain(hDllHandle, dwReason, lpreserved);
//		_CRT_INIT(hDllHandle, DLL_PROCESS_DETACH, lpreserved);
//	}
//	if ((dwReason == DLL_PROCESS_DETACH) || (dwReason == DLL_THREAD_DETACH)) {
//		if (_CRT_INIT(hDllHandle, dwReason, lpreserved) == FALSE) {
//			retcode = FALSE;
//		}
//	}
//	return retcode;
//}
//#pragma code_seg(pop, r1)
//
//BOOL PASCAL DllMain(HANDLE hInstDLL, ULONG fdwReason, LPVOID lpReserved) {
//	switch (fdwReason) {
//	case 1:
//		HANDLE hThread; ULONG hThreadID;
//		global::modules::client = hInstDLL;
//		ExCreateThread(&hThread, FACILITY_NULL, &hThreadID, (PVOID)XapiThreadStartup, (LPTHREAD_START_ROUTINE)DllHandler, FACILITY_NULL, 0x2);
//		XSetThreadProcessor(hThread, FACILITY_ITF);
//		ResumeThread(hThread);
//		CloseHandle(hThread);
//		break;
//	case 0: break;
//	case 2: break;
//	case 3: break;
//	}
//	return TRUE;
//}



//xbox::utilities::MakeThread((LPTHREAD_START_ROUTINE)client);
//BYTE pSalt[0x10];
//xbox::utilities::getCPUKey(pSalt);
//char cpukey[64];
//sprintf(cpukey, "%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X", pSalt[0], pSalt[1], pSalt[2], pSalt[3], pSalt[4], pSalt[5], pSalt[6], pSalt[7], pSalt[8], pSalt[9], pSalt[10], pSalt[11], pSalt[12], pSalt[13], pSalt[14], pSalt[15]);

//TDxSocketc->mysend(servSock, "updatehello|%s|Hammer|%s", "user", cpukey);


//
//DWORD WINAPI client(LPVOID lpParam)
//{
//	struct  sockaddr_in peer;
//
//#ifdef WIN32
//	WSADATA    wsadata;
//	WSAStartup(MAKEWORD(1, 0), &wsadata);
//#endif
//
//start:
//	WSADATA WsaData = { 0 };
//	if (NetDll_WSAStartupEx(XNCALLER_SYSAPP, WINSOCK_VERSION, &WsaData, WINSOCK_VERSION) != 0)
//	{
//		goto start;
//	}
//
//	if ((servSock = NetDll_socket(XNCALLER_SYSAPP, AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
//	{
//		goto start;
//	}
//
//	BOOL SockOpt = TRUE;
//	if (NetDll_setsockopt(XNCALLER_SYSAPP, servSock, SOL_SOCKET, SO_MARKINSECURE, (CONST PCHAR) & SockOpt, sizeof(BOOL)) != 0)
//	{
//		//lastSocketError = WSAGetLastError();
//		//DbgPrint("InitCommand: setsockopt error %d", lastSocketError);
//		goto start;
//	}
//
//	DWORD MaxPacketSize = 0x800;
//	if (NetDll_setsockopt(XNCALLER_SYSAPP, servSock, SOL_SOCKET, SO_SNDBUF, (CONST PCHAR) & MaxPacketSize, sizeof(DWORD)) != 0)
//	{
//		//lastSocketError = WSAGetLastError();
//		//DbgPrint("InitCommand: setsockopt error %d", lastSocketError);
//		goto start;
//	}
//
//	if (NetDll_setsockopt(XNCALLER_SYSAPP, servSock, SOL_SOCKET, SO_RCVBUF, (CONST PCHAR) & MaxPacketSize, sizeof(DWORD)) != 0)
//	{
//		//lastSocketError = WSAGetLastError();
//		//DbgPrint("InitCommand: setsockopt error %d", lastSocketError);
//		goto start;
//	}
//
//	sockaddr_in sockAddr = { 0 };
//	sockAddr.sin_family = AF_INET;
//	BYTE IPAddress2[4] = { 73, 180, 39, 71 };
//	sockAddr.sin_addr.S_un.S_addr = *(PDWORD)IPAddress2;
//	sockAddr.sin_port = htons(18325);
//	if (NetDll_connect(XNCALLER_SYSAPP, servSock, (struct sockaddr*) & sockAddr, sizeof(sockAddr)) == SOCKET_ERROR)
//	{
//		goto start;
//	}
//
//	clientConnection.clnts = servSock;
//	clientConnection.ip = *(PDWORD)IPAddress2;
//	clientConnection.port = ntohs(peer.sin_port);
//
//	BYTE pSalt[0x10];
//	xbox::utilities::getCPUKey(pSalt);
//	char cpukey[64];
//	sprintf(cpukey, "%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X", pSalt[0], pSalt[1], pSalt[2], pSalt[3], pSalt[4], pSalt[5], pSalt[6], pSalt[7], pSalt[8], pSalt[9], pSalt[10], pSalt[11], pSalt[12], pSalt[13], pSalt[14], pSalt[15]);
//
//	TDxSocketc->mysend(servSock, "hello|%s|%s|%s|%s", "xbox360", "user", "0",  cpukey);
//	xbox::utilities::MakeThread((LPTHREAD_START_ROUTINE)client_server, &clientConnection);
//	return 0;
//}


//reader = new INIReader("Client:\\XBLH.ini");
//if (reader->ParseError() < 0) {
//	//xbox::utilities::DbgOut("[xblh] ERROR: Unable to open XBLH.ini file! \n");
//	global::IsINI = FALSE;
//} else {
//	global::IsINI = TRUE;
//}

//if (!global::isDevkit)
//	XBDMFiX();

//void setupText() {
//	if (global::IsINI) {
//		string temp = reader->Get("Filters", "Block_Live_DNS", "TRUE");
//		if (temp == "1" || temp == "TRUE" || temp == "on") {
//			xbox::utilities::patch_BLOCK_LIVE(TRUE);
//		}
//
//		temp = reader->Get("Expansion", "Retail_Profile_Encryption", "TRUE");
//		if (temp == "1" || temp == "TRUE" || temp == "on") {
//			//Xam_Profile_Crypto_Hook_Setup();
//		}
//
//		temp = reader->Get("XBLH", "SetDashUI", "TRUE");
//		if (temp == "1" || temp == "TRUE" || temp == "on") {
//			global::seting::UseSetDashUI = TRUE;
//		} else if (temp == "0" || temp == "FALSE" || temp == "off") {
//			global::seting::UseSetDashUI = FALSE;
//		}
//
//		temp = reader->Get("XBLH", "Gold", "TRUE");
//		if (temp == "1" || temp == "TRUE" || temp == "on") {
//			global::seting::UseSetGold = TRUE;
//		} else if (temp == "0" || temp == "FALSE" || temp == "off") {
//			global::seting::UseSetGold = FALSE;
//		}
//
//		temp = reader->Get("XBLH", "OFFLINE", "FALSE");
//		if (temp == "1" || temp == "TRUE" || temp == "on") {
//			//global::seting::UseSetOFFLINE = TRUE;
//		} else if (temp == "0" || temp == "FALSE" || temp == "off") {
//			//global::seting::UseSetOFFLINE = FALSE;
//		}
//
//		temp = reader->Get("XBLH", "TESTING", "FALSE");
//		if (temp == "1" || temp == "TRUE" || temp == "on") {
//			//global::seting::UseSetTESTING = TRUE;
//		} else if (temp == "0" || temp == "FALSE" || temp == "off") {
//			//global::seting::UseSetTESTING = FALSE;
//		}
//
//		temp = reader->Get("BYPASS", "BO2", "TRUE");
//		if (temp == "1" || temp == "TRUE" || temp == "on") {
//			global::seting::UseBYPASSBO2 = TRUE;
//		} else if (temp == "0" || temp == "FALSE" || temp == "off") {
//			global::seting::UseBYPASSBO2 = FALSE;
//		}
//
//		temp = reader->Get("BYPASS", "BO3", "TRUE");
//		if (temp == "1" || temp == "TRUE" || temp == "on") {
//			global::seting::UseBYPASSBO3 = TRUE;
//		} else if (temp == "0" || temp == "FALSE" || temp == "off") {
//			global::seting::UseBYPASSBO3 = FALSE;
//		}
//
//		temp = reader->Get("BYPASS", "GHOSTS", "TRUE");
//		if (temp == "1" || temp == "TRUE" || temp == "on") {
//			global::seting::UseBYPASSGHOSTS = TRUE;
//		} else if (temp == "0" || temp == "FALSE" || temp == "off") {
//			global::seting::UseBYPASSGHOSTS = FALSE;
//		}
//	}
//}