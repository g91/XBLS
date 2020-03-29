#pragma once
#include "stdafx.h"



typedef unsigned __int64 QWORD;
	
namespace Hvx
{
	// HvSetState - change whether TLB memory protections are in effect
	typedef enum _SET_STATE_MODE
	{
		PROT_OFF = 2,
		PROT_ON = 3
	} SET_STATE_MODE;

	// syscalls
	QWORD HvGetVersion(DWORD magic, DWORD mode, UINT64 dest, UINT64 src, UINT32 len, UINT64 arg_r8 = NULL);
	QWORD HvQuiesceProcessor(BYTE Reason);
	QWORD HvPostOutput(BYTE code);

	// addresses for Hv Procedures:
	typedef enum _HV_PROCS {
		HvpSetRMCI = 0x398,
		HvpZeroCacheLines = 0x3C4,
		HvpGetFlashBaseAddress = 0x68C,
		HvpBuildSocMMIORegs = 0x6A0,
		HvpBuildPciConfigRegs = 0x6B4,
		HvpBuildHostBridgeRegs = 0x6CC,
		HvpInvalidateCachelines = 0xD7C,
		HvpRelocateCacheLines = 0xE14,
		HvpSaveCachelines = 0xEE4,
		HvpFlushSingleTb = 0x1804,
		HvpPhysicalToReal = 0x29E0,
		HvpRelocatePhysicalToEncrypted = 0x3280,
		HvpRelocateEncryptedToPhysical = 0x3358,
		HvpRelocatePhysicalToProtected = 0x33D8,
		HvpRelocateProtectedToPhysical = 0x34B8,
		HvpBurnFuse = 0x9558,
		HvpMemcpy = 0xA880,
		HvpMemset = 0xAD20,
		XeCryptHammingWeight = 0xB438,
		XeCryptRotSum = 0xB4A8,
		XeCryptRotSum4 = 0xB4B0,
		XeCryptRotSumSha = 0xB4B8,
		XeCryptUidEccDecode = 0xB4E8,
		XeCryptUidEccEncode = 0xB4F0
	} HV_PROCS;
	
	extern DWORD HvProcExpID;
	HRESULT InitializeHvProc();
	QWORD HvProc1(QWORD pqwProcedure, DWORD cArgs = NULL, PQWORD pqwArgs = NULL);
	QWORD HvProc(QWORD pqwProcedure, DWORD cArgs = NULL, QWORD Arg1 = NULL, QWORD Arg2 = NULL, QWORD Arg3 = NULL, QWORD Arg4 = NULL, QWORD Arg5 = NULL, QWORD Arg6 = NULL, QWORD Arg7 = NULL, QWORD Arg8 = NULL);
}