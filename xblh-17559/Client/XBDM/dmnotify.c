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

CRITICAL_SECTION csNotify;
LIST_ENTRY notifyList, notifySockList, notifyQueue;
DWORD dwNotifyQueue, notifyQueueLock;
BOOL bProcessingNotifications = FALSE;

#define DM_TITLESESSION 1

DMHRAPI DmOpenNotificationSession(DWORD dwFlags, PDMN_SESSION *pSession)
{
	if(!pSession)
		return E_INVALIDARG;

	ASSERT(KeGetCurrentIrql() == PASSIVE_LEVEL);

	if(KeGetCurrentProcessType() == 1)
		dwFlags |= DM_TITLESESSION;

	*pSession = (PDMN_SESSION)DmAllocatePoolWithTag(sizeof(DMN_SESSION), 'dmns');

	if(!*pSession)
		return E_OUTOFMEMORY;

	EnterCriticalSection(&csNotify);

	ZeroMemory(*pSession, sizeof(DMN_SESSION));

	InsertHeadList(&notifyList, &(*pSession)->Link);
	
	LeaveCriticalSection(&csNotify);

	return XBDM_NOERR;
}

DMHRAPI DmCloseNotificationSession(PDMN_SESSION Session)
{
	if(Session == NULL)
		return E_INVALIDARG;

	EnterCriticalSection(&csNotify);

	RemoveEntryList(&Session->Link);

	DmFreePool(Session);

	LeaveCriticalSection(&csNotify);

	return XBDM_NOERR;
}

BOOL FGetNotifySz(ULONG dwNotification, ULONG_PTR ulpParam, CHAR *sz, int cch)
{
	int i, j, k, l;
	char *str;
	BOOL fRet = TRUE;

	ZeroMemory(sz, cch);

#define pdmct ((PDMN_CREATETHREAD)ulpParam)
#define pdmds ((PDMN_DEBUGSTR)ulpParam)
#define pdme ((PDMN_EXCEPTION)ulpParam)
#define pdmb ((PDMN_BREAK)ulpParam)
#define pdmdb ((PDMN_DATABREAK)ulpParam)
#define pdmm ((PDMN_MODLOAD_EX)ulpParam)

	switch(dwNotification & DM_NOTIFICATIONMASK)
	{
	case DM_CREATETHREAD:
		RtlSprintf(sz, "create thread=0x%08x start=0x%08x", pdmct->ThreadId, pdmct->StartAddress);
		break;
	case DM_DESTROYTHREAD:
		RtlSprintf(sz, "terminate thread=0x%08x", ulpParam);
		break;
	case DM_DEBUGSTR:
		for(i = 0,j = 0,k = 0,l = 0;i < (int)pdmds->Length;i++)
		{
			BOOL lf = FALSE;
			
			if(pdmds->String[i] == '\n')
				lf = TRUE;

			if((i == pdmds->Length - 1) || lf)
			{
				if(k == 0)
					k = RtlSnprintf(sz, cch, "debugstr thread=0x%08x %sstring=",
						pdmds->ThreadId, lf ? "lf " : "");
				else
					k += RtlSnprintf(sz + k, cch - k, "\r\ndebugstr thread=0x%08x %sstring=",
						pdmds->ThreadId, lf ? "lf " : "");

				for(j = k;l <= i && j < cch;l++)
				{
					if(pdmds->String[l] != '\r'
						&& pdmds->String[l] != '\n')
					{
						sz[j] = pdmds->String[l];
						j++;
					}
				}

				j = i + 1;
				l = j;
			}
		}
		break;
	case DM_EXEC:
		switch(ulpParam)
		{
		case DMN_EXEC_PENDING:
			strcpy(sz, "execution pending");
			break;
		case DMN_EXEC_STOP:
			strcpy(sz, "execution stopped");
			break;
		case DMN_EXEC_START:
			strcpy(sz, "execution started");
			break;
		case DMN_EXEC_PENDING_TITLE:
			strcpy(sz, "execution pending_title");
			break;
		case DMN_EXEC_REBOOT_TITLE:
			strcpy(sz, "execution reboot_title");
			break;
		case DMN_EXEC_REBOOT:
			strcpy(sz, "execution rebooting");
			break;
		default:
			strcpy(sz, "null");
			break;
		}
		break;
	case DM_EXCEPTION:
		RtlSprintf(sz, "exception code=0x%08x thread=0x%08x address=0x%08x",
			pdme->Code, pdme->ThreadId, pdme->Address);
		if(pdme->Code == STATUS_ACCESS_VIOLATION)
			RtlSprintf(sz + strlen(sz), " %s=0x%08x", pdme->Information[0] == 0 ? "read" : "write", pdme->Information[1]);
		else
			RtlSprintf(sz + strlen(sz), " nparam=%lu params=0x%08x", pdme->Information[0], pdme->Information[1]);

		if(pdme->Flags & DM_EXCEPT_FIRSTCHANCE)
			strcat(sz, " first");
		if(pdme->Flags & DM_EXCEPT_NONCONTINUABLE)
			strcat(sz, " noncont");

		break;
	case DM_BREAK:
		RtlSprintf(sz, "break addr=0x%08x thread=0x%08x", pdmb->Address, pdmb->ThreadId);
		break;
	case DM_DATABREAK:
		if(pdmdb->BreakType == DMBREAK_READ)
			str = "read";
		else if(pdmdb->BreakType == DMBREAK_WRITE || pdmdb->BreakType == DMBREAK_READWRITE)
			str = "readwrite";
		else
			str = "execute";
		RtlSprintf(sz, "data %s=0x%08x addr=0x%08x thread=0x%08x", str, pdmdb->DataAddress, pdmdb->ThreadId);
		break;
	case DM_SINGLESTEP:
		RtlSprintf(sz, "singlestep addr=0x%08x thread=0x%08x", pdmb->Address, pdmb->ThreadId);
		break;
	case DM_MODLOAD:
		RtlSprintf(sz, "modload name=\"%s\" base=0x%08x size=0x%08x check=0x%08x timestamp=0x%08x pdata=0x%08x psize=0x%08x thread=0x%08x osize=0x%08x",
			pdmm->Name, pdmm->BaseAddress, pdmm->Size, pdmm->CheckSum, pdmm->TimeStamp, pdmm->PDataAddress, pdmm->PDataSize, pdmm->ThreadId, pdmm->OriginalSize);
		break;
	case DM_MODUNLOAD:
		RtlSprintf(sz, "modunload name=\"%s\" base=0x%08x size=0x%08x", pdmm->Name, pdmm->BaseAddress, pdmm->Size);
		break;
	default:
		strcpy(sz, "null");
		fRet = FALSE;
	}

	if(dwNotification & DM_STOPTHREAD)
		strcat(sz, " stop");

	return fRet;

#undef pdmct
#undef pdmds
#undef pdme
#undef pdmb
#undef pdmdb
#undef pdmm
}

VOID NotifyRemoteComponents(ULONG dwNotification, ULONG_PTR ulpParam)
{
	PDMN_NOTIFYSOCK sock;
	PLIST_ENTRY ple;
	char sz[0x200];

	FGetNotifySz(dwNotification, ulpParam, sz, sizeof(sz));

	KeEnterCriticalRegion();
	EnterCriticalSection(&csNotify);

	ple = notifySockList.Flink;
	while(ple != &notifySockList)
	{
		sock = CONTAINING_RECORD(ple, DMN_NOTIFYSOCK, Link);
		ple = ple->Flink;

		if(FSendLine(sock->s, sz) <= 0)
		{
			shutdown(sock->s, SD_BOTH);
			NetDll_closesocket(2, sock->s);
			RemoveEntryList(&sock->Link);
		}
	}

	LeaveCriticalSection(&csNotify);
	KeLeaveCriticalRegion();
}

VOID NotifyLocalComponents(ULONG dwNotification, ULONG_PTR ulpParam)
{
	PDMN_SESSION Session;
	PLIST_ENTRY ple;
	BOOL term = FALSE;

	EnterCriticalSection(&csNotify);

	ple = notifyList.Flink;
	while(ple != &notifyList)
	{
		Session = CONTAINING_RECORD(ple, DMN_SESSION, Link);
		ple = ple->Flink;

		if(Session->pNotifyFuncs[dwNotification - 1])
			Session->pNotifyFuncs[dwNotification - 1](dwNotification, ulpParam);
	}

	LeaveCriticalSection(&csNotify);
}

VOID ProcessQueuedNotifications()
{
	PLIST_ENTRY ple;
	PDMN_NOTIFYQUEUE pdmq;

	while(InterlockedCompareExchangeAcquire((PLONG)&notifyQueueLock, (LONG)PsGetCurrentThread(), 0) == 0);

	ple = notifyQueue.Flink;
	while(ple != &notifyQueue)
	{
		pdmq = CONTAINING_RECORD(ple, DMN_NOTIFYQUEUE, Link);
		ple = ple->Flink;
		dwNotifyQueue--;
		RemoveEntryList(&pdmq->Link);

		NotifyRemoteComponents(pdmq->dwNotification, pdmq->ulpParam);

		switch(pdmq->dwNotification)
		{
		case DM_DEBUGSTR:
			if(((PDMN_DEBUGSTR)pdmq->ulpParam)->String)
				DmFreePool((PVOID)((PDMN_DEBUGSTR)pdmq->ulpParam)->String);
			break;
		}

		DmFreePool(pdmq);
	}

	bProcessingNotifications = FALSE;

	InterlockedCompareExchangeRelease((PLONG)&notifyQueueLock, 0, (LONG)PsGetCurrentThread());
}

VOID FQueueNotification(ULONG dwNotification, ULONG_PTR ulpParam)
{
	BOOL bError = FALSE;
	PDMN_DEBUGSTR pdmds;
	PDMN_MODLOAD pdml;
	PDMN_CREATETHREAD pdmct;
	PDMN_THREADSWITCH pdmts;
	PDMN_NOTIFYQUEUE pdmq;

	// We will only pass along information stuff
	if(dwNotification == DM_EXCEPTION)
		return;

	pdmq = (PDMN_NOTIFYQUEUE)DmAllocatePoolTypeWithTag(sizeof(DMN_NOTIFYQUEUE), 'dmns', 2);

	if(!pdmq)
		return;

	pdmq->dwNotification = dwNotification;

	switch(dwNotification)
	{
	case DM_EXEC:
	case DM_DESTROYTHREAD:
		pdmq->ulpParam = ulpParam;
		break;
	case DM_DEBUGSTR:
		pdmds = (PDMN_DEBUGSTR)DmAllocatePoolTypeWithTag(sizeof(DMN_DEBUGSTR), 'dmns', 2);
		pdmq->ulpParam = (ULONG_PTR)pdmds;
		
		if(!pdmds)
			bError = TRUE;
		else
		{
			pdmds->Length = ((PDMN_DEBUGSTR)ulpParam)->Length;
			pdmds->ThreadId = ((PDMN_DEBUGSTR)ulpParam)->ThreadId;

			pdmds->String = (LPCSTR)DmAllocatePoolTypeWithTag(pdmds->Length, 'dmns', 2);

			if(!pdmds->String)
			{
				bError = TRUE;
				DmFreePool(pdmds);
			}
			else
				memcpy((char*)pdmds->String, ((PDMN_DEBUGSTR)ulpParam)->String, pdmds->Length);
		}
		break;
	case DM_MODLOAD:
	case DM_MODUNLOAD:
		pdml = (PDMN_MODLOAD)DmAllocatePoolTypeWithTag(sizeof(DMN_MODLOAD), 'dmns', 2);
		pdmq->ulpParam = (ULONG_PTR)pdml;
		
		if(!pdml)
			bError = TRUE;
		else
			memcpy(pdml, (PVOID)ulpParam, sizeof(DMN_MODLOAD));

		break;
	case DM_CREATETHREAD:
		pdmct = (PDMN_CREATETHREAD)DmAllocatePoolTypeWithTag(sizeof(DMN_CREATETHREAD), 'dmns', 2);
		pdmq->ulpParam = (ULONG_PTR)pdmct;

		if(!pdmct)
			bError = TRUE;
		else
			memcpy(pdmct, (PVOID)ulpParam, sizeof(DMN_CREATETHREAD));

		break;
	case DM_THREADSWITCH:
		pdmts = (PDMN_THREADSWITCH)DmAllocatePoolTypeWithTag(sizeof(DMN_THREADSWITCH), 'dmns', 2);
		pdmq->ulpParam = (ULONG_PTR)pdmts;

		if(!pdmts)
			bError = TRUE;
		else
			memcpy(pdmts, (PVOID)ulpParam, sizeof(DMN_THREADSWITCH));

		break;
	default:
		bError = TRUE;
	}

	if(bError)
	{
		DmFreePool(pdmq);
	}
	else
	{
		while(InterlockedCompareExchangeAcquire((PLONG)&notifyQueueLock, (LONG)PsGetCurrentThread(), 0) == 0);

		InsertHeadList(&notifyQueue, &pdmq->Link);
		dwNotifyQueue++;
		
		InterlockedCompareExchangeRelease((PLONG)&notifyQueueLock, 0, (LONG)PsGetCurrentThread());
	}
}

DMHRAPI FNotify(ULONG dwNotification, ULONG_PTR ulpParam)
{
	if(((dwNotification & DM_NOTIFICATIONMASK) == 0) || ((dwNotification & DM_NOTIFICATIONMASK) > DM_NOTIFYMAX))
		return E_INVALIDARG;

	if(KeGetCurrentIrql() <= DISPATCH_LEVEL)
		NotifyLocalComponents(dwNotification, ulpParam);

	if(KeGetCurrentIrql() == PASSIVE_LEVEL)
		NotifyRemoteComponents(dwNotification, ulpParam);
	else if(KeGetCurrentIrql() <= DISPATCH_LEVEL)
		FQueueNotification(dwNotification, ulpParam);

	return XBDM_NOERR;
}

DMHRAPI DmNotify(PDMN_SESSION Session, DWORD dwNotification, PDM_NOTIFY_FUNCTION pfnHandler)
{
	int i;

	if(Session == NULL || dwNotification > DM_NOTIFYMAX)
		return E_INVALIDARG;

	EnterCriticalSection(&csNotify);

	if(dwNotification == DM_NONE)
	{
		// We want to unregister something
		if(pfnHandler)
		{
			for(i = 0;i < DM_NOTIFYMAX - 1;i++)
				if(Session->pNotifyFuncs[i] == pfnHandler)
					Session->pNotifyFuncs[i] = NULL;
		}
		else
		{
			// Unregister ALL the functions!
			for(i = 0;i < DM_NOTIFYMAX - 1;i++)
				Session->pNotifyFuncs[i] = NULL;
		}
	}
	else // We want to register something
		Session->pNotifyFuncs[dwNotification - 1] = pfnHandler;

	LeaveCriticalSection(&csNotify);

	return XBDM_NOERR;
}

DMHRAPI FDropNotifySock(DWORD Port)
{
	PDMN_NOTIFYSOCK sock;
	PLIST_ENTRY ple;

	EnterCriticalSection(&csNotify);

	ple = notifySockList.Flink;
	while(ple != &notifySockList)
	{
		sock = CONTAINING_RECORD(ple, DMN_NOTIFYSOCK, Link);
		ple = ple->Flink;

		if(sock->port == Port)
		{
			shutdown(sock->s, SD_BOTH);
			NetDll_closesocket(2, sock->s);

			RemoveEntryList(&sock->Link);

			DmFreePool(sock);
		}
	}

	LeaveCriticalSection(&csNotify);

	return XBDM_NOERR;
}

DMHRAPI FConvertToNotifySock(PDMCONN Connection, DWORD Port)
{
	PDMN_NOTIFYSOCK sock;
	char sz[0x200];

	sock = (PDMN_NOTIFYSOCK)DmAllocatePoolWithTag(sizeof(DMN_NOTIFYSOCK), 'dmdb');

	if(!sock)
		return E_OUTOFMEMORY;

	sock->s = Connection->s;
	sock->port = Port;
	Connection->bKeepAlive = TRUE;
	Connection->bShutdown = TRUE;

	EnterCriticalSection(&csNotify);
	InsertHeadList(&notifySockList, &sock->Link);
	LeaveCriticalSection(&csNotify);

	FGetNotifySz(DM_EXEC, dwExecState, sz, sizeof(sz));
	
	FSendLine(sock->s, "205- now a notification channel");
	FSendLine(sock->s, sz);

	return XBDM_NOERR;
}