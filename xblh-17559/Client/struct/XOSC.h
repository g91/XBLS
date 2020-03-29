#pragma once

#include <xtl.h>
#include <stdio.h>

#define MODULE_XOSC "xosc9v2.xex"

#define REQUEST_SMC_VERSION 0x12
#define IOCTL_DISK_VERIFY 0x4D014

//#define STATUS_INVALID_HEADER 0xC8003005
//#define STATUS_KEY_RESULT_FAILED 0xC8003003
//#define STATUS_INSUFFICIENT_RESOURCES 0xC000009A

#define XOSC_FLAG_STATUS_TASK_SHOULD_EXIT 0x2000000000000000
#define XOSC_FLAG_STATUS_FLAG_TITLE_TERMINATED 0x4000000000000000
#define XOSC_DEVICESIZE_OPEN_OPTIONS FILE_DIRECTORY_FILE | FILE_SYNCHRONOUS_IO_NONALERT | 0x800000

struct xoscResponse {
	int result; //0x00
	short xoscMajor; //0x04
	short xoscMinor; //0x06
	long long operations; //0x08
	int ioCtlResult; //0x10
	int keyResultCert; //0x14
	int executionResult;//0x18
	int keyResultSerial; //0x1C
	int sataResult; // 0x20 0xC8003003
	byte _unk1[0x10]; //0x24 AA's
	int daeResult; //0x34 0x40000012
	XEX_EXECUTION_ID xexExecutionId; //0x38
	byte cpuKeyDigest[0x10]; //0x50
	byte kvDigest[0x10]; //0x60
	byte fuseDigest[0x10]; //0x70
	int drivePhaseLevel; //0x80
	DWORD mediaInfo; //0x84 0
	DWORD titleId; //0x88
	byte _unk2[0x64]; //0x8C
	byte driveIndentifier1[0x24]; //0xF0
	byte driveIndentifier2[0x24]; //0x114
	byte consoleSerial[0xC]; //0x138
	short serialByte; //0x144 0
	short bootloaderVersion; //0x146
	short xamRegion; //0x148
	short xamOdd; //0x14A
	int _unk3; //0x14C 0x8E03861C
	int flashSize; //0x150
	int xoscRegion; //0x154
	int hvFlags; //0x158
	int _unk4; //0x15C
	long long _unk5; //0x160
	int _unk6; //0x168
	int _unk7; //0x16C
	long long pcieHardwareInfo; //0x170
	int _unk8; //0x178
	int _unk9; //0x17C
	long long _unk10; //0x180
	long long _unk11; //0x188
	long long _unk12; //0x190
	long long hvProtectionFlags; //0x198
	long long consoleId; //0x1A0
	byte _unk14[0x28]; //0x1A8
	int hardwareFlags; //0x1D0
	byte _unk15[0xD4];  //0x1D4
	int memoryUnit0; //0x2A8
	int memoryUnit1; //0x2AC
	int memoryUnitIntFlash; //0x2B0
	int memoryUnitIntUSB; //0x2B4
	int mass0PartitionFileSize; //0x2B8
	int mass1PartitionFileSize; //0x2BC
	int mass2PartitionFileSize; //0x2C0
	int crlVersion; //0x2C4
	long long _unk16; //0x2C8
	long long _unk17; //0x2D0
	int xoscFooterMagic; //0x2D8
	int _unk18; //0x2DC
	byte unusedFiller[0x120]; //0x2E0
};

#define DVD_INQUIRY_RESPONSE_SIZE	0x24

typedef enum _MEDIA_TYPE {
	Unknown = 0x00,
	F5_1Pt2_512 = 0x01,
	F3_1Pt44_512 = 0x02,
	F3_2Pt88_512 = 0x03,
	F3_20Pt8_512 = 0x04,
	F3_720_512 = 0x05,
	F5_360_512 = 0x06,
	F5_320_512 = 0x07,
	F5_320_1024 = 0x08,
	F5_180_512 = 0x09,
	F5_160_512 = 0x0a,
	RemovableMedia = 0x0b,
	FixedMedia = 0x0c,
	F3_120M_512 = 0x0d,
	F3_640_512 = 0x0e,
	F5_640_512 = 0x0f,
	F5_720_512 = 0x10,
	F3_1Pt2_512 = 0x11,
	F3_1Pt23_1024 = 0x12,
	F5_1Pt23_1024 = 0x13,
	F3_128Mb_512 = 0x14,
	F3_230Mb_512 = 0x15,
	F8_256_128 = 0x16,
	F3_200Mb_512 = 0x17,
	F3_240M_512 = 0x18,
	F3_32M_512 = 0x19
} MEDIA_TYPE;

typedef struct _DISK_GEOMETRY {
	LARGE_INTEGER Cylinders;
	MEDIA_TYPE    MediaType;
	DWORD         TracksPerCylinder;
	DWORD         SectorsPerTrack;
	DWORD         BytesPerSector;
} DISK_GEOMETRY;

// needs pragma pack
#pragma pack(push, 1)
typedef struct _RESPONSE_DATA {
	DWORD dwResult; // 0
	WORD verMaj; // 4 = 9
	WORD verMin; // 6 = 2
	QWORD flags; // 8
	NTSTATUS DvdInqResp; // 0x10
	NTSTATUS XeikaInqResp; // 0x14
	NTSTATUS ExecIdResp; // 0x18
	NTSTATUS HvIdCacheDataResp; // 0x1C
	NTSTATUS MediaInfoResp; // 0x20
	DWORD MediaInfodwUnk1; // 0x24
	DWORD MediaInfodwUnk2; // 0x28
	DWORD MediaInfoAbUnk; // 0x2C
	DWORD MediaInfoPad5; // 0x30
	DWORD HardwareMaskTemplate; // 0x34 = this is hardcoded in xosc and filled in when PCI hardware revision query occurs
	XEX_EXECUTION_ID xid; // 0x38 sz 0x18
	BYTE hvCpuKeyHash[0x10]; // 0x50
	BYTE xexHashing[0x10]; // 0x60
	BYTE zeroEncryptedConsoleType[0x10]; // 0x70
	DWORD DvdXeikaPhaseLevel; // 0x80
	DWORD dwMediaType; // 0x84
	DWORD dwTitleId; // 0x88
	BYTE DvdPfiInfo[0x11]; // 0x8C
	BYTE DvdDmiMediaSerial[0x20]; // 0x9D
	BYTE DvdMediaId1[0x10]; // 0xBD
	BYTE abPad[3];			// BYTE tempPad[]; // 0xCD
	QWORD DvdDmi10Data; // 0xD0
	DISK_GEOMETRY DvdGeometry; // 0xD8
	BYTE DvdMediaId2[0x10]; // 0xE0
	BYTE DvdInqRespData[DVD_INQUIRY_RESPONSE_SIZE]; // 0xF0
	BYTE XeikaInqData[DVD_INQUIRY_RESPONSE_SIZE]; // 0x114
	BYTE ConsoleSerial[0xC]; // 0x138
	WORD wPad;				// BYTE tempPad[]; // 0x144
	WORD hvHeaderFlags; // 0x146
	WORD hvUnrestrictedPrivs; // 0x148
	WORD kvOddFeatures; // 0x14A
	DWORD hvUnknown; // 0x14C
	DWORD kvPolicyFlashSize; // 0x150
	DWORD kvRestrictedStatus; // 0x154
	DWORD hvKeyStatus; // 0x158
	DWORD dwPad1;			// BYTE tempPad[]; // 0x15C
	QWORD secDataDvdBootFailures; // 0x160 < not sure why they expand the lowpart into quad
	DWORD secDataFuseBlowFailures; // 0x168
	DWORD dwPad2; // 0x16C
	QWORD HardwareMask; // 0x170 calculated from pci info on device 2
	DWORD secDataDvdAuthExFailures; // 0x178
	DWORD secDataDvdAuthExTimeouts;		// BYTE tempPad[]; // 0x17C
	QWORD kvRestrictedPrivs; // 0x180
	QWORD hvSecurityDetected; // 0x188
	QWORD hvSecurityActivated; // 0x190
	QWORD hvProtectedFlags; // 0x198
	QWORD ConsoleId[6]; // 0x1A0
	DWORD XboxHardwareInfoFlags; // 0x1D0
		// 0x1D4 - 0x21C HDD related info
	BYTE HddSerialNumber[0x14]; // 0x1D4
	BYTE HddFirmwareRevision[0x8]; // 0x1E8
	BYTE HddModelNumber[0x28]; // 0x1F0
	DWORD HddUserAddressableSectors; // 0x218
	BYTE unkMediaInfo[0x80]; // 0x21C
	QWORD DvdUnkp1; // 0x29C
	DWORD MediaInfoUnkp3; // 0x2A4
	DWORD Mu0Au; // 0x2A8 "\\Device\\Mu0\\" allocationUnits.lowpart
	DWORD Mu1Au; // 0x2Ac "\\Device\\Mu1\\" allocationUnits.lowpart
	DWORD SfcAu; // 0x2B0 "\\Device\\BuiltInMuSfc" allocationUnits.lowpart
	DWORD IntMuAu; // 0x2B4 "\\Device\\BuiltInMuUsb\\Storage\\" allocationUnits.lowpart
	DWORD UsbMu0; // 0x2B8 "\\Device\\Mass0PartitionFile\\Storage\\" allocationUnits.lowpart
	DWORD UsbMu1; // 0x2BC "\\Device\\Mass1PartitionFile\\Storage\\" allocationUnits.lowpart
	DWORD UsbMu2; // 0x2C0 "\\Device\\Mass2PartitionFile\\Storage\\" allocationUnits.lowpart
	DWORD crlVersion; // 0x2C4
	QWORD Layer0PfiSectors; // 0x2C8
	QWORD Layer1PfiSectors; // 0x2D0
	DWORD respMagic; // 0x2D8 0x5F534750 '_SGP'
	DWORD dwFinalPad; // 0x2DC
} RESPONSE_DATA, * PRESPONSE_DATA; // total size 0x2E0
#pragma pack(pop)


extern byte* xamAllocatedData;

namespace global {
	namespace challenge {
		namespace XOSC {
			extern SHORT settingSize;

			extern DWORD flags;
			extern DWORD mediaInfo;
			extern DWORD titleId;

			extern XEX_EXECUTION_ID xexExecutionId;

			extern byte unknownBuffer[];
			extern byte securityDigest0[];
			extern byte securityDigest_xam[];
			extern byte securityDigest_krnl[];
			extern byte securityDigest[];
			extern byte macAddress[];
			extern byte smcOut[];
			extern byte smcMsg[];

			namespace AllowedMediaTypes {
				extern byte krnl[];
				extern byte dash[];
				extern byte XAM[];
			}
		}
	}
}

