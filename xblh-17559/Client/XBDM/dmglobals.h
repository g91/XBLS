/*
 Copyright (c) 2013 Nathan LeRoux
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 */

#ifndef _DMGLOBALS_H
#define _DMGLOBALS_H

#define CONSOLE_COLOR_FLAG_NOSIDECAR 0 // JTAG
#define CONSOLE_COLOR_FLAG_BLACK 1	// DEVKIT
#define CONSOLE_COLOR_FLAG_BLUE 2	// 1GB
#define CONSOLE_COLOR_FLAG_WHITE 4 // TESTKIT

typedef struct _KEXCEPTION_FRAME
{
	DWORD Status; // 0
	DWORD Unk; // 4
	DWORD Unk2; // 8
	DWORD Unk3; // C
	BOOL Continuable; // If the exception can be continued // 10
	DWORD ExceptionInformation[32]; // 14
} KEXCEPTION_FRAME, *PKEXCEPTION_FRAME;

typedef BOOL (*pfnTrapHandler)(PKTRAP_FRAME ptf, PKEXCEPTION_FRAME pef,
	PCONTEXT pcr, BOOL fSecondChance);

typedef struct _ldata{ //This is the variable exported on ordinal 1 from dashlaunch
	DWORD ID;
	DWORD ltype;
	char link[MAX_PATH];
	char dev[MAX_PATH];
	USHORT versionMaj;
	USHORT versionMin;
	USHORT targetKernel;
	USHORT reserved;
	DWORD options; // for external apps that want to know what dash launch has set/parsed
	pfnTrapHandler *DebugRoutine; // for external apps that want to recursively hook and call the first/last chance exception trap on their own
	LPDWORD DebugStepPatch; // address to patch single step exception to not be skipped (write 0x60000000/nop to this address to enable it)
} ldata, *pldata;

// Debug Monitor Global Data
typedef struct _DMGD
{
	BOOL bDirty; // If true, the saved settings will be flushed soon

	BOOL bDashlaunch; // If true, dashlaunch is loaded with the version we want

	pldata pLaunchData; // This is the data taken from dashlaunch

	HMODULE hXam; // xam.xex
	HMODULE hKernel; // xboxkrnl.exe
	HMODULE hDashlaunch; // launch.xex

	pfnTrapHandler PreviousTrap; // The trap handler that used to be there

	HANDLE pthrServ; // The server thread handle

	BOOL fClockSet; // If the clock was set yet

	BOOL bHasIp; // If we have an ip address

	DWORD dwPid; // Process id

	BOOL bDebugging; // If a debugger is present
	DWORD dwDebugPort; // The debugger port
	char rgchDebuggerName[256]; // The debugger name
	char rgchDebuggerUser[256]; // The debugger user

	DWORD dwStopFlags; // When we should stop

	BOOL bHypervisorEnabled; // If hypervisor expansions are enabled

	// BEGIN_SAVED_SETTINGS

	char rgchDbgName[256]; // The debug name of the xbox
	BOOL bDriveMap; // If we map internal drives or not

	DWORD dwConsoleColor;

	BOOL bMagicBoot; // If we are to write the magicboot settings to disk
	char szBootTitle[MAX_PATH]; // The path to the title that we want to boot
	char szBootPath[MAX_PATH]; // The path that we want to use as game:\\ 
	char szBootCmdLine[MAX_PATH]; // The command line arguments to pass when we boot
	DWORD dwBootFlags; // The flags for when we continue
	DWORD dwDumpMode; // What we do if we crash without a debugger attached

	// END_SAVED_SETTINGS
} DMGD, *PDMGD;

// Debug Monitor Debug Data
typedef struct _DMDD
{
	PKPROCESS KeSystemProcess; // A descriptor for all system threads (spinlock this!)
	PKPROCESS KeTitleProcess; // A descriptor for all title threads (spinlock this!)
	
	PLIST_ENTRY PsLoadedModuleList; // A list of all loaded modules
	DWORD *XexLoadedModuleListLock; // Spinlock this before using PsLoadedModuleList
} DMDD, *PDMDD;

extern DMGD g_dmGlobals;
extern DMDD g_dmDebug;

#ifdef _DEBUG
typedef struct
{
	DWORD MinVersion;
	DWORD Unk; // i dont set this
	DWORD XamXbdmRebootRequest; // run this to reboot
	DWORD Unk1;
	DWORD Unk2;
	DWORD Unk3;
	DWORD Unk4;
	DWORD Unk5;
	BYTE szTitle[0x100];
	BYTE szFolder[0x100];
	BYTE szCmdLine[0x100];
} XAMGLOBALS;
extern XAMGLOBALS g_XamGlobals;
#endif

// Exports

// XAM.XEX
//typedef NTSTATUS (*pfnXamLoaderLaunchTitleEx)(LPCSTR XexName, LPCSTR MountPath,
//	LPCSTR CmdLine, DWORD Flags);
//pfnXamLoaderLaunchTitleEx XamLoaderLaunchTitleEx;

#endif