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

#ifndef _DMSERV_H
#define _DMSERV_H

#define CONNECTION_MAX 8

#define DMPL_PRIV_HVX (DMPL_PRIV_CONTROL | 0x0020) // Hypervisor expansion is required
#define DMPL_PRIV_HVX_MASK 0x0020

// Default custom data, contains useful stuffs
typedef struct _DMCD
{
	DWORD cch, ib, cchBuf;
	BOOL fError;
	HANDLE h;
	HRESULT hr;
	LPSTR rgb;
	union
	{
		struct
		{
			int CurrentDrive;
		} DriveList;
		struct
		{
			FILE_NETWORK_OPEN_INFORMATION fni;
		} fni;
		struct
		{
			DWORD Address;
		} mem;
		struct
		{
			DWORD fmt;
			DWORD w, h, p, sw, sh, size;
			LPCSTR szFrame;
		} screen;
		struct
		{
			DWORD step;
			DWORD remain;

			// Current file info
			LARGE_INTEGER CreationTime;
			LARGE_INTEGER ChangeTime;
			DWORD FileSize;
			DWORD FileAttributes;
		} vfile;
		DMN_SECTIONLOAD dmsl;
		DM_THREADINFOEX dmti;
		char sz[0x100];
	};
} DMCD, *PDMCD;

// Just a helpful macro to avoid having to type that EVERY TIME >.<
#define pdmcd ((PDMCD)pdmcc->CustomData)

// Connection structure
typedef struct _DMCONN
{
	// TRUE if used, FALSE if standby
	BOOL bActive;

	// TRUE if we should shutdown soon
	BOOL bShutdown;

	BOOL bKeepAlive; // TRUE if we should keep the socket alive

	DWORD dwPriv; // The connection privilege

	// TRUE if the command is too long
	BOOL bTooLong;

	// Connection socket
	SOCKET s;

	// The client endpoint
	SOCKADDR_IN sin;

	// Continue structure
	DM_CMDCONT dmcc;

	// Custom data
	DMCD dmcd;

	// Temp buffer storage
	LPVOID Buffer;

	// If TRUE, we are in an extended handler
	BOOL bConversation;

	// The last return value
	HRESULT hr;

	// The position in the buffer
	DWORD dwRecv;

	// Command receive buffer
	BYTE szRecv[0x200];

	// Extended buffer
	BYTE szBuf[256];
} DMCONN, *PDMCONN;

// Command structure
typedef struct _DMCMD
{
	LPCSTR szName;
	DWORD dwPriv;
	PDM_CMDPROC pdmcp;
} DMCMD, *PDMCMD;

// Used in PcregNext
typedef struct _DMREG
{
	LPCSTR Name;
	DWORD Context;
	DWORD Offset;
	DWORD Size;
} DMREG;
// Used in HrGet/SetContext
typedef struct _DMCR
{
	XCONTEXT Context;
	DMREG *Register;
	DWORD CurrentRegister;
} DMCR;

extern char *rgszDumpMode[];
extern DMCMD rgbcmd[];
extern int cchcmd;
extern DMREG rgbregs[];
extern int cchregs;

ULONG __stdcall ServerThread(LPVOID lpParam);
int FSendLine(SOCKET s, LPCSTR fmt, ...);
VOID FStopServ();

#endif