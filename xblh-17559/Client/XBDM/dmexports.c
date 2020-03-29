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

DMHRAPI DmStub()
{
	return E_FAIL;
}

PVOID __stdcall DmAllocatePool(ULONG cb)
{
	return ExAllocatePoolWithTag(cb, 'xbdm');
}

PVOID __stdcall DmAllocatePoolWithTag(ULONG cb, ULONG tag)
{
	return ExAllocatePoolWithTag(cb, tag);
}

PVOID DmAllocatePoolTypeWithTag(ULONG cb, ULONG tag, ULONG type)
{
	return ExAllocatePoolTypeWithTag(cb, tag, (POOL_TYPE)type);
}

VOID __stdcall DmFreePool(PVOID p)
{
	ExFreePool(p);
}

DMHRAPI DmGetXboxName(LPSTR szName, LPDWORD pcch)
{
	DWORD i;

	if(!szName || !pcch)
		return E_INVALIDARG;

	if(strlen(g_dmGlobals.rgchDbgName) >= *pcch)
		return XBDM_BUFFER_TOO_SMALL;

	for(i = 0;i < *pcch;i++)
	{
		szName[i] = g_dmGlobals.rgchDbgName[i];

		if(g_dmGlobals.rgchDbgName[i] == 0)
			break;
	}

	if(g_dmGlobals.rgchDbgName[i])
		return XBDM_BUFFER_TOO_SMALL;
	else
		return XBDM_NOERR;
}

DMHRAPI DmGetXbeInfo(LPCSTR szName, PDM_XBE pdxbe)
{
	return DmGetXbeInfoEx(szName, pdxbe, 0);
}

DMHRAPI DmGetXbeInfoEx(LPCSTR szName, PDM_XBE pdxbe, DWORD dwFlags)
{
	if(!pdxbe)
		return E_INVALIDARG;

	if(dwFlags & DM_XBEONDISKONLY)
		return XBDM_NOSUCHFILE;

	ZeroMemory(pdxbe, sizeof(DM_XBE));
	
	if(ExLoadedImageName)
		strcpy(pdxbe->LaunchPath, ExLoadedImageName);

	pdxbe->CheckSum = 0;
	pdxbe->StackSize = 0;
	pdxbe->TimeStamp = 0;

	return XBDM_NOERR;
}

DMHRAPI DmGetMemory(LPCVOID lpbAddr, DWORD cb, LPVOID lpbBuf,
    LPDWORD pcbRet)
{
	DWORD page;
	DWORD addr;
	LPCSTR lpBuf = (LPCSTR)lpbBuf;
	LPSTR lpAddr = (LPSTR)lpbAddr;
	BOOL pageValid = TRUE;

	if(!lpbBuf)
		return E_INVALIDARG;

	addr = (DWORD)lpbAddr;
	page = addr + 0x1000;

	while(pageValid && (addr < (DWORD)lpbAddr + cb))
	{
		if((addr ^ page) & 0xFFFFF000)
		{
			page = addr & 0xFFFFF000;
			pageValid = MmIsAddressValid((LPVOID)addr);
		}

		if(pageValid)
			pageValid = FGetMemory(addr, (PBYTE)lpBuf);

		lpBuf++;
		addr++;
	}

	if(!pageValid)
		return XBDM_MEMUNMAPPED;

	return XBDM_NOERR;
}

DMHRAPI DmSetMemory(LPVOID lpbAddr, DWORD cb, LPCVOID lpbBuf,
    LPDWORD pcbRet)
{
	DWORD page;
	DWORD addr;
	LPCSTR lpBuf = (LPCSTR)lpbBuf;
	LPSTR lpAddr = (LPSTR)lpbAddr;
	BOOL pageValid = TRUE;

	if(!lpbBuf)
		return E_INVALIDARG;

	addr = (DWORD)lpbAddr;
	page = addr + 0x1000;

	while(pageValid && (addr < (DWORD)lpbAddr + cb))
	{
		if((addr ^ page) & 0xFFFFF000)
		{
			page = addr & 0xFFFFF000;
			pageValid = MmIsAddressValid((LPVOID)addr);
		}

		if(pageValid)
			pageValid = FSetMemory(addr, *lpBuf);

		lpBuf++;
		addr++;
	}

	if(!pageValid)
		return XBDM_MEMUNMAPPED;

	return XBDM_NOERR;
}

typedef struct _DM_WALK_MODULES
{
	LIST_ENTRY Link;
	DMN_MODLOAD_EX pdml;
} DM_WALK_MODULES;

DWORD g_ = 0;
DMHRAPI DmWalkLoadedModules(PDM_WALK_MODULES *ppdwm, PDMN_MODLOAD pdml)
{
	HRESULT hr;
	DMN_MODLOAD_EX dml;

	dml.SizeOfStruct = sizeof(DMN_MODLOAD_EX);

	hr = DmWalkLoadedModulesEx(ppdwm, &dml);

	if(pdml)
		memcpy(pdml, dml.Name, sizeof(DMN_MODLOAD));

	return hr;
}

DMHRAPI DmWalkLoadedModulesEx(PDM_WALK_MODULES *ppdwm, PDMN_MODLOAD_EX pdml)
{
	BYTE irql;
	PLIST_ENTRY plemod;
	PLIST_ENTRY ple = (PLIST_ENTRY)*ppdwm;
	PLDR_DATA_TABLE_ENTRY pldte;
	PDM_WALK_MODULES pdwm;
	HRESULT hr = XBDM_NOERR;
	PIMAGE_NT_HEADERS pinh;

	if(!ppdwm || !pdml)
		return E_INVALIDARG;

	if(ple == NULL)
	{
		// Initialize the list entry
		ple = (PLIST_ENTRY)DmAllocatePoolWithTag(sizeof(LIST_ENTRY), 'dmwm');

		if(!ple)
			return E_OUTOFMEMORY;

		InitializeListHead(ple);

		*ppdwm = (PDM_WALK_MODULES)ple;

		irql = KfAcquireSpinLock(g_dmDebug.XexLoadedModuleListLock);

		plemod = g_dmDebug.PsLoadedModuleList->Flink;
		while(plemod != g_dmDebug.PsLoadedModuleList)
		{
			pldte = CONTAINING_RECORD(plemod, LDR_DATA_TABLE_ENTRY, InLoadOrderLinks);
			plemod = plemod->Flink;

			pdwm = (PDM_WALK_MODULES)DmAllocatePoolWithTag(sizeof(DM_WALK_MODULES), 'dmwm');

			if(!pdwm)
			{
				hr = E_OUTOFMEMORY;
				break;
			}

			pinh = RtlImageNtHeader(pldte->ImageBase);

			ZeroMemory(pdwm, sizeof(DM_WALK_MODULES));

			InsertTailList(ple, &pdwm->Link);

			pdwm->pdml.SizeOfStruct = sizeof(DMN_MODLOAD_EX);

			// Fetch ALL the info
			pdwm->pdml.BaseAddress = pldte->ImageBase;
			pdwm->pdml.CheckSum = pldte->CheckSum;
			pdwm->pdml.Flags = 0;
			if(!(pinh->FileHeader.Characteristics & 0x20))
				pdwm->pdml.Flags |= DMN_MODFLAG_TLS;

			WideCharToMultiByte(CP_UTF8, 0, pldte->BaseDllName.Buffer, -1, pdwm->pdml.Name, MAX_PATH, NULL, NULL);
			pdwm->pdml.OriginalSize = _byteswap_ulong(pinh->OptionalHeader.SizeOfImage);
			pdwm->pdml.PDataAddress = RtlImageDirectoryEntryToData(pldte->NtHeadersBase, TRUE, 3, &pdwm->pdml.PDataSize);
			pdwm->pdml.Size = pldte->SizeOfNtImage;
			pdwm->pdml.ThreadId = 0;//(DWORD)PsGetCurrentThread()->ThreadId;
			pdwm->pdml.TimeStamp = pldte->TimeDateStamp;
		}

		KfReleaseSpinLock(g_dmDebug.XexLoadedModuleListLock, irql);

		if(FAILED(hr))
		{
			DmCloseLoadedModules(*ppdwm);
			*ppdwm = NULL;
		}
	}

	if(NT_SUCCESS(hr))
	{
		// Take an entry, copy the data, remove from list, free the memory
		ple = ((PLIST_ENTRY)*ppdwm)->Flink;

		if(ple->Flink == ple->Blink)
			hr = XBDM_ENDOFLIST;

		memcpy(pdml, &CONTAINING_RECORD(ple, DM_WALK_MODULES, Link)->pdml, sizeof(DMN_MODLOAD_EX));

		ple->Flink->Blink = ple->Blink;
		ple->Blink->Flink = ple->Flink;

		DmFreePool(CONTAINING_RECORD(ple, DM_WALK_MODULES, Link));
	}

	return hr;
}

DMHRAPI DmCloseLoadedModules(PDM_WALK_MODULES pdwm)
{
	PLIST_ENTRY ple;
	PDM_WALK_MODULES pdwm2;

	if(!pdwm)
		return E_INVALIDARG;

	ple = ((PLIST_ENTRY)pdwm)->Flink;
	while(ple != (PLIST_ENTRY)pdwm)
	{
		pdwm2 = CONTAINING_RECORD(ple, DM_WALK_MODULES, Link);

		ple->Flink->Blink = ple->Blink;
		ple->Blink->Flink = ple->Flink;
		ple = ple->Flink;

		DmFreePool(pdwm2);
	}

	DmFreePool(pdwm);

	return XBDM_NOERR;
}
typedef struct _DM_WALK_MODSECT
{
	LIST_ENTRY Link;
	DMN_SECTIONLOAD pdml;
} DM_WALK_MODSECT;
DMHRAPI DmWalkModuleSections(PDM_WALK_MODSECT *ppWalkModSect, LPCSTR lzModName, PDMN_SECTIONLOAD pSecLoad)
{
	BYTE irql;
	PLIST_ENTRY ple = (PLIST_ENTRY)*ppWalkModSect;
	PLDR_DATA_TABLE_ENTRY pldte;
	HRESULT hr = XBDM_NOERR;
	PIMAGE_SECTION_HEADER pish;
	DWORD dw;
	int i;

	if(!ppWalkModSect || !pSecLoad)
		return E_INVALIDARG;

	if(ple == NULL)
	{
		// Initialize the list entry
		ple = (PLIST_ENTRY)DmAllocatePoolWithTag(sizeof(LIST_ENTRY), 'dmwm');

		if(!ple)
			return E_OUTOFMEMORY;

		InitializeListHead(ple);

		*ppWalkModSect = (PDM_WALK_MODSECT)ple;

		irql = KfAcquireSpinLock(g_dmDebug.XexLoadedModuleListLock);
		
		if(NT_SUCCESS(hr = FGetModuleHandle(lzModName, &pldte, FALSE)))
		{
			pish = (PIMAGE_SECTION_HEADER)(RtlImageNtHeader(pldte->ImageBase) + 1);

			for(i = 0;pish->Name[0];i++)
			{
				PDM_WALK_MODSECT pdmwm = (PDM_WALK_MODSECT)DmAllocatePoolWithTag(sizeof(DM_WALK_MODSECT), 'dmwm');
				if(!pdmwm)
				{
					hr = E_OUTOFMEMORY;
					break;
				}

				ZeroMemory(pdmwm, sizeof(DM_WALK_MODSECT));

				InsertTailList(ple, &pdmwm->Link);

				pdmwm->pdml.Index = i + 1;
				memcpy(pdmwm->pdml.Name, pish->Name, 8);
				pdmwm->pdml.BaseAddress = (PVOID)(_byteswap_ulong(pish->VirtualAddress) + (DWORD)pldte->ImageBase);
				pdmwm->pdml.Size = _byteswap_ulong(pish->Misc.VirtualSize);
				pdmwm->pdml.Flags = 0;
				dw = _byteswap_ulong(pish->Characteristics);
				if(dw & 0x40000000)
					pdmwm->pdml.Flags |= DMN_SECFLAG_READABLE;
				if(dw & 0x80000000)
					pdmwm->pdml.Flags |= DMN_SECFLAG_WRITEABLE;
				if(dw & 0x20000000)
					pdmwm->pdml.Flags |= DMN_SECFLAG_EXECUTABLE;
				if(dw & 0x80)
					pdmwm->pdml.Flags |= DMN_SECFLAG_UNINITIALIZED;

				pish++;
			}
		}
		KfReleaseSpinLock(g_dmDebug.XexLoadedModuleListLock, irql);

		if(FAILED(hr))
		{
			DmCloseModuleSections(*ppWalkModSect);
			*ppWalkModSect = FALSE;
		}
	}

	if(NT_SUCCESS(hr))
	{
		// Take an entry, copy the data, remove from list, free the memory
		ple = ((PLIST_ENTRY)*ppWalkModSect)->Flink;

		if(ple->Flink == ple->Blink)
			hr = XBDM_ENDOFLIST;

		memcpy(pSecLoad, &CONTAINING_RECORD(ple, DM_WALK_MODSECT, Link)->pdml, sizeof(DMN_SECTIONLOAD));

		ple->Flink->Blink = ple->Blink;
		ple->Blink->Flink = ple->Flink;

		DmFreePool(CONTAINING_RECORD(ple, DM_WALK_MODULES, Link));
	}

	return hr;
}

DMHRAPI DmCloseModuleSections(PDM_WALK_MODSECT pWalkMod)
{
	PLIST_ENTRY ple;
	PDM_WALK_MODSECT pdwm2;

	if(!pWalkMod)
		return E_INVALIDARG;

	ple = ((PLIST_ENTRY)pWalkMod)->Flink;
	while(ple != (PLIST_ENTRY)pWalkMod)
	{
		pdwm2 = CONTAINING_RECORD(ple, DM_WALK_MODSECT, Link);

		ple->Flink->Blink = ple->Blink;
		ple->Blink->Flink = ple->Flink;
		ple = ple->Flink;

		DmFreePool(pdwm2);
	}

	DmFreePool(pWalkMod);

	return XBDM_NOERR;
}

DMHRAPI DmReboot(DWORD dwFlags)
{
	return DmRebootEx(dwFlags, NULL, NULL, NULL);
}

ULONG __stdcall DmBootThread(LPVOID param)
{
	XamLoaderLaunchTitleEx(g_dmGlobals.szBootTitle, g_dmGlobals.szBootPath, g_dmGlobals.szBootCmdLine, 0);
	return 0;
}

BOOL FWouldSystemCrash()
{
	BYTE irql;
	PKTHREAD pthr;
	PLIST_ENTRY ple;
	BOOL fRet = FALSE;
	DMTD *pdmtd;
	int i;

	irql = KfAcquireSpinLock(g_dmDebug.KeSystemProcess);

	ple = g_dmDebug.KeSystemProcess->ThreadListHead.Flink;
	
	for(i = 0;i < 2;i++)
	{
		while(ple != &g_dmDebug.KeSystemProcess->ThreadListHead && ple != &g_dmDebug.KeTitleProcess->ThreadListHead)
		{
			pthr = CONTAINING_RECORD(ple, KTHREAD, ThreadListEntry);
			ple = ple->Flink;

			pdmtd = (DMTD*)pthr->DebugMonitorData;

			if(pdmtd &&
				(pdmtd->StopReason == DM_EXCEPTION
				|| pdmtd->StopReason == DM_BREAK
				|| pdmtd->StopReason == DM_SINGLESTEP
				|| pdmtd->StopReason == DM_DATABREAK
				|| pdmtd->StopReason == DM_ASSERT
				|| pdmtd->StopReason == DM_RIP))
			{
				fRet = TRUE;
			}
		}

		ple = g_dmDebug.KeTitleProcess->ThreadListHead.Flink;
	}

	KfReleaseSpinLock(g_dmDebug.KeSystemProcess, irql);

	return fRet;
}

DMHRAPI DmRebootEx(DWORD dwFlags, LPCSTR szImagePath, LPCSTR szMediaPath, LPCSTR szDbgCmdLine)
{
	char sz[MAX_PATH];
	char szM[MAX_PATH];
	int i, j;
#ifdef _DEBUG
	HANDLE h;
#endif

	if((dwFlags & DMBOOT_WAIT) && (dwFlags & DMBOOT_STOP))
		return E_INVALIDARG;

	if(FWouldSystemCrash())	
	{
		DwChangeExecState(DMN_EXEC_REBOOT, FALSE, TRUE, FALSE);
		FStopServ();
		if(KeGetCurrentIrql() >= DISPATCH_LEVEL)
		{
			HalReturnToFirmware(1);
		}
		HalReturnToFirmware(6);
	}

	g_dmGlobals.dwBootFlags = dwFlags;

	if(szImagePath)
		strcpy_s(g_dmGlobals.szBootTitle, sizeof(g_dmGlobals.szBootTitle), szImagePath);
	if(szMediaPath)
		strcpy_s(g_dmGlobals.szBootPath, sizeof(g_dmGlobals.szBootPath), szMediaPath);
	if(szDbgCmdLine)
		strcpy_s(g_dmGlobals.szBootCmdLine, sizeof(g_dmGlobals.szBootCmdLine), szDbgCmdLine);

	if(dwFlags & DMBOOT_COLD)
	{
		DwChangeExecState(DMN_EXEC_REBOOT, FALSE, TRUE, FALSE);
		FStopServ();

		FWriteGlobals();

		if(KeGetCurrentIrql() >= DISPATCH_LEVEL)
			HalReturnToFirmware(1);

		HalReturnToFirmware(6);
	}

	if(dwFlags & DMBOOT_TITLE)
	{
		szImagePath = sz;
		szMediaPath = szM;

		if(ExLoadedImageName)
		{
			strcpy_s(sz, sizeof(sz), ExLoadedImageName);
			strcpy_s(szM, sizeof(szM), sz);

			// Parse out the directory
			for(i = 0, j = 0;szM[i];i++)
				if(szM[i] == '\\' || szM[i] == '//')
					j = i;
			szM[j] = 0;
		}
		else
			return E_FAIL;
	}

	// To make sure we can't get stuck
	DwChangeExecState(DMN_EXEC_START, TRUE, FALSE, FALSE);

	DwChangeExecState(DMN_EXEC_REBOOT_TITLE, FALSE, TRUE, FALSE);

#ifdef _DEBUG
	// DEVKIT
	ExCreateThread(&h, 0, 0, 0, DmBootThread, 0, 0x400);
	SetThreadPriority(h, THREAD_PRIORITY_TIME_CRITICAL);
	CloseHandle(h);

	Sleep(200);
	
#else
	XamLoaderLaunchTitleEx(szImagePath, szMediaPath, szDbgCmdLine, 0);
#endif

	if(KeGetCurrentProcessType() == 1)
		ExTerminateThread(-1); // kill off this thread

	return XBDM_NOERR;
}

LPCSTR ESysSymbolicLinkName =		"\\system??\\E:";
LPCSTR ESymbolicLinkName =			"\\??\\E:";
LPCSTR DEVKITSymbolicLinkName =		"\\??\\DEVKIT:";
LPCSTR DEVKITSysSymbolicLinkName =	"\\system??\\DEVKIT:";
LPCSTR DevkitDeviceName =			"\\Device\\Harddisk0\\Partition1\\DEVKIT";

DMHRAPI DmMapDevkitDrive()
{
	ANSI_STRING symName, devName;
	NTSTATUS st;

	DWORD b = KeGetCurrentProcessType();

	if(b == 2)
		RtlInitAnsiString(&symName, ESysSymbolicLinkName);
	else
		RtlInitAnsiString(&symName, ESymbolicLinkName);

	RtlInitAnsiString(&devName, DevkitDeviceName);

	st = ObCreateSymbolicLink(&symName, &devName);

	if(st < STATUS_OBJECT_NAME_COLLISION && st < 0)
		return (RtlNtStatusToDosError(st) & 0xFFFF) | 0x80070000;

	if(b == 2)
		RtlInitAnsiString(&symName, DEVKITSysSymbolicLinkName);
	else
		RtlInitAnsiString(&symName, DEVKITSymbolicLinkName);

	st = ObCreateSymbolicLink(&symName, &devName);

	if(st < STATUS_OBJECT_NAME_COLLISION && st < 0)
		return (RtlNtStatusToDosError(st) & 0xFFFF) | 0x80070000;

	return S_OK;
}

DMHRAPI DmSetDumpMode(DWORD dwDumpMode)
{
	if(dwDumpMode > DM_DUMPMODE_DISABLED)
		return E_INVALIDARG;

	g_dmGlobals.dwDumpMode = dwDumpMode;
	g_dmGlobals.bDirty = TRUE;
	
	return XBDM_NOERR;
}

DMHRAPI DmGetDumpMode(DWORD * pdwDumpMode)
{
	if(!pdwDumpMode)
		return E_INVALIDARG;

	*pdwDumpMode = g_dmGlobals.dwDumpMode;

	return XBDM_NOERR;
}

HRESULT FGetModuleHandle(LPCSTR ModuleName, PLDR_DATA_TABLE_ENTRY *ppdte, BOOL bSpinLock)
{
	BYTE irql;
	PLDR_DATA_TABLE_ENTRY pdte;
	PLIST_ENTRY ple;
	HRESULT hr = XBDM_NOSUCHFILE;
	char sz[MAX_PATH];
	int i;

	if(!ppdte || !ModuleName)
		return E_INVALIDARG;

	*ppdte = NULL;

	if(bSpinLock)
		irql = KfAcquireSpinLock(g_dmDebug.XexLoadedModuleListLock);

	ple = g_dmDebug.PsLoadedModuleList->Flink;
	while(ple != g_dmDebug.PsLoadedModuleList)
	{
		pdte = CONTAINING_RECORD(ple, LDR_DATA_TABLE_ENTRY, InLoadOrderLinks);
		ple = ple->Flink;

		sz[0] = 0;
		wcstombs_s(&i, sz, sizeof(sz), pdte->BaseDllName.Buffer, pdte->BaseDllName.Length);

		if(!strnicmp(sz, ModuleName, sizeof(sz)))
		{
			*ppdte = pdte;
			hr = XBDM_NOERR;
			break;
		}
	}

	if(bSpinLock)
		KfReleaseSpinLock(g_dmDebug.XexLoadedModuleListLock, irql);

	return hr;
}

DMHRAPI DmGetThreadContext(DWORD dwThreadId, PXCONTEXT pdmcr)
{
	PKTHREAD pthr;
	BYTE irql;
	DMTD *pdmtd;
	HRESULT hr;
	char *stack;
	DWORD flags;

	if(!pdmcr)
		return E_INVALIDARG;

	if(FAILED(ObLookupAnyThreadByThreadId(dwThreadId, &pthr)))
		return XBDM_NOTHREAD;

	irql = KfAcquireSpinLock(&pthr->Process->ThreadListLock);

	flags = pdmcr->ContextFlags;
	ZeroMemory(pdmcr, sizeof(XCONTEXT));

	pdmtd = (DMTD*)pthr->DebugMonitorData;

	if(pdmtd && !(pdmtd->DebugFlags & DMFLAG_DEBUGTHREAD))
	{
		stack = (char*)pthr->KernelStack;

		if(pdmtd->Context)
		{
			if(flags & CONTEXT_INTEGER)
			{
				pdmcr->ContextFlags |= CONTEXT_INTEGER;

				memcpy(&pdmcr->Gpr0, &pdmtd->Context->Gpr0, ((char*)&pdmcr->Xer - (char*)&pdmcr->Gpr0));
			}
			if(flags & CONTEXT_CONTROL)
			{
				pdmcr->ContextFlags |= CONTEXT_CONTROL;
				
				memcpy(&pdmcr->Msr, &pdmtd->Context->Msr, ((char*)&pdmcr->Ctr - (char*)&pdmcr->Msr));
			}
			if(flags & CONTEXT_FLOATING_POINT)
			{
				pdmcr->ContextFlags |= CONTEXT_FLOATING_POINT;
				
				memcpy(&pdmcr->Fpscr, &pdmtd->Context->Fpscr, ((char*)&pdmcr->Fill - (char*)&pdmcr->Fpscr));
			}
			if(flags & CONTEXT_VECTOR)
			{
				pdmcr->ContextFlags |= CONTEXT_VECTOR;
				
				memcpy(&pdmcr->Vscr[0], &pdmtd->Context->Vscr[0], ((char*)&pdmcr->Vr127[3] - (char*)&pdmcr->Vscr[0]));
			}
		}
		else
		{
			if(flags & CONTEXT_INTEGER)
			{
				pdmcr->ContextFlags |= CONTEXT_INTEGER;

				memset(&pdmcr->Gpr0, 0xFF, 0x70);
				memcpy(&pdmcr->Gpr14, stack + 0x50, 0x90);
				pdmcr->Xer = -1;
				pdmcr->Cr = ((LPDWORD)stack)[0x38];
				pdmcr->Gpr1 = (DWORD)stack;
			}
			if(flags & CONTEXT_CONTROL)
			{
				pdmcr->ContextFlags |= CONTEXT_CONTROL;

				pdmcr->Msr = -1;
				pdmcr->Iar = ((LPDWORD)stack)[0x39];
				pdmcr->Ctr = -1;
				pdmcr->Lr = ((LPDWORD)stack)[0x3A];
			}
		}

		hr = XBDM_NOERR;
	}
	else
		hr = XBDM_NOTHREAD;

	KfReleaseSpinLock(&pthr->Process->ThreadListLock, irql);

	ObDereferenceObject(pthr);

	return hr;
}

DMHRAPI DmSetThreadContext(DWORD dwThreadId, PXCONTEXT pdmcr)
{
	BYTE irql;
	PKTHREAD pthr;
	DMTD *pdmtd;
	HRESULT hr = XBDM_NOERR;

	if(!pdmcr)
		return E_FAIL;

	if(FAILED(ObLookupAnyThreadByThreadId(dwThreadId, &pthr)))
		return XBDM_NOTHREAD;

	irql = KfAcquireSpinLock(&pthr->Process->ThreadListLock);

	pdmtd = (DMTD*)pthr->DebugMonitorData;

	if(pdmtd && !(pdmtd->DebugFlags & DMFLAG_DEBUGTHREAD))
	{
		if(pdmtd->Context)
		{
			if(pdmcr->ContextFlags & CONTEXT_INTEGER)
				memcpy(&pdmtd->Context->Gpr0, &pdmcr->Gpr0, ((char*)&pdmcr->Xer - (char*)&pdmcr->Gpr0));
			if(pdmcr->ContextFlags & CONTEXT_CONTROL)
			{
				if(pdmcr->Msr & 0x400) // Just a quick fix
					pdmtd->DebugFlags |= DMFLAG_SINGLESTEP;

				memcpy(&pdmtd->Context->Msr, &pdmcr->Msr, ((char*)&pdmcr->Ctr - (char*)&pdmcr->Msr));
			}
			if(pdmcr->ContextFlags & CONTEXT_FLOATING_POINT)
				memcpy(&pdmtd->Context->Fpscr, &pdmcr->Fpscr, ((char*)&pdmcr->Fill - (char*)&pdmcr->Fpscr));
			if(pdmcr->ContextFlags & CONTEXT_VECTOR)
				memcpy(&pdmtd->Context->Vscr[0], &pdmcr->Vscr[0], ((char*)&pdmcr->Vr127[3] - (char*)&pdmcr->Vscr[0]));
		}
		else
			hr = XBDM_NOTSTOPPED;
	}

	KfReleaseSpinLock(&pthr->Process->ThreadListLock, irql);
	ObDereferenceObject(pthr);

	return hr;
}

DMHRAPI DmGetThreadList(LPDWORD rgdwThreads, LPDWORD pcThreads)
{
	BYTE irql;
	PLIST_ENTRY ple;
	PKTHREAD pthr;
	HRESULT hr = XBDM_NOERR;
	DWORD cchThreads = 0;
	DMTD *pdmtd;
	int i;

	if(!rgdwThreads || !pcThreads)
		return E_FAIL;

	if(*pcThreads == 0)
		return XBDM_BUFFER_TOO_SMALL;

	irql = KfAcquireSpinLock(&g_dmDebug.KeSystemProcess->ThreadListLock);
	KeAcquireSpinLockAtRaisedIrql(&g_dmDebug.KeTitleProcess->ThreadListLock);

	ple = g_dmDebug.KeSystemProcess->ThreadListHead.Flink;
	for(i = 0;i < 2;i++)
	{
		while(ple != &g_dmDebug.KeSystemProcess->ThreadListHead && ple != &g_dmDebug.KeTitleProcess->ThreadListHead)
		{
			pthr = CONTAINING_RECORD(ple, KTHREAD, ThreadListEntry);
			ple = ple->Flink;

			if(!pthr->DebugMonitorData)
				FInitThreadDebugData(pthr);

			pdmtd = (DMTD*)pthr->DebugMonitorData;

			if(pdmtd && !(pdmtd->DebugFlags & DMFLAG_DEBUGTHREAD))
			{
				if(cchThreads++ < *pcThreads)
					rgdwThreads[cchThreads - 1] = (DWORD)pthr->ThreadId;
				else
					hr = XBDM_BUFFER_TOO_SMALL;
			}
		}

		ple = g_dmDebug.KeTitleProcess->ThreadListHead.Flink;
	}

	*pcThreads = cchThreads;

	KeReleaseSpinLockFromRaisedIrql(&g_dmDebug.KeTitleProcess->ThreadListLock);
	KfReleaseSpinLock(&g_dmDebug.KeSystemProcess->ThreadListLock, irql);

	return hr;
}

DMHRAPI DmContinueThread(DWORD dwThreadId, BOOL fException)
{
	PKTHREAD pthr;
	BYTE irql;
	HRESULT hr = XBDM_NOERR;
	DMTD *pdmtd;

	if(dwExecState > 3)
		return XBDM_NOTHREAD;

	if(FAILED(ObLookupAnyThreadByThreadId(dwThreadId, &pthr)))
		return XBDM_NOTHREAD;

	irql = KfAcquireSpinLock(&pthr->Process->ThreadListLock);
	
	pdmtd = (DMTD*)pthr->DebugMonitorData;
	
	if(pdmtd && (pdmtd->DebugFlags & DMFLAG_CONTINUEABLE))
	{
		if(fException)
			pdmtd->DebugFlags |= DMFLAG_EXCEPTION;

		if(dwExecState != DMN_EXEC_START)
		{
			if(!(pdmtd->DebugFlags & DMFLAG_STOPPED))
			{
				pdmtd->DebugFlags |= DMFLAG_STOPPED;
				KeSuspendThread(pthr);
			}
		}

		pdmtd->DebugFlags &= ~DMFLAG_CONTINUEABLE;

		KeSetEvent(pdmtd->DebugEvent, TRUE, FALSE);
	}
	else
		hr = XBDM_NOTSTOPPED;

	KfReleaseSpinLock(&pthr->Process->ThreadListLock, irql);

	ObDereferenceObject(pthr);

	return hr;
}

DMHRAPI DmStopOn(DWORD dwStopFlags, BOOL fStop)
{
	// We should probably be synchronizing this for when titles feel like being dicks and not synchronizing
	// Oh well :/

	if(fStop)
		g_dmGlobals.dwStopFlags |= dwStopFlags;
	else
		g_dmGlobals.dwStopFlags &= ~dwStopFlags;

	return XBDM_NOERR;
}

DMHRAPI DmIsThreadStopped(DWORD dwThreadId, PDM_THREADSTOP pdmts)
{
	PKTHREAD pthr;
	DMTD *pdmtd;
	BYTE irql;
	HRESULT hr = XBDM_NOERR;

	pdmts->NotifiedReason = DM_NONE;

	if(FAILED(ObLookupAnyThreadByThreadId(dwThreadId, &pthr)))
		return XBDM_NOTHREAD;

	irql = KfAcquireSpinLock(&pthr->Process->ThreadListLock);

	pdmtd = (DMTD*)pthr->DebugMonitorData;

	if(pdmtd && !(pdmtd->DebugFlags & DMFLAG_DEBUGTHREAD))
	{
		if(pdmtd->Exception && (pdmtd->DebugFlags & DMFLAG_CONTINUEABLE))
		{
			// Time to play some FIGUREOUTWTFISWRONGWITHTHISTHREAD!
			pdmts->NotifiedReason = pdmtd->StopReason;
			switch(pdmtd->StopReason)
			{
			case DM_DEBUGSTR:
			case DM_ASSERT:
				pdmts->u.DebugStr.ThreadId = dwThreadId;
				pdmts->u.DebugStr.String = (LPCSTR)pdmtd->Context->Gpr3;
				pdmts->u.DebugStr.Length = (DWORD)pdmtd->Context->Gpr4;
				break;
			case DM_SINGLESTEP:
			case DM_BREAK:
				pdmts->u.Break.ThreadId = dwThreadId;
				pdmts->u.Break.Address = (PVOID)pdmtd->Context->Iar;
				break;
			case DM_DATABREAK:
				pdmts->u.DataBreak.ThreadId = dwThreadId;
				pdmts->u.DataBreak.Address = (PVOID)pdmtd->Context->Iar;
				pdmts->u.DataBreak.DataAddress = (PVOID)pdmtd->Exception->ExceptionInformation[1];
				// if FMatchDataBreak
				break;
			case DM_EXCEPTION:
				pdmts->u.Exception.ThreadId = dwThreadId;
				pdmts->u.Exception.Address = (PVOID)pdmtd->Context->Iar;
				if(pdmtd->DebugFlags & DMFLAG_FIRSTCHANCE)
					pdmts->u.Exception.Flags = DM_EXCEPT_FIRSTCHANCE;
				else
					pdmts->u.Exception.Flags = 0;
				
				pdmts->u.Exception.Information[0] = pdmtd->Exception->ExceptionInformation[0];
				pdmts->u.Exception.Information[1] = pdmtd->Exception->ExceptionInformation[1];
				break;
			}
		}
		else
			hr = XBDM_NOTSTOPPED;
	}
	else
		hr = XBDM_NOTHREAD;

	KfReleaseSpinLock(&pthr->Process->ThreadListLock, irql);
	ObDereferenceObject(pthr);

	return hr;
}

DMHRAPI DmSuspendThread(DWORD dwThreadId)
{
	PKTHREAD pthr;

	if(FAILED(ObLookupAnyThreadByThreadId(dwThreadId, &pthr)))
		return XBDM_NOTHREAD;

	KeSuspendThread(pthr);
	ObDereferenceObject(pthr);

	return XBDM_NOERR;
}

DMHRAPI DmResumeThread(DWORD dwThreadId)
{
	PKTHREAD pthr;

	if(FAILED(ObLookupAnyThreadByThreadId(dwThreadId, &pthr)))
		return XBDM_NOTHREAD;

	KeResumeThread(pthr);
	ObDereferenceObject(pthr);

	return XBDM_NOERR;
}

DMHRAPI DmGetSystemInfo(PDM_SYSTEM_INFO pdmGetSystemInfo)
{
	if(!pdmGetSystemInfo)
		return E_INVALIDARG;

	if(pdmGetSystemInfo->SizeOfStruct != sizeof(DM_SYSTEM_INFO))
		return E_INVALIDARG;

	memcpy(&pdmGetSystemInfo->BaseKernelVersion, &XboxKrnlBaseVersion, sizeof(DM_SYSTEM_INFO));
	memcpy(&pdmGetSystemInfo->KernelVersion, &XboxKrnlVersion, sizeof(DM_SYSTEM_INFO));
	
	pdmGetSystemInfo->XDKVersion.Major = 2;
	pdmGetSystemInfo->XDKVersion.Minor = 0;
	pdmGetSystemInfo->XDKVersion.Build = 20353;
	pdmGetSystemInfo->XDKVersion.Qfe = 0;

	pdmGetSystemInfo->dmSystemInfoFlags = (XboxHardwareInfo->Flags & 0x20) ? DM_XBOX_HW_FLAG_HDD : 0;

	return XBDM_NOERR;
}