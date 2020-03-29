// version: 0x23E4
// entry: 0x3C0
// size: 0x1AC0

// registers preset by the 1bl
// r27: not used
// r28: not used
// r29: not used
// r30: not used
// r31: next bl (cbb nand offset)
//	CB_A nand offset + CB_A size aligned to the upper 0x10 byte (ex: size = (size+0xF) & 0xFFFFFFF0)

#define STACK 	0x800002000001F700 // r1
#define TOC 	0x800002000001C000 // r2
#define SRAM	0x8000020000010000
#define POSTo 	0x8000020000061010
#define NAND	0x80000200C8000000
#define SOC	0x8000020000020000

// an attempt to make this easier to read
#define read64(addy) *(QWORD*)addy
#define read32(addy) *(DWORD*)addy
#define read16(addy) *(WORD*)addy
#define write64(addy, data) *(QWORD*)addy = data
#define write32(addy, data) *(DWORD*)addy = data
#define write16(addy, data) *(WORD*)addy = data

typedef struct _BLHeader
{
	WORD Magic;			// 0 : 2
	WORD Version;		// 2 : 2
	DWORD Flags;		// 4 : 4
	DWORD EntryPoint;	// 8 : 4
	DWORD Size;			// 0xC : 4
	BYTE key[0x10];		// 0x10 : 0x10
	QWORD Pad[4];		// 0x20 : 0x20
	XECRYPT_SIG Sig;	// 0x40 : 0x100
	// Header: 0x140
}BLHeader, *PBLHeader;

void POST(BYTE postCode)
{
	write64(POSTo, (postCode << 56));
}

void PanicGen()
{
	while(1)
		continue;
}

void Panic(QWORD postCode)
{
	POST(postCode);
	PanicGen();
}

bool VerifyOffset(DWORD offset, DWORD arg2)
{
	if(offset != (offset + 0xF) & 0xFFFFFFF0)
		return false;
	if(offset - 0x80 > 0x7FFFF7F)
		return false;
	if(arg2 & 0xFFFFFFF0 >= offset - 0x8000000)
		return false;
	return true;
}

// Copies by 0x10 byte blocks
// cBlocks: how many 0x10 byte blocks to copy
void CopyBy128(QWORD dest, QWORD src, DWORD cBlocks)
{
	for(int i = 0; i < cBlocks; i++)
	{
		write64(dest+(i*0x10), read64(src+(i*0x10)));
		write64(dest+(i*0x10)+8, read64(src+(i*0x10)+8))
	}
}

void ZeroBy128(QWORD addy, QWORD count)
{
	for(int i = 0; i < count; i++)
	{
		write64(addy+(i*0x10), 0ULL);
		write64(addy+(i*0x10)+8, 0ULL);
	}

}

QWORD getFuseline(DWORD fuse)
{
	if ((fuse * 0x40) < 0x300)
		return read64(SOC + ((fuse * 0x40) << 3));
	return 0;
}

void CBB_Jump(QWORD EntryPoint, QWORD NextBL)
{
	// presets for the next bootloader
	QWORD r27 = read64(SRAM + 0x20);
	QWORD r28 = read64(SRAM + 0x28);
	QWORD r29 = read64(SRAM + 0x30);
	QWORD r30 = read64(SRAM + 0x38);
	QWORD r31 = NextBL; // nand offset of the next bl

	// null the beginning of the cbb
	ZeroBy128(SRAM + 0x20, 0x12);

	DWORD tSize = (read32(SRAM + 0xC) + 0xF) & 0xFFFFFFF0;
	if(tSize > 0xC000)
		Panic(0xF3);

	// null the area after the cbb
	ZeroBy128(SRAM + tSize, (0xC000 - tSize) >> 4);

	// Sets r0-r26 and the CTR to 0

	// jump to cbb
	EntryPoint = (EntryPoint & 0xFFFF) + 0x2000000;
	goto EntryPoint;
}

void CBB_Load(const QWORD offCBB, QWORD destCBB)
{
	// sanity notes
	// r27 = TOC
	// r29 = destCBB - sram
	// r24 = offCBB
	// r30 = SOC
	// r31 = POST
	// r28 = r24 & 0xFFFFFFFF
	// r26 = NAND + r28

	// fuses:
	// 0x90: 0 - disable cpu jtag?
	// 0x98: 1 - retail/devkit?
	// 0xA0: 2 - CB LDV
	// 0xA8: 3 - CPUKey1
	// 0xB0: 4 - CPUKey1
	// 0xB8: 5 - CPUKey2
	// 0xC0: 6 - CPUKey2
	// 0xC8: 7 - LDV

	// first null the stack
	for(int i = 0; i < 0xB; i++)
		write64(stack-0x1A8+(i*8), 0ULL);

	POST(0xD1); // copy fuses for CBB decryption
	QWORD fuses[12] = { 0 };
	BYTE CPUKey[0x10] = { 0 };

	// if this is the mfg cb_a then the cpukey is set to 0
#ifdef RETAIL
	for(int i = 0; i < 12; i++)
		fuses[i] = getFuseline(i);
	QWORD fuse = fuses[3] | fuses[4]; // first CPUKey fuses
	write64(CPUKey, fuse);
	fuse = fuses[5] | fuses[6]; // second CPUKey fuses
	write64(CPUKey+8, fuse);
#endif

	POST(0xD2); // verify CBB offset
	DWORD cbbOffset = offCBB & 0xFFFFFFFF; // r28
	if(!VerifyOffset(cbbOffset, 0x10))
		Panic(0xF0);

	POST(0xD3); // copy cbb header to sram
	QWORD cbbAddy = NAND + cbbOffset;
	CopyBy128(destCBB, cbbAddy, 1);

	POST(0xD4); // verify header
	PBLHeader cbbHeader = (PBLHeader)destCBB;
	if((cbbHeader->Size - 0x3C0) > 0xBC40 // size check
		|| cbbHeader->Magic != read64(TOC) & 0xFFFF // magic check
		|| cbbHeader->EntryPoint & 0x3 // alignment check
		|| cbbHeader->EntryPoint < 0x3C0 // EntryPoint check
		|| cbbHeader->EntryPoint >= cbbHeader->Size & 0xFFFFFFFC // entrypoint/size relation check
		|| !VerifyOffset(cbbOffset, cbbHeader->Size))
		Panic(0xF1);

	POST(0xD5); // copy cbb to SRAM
	QWORD tSize = (cbbHeader->Size + 0xF) & 0xFFFFFFF0;
	CopyBy128(destCBB + 0x10, cbbAddy + 0x10, ((tSize - 0x10) >> 4) & 0xFFFFFFFF);

	POST(0xD6); // Gen cbb key
	// cbb key = hmacsha of the cb_a key, cb_b salt, and CPUKey
	XeCryptHmacSha(TOC+0x10, 0x10, &cbbHeader->key, 0x10, CPUKey, 0x10, 0, 0, &cbbHeader->key, 0x10);

	POST(0xD7); // set key
	XECRYPT_RC4_STATE rc4;
	XeCryptRc4Key(&rc4, &cbbHeader->key, 0x10);

	POST(0xD8); // decrypt cbb
	XeCryptRc4Ecb(&rc4, SRAM+0x20, tSize-0x20);

	POST(0xD9); // generate hash
	BYTE Hash[0x14] = { 0 };
	XeCryptRotSumSha(SRAM, 0x10, SRAM+0x140, tSize-0x140, Hash, 0x14);

	POST(0xDA); // verify integrity
	if(memcmp(Hash, TOC+0x39C, 0x14))
		Panic(0xF2);

	POST(0xDB); // jump to cbb
	write16(SRAM+6, read16(SRAM+6)); // copy flags
	CBB_Jump(cbbHeader->EntryPoint, tSize+offCBB);
	return;
}

void CBA_Main()
{
	// registers 27-31 are preset by the 1bl opon entry
	POST(0xD0); // CB_A entry, copy self to 0x800002000001C000 and continue from there
	DWORD size = *(QWORD*)SRAM+0xC;
	size = (size+0xF) >> 3;
	for(int i = 0; i < size; i++)
		write64(TOC+(i*8), read64(SRAM+(i*8)));

	// from now on we're executing from 0x800002000001C000
	CBB_Load(r31, SRAM);
}
