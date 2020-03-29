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
	
	// 360 Crypto functions
	DoSearchAndLabel(0, "XeCryptBnDw_Copy", "28 05 00 00 7F 23 20 40 7C 83 20 50 7C A9 03 A6 4D C2 00 20 4D DA 00 20 80 C3 00 00 7C C3 21 2E 38 63 00 04 43 20 FF F4 4E 80 00 20");
	//DoSearchAndLabel(0, "XeCryptHmacSha", "");
	//DoSearchAndLabel(0, "XeCryptHmacShaFinal", "");
	DoSearchAndLabel(-8, "XeCryptHmacShaInit", "F8 21 FF 01 3D 60 67 45 7C 7F 1B 78 61 67 23 01 3D 60 EF CD 3B 60 00 00 61 68 AB 89 3D 60 98 BA");
	DoSearchAndLabel(0, "XeCryptMemDiff", "2C 05 00 00 7C A9 03 A6 38 E0 00 00 41 82 00 24 88 C4 00 00 88 A3 00 00 48 00 00 0C 8C C4 00 01");
	DoSearchAndLabel(0, "XeCryptRc4Ecb", "28 05 00 00 4D C2 00 20 7C A9 03 A6 88 C3 01 00 88 E3 01 01 38 C6 00 01 54 C6 06 3E 7D 03 30 AE");
	DoSearchAndLabel(0, "XeCryptRc4Key", "3C C0 00 01 3C E0 08 08 60 C6 02 03 60 E7 08 08 78 C6 07 C6 78 E7 00 0E 64 C6 04 05 39 00 00 08");
	DoSearchAndLabel(0, "XeCryptRotSum", "E8 E3 00 00 E9 23 00 08 E8 C3 00 10 E9 43 00 18 48 00 00 48 E9 64 00 00 7D 0B 4A 14 39 20 00 01");
	DoSearchAndLabel(-8, "XeCryptRotSumSha", "F8 21 FF 01 39 60 00 00 7C 9E 23 78 7C 7F 1B 78");
	DoSearchAndLabel(-8, "XeCryptSha", "F8 21 FF 21 39 60 00 00 7C BE 2B 78 7C DF 33 78 7C FC 3B 78 7D 1D 43 78 91 61 00 50 3D 60 67 45");
	DoSearchAndLabel(-8, "XeCryptShaFinal", "F8 21 FF 61 7C 7F 1B 78 7C 99 23 78 3B DF 00 18 7C BA 2B 78 38 80 00 00 81 7F 00 00 55 7D 06 BE");
	DoSearchAndLabel(0, "XeCryptShaInit", "3D 40 67 45 3D 20 EF CD 3D 00 98 BA 3C E0 10 32 3C C0 C3 D2 39 60 00 00 61 4A 23 01 61 29 AB 89");
	DoSearchAndLabel(-12, "XeCryptShaTransform", "7C 77 1B 78 7C 83 23 78 38 A0 00 10 38 81 00 50 3B 41 00 50 83 77 00 00 83 97 00 04 83 B7 00 08");
	DoSearchAndLabel(0, "XeCryptShaUpdate", "F8 21 FF 71 7C 7D 1B 78 7C BF 2B 78 7C 9E 23 78 81 7D 00 00 55 7C 06 BE 7D 6B FA 14 2B 1C 00 00");
	
	// Basic bootloader functions
	DoSearchAndLabel(4, "panic", "00 00 00 00 38 00 00 00 7C 18 23 A6 4B FF FF F8 00 00 00 00");
	DoSearchAndLabel(0, "post_output", "78 84 C1 C6 F8 83 00 00 4E 80 00 20");
	
	// Compression Functions
	DoSearchAndLabel(-8, "LDICreateDecompression", "F8 21 FF 61 7C 7C 1B 78 7D 38 4B 78 7C 9B 23 78 7C BA 2B 78 7C D9 33 78 81 7C 00 00 7C FD 3B 78");
	DoSearchAndLabel(0, "LDIDecompress", "7D 88 02 A6 91 81 FF F8 FB E1 FF F0 94 21 FF 90 3D 40 43 49 81 63 00 00 39 20 00 00 61 4A 44 4C");
	DoSearchAndLabel(0, "LDIResetDecompression", "7D 88 02 A6 F9 81 FF F8 F8 21 FF A1 3D 40 43 49 81 63 00 00 61 4A 44 4C 7F 0B 50 40 41 9A 00 0C 38 60 00 02 48 00 00 10 38 63 00 10");
	DoSearchAndLabel(0, "LDISetWindowData", "7D 88 02 A6 F9 81 FF F8 F8 21 FF A1 3D 40 43 49 81 63 00 00 61 4A 44 4C 7F 0B 50 40 41 9A 00 0C 38 60 00 02 48 00 00 14 38 63 00 10");
	DoSearchAndLabel(-40, "LZX_DecodeNewGroup", "39 60 00 00 91 7F 2E DC 38 21 00 60 E9 81 FF F8 7D 88 03 A6 EB E1 FF F0 4E 80 00 20");
	DoSearchAndLabel(-8, "LZX_Decode", "F8 21 FF 91 7C CB 07 B4 7C 7F 1B 78 7D 6B 2A 14 7C 9E 23 78 39 6B 00 04 7D 3D 4B 78 F8 BF 2B 08 F8 FF 2B 18 F9 7F 2B 10");
	DoSearchAndLabel(0, "LZX_DecodeInsertDictionary", "7D 88 02 A6 F9 81 FF F8 FB C1 FF E8 FB E1 FF F0 F8 21 FF 91 7C 7E 1B 78 7C BF 2B 78 81 7E 00 08 7F 1F 58 40 40 99 00 0C 38 60 00 00 48 00 00 40");
	DoSearchAndLabel(-32, "LZX_DecodeInit", "39 7E FF FF 93 DF 00 08 7D 6A F0 38 2B 0A 00 00 91 7F 00 0C 41 9A 00 0C 38 60 00 00 48 00 00 20");
	DoSearchAndLabel(-16, "allocate_decompression_memory", "7C 7F 1B 78 39 60 00 04 81 3F 00 08 99 7F 2E C5 89 5F 2E C5 38 E0 00 01 7D 0A FA 14 39 4A 00 01");
	DoSearchAndLabel(-8, "build_global_tables", "3D 60 01 01 39 40 00 00 61 6B 02 02 39 20 00 02 39 00 00 04 38 E0 00 06 38 C0 00 0A 91 43 2F 08");
	DoSearchAndLabel(-20, "copy_data_to_output", "7C 7F 1B 78 7C 9E 23 78 7C A4 2B 78 7F C5 07 B4 E8 7F 2B 18");
	DoSearchAndLabel(0, "dec_free", "7C 6B 1B 78 E9 6B 2E F8 2B 2B 00 00 4D 9A 00 20 7C 83 23 78 7D 69 03 A6 4E 80 04 20");
	DoSearchAndLabel(0, "dec_malloc", "7C 6B 1B 78 E9 4B 2E F0 2B 2A 00 00 41 9A 00 10 7C 83 23 78 7D 49 03 A6 4E 80 04 20 E8 6B 2F 00");
	//DoSearchAndLabel(0, "decode_aligned_offset_block", "");
	DoSearchAndLabel(-12, "decode_data", "3B 40 00 00 7C 7F 1B 78 7C 9C 23 78 7F 5B D3 78 48 00 02 44 81 7F 2E EC 2F 0B 00 01 40 9A 02 08");
	DoSearchAndLabel(0, "decode_uncompressed_block", "7C 6B 1B 78 7C C4 2A 14 7C 89 23 78 E9 4B 2B 08 48 00 00 28 E9 0B 2B 10 7F 2A 40 40 40 98 00 80");
	//DoSearchAndLabel(0, "decode_verbatim_block", "");
	DoSearchAndLabel(0, "decoder_misc_init", "39 60 00 00 39 40 00 01 91 63 2E D0 91 43 00 10 91 43 00 14 91 43 00 18 91 63 2B 20 91 43 2E EC");
	DoSearchAndLabel(0, "decoder_translate_e8", "39 60 00 00 91 63 2E D8 4E 80 00 20");
	DoSearchAndLabel(-8, "fast_decode_aligned_offset_block", "7C 6B 1B 78 7F C4 2A 14 EB 8B 2B 10 EB AB 00 00 89 2B 2E C4 81 4B 2E C0 EB EB 2B 08 48 00 03 78");
	DoSearchAndLabel(-8, "fast_decode_verbatim_block", "7C 6B 1B 78 7F E4 2A 14 EB CB 2B 10 88 EB 2E C4 81 4B 2E C0 E8 AB 2B 08 48 00 02 A4 79 49 55 A2");
	DoSearchAndLabel(0, "fillbuf", "81 43 2E C0 89 63 2E C4 7D 64 58 50 7D 6B 07 74 2F 0B 00 00 99 63 2E C4 7D 48 20 30 91 03 2E C0");
	DoSearchAndLabel(-16, "getbits", "81 63 2E C0 21 44 00 20 7D 7F 54 30");
	DoSearchAndLabel(0, "handle_beginning_of_uncompressed_block", "E9 63 2B 08 E9 43 2B 10 39 6B FF FE 39 2B 00 04 7F 29 50 40 F9 63 2B 08 41 98 00 0C 38 60 00 00");
	//DoSearchAndLabel(0, "init_decoder_input", ""); // This one branches to initialise_decoder_bitbuf
	DoSearchAndLabel(0, "init_decoder_translation", "39 60 00 00 91 63 2E D8 4E 80 00 20");
	DoSearchAndLabel(0, "initialise_decoder_bitbuf", "81 63 2E E8 2F 0B 00 03 4D 9A 00 20 E9 63 2B 08 E9 23 2B 10 39 4B 00 04 7F 2A 48 40 4D 99 00 20");
	DoSearchAndLabel(-12, "make_table", "3B 20 00 00 7C 9A 23 78 7C B8 2B 78 7C FD 3B 78 7D 1B 43 78 39 41 00 A4 7F 29 CB 78 39 60 00 10");
	DoSearchAndLabel(-12, "make_table_8bit", "38 C0 00 01 7C 9E 23 78 7C BD 2B 78 7C CB 33 78 7C CA 33 78 3B E0 00 00 39 4A 00 01 55 69 0B FC");
	DoSearchAndLabel(-12, "read_aligned_offset_tree", "7C 7F 1B 78 3B C0 00 08 3B 9F 0E 38 7F 9D E3 78 38 80 00 03 7F E3 FB 78");
	DoSearchAndLabel(-20, "read_main_and_secondary_trees", "7C 7F 1B 78 38 80 01 00 3B DF 0A 1C 38 BF 2B 24 7F C6 F3 78");
	DoSearchAndLabel(-16, "reset_decoder_trees", "7C 7F 1B 78 38 80 00 00 38 7F 0A 1C 89 7F 2E C5 39 6B 00 20 55 6B 18 38 7D 65 07 B4");
}
