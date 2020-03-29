// No KV mode released by xbLive team :)
// NOTE: you'll have to edit your challenge code. When your client is using a server kv, you need to use the data from that kv on your server rather than the kv data they'll be sending for the challenge.

Detour<HRESULT> ThreadProcServiceSystemTasksStub;
HRESULT ThreadProcServiceSystemTasksHook(PVOID pvParam) {
	static int counter = 0;
	while (server.dwNoKVHash == 0) {
		Sleep(10);

		if (server.bLoadedProperly) // only count when initial networking is done etc
			counter++;

		// 20s timeout
		if (counter > 2000) {
			if (server.bHasTime) {
				Notify("server - Failed to get server KV").Message();
			}

			break;
		}
	}

	ThreadProcServiceSystemTasksStub.TakeDownDetour();

	printf("Allowing XOnline to initialize...\n");
	return ThreadProcServiceSystemTasksStub.CallOriginal(pvParam);
}

Detour<NTSTATUS> KerbAddConsoleCertHashPrePreAuthStub;
NTSTATUS KerbAddConsoleCertHashPrePreAuthHook(DWORD r3, BYTE* cert, DWORD r5) {
	// hash is sent from the server, if it's not 0 then a kv was downloaded from the server and we can init
	if (server.dwNoKVHash != 0x0) {
		if (cert) {
			memcpy(cert, server.szNoKVConsoleCertificate, 0x1A8);
		}
	}

	return KerbAddConsoleCertHashPrePreAuthStub.CallOriginal(r3, cert, r5);
}

Detour<NTSTATUS> XeKeysGetConsoleCertificateStub;
NTSTATUS XeKeysGetConsoleCertificateHook(BYTE* cert) {
	// hash is sent from the server, if it's not 0 then a kv was downloaded from the server and we can init
	if (server.dwNoKVHash != 0x0) {
		if (cert) {
			memcpy(cert, server.szNoKVConsoleCertificate, 0x1A8);
			return ERROR_SUCCESS;
		}
	}

	return XeKeysGetConsoleCertificateStub.CallOriginal(cert);
}

Detour<void> FormatXenonConsoleCertificatePrincipalNameStub;
void FormatXenonConsoleCertificatePrincipalNameHook(DWORD r3, char* r4, DWORD r5) {
	// hash is sent from the server, if it's not 0 then a kv was downloaded from the server and we can init
	if (server.dwNoKVHash != 0x0) {
		char* str = r4;
		str[0] = 0x58; // X
		str[1] = 0x45; // E
		str[2] = 0x2E; // .
		str += 3;

		unsigned long long r11 = 0;
		for (int i = 0; i < 5; i++) {
			BYTE r9 = *(BYTE*)(server.szNoKVConsoleCertificate + 2 + i);
			r11 = r11 << 8;
			r11 = r9 + r11;
		}

		_snprintf(str, r5, "%011I64u%u", r11 >> 4, r11 & 0xFFFFFFFF & 0xF);

		if (server.bDevkit) {
			DWORD firstArg = *(DWORD*)(r3 + 0x2D48);
			DWORD ret = 0;

			__asm rlwinm ret, firstArg, 0, 13, 13

			if (ret == 0) {
				str[0xC] = 0x0;
			} else {
				str[r5 - 1] = -1;
			}
		} else {
			str[0xF] = 0x0;
		}

		return;
	}

	return FormatXenonConsoleCertificatePrincipalNameStub.CallOriginal(r3, r4, r5);
}

Detour<NTSTATUS> GetSerialNumberStub;
NTSTATUS GetSerialNumberHook(DWORD r3, BYTE* outSerial) {
	if (server.dwNoKVHash != 0x0) {
		memcpy(outSerial, server.szNoKVSerial, 0xC);
		return ERROR_SUCCESS;
	}

	return GetSerialNumberStub.CallOriginal(r3, outSerial);
}

// hook
XeKeysGetConsoleCertificateStub.SetupDetour(MODULE_KERNEL, 31, &XeKeysGetConsoleCertificateHook);
ThreadProcServiceSystemTasksStub.SetupDetour(server.bDevkit ? 0x81AB8288 : 0x818CEE08, &ThreadProcServiceSystemTasksHook); // used to halt XOnline initializing until we have the kv
KerbAddConsoleCertHashPrePreAuthStub.SetupDetour(server.bDevkit ? 0x81B6EAF8 : 0x81946990, &KerbAddConsoleCertHashPrePreAuthHook);
FormatXenonConsoleCertificatePrincipalNameStub.SetupDetour(server.bDevkit ? 0x8181AE00 : 0x817336E0, &FormatXenonConsoleCertificatePrincipalNameHook);
GetSerialNumberStub.SetupDetour(server.bDevkit ? 0x8181B418 : 0x81734A68, &GetSerialNumberHook);

// vars you'll need
BYTE szNoKVConsoleCertificate[0x1A8];
BYTE szNoKVSerial[0xC];
DWORD dwNoKVHash;

// data you'll need to return from your server from the kv
DWORD dwHash; // set to server.dwNoKVHash
BYTE szConsoleObfuscationKey[0x10];
BYTE szConsolePrivateKey[0x1D0];
BYTE szXeIkaPrivateKey[0x390];
BYTE szConsoleSerial[0xC]; // copy to server.szNoKVSerial
BYTE szConsoleCertificate[0x1A8]; // copy to server.szNoKVConsoleCertificate
BYTE szMacAddress[0x6];

// what you'll also need to do when you get the kv data from the server
#define KEYVAULT_HV_PTR server.bDevkit ? 0x00000002000162e0 : 0x00000002000163C0
QWORD ptr = Hypervisor::HvPeekQWORD(KEYVAULT_HV_PTR);
Hypervisor::HvPokeBytes(ptr + 0xD0, szConsoleObfuscationKey, 0x10);
Hypervisor::HvPokeBytes(ptr + 0x298, szConsolePrivateKey, 0x1D0);
Hypervisor::HvPokeBytes(ptr + 0x468, szXeIkaPrivateKey, 0x390);

ExSetXConfigSetting(XCONFIG_SECURED_CATEGORY, XCONFIG_SECURED_MAC_ADDRESS, szMacAddress, 6);
XamCacheReset(XAM_CACHE_TICKETS);