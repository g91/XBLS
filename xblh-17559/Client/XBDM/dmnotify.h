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

#ifndef _DMNOTIFY_H
#define _DMNOTIFY_H

typedef struct _DMN_SESSION
{
	DWORD dwFlags;
	LIST_ENTRY Link;
	PDM_NOTIFY_FUNCTION pNotifyFuncs[DM_NOTIFYMAX - 1];
} DMN_SESSION, *PDMN_SESSION;

typedef struct _DMN_NOTIFYSOCK
{
	SOCKET s;
	LIST_ENTRY Link;
	DWORD port;
} DMN_NOTIFYSOCK, *PDMN_NOTIFYSOCK;

typedef struct _DMN_NOTIFYQUEUE
{
	DWORD dwNotification;
	ULONG_PTR ulpParam;
	LIST_ENTRY Link;
} DMN_NOTIFYQUEUE, *PDMN_NOTIFYQUEUE;

DMHRAPI FNotify(ULONG dwNotification, ULONG_PTR ulpParam);

DMHRAPI FConvertToNotifySock(PDMCONN Connection, DWORD Port);
DMHRAPI FDropNotifySock(DWORD Port);
VOID ProcessQueuedNotifications();
BOOL FGetNotifySz(ULONG dwNotification, ULONG_PTR ulpParam, CHAR *sz, int cch);

extern CRITICAL_SECTION csNotify;
extern LIST_ENTRY notifyList, notifySockList, notifyQueue;
extern DWORD dwNotifyQueue, notifyQueueLock;

#endif