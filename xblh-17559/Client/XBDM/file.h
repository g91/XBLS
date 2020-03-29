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

#ifndef _FILE_H
#define _FILE_H

// Handly little thing that makes it easier to do file io
typedef struct _INF {
	int cbBuf;
	void *pbBuf; // 0x1000 = a pretty good amount

	int cbUsed;
} INF, *PINF;

typedef struct _DRIVE
{
	LPCSTR DriveName;
	LPCSTR DevicePath;
	DWORD Visibility; // 0 = Not visible, 1 = internal, 2 = visible
} DRIVE;

NTSTATUS FCreateFile(PHANDLE FileHandle, ACCESS_MASK DesiredAccess, LPCSTR FileName, PLARGE_INTEGER AllocationSize,
	ULONG FileAttributes, ULONG ShareAccess, ULONG CreateDisposition, ULONG CreateOptions);
NTSTATUS FReadFile(HANDLE FileHandle, PVOID Buffer, ULONG Length);
NTSTATUS FWriteText(HANDLE FileHandle, PINF pinf, LPCSTR fmt, ...);
NTSTATUS FWriteFile(HANDLE FileHandle, PVOID Buffer, ULONG Length, PINF pinf);
NTSTATUS FCloseFile(HANDLE FileHandle, PINF pinf);

HRESULT FFileNameToObName(LPCSTR szFileName, CHAR *szObName, DWORD cchObName);

extern DRIVE Drives[];
extern int cchDrives;

#endif