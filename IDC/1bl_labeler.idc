#include <idc.idc>

#define _1BL_MAGIC 0x00000000
#define _1BL_CODE_START 0x00000008
#define _1BL_MS_SIG_ADDR 0x00000012
#define _1BL_MS_SIG_SIZE 0x0000008D
#define DATA_SECTION_START_PTR 0x000000FC
#define SOME_ADDR_TBL 0x00005840
#define SOME_ADDR_TBL_SIZE 0x00000038
#define NAND_ADDR_PTR 0x00005860
#define RTOC_VAL_PTR 0x00005868
#define _1BL_KEY_ADDR 0x00005878
#define _1BL_KEY_SIZE 0x00000010
#define _2BL_RSA_SALT_ADDR 0x00005888
#define _2BL_RSA_SALT_SIZE 0x0000000A

static DoMakeAndLabelCode(addr, size, name)
{
	MakeName(addr, name);
	MakeCode(addr);
	MakeFunction(addr, addr+size);
}

static DoMakeQWordTable(addr, size)
{
	auto i;
	for (i = 0; i < size; i = i + 8)
	{
		MakeQword(addr+i);
	}
}

static main()
{
	MakeDword(_1BL_MAGIC);
	MakeName(_1BL_MAGIC, "MAGIC");
	MakeDword(0x04);
	MakeDword(_1BL_CODE_START);
	MakeName(_1BL_CODE_START, "CODE_START");
	MakeWord(0x0C);
	MakeDword(0x0E);
	MakeStr(_1BL_MS_SIG_ADDR, _1BL_MS_SIG_SIZE);
	MakeName(_1BL_MS_SIG_ADDR, "copywrite");
	MakeDword(DATA_SECTION_START_PTR);
	MakeName(DATA_SECTION_START_PTR, "DATA_SEC_START");
	DoMakeAndLabelCode(0x00000100, 0x00000028, "start");
	DoMakeAndLabelCode(0x00000128, 0x00000020, "start_2_stage");
	DoMakeAndLabelCode(0x00000200, 0x00000028, "func_00000200");
	DoMakeAndLabelCode(0x00000300, 0x00000028, "func_00000300");
	DoMakeAndLabelCode(0x00000380, 0x00000028, "func_00000380");
	DoMakeAndLabelCode(0x00000400, 0x00000028, "func_00000400");
	DoMakeAndLabelCode(0x00000480, 0x00000028, "func_00000480");
	DoMakeAndLabelCode(0x00000500, 0x00000028, "func_00000500");
	DoMakeAndLabelCode(0x00000600, 0x00000028, "func_00000600");
	DoMakeAndLabelCode(0x00000700, 0x00000028, "func_00000700");
	DoMakeAndLabelCode(0x00000800, 0x00000028, "func_00000800");
	DoMakeAndLabelCode(0x00000900, 0x00000028, "func_00000900");
	DoMakeAndLabelCode(0x00000980, 0x00000028, "func_00000980");
	DoMakeAndLabelCode(0x00000C00, 0x00000028, "func_00000C00");
	DoMakeAndLabelCode(0x00000D00, 0x00000028, "func_00000D00");
	DoMakeAndLabelCode(0x00000F20, 0x00000028, "func_00000F20");
	DoMakeAndLabelCode(0x00001600, 0x00000028, "func_00001600");
	DoMakeAndLabelCode(0x00001800, 0x00000028, "func_00001800");
	DoMakeAndLabelCode(0x00003000, 0x00000274, "main");
	DoMakeAndLabelCode(0x00003000, 0x00000274, "main");
	DoMakeAndLabelCode(0x000032C4, 0x0000014C, "func_000032C4");
	DoMakeAndLabelCode(0x00003410, 0x00000040, "copy_128_bits_by_block");
	DoMakeAndLabelCode(0x00003450, 0x0000007C, "func_00003450");
	DoMakeAndLabelCode(0x000034D0, 0x000000D8, "func_000034D0");
	DoMakeAndLabelCode(0x000035A8, 0x000000AC, "func_000035A8");
	DoMakeAndLabelCode(0x00003658, 0x0000004C, "func_00003658");
	DoMakeAndLabelCode(0x000036A8, 0x00000048, "func_000036A8");
	DoMakeAndLabelCode(0x000036F0, 0x00000054, "func_000036F0");
	DoMakeAndLabelCode(0x00003748, 0x00000044, "func_00003748");
	DoMakeAndLabelCode(0x00003790, 0x00000040, "func_00003790");
	DoMakeAndLabelCode(0x000037D0, 0x00000040, "func_000037D0");
	DoMakeAndLabelCode(0x00003810, 0x00000068, "func_00003810");
	DoMakeAndLabelCode(0x00003878, 0x0000003C, "func_00003878");
	DoMakeAndLabelCode(0x000038B8, 0x0000010C, "func_000038B8");
	DoMakeAndLabelCode(0x000039C8, 0x00000114, "func_000039C8");
	DoMakeAndLabelCode(0x00003AE0, 0x0000004C, "func_00003AE0");
	DoMakeAndLabelCode(0x00003B30, 0x00000080, "func_00003B30");
	DoMakeAndLabelCode(0x00003BB0, 0x000000C8, "func_00003BB0");
	DoMakeAndLabelCode(0x00003C78, 0x00000090, "func_00003C78");
	DoMakeAndLabelCode(0x00003D08, 0x000000D8, "func_00003D08");
	DoMakeAndLabelCode(0x00003DE0, 0x000001A8, "func_00003DE0");
	DoMakeAndLabelCode(0x00003F88, 0x0000007C, "func_00003F88");
	DoMakeAndLabelCode(0x00004008, 0x00000078, "func_00004008");
	DoMakeAndLabelCode(0x00004080, 0x00000014, "func_00004080");
	DoMakeAndLabelCode(0x00004098, 0x000001A4, "func_00004098");
	DoMakeAndLabelCode(0x00004240, 0x00000250, "load_next_stage");
	DoMakeAndLabelCode(0x00004490, 0x00000038, "func_00004490");
	DoMakeAndLabelCode(0x000044D0, 0x0000000C, "func_000044D0");
	DoMakeAndLabelCode(0x000044E0, 0x0000000C, "func_000044E0");
	DoMakeAndLabelCode(0x000044F0, 0x0000000C, "post_output");
	DoMakeAndLabelCode(0x00004500, 0x0000000C, "panic");
	DoMakeAndLabelCode(0x00004510, 0x00000048, "int_check");
	DoMakeAndLabelCode(0x00004558, 0x000000FC, "XeCryptBnQwBeSigFormat");
	DoMakeAndLabelCode(0x00004658, 0x000000C0, "XeCryptBnQwBeSigVerify");
	DoMakeAndLabelCode(0x00004718, 0x00000074, "XeCryptRotSum");
	DoMakeAndLabelCode(0x00004790, 0x00000108, "XeCryptRotSumSha");
	DoMakeAndLabelCode(0x000048A0, 0x000000A8, "XeCryptRc4Key");
	DoMakeAndLabelCode(0x00004948, 0x00000060, "XeCryptRc4Ecb");
	DoMakeAndLabelCode(0x000049A8, 0x00000048, "XeCryptShaInit");
	DoMakeAndLabelCode(0x000049F0, 0x0000049C, "XeCryptShaTransform");
	DoMakeAndLabelCode(0x00004E90, 0x0000011C, "XeCryptShaUpdate");
	DoMakeAndLabelCode(0x00004FB0, 0x000000C8, "XeCryptShaFinal");
	DoMakeAndLabelCode(0x00005078, 0x00000108, "XeCryptHmacShaInit");
	DoMakeAndLabelCode(0x00005180, 0x00000050, "XeCryptHmacShaFinal");
	DoMakeAndLabelCode(0x000051D0, 0x00000098, "XeCryptHmacSha");
	DoMakeAndLabelCode(0x00005270, 0x0000022C, "XeCryptBnQwNeModMul");
	DoMakeAndLabelCode(0x000054A0, 0x00000020, "XeCryptBnDw_Copy");
	DoMakeAndLabelCode(0x000054C8, 0x00000020, "XeCryptBnQw_Copy");
	DoMakeAndLabelCode(0x000054F0, 0x00000024, "savegpr14");
	DoMakeAndLabelCode(0x00005514, 0x00000004, "savegpr23");
	DoMakeAndLabelCode(0x00005518, 0x00000004, "savegpr24");
	DoMakeAndLabelCode(0x0000551C, 0x00000004, "savegpr25");
	DoMakeAndLabelCode(0x00005520, 0x00000004, "savegpr26");
	DoMakeAndLabelCode(0x00005524, 0x00000004, "savegpr27");
	DoMakeAndLabelCode(0x00005528, 0x00000004, "savegpr28");
	DoMakeAndLabelCode(0x0000552C, 0x00000014, "savegpr29");
	DoMakeAndLabelCode(0x00005540, 0x00000024, "restoregpr14");
	DoMakeAndLabelCode(0x000055A0, 0x000000A8, "memcpy");
	DoMakeAndLabelCode(0x00005650, 0x000000A0, "memset");
	DoMakeAndLabelCode(0x000056F0, 0x00000038, "XeCryptMemDiff");
	DoMakeQWordTable(SOME_ADDR_TBL, SOME_ADDR_TBL_SIZE);
	MakeName(NAND_ADDR_PTR, "NAND_ADDR");
	MakeName(RTOC_VAL_PTR, "RTOC_VAL");
	MakeArray(_1BL_KEY_ADDR, _1BL_KEY_SIZE);
	MakeName(_1BL_KEY_ADDR, "_1BL_KEY");
	MakeArray(_2BL_RSA_SALT_ADDR, _2BL_RSA_SALT_SIZE);
	MakeName(_2BL_RSA_SALT_ADDR, "RSA_SALT");
}
