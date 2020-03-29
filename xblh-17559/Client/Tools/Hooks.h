#pragma once

namespace xbox {
	namespace hooks {
		PVOID NetDll_XHttpConnectHook(XNCALLER_TYPE CallerType, PVOID Session, CONST PCHAR ServerName, WORD ServerPort, DWORD Flags);

		VOID XHTTPSendRequestHook(SOCKET hRequest, const CHAR* pcszHeaders, DWORD dwHeadersLength, const VOID* lpOptional, DWORD dwOptionalLength, DWORD dwTotalLength, DWORD_PTR dwContext);
		VOID XHTTPOpenRequestUsingMemoryHook(SOCKET hConnect, const CHAR* pcszVerb, const CHAR* pcszObjectName, const CHAR* pcszVersion, const CHAR* pcszReferrer, const CHAR** ppReserved, DWORD dwFlags);

		VOID XHTTPHOOK();

		DWORD XexGetProcedureAddressHook(HANDLE hand, DWORD dwOrdinal, PVOID* pvAddress);
		NTSTATUS XexLoadExecutableHook(PCHAR Name, PHANDLE Handle, DWORD TypeFlags, DWORD Version);
		NTSTATUS XexLoadImageHook(CONST PCHAR Name, DWORD TypeFlags, DWORD Version, PHANDLE Handle);
		BOOL XenonPrivilegeHook(XEXPRIVS Privilege);
		DWORD XexLiveGoldHook(DWORD dwUserIndex, XPRIVILEGE_TYPE PrivilegeType, PBOOL pfResult);

		DWORD XexGetModuleHandleHook(PSZ moduleName, PHANDLE hand);
		DWORD XeKeysGetKeyHook(WORD KeyId, PVOID KeyBuffer, PDWORD KeyLength);
		DWORD XeKeysGetConsoleIDHook(PBYTE databuffer, char* szBuffer);
		DWORD NetDll_XNetGetTitleXnAddrHook(XNCALLER_TYPE xnc, XNADDR* pxna);
		DWORD NetDll_XNetXnAddrToMachineIdHook(XNCALLER_TYPE xnc, const XNADDR* pxnaddr, QWORD* pqwMachineId);
		VOID GenerateRandomValues(PLDR_DATA_TABLE_ENTRY ModuleHandle);
		char GenerateRandomNumericalCharacter();

		DWORD XamUserGetSigninInfo2(DWORD dwUserIndex, DWORD dwFlags, PXUSER_SIGNIN_INFO pSigninInfo);
		DWORD XamContentCreateEnumerator2(DWORD dwUserIndex, XCONTENTDEVICEID DeviceID, DWORD dwContentType, DWORD dwContentFlags, DWORD cItem, PDWORD pcbBuffer, PHANDLE phEnum);
		
		BYTE HookXamUserGetMembershipTierFromXUID(XUID xuid);
		BYTE HookXamUserGetMembershipTier(DWORD dwUserIndex);
	}
}