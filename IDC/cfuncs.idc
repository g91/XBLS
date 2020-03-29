#include <idc.idc>

static DoSearchAndLabel(diff, name, binary)
{
	auto currAddr;
	currAddr = 0;
	currAddr = FindBinary(currAddr, SEARCH_DOWN, binary);
	if(currAddr != BADADDR)
	{
		MakeNameEx(currAddr+diff, name, 0);
	}
}

static DoSaveRestGprSearch()
{
	auto currAddr, i;

	for(currAddr=0; currAddr != BADADDR; currAddr=currAddr+4)
	{
		currAddr = FindBinary(currAddr, SEARCH_DOWN, "F9 C1 FF 68 F9 E1 FF 70");
		if(currAddr == BADADDR)
			break;
		for(i=14; i<=31; i++)
		{
			MakeUnknown(currAddr, 4, 0); // DOUNK_SIMPLE
			MakeCode(currAddr);
			if(i != 31)
				MakeFunction(currAddr, currAddr + 4);
			else
				MakeFunction(currAddr, currAddr + 0x0C);
			MakeNameEx(currAddr, form("__savegprlr_%d", i), 0);
			currAddr = currAddr + 4;
		}
	}
	
	for(currAddr=0; currAddr != BADADDR; currAddr=currAddr+4)
	{
		currAddr = FindBinary(currAddr, SEARCH_DOWN, "E9 C1 FF 68 E9 E1 FF 70");
		if(currAddr == BADADDR)
			break;
		for(i=14; i<=31; i++)
		{
			MakeUnknown(currAddr, 4, 0);
			MakeCode(currAddr);
			if(i != 31)
				MakeFunction(currAddr, currAddr + 4);
			else
				MakeFunction(currAddr, currAddr + 0x10);
			MakeNameEx(currAddr, form("__restgprlr_%d", i), 0);
			currAddr = currAddr + 4;
		}
	}
}

static main()
{
	DoSaveRestGprSearch();
	
	// Basic C functions
	DoSearchAndLabel(0, "memset", "38 05 00 01 7C 09 03 A6 60 66 00 00 48 00 00 10");
	DoSearchAndLabel(0, "memcpy", "F8 61 FF F8 54 66 07 7E 7C 00 22 2C 28 06 00 00"); // This is how it was in the xbox kernel
	DoSearchAndLabel(0, "memcpy", "F8 61 FF F8 54 66 07 7E 28 06 00 00 20 C6 00 08"); // This is how it was in the others
	DoSearchAndLabel(0, "strncmp", "7C A0 2B 79 7C A9 03 A6 40 81 00 3C 89 03 00 00");
	DoSearchAndLabel(0, "strncpy", "7C 6B 1B 78 2B 05 00 00 4D 9A 00 20 89 44 00 00");
	DoSearchAndLabel(0, "_stricmp", "39 23 FF FF 38 84 FF FF 8C C4 00 01 8C A9 00 01");
	DoSearchAndLabel(0, "strchr", "88 C3 00 00 2C 04 00 00 41 82 00 1C 2C 86 00 00 7C 06 20 00 41 86 00 20 41 82 00 20 8C C3 00 01");
	
	
	// Winapi functions
	DoSearchAndLabel(0, "wcslen", "7C 6B 1B 78 A1 4B 00 00 39 6B 00 02 28 0A 00 00");
	DoSearchAndLabel(0, "wctomb", "7C 6B 1B 78 2B 0B 00 00 4D 9A 00 20 54 8A 04 3E");
	DoSearchAndLabel(0, "lstrcatW", "A1 43 00 00 7C 6B 1B 78 48 00 00 08 A5 4B 00 02 28 0A 00 00 40 82 FF F8 7D 64 58 50 A1 44 00 00");
	DoSearchAndLabel(0, "lstrcatA", "7C 6B 1B 78 89 4B 00 00 39 6B 00 01 2B 0A 00 00 40 9A FF F4 39 6B FF FF 89 44 00 00 38 84 00 01");
	DoSearchAndLabel(0, "lstrcpyA", "7D 64 18 50 89 44 00 00 28 0A 00 00 7D 4B 21 AE 38 84 00 01 40 82 FF F0 4E 80 00 20");
	DoSearchAndLabel(0, "lstrcpyW", "7D 64 18 50 A1 44 00 00 28 0A 00 00 7D 4B 23 2E 38 84 00 02 40 82 FF F0 4E 80 00 20");
	DoSearchAndLabel(0, "lstrcpynA", "7C 6B 1B 78 2F 05 00 00 4D 9A 00 20 7D 23 20 50 7D 49 58 AE 28 0A 00 00 41 82 00 14 99 4B 00 00");
	DoSearchAndLabel(0, "lstrcpynW", "7C 6B 1B 78 2F 05 00 00 4D 9A 00 20 7D 23 20 50 7D 49 5A 2E 28 0A 00 00 41 82 00 14 B1 4B 00 00");
	DoSearchAndLabel(0, "lstrlenA", "7C 6B 1B 78 89 4B 00 00 39 6B 00 01 2B 0A 00 00 40 9A FF F4 7D 63 58 50 39 6B FF FF 55 63 00 3E");
	
	// Other Functions
	DoSearchAndLabel(0, "_blkmov", "38 05 00 01 60 66 00 00 7C 09 03 A6 48 00 00 18");
	DoSearchAndLabel(0, "compare_diff", "7C 8B 23 78 7C C9 33 78 7F 06 58 40 40 98 00 30");
	DoSearchAndLabel(0, "compare_same", "FB E1 FF F8 7C A8 2B 78 7C 89 23 78 38 C0 00 00");
}
