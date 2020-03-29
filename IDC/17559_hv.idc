#include <idc.idc>
 
static GetSyscallName( id )
{
    if(        id == 0x00000000)    return "HvxGetVersions";//
    else if(id == 0x00000001)    return "HvxStartupProcessors";//
    else if(id == 0x00000002)    return "HvxQuiesceProcessor";//
    else if(id == 0x00000003)    return "HvxFlushEntireTb";//
    else if(id == 0x00000004)    return "HvxFlushSingleTb";//
    else if(id == 0x00000005)    return "HvxRelocateAndFlush";
    else if(id == 0x00000006)    return "HvxGetSpecialPurposeRegister";//
    else if(id == 0x00000007)    return "HvxSetSpecialPurposeRegister";//
    else if(id == 0x00000008)    return "HvxGetSocRegister";//
    else if(id == 0x00000009)    return "HvxSetSocRegister";//
    else if(id == 0x0000000A)    return "HvxSetTimeBaseToZero";//
    else if(id == 0x0000000B)    return "HvxZeroPage";//
    else if(id == 0x0000000C)    return "HvxFlushDcacheRange";//
    else if(id == 0x0000000D)    return "HvxPostOutput";//
    else if(id == 0x0000000E)    return "HvxEnablePPUPerformanceMonitor";//
    else if(id == 0x0000000F)    return "HvxGetImagePageTableEntry";//
    else if(id == 0x00000010)    return "HvxSetImagePageTableEntry";//
    else if(id == 0x00000011)    return "HvxCreateImageMapping";//
    else if(id == 0x00000012)    return "HvxMapImagePage";//
    else if(id == 0x00000013)    return "HvxCompleteImageMapping";//
    else if(id == 0x00000014)    return "HvxLoadImageData";//
    else if(id == 0x00000015)    return "HvxFinishImageDataLoad";//
    else if(id == 0x00000016)    return "HvxStartResolveImports";//
    else if(id == 0x00000017)    return "HvxResolveImports";//
    else if(id == 0x00000018)    return "HvxFinishImageLoad";//
    else if(id == 0x00000019)    return "HvxAbandonImageLoad";//
    else if(id == 0x0000001A)    return "HvxUnmapImagePages";//
    else if(id == 0x0000001B)    return "HvxUnmapImage";//
    else if(id == 0x0000001C)    return "HvxUnmapImageRange";//
    else if(id == 0x0000001D)    return "HvxCreateUserMode";//
    else if(id == 0x0000001E)    return "HvxDeleteUserMode";//
    else if(id == 0x0000001F)    return "HvxFlushUserModeTb";//
    else if(id == 0x00000020)    return "HvxSetPowerMode";//
    else if(id == 0x00000021)    return "HvxShadowBoot";
    else if(id == 0x00000022)    return "HvxBlowFuses";//
    else if(id == 0x00000023)    return "HvxFsbInterrupt";//
    else if(id == 0x00000024)    return "HvxLockL2";//
    else if(id == 0x00000025)    return "HvxDvdAuthBuildNVPage";//
    else if(id == 0x00000026)    return "HvxDvdAuthVerifyNVPage";//
    else if(id == 0x00000027)    return "HvxDvdAuthRecordAuthenticationPage";//
    else if(id == 0x00000028)    return "HvxDvdAuthRecordXControl";//
    else if(id == 0x00000029)    return "HvxDvdAuthGetAuthPage";//
    else if(id == 0x0000002A)    return "HvxDvdAuthVerifyAuthPage";//
    else if(id == 0x0000002B)    return "HvxDvdAuthGetNextLBAIndex";//
    else if(id == 0x0000002C)    return "HvxDvdAuthVerifyLBA";//
    else if(id == 0x0000002D)    return "HvxDvdAuthClearDiscAuthInfo";//
    else if(id == 0x0000002E)    return "HvxKeysInitialize";//
    else if(id == 0x0000002F)    return "HvxKeysGetKeyProperties";//
    else if(id == 0x00000030)    return "HvxKeysGetStatus";//
    else if(id == 0x00000031)    return "HvxKeysGenerateRandomKey";//
    else if(id == 0x00000032)    return "HvxKeysGetFactoryChallenge";//
    else if(id == 0x00000033)    return "HvxKeysSetFactoryResponse";//
    else if(id == 0x00000034)    return "HvxKeysSaveBootLoader";//
    else if(id == 0x00000035)    return "HvxKeysSaveKeyVault";//
    else if(id == 0x00000036)    return "HvxKeysSetKey";//
    else if(id == 0x00000037)    return "HvxKeysGetKey";//
    else if(id == 0x00000038)    return "HvxKeysGetDigest";//
    else if(id == 0x00000039)    return "HvxKeysRsaPrvCrypt";//
    else if(id == 0x0000003A)    return "HvxKeysHmacSha";//
    else if(id == 0x0000003B)    return "HvxKeysAesCbc";//
    else if(id == 0x0000003C)    return "HvxKeysDes2Cbc";//
    else if(id == 0x0000003D)    return "HvxKeysDesCbc";//
    else if(id == 0x0000003E)    return "HvxKeysObscureKey";//
	
    else if(id == 0x00000041)    return "HvxKeysSaveSystemUpdate";//
    else if(id == 0x00000042)    return "HvxKeysExecute";//

    else if(id == 0x00000072)    return "HvxExpansionInstall";//
    else if(id == 0x00000073)    return "HvxExpansionCall";
    else if(id == 0x00000075)    return "HvxDvdAuthFwcr";//
    else if(id == 0x00000079)    return "HvxDvdAuthFcrt";//
    else if(id == 0x0000007B)    return "HvxDvdAuthEx";//
    else if(id == 0x0000007D)    return "HvxTest";
    else return form("HvxSyscall_%02X", id);
}
 
 
static SetupRegSaves()
{
    auto currAddr, i;
 
    // find all saves of gp regs
    for(currAddr=0; currAddr != BADADDR; currAddr=currAddr+4)
    {
        // find "std %r14, -0x98(%sp)" followed by "std %r15, -0x90(%sp)"
        currAddr = FindBinary(currAddr, SEARCH_DOWN, "F9 C1 FF 68 F9 E1 FF 70");
        if(currAddr == BADADDR)
            break;
        for(i=14; i<=31; i++)
        {
            MakeUnknown(currAddr, 8, 0); // DOUNK_SIMPLE 0 DOUNK_DELNAMES  0x0002
            MakeCode(currAddr);
            if(i != 31)
                MakeFunction(currAddr, currAddr + 4);
            else
                MakeFunction(currAddr, currAddr + 0x0C);
            if(MakeNameEx(currAddr, form("__Save_R12_%d_thru_31", i), SN_NOCHECK|SN_NOWARN) != 1)
                MakeNameEx(currAddr, form("__Save_R12_%d_thru_31_", i), 0);
            currAddr = currAddr + 4;
        }
    }
 
    // find all loads of gp regs
    for(currAddr=0; currAddr != BADADDR; currAddr=currAddr+4)
    {
        // find "ld  %r14, var_98(%sp)" followed by "ld  %r15, var_90(%sp)"
        currAddr = FindBinary(currAddr, SEARCH_DOWN, "E9 C1 FF 68 E9 E1 FF 70");
        if(currAddr == BADADDR)
            break;
        for(i=14; i<=31; i++)
        {
            MakeUnknown(currAddr, 8, 0); // DOUNK_SIMPLE
            MakeCode(currAddr);
            if(i != 31)
                MakeFunction(currAddr, currAddr + 4);
            else
                MakeFunction(currAddr, currAddr + 0x10);
            if(MakeNameEx(currAddr, form("__Rest_R12_lr_%d_thru_31", i), SN_NOCHECK|SN_NOWARN) != 1)
                MakeNameEx(currAddr, form("__Rest_R12_lr_%d_thru_31_", i), 0);
            currAddr = currAddr + 4;
        }
    }
}
 
static SetupSyscallTable()
{
    auto currAddr, sctable, scmax, i, scOff, str;
 
    Message(form("SystemCall reference to 0x%X found at 0x%X.\n", 0x15FD0, 0xB28));
    // ROM:00000B28                addis    r4, r4, 1
    // ROM:00000B2C                addi      r4, r4, 0x5B70
	//ROM:00000B28                 addis     r4, r4, 1
	//ROM:00000B2C                 addi      r4, r4, 0x5FD0
	
    sctable = 0x15FD0;
    MakeNameEx(sctable, "_SyscallTable", 0);
 
    for(currAddr=0xB00; currAddr != BADADDR; currAddr=currAddr+4)
    {
        currAddr = FindBinary(currAddr, SEARCH_DOWN, "28 00 00");
        if(currAddr == BADADDR)
            break;
        if((currAddr & 0x3) == 0)
            break;
    }
    scmax = Byte(currAddr+3);
    MakeUnknown(sctable, scmax*4, DOUNK_DELNAMES);// DOUNK_SIMPLE 0 DOUNK_DELNAMES  0x0002
 
    for(i=0; i<scmax; i=i+1)
    {
        MakeDword(sctable+(4*i));
        scOff = Dword(sctable+(4*i));
        str = GetSyscallName(i);
        if((Dword(scOff) == 0x38600000) && (Dword(scOff+4) == 0x4E800020))
        {
            MakeRptCmt(sctable+(4*i), form("%s (disabled)", str));
        }
        else if((Word(scOff) == 0x3960) && (Word(scOff+4) == 0x4BFF)) // is a jumptable
        {
            MakeUnknown(scOff, 8, DOUNK_DELNAMES);
            MakeRptCmt(scOff, str);
        }
        else
        {
            MakeFunction(scOff, BADADDR);
            MakeNameEx(scOff, str, 0);
        }
    }
}
 
static SetupPointerBranches()
{
    auto currAddr, baseaddr, i, str, tabl;
    tabl = 1;
    for(currAddr = 0; currAddr != BADADDR; currAddr = currAddr + 4)
    {
        currAddr = FindBinary(currAddr, SEARCH_DOWN, "7D 8C 58 2E");
        if(currAddr == BADADDR)
            break;
        if((currAddr & 0x3) == 0)
        {
            currAddr = currAddr - 4;
            MakeFunction(currAddr, BADADDR);
            MakeName(currAddr, form("jt%d_jumper", tabl));
            baseaddr = 0xA590; 
            currAddr = 0xA7B4;
            i = 0;
            while(Word(currAddr) != 0)
            {
                str = CommentEx(currAddr, 1);
                if(strlen(str) != 0) // was commented previously, use the function name put there
                {
                    MakeNameEx(Dword(baseaddr+i), str, 0);
                    MakeRptCmt(currAddr, form("<- b 0x%X %s", Dword(baseaddr+i), str));
                    MakeNameEx(currAddr, form("jt%d_%s", tabl, str), 0);
                }
                else
                    MakeRptCmt(currAddr, form("<- b 0x%X", Dword(baseaddr+i)));
                MakeFunction(currAddr, BADADDR);
                MakeFunction(Dword(baseaddr+i), BADADDR);
                 
                currAddr = currAddr + 8;
                i = i+4;
            }
            break;
        }
    }
}
 
static RemoveAllChunks(address)
{
    auto a, b;
    a = NextFuncFchunk(address, address);
    b=0;
    while(a != BADADDR)
    {
        RemoveFchunk(address, a);
        a = NextFuncFchunk(address, address);
        b = b +1;
    }
    Message(form("function at 0x%08X, removed %d chunks\n",address,b));
}
 
static CreateVector(address, name)
{
    auto a, b;
    MakeName(address, name);
    MakeFunction(address, BADADDR);
}
 
static SetupVectors()
{
    CreateVector(0x00000100, "_v_RESET");
    CreateVector(0x00000200, "_v_MACHINE_CHECK");
    CreateVector(0x00000218, "_v_MACHINE_CHECK_0");
    CreateVector(0x00000300, "_v_DATA_STORAGE");
    CreateVector(0x00000380, "_v_DATA_SEGMENT");
    CreateVector(0x00000400, "_v_INSTRUCTION_STORAGE");
    CreateVector(0x00000480, "_v_INSTRUCTION_SEGMENT");
    CreateVector(0x00000500, "_v_EXTERNAL");
    CreateVector(0x00000600, "_v_ALIGNMENT");
    CreateVector(0x00000700, "_v_PROGRAM");
    CreateVector(0x00000800, "_v_FPU_UNAVAILABLE");
    CreateVector(0x00000900, "_v_DECREMENTER");
    CreateVector(0x00000980, "_v_HYPERVISOR_DECREMENTER");
    CreateVector(0x00000B9C, "_v_Reserved_B9C");
    CreateVector(0x00000C00, "_v_SYSTEM_CALL");
    CreateVector(0x00000D00, "_v_TRACE");
    CreateVector(0x00000A5C, "_v_FPU_Assist");
    CreateVector(0x00000F20, "_v_VPU_UNAVAILABLE");
    CreateVector(0x00001600, "_v_MAINTENANCE");
    CreateVector(0x00001700, "_v_VMX_ASSIST");
    CreateVector(0x00001800, "_v_THERMAL_MANAGEMENT");
}
 
static SetupVariousFunctions()
{
    CreateVector(0x00023F8C, "XeCryptAesEncrypt");
    CreateVector(0x00020108, "XeCryptAesEcb");
    CreateVector(0x000241D4, "XeCryptAesDecrypt");
    CreateVector(0x00020128, "XeCryptAesCbc");
    CreateVector(0x00023DD0, "XeCryptAesKeyTable");
    CreateVector(0x00020300, "XeCryptAesCbcMac");
    CreateVector(0x00023500, "XeCryptMemDiff");
    CreateVector(0x000226F0, "XeCryptShaInit");
    CreateVector(0x00022738, "XeCryptShaTransform");
    CreateVector(0x00020520, "XeCryptBnDw_Copy");
    CreateVector(0x0000A880, "memcpy");
    CreateVector(0x0000AD20, "memset");
    CreateVector(0x00022DB8, "XeCryptSha");
    CreateVector(0x00022BD0, "XeCryptShaUpdate");
    CreateVector(0x00022CF0, "XeCryptShaFinal");
    CreateVector(0x00023170, "XeCryptRc4Key");
    CreateVector(0x00023218, "XeCryptRc4Ecb");
    CreateVector(0x00020578, "XeCryptBnQwBeSigFormat");
    CreateVector(0x00020F00, "XeCryptBnQwNeModMul");
    CreateVector(0x00021210, "XeCryptBnQw_Copy");
    CreateVector(0x00020EC8, "XeCryptBnQwNeModInv");
    CreateVector(0x000244C0, "XeCryptBnQwNeDigLen");
    CreateVector(0x00024578, "XeCryptBnQwNeMul");
    CreateVector(0x000211F0, "XeCryptBnQw_Zero");
    CreateVector(0x00024AE0, "XeCryptBnQwNeAcc");
    CreateVector(0x00024870, "XeCryptBnQwNeAdd");
    CreateVector(0x00024A98, "XeCryptBnQwNeSub");
    CreateVector(0x000247D0, "XeCryptBnQwNeMod");
    CreateVector(0x00020910, "XeCryptBnQwNeModExp");
    CreateVector(0x00024C0C, "XeCryptBnQwNeCompare");
    CreateVector(0x00023108, "XeCryptRc4");
    CreateVector(0x00022E98, "XeCryptHmacShaInit");
    CreateVector(0x00023010, "XeCryptHmacShaFinal");
    CreateVector(0x00023060, "XeCryptHmacSha"); 
    CreateVector(0x000200F8, "XeCryptAesKey");
    CreateVector(0x00023008, "XeCryptHmacShaUpdate");
    CreateVector(0x00021128, "XeCryptBnQwNeRsaPubCrypt");
    CreateVector(0x00020D28, "XeCryptBnQwNeModExpRoot");
    CreateVector(0x000211A8, "XeCryptBnQwNeRsaPrvCrypt");
    CreateVector(0x00021240, "XeCryptBnQw_SwapDwQwLeBe");
    CreateVector(0x00021840, "XeCryptDes3Cbc");
    CreateVector(0x00021BC8, "XeCryptDes3Key");
    CreateVector(0x000217C0, "XeCryptDes3Ecb");
    CreateVector(0x00021968, "XeCryptDesKey");
    CreateVector(0x00021710, "XeCryptDesCbc");
    CreateVector(0x00021270, "XeCryptDesEcb");
    CreateVector(0x00021C08, "XeCryptDesParity");
    CreateVector(0x00023278, "XeCryptRotSum");
    CreateVector(0x00023330, "XeCryptRotSumSha");
    CreateVector(0x00020550, "XeCryptBnDw_SwapLeBe");
    CreateVector(0x00020250, "XeCryptAesCtr");
    CreateVector(0x00020468, "XeCryptBnDwLePkcs1Verify");
    CreateVector(0x000203A8, "XeCryptBnDwLePkcs1Format");
    CreateVector(0x00024274, "XeCryptBnQwBeSigDifference");
    CreateVector(0x00020680, "XeCryptBnQwBeSigVerify");
	
	CreateVector(0x00000384, "HvpSetRMCIEx");
	CreateVector(0x00000398, "HvpSetRMCI");
	CreateVector(0x000003C4, "HvpZeroCacheLines");
	
	CreateVector(0x00000484, "CopyBy64");						/* Copies 2 x 32 bits at a time */
	CreateVector(0x000004A8, "Sleep");							/* Suspends the processor for 16 cycles*r3. */
	CreateVector(0x000004D8, "HvpGetTimebase");					/* Gets the current timebase value. If tb = 0, waits until tb != 0 */
	CreateVector(0x0000068C, "HvpGetFlashBase");				/* Returns the flash base address */
	CreateVector(0x000006A0, "HvpGetSocMMIORegs");				/* Returns the soc hardware registers base address */
	CreateVector(0x000006B4, "HvpBuildPciConfigRegs");
	CreateVector(0x000006CC, "HvpGetHostBridgeRegs");
    CreateVector(0x00000E14, "HvpRelocateCacheLines");
    CreateVector(0x00000EE4, "HvpSaveCachelines");				/* Writes cache blocks back to memory for a given address */
    CreateVector(0x00001804, "HvpFlushSingleTb");	
    CreateVector(0x000029E0, "HvpPhysicalToReal");				/* Returns the real address of the given physical address */
    CreateVector(0x00003358, "HvpRelocateEncryptedToPhysical");	/* Moves data from an encrypted page and returns the new address */
    CreateVector(0x000033D8, "HvpRelocatePhysicalToProtected");	/* Moves data to a protected page and returns the new address */	
}
 
static SetupXeKeyTables()
{
    /* 
    Key Properties : Total Size = Dword
            @h 16 bits : Unknown
            @l 16 bits : Key Size
    thanks to ANTMAN @ XBH
    */
    auto i, addr;
    addr = 0x108C8;
    MakeName(addr, "_XeKeys_Properties_Table");
    MakeComm(0x4A50, "Key Table @ 0x108C8");
    for (i = 0; i < 0x39; i++) // keys 0x0 - 0x38
    {
        MakeDword(addr + (i*4));
        OpHex(addr + (i*4),-1);
    }
    addr = 0x10FC0;
    MakeName(addr, "_XeKeys_Properties_Table_2");
    MakeComm(0x4A60, "XeKeys 0x100 - 0x10D");
    MakeComm(0x4A78, "Key Table @ 0x10FC0");
    for(i = 0; i < 0xE; i++) // keys 0x100 - 0x10D
    {
        MakeDword(addr + (i*4));
        OpHex(addr + (i*4),-1);     
    }
    Message("Done with KeyTables\n");
}
 
static DoSearchAndLabel(diff, name, binary)
{
	auto currAddr;
	currAddr = 0;
	currAddr = FindBinary(currAddr, SEARCH_DOWN, binary);
	if(currAddr != BADADDR)
	{
		CreateVector(currAddr+diff, name);
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
    SetPrcsr("PPC");
    SetCharPrm(INF_COMPILER, COMP_MS);
    //SetCharPrm(INF_GENFLAGS, INFFL_LZERO); // Show leading zero's
    SetCharPrm(INF_MODEL, 0x33); // should be calling conv cdecl, memory model "code near,data near" - use GetCharPerm(INF_MODEL) with right settings to find out val if this is wrong
    SetShortPrm(INF_AF2, ~AF2_FTAIL&GetShortPrm(INF_AF2)); // turns off creating function chunk tails
 
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
 
 
    SetupSyscallTable();
    SetupVariousFunctions();
    SetupPointerBranches();
    SetupVectors();
    SetupRegSaves();
    SetupXeKeyTables();
 
    SetShortPrm(INF_AF2, ~AF2_FTAIL&GetShortPrm(INF_AF2)); // turns on creating function chunk tails
    Message("done!\n\n");
}