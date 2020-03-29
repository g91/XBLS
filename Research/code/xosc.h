
#ifndef __XOSC_H__
#define __XOSC_H__

#define MODULE_XOSC "xosc9v2.xex"

#define REQUEST_SMC_VERSION 0x12
#define IOCTL_DISK_VERIFY 0x4D014

#define STATUS_INVALID_HEADER 0xC8003005
#define STATUS_KEY_RESULT_FAILED 0xC8003003
#define STATUS_INVALID_PARAMETER 0xC000000D
#define STATUS_INVALID_PARAMETER_1 0xC00000EF
#define STATUS_INVALID_PARAMETER_7 0xC00000F5
#define STATUS_INSUFFICIENT_RESOURCES 0xC000009A

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

extern byte* xamAllocatedData;

#endif //__XOSC_H__