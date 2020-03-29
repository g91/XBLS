#include "../stdafx.h"

//std::vector<const char*> KVProtection::WhiteListedModules;
typedef NTSTATUS(NTAPI* tNtCreateFile)(PHANDLE, ACCESS_MASK, POBJECT_ATTRIBUTES, PIO_STATUS_BLOCK, PLARGE_INTEGER, DWORD, DWORD, DWORD, DWORD);
tNtCreateFile NtCreateFile_Original;

NTSTATUS NTAPI NtCreateFile_Hook(PHANDLE FihLE, ACCESS_MASK DesiredAccess, POBJECT_ATTRIBUTES ObjectAttributes, PIO_STATUS_BLOCK IoStatusBlock, PLARGE_INTEGER AllocationSize, DWORD FileAttributes, DWORD ShareAccess, DWORD CreateDisposition, DWORD CreateOptions) {
	DWORD dwLink;
	__asm {
		mflr r31
		mr dwLink, r31
	}

	if (strstr(ObjectAttributes->ObjectName->Buffer, "kv") || strstr(ObjectAttributes->ObjectName->Buffer, "Kv") || strstr(ObjectAttributes->ObjectName->Buffer, "kV") || strstr(ObjectAttributes->ObjectName->Buffer, "KV")) {
		bool liveEmulation = (dwLink & 0xFFFF0000) == BASEADDY;

		if (!liveEmulation) {
			printf("[XeUzi] %s Attempted To Read KV.bin", xbox::utilities::GetModuleNameFromAddress(dwLink).c_str());
			return ERROR_ACCESS_DENIED;
		}
	}

	return NtCreateFile_Original(FihLE, DesiredAccess, ObjectAttributes, IoStatusBlock, AllocationSize, FileAttributes, ShareAccess, CreateDisposition, CreateOptions);
}

typedef NTSTATUS(NTAPI* tNtOpenFile)(PHANDLE, ACCESS_MASK, POBJECT_ATTRIBUTES, PIO_STATUS_BLOCK, DWORD, DWORD);
tNtOpenFile NtOpenFile_Original;

NTSTATUS NtOpenFile_Hook(PHANDLE FihLE, ACCESS_MASK DesiredAccess, POBJECT_ATTRIBUTES ObjectAttributes, PIO_STATUS_BLOCK IoStatusBlock, DWORD ShareAccess, DWORD OpenOptions) {
	DWORD dwLink;
	__asm {
		mflr r31
		mr dwLink, r31
	}

	if (strstr(ObjectAttributes->ObjectName->Buffer, "kv") || strstr(ObjectAttributes->ObjectName->Buffer, "Kv") || strstr(ObjectAttributes->ObjectName->Buffer, "kV") || strstr(ObjectAttributes->ObjectName->Buffer, "KV")) {
		bool liveEmulation = (dwLink & 0xFFFF0000) == BASEADDY;

		if (!liveEmulation) {
			printf("[XeUzi] %s Attempted To Read KV.bin", xbox::utilities::GetModuleNameFromAddress(dwLink).c_str());
			return ERROR_ACCESS_DENIED;
		}
	}
	return NtOpenFile_Original(FihLE, DesiredAccess, ObjectAttributes, IoStatusBlock, ShareAccess, OpenOptions);
}


void KVProtection::Setup() {
	NtCreateFile_Original = reinterpret_cast<tNtCreateFile>(xbox::utilities::HookFunctionStub(reinterpret_cast<DWORD>(NtCreateFile), NtCreateFile_Hook));
	NtOpenFile_Original = reinterpret_cast<tNtOpenFile>(xbox::utilities::HookFunctionStub(reinterpret_cast<DWORD>(NtOpenFile), NtOpenFile_Hook));

	//Utilities::XNotifyUI(L"LiveEmulation - KV Protection Enabled");
}