// hypervisor payload execution released by xbLive team :)

BYTE* Hypervisor::CreateHypervisorPayload(BYTE* ppc, DWORD size) {
    BYTE* payload = (BYTE*)XPhysicalAlloc(0x1000, MAXULONG_PTR, 0x10000, PAGE_READWRITE);
    memset(payload, 0, 0x1000);

    // setup the hv header
    BYTE rc4Key[0x10];
    BYTE encryptionKey[0x10] = { 0x79, 0x20, 0x75, 0x20, 0x68, 0x65, 0x66, 0x66, 0x20, 0x72, 0x65, 0x76, 0x65, 0x72, 0x73, 0x65 };
	BYTE bootLoaderKey[0x10] = { 0xDD, 0x88, 0xAD, 0x0C, 0x9E, 0xD6, 0x69, 0xE7, 0xB5, 0x67, 0x94, 0xFB, 0x68, 0x56, 0x3E, 0xFA };

    *(WORD*)(payload) = server.bDevkit ? 0x5D4D : 0x4D4D;
    *(WORD*)(payload + 0x2) = 0x6969;
    *(DWORD*)(payload + 0x8) = 0x120;
    *(DWORD*)(payload + 0xC) = 0x120 + size;

    memcpy((void*)(payload + 0x10), encryptionKey, 0x10);
    memcpy(payload + 0x120, ppc, size);

	Crypto::XeCryptHmacSha(bootLoaderKey, 0x10, (BYTE*)(payload + 0x10), 0x10, 0, 0, 0, 0, rc4Key, 0x10);
	Crypto::XeCryptRc4(rc4Key, 0x10, payload + 0x20, *(DWORD*)(payload + 0xC) - 0x20);

    return payload;
}

QWORD Hypervisor::ExecuteHypervisorPayload(BYTE* payload, DWORD size, QWORD r4, QWORD r5, QWORD r6, QWORD r7) {
    BYTE* p = CreateHypervisorPayload(payload, size);
    if (p) {
        // patch signature verification
		HvPokeDWORD(server.bDevkit ? 0x60E4 : 0x617C, 0x38600001);

        // execute payload
		QWORD resp = HvxKeysExecute(MmGetPhysicalAddress(p), 0x1000, r4, r5, r6, r7);

        // re-patch signature verification
		HvPokeDWORD(server.bDevkit ? 0x60E4 : 0x617C, server.bDevkit ? 0x48004F6D : 0x4800525D);

        XPhysicalFree(p);

		return resp;
    }

    return 0;
}

// example
BYTE ppc[8] = { 0x38, 0x60, 0x00, 0x01, 0x4e, 0x80, 0x00, 0x20 }; // li r3, 1; blr;
printf("res: %i\n", Hypervisor::ExecuteHypervisorPayload(ppc, 8, 0, 0, 0, 0));