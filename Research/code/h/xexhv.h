/*++

Copyright (c) 2000-2005  Microsoft Corporation

Module Name:

    xexhv.h

Abstract:

    This module defines the structures of the Xenon Executable (XEX)
    format that are used by the hypervisor.

--*/

#ifndef _XEXHV_H_
#define _XEXHV_H_

//
// Define the root security information of an executable image.
//

typedef struct _HV_IMAGE_INFO {
    //
    // The signature of this object.
    //
    UCHAR       Signature[256];

    //
    // The size of this object.
    //
    ULONG       InfoSize;

    //
    // Flags describing this image.
    //
    ULONG       ImageFlags;

    //
    // Specifies the address at which this module is to be loaded.
    //
    ULONG       LoadAddress;

    //
    // The hash of the image's first page descriptor.
    //
    UCHAR       ImageHash[20];

    //
    // The number of import tables for this image.
    //
    ULONG       ImportTableCount;

    //
    // The digest of the first import table.
    //
    UCHAR       ImportDigest[20];

    //
    // Specifies the media identifier for this image.  This must immediately
    // follow the import/export information.
    //
    UCHAR       MediaID[16];

    //
    // Specifies the key used to encrypt this image.
    //
    UCHAR       ImageKey[16];

    //
    // The address of this image's export table, if any.
    //
    ULONG       ExportTableAddress;

    //
    // The hash of the header information.
    //
    UCHAR       HeaderHash[20];

    //
    // Game regions in which this image is allowed to run.
    //
    ULONG       GameRegion;
} HV_IMAGE_INFO, *PHV_IMAGE_INFO;

#define XEX_SECURITY_FLAG_MFG_MODE          0x00000006
#define XEX_SECURITY_FLAG_MFG_UTIL          0x00000002 // runs in verified mfg mode
#define XEX_SECURITY_FLAG_MFG_SUPPORT       0x00000004 // runs in all mfg modes
#define XEX_SECURITY_FLAG_MFG_AWARE         0x00000006 // runs in all modes
#define XEX_SECURITY_FLAG_XGD2_MEDIA        0x00000008
#define XEX_SECURITY_FLAG_HV_PRIVS_MASK     0x000FFF00
#define XEX_SECURITY_FLAG_HV_PRIVS_SHIFT        8
#define XEX_SECURITY_FLAG_SMALL_PAGES       0x10000000
#define XEX_SECURITY_FLAG_NO_REGION         0x20000000
#define XEX_SECURITY_FLAG_REVOCABLE         0x40000000
#define XEX_SECURITY_FLAG_REQUIRE_COOKIE    0x80000000

#define XEX_HV_PRIVILEGE_CARDEA_KEY             0
#define XEX_HV_PRIVILEGE_XEIKA_KEY              1
#define XEX_HV_PRIVILEGE_TITLE_USER_MODE        2
#define XEX_HV_PRIVILEGE_SYSTEM_USER_MODE       3
#define XEX_HV_PRIVILEGE_ORANGE_0               4
#define XEX_HV_PRIVILEGE_ORANGE_1               5
#define XEX_HV_PRIVILEGE_ORANGE_2               6

//
// Define a page descriptor for image data.
//

typedef struct _HV_PAGE_INFO {
    //
    // Information describing the page range.  The high 3 bits describe the
    // page access policy, and the low 29 bits are the number of pages over
    // which to apply it.
    //
    ULONG       PageDescription;

    //
    // The digest of the next range's page descriptor plus the next range's
    // data.
    //
    UCHAR       DataDigest[20];
} HV_PAGE_INFO, *PHV_PAGE_INFO;

#define XEX_SECURITY_PAGE_COUNT_SHIFT   4
#define XEX_SECURITY_PAGE_PROTECT_MASK  0x0000000F
#define XEX_SECURITY_PAGE_ENCRYPT       0x00000008
#define XEX_SECURITY_PAGE_PROTECT       0x00000004
#define XEX_SECURITY_PAGE_NOEXECUTE     0x00000002
#define XEX_SECURITY_PAGE_NOWRITE       0x00000001
#define XEX_SECURITY_PAGE_CODE \
    (XEX_SECURITY_PAGE_NOWRITE)
#define XEX_SECURITY_PAGE_READONLY \
    (XEX_SECURITY_PAGE_NOEXECUTE | XEX_SECURITY_PAGE_NOWRITE)
#define XEX_SECURITY_PAGE_READWRITE \
    (XEX_SECURITY_PAGE_NOEXECUTE)

//
// Define the header for image exports.
//

typedef struct _HV_IMAGE_EXPORT_TABLE {
    ULONG Magic[3];
    ULONG ModuleNumber[2];
    ULONG Version[3];
    ULONG ImageBaseAddress;
    ULONG Count;
    ULONG Base;
} HV_IMAGE_EXPORT_TABLE, *PHV_IMAGE_EXPORT_TABLE;

#define XEX_EXPORT_MAGIC_0      0x48000000
#define XEX_EXPORT_MAGIC_1      0x00485645
#define XEX_EXPORT_MAGIC_2      0x48000000

#endif // _XEXHV_H_
