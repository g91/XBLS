#pragma once

#include <xtl.h>
#include <stdio.h>
#include <xbdm.h>
#include <xkelib.h>
#include <map>
#include <xboxmath.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <xuiapp.h>
#include <xui.h>

using namespace std;

#include "INIReader.h"
#include "rgloader/OffsetManager.h"

#include "struct/XKE.h"
#include "struct/XOSC.h"

#include "Tools/Utilities.h"
#include "Tools/HvxCalls.h"
#include "Tools/KVGuard.h"

#include "Hooks/GameHooks.h"
#include "Hooks/System.h"

#include "Network/Network.h"
#include "Network/socket.h"

#include "patching.h"
#include "XBLAPI.h"
#include <xui.h>

#include "ntstatus.h"

#include "rgloader\xam.h"
#include "rgloader\xshell.h"

//Type defines
typedef unsigned int	uint;

#define BASEADDY		0x90DF0000
//#define MODULE_XOSC		"xosc.xex"
#define MODULE_DASH		"dash.xex"
#define MODULE_XSHELL	"xshell.xex"

/*----------------*/
/*---Structures---*/
struct CConnection
{
	SOCKET	clnts;
	u_long	ip;
	uint	port;
};
/*---Structures---*/
/*----------------*/

namespace global 
{
	extern BOOL isDevkit;
	extern BOOL isAuthed; 
	extern BOOL IsINI;
	extern DWORD supportedVersion;
	extern WCHAR wNotifyMsg[100];
	extern DWORD cryptData[6];
	extern BYTE g_pSessionToken[0x14];
	extern BOOL testA;


	extern PCHAR PATH_KV;
	extern PCHAR PATH_CPU;
	extern PCHAR PATH_XEX;

	namespace seting 
	{
		//
		extern BOOL UseSetDashUI;
		extern BOOL UseSetGold;

		//BYPASS
		extern BOOL UseBYPASSBO2;
		extern BOOL UseBYPASSBO3;
		extern BOOL UseBYPASSGHOSTS;

	}

	namespace DASHRESPONSE
	{
		extern BYTE Color[];
		extern BYTE Background[];
	}

	namespace modules 
	{
		extern HANDLE client;
		extern HANDLE xam;
		extern HANDLE krnl;
		extern HANDLE ModuleHandle;
		extern BYTE ModuleDigest[];
	}
}

//#define InsertHeadList(ListHead,Entry) {\
//    PLIST_ENTRY _EX_Flink;\
//    PLIST_ENTRY _EX_ListHead;\
//    _EX_ListHead = (ListHead);\
//    _EX_Flink = _EX_ListHead->Flink;\
//    (Entry)->Flink = _EX_Flink;\
//    (Entry)->Blink = _EX_ListHead;\
//    _EX_Flink->Blink = (Entry);\
//    _EX_ListHead->Flink = (Entry);\
//    }
//
//#define RemoveEntryList(Entry) {\
//    PLIST_ENTRY _EX_Blink;\
//    PLIST_ENTRY _EX_Flink;\
//    _EX_Flink = (Entry)->Flink;\
//    _EX_Blink = (Entry)->Blink;\
//    _EX_Blink->Flink = _EX_Flink;\
//    _EX_Flink->Blink = _EX_Blink;\
//    }
//
//// IRQL values
//#define PASSIVE_LEVEL 0
//#define LOW_LEVEL 0
//#define APC_LEVEL 1
//#define DISPATCH_LEVEL 2
//
//
//#ifdef __cplusplus
//extern "C" {
//#endif
//	int _cdecl RtlVsnprintf(CHAR* Buffer, int SizeInBytes, const CHAR* Format, va_list va);
//	VOID KeInitializeEvent(PKEVENT Event, DWORD Type, BOOL State);
//	VOID KeResetEvent(HANDLE Event);
//	PIMAGE_NT_HEADERS RtlImageNtHeader(PVOID ModuleAddress);
//	VOID KeSweepIcacheRange(PVOID Address, DWORD cbBytes);
//	VOID MmDbgReleaseAddress(PVOID pAddress, PHANDLE pHandle);
//	PVOID MmDbgReadCheck(PVOID pAddress);
//	NTSTATUS ObTranslateSymbolicLink(IN PVOID, OUT PANSI_STRING);
//
//#ifdef __cplusplus
//}   // extern "C"
//#endif
//
//#define SO_DECRYPTSOCK 0x5801 // Decrypt the socket
//
//#define DMNETWORK 2 // System (Title IP, supports WIFI)
//
//#define accept(s, addr, addrlen)							NetDll_accept(DMNETWORK, s, addr, addrlen)
//#define bind(s, name, namelen)								NetDll_bind(DMNETWORK, s, name, namelen)
//#define connect(s, name, namelen)							NetDll_connect(DMNETWORK, s, name, namelen)
//#define closesocket(s)										NetDll_closesocket(DMNETWORK, s)
//#define getpeername(s, name, namelen)						NetDll_getpeername(DMNETWORK, s, name, namelen)
//#define getsockname(s, name, namelen)						NetDll_getsockname(DMNETWORK, s, name, namelen)
//#define listen(s, backlog)									NetDll_listen(DMNETWORK, s, backlog)
//#define recv(s, buf, len, flags)							NetDll_recv(DMNETWORK, s, buf, len, flags)
//#define recvfrom(s, buf, len, flags, from, fromlen)			NetDll_recvfrom(DMNETWORK, s, buf, len, flags, from, fromlen)
//#define select(nfds, readfds, writefds, exceptfds, timeout)	NetDll_select(DMNETWORK, nfds, readfds, writefds, exceptfds, timeout)
//#define send(s, buf, len, flags)							NetDll_send(DMNETWORK, s, buf, len, flags)
//#define sendto(s, buf, len, flags, to, tolen)				NetDll_sendto(DMNETWORK, s, buf, len, flags, to, tolen)
//#define setsockopt(s, level, optname, optval, optlen)		NetDll_setsockopt(DMNETWORK, s, level, optname, optval, optlen)
//#define shutdown(s, how)									NetDll_shutdown(DMNETWORK, s, how)
//#define socket(af, type, protocol)							NetDll_socket(DMNETWORK, af, type, protocol)
////#define XnpNoteSystemTime()									NetDll_XnpNoteSystemTime(DMNETWORK)
//
//typedef struct _OBJECT_DIRECTORY_INFORMATION {
//	ANSI_STRING Name;
//	DWORD		Type;
//	CHAR		NameEx[MAX_PATH];
//} OBJECT_DIRECTORY_INFORMATION, * POBJECT_DIRECTORY_INFORMATION;
//
//typedef struct _TRANSLATE_SYMLINK
//{
//	DWORD reserved;
//	PANSI_STRING name;
//} TRANSLATE_SYMLINK, * PTRANSLATE_SYMLINK;
//
//typedef struct _FILE_RENAME_INFORMATION {
//	BOOLEAN ReplaceIfExists;
//	HANDLE  RootDirectory;
//	ANSI_STRING FileName;
//} FILE_RENAME_INFORMATION, * PFILE_RENAME_INFORMATION;
//
//
//typedef struct _FILE_DIRECTORY_INFORMATION {
//	ULONG		  NextEntryOffset;
//	ULONG		  FileIndex;
//	LARGE_INTEGER CreationTime;
//	LARGE_INTEGER LastAccessTime;
//	LARGE_INTEGER LastWriteTime;
//	LARGE_INTEGER ChangeTime;
//	LARGE_INTEGER EndOfFile;
//	LARGE_INTEGER AllocationSize;
//	ULONG		  FileAttributes;
//	ULONG		  FileNameLength;
//	CHAR		  FileName[MAX_PATH];
//} FILE_DIRECTORY_INFORMATION, * PFILE_DIRECTORY_INFORMATION;
//
//
//#include "XBDM\dmserv.h"
//#include "XBDM\dmglobals.h"
//#include "XBDM\dmbreak.h"
//#include "XBDM\dmnotify.h"
//#include "XBDM\file.h"
//#include "XBDM\dmexports.h"