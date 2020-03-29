/*++

Copyright (c) 2000-2005  Microsoft Corporation

Module Name:

    xex.h

Abstract:

    This module contains the structures that describe the Xenon Executable (XEX)
    format.

--*/

#ifndef _XEX_H_
#define _XEX_H_

#include "xexhv.h"

#pragma warning(push)
#pragma warning(disable:4201)

#define MAX_XEX_HEADERS_SIZE    (64 * 1024)

typedef struct _XEX_SECURITY_INFO {
    //
    // The size of this header.
    //
    ULONG Size;

    //
    // Specifies the total size of the image as loaded in memory (not
    // including headers).
    //
    ULONG ImageSize;

    //
    // The root of trust for this image.
    //
    HV_IMAGE_INFO ImageInfo;

    //
    // Specifies the allowed media sources for this image.
    //
    ULONG AllowedMediaTypes;

    //
    // The number of page ranges.
    //
    ULONG PageDescriptorCount;

    //
    // The individual page descriptors follow this structure.
    //
} XEX_SECURITY_INFO, *PXEX_SECURITY_INFO;

//
// All valid media types from which images may be loaded.
// N.B. Any media that may be inserted through the optical disc drive should be
// added to XEX_MEDIA_TYPE_DISC_MEDIA_MASK
//

#define XEX_MEDIA_TYPE_HARD_DISK                0x00000001
#define XEX_MEDIA_TYPE_DVD_X2                   0x00000002
#define XEX_MEDIA_TYPE_DVD_CD                   0x00000004
#define XEX_MEDIA_TYPE_DVD_5_RO                 0x00000008
#define XEX_MEDIA_TYPE_DVD_9_RO                 0x00000010
#define XEX_MEDIA_TYPE_FLASH                    0x00000020
#define XEX_MEDIA_TYPE_MEMORY_UNIT              0x00000080
#define XEX_MEDIA_TYPE_MASS_STORAGE             0x00000100
#define XEX_MEDIA_TYPE_NETWORK_FILESYSTEM       0x00000200
#define XEX_MEDIA_TYPE_UNKNOWN_SOURCE           0x00000400
#define XEX_MEDIA_TYPE_PACKAGE_MASK             0xFF000000
#define XEX_MEDIA_TYPE_PACKAGE(PackageType) \
    (1 << ((PackageType) + 24))

#define XEX_PACKAGE_TYPE_UNKNOWN                0x00
#define XEX_PACKAGE_TYPE_ANY_CONSOLE            0x01
#define XEX_PACKAGE_TYPE_THIS_CONSOLE           0x02
#define XEX_PACKAGE_TYPE_XBOX_LIVE              0x03
#define XEX_PACKAGE_TYPE_XBOX_PLATFORM          0x04
#define XEX_NUMBER_OF_PACKAGE_TYPES             0x05

#define XEX_MEDIA_TYPE_DISC_MEDIA_MASK          \
    (XEX_MEDIA_TYPE_DVD_X2 |                    \
    XEX_MEDIA_TYPE_DVD_CD |                     \
    XEX_MEDIA_TYPE_DVD_5_RO |                   \
    XEX_MEDIA_TYPE_DVD_9_RO)

//
// Everything in the header is stored in big-endian format.
//

typedef struct _IMAGE_XEX_HEADER {

    //
    // Contains XEX_HEADER_MAGIC.
    //
    ULONG Magic;

    //
    // Flags describing the load policy of this object to the loader.
    //
    ULONG ModuleFlags;

    //
    // Specifies the total size of header information, including this
    // header.
    //
    ULONG SizeOfHeaders;

    //
    // Specifies the size of header information that can be discarded
    // after the load is complete.
    //
    ULONG SizeOfDiscardableHeaders;

    //
    // A pointer to the security information for this module (in the file,
    // this a RVA).
    //
    PXEX_SECURITY_INFO SecurityInfo;

    //
    // Specifies the number of entries in the header field directory.
    //
    ULONG HeaderDirectoryEntryCount;
} IMAGE_XEX_HEADER, *PIMAGE_XEX_HEADER;

#define XEX_HEADER_MAGIC                        'XEX2'

//
// The type of this object.  This is a union of policy bits that describe
// the way the loader will treat this module:
//
#define XEX_MODULE_FLAG_TITLE_PROCESS   0x0001
#define XEX_MODULE_FLAG_TITLE_IMPORTS   0x0002
#define XEX_MODULE_FLAG_DEBUGGER        0x0004
#define XEX_MODULE_FLAG_DLL             0x0008
#define XEX_MODULE_FLAG_PATCH           0x0010
#define XEX_MODULE_FLAG_PATCH_FULL      0x0020
#define XEX_MODULE_FLAG_PATCH_DELTA     0x0040
#define XEX_MODULE_TYPE_TITLE \
    (XEX_MODULE_FLAG_TITLE_PROCESS)
#define XEX_MODULE_TYPE_TITLE_DLL \
    (XEX_MODULE_FLAG_TITLE_PROCESS | XEX_MODULE_FLAG_DLL)
#define XEX_MODULE_TYPE_SYSTEM_APP \
    (XEX_MODULE_FLAG_DLL)
#define XEX_MODULE_TYPE_SYSTEM_DLL \
    (XEX_MODULE_FLAG_DLL | XEX_MODULE_FLAG_TITLE_IMPORTS)

#define XEX_MODULE_FLAG_BOUND_PATH      0x40000000
#define XEX_MODULE_FLAG_SILENT_LOAD     0x80000000

//
// After the header structure is a list of header directory entries.  Each
// entry is an ordered pair of (key, value).  The keys correspond to the types
// of header data that can be present.  The upper 24 bits of the key number
// describe the type of data described (exe name, title ID, loader policy,
// whatever), and the lower 8 bits describe the size of the data in DWORDs.  If
// the size is 0, there is no data; if the size is 1, the value in the header
// is the value of the data; if the size is more than 1, the value in the
// header is the file offset to the location of the data.  The size 255 has a
// special meaning, indicating that the referenced data describes its own size
// in its first DWORD.
//

typedef struct _IMAGE_XEX_DIRECTORY_ENTRY {
    ULONG Key;
    ULONG Value;
} IMAGE_XEX_DIRECTORY_ENTRY, *PIMAGE_XEX_DIRECTORY_ENTRY;

#define XEX_HEADER_STRUCT(key, struct) \
    (((key) << 8) | (sizeof (struct) >> 2))
#define XEX_HEADER_FIXED_SIZE(key, size) \
    (((key) << 8) | ((size) >> 2))
#define XEX_HEADER_ULONG(key) \
    (((key) << 8) | 1)
#define XEX_HEADER_FLAG(key) \
    ((key) << 8)
#define XEX_HEADER_SIZEDSTRUCT(key) \
    (((key) << 8) | 0xFF)

#define XEX_HEADER_STRING(key) \
    XEX_HEADER_SIZEDSTRUCT(key)

//
// A section header.
//
#define XEX_SECTION_NAME_LENGTH         8

typedef struct _XEX_SECTION_HEADER {
    //
    // Name of this section
    //
    CHAR    SectionName[XEX_SECTION_NAME_LENGTH];

    //
    // Base address of this section
    //
    ULONG   VirtualAddress;

    //
    // Size of this section as loaded
    //
    ULONG   VirtualSize;
} XEX_SECTION_HEADER, *PXEX_SECTION_HEADER;

//
// The section table is a ULONG size of the total table followed by
// individual section entries stored in base address order.  The count
// is determined from the size of the table.
//
#define XEX_HEADER_SECTION_TABLE \
    XEX_HEADER_SIZEDSTRUCT(2)

//
// A description of blockwise data in this image.
//
typedef struct _XEX_DATA_DESCRIPTOR {
    //
    // The size of the data area.
    //
    ULONG   Size;

    //
    // The root digest of the data area.
    //
    UCHAR   DataDigest[20];
} XEX_DATA_DESCRIPTOR, *PXEX_DATA_DESCRIPTOR;

typedef struct _XEX_COMPRESSED_DATA_DESCRIPTOR {
    //
    // The size of the compression window.
    //
    ULONG                   WindowSize;

    //
    // The descriptor of the first data block.
    //
    XEX_DATA_DESCRIPTOR     FirstDescriptor;
} XEX_COMPRESSED_DATA_DESCRIPTOR, *PXEX_COMPRESSED_DATA_DESCRIPTOR;

#define XEX_DEFAULT_COMPRESSION_WINDOW      0x8000

typedef struct _XEX_FILE_DATA_DESCRIPTOR {
    //
    // The size of this header.
    //
    ULONG       Size;

    //
    // Data flags.
    //
    USHORT      Flags;

    //
    // The format of data in this image.
    //
    USHORT      Format;

    //
    // Format-specific data follows this header.
    //
} XEX_FILE_DATA_DESCRIPTOR, *PXEX_FILE_DATA_DESCRIPTOR;

#define XEX_DATA_FLAG_ENCRYPTED             0x0001

#define XEX_DATA_FORMAT_NONE                0x0000
#define XEX_DATA_FORMAT_RAW                 0x0001
#define XEX_DATA_FORMAT_COMPRESSED          0x0002
#define XEX_DATA_FORMAT_DELTA_COMPRESSED    0x0003

#define XEX_FILE_DATA_DESCRIPTOR_HEADER \
    XEX_HEADER_SIZEDSTRUCT(3)

//
// Patch files identify the base file they're patching by including the
// hash of the base file headers.
//
#define XEX_PATCH_FILE_BASE_REFERENCE \
    XEX_HEADER_FIXED_SIZE(4, 20)

//
// Delta patch files include the following header.
//
typedef struct _XEX_DELTA_PATCH_DESCRIPTOR {
    //
    // The size of this header.
    //
    ULONG       Size;

    //
    // The version of the target file.
    //
    ULONG       TargetVersion;

    //
    // The version of the source file.
    //
    ULONG       SourceVersion;

    //
    // The hash of HV_IMAGE_INFO.Signature[] of the source file.
    //
    UCHAR       DigestSource[20];

    //
    // The deobfuscated ImageKey of the source file encrypted with the
    // deobfuscated ImageKey of the target file.
    //
    UCHAR       ImageKeySource[16];

    //
    // The size of the XEX headers of the target file.
    //
    ULONG       SizeOfTargetHeaders;

    //
    // The offset into the source XEX headers to copy into the target
    // headers buffer before delta decompression begins.
    //
    ULONG       DeltaHeadersSourceOffset;

    //
    // The size of the source XEX headers starting at the above offset
    // to copy into the target headers buffer before delta decompression
    // begins.
    //
    ULONG       DeltaHeadersSourceSize;

    //
    // The offet into the target XEX headers buffer to copy the source 
    // headers range given above before delta decompression begins.
    //
    ULONG       DeltaHeadersTargetOffset;

    //
    // The offset into the source image to copy into the target image
    // buffer before delta decompression begins.
    //
    ULONG       DeltaImageSourceOffset;

    //
    // The size of the source image starting at the above offset to copy
    // into the target image buffer before delta decompression begins.
    //
    ULONG       DeltaImageSourceSize;

    //
    // The offset into the target image buffer to copy the source image
    // range given above before delta decompression begins.
    //
    ULONG       DeltaImageTargetOffset;

    //
    // Following this header is a series of LZX_DELTA_CHUNK structures
    // that describe the transformation of the source file headers into
    // the target file headers.
    //
} XEX_DELTA_PATCH_DESCRIPTOR, * PXEX_DELTA_PATCH_DESCRIPTOR;

#define XEX_HEADER_DELTA_PATCH_DESCRIPTOR \
    XEX_HEADER_SIZEDSTRUCT(5)

//
// The bound pathname of this image, if it can run from only one location.
//
#define XEX_HEADER_BOUND_PATH \
    XEX_HEADER_STRING(0x0080)

//
// The original base address of this image, if different from the load
// address.
//
#define XEX_HEADER_ORIGINAL_BASE_ADDRESS \
    XEX_HEADER_ULONG(0x0100)

//
// The entry point of this image.
//
#define XEX_HEADER_ENTRY_POINT \
    XEX_HEADER_FLAG(0x0101)

//
// The base of the PE image.
//
#define XEX_HEADER_PE_BASE \
    XEX_HEADER_ULONG(0x0102)

//
// A single table of imports.
//

#define XEX_HEADER_IMPORTS \
    XEX_HEADER_SIZEDSTRUCT(0x0103)

//
// The address of the PE export table.
//
#define XEX_HEADER_PE_EXPORTS \
    XEX_HEADER_STRUCT(0xE104, IMAGE_DATA_DIRECTORY)

//
// Image information for debugging.
//
typedef struct _XEX_VITAL_STATS {
    ULONG CheckSum;
    ULONG TimeDateStamp;
} XEX_VITAL_STATS, *PXEX_VITAL_STATS;

#define XEX_HEADER_VITAL_STATS \
    XEX_HEADER_STRUCT(0x0180, XEX_VITAL_STATS)

//
// Callcap import information.
//
typedef struct _XEX_CALLCAP_IMPORTS {
    ULONG BeginFunctionThunkAddress;
    ULONG EndFunctionThunkAddress;
} XEX_CALLCAP_IMPORTS, *PXEX_CALLCAP_IMPORTS;

#define XEX_HEADER_CALLCAP_IMPORTS \
    XEX_HEADER_STRUCT(0x0181, XEX_CALLCAP_IMPORTS)

//
// Fastcap information.
//
#define XEX_HEADER_FASTCAP_ENABLED \
    XEX_HEADER_FLAG(0x0182)

//
// PE Module name
//
#define XEX_HEADER_PE_MODULE_NAME \
    XEX_HEADER_STRING(0x0183)

#if defined(_M_PPCBE)
#pragma bitfield_order(push, lsb_to_msb)
#endif

//
// Define the length of the library name stored in a library version structure.
//

#define XEXIMAGE_LIBRARY_VERSION_NAME_LENGTH    8

//
// Define the structure of a XBE library version descriptor.
//

typedef struct _XEXIMAGE_LIBRARY_VERSION {

    //
    // Specifies ASCII text padded with nulls to identify the library.
    //
    UCHAR LibraryName[XEXIMAGE_LIBRARY_VERSION_NAME_LENGTH];

    //
    // Specifies the major version number of the library.
    //
    USHORT MajorVersion;

    //
    // Specifies the minor version number of the library.
    //
    USHORT MinorVersion;

    //
    // Specifies the build version number of the library.
    //
    USHORT BuildVersion;

    //
    // Specifies the QFE version number of the library.
    //
    USHORT QFEVersion : 8;

    //
    // The QFEVersion was 13 bits. Lets leach it down to 8 bits and leave ourselves some more bits for flags.
    //
    USHORT Unused : 4;

#if 0 // Features are unsupported for now.
    //
    // Specifies whether this is actually a feature and not a library
    //
    USHORT LibFeature : 1;
#endif

    //
    // Specifies whether this version stamp pertains to the module itself.
    //
    USHORT XEXVersion : 1;

    //
    // Specifies the approved status of this library
    // 0 = unapproved
    // 1 = conditionally approved
    // 2 = approved
    USHORT ApprovedLibrary : 2;

    //
    // Specifies TRUE if this is a debug build of the library, else FALSE.
    //
    USHORT DebugBuild : 1;

} XEXIMAGE_LIBRARY_VERSION, *PXEXIMAGE_LIBRARY_VERSION;

// People tend to initialize the raw bits of the XEXIMAGE_LIBRARY_VERSION struct.
// Here are some helpfull defines for doing that.
#define LIBVER_DEBUG_BIT        0x8000
#define LIBVER_APPROVED_BIT     0x4000
#define LIBVER_CONDITIONAL_BIT  0x2000
#define LIBVER_XBEVERSION_BIT   0x1000
#define LIBVER_FEATURE_BIT      0x0800
#define LIBVER_UNUSED_BITS      0x0700
#define LIBVER_QFEVERSION_BITS  0x00FF

#if defined(_M_PPCBE)
#pragma bitfield_order(pop)
#endif

//
// The build version table.
//
#define XEX_HEADER_BUILD_VERSIONS \
    XEX_HEADER_SIZEDSTRUCT(0x0200)

//
// A descriptor for static TLS data.
//
typedef struct _XEX_TLS_DATA {
    ULONG TlsSlotCount;
    PVOID AddressOfRawData;
    ULONG SizeOfRawData;
    ULONG SizeOfTlsData;
} XEX_TLS_DATA, *PXEX_TLS_DATA;

#define XEX_HEADER_TLS_DATA \
    XEX_HEADER_STRUCT(0x201, XEX_TLS_DATA)

//
// The default stack size for threads created in this process.
//
#define XEX_HEADER_STACK_SIZE \
    XEX_HEADER_FLAG(0x0202)

//
// The default filesystem cache size.
//
#define XEX_HEADER_FSCACHE_SIZE \
    XEX_HEADER_ULONG(0x203)

//
// Size of the initial XAPI heap
//
#define XEX_HEADER_XAPI_HEAP_SIZE \
    XEX_HEADER_ULONG(0x0204)

//
// Executable privilege settings.  Settings are numbered from 0 through
// 1024, where the high 5 bits indicate which header field in the range
// 0x300 through 0x31F contains the privilege bit and the low 5 bits indicate
// which bit of the header field contains the privilege bit.
//


//
// This flag allows a title to control whether the system forcibly reboots the
// running title when certain events happen (such as tray ejection, etc.).  The
// title may be required to do some notification handling if this privilege is
// specified.
//

#define XEX_PRIVILEGE_NO_FORCE_REBOOT                   0

//
// Allow the system to create foreground tasks on behalf of the title.
//

#define XEX_PRIVILEGE_FOREGROUND_TASKS                  1

//
// Do not create a mapping to the optical disc drive.  Note that, if the title
// lives on a disc in the drive, the title's D:\ and GAME:\ mappings will still
// be created to point at the root of the optical media, but the CdRom0:\
// mapping will not be created.
//

#define XEX_PRIVILEGE_NO_ODD_MAPPING                    2

//
// Indicates that the title is capable of handling MCE button press on remote
// control and that system should not have special processing for it.
//

#define XEX_PRIVILEGE_HANDLE_MCE_INPUT                  3

//
// This privilege restricts the use of the Xbox 360 Guide (HUD).  When this
// privilege is specified, the main menu of the guide will display a message
// saying it is disabled.  Any extra user functionality such as voice chats
// will also be disabled.
//

#define XEX_PRIVILEGE_RESTRICT_HUD_FEATURES             4

//
// Indicates that a title handles controller disconnections by displaying a
// message to the user directing him to reconnect it.
//

#define XEX_PRIVILEGE_HANDLE_GAMEPAD_DISCONNECT         5

//
// This privilege allows titles to create insecure sockets that do not use
// the XSP networking protocol wrapper.
//

#define XEX_PRIVILEGE_INSECURE_SOCKETS                  6

//
// This privilege configures XNet to allow interoperability with the original
// Xbox's XSP networking protocol.
//

#define XEX_PRIVILEGE_XBOX_1_XSP_INTEROP                7

//
// This privilege indicates that the title is allowed to set dash context
// information which can modify the way Guide (HUD) behaves in some cases.
//

#define XEX_PRIVILEGE_SET_DASH_CONTEXT                  8

//
// This privilege indicates to the Guide (HUD) that the title exposes a game
// voice channel, which should be shown to the user when appropriate (e.g. in
// QuickChat).
//

#define XEX_PRIVILEGE_TITLE_USES_GAME_VOICE_CHANNEL     9

//
// This privilege indicates that the title does not support PAL50
//

#define XEX_PRIVILEGE_TITLE_PAL50_INCOMPATIBLE         10

//
// This privilege indicates that the title can use an insecured utitilty cache
// partition (i.e. XMountUtitliyDrive will mount the cache partition using FATX
// instead of STFS).
//

#define XEX_PRIVILEGE_TITLE_INSECURE_UTILITYDRIVE      11

#define XEX_HEADER_EXECUTION_ID \
    XEX_HEADER_STRUCT(0x400, XEX_EXECUTION_ID)

//
// Array of custom Live service IDs to request
//
typedef struct _XEX_SERVICE_ID_LIST {
    ULONG Size;
    ULONG CustomServiceIDs[4];
} XEX_SERVICE_ID_LIST, *PXEX_SERVICE_ID_LIST;

#define XEX_HEADER_SERVICE_ID_LIST \
    XEX_HEADER_SIZEDSTRUCT(0x401)

//
// Size of the title workspace area.
//
#define XEX_HEADER_WORKSPACE_SIZE \
    XEX_HEADER_ULONG(0x0402)

//
// Game rating by region
//
#define XEX_NUMBER_GAME_RATING_SYSTEMS          64

#define XEX_HEADER_GAME_RATINGS \
    XEX_HEADER_FIXED_SIZE(0x403, XEX_NUMBER_GAME_RATING_SYSTEMS)

//
// System Link LAN key
//
#define XEX_LAN_KEY_SIZE                        16

#define XEX_HEADER_LAN_KEY \
    XEX_HEADER_FIXED_SIZE(0x404, XEX_LAN_KEY_SIZE)

//
// MS logo information.
//
#define XEX_HEADER_MSLOGO \
    XEX_HEADER_SIZEDSTRUCT(0x0405)

#pragma warning(pop)

#endif // _XEX_H_
