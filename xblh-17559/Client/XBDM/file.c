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

HRESULT FFileNameToObName(LPCSTR szFileName, CHAR *szObName, DWORD cchObName)
{
	HRESULT hr = S_OK;
	char szName[MAX_PATH], oszName[MAX_PATH];
	int cchName, i;
	ANSI_STRING as, as2;
	TRANSLATE_SYMLINK obName;

	if(!cchObName)
	{
		DbgPrint("[xbdm] cchObName invalid\n");
		return E_INVALIDARG;
	}
	if(!szFileName)
	{
		DbgPrint("[xbdm] szFileName invalid\n");
		return E_INVALIDARG;
	}
	if(!szObName)
	{
		DbgPrint("[xbdm] szObName invalid\n");
		return E_INVALIDARG;
	}

	strcpy_s(szName, sizeof(szName), szFileName);

	for(cchName = 0;szName[cchName];cchName++)
	{
		if(szName[cchName] == ':')
		{
			szName[cchName] = 0;

			break;
		}
	}

	if(!strcmpi(szName, "F") || !strcmpi(szName, "SMB"))
	{
		DbgPrint("[xbdm] SMB not supported yet!\n");
		DebugBreak();
	}

	oszName[0] = 0;

	for(i = 0;i < cchDrives;i++)
		if(!strcmpi(Drives[i].DriveName, szName))
		{
			strcpy(oszName, Drives[i].DevicePath);
		}

	if(!oszName[0])
	{
		obName.reserved = 0;
		obName.name = &as;

		strcat(szName, ":\\");

		RtlSnprintf(szObName, cchObName, "\\??\\%s", szName);

		RtlInitAnsiString(&as, szObName);

		as2.Buffer = oszName;
		as2.Length = 0;
		as2.MaximumLength = sizeof(oszName);

		if(NT_SUCCESS(ObTranslateSymbolicLink(&obName, &as2)))
			oszName[as2.Length] = 0;
		else
			hr = E_FAIL;
	}

	if(!FAILED(hr))
		RtlSnprintf(szObName, cchObName, "%s%s", oszName, szFileName + cchName + 1);
	else
		szObName[0] = 0;

	return hr;
}

NTSTATUS FCreateFile(PHANDLE FileHandle, ACCESS_MASK DesiredAccess, LPCSTR FileName, PLARGE_INTEGER AllocationSize,
	ULONG FileAttributes, ULONG ShareAccess, ULONG CreateDisposition, ULONG CreateOptions)
{
	char oszName[MAX_PATH];
	ANSI_STRING as;
	IO_STATUS_BLOCK iosb;
	OBJECT_ATTRIBUTES attr;

	if(FileName[0] == '\\')
		strcpy_s(oszName, sizeof(oszName), FileName);
	else if(FAILED(FFileNameToObName(FileName, oszName, sizeof(oszName))))
		return STATUS_ACCESS_DENIED;

	RtlInitAnsiString(&as, oszName);
	attr.Attributes = OBJ_CASE_INSENSITIVE;
	attr.ObjectName = &as;
	attr.RootDirectory = NULL;

	return NtCreateFile(FileHandle, DesiredAccess, &attr, &iosb, AllocationSize, FileAttributes, ShareAccess, CreateDisposition, CreateOptions);
}

NTSTATUS FReadFile(HANDLE FileHandle, PVOID Buffer, ULONG Length)
{
	IO_STATUS_BLOCK io;
	
	return NtReadFile(FileHandle, NULL, NULL, NULL, &io, Buffer, Length, NULL);
}

NTSTATUS FWriteText(HANDLE FileHandle, PINF pinf, LPCSTR fmt, ...)
{
	char szBuf[0x200];
	va_list va;

	va_start(va, fmt);
	RtlVsnprintf(szBuf, sizeof(szBuf), fmt, va);
	va_end(va);

	return FWriteFile(FileHandle, szBuf, (ULONG)strlen(szBuf), pinf);
}

NTSTATUS FWriteFile(HANDLE FileHandle, PVOID Buffer, ULONG Length, PINF pinf)
{
	IO_STATUS_BLOCK iosb;
	NTSTATUS st = STATUS_SUCCESS;
	DWORD cbT;
	PCHAR pb = (PCHAR)Buffer;

	if(pb)
	{
		while(Length)
		{
			cbT = pinf->cbBuf - pinf->cbUsed;
			if(Length >= cbT)
			{
				memcpy((char*)pinf->pbBuf + pinf->cbUsed, pb, cbT);
				st = NtWriteFile(FileHandle, NULL, NULL, NULL, &iosb, pinf->pbBuf,
					pinf->cbBuf, NULL);
				pb += cbT;
				Length -= cbT;
				pinf->cbUsed = 0;
			}
			else
			{
				memcpy((char*)pinf->pbBuf + pinf->cbUsed, pb, Length);
				pb += Length;
				pinf->cbUsed += Length;
				Length = 0;
			}
		}
	}

	return st;
}

NTSTATUS FCloseFile(HANDLE FileHandle, PINF pinf)
{
	IO_STATUS_BLOCK iosb;

	if(pinf && pinf->cbUsed)
	{
		NtWriteFile(FileHandle, NULL, NULL, NULL, &iosb, pinf->pbBuf, pinf->cbUsed, NULL);
		pinf->cbUsed = 0;
	}

	return NtClose(FileHandle);
}

DRIVE Drives[] =
{
	{ "FLASH",		"\\Device\\Flash",							1 },
	
	{ "INTUSB",		"\\Device\\BuiltInMuUsb\\Storage",			2 },
	{ "MUINT",		"\\Device\\BuiltInMuSfc",					2 },

	{ "HDD",		"\\Device\\Harddisk0\\Partition1",			2 },
	{ "DEVKIT",		"\\Device\\Harddisk0\\Partition1\\DEVKIT",	2 },

	{ "MU0",		"\\Device\\Mu0",							2 },
	{ "MU1",		"\\Device\\Mu1",							2 },

	{ "USB0",		"\\Device\\Mass0",							2 },
	{ "USB1",		"\\Device\\Mass1",							2 },
	{ "USB2",		"\\Device\\Mass2",							2 },
	{ "USBMU0",		"\\Device\\Mass0PartitionFile\\Storage",	2 },
	{ "USBMU1",		"\\Device\\Mass1PartitionFile\\Storage",	2 },
	{ "USBMU2",		"\\Device\\Mass2PartitionFile\\Storage",	2 },

	{ "DVD",		"\\Device\\CdRom0",							2 },
};
extern int cchDrives = sizeof(Drives) / sizeof(DRIVE);