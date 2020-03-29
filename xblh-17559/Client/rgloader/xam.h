#pragma once

#include "..\stdafx.h"
#include <xbdm.h>
#include <stdio.h>
//#include "xecrypt.h"
//#include "utilities.h"

//typedef void (*XECRYPTHMACSHA)(const BYTE * pbKey, DWORD cbKey, const BYTE * pbInp1, DWORD cbInp1, const BYTE * pbInp2, DWORD cbInp2, const BYTE * pbInp3, DWORD cbInp3, BYTE * pbOut, DWORD cbOut);
//typedef void  (*XECRYPTRC4KEY)(XECRYPT_RC4_STATE * pRc4State, const BYTE * pbKey, DWORD cbKey);
//typedef void  (*XECRYPTRC4ECB)(XECRYPT_RC4_STATE * pRc4State, BYTE * pbInpOut, DWORD cbInpOut);
typedef DWORD (*XEKEYSUNOBFUSCATE)(DWORD r3, BYTE* r4, DWORD r5, BYTE* r6, DWORD r7);
typedef DWORD (*XEKEYSOBFUSCATE)(DWORD r3, BYTE* r4, DWORD r5, BYTE* r6, DWORD* r7);
//typedef void (*XECRYPTRANDOM)(BYTE * pb, DWORD cb);
//typedef void (*XECRYPTRC4)(const BYTE * pbKey, DWORD cbKey, BYTE * pbInpOut, DWORD cbInpOut);

#define XAM_XeKeysUnObfuscate 0x81CC11DC //for retail profile decryption

DWORD XeKeysUnObfuscateHook(DWORD r3, BYTE* r4, DWORD r5, BYTE* r6, DWORD r7);

BOOL Xam_Profile_Crypto_Hook_Setup(void);
