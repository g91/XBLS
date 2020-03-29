#include "stdafx.h"


HRESULT CreateSymbolicLink(CHAR* szDrive, CHAR* szDeviceName, BOOL System) 
{
	CHAR szDestinationDrive[MAX_PATH];
	sprintf_s(szDestinationDrive, MAX_PATH, System ? "\\System??\\%s" : "\\??\\%s", szDrive);

	ANSI_STRING linkname, devicename;
	RtlInitAnsiString(&linkname, szDestinationDrive);
	RtlInitAnsiString(&devicename, szDeviceName);

	if (xbox::utilities::fileExists(szDrive))
		return S_OK;

	NTSTATUS status = ObCreateSymbolicLink(&linkname, &devicename);

	return (status >= 0) ? S_OK : S_FALSE;
}

DWORD WINAPI HVCleanerThread(PVOID pParam)
{
	if (CreateSymbolicLink("HDD:\\", "\\Device\\Harddisk0\\Partition1", TRUE) != ERROR_SUCCESS) 
	{
		return E_FAIL;
	}

	xbox::Hvx::InitializeHvPeekPoke();
	xbox::Hvx::InitializeHvProc();

	xbox::Cleaning::Go_Clean_HV();
}

BOOL APIENTRY DllMain(HANDLE hModule, DWORD dwReason, LPVOID lpReserved, CHAR* FilePath)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		HANDLE hThread = CreateThread(NULL, NULL, HVCleanerThread, NULL, NULL, NULL);	
		printf("UDP Server Thread Created %08X\n", hThread);
	}
	return TRUE;
}