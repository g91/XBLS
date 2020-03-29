

//
// All APIs unique to Xbox that live in XAPILIB.LIB should be
// defined in this header file
//

#ifndef _XBOXP_
#define _XBOXP_

#ifdef __cplusplus
extern "C" {
#endif

#include "xbox.h"

#ifdef __cplusplus
}
#endif

#pragma warning(push)
#pragma warning(disable: 4201) // unnamed struct/union

#define XBOXAPI

#ifdef __cplusplus
extern "C" {
#endif

#define GUEST_SELECTOR_XUID             ((XUID) 0xE000000000000000)

XBOXAPI
FORCEINLINE
BOOL
WINAPI
IsOfflineXUID(
    XUID xuid
    )
{
    return (xuid & 0xF000000000000000) == 0xE000000000000000;
}

XBOXAPI
FORCEINLINE
BOOL
WINAPI
IsOnlineXUID(
    XUID xuid
    )
{
    return (xuid & 0xFFFF000000000000) == 0x0009000000000000;
}

XBOXAPI
FORCEINLINE
BOOL
WINAPI
IsGuestXUID(
    XUID xuid
    )
{
    DWORD HighPart;

    HighPart = (DWORD)(xuid >> 48);

    return ((HighPart & 0x000F) == 0x9) && ((HighPart & 0x00C0) > 0);
}


#define MAX_DISPLAY_BLOCKS              50001

XBOXAPI
DWORD
WINAPI
XGetDisplayBlocks(
    IN      LPCSTR                      szPathName
    );

XBOXAPI
HANDLE
WINAPI
XapipCreateThread(
    IN      LPSECURITY_ATTRIBUTES       lpThreadAttributes  OPTIONAL,
    IN      DWORD                       dwStackSize         OPTIONAL,
    IN      LPTHREAD_START_ROUTINE      lpStartAddress,
    IN      LPVOID                      lpParameter         OPTIONAL,
    IN      DWORD                       dwCreationFlags     OPTIONAL,
    IN      DWORD                       dwThreadProcessor,
    OUT     LPDWORD                     lpThreadId          OPTIONAL
    );

#define XSAVEGAME_NOCOPY                1

XBOXAPI
DWORD
WINAPI
XCreateSaveGame(
    IN      LPCSTR                      szRootPathName,
    IN      LPCWSTR                     wszSaveGameName,
    IN      DWORD                       dwCreationDisposition,
    IN      DWORD                       dwCreateFlags,
    OUT     LPSTR                       szPathBuffer,
    IN      UINT                        uSize
    );

XBOXAPI
DWORD
WINAPI
XDeleteSaveGame(
    IN      LPCSTR                      szRootPathName,
    IN      LPCWSTR                     wszSaveGameName
    );

#define MAX_GAMENAME                    128

typedef struct _XGAME_FIND_DATA {
    WIN32_FIND_DATAA                    wfd;
    CHAR                                szSaveGameDirectory[MAX_PATH];
    WCHAR                               szSaveGameName[MAX_GAMENAME];
} XGAME_FIND_DATA, *PXGAME_FIND_DATA;

XBOXAPI
HANDLE
WINAPI
XFindFirstSaveGame(
    IN      LPCSTR                      szRootPathName,
    OUT     PXGAME_FIND_DATA            pFindGameData
    );

XBOXAPI
BOOL
WINAPI
XFindNextSaveGame(
    IN      HANDLE                      hFindGame,
    OUT     PXGAME_FIND_DATA            pFindGameData
    );

XBOXAPI
BOOL
WINAPI
XFindClose(
    IN      HANDLE                      hFind
    );

#define MAX_NICKNAME                    32

XBOXAPI
BOOL
WINAPI
XSetNicknameW(
    IN      LPCWSTR                     wszNickname,
    IN      BOOL                        fPreserveCase
    );
#define XSetNickname                    XSetNicknameW

XBOXAPI
HANDLE
WINAPI
XFindFirstNicknameW(
    IN      BOOL                        fThisTitleOnly,
    OUT     LPWSTR                      wszNickname,
    IN      UINT                        uSize
    );
#define XFindFirstNickname              XFindFirstNicknameW

XBOXAPI
BOOL
WINAPI
XFindNextNicknameW(
    IN      HANDLE                      hFindNickname,
    OUT     LPWSTR                      wszNickname,
    IN      UINT                        uSize
    );
#define XFindNextNickname               XFindNextNicknameW

typedef ULONGLONG                       XOFFERING_ID;

#define MAX_CONTENT_DISPLAY_NAME        128

typedef struct _XCONTENT_FIND_DATA {
    WIN32_FIND_DATAA                    wfd;
    XOFFERING_ID                        qwOfferingId;
    DWORD                               dwFlags;
    CHAR                                szContentDirectory[MAX_PATH];
    WCHAR                               szDisplayName[MAX_CONTENT_DISPLAY_NAME];
} XCONTENT_FIND_DATA, *PXCONTENT_FIND_DATA;

XBOXAPI
HANDLE
WINAPI
XFindFirstContent(
    IN      LPCSTR                      szRootPathName,
    IN      DWORD                       dwFlagFilter,
    OUT     PXCONTENT_FIND_DATA         pFindContentData
    );

XBOXAPI
BOOL
WINAPI
XFindNextContent(
    IN      HANDLE                      hFindContent,
    OUT     PXCONTENT_FIND_DATA         pFindContentData
    );

XBOXAPI
BOOL
WINAPI
XGetContentInstallLocation(
    IN      DWORD                       dwTitleID,
    IN      LPCSTR                      szSourceMetadataFileName,
    OUT     LPSTR                       szInstallDirectory
    );

XBOXAPI
BOOL
WINAPI
XGetContentInstallLocationFromIDs(
    IN      DWORD                       dwTitleID,
    IN      XOFFERING_ID                xOfferingID,
    OUT     LPSTR                       szInstallDirectory
    );

XBOXAPI
BOOL
WINAPI
XInstallContentSignatures(
    IN      DWORD                       dwTitleID,
    IN      LPCSTR                      szSourceMetadataFileName,
    IN      LPCSTR                      szDestinationDirectory
    );

XBOXAPI
BOOL
WINAPI
XCreateContentSimple(
    IN      DWORD                       dwTitleID,
    IN      XOFFERING_ID                xOfferingID,
    IN      DWORD                       dwContentFlags,
    IN      LPCWSTR                     wszContentName,
    IN      LPCSTR                      szDestinationDirectory
    );

XBOXAPI
BOOL
WINAPI
XRemoveContent(
    IN      LPCSTR                      szDirectoryName
    );

XBOXAPI
HANDLE
WINAPI
XLoadContentSignaturesWithFileName(
    IN      DWORD                       dwTitleID,
    IN      LPCSTR                      szMetadataFileName
);

XBOXAPI
BOOL
WINAPI
XLocateSignatureByNameEx(
    IN      HANDLE                      hSignature,
    IN      LPCSTR                      szFileName,
    IN      DWORD                       dwFileOffset,
    IN OUT  LPDWORD                     pdwDataSize,
    OUT     LPBYTE*                     ppbSignatureData,
    OUT     LPDWORD                     pdwSignatureSize
);

XBOXAPI
BOOL
WINAPI
XLocateNextSignature(
    IN      HANDLE                      hSignature,
    OUT     LPSTR*                      pszFileName,
    OUT     LPDWORD                     pdwFileNameLength,
    OUT     LPDWORD                     pdwFileOffset,
    OUT     LPDWORD                     pdwDataSize,
    OUT     LPBYTE*                     ppbSignatureData,
    OUT     LPDWORD                     pdwSignatureSize
);

XBOXAPI
BOOL
WINAPI
XInstallContentSignaturesWithFileName(
    IN      DWORD                       dwTitleID,
    IN      LPCSTR                      szSourceMetadataFileName,
    IN      LPCSTR                      szDestinationName,
    IN      DWORD                       dwInstallFlags
);

XBOXAPI
BOOL
WINAPI
XInstallContentSignaturesEx(
    IN      DWORD                       dwTitleID,
    IN      LPCSTR                      szSourceMetadataFileName,
    IN      LPCSTR                      szInstallDirectory,
    IN      DWORD                       dwInstallFlags
    );

#define XSIG_INSTALL_NO_CHECK_SIGNATURE 0x00000001
#define XSIG_INSTALL_MARK_AS_INSTALLED  0x00000002

#define XCALCSIG_LIVE_SIGNATURE_SIZE    100

typedef struct {
    DWORD                               SignatureFlags;
    BYTE                                LiveSignature[XCALCSIG_LIVE_SIGNATURE_SIZE];
} XCONTSIG_LIVE_SIGNATURE_INFO, *PXCONTSIG_LIVE_SIGNATURE_INFO;

XBOXAPI
HANDLE
WINAPI
XLoadContentSignaturesEx(
    IN      DWORD                       dwTitleID,
    IN      LPCSTR                      szDirectoryName
    );

#define XLoadContentSignatures(lpDirectoryName) \
    XLoadContentSignaturesEx(0, lpDirectoryName)

XBOXAPI
BOOL
WINAPI
XLocateLiveSignature(
    IN      HANDLE                          hSignature,
    OUT     PXCONTSIG_LIVE_SIGNATURE_INFO   pxlsInfo,
    OUT     PBYTE                           pbLiveDigest
    );

XBOXAPI
BOOL
WINAPI
XLocateSignatureByIndex(
    IN      HANDLE                      hSignature,
    IN      DWORD                       dwSignatureIndex,
    OUT     LPBYTE*                     ppbSignatureData,
    OUT     LPDWORD                     pdwSignatureSize
    );

XBOXAPI
BOOL
WINAPI
XLocateSignatureByName(
    IN      HANDLE                      hSignature,
    IN      LPCSTR                      szFileName,
    IN      DWORD                       dwFileOffset,
    IN      DWORD                       dwDataSize,
    OUT     LPBYTE*                     ppbSignatureData,
    OUT     LPDWORD                     pdwSignatureSize
    );

XBOXAPI
BOOL
WINAPI
XCalculateContentSignature(
    IN      LPBYTE                      pbData,
    IN      DWORD                       dwDataSize,
    OUT     LPBYTE                      pbSignature,
    IN OUT  LPDWORD                     pdwSignatureSize
    );

XBOXAPI
VOID
WINAPI
XCloseContentSignatures(
    IN      HANDLE                      hSignature
    );

XBOXAPI
VOID
WINAPI
XComputeContentSignatureKey(
    IN      ULONG                       dwTitleID,
    OUT     PUCHAR                      pbSignatureKey
    );
XBOXAPI
DWORD
WINAPI
XGetLocale();
#define XC_VIDEO_STANDARD_PAL_M         4

//
// Index for reserved fields in XVIDEO_MODE
//

#define XVIDEO_MODE_INDEX_PIXEL_CLOCK   0

#define XC_AV_PACK_SDC                  0   // Standard-definition component
#define XC_AV_PACK_SCART                1   // SCART (composite and RGB SDTV)
#define XC_AV_PACK_RFU                  2   // RF SDTV
#define XC_AV_PACK_HDC                  3   // High-definition component
#define XC_AV_PACK_RESERVED             4   // Reserved
#define XC_AV_PACK_CSV                  5   // Composite/S-Video
#define XC_AV_PACK_PC                   6   // PC (output RGB VGA, hsync/vsync/DDC)
#define XC_AV_PACK_NONE                 7   // Indicates no AV pack plugged in
#define XC_AV_PACK_MAX                  8

XBOXAPI
DWORD
WINAPI
XGetAVPack(
    VOID
    );

XBOXAPI
DWORD
WINAPI
XGetVideoStandard(
    VOID
    );
#define XC_VIDEO_FLAGS_LETTERBOX        0x00000010
#define XC_VIDEO_FLAGS_PAL_60Hz         0x00000040

//
// Analog speaker configuration values are a enumeration while digital values
// are a bitmask.  0 is not a valid analog value, but 0 in the digital word
// indicates that no digital encoding or preencoded output is allowed on the
// digital channel.  In that case, the digital channel will output the same
// data as the analog.
//

#define XC_AUDIO_FLAGS_SURROUND             0x00000001
#define XC_AUDIO_FLAGS_MONO                 0x00000002
#define XC_AUDIO_FLAGS_ENABLE_DOLBYDIGITAL  0x00010000
#define XC_AUDIO_FLAGS_ENABLE_WMAPRO        0x00020000

#define XC_AUDIO_FLAGS_BASICMASK            0x0000FFFF
#define XC_AUDIO_FLAGS_ENCODEDMASK          0xFFFF0000

#define XC_AUDIO_FLAGS_BASIC(c)             ((DWORD)(c) & XC_AUDIO_FLAGS_BASICMASK)
#define XC_AUDIO_FLAGS_ENCODED(c)           ((DWORD)(c) & XC_AUDIO_FLAGS_ENCODEDMASK)
#define XC_AUDIO_FLAGS_COMBINED(b,e)        (XC_AUDIO_FLAGS_BASIC(b) | XC_AUDIO_FLAGS_ENCODED(e))

#define XC_AUDIO_FLAGS_DEFAULT              XC_AUDIO_FLAGS_COMBINED(XC_AUDIO_FLAGS_SURROUND, XC_AUDIO_FLAGS_ENABLE_DOLBYDIGITAL)

XBOXAPI
DWORD
WINAPI
XGetAudioFlags(
    VOID
    );
#define XC_CONSOLE_REGION_NA            0x00
#define XC_CONSOLE_REGION_ASIA          0x01
#define XC_CONSOLE_REGION_EUROPE        0x02
#define XC_CONSOLE_REGION_RESTOFWORLD   0x03
#define XC_CONSOLE_REGION_DEVKIT        0x7F

#define XC_GAME_REGION(region, subregion) \
    ((XC_CONSOLE_REGION_##region << 8) | (subregion))

#define XC_GAME_REGION_NA_ALL           XC_GAME_REGION(NA, 0xFF)
#define XC_GAME_REGION_ASIA_ALL         XC_GAME_REGION(ASIA, 0xFF)
#define XC_GAME_REGION_ASIA_JAPAN       XC_GAME_REGION(ASIA, 0x01)
#define XC_GAME_REGION_ASIA_CHINA       XC_GAME_REGION(ASIA, 0x02)
#define XC_GAME_REGION_ASIA_REST        XC_GAME_REGION(ASIA, 0xFC)
#define XC_GAME_REGION_EUROPE_ALL       XC_GAME_REGION(EUROPE, 0xFF)
#define XC_GAME_REGION_EUROPE_AUNZ      XC_GAME_REGION(EUROPE, 0x01)
#define XC_GAME_REGION_EUROPE_REST      XC_GAME_REGION(EUROPE, 0xFE)
#define XC_GAME_REGION_RESTOFWORLD_ALL  XC_GAME_REGION(RESTOFWORLD, 0xFF)
#define XC_GAME_REGION_DEVKIT_ALL       XC_GAME_REGION(DEVKIT, 0xFF)
#define XC_GAME_REGION_MANUFACTURING    0x8000

#define XC_GAME_REGION_REGION(region) \
    (((region) & 0xFF00) >> 8)

//
// These flags are stored in the retail flags (XCONFIG_USER_RETAIL_FLAGS).
//

#define XC_MISC_FLAG_AUTOPOWERDOWN      0x00000001
#define XC_MISC_FLAG_DONT_USE_DST       0x00000002
#define XC_MISC_FLAG_CONNECTIONNOTICE   0x00000004
#define XC_MISC_FLAG_24HCLOCK           0x00000008
#define XC_MISC_FLAG_NO_NOTIFY_DISPLAY  0x00000010
#define XC_MISC_FLAG_NO_NOTIFY_SOUND    0x00000020
#define XC_MISC_FLAG_OOBE_HAS_RUN       0x00000040

#define XC_MISC_FLAG_ALL_MASK           ((XC_MISC_FLAG_AUTOPOWERDOWN) | (XC_MISC_FLAG_DONT_USE_DST) | (XC_MISC_FLAG_CONNECTIONNOTICE) | \
                                         (XC_MISC_FLAG_24HCLOCK) | (XC_MISC_FLAG_NO_NOTIFY_DISPLAY) | (XC_MISC_FLAG_NO_NOTIFY_SOUND) | \
                                         (XC_MISC_FLAG_OOBE_HAS_RUN))

#define XINPUT_GAMEPAD_XE               0x0400
#define XINPUT_GAMEPAD_BINDING          0x0800
#define XINPUT_FLAG_SYSTEMAPP           0x80000000
#define XINPUT_MAX_RAW_BUFFER           (32)

typedef struct _XINPUT_RAW
{
    BYTE                                Buffer[XINPUT_MAX_RAW_BUFFER];
    BYTE                                Length;
    DWORD                               dwPacketNumber;
} XINPUT_RAW, *PXINPUT_RAW;

//
// The master vibration level is stored as a user profile setting.  It may be
// one of the following.  These are redundant definitions.  The actual profile
// enum values may be found in xonline.h, but this header includes these
// definitions for the driver and other system components.
//

#define XINPUT_VIBRATION_LEVEL_NONE     0
#define XINPUT_VIBRATION_LEVEL_LOW      1
#define XINPUT_VIBRATION_LEVEL_MEDIUM   2
#define XINPUT_VIBRATION_LEVEL_HIGH     3
#define XINPUT_VIBRATION_LEVEL_MAX      4

//
// Battery level may only be one of the following
//

#define XINPUT_BATTERY_LEVEL_LITTLE     0
#define XINPUT_BATTERY_LEVEL_LOW        1
#define XINPUT_BATTERY_LEVEL_MEDIUM     2
#define XINPUT_BATTERY_LEVEL_HIGH       3
#define XINPUT_BATTERY_LEVEL_MAX        4

//
// Wireless signal strength may be reported as one of the following values
//

#define XINPUT_SIGNAL_STRENGTH_VERY_LOW 0
#define XINPUT_SIGNAL_STRENGTH_LOW      1
#define XINPUT_SIGNAL_STRENGTH_MEDIUM   2
#define XINPUT_SIGNAL_STRENGTH_GOOD     3
#define XINPUT_SIGNAL_STRENGTH_MAX      4

typedef struct _XINPUT_DEVICE_STATS {
    ULONG                               ulBatteryLevel;
    ULONG                               ulSignalStrength;
    ULONG                               ulDeviceType;
    ULONG                               ulDevicePort;
    ULONG                               ulDeviceVersion;
} XINPUT_DEVICE_STATS, *PXINPUT_DEVICE_STATS;
XBOXAPI
DWORD
WINAPI
XInputSetStateEx(
    IN      DWORD                       dwUserIndex,
    IN      PXINPUT_VIBRATION           pVibration,
    IN      BYTE                        bAmplitude          OPTIONAL,
    IN      BYTE                        bFrequency          OPTIONAL,
    IN      BYTE                        bOffset             OPTIONAL
    );

XBOXAPI
DWORD
WINAPI
XInputRawState(
    IN      DWORD                       dwUserIndex,
    IN      DWORD                       dwFlags,
    IN      BOOL                        fSetState,
    IN      PXINPUT_RAW                 pRawState
    );

typedef struct _XINPUT_POLLING_PARAMETERS
{
    BYTE                                fAutoPoll:1;
    BYTE                                fInterruptOut:1;
    BYTE                                ReservedMBZ1:6;
    BYTE                                bInputInterval;
    BYTE                                bOutputInterval;
    BYTE                                ReservedMBZ2;
} XINPUT_POLLING_PARAMETERS, *PXINPUT_POLLING_PARAMETERS;

typedef struct _XINPUT_DEVICE_DESCRIPTION
{
    WORD                                wVendorID;
    WORD                                wProductID;
    WORD                                wVersion;
} XINPUT_DEVICE_DESCRIPTION, *PXINPUT_DEVICE_DESCRIPTION;

XBOXAPI
DWORD
WINAPI
XInputGetDeviceDescription(
    IN      HANDLE                      hDevice,
    OUT     PXINPUT_DEVICE_DESCRIPTION  pDescription
    );

#define XINPUT_LIGHTGUN_CALIBRATION_CENTER_X      0
#define XINPUT_LIGHTGUN_CALIBRATION_CENTER_Y      0
#define XINPUT_LIGHTGUN_CALIBRATION_UPPERLEFT_X  -25000
#define XINPUT_LIGHTGUN_CALIBRATION_UPPERLEFT_Y   25000

typedef struct _XINPUT_LIGHTGUN_CALIBRATION_OFFSETS
{
    WORD                                wCenterX;
    WORD                                wCenterY;
    WORD                                wUpperLeftX;
    WORD                                wUpperLeftY;
} XINPUT_LIGHTGUN_CALIBRATION_OFFSETS, *PXINPUT_LIGHTGUN_CALIBRATION_OFFSETS;

//
// XVoice APIs
//

typedef PVOID                           XVOICE_HANDLE, *PXVOICE_HANDLE;
typedef struct XMEDIAPACKET             *PXMEDIAPACKET;

#ifdef  __XVOICE_H__
XBOXAPI
HRESULT
WINAPI
XVoiceCreate(
    IN      DWORD                       dwUserIndex,
    IN      DWORD                       dwMaxAttachedPackets,
    OUT     PXVOICE_HANDLE              phHandle
    );

XBOXAPI
HRESULT
WINAPI
XVoiceSubmitPacket(
    IN      XVOICE_HANDLE               hObject,
    IN      BOOL                        fInput,
    IN OUT  PXMEDIAPACKET               pPacket
    );

XBOXAPI
BOOL
WINAPI
XVoiceClose(
    IN      XVOICE_HANDLE               hObject
    );
#endif  // __XVOICE_H__


XBOXAPI
DWORD
WINAPI
XCleanDrive(
    IN      CHAR                        chDrive
    );

XBOXAPI
BOOL
WINAPI
XapiRecovery(
    IN      BOOL                        QuickFormat
    );

#define XINIT_LIMIT_DEVKIT_MEMORY               0x00000004
#define XINIT_NO_SETUP_HARD_DISK                0x00000008
#define XINIT_DONT_MODIFY_HARD_DISK             0x00000010

XBOXAPI
DWORD
WINAPI
XMountUtilityDriveInternal(
    IN      DWORD                       dwTitleId,
    IN      BOOL                        fFormatClean,
    IN      DWORD                       dwBytesPerCluster,
    IN      SIZE_T                      dwFileCacheSize
    );

XBOXAPI
BOOL
WINAPI
XFormatUtilityDrive(
    VOID
    );

XBOXAPI
DWORD
WINAPI
XMountAlternateTitleA(
    IN      LPCSTR                      szRootPath,
    IN      DWORD                       dwAltTitleId,
    OUT     PCHAR                       pchDrive
    );
#define XMountAlternateTitle            XMountAlternateTitleA

XBOXAPI
DWORD
WINAPI
XUnmountAlternateTitleA(
    IN      CHAR                        chDrive
    );
#define XUnmountAlternateTitle          XUnmountAlternateTitleA

XBOXAPI
DWORD
WINAPI
XGetDiskSectorSizeA(
    IN      LPCSTR                      szRootPathName
    );
#define XGetDiskSectorSize              XGetDiskSectorSizeA

#define XBOX_HD_SECTOR_SIZE             512
#define XBOX_DVD_SECTOR_SIZE            2048
#define XBOX_MU_SECTOR_SIZE             4096

XBOXAPI
DWORD
WINAPI
XGetDiskClusterSizeA(
    IN      LPCSTR                      szRootPathName
    );
#define XGetDiskClusterSize             XGetDiskClusterSizeA


#ifdef _XBOX_ //only define this if xbox.h was already included.
#include <pshpack1.h>
typedef struct _XDCS_DVD_CODE_INFORMATION
{
    WORD                                bcdVersion;
    DWORD                               dwCodeLength;
} XDCS_DVD_CODE_INFORMATION, *PXDCS_DVD_CODE_INFORMATION;
#include <poppack.h>

typedef struct _XDCS_ASYNC_DOWNLOAD_REQUEST
{
    DWORD                               dwDeviceInstance;
    PVOID                               pvBuffer;
    ULONG                               ulOffset;
    ULONG                               ulLength;
    ULONG                               ulBytesRead;
    ULONG                               ulStatus;
    HANDLE                              hCompleteEvent;
} XDCS_ASYNC_DOWNLOAD_REQUEST, *PXDCS_ASYNC_DOWNLOAD_REQUEST;

DWORD
WINAPI
XDCSGetInformation(
    IN      DWORD                       dwPort,
    OUT     PDWORD                      pdwDeviceInstance,
    OUT     PXDCS_DVD_CODE_INFORMATION  pDvdCodeInformation
    );

DWORD
WINAPI
XDCSDownloadCode(
    DWORD                               dwDeviceInstance,
    PVOID                               pvBuffer,
    ULONG                               ulOffset,
    ULONG                               ulLength,
    PULONG                              pulBytesRead
    );

DWORD
WINAPI
XDCSDownloadCodeAsync(
    IN OUT  PXDCS_ASYNC_DOWNLOAD_REQUEST pXDCSDownloadRequest
    );
#endif  //_XBOX_

BOOL
WINAPI
XapiSetLocalTime(
    IN      CONST SYSTEMTIME*           lpLocalTime
    );

DWORD
WINAPI
XapipQueryTimeZoneInformation(
    OUT     PTIME_ZONE_INFORMATION      TimeZoneInformation,
    OUT     PBOOL pfUseDST
    );

DWORD
WINAPI
XapipSetTimeZoneInformation(
    IN      PTIME_ZONE_INFORMATION      TimeZoneInformation
    );

BOOL
WINAPI
XapipUseDaylightSavingTime();

#define MAX_LAUNCH_DATA_SIZE            1020
#define XLDEMO_RUNMODE_KIOSKMODE        0x01
#define XLDEMO_RUNMODE_USERSELECTED     0x02
#define MAX_LAUNCH_CMDLINE_SIZE         256


//
// Structures and enumerations for LaunchData.
//

#define XDASHLAUNCHDATA_RESERVED_SIZE   (MAX_LAUNCH_DATA_SIZE - 12)

#define XDASHLAUNCHDATA_COMMAND_DEFAULT                             0
#define XDASHLAUNCHDATA_COMMAND_SIGNUP                              1
#define XDASHLAUNCHDATA_COMMAND_NETWORKTROUBLESHOOTER               2
#define XDASHLAUNCHDATA_COMMAND_ARCADE                              3
#define XDASHLAUNCHDATA_COMMAND_MEMORY                              4
#define XDASHLAUNCHDATA_COMMAND_MUSIC                               6
#define XDASHLAUNCHDATA_COMMAND_DVD                                 7
#define XDASHLAUNCHDATA_COMMAND_MCXDOWNLOADER                       8    // MCX depends on this value *never* changing
#define XDASHLAUNCHDATA_COMMAND_MEDIANETWORKTROUBLESHOOTER          9
#define XDASHLAUNCHDATA_COMMAND_ACCOUNTMANAGE_HOME                  10
#define XDASHLAUNCHDATA_COMMAND_ACCOUNTMANAGE_PRIVACY               11
#define XDASHLAUNCHDATA_COMMAND_ACCOUNTMANAGE_ACCEPTTOU             12
#define XDASHLAUNCHDATA_COMMAND_ACCOUNTMANAGE_BILLING               13
#define XDASHLAUNCHDATA_COMMAND_GAMES_DEMOS                         14
#define XDASHLAUNCHDATA_COMMAND_GAMES_TRAILERS                      15
#define XDASHLAUNCHDATA_COMMAND_RETURNFROMENTRYPOINT_MUSIC          16
#define XDASHLAUNCHDATA_COMMAND_MARKETPLACE_TILES                   17
#define XDASHLAUNCHDATA_COMMAND_SETTINGS                            18
#define XDASHLAUNCHDATA_COMMAND_RETURNFROMENTRYPOINT_GAMES          19
#define XDASHLAUNCHDATA_COMMAND_FAMILYSETTINGS                      20
#define XDASHLAUNCHDATA_COMMAND_RETURNFROMENTRYPOINT_SYSTEM         21
#define XDASHLAUNCHDATA_COMMAND_OOBE_WELCOME                        22
#define XDASHLAUNCHDATA_COMMAND_GAMES_ARCADE                        23

typedef struct _XDASHLAUNCHDATA
{
    DWORD                               dwVersion;
    DWORD                               dwCommand;
    DWORD                               dwUserIndex;
    BYTE                                Reserved[XDASHLAUNCHDATA_RESERVED_SIZE];
} XDASHLAUNCHDATA;


XBOXAPI
DWORD
WINAPI
XSetLaunchData(
    IN      PVOID                       pLaunchData,
    IN      DWORD                       dwLaunchDataSize
    );

XBOXAPI
DWORD
WINAPI
XGetLaunchDataSize(
    OUT     LPDWORD                     pdwLaunchDataSize
    );

XBOXAPI
DWORD
WINAPI
XGetLaunchData(
    OUT     PVOID                       pBuffer,
    IN      DWORD                       dwBufferSize
    );

DECLSPEC_NORETURN
XBOXAPI
VOID
WINAPI
XLaunchNewImage(
    IN      LPCSTR                      szImagePath,
    IN      DWORD                       dwFlags
    );

// XLaunchNewImage keyword constants.
// Titles depend on these strings staying the same.
#define XLAUNCH_KEYWORD_DETECT_MEDIA    "XLNI_DET_MEDIA"

#define XLAUNCH_FLAG_FROM_MEMORY        0x00000001
#define XLAUNCH_FLAG_DETECT_MEDIA       0x00000002
#define XLAUNCH_FLAG_NO_ABSOLUTE_PATHS  0x00000004
#define XLAUNCH_FLAG_NO_PACKAGES        0x00000008
#define XLAUNCH_FLAG_UNLOAD_HUD         0x00000010
#define XLAUNCH_FLAG_BOUND_PATH         0x00000020
#define XLAUNCH_FLAG_SYSTEM_VERSION     0x00000040
#define XLAUNCH_FLAG_ASSUME_DVD         0x00000080
#define XLAUNCH_FLAG_DASH_ARCADE        0x00000100
#define XLAUNCH_FLAG_HYBRID_FORCE_DVD   0x00000200
#define XLAUNCH_FLAG_HYBRID_FORCE_GAME  0x00000400
#define XLAUNCH_FLAG_HYBRID_NO_NOTIFY   0x00000800

#define XTRAY_STATE_CLOSED            0
#define XTRAY_STATE_CLOSING           1
#define XTRAY_STATE_OPEN              2
#define XTRAY_STATE_OPENING           3
#define XTRAY_STATE_READING           4

XBOXAPI
DWORD
WINAPI
XGetTrayState(
    VOID
    );

XBOXAPI
HRESULT
WINAPI
XLaunchMedia(
    VOID
    );

XBOXAPI
VOID
WINAPI
XLaunchNewImageEx(
    IN      LPCSTR                      szImagePath,
    IN      LPCSTR                      szDDrivePath,
    IN      LPCSTR                      szCmdLine,
    IN      DWORD                       dwFlags
    );

typedef struct _XSWAPDISC_RESULTS
{
    DWORD   dwNewDiscNumber;
} XSWAPDISC_RESULTS, *PXSWAPDISC_RESULTS;

XBOXAPI
DWORD
WINAPI
XSwapDiscAndLaunchNewImage(
    IN      LPCWSTR                     wszDiscName,
    IN      DWORD                       dwDiscNumber,
    IN      LPCSTR                      szImagePath,
    IN      DWORD                       dwFlags,
    OUT     PXSWAPDISC_RESULTS          pResults            OPTIONAL,
    IN OUT  PXOVERLAPPED                pOverlapped         OPTIONAL
    );

//
// Register or deregister a notification routine
// which will be called when a thread is created or deleted.
//
// NOTE: The XTHREAD_NOTIFICATION structure must remain
// valid until the thread notification routine is deregistered.
// For example, you can use a global variable for this.
// But you should NOT use a local variable inside a function.
//
DWORD
WINAPI
XGetFilePhysicalSortKey(
    IN      HANDLE                      hFile
    );

VOID
WINAPI
XSetProcessHeap(
    IN      HANDLE                      hHeap
    );

#define XCALCSIG_SIGNATURE_SIZE         20
typedef union {
    BYTE                                Signature[XCALCSIG_SIGNATURE_SIZE];
    BYTE                                LiveSignature[XCALCSIG_LIVE_SIGNATURE_SIZE];
} XCALCSIG_SIGNATURE, *PXCALCSIG_SIGNATURE;

#define XCALCSIG_FLAG_SAVE_GAME         (0x00000000)
#define XCALCSIG_FLAG_NON_ROAMABLE      (0x00000001)
#define XCALCSIG_FLAG_CONTENT           (0x00000002)
#define XCALCSIG_FLAG_DIGEST            (0x00000004)
#define XCALCSIG_FLAG_ONLINE            (0x00000008)

XBOXAPI
HANDLE
WINAPI
XCalculateSignatureBegin(
    IN      DWORD                       dwFlags
    );

XBOXAPI
HANDLE
WINAPI
XCalculateSignatureBeginEx(
    IN      DWORD                       dwFlags,
    IN      DWORD                       dwAltTitleId
    );

XBOXAPI
DWORD
WINAPI
XCalculateSignatureUpdate(
    IN      HANDLE                      hCalcSig,
    IN      CONST BYTE*                 pbData,
    IN      ULONG                       cbData
    );

XBOXAPI
DWORD
WINAPI
XCalculateSignatureEnd(
    IN      HANDLE                      hCalcSig,
    OUT     PXCALCSIG_SIGNATURE         pSignature
    );

XBOXAPI
ULONG
WINAPI
XAutoPowerDownTimeRemaining(
    VOID
    );

typedef VOID (*FLASH_PROGRESS_ROUTINE)(ULONG BytesWritten);

XBOXAPI
DWORD
WINAPI
XapiFlashKernelImage(
    IN      PVOID                       ImageBuffer,
    IN      SIZE_T                      ImageSize,
    IN      BOOL                        IgnoreVersionChecking,
    IN      BOOL                        ForceStockImage,
    IN      FLASH_PROGRESS_ROUTINE      ProgressRoutine         OPTIONAL
    );

XBOXAPI
BOOL
WINAPI
XapiReplaceRootDirectoryFile(
    IN      HANDLE                      hVolume,
    IN      LPCSTR                      szReplacedFileName,
    IN      LPCSTR                      szReplacementFileName,
    IN      BOOL                        fCleanupMode
    );
// XOVERLAPPED::InternalLow is a Win32 error code.  If the operation is pending
// the value is ERROR_IO_PENDING, else it is the result of the operation.
#define XCONTENTTYPE_NONE                           0x00000000
#define XCONTENTTYPE_PROFILE                        0x00010000
#define XCONTENTTYPE_GAMERPICTURE                   0x00020000
#define XCONTENTTYPE_THEMATICSKIN                   0x00030000
#define XCONTENTTYPE_CACHE                          0x00040000
#define XCONTENTTYPE_STORAGEDOWNLOAD                0x00050000
#define XCONTENTTYPE_XBOXSAVEDGAME                  0x00060000
#define XCONTENTTYPE_XBOXDOWNLOAD                   0x00070000
#define XCONTENTTYPE_GAMEDEMO                       0x00080000
#define XCONTENTTYPE_VIDEO                          0x00090000
#define XCONTENTTYPE_GAMETITLE                      0x000A0000
#define XCONTENTTYPE_INSTALLER                      0x000B0000
#define XCONTENTTYPE_GAMETRAILER                    0x000C0000
#define XCONTENTTYPE_ARCADE                         0x000D0000

#define XCONTENTTYPE_PRIVATEMASK                    0xFFFF0000
#define XCONTENTTYPE_PUBLICMASK                     0x0000FFFF
#define XCONTENTTYPE_VALID                          (XCONTENTTYPE_PRIVATEMASK | XCONTENTTYPE_PUBLICMASK)
#define XCONTENTTYPE_ANY                            XCONTENTTYPE_VALID
#define _XCONTENTFLAG_CREATIONMASK_                 0x0000000F
#define XCONTENTFLAG_DISALLOWSOURCEDEVICESELECTION  0x00000400

#define XCONTENTFLAG_EXECUTE                        0x04000000

//  Private enumeration scoping
#define XCONTENTFLAG_OWNER                          0x10000000
#define XCONTENTFLAG_TITLE                          0x20000000
#define XCONTENTFLAG_TYPE                           0x40000000

#define XCONTENTFLAG_ENUM_SCOPING_MASK              (XCONTENTFLAG_ENUM_EXCLUDECOMMON                | \
                                                     XCONTENTFLAG_OWNER                             | \
                                                     XCONTENTFLAG_TITLE                             | \
                                                     XCONTENTFLAG_TYPE)


#define XCONTENTFLAGS_VALID                         (XCONTENTFLAG_NONE                              | \
                                                     XCONTENTFLAG_CREATENEW                         | \
                                                     XCONTENTFLAG_CREATEALWAYS                      | \
                                                     XCONTENTFLAG_OPENEXISTING                      | \
                                                     XCONTENTFLAG_OPENALWAYS                        | \
                                                     XCONTENTFLAG_TRUNCATEEXISTING                  | \
                                                     XCONTENTFLAG_NOPROFILE_TRANSFER                | \
                                                     XCONTENTFLAG_STRONG_SIGNED                     | \
                                                     XCONTENTFLAG_NODEVICE_TRANSFER                 | \
                                                     XCONTENTFLAG_MANAGESTORAGE                     | \
                                                     XCONTENTFLAG_FORCE_SHOW_UI                     | \
                                                     XCONTENTFLAG_DISALLOWSOURCEDEVICESELECTION     | \
                                                     XCONTENTFLAG_ENUM_EXCLUDECOMMON                | \
                                                     XCONTENTFLAG_EXECUTE                           | \
                                                     XCONTENTFLAG_OWNER                             | \
                                                     XCONTENTFLAG_TITLE                             | \
                                                     XCONTENTFLAG_TYPE)


#ifdef  __cplusplus
typedef struct _XCONTENT_DATA_INTERNAL : public XCONTENT_DATA {
#else   // __cplusplus
typedef struct _XCONTENT_DATA_INTERNAL {
    XCONTENT_DATA;
#endif  // !__cplusplus
    XUID                                xuid;
    DWORD                               dwTitleId;
} XCONTENT_DATA_INTERNAL, *PXCONTENT_DATA_INTERNAL;

#define XCONTENTDEVICETYPE_NONE         ((XCONTENTDEVICETYPE)0)
#define XCONTENTDEVICETYPE_SYSTEMMU     ((XCONTENTDEVICETYPE)3)
#define XCONTENTDEVICETYPE_USBMASS      ((XCONTENTDEVICETYPE)16)

#define XCONTENTDEVICETYPE_MASK         0xF

//
// This flag is OR'd into a device type if the device is unformatted
//

#define XCONTENTDEVICEFLAG_UNFORMATTED  ((XCONTENTDEVICETYPE)0x80000000)

//
// This flag can be supplied to XContentCreateDeviceEnumerator to enumerate
// USB mass storage devices
//

#define XCONTENTDEVICEFLAG_USBMASS      (0x40000000)

typedef struct _XCREATECONTENTPARAM
{
    DWORD                               dwUserIndex;
    CHAR                                szRootName[64];
    union
    {
        XCONTENT_DATA                   cd;
        XCONTENT_DATA_INTERNAL          cdi;
    };
    DWORD                               dwContentFlags;
    PDWORD                              pdwDisposition;
    PDWORD                              pdwLicenseMask;
    DWORD                               dwFileCacheSize;
    ULARGE_INTEGER                      uliContentSize;
    PXOVERLAPPED                        pOverlapped;
    DWORD                               cbContentData;
} XCREATECONTENTPARAM, *PXCREATECONTENTPARAM;


typedef PVOID                           HXAMAPP;

#define XENUMHEADERFLAG_NONE            0x00000000
#define XENUMHEADERFLAG_FOREGROUND_PRI  0x00000001

typedef struct _XENUMERATORHEADER
{
    HXAMAPP                             hxamapp;
    DWORD                               dwMsgIDEnum;
    DWORD                               dwMsgIDCloseEnum;
    DWORD                               dwUserIndex;
    DWORD                               cItemsRequested;
    DWORD                               dwEnumFlags;
} XENUMERATORHEADER, *PXENUMERATORHEADER;

DWORD
WINAPI
XContentCreateDeviceEnumerator(
    IN      DWORD                       dwContentTypes,
    IN      DWORD                       dwFlags,
    IN      DWORD                       cItem,
    OUT     PDWORD                      pcbBuffer           OPTIONAL,
    OUT     PHANDLE                     phEnum
    );

DWORD
WINAPI
XContentFormatDevice(
    IN      XCONTENTDEVICEID            DeviceID,
    IN OUT  PXOVERLAPPED                pOverlapped         OPTIONAL
    );

DWORD
WINAPI
XContentRenameDevice(
    IN      XCONTENTDEVICEID            DeviceID,
    IN      LPCWSTR                     pwszName,
    IN      DWORD                       cchName
    );


typedef struct _XENUMERATEPARAM
{
    DWORD                               dwUserIndex;
    DWORD                               dwFlags;
    PVOID                               pvPrivateEnumStructure;
    PVOID                               pvBuffer;
    DWORD                               cbBuffer;
    DWORD                               cItemsRequested;
    PDWORD                              pcItemsReturned;
    PXOVERLAPPED                        pxoverlapped;
} XENUMERATEPARAM;

// Enumeration flags
#define ENUMERATEFLAG_NONE                      0x00000000
#define ENUMERATEFLAG_BACK                      0x00000001
#define ENUMERATEFLAG_FOREGROUND                0x00000002
#define ENUMERATEFLAG_MATCHINGINSTANCE          0x00000004
#define ENUMERATEFLAG_INCLUDEPARTIALDOWNLOADS   0x00000008
#define ENUMERATEFLAG_INCLUDECORRUPTCONTENT     0x00000010

//-----------------------------------------------------------------------------
//  Private Game Instrumentation structures and functions
//-----------------------------------------------------------------------------

typedef struct
{
    DWORD                               dwUserIndex;
    XUID                                xuid;
    DWORD                               dwContextId;
    DWORD                               dwContextValue;
} XGI_USERSETCONTEXT_MSG, *PXGI_USERSETCONTEXT_MSG;

typedef struct
{
    DWORD                               dwUserIndex;
    XUID                                xuid;
    DWORD                               dwPropertyId;
    DWORD                               cbValue;
    CONST VOID*                         pvValue;
} XGI_USERSETPROPERTY_MSG;

// General enumererator structure for XGI title and achievement enumerations
typedef struct _XENUMERATOR_XGI
{
    DWORD                               dwTitleId;
    XUID                                xuid;
    DWORD                               dwUserIndex;
    DWORD                               dwDetailFlags;
    DWORD                               dwCurrentOffset;
    BOOL                                fServer;
} XENUMERATOR_XGI, *PXENUMERATOR_XGI;

typedef struct _XGI_CREATEENUM_MSG
{
    DWORD                               dwTitleId;          // A title in your family or 0 for the current title
    DWORD                               dwUserIndex;        // User index of locally signed-in user whose "things" are enumerated
    XUID                                xuid;               // XUID of remote user whose "things" are enumerated
    DWORD                               dwDetailFlags;      // Get the descriptions, etc. (used for achievements)
    DWORD                               dwStartingIndex;    // Number to start at
    PXENUMERATOR_XGI                    pxenum;
} XGI_CREATEENUM_MSG, *PXGI_CREATEENUM_MSG;

// Message passed to system app to write an achievement
typedef struct
{
    DWORD                               dwNumAchievements;      // Number of structs in pAchievements
    CONST XUSER_ACHIEVEMENT*            pAchievements;          // Achievement/user tuple to set
} XGI_WRITEACHIEVEMENT_MSG;

//-----------------------------------------------------------------------------
// Internal functions
//-----------------------------------------------------------------------------

DWORD XVerifySameFamily(DWORD dwTitleId);


//
// Internal only privileges
//

#define XPRIVILEGE_ADD_FRIEND                           255 // on|off
#define XPRIVILEGE_MULTIPLAYER_ENABLED_BY_TIER          253 // on|off
#define XPRIVILEGE_VIDEO_MESSAGING_SEND                 250 // on|off
#define XPRIVILEGE_XBOX1_LIVE_ACCESS                    242 // on|off

#define X_PROPERTY_MODIFIER_MASK        0x0F000000
#define X_PROPERTY_MATCHTYPE_MASK       0x00F00000
#define X_PROPERTY_RESERVED_MASK        0x000F0000
// These must match the X_ATTRIBUTE_TYPE_MASK value defines
#define X_PROPERTY_MODIFIER_PARAM       0x02000000
#define X_PROPERTY_MODIFIER_BUILTIN     0x03000000
#define X_PROPERTY_MODIFIER_CONSTANT    0x05000000

// These must match the X_ATTRIBUTE_DATATYPE_MASK value defines
#define X_PROPERTY_MATCHTYPE_INTEGER    0x00000000
#define X_PROPERTY_MATCHTYPE_STRING     0x00100000
#define X_PROPERTY_MATCHTYPE_BLOB       0x00200000
#define X_PROPERTY_MATCHTYPE_NULL       0x00F00000

// Picture keys are in the format of XXXXXXXXXYYYYYYYYZZZZZZZZ
// where
//  XXXXXXXX is the title id associated with the picture (in hex)
//  YYYYYYYY is the normal picture image id (in hex)
//  ZZZZZZZZ is the small picture image id (in hex)
//

#define XUSER_PICTURE_KEY_LEN           ((sizeof(DWORD) * 2) * 3)
// Add room for a terminating null
#define XUSER_PICTURE_KEY_CHARS         (XUSER_PICTURE_KEY_LEN + 1)

// Stats APIs
//-----------------------------------------------------------------------------
//  Private stats structures and functions
//-----------------------------------------------------------------------------

typedef struct _XGI_VIEWRESET_MSG
{
    DWORD                               dwUserIndex;
    DWORD                               dwViewId;
} XGI_VIEWRESET_MSG, *PXGI_VIEWRESET_MSG;

typedef struct  _XGI_STATSREAD_MSG
{
    DWORD                               dwTitleId;
    DWORD                               dwNumXuids;
    CONST XUID*                         pXuids;
    DWORD                               dwNumStatsSpecs;
    CONST XUSER_STATS_SPEC*             pSpecs;
    DWORD                               cbResults;
    PXUSER_STATS_READ_RESULTS           pResults;
} XGI_STATSREAD_MSG, *PXGI_STATSREAD_MSG;

typedef struct _XGI_STATSENUM_MSG
{
    DWORD                               dwTitleId;
    DWORD                               dwRankStart;
    DWORD                               dwNumRows;
    DWORD                               dwNumStatsSpecs;
    CONST XUSER_STATS_SPEC*             pSpecs;
    DWORD                               cbBuffer;
    PHANDLE                             ph;                 // Handle to created enumerator
} XGI_STATSENUM_MSG, *PXGI_STATSENUM_MSG;


typedef enum _XGI_STATS_ENUMERATOR_TYPE
{
    XGI_STATS_ENUM_BY_XUID,
    XGI_STATS_ENUM_BY_RANK,
    XGI_STATS_ENUM_BY_RANK_PER_SPEC,
    XGI_STATS_ENUM_BY_RATING
} XGI_STATS_ENUMERATOR_TYPE;

// Data held by each stats enumerator.
typedef struct _XENUMERATOR_STATS
{
    DWORD                               dwTitleId;
    XGI_STATS_ENUMERATOR_TYPE           enumType;
    ULONGLONG                           qwPivot;
    PDWORD                              pStaringRanks;
    DWORD                               dwNumStatsSpecs;
    PXUSER_STATS_SPEC                   pSpecs;
} XENUMERATOR_STATS, *PXENUMERATOR_STATS;

typedef struct _XGI_CREATESTATSENUM_MSG
{
    DWORD                               dwTitleId;
    PXENUMERATOR_STATS                  pStatsEnum;
} XGI_CREATESTATSENUM_MSG, *PXGI_CREATESTATSENUM_MSG;

// Signin UI API
#define XSSUI_FLAGS_ADDUSER                         0x00010000
#define XSSUI_FLAGS_COMPLETESIGNIN                  0x00020000
#define XSSUI_FLAGS_SHOWONLYPARENTALLYCONTROLLED    0x00040000
#define XSSUI_FLAGS_ENABLE_GUEST                    0x00080000
#define XSSUI_FLAGS_DISALLOWRELOAD                  0x00100000
#define XSSUI_FLAGS_VALID                   (XSSUI_FLAGS_SHOWONLYONLINEENABLED | \
                                             XSSUI_FLAGS_LOCALSIGNINONLY | \
                                             XSSUI_FLAGS_ADDUSER | \
                                             XSSUI_FLAGS_COMPLETESIGNIN | \
                                             XSSUI_FLAGS_SHOWONLYPARENTALLYCONTROLLED | \
                                             XSSUI_FLAGS_ENABLE_GUEST | \
                                             XSSUI_FLAGS_DISALLOWRELOAD)


XBOXAPI
DWORD
WINAPI
XShowSigninUIp(
    IN      DWORD                       dwUserIndex,
    IN      DWORD                       cPanes,
    IN      DWORD                       dwFlags
    );


typedef enum _XSHOWMARKETPLACEUI_PRIVATE_ENTRYPOINTS {
    XSHOWMARKETPLACEUI_PRIVATE_ENTRYPOINT_ADDPOINTS = XSHOWMARKETPLACEUI_ENTRYPOINT_MAX,
    XSHOWMARKETPLACEUI_PRIVATE_ENTRYPOINT_PREPAIDCODE,
    XSHOWMARKETPLACEUI_PRIVATE_ENTRYPOINT_FNC,
    XSHOWMARKETPLACEUI_PRIVATE_ENTRYPOINT_GAMERTAGPURCHASE,
    XSHOWMARKETPLACEUI_PRIVATE_ENTRYPOINT_SIGNUP_CREDITCARD,
    XSHOWMARKETPLACEUI_PRIVATE_ENTRYPOINT_SIGNUP_PARENTCREDITCARD,
    XSHOWMARKETPLACEUI_PRIVATE_ENTRYPOINT_FILTERED_CONTENTLIST,
    XSHOWMARKETPLACEUI_PRIVATE_ENTRYPOINT_MAX
} XSHOWMARKETPLACEUI_PRIVATE_ENTRYPOINTS;

#define XMB_ICONMASK                    0x00000003
#define XMB_WAITANIMATION               0x00001000
#define XMB_LIVEPASSCODEMODE            0x00030000
#define XMB_MODEMASK                    0x00030000

#define MAXACTIONTEXTLENGTH             30
#define MAXACTIONS                      3

XBOXAPI
VOID
WINAPI
XCustomGetActionSetting(
   IN       DWORD                       dwActionIndex,
   OUT      DWORD*                      pdwFlags,
   OUT      LPWSTR                      szActionText,
   IN       DWORD                       cchMaxText
   );

XBOXAPI
VOID
WINAPI
XCustomBroadcastActionEvent(
    IN      DWORD                       dwUserIndex,
    IN      DWORD                       dwActionIndex,
    IN      XUID                        xuid
    );

#ifndef HXUIBRUSH
typedef struct _XUIBRUSH*               HXUIBRUSH;
#endif

HRESULT
WINAPI
XCustomGetBannerImage(
    OUT     HXUIBRUSH*                  phBrush
    );

#ifdef __cplusplus
}
#endif

#pragma warning(pop)

#endif  // _XBOXP_

