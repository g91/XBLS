// Project started early 2011
// If you want to get in touch, shoot me an email <confettimancer@gmail.com>

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

#include "dmincludes.h"

DMGD g_dmGlobals;
DMDD g_dmDebug;

EX_TITLE_TERMINATE_REGISTRATION titleRegistration = { LpTitleTerminateRoutine, 0 };
EX_THREAD_REGISTRATION threadRegistration = { LpThreadNotificationRoutine, 0 };

DWORD _resolve(HMODULE Module, DWORD Export, DWORD off1, DWORD off2)
{
	SHORT t1, t2;
	DWORD *f;

	if(FAILED(XexGetProcedureAddress(Module, Export, &f)))
		return 0;

	t1 = f[off1] & 0xFFFF;
	t2 = f[off2] & 0xFFFF;

	return (t1 << 16) + t2;
}

VOID ResolveData()
{
	DbgPrint("[xbdm] resolving kernel stuff\n");

	if(!(g_dmDebug.KeSystemProcess = (PKPROCESS)_resolve(g_dmGlobals.hKernel, 13, 16, 18)))
		DbgPrint("[xbdm] unable to resolve KeSystemProcess!\n");
	if(!(g_dmDebug.KeTitleProcess = (PKPROCESS)_resolve(g_dmGlobals.hKernel, 13, 20, 22)))
		DbgPrint("[xbdm] unable to resolve KeTitleProcess!\n");
	if(!(g_dmDebug.PsLoadedModuleList = (PLIST_ENTRY)_resolve(g_dmGlobals.hKernel, 412, 9, 11)))
		DbgPrint("[xbdm] unable to resolve PsLoadedModuleList!\n");
	if(!(g_dmDebug.XexLoadedModuleListLock = (LPDWORD)_resolve(g_dmGlobals.hKernel, 412, 3, 5)))
		DbgPrint("[xbdm] unable to resolve XexLoadedModuleListLock!\n");

	DbgPrint("[xbdm] resolving xam exports\n");
	XexGetProcedureAddress(g_dmGlobals.hXam, 421, &XamLoaderLaunchTitleEx);
}

//
//#include <stddef.h>
//#include <xbdm.h>
//#pragma comment(lib, "xbdm")
//
//#define XDRPCVersion 4
//
//// so we don't use any xbdm imports
//#define DmFreePool ExFreePool
//#define DmAllocatePoolWithTag ExAllocatePoolWithTag
//
//EXTERN_C {
//	NTSTATUS KeWaitForSingleObject(int Object, int WaitReason, int WaitMode, int Alertable, PLARGE_INTEGER Timeout);
//}
//
//typedef struct _DM_CALL {
//
//	void* pDmCallQuery;	//	0x00 - 0x04
//	BOOL bFreeMemory;	//	0x04 - 0x08
//	BOOL bSystemThread;	//	0x08 - 0x0C
//	HANDLE hThread;		//	0x0C - 0x10
//	DWORD dwBufferSize;	//	0x10 - 0x14
//
//	DWORD dwPad1;		//	0x14 - 0x18
//
//	QWORD ResponseFlag;	//	0x18 - 0x20
//	CHAR ThreadName[64];	//	0x20 - 0x60
//	BOOL Completed;		//	0x60 - 0x64
//
//	DWORD dwPad3;		//	0x64 - 0x68
//
//	QWORD qwError;		//	0x68 - 0x70
//	BYTE Return[8];		//	0x70 - 0x78
//	QWORD qwResultCode;	//	0x78 - 0x80, 1 = report GetLastError()
//	QWORD IsFloat;		//	0x80 - 0x88
//	QWORD NumOfInts;	//	0x88 - 0x90, (*8 || << 3) to get the buffer length
//	QWORD NumOfFloats;	//	0x90 - 0x98, (*8 || << 3) to get the buffer length
//
//	DWORD Pad4;		//	0x98 - 0x9C
//
//	PCHAR XexName;		//	0x9C - 0xA0
//	QWORD CallAddress;	//	0xA0 - 0xA8
//	BYTE ArgBuffer[50];	//	0xA8,			The buffer size is ((NumOfInts + NumOfFloats) * 8)
//
//} DM_CALL, *PDM_CALL;
//
//void DmCallProcedure(PDM_CALL pdmcl) {
//
//	DWORD CallAddress, Temp;
//	QWORD TempInt, IntArgs[36];
//	double FloatArgs[36], f1;
//
//	while(pdmcl->bFreeMemory == 1)// had to do this so it would work
//		Sleep(0);
//
//	if(pdmcl->bFreeMemory) {
//		DmFreePool(pdmcl);
//		return;
//	}
//
//	// Zero the args
//	ZeroMemory(IntArgs, sizeof(IntArgs));
//	ZeroMemory(FloatArgs, sizeof(FloatArgs));
//
//	// Get the address
//	CallAddress = pdmcl->CallAddress & 0xFFFFFFFF;
//
//	// Resolve the address
//	if(pdmcl->XexName)
//	{
//		HANDLE Module;
//		DWORD Ord = CallAddress;
//		if(NT_SUCCESS(XexGetModuleHandle(pdmcl->XexName, &Module)))
//		{
//			if(!NT_SUCCESS(XexGetProcedureAddress(Module, Ord, &CallAddress)))
//			{
//				pdmcl->qwError = HRESULT_FROM_WIN32(ERROR_PROC_NOT_FOUND);//0x8007007F;
//				goto Error_Return;
//			}
//		}
//		else
//		{
//			pdmcl->qwError = HRESULT_FROM_WIN32(ERROR_MOD_NOT_FOUND);//0x8007007E;
//Error_Return:
//			pdmcl->Completed = TRUE;
//			return;
//		}
//	}
//
//	// Check if it is a valid address
//	if(!MmIsAddressValid((PVOID)CallAddress)) {
//		pdmcl->qwError = XBDM_MEMUNMAPPED;//0x82DA0004
//		goto Error_Return;
//	}
//
//	// Copy the args
//	memcpy(IntArgs, pdmcl->ArgBuffer, pdmcl->NumOfInts << 3);
//	memcpy(FloatArgs, pdmcl->ArgBuffer + (pdmcl->NumOfInts << 3), pdmcl->NumOfFloats << 3);
//
//	f1 = 
//		((double(*)(QWORD, ...))CallAddress)(
//		IntArgs[0], IntArgs[1], IntArgs[2], IntArgs[3],
//		IntArgs[4], IntArgs[5], IntArgs[6], IntArgs[7],
//
//		FloatArgs[0], FloatArgs[1], FloatArgs[2], FloatArgs[3],
//		FloatArgs[4], FloatArgs[5], FloatArgs[6], FloatArgs[7]
//	);
//
//	// Copy the int result
//	__asm mr TempInt, r3
//
//	// See if it is a float return
//	pdmcl->IsFloat &= 1;
//
//	// Copy the return
//	memcpy(pdmcl->Return, pdmcl->IsFloat ? &*(QWORD *)&f1 : &TempInt, 8);
//
//
//	if(pdmcl->qwResultCode == 1)
//		pdmcl->qwResultCode = GetLastError();
//
//	pdmcl->qwError = 0;
//	pdmcl->Completed = TRUE;
//}
//
//// This function wasn't reversed, I made it :D
//DMHRAPI HrRemoteProcedureCallResponse(PDM_CMDCONT pdmcc, LPSTR szResponse, DWORD cchResponse)
//{
//
//	PDM_CALL CustomData = (PDM_CALL)pdmcc->CustomData;
//	DWORD Tick;
//
//	if(CustomData->Completed)// if we have called the function
//	{
//		if(pdmcc->BytesRemaining == 0)
//		{
//			if(CustomData->ResponseFlag == ERROR_IO_PENDING)// One last time so we don't skip the buffer
//			{
//				CustomData->ResponseFlag = 0;
//				goto WaitFor;
//			}
//			pdmcc->Buffer = &CustomData->qwError;
//			pdmcc->DataSize = pdmcc->BufferSize;
//			pdmcc->BytesRemaining = 1;
//		}
//		else
//		{
//			if(pdmcc->DataSize != -1 && pdmcc->DataSize != 0)
//				pdmcc->Buffer = (PVOID)((DWORD)pdmcc->Buffer + pdmcc->DataSize);// To adjust the buffer
//			else
//			{
//				DmFreePool(CustomData);
//				return XBDM_ENDOFLIST;
//			}
//		}
//	}
//	else
//	{
//WaitFor:
//		Tick = GetTickCount();
//		while(!CustomData->Completed) {
//			if((GetTickCount() - Tick) >= 100)
//				break;
//			Sleep(10);
//		}
//		pdmcc->DataSize = 8;
//		pdmcc->Buffer = &CustomData->ResponseFlag;
//	}
//	return XBDM_NOERR;
//}
//
//DMHRAPI HrRemoteProcedureCallReceive(PDM_CMDCONT pdmcc, LPSTR szResponse, DWORD cchResponse)
//{
//
//	PDM_CALL CustomData = (PDM_CALL)pdmcc->CustomData;
//
//	if(pdmcc->DataSize) 
//	{
//		pdmcc->Buffer = (PVOID)((DWORD)pdmcc->Buffer + pdmcc->DataSize);
//		pdmcc->BytesRemaining -= pdmcc->DataSize;
//	}
//	else
//	{
//		if(pdmcc->BytesRemaining)
//		{
//			pdmcc->BytesRemaining = 0;
//			pdmcc->DataSize = 1;
//			if(CustomData->ThreadName[0])
//				DmFreePool((PVOID)CustomData);
//			else
//			{
//				KeResumeThread(CustomData->hThread);
//				ObDereferenceObject(CustomData->hThread);
//			}
//			return XBDM_NOERR;
//		}
//	}
//
//	if(pdmcc->BytesRemaining == 0)
//	{
//		if(!CustomData->ThreadName[0])
//			KeResumeThread(CustomData->hThread);
//		pdmcc->HandlingFunction = HrRemoteProcedureCallResponse;
//		return XBDM_BINRESPONSE;
//	}
//
//	return XBDM_NOERR;
//}
//
//DMHRAPI HrRemoteProcedureCall(LPCSTR szCommand, LPSTR szResponse,
//	DWORD cchResponse, PDM_CMDCONT pdmcc)
//{
//
//	DWORD dwVersion,
//		dwCreationFlagsMod,
//		dwBufsize,
//		dwProcessor;
//
//	PDM_CALL pdmcl;
//
//	char thread[0x40];
//
//	// Get the version
//	if(!FGetDwParam(szCommand, "version", &dwVersion)) {
//		sprintf_s(szResponse, cchResponse, "error=Version is not specified, expecting major version %d", XDRPCVersion);
//		return XBDM_NOERR;
//	}
//
//	// Compair the version
//	if(dwVersion != XDRPCVersion) {
//		sprintf_s(szResponse, cchResponse, "error=Version mismatch, expected %d but got %d", XDRPCVersion, dwVersion);
//		return XBDM_NOERR;
//	}
//
//	// Check if it is a system or title thread
//	dwCreationFlagsMod = PchGetParam(szCommand, "system", 0) ? 2 : 0;
//
//	if(!dwCreationFlagsMod && !PchGetParam(szCommand, "title", 0))
//		return XBDM_INVALIDARG;
//
//	// Get the size of the buffer
//	if(!FGetDwParam(szCommand, "buf_size", &dwBufsize))
//		return XBDM_INVALIDARG;
//
//	// Get the processor
//	if(!FGetDwParam(szCommand, "processor", &dwProcessor))
//		dwProcessor = 5;
//
//	// Get the thread name
//	if(!FGetSzParam(szCommand, "thread", thread, 0x40))
//		thread[0] = 0;
//	else thread[0x3F] = 0;
//
//	// Alloc the buffer
//	pdmcl = (PDM_CALL)DmAllocatePoolWithTag(dwBufsize + 0x68, 'drpc');
//
//	if(!pdmcl)
//		return XBDM_NOMEMORY;
//
//	// Setup the buffer
//	pdmcl->pDmCallQuery = 0;
//	pdmcl->bFreeMemory = FALSE;
//	pdmcl->ResponseFlag = ERROR_IO_PENDING;
//	pdmcl->hThread = 0;
//	pdmcl->bSystemThread = dwCreationFlagsMod == 2;
//	pdmcl->dwBufferSize = dwBufsize;
//	pdmcl->Completed = FALSE;
//	strcpy_s(pdmcl->ThreadName, 0x40, thread);
//
//	// Create the thread in a suspended state and with our settings
//	dwCreationFlagsMod = ExCreateThread(&pdmcl->hThread, 0, 0, 0, (LPTHREAD_START_ROUTINE)DmCallProcedure, pdmcl,
//		((dwCreationFlagsMod | ((1 << dwProcessor) << 24)) | 0x81));
//
//	if(dwCreationFlagsMod < 0) {
//		DmFreePool(pdmcl);
//		return dwCreationFlagsMod | 0x10000000;
//	}
//
//	// Setup the continue params
//	pdmcc->CustomData = pdmcl;
//	pdmcc->Buffer = &pdmcl->qwError;
//	pdmcc->HandlingFunction = HrRemoteProcedureCallReceive;
//	pdmcc->BytesRemaining = dwBufsize;
//	pdmcc->BufferSize = dwBufsize;
//
//	// Return the buffer address
//	sprintf_s(szResponse, cchResponse, "buf_addr=%p", pdmcc->Buffer);
//	
//	return XBDM_READYFORBIN;
//}

BOOL DmDllMain()
{
#ifdef _DEBUG
	DWORD nop = 0x60000000;
#endif

#ifdef _DEBUG
	DbgPrint("[xbdm] please attach windbg\n");
	DebugBreak();
#endif

	DbgPrint("[xbdm] hi cOz!\n");

	DbgPrint("[xbdm] zeroing out initial global state\n");
	ZeroMemory(&g_dmGlobals, sizeof(g_dmGlobals));

	DbgPrint("[xbdm] initializing breakpoint data\n");
	DmpBreakSpinLock = 0;
	InitializeListHead(&leBreaks);
	ZeroMemory(&HardwareBreakpoint, sizeof(DMHB));

#ifdef _DEBUG
	DbgPrint("[xbdm] patching MmIsAddressValid (DEVKIT)\n");
	DmSetMemory((LPVOID)0x80096B58, 4, &nop, NULL);
	DmSetMemory((LPVOID)0x80096B08, 4, &nop, NULL);
	DmSetMemory((LPVOID)0x80096C04, 4, &nop, NULL);
	DmSetMemory((LPVOID)0x80096BB0, 4, &nop, NULL);
	DmSetMemory((LPVOID)0x80096A88, 4, &nop, NULL);
	DmSetMemory((LPVOID)0x80096B7C, 4, &nop, NULL);
#endif

	// Setup the exception data
	DbgPrint("[xbdm] initializing exception data\n");
	ExceptionStack = MmCreateKernelStack(0x8000, 2); // 8kb stack for exceptions
	ExceptionStackTitle = MmCreateKernelStack(0x8000, 2);
	InitializeCriticalSection(&csExceptionStack);
	InitializeCriticalSection(&csExceptionStackTitle);
	InitializeCriticalSection(&csExecState);

	DbgPrint("[xbdm] initializing debug monitor thread data\n");
#if 0
	InitializeCriticalSection(&csDebugMonitorData);
	leDebugMonitorData.Flink = leDebugMonitorData.Blink = &leDebugMonitorData;
#endif
	FInitThreadDebugData(PsGetCurrentThread());

	DbgPrint("[xbdm] initializing notifications\n");
	InitializeCriticalSection(&csNotify);
	InitializeListHead(&notifyList);
	InitializeListHead(&notifySockList);
	InitializeListHead(&notifyQueue);
	dwNotifyQueue = 0;
	notifyQueueLock = 0;

	DbgPrint("[xbdm] registering notifications\n");
	ExRegisterThreadNotification(&threadRegistration, TRUE);
	ExRegisterTitleTerminateNotification(&titleRegistration, TRUE);

	if(FAILED(XexGetModuleHandle("xboxkrnl.exe", &g_dmGlobals.hKernel)))
	{
		DbgPrint("[xbdm] Failed to get kernel handle\n");
		DebugBreak();
		return FALSE;
	}
	if(FAILED(XexGetModuleHandle("xam.xex", &g_dmGlobals.hXam)))
	{
		DbgPrint("[xbdm] Failed to get xam handle\n");
		DebugBreak();
		return FALSE;
	}
	if(FAILED(XexGetModuleHandle("launch.xex", &g_dmGlobals.hDashlaunch)))
	{
		DbgPrint("[xbdm] Failed to get dashlaunch handle\n");

		// Only fail in jtag build
#ifndef _DEBUG
		DebugBreak();
		return FALSE;
#else
		DbgPrint("[xbdm] hooking the trap handler (DEVKIT)\n");

		g_dmGlobals.PreviousTrap = *(pfnTrapHandler*)0x801C1B64;
		*(pfnTrapHandler*)0x801C1B64 = DmTrapHandler; // DEVKIT 13599/20871.2
#endif
	}
	else if(FAILED(XexGetProcedureAddress(g_dmGlobals.hDashlaunch, 1, &g_dmGlobals.pLaunchData)))
	{
		DbgPrint("[xbdm] Failed to get dashlaunch export\n");
		
		// Only fail in jtag build
#ifndef _DEBUG
		DebugBreak();
		return FALSE;
#endif
	}
	else if(*(DWORD*)(&g_dmGlobals.pLaunchData->versionMaj) < 0x00020018)
		DbgPrint("[xbdm] dashlaunch version %i.%i is not supported\n", g_dmGlobals.pLaunchData->versionMaj, g_dmGlobals.pLaunchData->versionMin);
	else
	{
		DbgPrint("[xbdm] dashlaunch version %i.%i supported\n", g_dmGlobals.pLaunchData->versionMaj, g_dmGlobals.pLaunchData->versionMin);

		g_dmGlobals.bDashlaunch = TRUE;

		// Enable single step exceptions
		DbgPrint("[xbdm] enabling single step exceptions\n");
		*g_dmGlobals.pLaunchData->DebugStepPatch = 0x60000000;

		DbgPrint("[xbdm] hooking the trap handler\n");
		g_dmGlobals.PreviousTrap = *g_dmGlobals.pLaunchData->DebugRoutine;
		*g_dmGlobals.pLaunchData->DebugRoutine = DmTrapHandler;
		DbgPrint("[xbdm] handler is hooked\n");
	}

#ifdef _DEBUG
	strcpy(g_dmGlobals.rgchDbgName, "XeDevkit"); // XeDevkit is default name for debug (aka devkit testing)
#else
	strcpy(g_dmGlobals.rgchDbgName, "Jtag"); // Jtag is default name for release (aka jtag)
#endif

	FLoadGlobals();
	FWriteGlobals(); // Force ini creation

	ResolveData();

	DbgPrint("[xbdm] installing hypervisor expansion\n");
	if(NT_SUCCESS(HvInitialize()))
		g_dmGlobals.bHypervisorEnabled = TRUE;

	DbgPrint("[xbdm] starting server\n");

	// lets just pull 16kb of stack for fun or something
	if(FAILED(ExCreateThread(&g_dmGlobals.pthrServ, 0x10000, NULL, NULL, ServerThread, NULL, 0x040004A6)))
	{
		DbgPrint("[xbdm] Failed to startup server\n");
#ifdef _DEBUG
		DebugBreak();
		return FALSE;
#endif
	}
	
	return TRUE;
}

BOOL APIENTRY DllMain(HANDLE hModule, DWORD dwReason, LPVOID lpReserved)
{
	if(dwReason == DLL_PROCESS_ATTACH)
		return DmDllMain();
	
	return TRUE;
}