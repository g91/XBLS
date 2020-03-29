typedef struct _XECRYPT_SHA_STATE { 
	DWORD count; // 0x0 sz:0x4
	DWORD state[0x5]; // 0x4 sz:0x14
	BYTE buffer[0x40]; // 0x18 sz:0x40
} XECRYPT_SHA_STATE, *PXECRYPT_SHA_STATE; // size 88
C_ASSERT(sizeof(XECRYPT_SHA_STATE) == 0x58);

extern "C"{
	void __stdcall XeCryptShaInit(IN OUT PXECRYPT_SHA_STATE pShaState);
	void __stdcall XeCryptShaUpdate(IN OUT PXECRYPT_SHA_STATE pShaState, IN const PBYTE pbInp, IN DWORD cbInp);
	void __stdcall XeCryptShaFinal(IN PXECRYPT_SHA_STATE pShaState, OUT PBYTE pbOut, IN DWORD cbOut);
}

void (*sub_218)() = (void(*)())0x218;
PBYTE (*sub_6A0)(int r3) = (PBYTE(*)(int))0x6A0;
void (*sub_EE4)(int r3, int r4) = (void(*)(int, int))0xEE4;
void (*sub_204)(int r3) = (void(*)(int))0x204;

void sub_2210(){
	XECRYPT_SHA_STATE sha1;

	int r2 = 0x200000000;
	int r11 = *(int*)(r2 + (1 << 16));

	XeCryptShaInit(&sha1);

	int r29 = ((r2 + (1 << 16)) + 0x710);

result:
	int r10 = (*(int*)(r29 + 0x4) & 0xFFFFFF80);
	int r31 = ((r29 + 0x7F) & 0xFFFFFF80);

	if(r31 < r10){
		int r11 = (r31 & 0xFFFFFFFF);
		sub_EE4(((((r11 >> 16) * 0x10000) & 0xFFFF) + (r11 & 0xFFFF)), (((r10 - r31) & 0x7F) >> 7));

		int r11 = (r31 & 0x7F);

		if(r11 || r31 < (4 << 16))
			sub_218();

		PBYTE result = sub_6A0((((r31 >> 6) + (1 << 16)) & 0xFFFFFFFF));

		XeCryptShaUpdate(&sha1, result, (r10 - r31));

		for(int i = 0; i < 6; i++){
			r29 += 0x8;
			goto result;
		}
		XeCryptShaFinal(&sha1, (PBYTE)(((r2 + (1 << 16)) + 0xC0) + 0x30), 0x10);
		sub_204(r11);
	}
}


DWORD hashcount = 0, r28 = 0;
void sub_2210()
{
	QWORD r3, r4, r6, r7, r8, r9, r10, r11, r29, r30, r31;
    DWORD r5;

    XECRYPT_SHA_STATE sha;
	XeCryptShaInit(&sha); //sub_B4D0

	BYTE addrs[0x38], sizes[0x38];

loc_223C:
	{
		r29 = 0x8000010200010710 + hashcount;//(r11 + 0x710);
		r11 = HvPeekDWORD(r29);//(r29 + 0x00);
		r10 = HvPeekDWORD(r29 + 0x4);//(r29 + 0x04);
		r11 += 0x7F;
		r10 &= 0xFFFFFF80;
		r31 = r11 & 0xFFFFFF80;
		
		if (r31 >= r10)
		{
			goto loc_22BC;
		}
		
		r30 = (r10 - r31);
		r10 = (0x20001 >> 16);
		r11 = r31 & 0x00000000FFFFFFFF;
		r10 |= (0x20001 & 0xFFFF);
		r8 = (r11 >> 16);
		r9 = (r10 << 16);
		r10 = r11 & 0x3FF;//r10 = r11 & 0x0000FFFFFFFFFFFF;
		r11 = (r8 * r9);
		r4 = (r30 & 0x7F) >> 0xFFFFFFFF;
		r3 = (r11 + r10);
		//HvpSaveCachelines(r3, r4);//sub_EE4

		r11 = (r31 & 0x7F);
		if (r11 != 0)
		{
			//loc_22F4();
		}
		else
		{
			r11 = 4;
			if (r31 >= r11)
			{
				//loc_22F4();
			}
			
			r11 = (r31 >> 6);
			// r11 <<= 1;
			r3 = r11 & 0x00000000FFFFFFFF;
			//HvpGetSocMMIORegs(r3);//sub_6A0
			//r4 = r3;
			r4 = 0x8000020000010000 + r3; // equivelient to HvpGetSocMMIORegs with r11 <<= 1;
			r5 = (r30 >> 6);
            //XeCryptShaUpdate(&sha, r4, r5); //sub_B4D8

			*(QWORD*)(addrs + (r28 * 8)) = r4;
			*(QWORD*)(sizes + (r28 * 8)) = r5;
		}
	}

loc_22BC:
	{
		hashcount += 0x8;
		r28 += 1;
		if (r28 < 6)
		{
			goto loc_223C;
		}
		else
		{
		    //QWORD r2 = 0x8000010200010000;
			//r2 += 0xC0;
			//XeCryptShaFinal(&sha, r2 + 0x30, 0x10); //sub_B4C8

			CWriteFile("HDD:\\dump\\addrs.bin", addrs, 0x38);
			CWriteFile("HDD:\\dump\\sizes.bin", sizes, 0x38);
		}
	}

	if (hashcount == 0)
	{
		goto loc_223C;
	}
}