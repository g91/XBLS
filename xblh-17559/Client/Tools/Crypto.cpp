#include "Crypto.h"

void RC4(unsigned char * ByteInput, unsigned char * pwd, unsigned char * &ByteOutput)
{
	unsigned char * temp;
	int i,j=0,t,tmp,tmp2,s[256], k[256];
	for (tmp=0;tmp<256;tmp++){
		s[tmp]=tmp;
		k[tmp]=pwd[(tmp % strlen((char *)pwd))];
	}
		for (i=0;i<256;i++){
		j = (j + s[i] + k[i]) % 256;
		tmp=s[i];
		s[i]=s[j];
		s[j]=tmp;
	}
temp = new unsigned char [ (int)strlen((char *)ByteInput)  + 1 ] ;
	i=j=0;
	for (tmp=0;tmp<(int)strlen((char *)ByteInput);tmp++){
	    i = (i + 1) % 256;
        j = (j + s[i]) % 256;
		tmp2=s[i];
		s[i]=s[j];
		s[j]=tmp2;
        t = (s[i] + s[j]) % 256;
if (s[t]==ByteInput[tmp])
	temp[tmp]=ByteInput[tmp];
else
	temp[tmp]=s[t]^ByteInput[tmp];
	}
temp[tmp]='\0';
ByteOutput = temp;
}


VOID DecryptData(BYTE *data, DWORD length) {
	DWORD i, r8, r9, r10;
	r8 = r9 = r10 = 0;

	for (i = 0; i < length; i++) {
		r10 = data[i];
		r8 = r9 & 0xFF;
		r9 = r10;
		r10 ^= 0xBB;
		r10 -= i;
		r10 ^= r8;
		data[i] = r10;
	}
}

VOID EncryptData(BYTE *data, DWORD length) {
	DWORD i, r8, r9, r10;
	r8 = r9 = r10 = 0;

	for (i = 0; i < length; i++) {
		r8 = data[i];
		r10 &= 0xFF;
		r10 ^= r8;
		r10 += i;
		r10 &= 0xFF;
		r10 ^= 0xBB;
		data[i] = r10;
	}
}