/************************************************************************
*                                                                       *
*   xamcache.h -- This module defines the XAM cache API                 *
*                                                                       *
*   Copyright (c) Microsoft Corp. All rights reserved.                  *
*                                                                       *
************************************************************************/

#ifndef __XAMCACHE_H__
#define __XAMCACHE_H__


#ifdef __cplusplus
extern "C" {
#endif


typedef enum _XAM_CACHE_FILE_TYPE
{
    XAM_CACHE_ALL,                      // special invalid cache type used to signify all cache types
    XAM_CACHE_GAME_TILE,                // Single tile, dwIdentifier = dwTitleId, qwIdentifier = qwImageId
    XAM_CACHE_ACHIEVEMENT_TILE,         // Single tile, dwIdentifier = dwTitleId, qwIdentifier = qwImageId
    XAM_CACHE_GAMER_TILE,               // Single tile, dwIdentifier = dwTitleId, qwIdentifier = qwImageId
    XAM_CACHE_GAMER_TILE_SMALL,         // Single tile, dwIdentifier = dwTitleId, qwIdentifier = qwImageId
    XAM_CACHE_CUSTOM_GAMER_TILE,        // dwIdentifier = <unused>, qwIdentifier = qwUserId that owns tile
    XAM_CACHE_CUSTOM_GAMER_TILE_SMALL,  // dwIdentifier = <unused>, qwIdentifier = qwUserId that owns tile
    XAM_CACHE_FRIEND_MUTE_LIST,         // dwIdentifier = <unused>, qwIdentifier = qwUserId that owns list
    XAM_CACHE_TICKETS,                  // dwIdentifier = <unused>, qwIdentifier = qwUserId that owns tickets
    XAM_CACHE_TITLE_NAMES,              // dwIdentifier = <unused>, qwIdentifier = <unused>
    XAM_CACHE_RECENT_PLAYERS,           // dwIdentifier = <unused>, qwIdentifier = qwUserId that owns list
    XAM_CACHE_TITLE_UPDATE,             // dwIdentifier = dwTitleId, qwIdentifier = dwTitleBaseVersion << 32 | dwCurrentSystemVersion
    XAM_CACHE_SYSTEM_UPDATE,            // dwIdentifier = dwTitleId, qwIdentifier = dwBaseVersion << 32 | dwCurrentSystemVersion
    XAM_CACHE_DASHBOARD_APP,            // dwIdentifier = dwTitleId of App
    XAM_CACHE_SPA_FILE,                 // dwIdentifier = dwTitleId,qwIdentifier = edition
    XAM_CACHE_GAME_INVITE,              // dwIdentifier = <unused>, qwIdentifier = <unused>
    XAM_CACHE_GAMER_TAG                 // dwIdentifier = <unused>, qwIdentifier = <unused>
} XAM_CACHE_FILE_TYPE;

// XamCacheStoreFile and XamCacheFetchFile are APIs for
// simple synchronous access.

XBOXAPI
DWORD
WINAPI
XamCacheStoreFile(
    IN      XAM_CACHE_FILE_TYPE         FileType,
    IN      DWORD                       dwIdentifier,
    IN      ULONGLONG                   qwIdentifier,
    IN      ULONGLONG                   qwVersion,
    IN      PVOID                       pvBuffer,
    IN      DWORD                       cbBuffer
    );

XBOXAPI
DWORD
WINAPI
XamCacheFetchFile(
    IN      XAM_CACHE_FILE_TYPE         FileType,
    IN      DWORD                       dwIdentifier,
    IN      ULONGLONG                   qwIdentifier,
    OUT     ULONGLONG*                  pqwVersion,
    OUT     PVOID                       pvBuffer,
    IN OUT  PDWORD                      pcbBuffer
    );

XBOXAPI
DWORD
WINAPI
XamCacheDeleteFile(
    IN      XAM_CACHE_FILE_TYPE         FileType,
    IN      DWORD                       dwIdentifier,
    IN      ULONGLONG                   qwIdentifier
    );


#define XAM_COF_FETCH                   0x0000
#define XAM_COF_STORE                   0x0001
#define XAM_COF_STORE_RESUME            0x0003              // XAM_COF_STORE + supports resume
#define XAM_COF_GET_PATH_ONLY           0x1000              // XamCacheOpenFile does not open file - provides path
#define XAM_COF_NO_LOCK                 0x2000              // valid only with XAM_COF_FETCH and XAM_COF_GET_PATH_ONLY
                                                            // does not lock file in cache


typedef struct _XAM_CACHE_OPEN_FILE     *PXAM_CACHE_OPEN_FILE;

typedef void (*PFNONCACHEDEVICEREMOVED)(PXAM_CACHE_OPEN_FILE CacheFile);

typedef struct _XAM_CACHE_OPEN_FILE
{
    //
    // Caller must fill out before calling XamCacheOpenFile
    //

    DWORD                               Flags;
    XAM_CACHE_FILE_TYPE                 FileType;
    DWORD                               dwIdentifier;
    ULONGLONG                           qwIdentifier;

    //
    // XAM_COF_FETCH - caller must fill out before calling XamCacheOpenFile
    // XAM_COF_STORE - filled out by XamCacheOpenFile
    //

    ULONGLONG                           qwVersion;
    DWORD                               cbSize;

    //
    // Filled out by XamCacheOpenFile
    //

    HANDLE                              hFile;
    char                                FilePath[MAX_PATH];

    //
    // Notification
    //

    PFNONCACHEDEVICEREMOVED             OnCacheDeviceRemoved    OPTIONAL;
    ULONG_PTR                           Context;

    //
    // Internal use only
    //

    ULONG_PTR                           Reserved[2];
    PVOID                               pvMountedPackage;
    CHAR                                PackageFilePath[MAX_PATH];
} XAM_CACHE_OPEN_FILE;

XBOXAPI
DWORD
WINAPI
XamCacheOpenFile(
    IN OUT  PXAM_CACHE_OPEN_FILE        pCacheOpenFile
    );

XBOXAPI
DWORD
WINAPI
XamCacheRenameFile(
    IN      PXAM_CACHE_OPEN_FILE        pCacheOpenFile,
    IN      DWORD                       dwIdentifier,
    IN      ULONGLONG                   qwIdentifier,
    IN      ULONGLONG                   qwVersion
    );

XBOXAPI
VOID
WINAPI
XamCacheCloseFile(
    IN      PXAM_CACHE_OPEN_FILE        pCacheOpenFile,
    IN      BOOL                        fDelete
    );

XBOXAPI
BOOL
WINAPI
XamCacheReset(
    IN      XAM_CACHE_FILE_TYPE         FileType
    );


#ifdef __cplusplus
}
#endif


#endif // __XAMCACHE_H__

