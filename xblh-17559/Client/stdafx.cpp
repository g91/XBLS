#include "stdafx.h"

namespace Globals
{
	/*Cheats*/
	byte BO2_Addresses[1000] = { 0 };
	byte BO1_Addresses[1000] = { 0 };
	byte MW3_Addresses[1000] = { 0 };
	byte COD4_Addresses[1000] = { 0 };
	byte GHOST_Addresses[1000] = { 0 };
	byte AW_Addresses[1000] = { 0 };
}

namespace global 
{
	//
	BOOL isDevkit = FALSE;
	BOOL isAuthed = FALSE;
	BOOL IsINI	  = FALSE;
	BOOL testA	 = FALSE;

	WCHAR wNotifyMsg[100];
	DWORD supportedVersion = 17559;
	BYTE g_pSessionToken[0x14];


	PCHAR PATH_KV	= "Client:\\KV.bin";
	PCHAR PATH_CPU	= "Client:\\CPUKey.bin";
	PCHAR PATH_XEX	= "Client:\\Client.xex";

	namespace seting 
	{
		BOOL UseSetDashUI		= TRUE;
		BOOL UseSetGold			= TRUE;

		BOOL UseBYPASSBO2		= TRUE;
		BOOL UseBYPASSBO3		= TRUE;
		BOOL UseBYPASSGHOSTS	= TRUE;

	}

	namespace DASHRESPONSE
	{
		BYTE Color[0x04] = { 0xFF, 0x66, 0x00, 0x66 };
		BYTE Background[0x04] = { 0xFF, 0x00, 0x00, 0x00 };
	}


	namespace challenge 
	{
		PVOID cleanhvv;
		PVOID bufferAddress;
		DWORD bufferSize;
		BOOL hasChallenged = FALSE;

		XEX_EXECUTION_ID executionId = {
			0, // media id
			XboxKrnlVersion->Major << 28 | supportedVersion << 8 | XboxKrnlVersion->Qfe, // version
			XboxKrnlVersion->Major << 28 | supportedVersion << 8 | XboxKrnlVersion->Qfe, // base version
			0xFFFE07D1, // title id
			0, 0, 0, 0, 0 // other shit
		};
		XECRYPT_SHA_STATE xShaCurrentXex;

		BYTE spoofedMacAddress[6];
		BYTE cpukey[0x10];

		namespace XOSC {
			SHORT settingSize = 6;
			DWORD flags = 0;
			DWORD mediaInfo;
			DWORD titleId;
			XEX_EXECUTION_ID xexExecutionId = {
				0, // media id
				XboxKrnlVersion->Major << 28 | supportedVersion << 8 | XboxKrnlVersion->Qfe, // version
				XboxKrnlVersion->Major << 28 | supportedVersion << 8 | XboxKrnlVersion->Qfe, // base version
				0xFFFE07D1, // title id
				0, 0, 0, 0, 0 // other shit
			};

			byte unknownBuffer[0x10] = { 0 };
			byte securityDigest0[0x14];
			byte securityDigest_xam[0x14];
			byte securityDigest_krnl[0x14];
			byte securityDigest[0x14];
			byte macAddress[0x6];
			byte smcOut[0x5];
			byte smcMsg[0x5];
		}
	}

	namespace modules {
		HANDLE client;
		HANDLE xam;
		HANDLE krnl;
		HANDLE ModuleHandle;
		BYTE ModuleDigest[0x14];
	}
}
