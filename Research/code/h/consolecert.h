/************************************************************************
*                                                                       *
*   consolecert.h -- Xenon Console Certificate Definition               *
*                                                                       *
*   Copyright (c) Microsoft Corp. All rights reserved.                  *
*                                                                       *
************************************************************************/

#ifndef _CONSOLECERT_H_
#define _CONSOLECERT_H_


#define CONSOLE_PUBLIC_KEY_EXPONENT_SIZE    4
#define CONSOLE_PUBLIC_KEY_MODULUS_SIZE     128
#define CONSOLE_ID_SIZE                     5
#define CONSOLE_CERT_PART_NUMBER_SIZE       11
#define CONSOLE_CERTIFICATE_RESERVED_SIZE   6
#define CONSOLE_CERTIFICATE_HASH_SIZE       20
#define CONSOLE_CERTIFICATE_SIGNATURE_SIZE  256

#pragma pack(push, 1)

typedef struct _CONSOLE_PUBLIC_KEY
{
    BYTE                PublicExponent[CONSOLE_PUBLIC_KEY_EXPONENT_SIZE]; // In Big endian
    BYTE                Modulus[CONSOLE_PUBLIC_KEY_MODULUS_SIZE];       // In QWORD Big endian
} CONSOLE_PUBLIC_KEY;

typedef struct _XE_CONSOLE_CERTIFICATE
{
    USHORT              CertSize;                                      // Size of this sturcture (424)
    BYTE                ConsoleId[CONSOLE_ID_SIZE];                    // Uniquely ids console
    BYTE                ConsolePartNumber[CONSOLE_CERT_PART_NUMBER_SIZE];   // Identifies mfg part number
    BYTE                Reserved[CONSOLE_CERTIFICATE_RESERVED_SIZE];   // Reserved for future use
    ULONG               ConsoleType;                                   // States whether console is a retail or dev/test kit
    UINT64              ManufacturingDate;                             // Date of mfg for console
    CONSOLE_PUBLIC_KEY  ConsolePublicKey;                              // Console's Public Key
    BYTE                Signature[CONSOLE_CERTIFICATE_SIGNATURE_SIZE]; // RsaSign(MasterKey.Private, CertSize thru ConsolePublicKey)
} XE_CONSOLE_CERTIFICATE;

typedef struct _XE_CONSOLE_SIGNATURE
{
    XE_CONSOLE_CERTIFICATE  Cert;
    BYTE                    Signature[CONSOLE_PUBLIC_KEY_MODULUS_SIZE];
} XE_CONSOLE_SIGNATURE;

#define XE_CONSOLE_TYPE_MASK                0x00FFFFFF

#define XE_CONSOLE_TYPE_DEVKIT              0x00000001
#define XE_CONSOLE_TYPE_RETAIL              0x00000002

#define XE_CONSOLE_TYPE_TESTKIT             0x40000000
#define XE_CONSOLE_TYPE_TEMPORARY_KEY       0x80000000

#pragma pack(pop)


#endif // _CONSOLECERT_H_
