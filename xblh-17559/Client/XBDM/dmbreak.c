// Copyright (c) 2013 Nathan LeRoux
// Project started early 2011
// If you want to get in touch, shoot me an email <confettimancer@gmail.com>
// I'm currently seeking employment, and figured 'what the hell, its free advertising'

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

#include "..\stdafx.h"

DWORD DmpBreakSpinLock;
CRITICAL_SECTION csExceptionStack, csExceptionStackTitle, csDebugMonitorData, csExecState;
PVOID ExceptionStack, ExceptionStackTitle;
LIST_ENTRY leDebugMonitorData, leBreaks;
DMHB HardwareBreakpoint;

DWORD dwExecState = DMN_EXEC_PENDING;

DWORD __declspec(naked) DebugRtlAssert(PANSI_STRING Message)
{
	__asm
	{
		lhz r4, 0(r3)
		lwz r3, 4(r3)
		twi 31, r0, 26
		blr
	}
}

VOID __declspec(naked) DbgBreakPoint()
{
	__asm
	{
		twi 31, r0, 22
		blr
	}
}

VOID __declspec(naked) DebugPrint(PANSI_STRING String)
{
	__asm
	{
		lhz r4, 0(r3)
		lwz r3, 4(r3)
		twi 31, r0, 20
		blr
	}
}

VOID __stdcall RtlAssert(LPCSTR FailedAssertion, LPCSTR FileName, ULONG LineNumber, PCHAR Message)
{
	char result;
	char sz[0x200];
	ANSI_STRING as;

	_snprintf(sz, sizeof(sz), "\n*** Assertion failed: %s%s\n***   Source File: %s, line %ld\n\n", Message, FailedAssertion, FileName, LineNumber);

	RtlInitAnsiString(&as, sz);

	for(;;)
	{
		result = (BYTE)DebugRtlAssert(&as);
		if(result == 'b' || result == 'B')
			DbgBreakPoint();
		else if(result == 'i' || result == 'I')
			return;
		else if(result == 'T' || result == 't')
			ExTerminateThread(STATUS_UNSUCCESSFUL);
	}
}

DMHRAPI DwChangeExecState(DWORD dwState, BOOL fAlterThreads, BOOL fTell, BOOL bStop)
{
	// dwState = DMN_EXEC_XXX
	// fAlterThreads = TRUE to start/stop threads
	// fTell = TRUE to tell others, FALSE to hide (notifications)
	// bStop = TRUE to add a DM_STOPTHREAD flag to the notification
	PLIST_ENTRY ple;
	PKTHREAD pthr;
	DMTD *pdmtd;
	BYTE irql;
	int i;

	if(dwExecState == dwState)
	{
		if(dwState == DMN_EXEC_START)
			return XBDM_NOTSTOPPED;
		else
			return XBDM_ALREADYSTOPPED;
	}

	if(dwState > DMN_EXEC_PENDING_TITLE)
		return E_INVALIDARG;
	
	KeEnterCriticalRegion();

	dwExecState = dwState;

	if(fAlterThreads)
	{
		irql = KfAcquireSpinLock(&g_dmDebug.KeTitleProcess->ThreadListLock);
		ple = g_dmDebug.KeTitleProcess->ThreadListHead.Flink;

		for(i = 0;i < 2;i++)
		{
			while(ple != &g_dmDebug.KeTitleProcess->ThreadListHead
				&& ple != &g_dmDebug.KeSystemProcess->ThreadListHead)
			{
				pthr = CONTAINING_RECORD(ple, KTHREAD, ThreadListEntry);
#if 0
				pdmtd = DmGetThreadDmtd((DWORD)pthr->ThreadId);
#else
				pdmtd = (DMTD*)pthr->DebugMonitorData;
#endif

				if(!pdmtd)
				{
					FInitThreadDebugData(pthr);
					pdmtd = (DMTD*)pthr->DebugMonitorData;
				}

				ple = ple->Flink;

				if(!pdmtd || (pdmtd->DebugFlags & DMFLAG_DEBUGTHREAD)
					|| (PsGetCurrentThread()->ThreadId == pthr->ThreadId))
					continue;

				if(dwState == DMN_EXEC_START)
					KeSetEvent(pdmtd->DebugEvent, TRUE, FALSE);

				if((dwState == DMN_EXEC_START) & (pdmtd->DebugFlags & DMFLAG_STOPPED))
				{
					KeResumeThread(pthr);
					pdmtd->DebugFlags &= ~DMFLAG_STOPPED;
				}
				else if((dwState != DMN_EXEC_START) && !(pdmtd->DebugFlags & DMFLAG_STOPPED))
				{
					KeSuspendThread(pthr);
					pdmtd->DebugFlags |= DMFLAG_STOPPED;
				}
			}

			if(i == 0)
			{
				KfReleaseSpinLock(&g_dmDebug.KeTitleProcess->ThreadListLock, irql);

				irql = KfAcquireSpinLock(&g_dmDebug.KeSystemProcess->ThreadListLock);
				ple = g_dmDebug.KeSystemProcess->ThreadListHead.Flink;
			}
			else
				KfReleaseSpinLock(&g_dmDebug.KeSystemProcess->ThreadListLock, irql);
		}
	}

	if(fTell)
		FNotify(bStop ? (DM_EXEC | DM_STOPTHREAD) : DM_EXEC, dwState);

	KeLeaveCriticalRegion();

	return XBDM_NOERR;
}

DMHRAPI DmGetThreadInfoEx(DWORD dwThreadId, PDM_THREADINFOEX pdmti)
{
	PKTHREAD pthr;
	BYTE irql;
	DMTD *pdmtd;

	if(!pdmti || pdmti->Size < sizeof(DM_THREADINFOEX)) // Kill everything compiled before a certain date? WHY CERTAINLY I SHALL
		return E_INVALIDARG;
	
	if(FAILED(ObLookupAnyThreadByThreadId(dwThreadId, &pthr)))
		return XBDM_NOTHREAD;

	irql = KfAcquireSpinLock((PDWORD)pthr->Process);

	ZeroMemory(pdmti + 4, pdmti->Size - 4);

#if 0
	pdmtd = DmGetThreadDmtd(dwThreadId);
#else
	pdmtd = (DMTD*)pthr->DebugMonitorData;
#endif

	pdmti->SuspendCount = pthr->SuspendCount;
	pdmti->Priority = pthr->Priority;
	pdmti->TlsBase = pthr->TlsData;
	pdmti->StartAddress = pthr->StartAddress;
	pdmti->StackBase = pthr->StackBase;
	pdmti->StackLimit = pthr->StackLimit;
	pdmti->CreateTime.dwHighDateTime = pthr->CreateTime.HighPart;
	pdmti->CreateTime.dwLowDateTime = pthr->CreateTime.LowPart;
	pdmti->StackSlackSpace = 0x540;

	if(pdmtd)
	{
		if(pdmtd->DebugFlags & DMFLAG_STOPPED)
			pdmti->SuspendCount--;

		pdmti->ThreadNameAddress = pdmtd->ThreadName;

		if(pdmti->ThreadNameAddress)
			pdmti->ThreadNameLength = strlen(pdmtd->ThreadName) + 1;
		else
			pdmti->ThreadNameLength = 0;
	}

	pdmti->CurrentProcessor = pthr->CurrentProcessor;
	pdmti->LastError = pthr->LastWin32ErrorCode;

	KfReleaseSpinLock((PDWORD)pthr->Process, irql);

	ObDereferenceObject(pthr);

	return XBDM_NOERR;
}

VOID VSetThreadName(DWORD dwThreadId, LPCSTR szName)
{
	DMTD *pdmtd;
	PKTHREAD pthr = NULL;
	int i;

	if(dwThreadId == -1)
		pdmtd = DmGetCurrentDmtd();
	else
	{
		if(NT_SUCCESS(ObLookupAnyThreadByThreadId(dwThreadId, &pthr)))
		{
#if 0
			if(!(pdmtd = DmGetThreadDmtd(dwThreadId)))
#else
			if(!(pdmtd = (DMTD*)pthr->DebugMonitorData))
#endif
			{
				FInitThreadDebugData(pthr);
#if 0
				pdmtd = DmGetThreadDmtd(dwThreadId);
#else
				pdmtd = (DMTD*)pthr->DebugMonitorData;
#endif
			}
		}
	}

	if(pdmtd)
	{
		if(pdmtd->ThreadName)
				DmFreePool(pdmtd->ThreadName);

		if(szName)
		{
			i = strlen(szName) + 1;

			pdmtd->ThreadName = (char*)DmAllocatePoolTypeWithTag(i, 'Dmtd', 2);

			if(pdmtd->ThreadName)
				strcpy_s(pdmtd->ThreadName, i, szName);
		}
		else
			pdmtd->ThreadName = NULL;
	}

	if(pthr)
		ObDereferenceObject(pthr);
}

BOOL FInitThreadDebugData(PKTHREAD pthr)
{
	DMTD *pdmtd = (DMTD*)DmAllocatePoolTypeWithTag(sizeof(DMTD), 'Dmtd', 2);

	if(!pdmtd)
		return FALSE;

	ZeroMemory(pdmtd, sizeof(DMTD));

	if(pthr->CreateOptions & 0x400)
		pdmtd->DebugFlags |= DMFLAG_DEBUGTHREAD;

	KeInitializeEvent(&pdmtd->DebugEventData, 0, FALSE);
	KeSetEvent(&pdmtd->DebugEventData, TRUE, FALSE);

	pdmtd->DebugEvent = &pdmtd->DebugEventData;

	pdmtd->dwThreadId = (DWORD)pthr->ThreadId;
#if 0
	// Add the data to the list
	EnterCriticalSection(&csDebugMonitorData);
	pdmtd->Link.Flink = leDebugMonitorData.Flink;
	pdmtd->Link.Blink = &leDebugMonitorData;
	leDebugMonitorData.Flink->Blink = &pdmtd->Link;
	leDebugMonitorData.Flink = &pdmtd->Link;
	LeaveCriticalSection(&csDebugMonitorData);
#else
	pthr->DebugMonitorData = pdmtd;
#endif
	return TRUE;
}

VOID DmFreeThreadData(DMTD *pdmtd)
{
#if 0
	// Patch up the hole
	EnterCriticalSection(&csDebugMonitorData);
	pdmtd->Link.Flink->Blink = pdmtd->Link.Blink;
	pdmtd->Link.Blink->Flink = pdmtd->Link.Flink;
	LeaveCriticalSection(&csDebugMonitorData);
#endif
	if(!pdmtd)
		return;

	if(pdmtd->ThreadName)
		DmFreePool(pdmtd->ThreadName);

	DmFreePool(pdmtd);
}
#if 0
DMTD *DmGetThreadDmtd(DWORD dwThreadId)
{
	DMTD *pdmtd = NULL;
	PLIST_ENTRY ple;

	EnterCriticalSection(&csDebugMonitorData);

	ple = leDebugMonitorData.Flink;
	
	while(ple != &leDebugMonitorData)
	{
		pdmtd = CONTAINING_RECORD(ple, DMTD, Link);
		ple = ple->Flink;

		if(pdmtd->dwThreadId == dwThreadId)
			break;
		else
			pdmtd = NULL;
	}

	LeaveCriticalSection(&csDebugMonitorData);

	return pdmtd;
}
#endif
DMTD *DmGetCurrentDmtd()
{
#if 0
	DMTD *pdmtd = NULL;
	PLIST_ENTRY ple;

	EnterCriticalSection(&csDebugMonitorData);

	ple = leDebugMonitorData.Flink;
	
	while(ple != &leDebugMonitorData)
	{
		pdmtd = CONTAINING_RECORD(ple, DMTD, Link);
		ple = ple->Flink;

		if(pdmtd->dwThreadId == (DWORD)PsGetCurrentThread()->ThreadId)
			break;
		else
			pdmtd = NULL;
	}

	LeaveCriticalSection(&csDebugMonitorData);

	return pdmtd;
#else
	return (DMTD*)PsGetCurrentThread()->DebugMonitorData;
#endif
}

VOID DbgOut(LPCSTR fmt, ...)
{
	char sz[0x200];
	va_list va;
	ANSI_STRING as;

	va_start(va, fmt);
	RtlVsnprintf(sz, sizeof(sz), fmt, va);
	va_end(va);

	if(KeGetCurrentIrql() == PASSIVE_LEVEL)
	{
		RtlInitAnsiString(&as, sz);
		DebugPrint(&as);
	}
}

BOOL ResumeAfterBreakpoint(PCONTEXT pcr)
{
	BOOL fRet = FALSE;
	PDMBP bp = FFindBreak((PVOID)pcr->Iar, TRUE);
	
	if(bp)
	{
		fRet = TRUE;

		DoDisableBreak(bp);

		// Single step exceptions
		pcr->Msr |= 0x400;
	}

	return fRet;
}

VOID PrepareToStop()
{
	DMTD *pdmtd = DmGetCurrentDmtd();

	if(!pdmtd)
		ASSERT(FALSE);

	KeResetEvent(pdmtd->DebugEvent);

	DwChangeExecState(DMN_EXEC_STOP, TRUE, TRUE, FALSE);
}

BOOL FStopAtException()
{
	BOOL fRet = TRUE;
	DMTD *pdmtd = DmGetCurrentDmtd();
	NTSTATUS st;

	if(!pdmtd)
		ASSERT(FALSE);

	pdmtd->DebugFlags |= DMFLAG_CONTINUEABLE;

	st = KeWaitForSingleObject(pdmtd->DebugEvent, UserRequest, PROC_USER, 0, NULL);
	ASSERT(NT_SUCCESS(st));

	pdmtd->DebugFlags &= ~DMFLAG_CONTINUEABLE;

	fRet = pdmtd->DebugFlags & DMFLAG_EXCEPTION;
	pdmtd->DebugFlags &= ~DMFLAG_EXCEPTION;

	return fRet; // True means that the debugger did not handle the exception
}

BOOL FTrapNotify(DWORD dwMask, ULONG_PTR ulpParam, BOOL fStop, BOOL *pPassAlong)
{
	BOOL fRet = FALSE;
	DMTD *pdmtd = DmGetCurrentDmtd();

	if(!pdmtd)
		return FALSE;

	if((KeGetCurrentIrql() != PASSIVE_LEVEL) || (pdmtd->DebugFlags & DMFLAG_DEBUGTHREAD))
		fStop = FALSE;
	else if(!g_dmGlobals.bDebugging)
		fStop = FALSE; // TODO: get kd working so i can check if kd is connected before passing to it

	if(fStop)
		PrepareToStop();

	pdmtd->StopReason = dwMask & DM_NOTIFICATIONMASK;

	FNotify(fStop ? (dwMask | DM_STOPTHREAD) : dwMask, ulpParam);
	
	if(fStop)
	{
		fRet = FStopAtException();

		if(!fRet && pPassAlong) // Debugger did not handle, thus pass it along
			*pPassAlong = FALSE;
	}

	pdmtd->StopReason = 0;

	return fRet;
}

VOID DoModuleWait()
{
	DWORD dwFlags;
	LARGE_INTEGER li;
	PLARGE_INTEGER pli;
	DMTD* pdmtd = DmGetCurrentDmtd();

	dwFlags = g_dmGlobals.dwBootFlags & (DMBOOT_WAIT | DMBOOT_STOP);
	g_dmGlobals.dwBootFlags &= ~(DMBOOT_WAIT | DMBOOT_STOP);
	g_dmGlobals.bDirty = TRUE;

	if(!dwFlags || !pdmtd || (KeGetCurrentIrql() != PASSIVE_LEVEL))
		return;

	if(dwFlags == DMBOOT_STOP)
		pli = NULL;
	else
	{
		pli = &li;
		li.QuadPart = -150000000;
	}

	KeResetEvent(pdmtd->DebugEvent);
	DwChangeExecState(DMN_EXEC_PENDING_TITLE, TRUE, TRUE, TRUE);

	if(KeWaitForSingleObject(pdmtd->DebugEvent, UserRequest, PROC_USER, FALSE, pli) == STATUS_TIMEOUT)
		DwChangeExecState(DMN_EXEC_START, TRUE, TRUE, FALSE);
}

typedef struct tagTHREADNAME_INFO
{
   DWORD dwType; // Must be 0x1000.
   LPCSTR szName; // Pointer to name (in user addr space).
   DWORD dwThreadID; // Thread ID (-1=caller thread).
   DWORD dwFlags; // Reserved for future use, must be zero.
} THREADNAME_INFO;
BOOL DmTrapHandlerImp(PKTRAP_FRAME ptf, PKEXCEPTION_FRAME pef,
	PCONTEXT pcr, BOOL fSecondChance, PVOID Unused)
{
	BOOL fPassAlong = TRUE;
	BOOL fRet = TRUE;
	DMTD *pdmtd = DmGetCurrentDmtd();
	PIMAGE_NT_HEADERS pinh;
	PANSI_STRING pas;
	BOOL fSkip = TRUE;

	pdmtd = DmGetCurrentDmtd();

	if(pdmtd)
	{
		pdmtd->Context = pcr;
		pdmtd->Exception = pef;

		if(pef->Status == STATUS_BREAKPOINT)
		{
			if(pef->ExceptionInformation[0] == BREAKPOINT_PRINT)
			{
				DMN_DEBUGSTR dmds;
				dmds.ThreadId = (DWORD)PsGetCurrentThread()->ThreadId;
				dmds.String = (LPCSTR)pcr->Gpr3;
				dmds.Length = (DWORD)pcr->Gpr4;
			
				FTrapNotify(DM_DEBUGSTR, (ULONG_PTR)&dmds, g_dmGlobals.dwStopFlags & DMSTOP_DEBUGSTR, NULL);
			}
			else if(pef->ExceptionInformation[0] == BREAKPOINT_LOAD_SYMBOLS)
			{
				if(pcr->Gpr3 && pcr->Gpr4)
				{
					DMN_MODLOAD_EX dmmd;
					LPDWORD lp;

					ZeroMemory(&dmmd, sizeof(dmmd));
			
					dmmd.SizeOfStruct = sizeof(dmmd);

					pas = (PANSI_STRING)pcr->Gpr3;
					lp = (LPDWORD)pcr->Gpr4;
					pinh = RtlImageNtHeader((PVOID)lp[0]);

					strncpy_s(dmmd.Name, 260, pas->Buffer, pas->Length);
					dmmd.BaseAddress = (PVOID)lp[0];
					dmmd.Size = lp[3];
					dmmd.CheckSum = _byteswap_ulong(pinh->OptionalHeader.CheckSum);
					dmmd.Flags = 0;
					dmmd.OriginalSize = _byteswap_ulong(pinh->OptionalHeader.SizeOfImage);
					dmmd.PDataAddress = (LPDWORD)RtlImageDirectoryEntryToData(dmmd.BaseAddress, TRUE, 3, &dmmd.PDataSize);
					dmmd.ThreadId = (DWORD)PsGetCurrentThread()->ThreadId;

					if((lp[0] & 0xEFFFFFFF) == 0x82000000)
						DoModuleWait();

					FTrapNotify(DM_MODLOAD, (ULONG_PTR)&dmmd, g_dmGlobals.dwStopFlags & DMSTOP_MODLOAD, NULL);
				}
			}
			else if(pef->ExceptionInformation[0] == BREAKPOINT_UNLOAD_SYMBOLS)
			{
				if(pcr->Gpr3 && pcr->Gpr4)
				{
					DMN_MODLOAD_EX dmmd;
					LPDWORD lp;

					pas = (PANSI_STRING)pcr->Gpr3;
					lp = (LPDWORD)pcr->Gpr4;

					strcpy_s(dmmd.Name, 260, pas->Buffer);
			
					dmmd.BaseAddress = (PVOID)lp[0];
					dmmd.Size = lp[3];
					dmmd.ThreadId = (DWORD)PsGetCurrentThread()->ThreadId;
			
					pas = (PANSI_STRING)pcr->Gpr3;

					FTrapNotify(DM_MODUNLOAD, (ULONG_PTR)&dmmd, FALSE, NULL);
				}
			}
			else if(pef->ExceptionInformation[0] == BREAKPOINT_BREAK)
			{
				DMN_BREAK dmb;

				dmb.Address = (PVOID)pcr->Iar;
				dmb.ThreadId = (DWORD)PsGetCurrentThread()->ThreadId;

				if(FFindBreak(dmb.Address, TRUE))
					fSkip = FALSE;

				FTrapNotify(DM_BREAK, (ULONG_PTR)&dmb, TRUE, &fPassAlong);

				if(g_dmGlobals.bDebugging)
					fPassAlong = FALSE; // we dont pass along breakpoints while debugging
				
				if(ResumeAfterBreakpoint(pcr))
					pdmtd->BreakpointAddress = (DWORD)dmb.Address;
			}
			else if(pef->ExceptionInformation[0] == BREAKPOINT_ASSERT)
			{
				DMN_DEBUGSTR dmds;
				dmds.String = (LPCSTR)pcr->Gpr3;
				dmds.Length = (DWORD)pcr->Gpr4;
				dmds.ThreadId = (DWORD)PsGetCurrentThread()->ThreadId;
			
				FTrapNotify(DM_ASSERT, (ULONG_PTR)&dmds, TRUE, &fPassAlong);
			}
			else if(pef->ExceptionInformation[0] == BREAKPOINT_RIP)
			{
				// TODO: this thing here
				ASSERT(FALSE);
			}
		}
		else if(pef->Status == STATUS_SINGLE_STEP)
		{
			// We dont want to skip the current instruction in a single step exception
			fSkip = FALSE;

			if(pef->ExceptionInformation[0])
			{
				BOOL fStep = pdmtd->DebugFlags & DMFLAG_SINGLESTEP;
				pdmtd->DebugFlags &= ~DMFLAG_SINGLESTEP;
				pcr->Msr &= ~0x400;

				// Single step exception
				if(pdmtd->BreakpointAddress)
				{
					PDMBP bp = FFindBreak((PVOID)pdmtd->BreakpointAddress, TRUE);
					if(bp)
						DoEnableBreak(bp);

					pdmtd->BreakpointAddress = 0;

					fPassAlong = FALSE;
				}
				else if(pdmtd->DebugFlags & DMFLAG_DATABREAK)
				{
					// Set the breakpoint again
					DmSetDataBreakpoint((PVOID)HardwareBreakpoint.dwAddr, HardwareBreakpoint.dwType, HardwareBreakpoint.dwSize);
					pdmtd->DebugFlags &= ~DMFLAG_DATABREAK;

					fPassAlong = FALSE;
				}
				else
					fStep = TRUE;

				if(fStep)
				{
					// we have to stop
					DMN_BREAK dmb;
					dmb.Address = (PVOID)pcr->Iar;
					dmb.ThreadId = (DWORD)PsGetCurrentThread()->ThreadId;

					FTrapNotify(DM_SINGLESTEP, (ULONG_PTR)&dmb, TRUE, &fPassAlong);

					if(g_dmGlobals.bDebugging)
						fPassAlong = FALSE;
				}
			}
			else
			{
				// Data breakpoint

				if(FMatchDataBreak((PVOID)pef->ExceptionInformation[1]))
				{
					DMN_DATABREAK dmdb;
					dmdb.Address = (PVOID)pcr->Iar;
					dmdb.DataAddress = (PVOID)pef->ExceptionInformation[1];

					pdmtd->DebugFlags |= DMFLAG_DATABREAK;

					KeIpiGenericCall(DmpSetHardwareBreakpoint, 0);

					FTrapNotify(DM_DATABREAK, (ULONG_PTR)&dmdb, TRUE, &fPassAlong);

					// Single step
					pcr->Msr |= 0x400;
				}
				else
				{
					DMN_BREAK dmb;
					dmb.Address = (PVOID)pcr->Iar;
					dmb.ThreadId = (DWORD)PsGetCurrentThread()->ThreadId;

					FTrapNotify(DM_DATABREAK, (ULONG_PTR)&dmb, TRUE, &fPassAlong);
				}

				if(g_dmGlobals.bDebugging)
						fPassAlong = FALSE;
			}
		}
		else if(pef->Status == 0x406D1388)
		{
			if(pef->ExceptionInformation[0] == 0x1000)
			{
				VSetThreadName(pef->ExceptionInformation[2], (LPCSTR)pef->ExceptionInformation[1]);
			}
		}
		else
		{
			DMN_EXCEPTION dme;
			BOOL fStop = TRUE;

			dme.Address = (PVOID)pcr->Iar;
			dme.Code = pef->Status;
			dme.ThreadId = (DWORD)PsGetCurrentThread()->ThreadId;

			if(!fSecondChance)
			{
				dme.Flags = DM_EXCEPT_FIRSTCHANCE;
				pdmtd->DebugFlags |= DMFLAG_FIRSTCHANCE;
				fStop = (g_dmGlobals.dwStopFlags & DMSTOP_FCE);
			}
			else
				dme.Flags = 0;

			if(pef->Status == STATUS_ACCESS_VIOLATION)
			{
				dme.Information[0] = pef->ExceptionInformation[0];
				dme.Information[1] = pef->ExceptionInformation[1];
			}
			else
			{
				dme.Information[0] = pef->Continuable;
				dme.Information[1] = (DWORD)&pef->ExceptionInformation[0];
			}

			fRet = !FTrapNotify(DM_EXCEPTION, (ULONG_PTR)&dme, fStop, &fPassAlong);

			pdmtd->DebugFlags &= ~DMFLAG_FIRSTCHANCE;

			if(g_dmGlobals.bDebugging && (KeGetCurrentIrql() == PASSIVE_LEVEL))
			{
				fPassAlong = FALSE; // We don't pass along if we are debugging

				if(fSecondChance)
					fRet = TRUE; // continue second chance if we are debugging no matter what
			}
		
			fSkip = FALSE;
		}

		pdmtd->Context = NULL;
		pdmtd->Exception = NULL;
	}

	if(fPassAlong)
		return g_dmGlobals.PreviousTrap(ptf, pef, pcr, fSecondChance);

	if(fSkip)
		pcr->Iar += 4;

	return fRet;
}

BOOL __declspec(naked) DmTrapOnStack(PKTRAP_FRAME ptf, PKEXCEPTION_FRAME pef,
	PCONTEXT pcr, BOOL fSecondChance, PVOID Unused, PVOID stack)
{
	__asm
	{
		// Store LR
		mflr r12
		stw r12, -8(sp)

		// Get some stack
		stwu sp, -0x60(sp)

		// Get some breathing room
		addi r8, r8, -0x50

		// r8 = sp - r8
		subf r8, sp, r8

		// r9 = sp + 0x60
		addi r9, sp, 0x60

		// temp = sp + r8
		// *r9 = temp
		// sp = temp
		stwux r9, sp, r8

		// Branch
		bl DmTrapHandlerImp

		// Get the stack pointer
		lwz sp, 0(sp)

		// Get the link register
		lwz r12, -8(sp)
		mtlr r12

		// Return
		blr
	}
}

BOOL DmTrapHandler(PKTRAP_FRAME ptf, PKEXCEPTION_FRAME pef,
	PCONTEXT pcr, BOOL fSecondChance)
{
	BOOL fRet;
	DMTD *pdmtd = DmGetCurrentDmtd();
	PCRITICAL_SECTION cs;
	PVOID stack;

	if((KeGetCurrentIrql() == PASSIVE_LEVEL) && pdmtd && !(pdmtd->DebugFlags & DMFLAG_TRAPPED) && !(pdmtd->DebugFlags & DMFLAG_DEBUGTHREAD)) // Prevent trapception
	{
		if(KeGetCurrentProcessType() == 2)
		{
			cs = &csExceptionStack;
			stack = ExceptionStack;
		}
		else
		{
			cs = &csExceptionStackTitle;
			stack = ExceptionStackTitle;
		}

		EnterCriticalSection(cs);

		pdmtd->DebugFlags |= DMFLAG_TRAPPED;

		// swap stack and trap
		fRet = DmTrapOnStack(ptf, pef, pcr, fSecondChance, NULL, stack);

		pdmtd->DebugFlags &= ~DMFLAG_TRAPPED;

		LeaveCriticalSection(cs);
	}
	else
		fRet = DmTrapHandlerImp(ptf, pef, pcr, fSecondChance, NULL);

	return fRet;
}

VOID LpTitleTerminateRoutine()
{
	// TODO: free up stuff used by titles (notifications, command handlers, etc)

	DwChangeExecState(DMN_EXEC_REBOOT_TITLE, FALSE, TRUE, FALSE);
}

VOID LpThreadNotificationRoutine(PEX_THREAD_REGISTRATION ThisRegistration, PKTHREAD Thread, BOOL Creating)
{
	DMTD *pdmtd;
	BOOL bBreak = FALSE;
	BOOL bStop = FALSE;

	if(Creating)
	{
		DMN_CREATETHREAD dmct;

		FInitThreadDebugData(Thread);
		pdmtd = (DMTD*)Thread->DebugMonitorData;

		if(Thread->CreateOptions & 0x100)
		{
			// Title launched, initial breakpoint
			if(g_dmGlobals.dwStopFlags & DMSTOP_TITLELAUNCH)
			{
				g_dmGlobals.dwStopFlags &= ~DMSTOP_TITLELAUNCH;
				bBreak = TRUE;
			}
			else
				DwChangeExecState(DMN_EXEC_START, FALSE, TRUE, FALSE);
		}

		dmct.StartAddress = Thread->StartAddress;
		dmct.ThreadId = (DWORD)Thread->ThreadId;
		dmct.ThreadNameAddress = NULL;

		bStop = g_dmGlobals.dwStopFlags & DMSTOP_CREATETHREAD;

		if(!pdmtd || !(pdmtd->DebugFlags & DMFLAG_DEBUGTHREAD))
		{
			if(bStop)
				PrepareToStop();

			FNotify(bStop ? (DM_CREATETHREAD | DM_STOPTHREAD) : DM_CREATETHREAD, (ULONG_PTR)&dmct);

			if(bStop)
				FStopAtException();

			if(bBreak)
				__emit(BREAKPOINT_BREAK);
		}
	}
	else
	{
#if 0
		pdmtd = DmGetThreadDmtd((DWORD)Thread->ThreadId);
#else
		pdmtd = (DMTD*)Thread->DebugMonitorData;
#endif
		KeEnterCriticalRegion();

		FNotify(DM_DESTROYTHREAD, (ULONG_PTR)Thread->ThreadId);

		if(pdmtd)
			DmFreeThreadData(pdmtd);

		KeLeaveCriticalRegion();
	}
}

BOOL FGetMemory(DWORD dwAddr, PBYTE pb)
{
	BYTE irql;
	BOOL fRet = TRUE;
	PBYTE pAddr;
	PDMBP bp;

	irql = KfRaiseIrql(0x7C);
	KeAcquireSpinLockAtRaisedIrql(&DmpBreakSpinLock);

	bp = FFindBreak((PVOID)dwAddr, FALSE);

	if(bp)
		dwAddr = (DWORD)bp->Code + (dwAddr & 3);

	pAddr = (PBYTE)PvDbgReadCheck((PVOID)dwAddr);
	if(pAddr)
		*pb = *pAddr;
	else
		fRet = FALSE;

	KeReleaseSpinLockFromRaisedIrql(&DmpBreakSpinLock);
	KfLowerIrql(irql);

	return fRet;
}

BOOL FSetMemory(DWORD dwAddr, BYTE b)
{
	BYTE irql;
	BOOL fRet = TRUE;
	PBYTE pAddr;
	HANDLE h;
	PDMBP bp;

	irql = KfRaiseIrql(0x7C);
	KeAcquireSpinLockAtRaisedIrql(&DmpBreakSpinLock);

	bp = FFindBreak((PVOID)dwAddr, FALSE);
	if(bp)
		dwAddr = (DWORD)bp->Code + (dwAddr & 3);

	pAddr = (PBYTE)PvDbgWriteCheck((PVOID)dwAddr, &h);

	if(pAddr)
	{
		*pAddr = b;

		KeSweepIcacheRange((PVOID)pAddr, 1);
		MmDbgReleaseAddress((PVOID)pAddr, &h);
	}
	else
		fRet = FALSE;

	KeReleaseSpinLockFromRaisedIrql(&DmpBreakSpinLock);
	KfLowerIrql(irql);

	return fRet;
}

// Breakpoints
DMHRAPI DmSetBreakpoint(PVOID addr)
{
	BYTE irql;
	HRESULT hr = XBDM_NOERR;
	PDMBP bp = (PDMBP)DmAllocatePoolTypeWithTag(sizeof(DMBP), 'dmbp', 2);

	irql = KfRaiseIrql(0x7C);
	KeAcquireSpinLockAtRaisedIrql(&DmpBreakSpinLock);

	if(FFindBreak(addr, FALSE))
		hr = E_FAIL;
	else
	{
		if(bp == NULL)
			hr = E_FAIL;
		else
		{
			InsertHeadList(&leBreaks, &bp->Link);

			bp->bEnabled = FALSE;
			bp->dwAddr = (DWORD)addr;
			DoEnableBreak(bp);
		}
	}

	KeReleaseSpinLockFromRaisedIrql(&DmpBreakSpinLock);
	KfLowerIrql(irql);

	if(FAILED(hr))
		DmFreePool(bp);

	return hr;
}

DMHRAPI DmRemoveBreakpoint(PVOID addr)
{
	BYTE irql;
	HRESULT hr = XBDM_NOERR;
	PDMBP bp;

	irql = KfRaiseIrql(0x7C);
	KeAcquireSpinLockAtRaisedIrql(&DmpBreakSpinLock);

	bp = FFindBreak(addr, FALSE);
	if(bp)
	{
		DoDisableBreak(bp);
		RemoveEntryList(&bp->Link);
	}
	else
		hr = E_FAIL;

	KeReleaseSpinLockFromRaisedIrql(&DmpBreakSpinLock);
	KfLowerIrql(irql);

	if(NT_SUCCESS(hr))
		DmFreePool(bp);

	return hr;
}

DMHRAPI DmIsBreakpoint(PVOID addr, LPDWORD dwType)
{
	if(FFindBreak(addr, TRUE))
		*dwType = DMBREAK_FIXED;
	else
	{
		// TODO: check hardware breakpoint
		*dwType = DMBREAK_NONE;
	}

	return XBDM_NOERR;
}

DMHRAPI DmSetInitialBreakpoint()
{
	if(dwExecState != DMN_EXEC_PENDING_TITLE
		&& dwExecState != DMN_EXEC_PENDING)
		return XBDM_NOTSTOPPED;

	g_dmGlobals.dwStopFlags |= DMSTOP_TITLELAUNCH;
	return XBDM_NOERR;
}

VOID DoDisableBreak(PDMBP bp)
{
	PVOID addr;
	HANDLE h;

	if(!bp->bEnabled)
		return;

	if(addr = PvDbgWriteCheck((PVOID)bp->dwAddr, &h))
	{
		*(LPDWORD)addr = *(LPDWORD)bp->Code;

		KeSweepIcacheRange((PVOID)bp->dwAddr, 4);
		MmDbgReleaseAddress(addr, &h);

		bp->bEnabled = FALSE;
	}
}

VOID DoEnableBreak(PDMBP bp)
{
	PVOID addr;
	HANDLE h;

	if(bp->bEnabled)
		return;

	if(addr = PvDbgWriteCheck((PVOID)bp->dwAddr, &h))
	{
		*(LPDWORD)bp->Code = *(LPDWORD)addr;
		*(LPDWORD)addr = BREAKPOINT_BREAK;

		KeSweepIcacheRange((PVOID)bp->dwAddr, 4);
		MmDbgReleaseAddress(addr, &h);

		bp->bEnabled = TRUE;
	}
}

DMHRAPI DmRemoveAllBreakpoints()
{
	BYTE irql;
	PLIST_ENTRY ple;
	PDMBP bp;

	irql = KfAcquireSpinLock(&DmpBreakSpinLock);

	ple = leBreaks.Flink;
	while(ple != &leBreaks)
	{
		bp = CONTAINING_RECORD(ple, DMBP, Link);
		ple = ple->Flink;

		DoDisableBreak(bp);
		RemoveEntryList(&bp->Link);
		DmFreePool(bp);
	}

	KfReleaseSpinLock(&DmpBreakSpinLock, irql);

	return E_FAIL;
}

BOOL FMatchDataBreak(PVOID addr)
{
	DWORD dw = (DWORD)addr;

	if(dw >= HardwareBreakpoint.dwAddr && dw < (HardwareBreakpoint.dwAddr + HardwareBreakpoint.dwSize))
		return TRUE;

	return FALSE;
}

ULONG_PTR DmpSetHardwareBreakpoint(DWORD Context)
{
#ifdef _DEBUG
	if(!Context)
		KeSetSpecialPurposeRegister(SPR_DABRX, 0); // break disabled

	KeSetSpecialPurposeRegister(SPR_DABR, Context); // set context

	if(Context)
		KeSetSpecialPurposeRegister(SPR_DABRX, 3); // break enabled
#else
	//if(!Context)
	//	HvPokeSPR(SPR_DABRX, 0); // break disabled

	//HvPokeSPR(SPR_DABR, Context); // set context

	//if(Context)
	//	HvPokeSPR(SPR_DABRX, 3); // break enabled
#endif
	return Context;
}

DMHRAPI DmSetDataBreakpoint(PVOID addr, DWORD dwType, DWORD dwSize)
{
	BYTE irql;
	DWORD dw = (DWORD)addr;
	DWORD dwMask = 0;
	HRESULT hr = XBDM_NOERR;

	irql = KfAcquireSpinLock(&DmpBreakSpinLock);

	if(dwType == DMBREAK_NONE)
	{
		HardwareBreakpoint.dwAddr = 0;
		HardwareBreakpoint.dwType = 0;
		HardwareBreakpoint.dwSize = 0;
	}
	else
	{
		if((dw & 3) + dwSize > 8)
			hr = E_INVALIDARG;
		else
		{
			if(dwType == DMBREAK_WRITE)
				dwMask = HWBP_WRITE;
			else if(dwType == DMBREAK_READ)
				dwMask = HWBP_READ;
			else if(dwType == DMBREAK_READWRITE)
				dwMask = HWBP_READWRITE;
			else if(dwType == DMBREAK_EXECUTE)
				dwMask = HWBP_EXECUTE;

			HardwareBreakpoint.dwType = dwMask;
			HardwareBreakpoint.dwAddr = dw;
			HardwareBreakpoint.dwSize = dwSize;

			dwMask |= (dw & 0xFFFFFFF8) | 4;
		}

		KeIpiGenericCall(DmpSetHardwareBreakpoint, (PDWORD)dwMask);
	}

	KfReleaseSpinLock(&DmpBreakSpinLock, irql);

	return hr;
}

PDMBP FFindBreak(PVOID addr, BOOL lock)
{
	BYTE irql;
	PDMBP bp = NULL, pbp;
	PLIST_ENTRY ple;

	if(lock)
	{
		irql = KfRaiseIrql(0x7C);
		KeAcquireSpinLockAtRaisedIrql(&DmpBreakSpinLock);
	}

	ple = leBreaks.Flink;
	while(ple != &leBreaks)
	{
		pbp = CONTAINING_RECORD(ple, DMBP, Link);
		ple = ple->Flink;

		if(pbp->dwAddr == ((DWORD)addr & 0xFFFFFFFC))
		{
			bp = pbp;
			break;
		}
	}

	if(lock)
	{
		KeReleaseSpinLockFromRaisedIrql(&DmpBreakSpinLock);
		KfLowerIrql(irql);
	}

	return bp;
}

BOOL FIsBreakpoint(PVOID addr)
{
	return (BOOL)FFindBreak(addr, TRUE);
}

const DWORD MMIORangeTable[] =
{
	0x7FC80000, 0x7FC9FFFF,
	0x7FD00000, 0x7FDFFFFF,
	0x7FEA0000, 0x7FEAFFFF,
	0x7FED0000, 0x7FEDFFFF,
	0x7FED0000, 0x7FEDFFFF,
	0x8FFF0000, 0x8FFF0FFF,
	0x8FFF1000, 0x8FFF1FFF,
	0x00000000, 0x00000000,
};
BOOL FIsMmIoAddress(PVOID addr)
{
	int i;

	for(i = 0;MMIORangeTable[i];i += 2)
	{
		if(((DWORD)addr > MMIORangeTable[i])
			&& ((DWORD)addr < MMIORangeTable[i + 1]))
			return TRUE;
	}

	return FALSE;
}
PVOID PvDbgWriteCheck(PVOID Address, PHANDLE Handle)
{
	PVOID addr;

#ifndef _DEBUG
	if(!FIsMmIoAddress(Address) && MmIsAddressValid(Address))
		addr = Address;
	else
		addr = NULL;
#else
	if(addr = MmDbgWriteCheck(Address, Handle))
	{
		if(FIsMmIoAddress(addr))
		{
			MmDbgReleaseAddress(addr, Handle);
			addr = NULL;
		}
	}
#endif

	return addr;
}
PVOID PvDbgReadCheck(PVOID Address)
{
	PVOID addr;

	if(addr = MmDbgReadCheck(Address))
	{
		if(FIsMmIoAddress(addr))
			addr = NULL;
	}

	return addr;
}

#define MAKE_CONTEXT(x, y) { #x, y, (DWORD)&((XCONTEXT*)0)->##x, sizeof(((XCONTEXT*)0)->##x) },
#define MV(a) \
	MAKE_CONTEXT(a##0, CONTEXT_VECTOR) MAKE_CONTEXT(a##1, CONTEXT_VECTOR) MAKE_CONTEXT(a##2, CONTEXT_VECTOR) \
	MAKE_CONTEXT(a##3, CONTEXT_VECTOR) MAKE_CONTEXT(a##4, CONTEXT_VECTOR) MAKE_CONTEXT(a##5, CONTEXT_VECTOR) \
	MAKE_CONTEXT(a##6, CONTEXT_VECTOR) MAKE_CONTEXT(a##7, CONTEXT_VECTOR) MAKE_CONTEXT(a##8, CONTEXT_VECTOR) \
	MAKE_CONTEXT(a##9, CONTEXT_VECTOR)


DMREG rgbregs[] =
{
	MAKE_CONTEXT(Msr, CONTEXT_CONTROL)
	MAKE_CONTEXT(Iar, CONTEXT_CONTROL)
	MAKE_CONTEXT(Lr, CONTEXT_CONTROL)
	MAKE_CONTEXT(Ctr, CONTEXT_CONTROL)

	MAKE_CONTEXT(Gpr0, CONTEXT_INTEGER)
	MAKE_CONTEXT(Gpr1, CONTEXT_INTEGER)
	MAKE_CONTEXT(Gpr2, CONTEXT_INTEGER)
	MAKE_CONTEXT(Gpr3, CONTEXT_INTEGER)
	MAKE_CONTEXT(Gpr4, CONTEXT_INTEGER)
	MAKE_CONTEXT(Gpr5, CONTEXT_INTEGER)
	MAKE_CONTEXT(Gpr6, CONTEXT_INTEGER)
	MAKE_CONTEXT(Gpr7, CONTEXT_INTEGER)
	MAKE_CONTEXT(Gpr8, CONTEXT_INTEGER)
	MAKE_CONTEXT(Gpr9, CONTEXT_INTEGER)
	MAKE_CONTEXT(Gpr10, CONTEXT_INTEGER)
	MAKE_CONTEXT(Gpr11, CONTEXT_INTEGER)
	MAKE_CONTEXT(Gpr12, CONTEXT_INTEGER)
	MAKE_CONTEXT(Gpr13, CONTEXT_INTEGER)
	MAKE_CONTEXT(Gpr14, CONTEXT_INTEGER)
	MAKE_CONTEXT(Gpr15, CONTEXT_INTEGER)
	MAKE_CONTEXT(Gpr16, CONTEXT_INTEGER)
	MAKE_CONTEXT(Gpr17, CONTEXT_INTEGER)
	MAKE_CONTEXT(Gpr18, CONTEXT_INTEGER)
	MAKE_CONTEXT(Gpr19, CONTEXT_INTEGER)
	MAKE_CONTEXT(Gpr20, CONTEXT_INTEGER)
	MAKE_CONTEXT(Gpr21, CONTEXT_INTEGER)
	MAKE_CONTEXT(Gpr22, CONTEXT_INTEGER)
	MAKE_CONTEXT(Gpr23, CONTEXT_INTEGER)
	MAKE_CONTEXT(Gpr24, CONTEXT_INTEGER)
	MAKE_CONTEXT(Gpr25, CONTEXT_INTEGER)
	MAKE_CONTEXT(Gpr26, CONTEXT_INTEGER)
	MAKE_CONTEXT(Gpr27, CONTEXT_INTEGER)
	MAKE_CONTEXT(Gpr28, CONTEXT_INTEGER)
	MAKE_CONTEXT(Gpr29, CONTEXT_INTEGER)
	MAKE_CONTEXT(Gpr30, CONTEXT_INTEGER)
	MAKE_CONTEXT(Gpr31, CONTEXT_INTEGER)
	MAKE_CONTEXT(Cr, CONTEXT_INTEGER)
	MAKE_CONTEXT(Xer, CONTEXT_INTEGER)

	MAKE_CONTEXT(Fpscr, CONTEXT_FLOATING_POINT)
	MAKE_CONTEXT(Fpr0, CONTEXT_FLOATING_POINT)
	MAKE_CONTEXT(Fpr1, CONTEXT_FLOATING_POINT)
	MAKE_CONTEXT(Fpr2, CONTEXT_FLOATING_POINT)
	MAKE_CONTEXT(Fpr3, CONTEXT_FLOATING_POINT)
	MAKE_CONTEXT(Fpr4, CONTEXT_FLOATING_POINT)
	MAKE_CONTEXT(Fpr5, CONTEXT_FLOATING_POINT)
	MAKE_CONTEXT(Fpr6, CONTEXT_FLOATING_POINT)
	MAKE_CONTEXT(Fpr7, CONTEXT_FLOATING_POINT)
	MAKE_CONTEXT(Fpr8, CONTEXT_FLOATING_POINT)
	MAKE_CONTEXT(Fpr9, CONTEXT_FLOATING_POINT)
	MAKE_CONTEXT(Fpr10, CONTEXT_FLOATING_POINT)
	MAKE_CONTEXT(Fpr11, CONTEXT_FLOATING_POINT)
	MAKE_CONTEXT(Fpr12, CONTEXT_FLOATING_POINT)
	MAKE_CONTEXT(Fpr13, CONTEXT_FLOATING_POINT)
	MAKE_CONTEXT(Fpr14, CONTEXT_FLOATING_POINT)
	MAKE_CONTEXT(Fpr15, CONTEXT_FLOATING_POINT)
	MAKE_CONTEXT(Fpr16, CONTEXT_FLOATING_POINT)
	MAKE_CONTEXT(Fpr17, CONTEXT_FLOATING_POINT)
	MAKE_CONTEXT(Fpr18, CONTEXT_FLOATING_POINT)
	MAKE_CONTEXT(Fpr19, CONTEXT_FLOATING_POINT)
	MAKE_CONTEXT(Fpr20, CONTEXT_FLOATING_POINT)
	MAKE_CONTEXT(Fpr21, CONTEXT_FLOATING_POINT)
	MAKE_CONTEXT(Fpr22, CONTEXT_FLOATING_POINT)
	MAKE_CONTEXT(Fpr23, CONTEXT_FLOATING_POINT)
	MAKE_CONTEXT(Fpr24, CONTEXT_FLOATING_POINT)
	MAKE_CONTEXT(Fpr25, CONTEXT_FLOATING_POINT)
	MAKE_CONTEXT(Fpr26, CONTEXT_FLOATING_POINT)
	MAKE_CONTEXT(Fpr27, CONTEXT_FLOATING_POINT)
	MAKE_CONTEXT(Fpr28, CONTEXT_FLOATING_POINT)
	MAKE_CONTEXT(Fpr29, CONTEXT_FLOATING_POINT)
	MAKE_CONTEXT(Fpr30, CONTEXT_FLOATING_POINT)
	MAKE_CONTEXT(Fpr31, CONTEXT_FLOATING_POINT)
	
	MAKE_CONTEXT(Vscr, CONTEXT_VECTOR)
	MV(Vr)
	MV(Vr1)
	MV(Vr2)
	MV(Vr3)
	MV(Vr4)
	MV(Vr5)
	MV(Vr6)
	MV(Vr7)
	MV(Vr8)
	MV(Vr9)
	MV(Vr10)
	MV(Vr11)
	MAKE_CONTEXT(Vr120, CONTEXT_VECTOR)
	MAKE_CONTEXT(Vr121, CONTEXT_VECTOR)
	MAKE_CONTEXT(Vr122, CONTEXT_VECTOR)
	MAKE_CONTEXT(Vr123, CONTEXT_VECTOR)
	MAKE_CONTEXT(Vr124, CONTEXT_VECTOR)
	MAKE_CONTEXT(Vr125, CONTEXT_VECTOR)
	MAKE_CONTEXT(Vr126, CONTEXT_VECTOR)
	MAKE_CONTEXT(Vr127, CONTEXT_VECTOR)
	{ 0, 0, 0}
};
int cchregs = (sizeof(rgbregs) / sizeof(DMREG));

#undef MV
#undef MAKE_CONTEXT