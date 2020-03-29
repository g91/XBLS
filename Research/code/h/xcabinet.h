// ---------------------------------------------------------------------------------------
// xcabinet.h
//
// Copyright (C) Microsoft Corporation
// ---------------------------------------------------------------------------------------

#ifndef __XCABINET_H__
#define __XCABINET_H__

// ---------------------------------------------------------------------------------------
// Includes
// ---------------------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif

#include "xecrypt.h"
#include "cabinet.h"

#ifdef __cplusplus
}
#endif

#pragma pack(push, 1)


// ---------------------------------------------------------------------------------------

//
// Define the real RC4 SHA1 structures and functions
//
#define RC4_CONFOUNDER_LEN  8

typedef struct _RC4_SHA_HEADER {
    BYTE Checksum[XECRYPT_SHA_DIGEST_SIZE];
    BYTE Confounder[RC4_CONFOUNDER_LEN];
} RC4_SHA_HEADER, *PRC4_SHA_HEADER;

//
// Define a structure that describes an extended CFFOLDER entry
// that also has an associated HMAC (per-folder reserved data)
//
typedef struct
{
    CFFOLDER            cffolder;      // CFFOLDER
    RC4_SHA_HEADER      hmac;          // RC4 SHA1 Hmac

} CFFOLDER_HMAC, *PCFFOLDER_HMAC;

//
// Define a union of all known CAB flags
//
#define cfhdrFLAGS_ALL    (cfhdrPREV_CABINET | \
                         cfhdrNEXT_CABINET | \
                         cfhdrRESERVE_PRESENT)

//
// Define our header cache structure
//
typedef struct 
{
    CFHEADER            cfheader;       // Cabinet file header
    CFRESERVE           cfreserve;      // Reserved data specification
    
    RC4_SHA_HEADER      digestFolders;  // CFFOLDERS digest
    RC4_SHA_HEADER      digestFiles;    // CFFILES digest
    
} XONLINECONTENT_HEADER, *PXONLINECONTENT_HEADER;

//
// Define sizes related to the fixed header
//
#define XONLINECONTENT_FIXED_HEADER_SIZE    \
            (sizeof(XONLINECONTENT_HEADER))

#define XONLINECONTENT_FIXED_HEADER_SIZE_WITH_HMAC    \
            (XONLINECONTENT_FIXED_HEADER_SIZE + \
             sizeof(RC4_SHA_HEADER))

#define XONLINECONTENT_FIXED_HEADER_SIZE_WITH_HMAC_AND_CHECKPOINT    \
            (XONLINECONTENT_FIXED_HEADER_SIZE + \
             sizeof(RC4_SHA_HEADER) + sizeof(DWORD))

#define XONLINECONTENT_COMPLETE_HEADER_SIZE    \
            (XONLINECONTENT_FIXED_HEADER_SIZE_WITH_HMAC_AND_CHECKPOINT + \
             XONLINECONTENT_PK_SIGNATURE_SIZE)

#define XONLINECONTENT_CHECKPOINT    \
            (XONLINECONTENT_FIXED_HEADER_SIZE + \
             sizeof(RC4_SHA_HEADER))

//
// Define the maximum number of CFFOLDER entries allowed in a content package.
//
#define XONLINECONTENT_MAX_CFFOLDER             ((DWORD)100)

//
// Define a threshold size for the minimum folder size to justify the
// additional folder overhead.
//
#define XONLINECONTENT_MIN_FOLDER_SIZE          ((DWORD)(5 * 1024)) // 5KB

//
// Define the "attribute" flag to indicate that the current folder is a
// continuation from  the same file in the previous folder.
//
#define XONLINECONTENT_FOLDER_CONTINUATION      ((WORD)0x8000)

//
// Define the minimum size for a CFFILE entry (+ 2 == one character name + NULL
// terminator).
//
#define XONLINECONTENT_MIN_CFFILE_SIZE          ((DWORD)(sizeof(CFFILE) + 2))

//
// Define the maximum number of CFFILE entries allowed in a content package.
//
#define XONLINECONTENT_MAX_CFFILE               ((DWORD)1000000)
C_ASSERT(XONLINECONTENT_MAX_CFFILE <= (0xFFFFFFFF / XONLINECONTENT_MIN_CFFILE_SIZE));

//
// Define the size of a PK signature.
//
#define XONLINECONTENT_PK_SIGNATURE_SIZE        256

#ifndef BSAFE_PUB_KEY

//
// BUGBUG:
//
// BSAFE_PUB_KEY not defined in XeCrypt yet, so we define it here
//
typedef struct {
    DWORD       magic;                  /* Should always be RSA1 */
    DWORD       keylen;                 // size of modulus buffer
    DWORD       bitlen;                 // # of bits in modulus
    DWORD       datalen;                // max number of bytes to be encoded
    DWORD       pubexp;                 //public exponent
} BSAFE_PUB_KEY, FAR *LPBSAFE_PUB_KEY;

#endif

//
// Define the max size of a public key
//
#define XONLINECONTENT_MAX_PUBLIC_KEY_SIZE    \
        (XONLINECONTENT_PK_SIGNATURE_SIZE + \
         sizeof(BSAFE_PUB_KEY) + \
         (sizeof(DWORD) * 4))


//
// Define the various reserve values
//
#define XONLINECONTENT_HEADER_RESERVE_SIZE    \
            ((sizeof(RC4_SHA_HEADER) * 3) + sizeof(DWORD) + \
             XONLINECONTENT_PK_SIGNATURE_SIZE)

#define XONLINECONTENT_PERFOLDER_RESERVE_SIZE    \
            (sizeof(RC4_SHA_HEADER))

//
// Define the smallest possible size for a content package
//
#define XONLINECONTENT_MIN_CONTENT_SIZE    \
            (sizeof(CFHEADER) + sizeof(CFRESERVE) + \
             XONLINECONTENT_HEADER_RESERVE_SIZE)

//
// Define a confounder for the version stamp
//
#define XONLINECONTENT_CHECKPOINT_CONFOUNDER        ((DWORD)0x5aef320b)

//
// Define the prefix for files with special installation meaning
//
#define XINSTALLER_SPECIAL_NAME_PREFIX              "$install_"

//
// Define the fixed name of the package within the CAB
//
#define XINSTALLER_PACKAGE_FILE_NAME                "$package"

//
// Define the installation extender prefix and suffix
//
#define XINSTALLER_EXTENDER_FILE_NAME_PREFIX        XINSTALLER_SPECIAL_NAME_PREFIX
#define XINSTALLER_EXTENDER_FILE_NAME_SUFFIX        ".xex"

//
// We deal with clusters a lot, so define the size of a cluster
//
#define XBOX_CLUSTER_SIZE                           (1 << 14)


// ---------------------------------------------------------------------------------------

typedef enum _XONLINECONTENT_RESUME_STATE
{
    XONLINECONTENT_RESUME_STATE_FILE_HEADERS_NOT_READY      = 'FILH',
    XONLINECONTENT_RESUME_STATE_NEW_FOLDER                  = 'FOLD',
    XONLINECONTENT_RESUME_STATE_NEW_FOLDER_RESUME_ATTEMPT_2 = 'FOL2',
    XONLINECONTENT_RESUME_STATE_NEW_FOLDER_RESUME_ATTEMPT_3 = 'FOL3',
} XONLINECONTENT_RESUME_STATE;

typedef struct _XONLINECONTENT_RESUME_HEADER {

    //
    // Resume state identifier.
    //
    XONLINECONTENT_RESUME_STATE     ResumeState; 

    //
    // Index of current file being downloaded/processed.
    //
    DWORD                           dwCurrentFileIndex;

    //
    // Offset into current file being downloaded/processed.
    //
    LARGE_INTEGER                   liCurrentFileOffset;

    //
    // Number of bytes successfully downloaded/processed.
    //
    LARGE_INTEGER                   liBytesProcessed;

    //
    // Last-modified timestamp for resuming download/processing.
    //
    LARGE_INTEGER                   liLastModified;
} XONLINECONTENT_RESUME_HEADER;

#define XONLINECONTENT_MAX_SINGLE_FILE_RESUME_DATA_SIZE     \
            (XONLINECONTENT_COMPLETE_HEADER_SIZE + \
             (XONLINECONTENT_MAX_CFFOLDER * sizeof(CFFOLDER_HMAC)) + \
             (XONLINECONTENT_MAX_CFFOLDER * sizeof(CFFILE)))



// ---------------------------------------------------------------------------------------


//
// Content delivery
//

//
// The CFFILE structure has a WORD field for the file time which
// we will hijack for our special flags. Xbox content will use thie
// field to indicate special options instead of the file time.
// The following bits are defined for the time field, and honored
// by the content installation API.
//

// This flag indicates that the file should be copied to the
// user partition rather than the title area
#define XONLINECONTENT_A_USER_DATA              (0x0001)

// This flag indicates that this file is a continuation of
// a file in the previous folder. The data in this file should
// be appended to the previous file. This file must be the first
// file in the folder.
#define XONLINECONTENT_A_CONTINUED_FROM_PREV    (0x0002)

// This flag indicates that this file will be continued into the
// next folder. The data in the next folder should be appended to
// this file. This file must be the last file in the folder.
#define XONLINECONTENT_A_CONTINUED_INTO_NEXT    (0x0004)

//
// Define the size of the download buffer. This cannot be
// less than XONLINECONTENT_LZX_OUTPUT_SIZE
//
#define XONLINECONTENT_DL_BUFFER_SIZE           (1024 * 64)

//
// Define the LZX decoder history window size, this should be no
// less than 32k (ROM decompressor uses 128k)
//
#define XONLINECONTENT_LZX_WINDOW_SIZE          CHUNK_SIZE

//
// Define the output buffer for decompress. This must not be
// less than 32k
//#define XONLINECONTENT_LZX_OUTPUT_SIZE    \
//            ((CHUNK_SIZE) + XBOX_HD_SECTOR_SIZE)
#define XONLINECONTENT_LZX_OUTPUT_SIZE    \
            (CHUNK_SIZE)



//
// TODO: From \public\i386\sdk\inc\fdi.h.  Need byte reversal?
//

/***    tcompXXX - Diamond compression types
 *
 *  These are passed to FCIAddFile(), and are also stored in the CFFOLDER
 *  structures in cabinet files.
 *
 *  NOTE: We reserve bits for the TYPE, QUANTUM_LEVEL, and QUANTUM_MEM
 *        to provide room for future expansion.  Since this value is stored
 *        in the CFDATA records in the cabinet file, we don't want to
 *        have to change the format for existing compression configurations
 *        if we add new ones in the future.  This will allows us to read
 *        old cabinet files in the future.
 */

typedef unsigned short TCOMP; /* tcomp */

#define tcompMASK_TYPE          0x000F  // Mask for compression type
#define tcompTYPE_NONE          0x0000  // No compression
#define tcompTYPE_MSZIP         0x0001  // MSZIP
#define tcompTYPE_QUANTUM       0x0002  // Quantum
#define tcompTYPE_LZX           0x0003  // LZX
#define tcompBAD                0x000F  // Unspecified compression type

#define tcompMASK_LZX_WINDOW    0x1F00  // Mask for LZX Compression Memory
#define tcompLZX_WINDOW_LO      0x0F00  // Lowest LZX Memory (15)
#define tcompLZX_WINDOW_HI      0x1500  // Highest LZX Memory (21)
#define tcompSHIFT_LZX_WINDOW        8  // Amount to shift over to get int

#define tcompMASK_QUANTUM_LEVEL 0x00F0  // Mask for Quantum Compression Level
#define tcompQUANTUM_LEVEL_LO   0x0010  // Lowest Quantum Level (1)
#define tcompQUANTUM_LEVEL_HI   0x0070  // Highest Quantum Level (7)
#define tcompSHIFT_QUANTUM_LEVEL     4  // Amount to shift over to get int

#define tcompMASK_QUANTUM_MEM   0x1F00  // Mask for Quantum Compression Memory
#define tcompQUANTUM_MEM_LO     0x0A00  // Lowest Quantum Memory (10)
#define tcompQUANTUM_MEM_HI     0x1500  // Highest Quantum Memory (21)
#define tcompSHIFT_QUANTUM_MEM       8  // Amount to shift over to get int

#define tcompMASK_RESERVED      0xE000  // Reserved bits (high 3 bits)

#define CompressionTypeFromTCOMP(tc) \
            ((tc) & tcompMASK_TYPE)

#define CompressionLevelFromTCOMP(tc) \
            (((tc) & tcompMASK_QUANTUM_LEVEL) >> tcompSHIFT_QUANTUM_LEVEL)

#define CompressionMemoryFromTCOMP(tc) \
            (((tc) & tcompMASK_QUANTUM_MEM) >> tcompSHIFT_QUANTUM_MEM)

#define TCOMPfromTypeLevelMemory(t,l,m)           \
            (((m) << tcompSHIFT_QUANTUM_MEM  ) |  \
             ((l) << tcompSHIFT_QUANTUM_LEVEL) |  \
             ( t                             ))

#define LZXCompressionWindowFromTCOMP(tc) \
            (((tc) & tcompMASK_LZX_WINDOW) >> tcompSHIFT_LZX_WINDOW)

#define TCOMPfromLZXWindow(w)      \
            (((w) << tcompSHIFT_LZX_WINDOW ) |  \
             ( tcompTYPE_LZX ))


#pragma pack(pop)

#endif // ! defined __XCABINET_H__

