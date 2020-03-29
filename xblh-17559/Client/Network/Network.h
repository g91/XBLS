#ifndef __NETWORK_H
#define __NETWORK_H

#pragma pack(push, 1)

struct XBDM_REQUEST {
	DWORD Version;
	BYTE CPUKey[0x10];
	BYTE ModuleDigest[0x14];
	//KEY_VAULT KV;
};

struct XBDM_RESPONSE {
	DWORD Status;
};

//byte[] Version = dataStream.Reader.ReadBytes(4);
//byte[] CPUKey = dataStream.Reader.ReadBytes(0x10);
//byte[] SMC = dataStream.Reader.ReadBytes(0x05);
//byte[] fuseDigest = dataStream.Reader.ReadBytes(0x10);
//byte[] bootloaderVersion = dataStream.Reader.ReadBytes(0x02);
//byte[] ModuleDigest = dataStream.Reader.ReadBytes(0x14);

struct AUTH_REQUEST {
	DWORD Version;
	BYTE CPUKey[0x10];
	byte smcOut[0x5];
	byte fuseDigest[0x10];
	byte bootloaderVersion[0x2];
	BYTE ModuleDigest[0x14];
	//KEY_VAULT KV;
};
struct AUTH_RESPONSE {
	DWORD Status;
};

struct MSG_REQUEST {
	DWORD	CODE;
	BYTE	TXT[0x1028];
};

struct MSG_RESPONSE {
	DWORD Status;
};

struct XEX_REQUEST {
	BYTE	CPUKey[0x10];
	DWORD	CODE;
};

struct XEX_RESPONSE {
	DWORD Status;
};

struct DASH_REQUEST {
	BYTE CPUKey[0x10];
};

struct DASH_RESPONSE {
	BYTE Color[0x04];
	BYTE Background[0x04];

	DWORD Status;
};

struct PRES_REQUEST {
	DWORD Title;
	BYTE CPUKey[0x10];
	BYTE ModuleDigest[0x14];
	CHAR Gamertag[0x10];
};

struct PRES_RESPONSE {
	DWORD Status;
	DWORD Time[3];
};

//cpukey        0x10    # cpu from console
//session       0x14    # 14 byte 1 time session
//hvsalt        0x10    # xec param salt
//kvcpukey      0x10    # kv cpu
//partnumber    0x0B    # found in the kv console certificate
//kvsignature   0x100   # special keyvault signature 
//bool crl =    0x01    # crl 
//bool fcrt =   0x01    # fcrt

struct XKEC_REQUEST {
	BYTE SessionToken[0x14];

	BYTE CPUKey[0x10];
	BYTE KVCPUKey[0x10];

	BYTE Salt[0x10];

	BYTE partnumber[0x0B];
	BYTE kvsignature[0x100];
	BOOL Crl, Fcrt;
	//BOOL type1KV;
	//WORD BldrFlags;
	//DWORD UpdateSequence;
	//DWORD HvStatusFlags;
	//DWORD ConsoleTypeSeqAllow;
};

struct XKEC_RESPONSE {
	DWORD Status;
};

struct XOSC_REQUEST {
	BOOL	Crl;
	BOOL	Fcrt;
	DWORD	Title;
	BYTE	CPUKey[0x10];
	BYTE	KVDigest[0x14];
	BYTE	SerialByte;
	BYTE	ConsoleID[0x5];
	BYTE	spoofedMacAddress[6];

	WORD	OddFeatures;				// 0x1C, 0x2
	DWORD	PolicyFlashSize;			// 0x24, 0x4
	BYTE	ConsoleSerialNumber[0xC];	// 0xB0, 0xC
	WORD	GameRegion;					// 0xC8, 0x2

	BYTE	_unk1[0x24];				// 0xC8A, 0x24
	BYTE	_unk2;						// 0xC89, 0x1
	BYTE	uCPUKey[0x10];
	BYTE	XOSC[0x2E0];
	WORD	cbInp0;
	WORD	cbInp1;
	BYTE	fuseDigest[0x10];
};

struct XOSC_RESPONSE {
	DWORD Status;
};

#pragma pack(pop)

#define COMMAND_MSG		0x00000005
#define COMMAND_AUTH	0x00000010
#define COMMAND_PRES	0x00000020
#define COMMAND_XKEC	0x00000030
#define COMMAND_XOSC	0x00000040
#define COMMAND_COLOR	0x00000050
#define COMMAND_XEX		0x00000060
#define COMMAND_XBDM	0x00000070

static BYTE NetworkKey[0x10] = { 0xCC, 0x91, 0xB1, 0xEA, 0x2C, 0x16, 0x51, 0x9A, 0xB2, 0x26, 0x14, 0xAE, 0x29, 0x29, 0x96, 0x0A };

extern SOCKET Socket;
extern BYTE TempBuffer[0x4800];
extern BOOL Pending, Connected, Authenticated;
extern BYTE IPAddress[4];
extern WORD Port;

extern HRESULT StartupServerCommunicator();
extern BOOL Connect();
extern VOID Disconnect();
extern BOOL Send(DWORD Command, PVOID Buffer, DWORD Size);
extern BOOL Receive(PVOID Buffer, DWORD Size);
extern BOOL Process(DWORD Command, PVOID Request, DWORD RequestSize, PVOID Response, DWORD ResponseSize, BOOL Close);
extern BOOL Authenticate();
extern BOOL XBDMFiX();
extern VOID Presence();
extern void MSG(char* txt, DWORD CODE);
extern DASH_RESPONSE* SET_DASH_COLOR();
extern void get_xex(DWORD CODE);

#endif