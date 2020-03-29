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

#ifndef _DMBREAK_H
#define _DMBREAK_H

// Thread data structure
typedef struct _DMTD
{
	DWORD DebugFlags;

	char *ThreadName;

	DWORD dwThreadId;
#if 0
	LIST_ENTRY Link;
#endif

	DWORD StopReason;

	DWORD BreakpointAddress;

	PCONTEXT Context;
	PKEXCEPTION_FRAME Exception;

	HANDLE DebugEvent;
	KEVENT DebugEventData;
} DMTD;

// Breakpoint structure
typedef struct _DMBP
{
	DWORD dwAddr; // The address of the breakpoint
	BYTE Code[4]; // The code data that used to be there
	BOOL bEnabled; // If the breakpoint is active

	LIST_ENTRY Link; // List entry
} DMBP, *PDMBP;

// Hardware breakpoint structure
typedef struct _DMHB
{
	DWORD dwAddr; // The address
	DWORD dwType; // The type
	DWORD dwSize; // The size
} DMHB;

// Debug thread flags
#define DMFLAG_STOPPED			0x0001 // Execution is stopped
#define DMFLAG_DEBUGTHREAD		0x0002 // We are a debug thread
#define DMFLAG_TRAPPED			0x0004 // We are in a trap handler
#define DMFLAG_EXCEPTION		0x0008 // Thread is stopped
#define DMFLAG_SINGLESTEP		0x0010 // We are single stepping from the debugger
#define DMFLAG_DATABREAK		0x0020 // We are patching up the data breakpoint
#define DMFLAG_FIRSTCHANCE		0x0040 // We are in a first chance exception
#define DMFLAG_CONTINUEABLE		0x0080 // Thread is continuable via dmcontinue
// 0x0100
// 0x0400
// 0x0800
// 0x0C00
// 0x1000
// 0x2000
// 0x4000
// 0x8000

// Breakpoints
#define BREAKPOINT_PRINT			0x0FE00014 // Debug printing
#define BREAKPOINT_PROMPT			0x0FE00015 // Debug prompt from the kernel debugger
#define BREAKPOINT_BREAK			0x0FE00016 // Breakpoint
#define BREAKPOINT_LOAD_SYMBOLS		0x0FE00017 // Load symbols for an exe
#define BREAKPOINT_UNLOAD_SYMBOLS	0x0FE00018 // Unload symbols for an exe
#define BREAKPOINT_ASSERT			0x0FE0001A // Failed an assert
#define BREAKPOINT_RIP				0x0FE0001B // Failed a rip

#define BREAKPOINT_MAX				128			// Maximum breakpoint count

// Hardware breakpoints
#define HWBP_READ 1
#define HWBP_WRITE 2
#define HWBP_EXECUTE 4
#define HWBP_READWRITE (HWBP_READ | HWBP_WRITE)

VOID VSetThreadName(DWORD dwThreadId, LPCSTR szName);
BOOL FInitThreadDebugData(PKTHREAD pthr);
VOID DmFreeThreadData(DMTD *pdmtd);
DMTD *DmGetCurrentDmtd();

#if 0
DMTD *DmGetThreadDmtd(DWORD dwThreadId);
#endif

VOID LpTitleTerminateRoutine();
VOID LpThreadNotificationRoutine(PEX_THREAD_REGISTRATION ThisRegistration, PKTHREAD Thread, BOOL Creating);

BOOL DmTrapHandler(PKTRAP_FRAME ptf, PKEXCEPTION_FRAME pef,
	PCONTEXT pcr, BOOL fSecondChance);

BOOL FSetMemory(DWORD dwAddr, BYTE b);
BOOL FGetMemory(DWORD dwAddr, PBYTE pb);

DMHRAPI DwChangeExecState(DWORD dwState, BOOL fAlterThreads, BOOL fTell, BOOL bStop);

PVOID PvDbgWriteCheck(PVOID Address, PHANDLE Handle);
PVOID PvDbgReadCheck(PVOID Address);
BOOL FIsMmIoAddress(PVOID addr);

BOOL FIsBreakpoint(PVOID addr);
DMHRAPI DmRemoveAllBreakpoints();
PDMBP FFindBreak(PVOID addr, BOOL raiseIrql);
VOID DoEnableBreak(PDMBP bp);
VOID DoDisableBreak(PDMBP bp);
BOOL FMatchDataBreak(PVOID addr);
ULONG_PTR DmpSetHardwareBreakpoint(DWORD Context);

PKPCR __forceinline __declspec(naked) KeGetCurrentPcr()
{
	__asm
	{
		mr r3, r13
		blr
	}
}

PKTHREAD __forceinline PsGetCurrentThread()
{
	return KeGetCurrentPcr()->Prcb->CurrentThread;
}

BYTE __forceinline KeGetCurrentIrql()
{
	return KeGetCurrentPcr()->CurrentIrql;
}

extern DWORD DmpBreakSpinLock, dwExecState;
extern CRITICAL_SECTION csExceptionStack, csExceptionStackTitle, csDebugMonitorData, csExecState;
extern PVOID ExceptionStack, ExceptionStackTitle;
extern LIST_ENTRY leDebugMonitorData, leBreaks;
extern DMHB HardwareBreakpoint;

#endif