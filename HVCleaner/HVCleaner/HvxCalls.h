#pragma once

typedef unsigned __int64 QWORD;
namespace xbox {
	namespace Hvx
	{
		// HvSetState - change whether TLB memory protections are in effect
		typedef enum _SET_STATE_MODE
		{
			PROT_OFF = 2,
			PROT_ON = 3
		} SET_STATE_MODE;

		// syscalls
		QWORD HvExpansionInstall(DWORD PhysicalAddress, DWORD CodeSize);
		QWORD HvExpansionCall(DWORD ExpansionId, QWORD Param1, QWORD Param2, QWORD Param3, QWORD Param4);
		QWORD HvKeysExecute(PVOID pvPayload, DWORD cbPayload, PVOID arg1, DWORD arg2, QWORD arg3, QWORD arg4);

		// KeysExecute stuff
		extern LPCSTR KeysExecutePayloadFile;
		extern LPCSTR KeysExecuteRespFile;
		typedef enum _KeysExecuteError
		{
			EXECUTE_SUCCESS,
			EXECUTE_INVALID_PAYLOAD_SIZE,
			EXECUTE_INVALID_BUFFER_SIZE,
			EXECUTE_INVALID_BUFFER_ADDRESS,
			EXECUTE_INVALID_PARAMETERS
		} KeysExecuteError;
		//QWORD ExecutePayload(PBYTE pbPayload, DWORD cbPayload, DWORD EntryPoint, QWORD Arg1, QWORD Arg2, QWORD Arg3, QWORD Arg4);


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
			sub_2210 = 0x2210,
			HvpPhysicalToReal = 0x29E0,
			sub_2E90 = 0x2E90,
			sub_3100 = 0x3100,
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

		typedef enum _SOC_KEY_SELECT
		{
			ksHV_0 = 0,
			ksHV_1 = 1,
			ksHV_2 = 2,
			ksHV_3 = 3,
			ksUnk_4 = 4,
			ksKeys = 0x3A, // used for things relating to keys, kv info, dvd, and expansions
			ksSysUpdate = 0x3C,
			ksLoadImage = 0x3D, // used during xex image load
			ksKeysExecute = 0x3E
		} SOC_KEY_SELECT;

		// Used to create SRAM hashes of a data buffer
		// qwInpAddSize: start offset and cacheblock ammount (bits 30-47 is offset, bits 50-63 is block count)
		// qwInpProtBuf: temp buffer address with protected flags (use HvpRelocatePhysicalToProtected)
		// qwInpDataBuf: data to be hashed
		// qwOutHashBuf: buffer to write sram hashes to
		//extern DWORD HvHashExpID;
		//HRESULT InitializeHvHash();
		//QWORD HvHash(QWORD qwInpAddSize, QWORD qwInpProtBuf, QWORD qwInpDataBuf, QWORD qwOutHashBuf);
	
		// the peek/poke expansion
		typedef enum _PEEK_POKE_TYPE {
			PEEK_BYTE = 0,
			PEEK_WORD = 1,
			PEEK_DWORD = 2,
			PEEK_QWORD = 3,
			PEEK_BYTES = 4,
			POKE_BYTE = 5,
			POKE_WORD = 6,
			POKE_DWORD = 7,
			POKE_QWORD = 8,
			POKE_BYTES = 9,
			PEEK_SPR = 10,
			POKE_SPR = 11
		} PEEK_POKE_TYPE;

		typedef enum _SOC_SPRS {
			SPR_XER = 0x1,
			SPR_LR = 0x8,
			SPR_CTR = 0x9,
			SPR_DSISR = 0x12,
			SPR_DAR = 0x13,
			SPR_DEC = 0x16,
			SPR_SDR1 = 0x19,
			SPR_SRR0 = 0x1A,
			SPR_SRR1 = 0x1B,
			SPR_ACCR = 0x1D,
			SPR_CTRL_R = 0x88,
			SPR_CTRL_W = 0x98,
			SPR_VRSAVE = 0x100,
			SPR_SPRG3_R = 0x103,
			SPR_TB_R = 0x10C,
			SPR_TBU_R = 0x10D,
			SPR_SPRG0 = 0x110,
			SPR_SPRG1 = 0x111,
			SPR_SPRG2 = 0x112,
			SPR_SPRG3 = 0x113,
			SPR_TBL_W = 0x11C,
			SPR_TBU_W = 0x11D,
			SPR_PVR = 0x11F,
			SPR_HSPRG0 = 0x130,
			SPR_HSPRG1 = 0x131,
			SPR_HDEC = 0x136,
			SPR_HIOR = 0x137,
			SPR_RMOR = 0x138,
			SPR_HRMOR = 0x139,
			SPR_HSRR0 = 0x13A,
			SPR_HSRR1 = 0x13B,
			SPR_LPCR = 0x13E,
			SPR_LPIDR = 0x13F,
			SPR_TSRL = 0x380,
			SPR_TSRR = 0x381,
			SPR_TSCR = 0x399,
			SPR_TTR = 0x39A,
			SPR_TLB_HINT = 0x3B2,
			SPR_TLB_INDEX = 0x3B3,
			SPR_TLB_VPN = 0x3B4,
			SPR_TLB_RPN = 0x3B5,
			SPR_TLB_RMT = 0x3B7,
			SPR_DRSR0 = 0x3B8,
			SPR_DRMR0 = 0x3B9,
			SPR_DCIDR0 = 0x3BA,
			SPR_DRSR1 = 0x3BB,
			SPR_DRMR1 = 0x3BC,
			SPR_DCIDR1 = 0x3BD,
			SPR_IRSR0 = 0x3D0,
			SPR_IRMR0 = 0x3D1,
			SPR_ICIDR0 = 0x3D2,
			SPR_IRSR1 = 0x3D3,
			SPR_IRMR1 = 0x3D4,
			SPR_ICIDR1 = 0x3D5,
			SPR_HID0 = 0x3F0,
			SPR_HID1 = 0x3F1,
			SPR_IABR = 0x3F2,
			SPR_HID4 = 0x3F4,
			SPR_DABR = 0x3F5,
			SPR_HID5 = 0x3F6,
			SPR_DABRX = 0x3F7,
			SPR_TDABRX = 0x3F8,
			SPR_HID6 = 0x3F9,
			SPR_HID7 = 0x3FA,
			SPR_TIABR = 0x3FB,
			SPR_BKMK = 0x3FC,
			SPR_TDABR = 0x3FD,
			SPR_PIR = 0x3FF
		} SOC_SPRS;

		extern DWORD HvPeekPokeExpID;
		HRESULT InitializeHvPeekPoke(); // init the expansion

		// reading with the expansion
		BYTE    HvPeekBYTE(QWORD Address);
		WORD    HvPeekWORD(QWORD Address);
		DWORD   HvPeekDWORD(QWORD Address);
		QWORD   HvPeekQWORD(QWORD Address);
		HRESULT HvPeekBytes(QWORD Address, PVOID Buffer, DWORD Size);

		// writing with the expansion
		HRESULT HvPokeBYTE(QWORD Address, BYTE Value);
		HRESULT HvPokeWORD(QWORD Address, WORD Value);
		HRESULT HvPokeDWORD(QWORD Address, DWORD Value);
		HRESULT HvPokeQWORD(QWORD Address, QWORD Value);
		HRESULT HvPokeBytes(QWORD Address, PVOID Buffer, DWORD Size);

		// get/set SPR
		QWORD   HvPeekSPR(SOC_SPRS SPR);
		QWORD   HvPokeSPR(SOC_SPRS SPR, QWORD Value);
	}
}