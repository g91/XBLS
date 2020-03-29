#include "xam.h"
#include <xbdm.h>


DWORD XeKeysUnObfuscateHook(DWORD r3, BYTE* r4, DWORD r5, BYTE* r6, DWORD r7)
{
	//printf("\n\n ***RGLoader.xex*** \n   -Decrypting profile!\n\n");
	XEKEYSUNOBFUSCATE XeKeysUnObfuscate = (XEKEYSUNOBFUSCATE)xbox::utilities::resolveFunction("xboxkrnl.exe", 597);
	if (r3 == 1) // From tests I did, profiles only called when set to 1
	{
		// Try with original key
		DWORD ret = XeKeysUnObfuscate(r3, r4, r5, r6, r7);
		if (ret == 1) // If pass: continue
			return ret;
		else // fail: swap key and try again
		{

			XECRYPT_RC4_STATE rc4State;
			BYTE HmacShaKey[0x10] = {0xE1, 0xBC, 0x15, 0x9C, 0x73, 0xB1, 0xEA, 0xE9, 0xAB, 0x31, 0x70, 0xF3, 0xAD, 0x47, 0xEB, 0xF3}; //retail key
			//BYTE HmacShaKey[0x10] = {0xDA, 0xB6, 0x9A, 0xD9, 0x8E, 0x28, 0x76, 0x4F, 0x97, 0x7E, 0xE2, 0x48, 0x7E, 0x4F, 0x3F, 0x68}; //devkit key
			BYTE hash[0x18];
			BYTE newHash[0x10];
			BYTE rc4Key[0x10];
			memcpy(hash, r4, 0x18);
			memcpy(r6, r4 + 0x18, r5 - 0x18);
			XeCryptHmacSha((BYTE *)HmacShaKey, 0x10, hash, 0x10, 0, 0, 0, 0, rc4Key, 0x10);
			XeCryptRc4Key(&rc4State, rc4Key, 0x10);
			XeCryptRc4Ecb(&rc4State, hash + 0x10, 0x8);
			XeCryptRc4Ecb(&rc4State, (BYTE *)r6, r5 - 0x18);
			XeCryptHmacSha((BYTE *)HmacShaKey, 0x10, hash+0x10, 8, (BYTE *)r6, r5 - 0x18, 0, 0, newHash, 0x10);
			int result = memcmp(hash, newHash, 0x10);
			if (result == 0)
				return (1);
			else
				return result;
		}		
	}
	else
	{
		return XeKeysUnObfuscate(r3, r4, r5, r6, r7);
	}
}

DWORD XeKeysObfuscateHook(DWORD r3, BYTE* r4, DWORD r5, BYTE* r6, DWORD* r7)
{
        XEKEYSOBFUSCATE XeKeysObfuscate = (XEKEYSOBFUSCATE)xbox::utilities::resolveFunction("xboxkrnl.exe", 596);
        if (r3 == 1)
        {
                //Encrypt with retail Key
                BYTE retailKey[0x10] = {0xE1, 0xBC, 0x15, 0x9C, 0x73, 0xB1, 0xEA, 0xE9, 0xAB, 0x31, 0x70, 0xF3, 0xAD, 0x47, 0xEB, 0xF3}; //retail key
                //BYTE HmacShaKey[0x10] = {0xDA, 0xB6, 0x9A, 0xD9, 0x8E, 0x28, 0x76, 0x4F, 0x97, 0x7E, 0xE2, 0x48, 0x7E, 0x4F, 0x3F, 0x68}; //devkit key
			    //copy decrypted data to 0x18+ of buffer
                memcpy(r6 + 0x18, r4, r5);
                *r7 = r5 + 0x18;
                // Create random data then copy to 0x10
                XeCryptRandom(r6 + 0x10, 8);
                // create a Hmac-Sha hash of the random data & decrypted data
                XeCryptHmacSha((BYTE*)retailKey, 0x10, r6 + 0x10, *r7 - 0x10, 0, 0, 0, 0, r6, 0x10);
                BYTE rc4Key[0x10];
                // Hash previously created hash to make the RC4 key
                XeCryptHmacSha((BYTE*)retailKey, 0x10, r6, 0x10, 0, 0, 0, 0, (BYTE*)rc4Key, 0x10);
                // Encrypt the data
                XeCryptRc4((BYTE*)rc4Key, 0x10, r6 + 0x10, *r7 - 0x10);
                return (0);
        }
        else
        {
                return XeKeysObfuscate(r3, r4, r5, r6, r7);            
        }
}

BOOL Xam_Profile_Crypto_Hook_Setup(void){
	if (xbox::utilities::patchModuleImport(MODULE_XAM, MODULE_KERNEL, 596, (DWORD)XeKeysObfuscateHook) != S_OK) 
		return FALSE;

	if (xbox::utilities::patchModuleImport(MODULE_XAM, MODULE_KERNEL, 597, (DWORD)XeKeysObfuscateHook) != S_OK) 
		return FALSE;

	return 1;
}

/*
	r3 - ?
	r4 - account info start(buffer)
	r5 - data size
	r6 - decrypt buffer
	r7 - ?
*/

//XECRYPTHMACSHA XeCryptHmacSha = (XECRYPTHMACSHA)resolveFunct("xboxkrnl.exe", 386);
//XECRYPTRC4KEY XeCryptRc4Key = (XECRYPTRC4KEY)resolveFunct("xboxkrnl.exe", 395);
//XECRYPTRC4ECB XeCryptRc4Ecb = (XECRYPTRC4ECB)resolveFunct("xboxkrnl.exe", 396);

/*BYTE data[0x10];
patchInJump((PDWORD)data, (DWORD)XeKeysUnObfuscateHook, FALSE);
HRESULT hr;
hr = DmSetMemory((PDWORD)(XAM_XeKeysUnObfuscate), 0x10, (LPCVOID)data, 0);*/

//hookImpStubDebug("xam.xex", "xboxkrnl.exe", 596, (DWORD)XeKeysObfuscateHook);
//hookImpStubDebug("xam.xex", "xboxkrnl.exe", 597, (DWORD)XeKeysUnObfuscateHook);