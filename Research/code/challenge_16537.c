// reversed by teir
// tried to make it as optimized as I could while not disrupting the flow
// version: 0x4099 - 16537

// some of this was edited to make some people happy

#define BIT_MASK64(n) (~( ((~0ull) << ((n)-1)) << 1 ))
#define extrdi(inp, n, b) ((inp >> 64-(n+b)) & BIT_MASK64(n))
// eg: extrdi r4, r12, 10, 48 = [r4 = extrdi(r12, 10, 48)]
// eg: r4 = extrdi(r12, 10, 48) = [r4 = ((r12 >> 6) & BIT_MASK64(10))]

#define SRAM 0x8000020000010000

/*
0x50 hash info
*/
QWORD xAddy[0xD] = {
	0x34000C, 			// HV 0x34-0x3F, 0xC bytes
	0x400030, 			// HV 0x40-0x6F, 0x30 bytes
	0x700004, 			// HV 0x70-0x73, 4 bytes
	0x780008, 			// HV 0x78-0x7F, 8 bytes
	0x8081FF, 			// SRAM 0x2-0x3FF, 0x3FE bytes ; HV 0x80-0xFFFF
	0x2000100C00040, 	// HV 0x100C0-0x100FF, 0x40 bytes
	0x2000103500030, 	// HV 0x10350-0x1037F, 0x30 bytes
	0x20001038080BB, 	// SRAM 0x40E-0x583, 0x176 bytes ; HV 0x10380-0x160FF
	0x2000161000040, 	// HV 0x16100-0x1613F, 0x40 bytes
	0x200016D200060, 	// HV 0x16D20-0x16D7F, 0x60 bytes
	0x200016D808125, 	// SRAM 0x5B6-0x7FF, 0x24A bytes ; HV 0x16D80-0x1FFFF
	0x4000200008200, 	// SRAM 0x800-0xBFF, 0x400 bytes ; HV 0x20000-0x2FFFF
	0x6000300008200  	// SRAM 0xC00-0xFFF, 0x400 bytes ; HV 0x30000-0x3FFFF 
};

// 0xEC hash info
// this should give a good idea on whats the same for all consoles / bootups
QWORD zAddy[7] = {
	0x340040, 			// 0x34-0x74, 0x40 bytes
	0x78FF88, 			// 0x78-0x1000, 0xF88 bytes
	0x2000100C00040, 	// 0x2000100C0-0x200010100, 0x40 bytes
	0x2000103505DF0, 	// 0x200010350-0x200011140, 0xDF0 bytes
	0x200016D2092E0, 	// 0x200016D20-0x200017000, 0x3E0 bytes
	0x400020000FFFC, 	// 0x400020000-0x400020FFC, 0xFFC bytes
	0x600030000FFFC 	// 0x600030000-0x600030FFC, 0xFFC bytes
};

typedef struct {
	QWORD qwPad[5];
	QWORD qwMagicBuildQFE;
	QWORD qwKernelVersion;
	DWORD dwXeKeysFlags;
	DWORD dwUnk74; // ??
	QWORD qwRTOC;
	QWORD qwHRMOR;
	BYTE pbRenamedHash[0x14]; // 0x50
	BYTE pbCPUKeyHash[0x14]; // cpu key hash
	BYTE pbBuf[0x80]; // <removed, renamed>
	WORD wPageAddy; // looks like the memory page the response is located in?
	BYTE pbHvHash[6]; // 0xEC hash - NOTE: HASH THIS AS 20 BYTES BUT ONLY WRITE THE LAST 6 BYTES. in the challenge the above variables overwrite the first 14 bytes
} CHALLENGE_RESPONSE;

// Function from the HV
// Challenge doesn't use the HV function but does the same thing when its called
// Why not just use the HV function?
// sub_EE4
void FillCacheLines(QWORD Address, QWORD cCacheline)
{
	for(int i = 0; i < cCacheline; i++)
	{
		*Address+(i*0x80) = *(BYTE*)Address+(i*0x80);
		__dcbst(Address+(i*0x80));
	}
	__sync();
	__isync();
}

QWORD PhysicalToReal(QWORD arg1, QWORD arg2)
{
	if((DWORD)(arg1-4) > 0x1FFBFFFF)
		MACHINE_CHECK();
	if((DWORD)arg2 > (DWORD)(arg1-0x20000000))
		MACHINE_CHECK();
	return (arg1 & 0xFFFFFFFF) | 0x8000000000000000;
}

QWORD Challenge_16537(QWORD retbuf, QWORD HvSalt, QWORD krnlbuild)
{
	// NOTE: All addresses in the response file are offset by 0x20
	QWORD resp = retbuf + 0x20;

	// copy some stuff from the hv and misc registers
	*resp+8 = *(QWORD*)0; // hv magic + build + qfe
	*resp+0x10 = *(QWORD*)0x10; // kernel version
	*resp+0x18 = *(DWORD*)0x30; // XeKeys Flags
	*resp+0x1C = *(DWORD*)0x74;
	*resp+0x20 = 0x0000000200000000; // r2
	*resp+0x28 = 0x0000010000000000; // HRMOR

	HvSalt = PhysicalToReal(HvSalt, 0x1000);

	// start the first hash, location 0xEC in the response file
	XECRYPT_SHA_STATE sha;
	XeCryptShaInit(&sha);
	XeCryptShaUpdate(&sha, HvSalt, 0x10); // hash the salt first
	for(int i = 0; i < 7; i++)
		XeCryptShaUpdate(&sha, zAddy[i] >> 16, zAddy[i] & 0xFFF);
	XeCryptShaFinal(&sha, resp+0xCC, 0x14);

	XeCryptShaInit(&sha);

	// checking the address? purpose unknown but doesn't seem to effect online status
	QWORD tmp = resp + 0x3E0;
	*resp+0xD8 = (WORD)((tmp >> 16) & 0xFFFF);

	// <info removed>
	QWORD tmp = 0x01BB;
	for(int i = 0; i < 8; i++)
	{
		*tmp+(i*0x10) = *(QWORD*)HvSalt;
		*tmp+(i*0x10)+8 = *(QWORD*)HvSalt+8;
	}
	__dcbst(resp+0x3E0);
	__sync();


	// start the second hash, location 0x50 in the response file
	tmp = SRAM + (0xF800 | ((resp+0x3E0 >> 6) & 0x3FF)); // 0x50 salt, offset formula is different - look into later
	XeCryptShaUpdate(&sha, tmp, 2);
	for(int i = 0; i < 0xD; i++)
	{
		// <info removed>
		if(xAddy[i] & 0x8000)
		{
			FillCacheLines(xAddy[i] >> 16, xAddy[i] & 0x3FF);
			XeCryptShaUpdate(&sha, SRAM+((xAddy[i] >> 22) & 0xFFF), (xAddy[i] & 0x3FF) << 1);
		}
		else
		{
			FillCacheLines(xAddy[i] >> 16, 1);
			if((xAddy[i] & 0x7F) >= 0x10)
				XeCryptShaUpdate(&sha, (((xAddy[i] >> 16) & 0x3FFFF) | 0x8000000000000000), xAddy[i] & 0x7F);
			else
				XeCryptShaUpdate(&sha, xAddy[i] >> 16, xAddy[i] & 0x7F);
		}
	}
	XeCryptShaFinal(&sha, resp+0x30, 0x14);

	// hash the cpukey, location 0x64 in the response file
	XeCryptShaInit(&sha);
	XeCryptShaUpdate(&sha, 0x20, 0x10);
	XeCryptShaFinal(&sha, resp+0x44, 0x14);

	// copy other data from the HV, location 0x78 in the response file
	// <info removed>
	resp += 0x58;
	QWORD HvData = 0x200010040;
	for(int i = 0; i < 0x10; i++)
		*resp+(i*8) = *(QWORD*)HvData+(i*8);

	// done
	return 0;
}
