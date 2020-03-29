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

DMCONN rgdmc[CONNECTION_MAX];
SOCKET sockServ, sockName;

const char rgchHex[] = "0123456789ABCDEF";
char *rgszDumpMode[] = { "smart", "enabled", "disabled" };

/* BEGIN MICROSOFT CODE */

int SgnCompareRgch(const char *sz1, const char *sz2, int cch)
{
    while(cch-- && *sz1) {
        char ch1 = *sz1++;
        char ch2 = *sz2++;
        if(ch1 >= 'a' && ch2 <= 'z')
            ch1 -= 32;
        if(ch2 >= 'a' && ch2 <= 'z')
            ch2 -= 32;
        if(ch1 != ch2)
            return ch1 - ch2;
    }
    if(*sz1)
        return *sz1;
    return cch < 0 ? 0 : -*sz2;
}

BOOL FEqualRgch(const char *sz1, const char *sz2, int cch)
{
    return SgnCompareRgch(sz1, sz2, cch) == 0;
}

DWORD DwHexFromSz(LPCSTR sz, LPCSTR *szOut)
{
    DWORD dw = 0;

    for(;;) {
        if(*sz >= '0' && *sz <= '9')
            dw = dw * 16 + (*sz - '0');
        else if(*sz >= 'A' && *sz <= 'F')
            dw = dw * 16 + (*sz - 'A' + 10);
        else if(*sz >= 'a' && *sz <= 'f')
            dw = dw * 16 + (*sz - 'a' + 10);
        else
            break;
        ++sz;
    }
    if(szOut)
        *szOut = sz;
    return dw;
}

DWORD DwFromSz(LPCSTR sz, int *pcchUsed)
{
    DWORD dw = 0;
    LPCSTR szStart = sz;

    /* Process decimal, octal, or hex */
    if(*sz == '0') {
        ++sz;
        if(*sz == 'x')
            dw = DwHexFromSz(++sz, &sz);
        else
            while(*sz >= '0' && *sz <= '7')
                dw = dw * 8 + (*sz++ - '0');
    } else
        while(*sz >= '0' && *sz <= '9')
            dw = dw * 10 + (*sz++ - '0');
    if(pcchUsed)
        *pcchUsed = sz - szStart;
    return dw;
}

__inline BOOL FIsSpace(char ch)
{
    return ch == ' ' || ch == '\015' || ch == 0;
}

const char *PchGetParam(LPCSTR szCmd, LPCSTR szKey, BOOL fNeedValue)
{
    const char *pchTok;
    int cchTok;
    BOOL fQuote = FALSE;

    /* Skip the command */
    for(pchTok = szCmd; !FIsSpace(*pchTok); ++pchTok);

    while(*pchTok) {
        /* Skip leading spaces */
        while(*pchTok && FIsSpace(*pchTok))
            ++pchTok;
        if(!*pchTok)
            return NULL;
        for(cchTok = 0; !FIsSpace(pchTok[cchTok]); ++cchTok) {
            if(pchTok[cchTok] == '=') {
                if(FEqualRgch(szKey, pchTok, cchTok))
                    return pchTok + cchTok + 1; /* Skip the '=' */
                break;
            }
        }
        /* If we didn't see the '=' we need to check anyway */
        if(!fNeedValue && pchTok[cchTok] != '=' && FEqualRgch(szKey, pchTok,
                cchTok))
            return pchTok + cchTok;
        /* No match, so we need to skip past the value */
        pchTok += cchTok;
        while(*pchTok && (!FIsSpace(*pchTok) || fQuote))
            if(*pchTok++ == '"')
                fQuote = !fQuote;
    }
    return NULL;
}

void GetParam(LPCSTR szLine, LPSTR szBuf, int cchBuf)
{
    int cch = 0;
    BOOL fQuote = FALSE;

    while(cch < cchBuf-1 && *szLine && (!FIsSpace(*szLine) || fQuote)) {
        if(*szLine == '"') {
            if(fQuote && szLine[1] == '"') {
                /* Double quote inside a string gets copied as a single
                 * quote */
                szBuf[cch++] = '"';
                szLine += 2;
            } else {
                fQuote = !fQuote;
                ++szLine;
            }
        } else
            szBuf[cch++] = *szLine++;
    }
    szBuf[cch] = 0;
}

BOOL FGetSzParam(LPCSTR szLine, LPCSTR szKey, LPSTR szBuf, int cchBuf)
{
    LPCSTR pch = PchGetParam(szLine, szKey, TRUE);
    if(!pch)
        return FALSE;
    GetParam(pch, szBuf, cchBuf);
    return TRUE;
}

BOOL FGetDwParam(LPCSTR szLine, LPCSTR szKey, DWORD *pdw)
{
    int cch;
    char sz[32];
    LPCSTR pch = PchGetParam(szLine, szKey, TRUE);
    if(!pch)
        return FALSE;
    GetParam(pch, sz, sizeof sz);
    *pdw = DwFromSz(sz, &cch);
    return FIsSpace(sz[cch]);
}

/* END MICROSOFT CODE */

BOOL FGetVectorParam(LPCSTR szLine, LPCSTR szKey, float *pvr)
{
	char sz[63];
	int j = 0, i;

	LPCSTR pch = PchGetParam(szLine, szKey, TRUE);
	if(!pch)
		return FALSE;
	GetParam(pch, sz, sizeof sz);
	
	for(i = 0;i < 4;i++)
	{
		((DWORD*)pvr)[i] = DwFromSz(sz + j, NULL);

		do{	j++; } while(sz[j] != ',');

		if(i < 3 && (sz[j] != ',') && !FIsSpace(sz[j]))
			return FALSE;

		j++;
	}

	return TRUE;
}

BOOL FGetQwordParam(LPCSTR szLine, LPCSTR szKey, ULARGE_INTEGER *plu)
{
    int cch;
    char sz[32];
    LPCSTR pch;

    pch = PchGetParam(szLine, szKey, TRUE);
    if(!pch)
        return FALSE;
    GetParam(pch, sz, sizeof sz - 1);
    sz[sizeof sz - 1] = 0;

    /* Verify the 0q prefix */
    if(sz[0] != '0' || sz[1] != 'q')
        return FALSE;
    /* Make sure we have a bunch of hex characters */
    for(cch = 2; cch < sizeof sz && !FIsSpace(sz[cch]); ++cch) {
        if(!(sz[cch] >= '0' && sz[cch] <= '9' ||
                sz[cch] >= 'A' && sz[cch] <= 'F' ||
                sz[cch] >= 'a' && sz[cch] <= 'f'))
            return FALSE;
    }
    cch -= 2;
    if(cch <= 0)
        return FALSE;

    /* Move the text out to the end of the string and fill the preceding
     * characters with zeroes */
    memmove(&sz[sizeof sz - 1 - cch], &sz[2], cch);
    memset(sz, '0', sizeof sz - 1 - cch);

    /* Now parse out the two dwords */
    plu->LowPart = DwHexFromSz(&sz[sizeof sz - 9], NULL);
    sz[sizeof sz - 9] = 0;
    plu->HighPart = DwHexFromSz(&sz[sizeof sz - 17], NULL);
    return TRUE;
}

BOOL FGetNamedDwParam(LPCSTR szLine, LPCSTR szKey, DWORD *pdw, LPSTR szResp)
{
    if(!FGetDwParam(szLine, szKey, pdw)) {
        RtlSprintf(szResp, "missing %s", szKey);
        return FALSE;
    }
    return TRUE;
}

ULONG UlAddrFromSz(LPCSTR sz)
{
    ULONG ul;
    int ib;
    int ich;

    for(ib = 0; ib < 4; ++ib) {
        BYTE b = 0;

        for(ich = 0; ich < 3; ++ich) {
            if(sz[ich] < '0' || sz[ich] > '9')
                break;
            b = 10 * b + (sz[ich] - '0');
        }
        if(ich == 0 || sz[ich] != (ib == 3 ? 0 : '.'))
            return 0;
        sz += ich + 1;
        ((BYTE *)&ul)[ib ^ 3] = b;
    }
    return ul;
}

void GetFileAttrSz(LPSTR sz, ULONG dwAttributes, PLARGE_INTEGER pliChange,
    PLARGE_INTEGER pliCreate, PLARGE_INTEGER pliSize)
{
    RtlSprintf(sz, "sizehi=0x%x sizelo=0x%x createhi=0x%08x createlo=0x%08x "
        "changehi=0x%08x changelo=0x%08x%s%s%s", pliSize->HighPart,
        pliSize->LowPart, pliCreate->HighPart, pliCreate->LowPart,
        pliChange->HighPart, pliChange->LowPart,
        dwAttributes & FILE_ATTRIBUTE_DIRECTORY ? " directory" : "",
        dwAttributes & FILE_ATTRIBUTE_READONLY ? " readonly" : "",
        dwAttributes & FILE_ATTRIBUTE_HIDDEN ? " hidden" : "");
}

VOID FStopServ()
{
	int i;

	closesocket(sockServ);
	closesocket(sockName);

	for(i = 0;i < CONNECTION_MAX;i++)
		if(rgdmc[i].bActive)
			closesocket(rgdmc[i].s);
}

int FSend(SOCKET s, LPCSTR fmt, ...)
{
	char buf[0x200];

	va_list list;
	va_start(list, fmt);
	RtlVsnprintf(buf, sizeof(buf), fmt, list);
	va_end(list);

	return send(s, buf, strlen(buf), 0);
}

int FSendLine(SOCKET s, LPCSTR fmt, ...)
{
	char buf[0x202];
	int i;

	va_list list;
	va_start(list, fmt);
	i = RtlVsnprintf(buf, sizeof(buf) - 2, fmt, list);
	va_end(list);

	strcat(buf, "\r\n");

	return send(s, buf, i + 2, 0);
}

LPCSTR SzStdResponse(HRESULT hr)
{
    LPCSTR pszResp;

    switch(hr) {
	case XBDM_LINE_TOO_LONG:
		pszResp = "line too long";
		break;
    case XBDM_NOSUCHFILE:
        pszResp = "file not found";
        break;
    case XBDM_NOMODULE:
        pszResp = "no such module";
        break;
    case XBDM_MEMUNMAPPED:
        pszResp = "memory not mapped";
        break;
    case XBDM_NOTHREAD:
        pszResp = "no such thread";
        break;
    case XBDM_INVALIDCMD:
        pszResp = "unknown command";
        break;
    case XBDM_NOTSTOPPED:
        pszResp = "not stopped";
        break;
	case XBDM_ALREADYSTOPPED:
		pszResp = "already stopped";
		break;
    case XBDM_MUSTCOPY:
        pszResp = "file must be copied";
        break;
    case XBDM_ALREADYEXISTS:
        pszResp = "file already exists";
        break;
    case XBDM_DIRNOTEMPTY:
        pszResp = "directory not empty";
        break;
    case XBDM_BADFILENAME:
        pszResp = "filename is invalid";
        break;
    case XBDM_CANNOTCREATE:
        pszResp = "file cannot be created";
        break;
    case XBDM_DEVICEFULL:
        pszResp = "no room on device";
        break;
    case XBDM_MULTIRESPONSE:
        pszResp = "multiline response follows";
        break;
    case XBDM_BINRESPONSE:
        pszResp = "binary response follows";
        break;
    case XBDM_READYFORBIN:
        pszResp = "send binary data";
        break;
    case XBDM_CANNOTACCESS:
        pszResp = "access denied";
        break;
    case XBDM_NOTDEBUGGABLE:
        pszResp = "not debuggable";
        break;
    case XBDM_BADCOUNTTYPE:
        pszResp = "type invalid";
        break;
    case XBDM_COUNTUNAVAILABLE:
        pszResp = "data not available";
        break;
    case XBDM_NOTLOCKED:
        pszResp = "box is not locked";
        break;
    case XBDM_KEYXCHG:
        pszResp = "key exchange required";
        break;
    case XBDM_MUSTBEDEDICATED:
        pszResp = "dedicated connection required";
        break;
    case E_OUTOFMEMORY:
        pszResp = "out of memory";
        break;
    case E_UNEXPECTED:
        pszResp = "unexpected error";
        break;
    case E_INVALIDARG:
        pszResp = "bad parameter";
        break;
    case XBDM_NOERR:
        pszResp = "OK";
        break;
    default:
        pszResp = "";
        break;
    }
    return pszResp;
}

int SendHrSzResp(SOCKET s, HRESULT hr, LPCSTR szResp, LPSTR szBuf)
{
    /* Make sure we have an error code we like */
    if(((hr >> 16) & 0x7fff) != FACILITY_XBDM) {
        hr = SUCCEEDED(hr) ? XBDM_NOERR : XBDM_UNDEFINED;
        if(!szResp)
            szResp = SzStdResponse(E_UNEXPECTED);
    } else if((hr & 0xffff) > 0xff)
        hr = XBDM_UNDEFINED;

    if(FAILED(hr))
        szBuf[0] = '4';
    else
        szBuf[0] = '2';
    szBuf[1] = (char) ('0' + (hr & 0xffff) / 10);   // overflow?
    szBuf[2] = (char) ('0' + (hr & 0xffff) % 10);
    szBuf[3] = '-';
    szBuf[4] = ' ';
    if(szResp != szBuf) {
        if(szResp)
            strcpy(szBuf + 5, szResp);
        else
            szBuf[5] = 0;
    }
    return FSendLine(s, "%s", szBuf);
}

VOID DoReadWrite(PDMCONN pdmc, BOOL bCanRead)
{
	int i, j;
	DWORD dw;
	char sz[0x200];
	char resp[0x200];
	HRESULT hr;

	if(!pdmc->bConversation)
	{
		// We are not currently in a handling function

		// Check for shutdown
		if(pdmc->bShutdown)
		{
			if(!pdmc->bKeepAlive)
				closesocket(pdmc->s);

			ZeroMemory(pdmc, sizeof(DMCONN));

			return;
		}

		// First, scan the buffer to search for newlines
		for(dw = 0;dw < pdmc->dwRecv && (pdmc->szRecv[dw] != '\n');dw++);

		// If i == pdmc->dwRecv then there are no commands in the buffer
		if(dw == pdmc->dwRecv)
		{
			// Recieve into the buffer
			if(bCanRead)
			{
				i = recv(pdmc->s, (char*)pdmc->szRecv + pdmc->dwRecv, sizeof(pdmc->szRecv) - pdmc->dwRecv, 0);
				if(i <= 0)
				{
					pdmc->bShutdown = TRUE;
					return;
				}

				pdmc->dwRecv += i;
			}
		}

		// Scan the buffer for a newline
		for(dw = 0;dw < pdmc->dwRecv && (pdmc->szRecv[dw] != '\n');dw++);

		if(dw != pdmc->dwRecv)
		{
			// We found a command
			if(pdmc->bTooLong)
			{
				SendHrSzResp(pdmc->s, XBDM_LINE_TOO_LONG, "", sz);
				pdmc->bTooLong = FALSE;
				pdmc->dwRecv = 0;

				return;
			}

			// Find the command name
			for(i = 0;(pdmc->szRecv[i]) && (pdmc->szRecv[i] != '\r') && (pdmc->szRecv[i] != '\n') && (pdmc->szRecv[i] != ' ');i++)
				sz[i] = pdmc->szRecv[i];
			sz[i] = 0;

			// Now we just walk the list with our super inefficient algo of BRUTE FORCE SEARCHING
			for(j = 0;j < cchcmd && stricmp(sz, rgbcmd[j].szName);j++);

			if(j == cchcmd) // Command not found
			{
				SendHrSzResp(pdmc->s, XBDM_INVALIDCMD, SzStdResponse(XBDM_INVALIDCMD), sz);

				memcpy(sz, pdmc->szRecv, dw - 1);
				sz[dw - 1] = 0;

				DbgPrint("[xbdm] unknown command \"%s\"\n", sz);
			}
			else if((rgbcmd[j].dwPriv & pdmc->dwPriv) != rgbcmd[j].dwPriv)
			{
				// Not enough permissions
				SendHrSzResp(pdmc->s, XBDM_CANNOTACCESS, SzStdResponse(XBDM_CANNOTACCESS), sz);
			}
			else
			{
				// Command foundzorz

				// Copy the whole string over
				for(i = 0;(pdmc->szRecv[i] != '\r') && (pdmc->szRecv[i] != '\n');i++)
					sz[i] = pdmc->szRecv[i];
				
				sz[i] = 0;
				resp[0] = 0;

				// Setup some final state information
				pdmc->dmcc.Buffer = NULL;
				pdmc->dmcc.BufferSize = 0;
				pdmc->dmcc.BytesRemaining = 0;
				pdmc->dmcc.CustomData = &pdmc->dmcd;
				pdmc->dmcc.DataSize = -1;
				pdmc->dmcc.HandlingFunction = NULL;

				pdmc->hr = hr = rgbcmd[j].pdmcp(sz, resp, sizeof(resp), &pdmc->dmcc);

				if(hr == XBDM_MULTIRESPONSE
					|| hr == XBDM_BINRESPONSE
					|| hr == XBDM_READYFORBIN)
					pdmc->bConversation = TRUE;

				if(!pdmc->bKeepAlive)
				{
					if(resp[0])
					{
						if(SendHrSzResp(pdmc->s, hr, resp, sz) <= 0)
							pdmc->bShutdown = TRUE;
					}
					else if(SendHrSzResp(pdmc->s, hr, SzStdResponse(hr), sz) <= 0)
						pdmc->bShutdown = TRUE;
				}
			}

			// Fetch the index of the \n
			for(i = 0;pdmc->szRecv[i] != '\n';i++);

			// Move the memory
			memmove(pdmc->szRecv, pdmc->szRecv + (i + 1), sizeof(pdmc->szRecv) - (i + 1));

			// Adjust the vars
			pdmc->dwRecv -= i + 1;
		}
		else if(pdmc->dwRecv == sizeof(pdmc->szRecv))
			pdmc->bTooLong = TRUE; // Overflow....

		// On overflow, just ignore the rest of the data until newline
		if(pdmc->bTooLong)
			pdmc->dwRecv = 0;
	}
	else
	{
		// We are currently in a handling function

		ASSERT(pdmc->dmcc.HandlingFunction);

		if(pdmc->dmcc.Buffer == NULL)
		{
			pdmc->dmcc.Buffer = pdmc->szBuf;
			pdmc->dmcc.BufferSize = sizeof(pdmc->szBuf);
		}

		// Check for shutdown
		if(pdmc->bShutdown)
		{
			if(pdmc->hr == XBDM_READYFORBIN)
			{
				// Multiline responses are free to continue, but they wont go anywhere
				pdmc->dmcc.DataSize = 0;
				pdmc->bConversation = FALSE;
			}
		}

		if(pdmc->hr == XBDM_READYFORBIN)
		{
			if(bCanRead)
			{
				if(!pdmc->bShutdown)
				{
					i = recv(pdmc->s, (char*)pdmc->dmcc.Buffer,
						pdmc->dmcc.BytesRemaining > pdmc->dmcc.BufferSize ? pdmc->dmcc.BufferSize : pdmc->dmcc.BytesRemaining,
						0);

					if(i <= 0)
					{
						pdmc->dmcc.DataSize = 0;
						pdmc->bShutdown = TRUE;
					}
					else
						pdmc->dmcc.DataSize = i;
				}

				hr = pdmc->dmcc.HandlingFunction(&pdmc->dmcc, resp, sizeof(resp));

				if(!pdmc->bShutdown)
				{
					if(pdmc->dmcc.BytesRemaining == 0)
					{
						if(hr == XBDM_MULTIRESPONSE
						|| hr == XBDM_BINRESPONSE
						|| hr == XBDM_READYFORBIN)
						{
							pdmc->hr = hr;
							pdmc->bConversation = TRUE;
							pdmc->dmcc.DataSize = 0;
						}
						else
						{
							pdmc->bConversation = FALSE;
							pdmc->dmcc.HandlingFunction = NULL;
						}

						SendHrSzResp(pdmc->s, hr, SzStdResponse(hr), sz);
					}
				}

				if(pdmc->bShutdown)
					pdmc->bConversation = FALSE;
			}
		}
		else
		{
			if(pdmc->bShutdown || pdmc->dmcc.DataSize == 0 || pdmc->dmcc.DataSize == -1)
			{
				// Multiline/binary
				pdmc->dmcc.DataSize = -1;
#ifdef _DEBUG
				hr = pdmc->dmcc.HandlingFunction(&pdmc->dmcc, NULL, 0x100); // This way i can catch those annoying errors
#else
				hr = pdmc->dmcc.HandlingFunction(&pdmc->dmcc, NULL, 0);
#endif

				pdmc->Buffer = pdmc->dmcc.Buffer;
			}

			if(pdmc->bShutdown)
			{
				if(FAILED(hr)
					|| hr == XBDM_MULTIRESPONSE
					|| hr == XBDM_BINRESPONSE
					|| hr == XBDM_READYFORBIN) // Just let them keep talking
					pdmc->bConversation = FALSE;
			}
			else
			{
				if(hr == XBDM_ENDOFLIST
						|| hr == XBDM_MULTIRESPONSE
						|| hr == XBDM_BINRESPONSE
						|| hr == XBDM_READYFORBIN)
				{
					if(pdmc->hr == XBDM_MULTIRESPONSE)
						FSend(pdmc->s, ".\r\n");

					pdmc->bConversation = FALSE;

					if(hr == XBDM_MULTIRESPONSE
						|| hr == XBDM_BINRESPONSE
						|| hr == XBDM_READYFORBIN)
					{
						pdmc->hr = hr;
						pdmc->bConversation = TRUE;
					}
					else
						pdmc->dmcc.HandlingFunction = NULL;
				}
				else if(NT_SUCCESS(hr))
				{
					if(pdmc->dmcc.DataSize == -1)
					{
						// Null terminated string with a newline
						if(FSend(pdmc->s, "%s\r\n", pdmc->dmcc.Buffer) <= 0)
							pdmc->bShutdown = TRUE;
					}
					else if(pdmc->dmcc.DataSize != 0)
					{
						// Binary data
						if((i = send(pdmc->s, (char*)pdmc->Buffer, pdmc->dmcc.DataSize, 0)) <= 0)
							pdmc->bShutdown = TRUE;

						pdmc->dmcc.DataSize -= i;
						pdmc->Buffer = (PVOID)((DWORD)pdmc->Buffer + i);
					}
				}
				else
				{
					if(pdmc->dmcc.DataSize == -1)
						FSend(pdmc->s, "%s\r\n", pdmc->dmcc.Buffer);

					// Forcefully terminate the connection
					pdmc->bShutdown = TRUE;
					pdmc->bConversation = FALSE;
				}
			}
		}
	}
}

VOID AnswerName(SOCKET s)
{
	struct {
		BYTE bRequest;
		BYTE cchName;
		char szName[256];
	} nm;

	SOCKADDR_IN sin;
	int cbAddr = sizeof(sin);
	int cbPkt;

	cbPkt = recvfrom(s, (char*)&nm, sizeof(nm), 0, (SOCKADDR*)&sin, &cbAddr);
	switch(nm.bRequest)
	{
	case 1:
	case 3:
		if(nm.bRequest == 1)
		{
			nm.bRequest = 0;

			if(cbPkt < 2 || cbPkt < (2 + nm.cchName))
				break;

			if(!nm.cchName || strcmpi(nm.szName, g_dmGlobals.rgchDbgName))
				break;
		}

		nm.bRequest = 2;
		break;
	default:
		nm.bRequest = 0;
		break;
	}

	if(nm.bRequest)
		sendto(s, (char*)&nm, cbPkt, 0, (SOCKADDR*)&sin, cbAddr);
}

ULONG __stdcall ServerThread(LPVOID lpParam)
{
	SOCKET sock;
	BOOL bReuse;
	SOCKADDR_IN sin;
	FD_SET readfds, writefds;
	struct timeval timeout;
	XNADDR xna;
	DMTD *pdmtd;
	int i;

	KeSetBasePriorityThread(PsGetCurrentThread(), THREAD_PRIORITY_TIME_CRITICAL);
	pdmtd = DmGetCurrentDmtd();

	pdmtd->DebugFlags |= DMFLAG_DEBUGTHREAD;

	VSetThreadName(-1, "Debugger Command Thread");

	ZeroMemory(rgdmc, sizeof(rgdmc));

	do
	{
		// Well, this IS the server thread, so if we can't start a server then screw you
		Sleep(5000);
		sockServ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	} while(sockServ == INVALID_SOCKET);

	bReuse = TRUE;
	if(setsockopt(sockServ, SOL_SOCKET, SO_DECRYPTSOCK, (char*)&bReuse, sizeof(bReuse)))
	{
		DbgPrint("[xbdm] failed %i\n", WSAGetLastError());
		DebugBreak();
	}
	if(setsockopt(sockServ, SOL_SOCKET, SO_REUSEADDR, (char*)&bReuse, sizeof(bReuse)))
	{
		DbgPrint("[xbdm] failed %i\n", WSAGetLastError());
		DebugBreak();
	}

	sin.sin_family = AF_INET;
	sin.sin_port = 730;
	sin.sin_addr.s_addr = INADDR_ANY;
	if(bind(sockServ, (SOCKADDR*)&sin, sizeof(sin))
		|| listen(sockServ, 8))
	{
		DbgPrint("[xbdm] failed %i\n", WSAGetLastError());
		DebugBreak();
		goto abortsocket;
	}

	sockName = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if(setsockopt(sockName, SOL_SOCKET, SO_DECRYPTSOCK, (char*)&bReuse, sizeof(bReuse)))
	{
		DbgPrint("[xbdm] failed %i\n", WSAGetLastError());
		DebugBreak();
	}
	if(setsockopt(sockName, SOL_SOCKET, SO_REUSEADDR, (char*)&bReuse, sizeof(bReuse)))
	{
		DbgPrint("[xbdm] failed %i\n", WSAGetLastError());
		DebugBreak();
	}
	if(setsockopt(sockName, SOL_SOCKET, SO_BROADCAST, (char*)&bReuse, sizeof(bReuse)))
	{
		DbgPrint("[xbdm] failed %i\n", WSAGetLastError());
		DebugBreak();
	}
	if(bind(sockName, (SOCKADDR*)&sin, sizeof(sin)))
	{
		DbgPrint("[xbdm] failed %i\n", WSAGetLastError());
		DebugBreak();
	}

	DbgPrint("[xbdm] server started\n");

	for(;;)
	{
		readfds.fd_count = 0;
		writefds.fd_count = 0;

		FD_SET(sockServ, &readfds);
		FD_SET(sockName, &readfds);

		for(i = 0;i < CONNECTION_MAX;i++)
		{
			if(rgdmc[i].bActive)
				FD_SET(rgdmc[i].s, &readfds);
		}

		timeout.tv_sec = 0;
		timeout.tv_usec = 0;

		if(g_dmGlobals.bDirty)
		{
			FWriteGlobals();

			g_dmGlobals.bDirty = FALSE;
		}

		if(!g_dmGlobals.bHasIp)
		{
			i = XNetGetTitleXnAddr(&xna);
			if(i != XNET_GET_XNADDR_PENDING)
			{
				DbgPrint("[xbdm] IP Address Acquired [%i.%i.%i.%i] (0x%08x)\n",
					xna.ina.S_un.S_un_b.s_b1, xna.ina.S_un.S_un_b.s_b2,
					xna.ina.S_un.S_un_b.s_b3, xna.ina.S_un.S_un_b.s_b4,
					i);

				g_dmGlobals.bHasIp = TRUE;
			}
		}

		// Yield to others (its the right thing to do)
		Sleep(0);

		ProcessQueuedNotifications();

		select(0, &readfds, &writefds, NULL, &timeout);

		if(FD_ISSET(sockName, &readfds))
			AnswerName(sockName);

		if(FD_ISSET(sockServ, &readfds))
		{
			i = sizeof(sin);
			sock = accept(sockServ, (SOCKADDR*)&sin, &i);

			for(i = 0;i < CONNECTION_MAX;i++)
			{
				if(!rgdmc[i].bActive)
				{
					rgdmc[i].bActive = TRUE;
					rgdmc[i].s = sock;
					memcpy(&rgdmc[i].sin, &sin, sizeof(sin));
					break;
				}
			}

			if(i == CONNECTION_MAX)
			{
				// No more connection slots
				FSendLine(sock, "401- max number of connections exceeded");
				closesocket(sock);
			}
			else
			{
				// Some quick init

				// Give all permssions, as we dont have locking yet
				rgdmc[i].dwPriv = DMPL_PRIV_READ | DMPL_PRIV_WRITE | DMPL_PRIV_CONFIGURE | DMPL_PRIV_CONTROL;
				
				// Only give hypervisor access if its enabled
				if(g_dmGlobals.bHypervisorEnabled)
					rgdmc[i].dwPriv |= DMPL_PRIV_HVX_MASK;

				// Say hello!
				FSendLine(rgdmc[i].s, "201- connected");
			}
		}

		for(i = 0;i < CONNECTION_MAX;i++)
		{
			if(rgdmc[i].bActive)
				DoReadWrite(&rgdmc[i], FD_ISSET(rgdmc[i].s, &readfds));
		}
	}

abortsocket:
	closesocket(sockServ);

	DebugBreak();
	return 0;
}

DMHRAPI HrGetAltAddr(LPCSTR szCommand, LPSTR szResponse,
    DWORD cchResponse, PDM_CMDCONT pdmcc)
{
	XNADDR xna;
	DWORD dw;

	if(!pdmcc)
		return E_FAIL;

	dw = XNetGetTitleXnAddr(&xna);

	if(dw == XNET_GET_XNADDR_PENDING || dw == XNET_GET_XNADDR_NONE)
		return E_FAIL;

	RtlSnprintf(szResponse, cchResponse, "addr=0x%08x", xna.ina.s_addr);

	return XBDM_NOERR;
}

DMHRAPI HrEndConversation(LPCSTR szCommand, LPSTR szResponse,
    DWORD cchResponse, PDM_CMDCONT pdmcc)
{
	PDMCONN pdmc;

	if(!pdmcc)
		return E_FAIL;

	// Snag the structure
	pdmc = CONTAINING_RECORD(pdmcc, DMCONN, dmcc);

	// Say goodbye
	strcpy(szResponse, "bye");

	// Signal shutdown
	pdmc->bShutdown = TRUE;

	return XBDM_NOERR;
}

DMHRAPI HrMagicReboot(LPCSTR szCommand, LPSTR szResponse,
	DWORD cchResponse, PDM_CMDCONT pdmcc)
{
	PDMCONN pdmc;

	char szTmp[MAX_PATH];
	char szLaunchPath[MAX_PATH];
	char szMountPath[MAX_PATH];
	char szCmdLine[MAX_PATH];

	DWORD dwMask = 0;
	HRESULT hr = XBDM_NOERR;

	szCmdLine[0] = 0;
	szMountPath[0] = 0;
	szLaunchPath[0] = 0;

	if(PchGetParam(szCommand, "wait", FALSE))
		dwMask = DMBOOT_WAIT;
	else if(PchGetParam(szCommand, "stop", FALSE))
		dwMask = DMBOOT_STOP;
	if(PchGetParam(szCommand, "cold", FALSE))
		dwMask |= DMBOOT_COLD;

	// TODO: if(stopped and exception) flag |= cold
	if(FGetSzParam(szCommand, "title", szTmp, sizeof(szTmp)))
	{
		if(szTmp[0] == '\\')
			strcpy_s(szLaunchPath, sizeof(szLaunchPath), szTmp);
		else if(FAILED(FFileNameToObName(szTmp, szLaunchPath, sizeof(szLaunchPath))))
			hr = XBDM_NOSUCHFILE;
	}
	if(FGetSzParam(szCommand, "directory", szTmp, sizeof(szTmp)))
	{
		if(szTmp[0] == '\\')
			strcpy_s(szMountPath, sizeof(szMountPath), szTmp);
		else if(FAILED(FFileNameToObName(szTmp, szMountPath, sizeof(szMountPath))))
			hr = XBDM_NOSUCHFILE;
	}

	FGetSzParam(szCommand, "cmdline", szCmdLine, sizeof(szCmdLine));

	if(NT_SUCCESS(hr))
	{
		if(dwMask & DMBOOT_COLD)
		{
			pdmc = CONTAINING_RECORD(pdmcc, DMCONN, dmcc);
			FSendLine(pdmc->s, "200- OK");

			Sleep(200);
			FStopServ();
		}

		DmRebootEx(dwMask, szLaunchPath, szMountPath, szCmdLine);
	}

	return XBDM_NOERR;
}

DMHRAPI HrGetConsoleFeatures(LPCSTR szCommand, LPSTR szResponse,
	DWORD cchResponse, PDM_CMDCONT pdmcc)
{
	if(!pdmcc)
		return E_FAIL;

	strcpy_s(szResponse, cchResponse, "DEBUGGING");

	if(g_dmGlobals.dwConsoleColor & CONSOLE_COLOR_FLAG_BLUE)
		strcat_s(szResponse, cchResponse, " 1GB_RAM");

	return XBDM_NOERR;
}

DMHRAPI HrGetConsoleType(LPCSTR szCommand, LPSTR szResponse,
	DWORD cchResponse, PDM_CMDCONT pdmcc)
{
	if(!pdmcc)
		return E_FAIL;

	if(g_dmGlobals.dwConsoleColor & CONSOLE_COLOR_FLAG_BLACK)
		strcpy_s(szResponse, cchResponse, "devkit");
	else if(g_dmGlobals.dwConsoleColor & CONSOLE_COLOR_FLAG_WHITE)
		strcpy_s(szResponse, cchResponse, "testkit");
	else
		strcpy_s(szResponse, cchResponse, "reviewerkit");
		

	return XBDM_NOERR;
}

DMHRAPI HrDbgName(LPCSTR szCommand, LPSTR szResponse,
	DWORD cchResponse, PDM_CMDCONT pdmcc)
{
	char sz[256];

	if(FGetSzParam(szCommand, "name", sz, sizeof(sz)))
	{
		strcpy_s(g_dmGlobals.rgchDbgName, 256, sz);
		g_dmGlobals.bDirty = TRUE;

		return XBDM_NOERR;
	}

	strcpy_s(szResponse, cchResponse, g_dmGlobals.rgchDbgName);
	return XBDM_NOERR;
}

DMHRAPI HrDrivemap(LPCSTR szCommand, LPSTR szResponse,
	DWORD cchResponse, PDM_CMDCONT pdmcc)
{
	if(PchGetParam(szCommand, "internal", FALSE))
		g_dmGlobals.bDriveMap = TRUE;
	else
		g_dmGlobals.bDriveMap = FALSE;

	g_dmGlobals.bDirty = TRUE;

	return XBDM_NOERR;
}

DMHRAPI HrReportHelpInfo(PDM_CMDCONT pdmcc, LPSTR szResponse, DWORD cchResponse)
{
	if((int)pdmcd->cch >= cchcmd)
		return XBDM_ENDOFLIST;

	strcpy_s((char*)pdmcc->Buffer, pdmcc->BufferSize, rgbcmd[pdmcd->cch].szName);
	pdmcd->cch++;

	return XBDM_NOERR;
}

DMHRAPI HrHelp(LPCSTR szCommand, LPSTR szResponse,
	DWORD cchResponse, PDM_CMDCONT pdmcc)
{
	if(!pdmcc)
		return E_FAIL;

	pdmcc->HandlingFunction = HrReportHelpInfo;
	pdmcc->BufferSize = 1;
	pdmcd->cch = 0;
	
	strcpy_s(szResponse, cchResponse, "command names follow");

	return XBDM_MULTIRESPONSE;
}

DMHRAPI HrReboot(LPCSTR szCommand, LPSTR szResponse,
	DWORD cchResponse, PDM_CMDCONT pdmcc)
{
	if(!pdmcc)
		return E_FAIL;

	FStopServ();

	HalReturnToFirmware(6);
	return XBDM_NOERR;
}

DMHRAPI HrSetSystemTime(LPCSTR szCommand, LPSTR szResponse,
	DWORD cchResponse, PDM_CMDCONT pdmcc)
{
	ULARGE_INTEGER lu, luUnused;

	if(!pdmcc)
		return E_FAIL;
	
	if(!FGetDwParam(szCommand, "clockhi", &lu.HighPart) || !FGetDwParam(szCommand, "clocklo", &lu.LowPart))
		return XBDM_CLOCKNOTSET;

	NtSetSystemTime((PFILETIME)&lu, (PFILETIME)&luUnused);
	XnpNoteSystemTime();

	g_dmGlobals.fClockSet = TRUE;

	return XBDM_NOERR;
}

DMHRAPI HrGetSystemTime(LPCSTR szCommand, LPSTR szResponse,
	DWORD cchResponse, PDM_CMDCONT pdmcc)
{
	ULARGE_INTEGER lu;

	if(!pdmcc)
		return E_FAIL;

	if(!g_dmGlobals.fClockSet)
		return XBDM_CLOCKNOTSET;

	KeQuerySystemTime(&lu);
	
	RtlSnprintf(szResponse, cchResponse, "high=0x%x low=0x%x", lu.HighPart, lu.LowPart);

	return XBDM_NOERR;
}

DMHRAPI HrShutdown(LPCSTR szCommand, LPSTR szResponse,
	DWORD cchResponse, PDM_CMDCONT pdmcc)
{
	if(!pdmcc)
		return E_FAIL;

	FStopServ();

	HalReturnToFirmware(5);
	return XBDM_NOERR;
}

DMHRAPI HrSpew(LPCSTR szCommand, LPSTR szResponse,
	DWORD cchResponse, PDM_CMDCONT pdmcc)
{
	DbgPrint("SPEW: %s\n", szCommand);
	return XBDM_NOERR;
}

DMHRAPI HrReportXbeInfo(PDM_CMDCONT pdmcc, LPSTR szResponse, DWORD cchResponse)
{
	PDM_XBE pdxbe = (PDM_XBE)pdmcc->CustomData;
	int i;

	if(pdmcc->BytesRemaining == 3)
	{
		DmFreePool(pdmcc->CustomData);
		return XBDM_ENDOFLIST;
	}
	else if(pdmcc->BytesRemaining == 2)
	{
		i = strlen(pdxbe->LaunchPath);

		pdxbe->LaunchPath[i++] = '"';
		pdxbe->LaunchPath[i + 1] = 0;
		memmove(pdxbe->LaunchPath + 6, pdxbe->LaunchPath, i++);
		memcpy(pdxbe->LaunchPath, "name=\"", 6);

		pdmcc->Buffer = pdxbe->LaunchPath;
		pdmcc->BytesRemaining++;
	}
	else if(pdmcc->BytesRemaining == 1)
	{
		RtlSnprintf((char*)pdmcc->Buffer, pdmcc->BufferSize, "timestamp=0x%08x checksum=0x%08x", pdxbe->TimeStamp, pdxbe->CheckSum);

		pdmcc->BytesRemaining++;
	}

	return XBDM_NOERR;
}

DMHRAPI HrGetXbeInfo(LPCSTR szCommand, LPSTR szResponse,
	DWORD cchResponse, PDM_CMDCONT pdmcc)
{
	PDM_XBE pdxbe;
	DWORD dwFlags = 0;
	char sz[0x200];
	LPCSTR szName;
	HRESULT hr;

	if(!pdmcc)
		return E_FAIL;

	if(PchGetParam(szCommand, "running", FALSE))
		szName = NULL;
	else if(FGetSzParam(szCommand, "name", sz, sizeof(sz)))
	{
		szName = sz;

		if(PchGetParam(szCommand, "ondiskonly", FALSE))
			dwFlags = DM_XBEONDISKONLY;
	}
	else
	{
		strcpy_s(szResponse, cchResponse, "missing name");
		return E_FAIL;
	}

	pdxbe = (PDM_XBE)DmAllocatePoolWithTag(sizeof(DM_XBE), 'Xbdm');
	pdmcc->CustomData = pdxbe;

	if(!pdxbe)
		return E_OUTOFMEMORY;

	hr = DmGetXbeInfoEx(szName, pdxbe, dwFlags);
	
	if(NT_SUCCESS(hr))
	{
		pdmcc->HandlingFunction = HrReportXbeInfo;
		pdmcc->BytesRemaining = 1;

		hr = XBDM_MULTIRESPONSE;
	}
	else
		DmFreePool(pdxbe);

	return hr;
}

DMHRAPI HrReportDriveList(PDM_CMDCONT pdmcc, LPSTR szResponse, DWORD cchResponse)
{
	CHAR sz[MAX_PATH];
	NTSTATUS st;
	ANSI_STRING as;
	OBJECT_ATTRIBUTES oa;
	BOOL bExists = FALSE;
	OBJECT_DIRECTORY_INFORMATION odi;
	HANDLE h;
	int i;

start:
	if(pdmcd->cch == 0)
	{
		// List from our interal list

		i = Drives[pdmcd->DriveList.CurrentDrive].Visibility;

		// Check verbosity
		if(i != 0 && !(i == 1 && !g_dmGlobals.bDriveMap))
		{
			// Get name
			strcpy(sz, Drives[pdmcd->DriveList.CurrentDrive].DriveName);
			i = strlen(sz);
			strcat(sz, ":\\");

			st = FCreateFile(&h, SYNCHRONIZE, sz, NULL, 0, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
				FILE_OPEN, FILE_DIRECTORY_FILE | FILE_SYNCHRONOUS_IO_NONALERT);
			if(NT_SUCCESS(st))
			{
				sz[i] = 0;
				bExists = TRUE;
				NtClose(h);
			}
		}

		pdmcd->DriveList.CurrentDrive++;

		if(pdmcd->DriveList.CurrentDrive >= cchDrives)
		{
			// Move on to the actual object enumeration
			pdmcd->cch = 1;

			RtlInitAnsiString(&as, "\\??");
			oa.Attributes = OBJ_CASE_INSENSITIVE;
			oa.ObjectName = &as;
			oa.RootDirectory = NULL;

			pdmcd->DriveList.CurrentDrive = 0;

			st = NtOpenDirectoryObject(&pdmcd->h, &oa);

			if(FAILED(st))
			{
				pdmcd->h = INVALID_HANDLE_VALUE;
				pdmcd->cch = 2;
			}
		}
	}
	else if(pdmcd->cch == 1)
	{
		// List the objects
		st = NtQueryDirectoryObject(pdmcd->h, &odi, sizeof(odi), (pdmcd->DriveList.CurrentDrive == 0), (PULONG)&pdmcd->DriveList.CurrentDrive, NULL);
		if(NT_SUCCESS(st))
		{
			// Attempt to open the device that we found
			memcpy(sz, odi.Name.Buffer, odi.Name.Length);

			// But first, check the drive list
			sz[odi.Name.Length - 1] = 0;
			for(i = 0;i < cchDrives;i++)
			{
				if(!strcmpi(Drives[i].DriveName, sz))
				{
					bExists = TRUE;
					break;
				}
			}

			if(bExists)
				bExists = FALSE;
			else
			{
				strcat(sz, ":\\");

				st = FCreateFile(&h, SYNCHRONIZE, sz, NULL, 0,
					FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
					FILE_OPEN, FILE_DIRECTORY_FILE | FILE_SYNCHRONOUS_IO_NONALERT);
				if(NT_SUCCESS(st))
				{
					NtClose(h);
					sz[odi.Name.Length - 1] = 0;
					bExists = TRUE;
				}
			}
		}
		else
		{
			NtClose(pdmcd->h);
			pdmcd->cch = 2;
		}
	}
	else
		return XBDM_ENDOFLIST;

	if(bExists)
		RtlSnprintf((char*)pdmcc->Buffer, pdmcc->BufferSize, "drivename=\"%s\"", sz);
	else
		goto start;

	return XBDM_NOERR;
}

DMHRAPI HrGetDriveList(LPCSTR szCommand, LPSTR szResponse,
	DWORD cchResponse, PDM_CMDCONT pdmcc)
{
	if(!pdmcc)
		return E_FAIL;

	pdmcd->cch = 0;
	pdmcd->DriveList.CurrentDrive = 0;
	pdmcd->h = INVALID_HANDLE_VALUE;
	
	pdmcc->BytesRemaining = 1;
	pdmcc->HandlingFunction = HrReportDriveList;

	return XBDM_MULTIRESPONSE;
}

DMHRAPI HrReportDriveFreeSpace(PDM_CMDCONT pdmcc, LPSTR szResponse, DWORD cchResponse)
{
	FILE_FS_SIZE_INFORMATION fsi;
	IO_STATUS_BLOCK iosb;
	DWORD dwBPU;
	ULARGE_INTEGER ulFree, ulTotal;
	NTSTATUS st;

	if(pdmcd->cch)
		return XBDM_ENDOFLIST;

	pdmcd->cch = 1;

	st = NtQueryVolumeInformationFile(pdmcd->h, &iosb, &fsi, sizeof(fsi), FileFsSizeInformation);

	if(FAILED(st))
	{
		RtlSnprintf((char*)pdmcc->Buffer, pdmcc->BufferSize, "unknown error (%d)", st);
		return E_FAIL;
	}

	dwBPU = fsi.SectorsPerAllocationUnit * fsi.BytesPerSector;

	ulFree.QuadPart = fsi.AvailableAllocationUnits.QuadPart * dwBPU;
	ulTotal.QuadPart = fsi.TotalAllocationUnits.QuadPart * dwBPU;

	RtlSnprintf((char*)pdmcc->Buffer, pdmcc->BufferSize, "freetocallerlo=0x%08x freetocallerhi=0x%08x totalbyteslo=0x%08x totalbyteshi=0x%08x totalfreebyteslo=0x%08x totalfreebyteshi=0x%08x",
		ulFree.LowPart, ulFree.HighPart, ulTotal.LowPart, ulTotal.HighPart, ulFree.LowPart, ulFree.HighPart);

	return XBDM_NOERR;
}

DMHRAPI HrGetDriveFreeSpace(LPCSTR szCommand, LPSTR szResponse,
	DWORD cchResponse, PDM_CMDCONT pdmcc)
{
	NTSTATUS st;
	char sz[MAX_PATH];

	if(!pdmcc)
		return E_FAIL;

	if(!FGetSzParam(szCommand, "name", sz, sizeof(sz)))
	{
		strcpy(szResponse, "missing name");
		return E_FAIL;
	}

	st = FCreateFile(&pdmcd->h, FILE_READ_ATTRIBUTES, sz, NULL, 0, FILE_SHARE_READ | FILE_SHARE_WRITE, FILE_OPEN,
		FILE_DIRECTORY_FILE | FILE_SYNCHRONOUS_IO_NONALERT);

	if(FAILED(st))
		return XBDM_CANNOTACCESS;
	
	pdmcd->cch = 0;
	pdmcc->HandlingFunction = HrReportDriveFreeSpace;

	return XBDM_MULTIRESPONSE;
}

DMHRAPI HrReportDirList(PDM_CMDCONT pdmcc, LPSTR szResponse, DWORD cchResponse)
{
	NTSTATUS st;
	IO_STATUS_BLOCK iosb;
	FILE_DIRECTORY_INFORMATION fna;
	HRESULT hr = XBDM_NOERR;

	ZeroMemory(&fna, sizeof(fna));
	st = NtQueryDirectoryFile(pdmcd->h, NULL, NULL, NULL, &iosb,
		&fna, sizeof(fna), NULL, NULL);

	if(NT_SUCCESS(st))
	{
		RtlSnprintf((char*)pdmcc->Buffer, pdmcc->BufferSize, "name=\"%s\" ", fna.FileName);
		GetFileAttrSz((char*)pdmcc->Buffer + strlen((char*)pdmcc->Buffer), fna.FileAttributes,
			&fna.LastWriteTime, &fna.CreationTime, &fna.EndOfFile);
	}
	else
	{
		NtClose(pdmcd->h);
		hr = XBDM_ENDOFLIST;
	}

	return hr;
}

DMHRAPI HrGetDirList(LPCSTR szCommand, LPSTR szResponse,
	DWORD cchResponse, PDM_CMDCONT pdmcc)
{
	NTSTATUS st;
	CHAR sz[MAX_PATH];

	if(!pdmcc)
		return E_FAIL;

	if(!FGetSzParam(szCommand, "name", sz, sizeof(sz)))
	{
		strcpy(szResponse, "missing name");
		return E_FAIL;
	}

	pdmcc->BytesRemaining = 1;
	pdmcc->HandlingFunction = HrReportDirList;

	st = FCreateFile(&pdmcd->h, FILE_LIST_DIRECTORY | SYNCHRONIZE, sz, NULL, 0,
		FILE_SHARE_READ | FILE_SHARE_WRITE, FILE_OPEN,
		FILE_DIRECTORY_FILE | FILE_SYNCHRONOUS_IO_NONALERT);

	return NT_SUCCESS(st) ? XBDM_MULTIRESPONSE : XBDM_CANNOTACCESS;
}

DMHRAPI HrDvdEject(LPCSTR szCommand, LPSTR szResponse,
	DWORD cchResponse, PDM_CMDCONT pdmcc)
{
	DWORD dwEject = 1;

	if(!pdmcc)
		return E_FAIL;

	FGetDwParam(szCommand, "eject", &dwEject);

	HalOpenCloseODDTray(dwEject);

	return XBDM_NOERR;
}

DMHRAPI HrDelete(LPCSTR szCommand, LPSTR szResponse,
	DWORD cchResponse, PDM_CMDCONT pdmcc)
{
	FILE_DISPOSITION_INFORMATION fdi;
	IO_STATUS_BLOCK iosb;
	char sz[MAX_PATH];
	NTSTATUS st;
	HANDLE h;
	BOOL b;

	if(!pdmcc)
		return E_FAIL;

	if(!FGetSzParam(szCommand, "name", sz, sizeof(sz)))
	{
		strcpy_s(szResponse, cchResponse, "missing name");
		return E_FAIL;
	}

	b = (BOOL)PchGetParam(szCommand, "dir", FALSE);

	st = FCreateFile(&h, DELETE | SYNCHRONIZE, sz, NULL, 0, 0,
		FILE_OPEN, (b ? FILE_DIRECTORY_FILE : FILE_NON_DIRECTORY_FILE)
		| FILE_SYNCHRONOUS_IO_NONALERT);

	if(FAILED(st))
		return XBDM_CANNOTACCESS;

	ZeroMemory(&fdi, sizeof(fdi));
	fdi.DeleteFile = TRUE;

	st = NtSetInformationFile(h, &iosb, &fdi, sizeof(fdi), FileDispositionInformation);
	NtClose(h);

	if(FAILED(st))
		return XBDM_CANNOTACCESS;

	return XBDM_NOERR;
}

DMHRAPI HrCreateDirectory(LPCSTR szCommand, LPSTR szResponse,
	DWORD cchResponse, PDM_CMDCONT pdmcc)
{
	char sz[MAX_PATH];
	NTSTATUS st;
	HANDLE h;

	if(!pdmcc)
		return E_FAIL;

	if(!FGetSzParam(szCommand, "name", sz, sizeof(sz)))
	{
		strcpy_s(szResponse, cchResponse, "missing name");
		return E_FAIL;
	}

	st = FCreateFile(&h, FILE_LIST_DIRECTORY | SYNCHRONIZE, sz,
		NULL, FILE_ATTRIBUTE_NORMAL, 0, FILE_CREATE, FILE_DIRECTORY_FILE |
		FILE_SYNCHRONOUS_IO_NONALERT);

	if(FAILED(st))
	{
		if(st == STATUS_OBJECT_NAME_COLLISION)
			return XBDM_ALREADYEXISTS;
		return XBDM_CANNOTCREATE;
	}

	NtClose(h);
	return XBDM_NOERR;
}

DMHRAPI HrRenameFile(LPCSTR szCommand, LPSTR szResponse,
	DWORD cchResponse, PDM_CMDCONT pdmcc)
{
	char sz[MAX_PATH];
	char szNew[MAX_PATH];
	IO_STATUS_BLOCK iosb;
	NTSTATUS st;
	HANDLE h;
	FILE_RENAME_INFORMATION fri;

	if(!pdmcc)
		return E_FAIL;

	if(!FGetSzParam(szCommand, "newname", sz, sizeof(sz)))
	{
		strcpy_s(szResponse, cchResponse, "missing newname");
		return E_FAIL;
	}
	if(FAILED(FFileNameToObName(sz, szNew, sizeof(szNew))))
	{
		strcpy_s(szResponse, cchResponse, "new name does not exist");
		return XBDM_NOSUCHFILE;
	}
	if(!FGetSzParam(szCommand, "name", sz, sizeof(sz)))
	{
		strcpy_s(szResponse, cchResponse, "missing name");
		return E_FAIL;
	}

	st = FCreateFile(&h, GENERIC_WRITE | SYNCHRONIZE, sz, NULL, 0, 0,
		FILE_OPEN, FILE_SYNCHRONOUS_IO_NONALERT);
	
	if(FAILED(st))
		return XBDM_CANNOTACCESS;

	ZeroMemory(&fri, sizeof(fri));
	
	RtlInitAnsiString(&fri.FileName, szNew);
	fri.ReplaceIfExists = FALSE;
	fri.RootDirectory = NULL;

	st = NtSetInformationFile(h, &iosb, &fri, sizeof(fri), FileRenameInformation);
	NtClose(h);

	if(st == STATUS_NOT_SAME_DEVICE)
		return XBDM_MUSTCOPY;

	if(FAILED(st))
		return XBDM_CANNOTCREATE;

	return XBDM_NOERR;
}

DMHRAPI HrReportFileAttributes(PDM_CMDCONT pdmcc, LPSTR szResponse, DWORD cchResponse)
{
	if(pdmcd->cch)
		return XBDM_ENDOFLIST;

	pdmcd->cch = 1;

	GetFileAttrSz((LPSTR)pdmcc->Buffer, pdmcd->fni.fni.FileAttributes,
		&pdmcd->fni.fni.LastWriteTime, &pdmcd->fni.fni.CreationTime,
		&pdmcd->fni.fni.EndOfFile);

	return XBDM_NOERR;
}

DMHRAPI HrGetFileAttr(LPCSTR szCommand, LPSTR szResponse,
	DWORD cchResponse, PDM_CMDCONT pdmcc)
{
	char sz[MAX_PATH];
	char osz[MAX_PATH];
	ANSI_STRING as;
	NTSTATUS st;
	OBJECT_ATTRIBUTES oa;

	if(!pdmcc)
		return E_FAIL;

	if(!FGetSzParam(szCommand, "name", sz, sizeof(sz)))
	{
		strcpy_s(szResponse, cchResponse, "missing name");
		return E_FAIL;
	}

	if(FAILED(FFileNameToObName(sz, osz, sizeof(osz))))
		return XBDM_NOSUCHFILE;

	RtlInitAnsiString(&as, osz);
	oa.Attributes = OBJ_CASE_INSENSITIVE;
	oa.RootDirectory = NULL;
	oa.ObjectName = &as;

	pdmcc->HandlingFunction = HrReportFileAttributes;
	pdmcc->BytesRemaining = 1;
	pdmcd->cch = 0;
	
	st = NtQueryFullAttributesFile(&oa, &pdmcd->fni.fni);
	return NT_SUCCESS(st) ? XBDM_MULTIRESPONSE : XBDM_NOSUCHFILE;
}

DMHRAPI HrSetFileAttr(LPCSTR szCommand, LPSTR szResponse,
	DWORD cchResponse, PDM_CMDCONT pdmcc)
{
	NTSTATUS st;
	HANDLE h;
	IO_STATUS_BLOCK iosb;
	char sz[MAX_PATH];
	FILE_NETWORK_OPEN_INFORMATION fna;
	FILE_BASIC_INFORMATION fba;
	DWORD dwAttrMask = 0;
	DWORD dwAttrNew = 0;
	DWORD dwT = 0;

	if(!pdmcc)
		return E_FAIL;
	
	if(!FGetSzParam(szCommand, "name", sz, sizeof(sz)))
	{
		strcpy_s(szResponse, cchResponse, "missing name");
		return E_FAIL;
	}

	st = FCreateFile(&h, SYNCHRONIZE, sz, NULL, 0,
		FILE_SHARE_READ | FILE_SHARE_WRITE, FILE_OPEN,
		FILE_SYNCHRONOUS_IO_NONALERT);
	
	if(FAILED(st))
		return XBDM_CANNOTACCESS;

	st = NtQueryInformationFile(h, &iosb, &fna, sizeof(fna), FileNetworkOpenInformation);

	if(FAILED(st))
	{
		NtClose(h);
		return XBDM_CANNOTACCESS;
	}

	ZeroMemory(&fba, sizeof(fba));
	if(FGetDwParam(szCommand, "readonly", &dwT))
	{
		dwAttrMask |= FILE_ATTRIBUTE_READONLY;
		if(dwT)
			dwAttrNew |= FILE_ATTRIBUTE_READONLY;
	}
	if(FGetDwParam(szCommand, "hidden", &dwT))
	{
		dwAttrMask |= FILE_ATTRIBUTE_HIDDEN;
		if(dwT)
			dwAttrNew |= FILE_ATTRIBUTE_HIDDEN;
	}

	FGetDwParam(szCommand, "createhi", (DWORD*)&fba.CreationTime.HighPart);
	FGetDwParam(szCommand, "createlo", (DWORD*)&fba.ChangeTime.LowPart);
	FGetDwParam(szCommand, "changehi", (DWORD*)&fba.LastWriteTime.HighPart);
	FGetDwParam(szCommand, "changelo", (DWORD*)&fba.LastWriteTime.LowPart);

	fba.FileAttributes = fna.FileAttributes ^ ((fna.FileAttributes ^ dwAttrNew) & dwAttrMask);

	if(!fba.FileAttributes)
		fba.FileAttributes = FILE_ATTRIBUTE_NORMAL;

	st = NtSetInformationFile(h, &iosb, &fba, sizeof(fba), FileBasicInformation);

	NtClose(h);

	return NT_SUCCESS(st) ? XBDM_NOERR : XBDM_CANNOTACCESS;
}

DMHRAPI HrReportMemoryEx(PDM_CMDCONT pdmcc, LPSTR szResponse, DWORD cchResponse)
{
	DWORD chars, addr, read = 0;
	BYTE mem;

	if(!pdmcd->cch)
	{
		pdmcc->BytesRemaining = 0;
		DmFreePool(pdmcc->Buffer);

		return XBDM_ENDOFLIST;
	}

	chars = pdmcd->cch;
	if(chars > 0x400)
	{
		chars = 0x400;
		((PBYTE)pdmcc->Buffer)[1] = 0x00;
	}
	else
		((PBYTE)pdmcc->Buffer)[1] = 0x80;

	((PBYTE)pdmcc->Buffer)[0] = 0;

	for(addr = pdmcd->mem.Address;addr < pdmcd->mem.Address + chars;addr++)
	{
		if(FGetMemory(addr, &mem))
		{
			((PBYTE)pdmcc->Buffer)[addr - pdmcd->mem.Address + 2] = mem;
			read++;
		}
		else
		{
			pdmcd->cch = 0;
			((PBYTE)pdmcc->Buffer)[1] = 0x80;
			break;
		}
	}

	*(PWORD)pdmcc->Buffer |= _byteswap_ushort((WORD)read);
	
	if(pdmcd->cch)
		pdmcd->cch -= read;

	pdmcd->mem.Address += read;
	
	pdmcc->BytesRemaining = 1;
	pdmcc->DataSize = read + 2;

	return XBDM_NOERR;
}

DMHRAPI HrGetMemoryEx(LPCSTR szCommand, LPSTR szResponse,
	DWORD cchResponse, PDM_CMDCONT pdmcc)
{
	DWORD dwAddr, dwLength;

	if(!pdmcc)
		return E_FAIL;

	if(!FGetNamedDwParam(szCommand, "addr", &dwAddr, szResponse)
		|| !FGetNamedDwParam(szCommand, "length", &dwLength, szResponse))
		return E_FAIL;

	pdmcc->BufferSize = 0x402;
	if(!(pdmcc->Buffer = DmAllocatePoolWithTag(pdmcc->BufferSize, 'xbdm')))
		return E_OUTOFMEMORY;

	pdmcc->BytesRemaining = 1;
	pdmcc->HandlingFunction = HrReportMemoryEx;
	pdmcd->cch = dwLength;
	pdmcd->mem.Address = dwAddr;

	return XBDM_BINRESPONSE;
}

DMHRAPI HrReportMemory(PDM_CMDCONT pdmcc, LPSTR szResponse, DWORD cchResponse)
{
	DWORD chars;
	DWORD addr;
	BYTE b;

	if(!pdmcd->cch)
		return XBDM_ENDOFLIST;

	chars = pdmcd->cch;
	if(chars > 64)
		chars = 64;

	for(addr = pdmcd->mem.Address;addr < pdmcd->mem.Address + chars;addr++)
	{
		if(FGetMemory(addr, &b))
		{
			((PBYTE)pdmcc->Buffer)[(addr - pdmcd->mem.Address) * 2] = rgchHex[(b >> 4) & 0xf];
			((PBYTE)pdmcc->Buffer)[(addr - pdmcd->mem.Address) * 2 + 1] = rgchHex[b & 0xf];
		}
		else
			((PBYTE)pdmcc->Buffer)[(addr - pdmcd->mem.Address) * 2] = ((PBYTE)pdmcc->Buffer)[(addr - pdmcd->mem.Address) * 2 + 1] = '?';
	}

	((PBYTE)pdmcc->Buffer)[(addr - pdmcd->mem.Address) * 2] = 0;

	pdmcd->cch -= chars;
	pdmcd->mem.Address += chars;

	return XBDM_NOERR;
}

DMHRAPI HrGetMemory(LPCSTR szCommand, LPSTR szResponse,
	DWORD cchResponse, PDM_CMDCONT pdmcc)
{
	DWORD dwAddr, dwLength;

	if(!pdmcc)
		return E_FAIL;

	if(!FGetNamedDwParam(szCommand, "addr", &dwAddr, szResponse)
		|| !FGetNamedDwParam(szCommand, "length", &dwLength, szResponse))
		return E_FAIL;

	strcpy_s(szResponse, cchResponse, "memory data follows");

	pdmcc->BytesRemaining = 1;
	pdmcc->HandlingFunction = HrReportMemory;
	pdmcd->cch = dwLength;
	pdmcd->mem.Address = dwAddr;

	return XBDM_MULTIRESPONSE;
}

DMHRAPI HrSetMemory(LPCSTR szCommand, LPSTR szResponse,
	DWORD cchResponse, PDM_CMDCONT pdmcc)
{
	int i;
	DWORD addr;
	LPCSTR data;
	char rgch[5];
	DWORD page;
	BOOL pageValid;
	BYTE b;
	int count = 0;

	if(!pdmcc)
		return E_FAIL;

	if(!FGetNamedDwParam(szCommand, "addr", &addr, szResponse))
		return E_FAIL;

	data = PchGetParam(szCommand, "data", FALSE);
	page = addr + 0x1000;
	
	rgch[0] = '0';
	rgch[1] = 'x';
	rgch[4] = 0;

	if(data)
	{
		for(;;count++, addr++)
		{
			if(FIsSpace(*data))
				break;
			for(i = 0;i < 2;i++)
			{
				if(!(*data >= '0' && *data <= '9' ||
					*data >= 'a' && *data <= 'f' ||
					*data >= 'A' && *data <= 'F'))
				{
						strcpy(szResponse, "syntax error in data");
						return E_FAIL;
				}
				rgch[i + 2] = *data++;
			}
			b = (BYTE)DwFromSz(rgch, NULL);
			if((addr ^ page) & 0xFFFFF000)
			{
				page = addr & 0xFFFFF000;
				pageValid = MmIsAddressValid((LPVOID)addr);
			}
			if(pageValid)
				DmSetMemory((PVOID)addr, 1, &b, NULL);
			else
			{
				RtlSnprintf(szResponse, cchResponse, "set %d bytes", count);
				return XBDM_MEMUNMAPPED;
			}
		}
	}

	RtlSnprintf(szResponse, cchResponse, "set %d bytes", count);
	return XBDM_NOERR;
}

DMHRAPI HrReportModules(PDM_CMDCONT pdmcc, LPSTR szResponse, DWORD cchResponse)
{
	DMN_MODLOAD_EX dmnex;

	if(pdmcc->BytesRemaining == 2)
		return XBDM_ENDOFLIST;

	if(FAILED(DmWalkLoadedModulesEx((PDM_WALK_MODULES*)&pdmcd->rgb, &dmnex)))
	{
		DmCloseLoadedModules((PDM_WALK_MODULES)pdmcd->rgb);
		pdmcc->BytesRemaining++;
	}
	
	RtlSnprintf((LPSTR)pdmcc->Buffer, pdmcc->BufferSize,
		"name=\"%s\" base=0x%08x size=0x%08x check=0x%08x timestamp=0x%08x pdata=0x%08x psize=0x%08x %sthread=0x%08x osize=0x%08x",
		dmnex.Name, dmnex.BaseAddress, dmnex.Size, dmnex.CheckSum, dmnex.TimeStamp, dmnex.PDataAddress, dmnex.PDataSize,
		dmnex.Flags & DMN_MODFLAG_TLS ? "" : "dll", dmnex.ThreadId, dmnex.OriginalSize);

	return XBDM_NOERR;
}

DMHRAPI HrGetModules(LPCSTR szCommand, LPSTR szResponse,
	DWORD cchResponse, PDM_CMDCONT pdmcc)
{
	if(!pdmcc)
		return E_FAIL;

	pdmcd->rgb = NULL;
	pdmcc->HandlingFunction = HrReportModules;
	pdmcc->BytesRemaining = 1;

	return XBDM_MULTIRESPONSE;
}

DMHRAPI HrStop(LPCSTR szCommand, LPSTR szResponse,
	DWORD cchResponse, PDM_CMDCONT pdmcc)
{
	if(!pdmcc)
		return E_FAIL;

	return DwChangeExecState(DMN_EXEC_STOP, TRUE, TRUE, FALSE);
}

DMHRAPI HrGo(LPCSTR szCommand, LPSTR szResponse,
	DWORD cchResponse, PDM_CMDCONT pdmcc)
{
	if(!pdmcc)
		return E_FAIL;

	return DwChangeExecState(DMN_EXEC_START, TRUE, TRUE, FALSE);
}

DMHRAPI HrReportScreenshot(PDM_CMDCONT pdmcc, LPSTR szResponse, DWORD cchResponse)
{
	if(pdmcd->cch == 0)
	{
		RtlSnprintf((LPSTR)pdmcc->Buffer, pdmcc->BufferSize,
			"pitch=0x%08x width=0x%08x height=0x%08x format=0x%08x offsetx=0x%08x offsety=0x%08x, framebuffersize=0x%08x sw=0x%08x sh=0x%08x colorspace=0x%x\r\n",
			pdmcd->screen.p, pdmcd->screen.w, pdmcd->screen.h, pdmcd->screen.fmt, 0, 0, pdmcd->screen.size, pdmcd->screen.sw, pdmcd->screen.sh, 0);
		
		pdmcd->cch = 1;
		pdmcc->DataSize = strlen((char*)pdmcc->Buffer);
	}
	else if(pdmcd->cch == 1)
	{
		pdmcc->Buffer = (PVOID)pdmcd->screen.szFrame;
		pdmcc->DataSize = pdmcc->BytesRemaining;
		pdmcd->cch = 2;
	}
	else
	{
		if(NT_SUCCESS(pdmcd->hr))
			DwChangeExecState(DMN_EXEC_START, TRUE, FALSE, FALSE);

		return XBDM_ENDOFLIST;
	}

	return XBDM_NOERR;
}

DMHRAPI HrScreenshot(LPCSTR szCommand, LPSTR szResponse,
	DWORD cchResponse, PDM_CMDCONT pdmcc)
{
	DWORD dwStart, ptrOffset;
	char *frameBuffer;
	LPDWORD lpgpu = (LPDWORD)0x7FC81740;
	DISPLAY_INFORMATION display;
	DWORD w, h, p, size;
	DWORD vw, vh, vp, vs;

	if(!pdmcc)
		return E_FAIL;

	pdmcd->hr = DwChangeExecState(DMN_EXEC_STOP, TRUE, FALSE, FALSE);

	dwStart = *KeTimeStampBundle;
	while((*lpgpu & 0x80000000) && (*KeTimeStampBundle - dwStart < 5000))
		Sleep(100);

	if(*lpgpu & 0x80000000)
	{
		if(NT_SUCCESS(pdmcd->hr))
			DwChangeExecState(DMN_EXEC_START, TRUE, FALSE, FALSE);
		strcpy_s(szResponse, cchResponse, "can't lock GPU");
		return E_FAIL;
	}

	ptrOffset = *((DWORD*)0x7FC86110);
	frameBuffer = (char*)(0xC0000000 + ptrOffset);
	if(!MmIsAddressValid(frameBuffer)) {
		frameBuffer = (char*)(0xA0000000 + ptrOffset);
		if(!MmIsAddressValid(frameBuffer)) {
			frameBuffer = (char*)(0xDFFFF000 + ptrOffset);
		}
	}

	VdGetCurrentDisplayInformation(&display);
	w = display.FrontBufferWidth;
	h = display.FrontBufferHeight;
	p = w * 4;
	size = h * p;

	vw = w;vh = h;
	if(vw % 128)
		vw += (128 - vw % 128);
	if(vh % 128)
		vh += (128 - vh % 128);
	vp = vw * 4;
	vs = vh * vp;

	pdmcc->HandlingFunction = HrReportScreenshot;
	pdmcc->BytesRemaining = vs;
	pdmcd->cch = 0;
	
	pdmcd->screen.fmt = (((*((UINT*)0x7FC86104) >> 24) & 7) == 0) ? D3DFMT_A8R8G8B8 : D3DFMT_A2R10G10B10;

	pdmcd->screen.w = w;
	pdmcd->screen.h = h;
	pdmcd->screen.sw = display.DisplayWidth;
	pdmcd->screen.sh = display.DisplayHeight;
	pdmcd->screen.p = p;
	pdmcd->screen.size = vs;
	pdmcd->screen.szFrame = frameBuffer;

	return XBDM_BINRESPONSE;
}

DMHRAPI HrReportWalkMemory(PDM_CMDCONT pdmcc, LPSTR szResponse, DWORD cchResponse)
{
	DWORD dwAddr, dwLength, dwProtect, dwPhys;

	dwAddr = pdmcd->cch;

	if(dwAddr == 0xFFFFFFFF)
		return XBDM_ENDOFLIST;

	while(!MmIsAddressValid((PVOID)dwAddr))
	{
		if(dwAddr == 0xFFFFF000)
			return XBDM_ENDOFLIST;
		dwAddr += 0x1000;
	}

	// dwAddr now contains a valid page start

	dwProtect = XQueryMemoryProtect((LPVOID)dwAddr);

	// Calc the length of the page
	dwLength = 0x1000;

	while(MmIsAddressValid((PVOID)(dwAddr + dwLength)) && (XQueryMemoryProtect((LPVOID)(dwAddr + dwLength)) == dwProtect))
	{
		if((dwAddr + dwLength) == 0)
			break;
		dwLength += 0x1000;
	}

	// Now dwLength contains the page length
	if((dwAddr + dwLength) == 0)
		pdmcd->cch = 0xFFFFFFFF;
	else
		pdmcd->cch = dwAddr + dwLength;

	dwPhys = MmGetPhysicalAddress((PVOID)dwAddr);

	RtlSnprintf((LPSTR)pdmcc->Buffer, pdmcc->BufferSize, "base=0x%0.8x size=0x%0.8x protect=0x%0.8x phys=0x%0.8x",
		dwAddr, dwLength, dwProtect, dwPhys);
	return XBDM_NOERR;
}

DMHRAPI HrWalkMemory(LPCSTR szCommand, LPSTR szResponse,
	DWORD cchResponse, PDM_CMDCONT pdmcc)
{
	if(!pdmcc)
		return E_FAIL;

	pdmcd->cch = 0;
	pdmcc->BytesRemaining = 1;
	pdmcc->HandlingFunction = HrReportWalkMemory;

	strcpy_s(szResponse, cchResponse, "Valid Virtual Address Ranges Follow");
	return XBDM_MULTIRESPONSE;
}

DMHRAPI HrSetColor(LPCSTR szCommand, LPSTR szResponse,
	DWORD cchResponse, PDM_CMDCONT pdmcc)
{
	char sz[0x10];

	sz[0] = 0;
	FGetSzParam(szCommand, "name", sz, sizeof(sz));

	g_dmGlobals.dwConsoleColor = 0;

	if(!stricmp(sz, "black"))
		g_dmGlobals.dwConsoleColor = CONSOLE_COLOR_FLAG_BLACK;
	else if(!stricmp(sz, "blue"))
		g_dmGlobals.dwConsoleColor = CONSOLE_COLOR_FLAG_BLACK | CONSOLE_COLOR_FLAG_BLUE;
	else if(!stricmp(sz, "bluegray"))
		g_dmGlobals.dwConsoleColor = CONSOLE_COLOR_FLAG_WHITE | CONSOLE_COLOR_FLAG_BLUE;
	else if(!stricmp(sz, "nosidecar"))
		g_dmGlobals.dwConsoleColor = CONSOLE_COLOR_FLAG_NOSIDECAR;
	else if(!stricmp(sz, "white"))
		g_dmGlobals.dwConsoleColor = CONSOLE_COLOR_FLAG_WHITE;

	g_dmGlobals.bDirty = TRUE;

	return XBDM_NOERR;
}

DMHRAPI HrSendFileData(PDM_CMDCONT pdmcc, LPSTR szResponse, DWORD cchResponse)
{
	NTSTATUS st;
	DWORD cb;

	if(pdmcc->BytesRemaining == 1)
	{
		// Send the length
		*(LPDWORD)pdmcc->Buffer = _byteswap_ulong(pdmcd->cch);
		pdmcc->DataSize = 4;
		pdmcc->BytesRemaining = 2;
	}
	else if(pdmcc->BytesRemaining == 2)
	{
		// Send the file data
		cb = pdmcc->BufferSize;
		if(cb > pdmcd->cch)
			cb = pdmcd->cch;
		st = FReadFile(pdmcd->h, pdmcc->Buffer, cb);
		if(FAILED(st))
			ZeroMemory(pdmcc->Buffer, cb);
		pdmcd->cch -= cb;
		pdmcc->DataSize = cb;

		if(pdmcd->cch == 0)
			pdmcc->BytesRemaining = 3;
	}
	else
	{
		// Close and exit
		NtClose(pdmcd->h);
		DmFreePool(pdmcc->Buffer);

		return XBDM_ENDOFLIST;
	}

	return XBDM_NOERR;
}

DMHRAPI HrGetFile(LPCSTR szCommand, LPSTR szResponse,
	DWORD cchResponse, PDM_CMDCONT pdmcc)
{
	NTSTATUS st;
	IO_STATUS_BLOCK iosb;
	char sz[MAX_PATH];
	FILE_NETWORK_OPEN_INFORMATION fni;

	if(!pdmcc)
		return E_FAIL;

	if(!FGetSzParam(szCommand, "name", sz, sizeof(sz)))
	{
		strcpy_s(szResponse, cchResponse, "missing name");
		return E_FAIL;
	}
	
	st = FCreateFile(&pdmcd->h, GENERIC_READ | SYNCHRONIZE, sz,
		NULL, 0, 0, FILE_OPEN, FILE_SYNCHRONOUS_IO_NONALERT);

	if(FAILED(st))
		return XBDM_CANNOTACCESS;

	st = NtQueryInformationFile(pdmcd->h, &iosb, &fni, sizeof(fni), FileNetworkOpenInformation);

	if(FAILED(st))
	{
		NtClose(pdmcd->h);
		return E_UNEXPECTED;
	}

	if(fni.EndOfFile.HighPart)
	{
		NtClose(pdmcd->h);

		strcpy_s(szResponse, cchResponse, "file is too big");
		return E_FAIL;
	}

	pdmcc->BufferSize = 0x3000;
	pdmcc->Buffer = DmAllocatePoolWithTag(pdmcc->BufferSize, 'bdbd');

	if(pdmcc->Buffer == NULL)
	{
		NtClose(pdmcd->h);
		return E_OUTOFMEMORY;
	}

	pdmcd->cch = fni.EndOfFile.LowPart;
	pdmcc->BytesRemaining = 1;
	pdmcc->HandlingFunction = HrSendFileData;

	return XBDM_BINRESPONSE;
}

DMHRAPI HrRecieveFileData(PDM_CMDCONT pdmcc, LPSTR szResponse, DWORD cchResponse)
{
	FILE_DISPOSITION_INFORMATION fdi;
	IO_STATUS_BLOCK iosb;
	NTSTATUS st;

	if(pdmcc->DataSize)
	{
		pdmcd->ib += pdmcc->DataSize;
		pdmcc->BytesRemaining -= pdmcc->DataSize;
	}
	else if(pdmcc->BytesRemaining)
	{
		pdmcc->BytesRemaining = 0;
		fdi.DeleteFile = TRUE;
		NtSetInformationFile(pdmcd->h, &iosb, &fdi, sizeof(fdi), FileDispositionInformation);
		pdmcd->fError = TRUE;
	}

	if(!pdmcc->BytesRemaining || pdmcd->ib == pdmcd->cchBuf)
	{
		if(pdmcd->h != INVALID_HANDLE_VALUE)
		{
			st = NtWriteFile(pdmcd->h, NULL, NULL, NULL, &iosb,
				pdmcd->rgb, pdmcd->ib, NULL);

			if(FAILED(st))
			{
				fdi.DeleteFile = TRUE;
				NtSetInformationFile(pdmcd->h, &iosb, &fdi, sizeof(fdi), FileDispositionInformation);
				NtClose(pdmcd->h);
				pdmcd->fError = TRUE;
				pdmcd->h = INVALID_HANDLE_VALUE;
			}
			else if(!pdmcc->BytesRemaining)
			{
				NtClose(pdmcd->h);
				pdmcd->h = INVALID_HANDLE_VALUE;
			}
		}

		pdmcc->Buffer = (char*)pdmcc->Buffer - pdmcd->ib;
		pdmcd->ib = 0;

		if(!pdmcc->BytesRemaining && pdmcc->Buffer)
			DmFreePool(pdmcd->rgb);
	}

	if(pdmcd->rgb)
	{
		pdmcc->Buffer = pdmcd->rgb + pdmcd->ib;
		pdmcc->BufferSize = pdmcd->cchBuf - pdmcd->ib;
	}

	if(pdmcd->fError)
	{
		DmFreePool(pdmcd->rgb);
		NtClose(pdmcd->h);
		pdmcd->h = INVALID_HANDLE_VALUE;
	}

	return pdmcd->fError ? E_UNEXPECTED : XBDM_NOERR;
}

DMHRAPI HrSendFile(LPCSTR szCommand, LPSTR szResponse,
	DWORD cchResponse, PDM_CMDCONT pdmcc)
{
	NTSTATUS st;
	char sz[MAX_PATH];
	IO_STATUS_BLOCK iosb;
	FILE_DISPOSITION_INFORMATION fdi;
	LARGE_INTEGER liSize;

	if(!pdmcc)
		return E_FAIL;

	if(!FGetSzParam(szCommand, "name", sz, sizeof(sz)))
	{
		strcpy_s(szResponse, cchResponse, "missing name");
		return E_FAIL;
	}

	if(!FGetNamedDwParam(szCommand, "length", &pdmcd->cch, szResponse))
		return E_FAIL;

	liSize.HighPart = 0;
	liSize.LowPart = pdmcd->cch;

	st = FCreateFile(&pdmcd->h, GENERIC_WRITE | DELETE | SYNCHRONIZE,
		sz, &liSize, 0, 0, FILE_OVERWRITE_IF,
		FILE_SYNCHRONOUS_IO_NONALERT);

	if(FAILED(st))
		return XBDM_CANNOTCREATE;

	st = NtSetInformationFile(pdmcd->h, &iosb, &liSize, sizeof(liSize), FileEndOfFileInformation);

	if(FAILED(st))
	{
		fdi.DeleteFile = TRUE;
		NtSetInformationFile(pdmcd->h, &iosb, &fdi, sizeof(fdi), FileDispositionInformation);
		NtClose(pdmcd->h);

		return XBDM_DEVICEFULL;
	}

	pdmcc->BufferSize = 0x4000;
	pdmcc->Buffer = DmAllocatePoolWithTag(pdmcc->BufferSize, 'bdbd');

	if(pdmcc->Buffer == NULL)
	{
		fdi.DeleteFile = TRUE;
		NtSetInformationFile(pdmcd->h, &iosb, &fdi, sizeof(fdi), FileDispositionInformation);
		NtClose(pdmcd->h);
		
		return E_OUTOFMEMORY;
	}

	pdmcd->cchBuf = pdmcc->BufferSize;
	pdmcd->cch = 0;
	pdmcc->HandlingFunction = HrRecieveFileData;
	pdmcd->ib = 0;
	pdmcd->rgb = (LPSTR)pdmcc->Buffer;
	pdmcd->fError = FALSE;

	pdmcc->BytesRemaining = liSize.LowPart;

	return XBDM_READYFORBIN;
}

DMHRAPI HrRecieveVolumeFileData(PDM_CMDCONT pdmcc, LPSTR szResponse, DWORD cchResponse)
{
	// We act under the assumption that if the buffer is big enough, we get exactly however
	// many bytes we asked for in BytesRemaining, otherwise we just get a full buffer

	FILE_DISPOSITION_INFORMATION fdi;
	IO_STATUS_BLOCK iosb;

#define st ((DWORD*)(pdmcd->rgb + 0x4000))[pdmcd->vfile.remain]

	if(pdmcd->vfile.step != 3 && !pdmcc->DataSize)
	{
		// We lost the connection...
		if(pdmcd->h != INVALID_HANDLE_VALUE)
		{
			fdi.DeleteFile = TRUE;
			NtSetInformationFile(pdmcd->h, &iosb, &fdi, sizeof(fdi), FileDispositionInformation);

			NtClose(pdmcd->h);
			pdmcd->h = INVALID_HANDLE_VALUE;
		}

		DmFreePool(pdmcd->rgb);
		pdmcc->BytesRemaining = 0;

		return XBDM_ENDOFLIST;
	}
	else if(pdmcd->vfile.step == 0)
	{
		// Recieved file info block
#pragma pack(1)
		typedef struct
		{
			DWORD dwSize;
			ULONGLONG CreateTime;
			ULONGLONG ChangeTime;
			ULONGLONG FileSize;
			DWORD FileAttributes;
		} *__info;

		__info fInfo = (__info)pdmcc->Buffer;

		pdmcd->vfile.ChangeTime.QuadPart = fInfo->ChangeTime;
		pdmcd->vfile.CreationTime.QuadPart = fInfo->CreateTime;
		pdmcd->vfile.FileAttributes = fInfo->FileAttributes;
		pdmcd->vfile.FileSize = (DWORD)fInfo->FileSize;
		
		if(fInfo->FileSize > 0xFFFFFFFF)
			 st = E_FAIL; // File too big
		else
			st = STATUS_SUCCESS;

		pdmcc->BytesRemaining = fInfo->dwSize - 0x20;
		pdmcd->ib = 0;

		pdmcd->vfile.step++;
	}
	else if(pdmcd->vfile.step == 1)
	{
		// Recieved file name
		LARGE_INTEGER li;

		if(NT_SUCCESS(st))
		{
			li.HighPart = 0;
			li.LowPart = pdmcd->vfile.FileSize;

			st = FCreateFile(&pdmcd->h, GENERIC_WRITE | DELETE | SYNCHRONIZE,
				(char*)pdmcc->Buffer, &li, 0, 0, FILE_OVERWRITE_IF,
				FILE_SYNCHRONOUS_IO_NONALERT);
		}

		pdmcc->BytesRemaining = pdmcd->vfile.FileSize;
		pdmcd->vfile.step++;
	}
	else if(pdmcd->vfile.step == 2)
	{
		// Recieved file data
		pdmcd->ib += pdmcc->DataSize;
		pdmcc->BytesRemaining -= pdmcc->DataSize;

		if((pdmcc->BytesRemaining == 0) || (pdmcd->ib == 0x4000))
		{
			// Write to file
			if((pdmcd->h != INVALID_HANDLE_VALUE) && NT_SUCCESS(st))
			{
				st = NtWriteFile(pdmcd->h, NULL, NULL, NULL, &iosb, pdmcd->rgb, pdmcd->ib, NULL);
				if(FAILED(st))
				{
					fdi.DeleteFile = TRUE;
					NtSetInformationFile(pdmcd->h, &iosb, &fdi, sizeof(fdi), FileDispositionInformation);
					NtClose(pdmcd->h);
					pdmcd->h = INVALID_HANDLE_VALUE;
				}

				// Reset back to the start
				pdmcd->ib = 0;
			}
		}

		if(pdmcc->BytesRemaining == 0)
		{
			pdmcd->vfile.remain++;
			
			if(pdmcd->h != INVALID_HANDLE_VALUE)
			{
				NtClose(pdmcd->h);
				pdmcd->h = INVALID_HANDLE_VALUE;
			}

			if(pdmcd->vfile.remain == pdmcd->cch)
			{
				pdmcd->vfile.step++;
				return XBDM_BINRESPONSE;
			}
			else
			{
				pdmcd->vfile.step = 0;
				pdmcc->BytesRemaining = 0x20;

				pdmcd->ib = 0;
			}
		}
	}
	else if(pdmcd->vfile.step == 3)
	{
		// Send back status codes
		pdmcc->Buffer = pdmcd->rgb + 0x4000;
		pdmcc->BytesRemaining = 1;
		pdmcc->DataSize = pdmcd->cchBuf - 0x4000;

		pdmcd->vfile.step++;
	}
	else if(pdmcd->vfile.step == 4)
	{
		DmFreePool(pdmcd->rgb);

		return XBDM_ENDOFLIST; // Signal completion
	}

	// Fix up the values
	if(pdmcd->vfile.step != 4)
	{
		pdmcc->Buffer = pdmcd->rgb + pdmcd->ib;
		pdmcc->BufferSize = 0x4000 - pdmcd->ib;
	}

#undef st

	return XBDM_NOERR;
}

DMHRAPI HrSendVolumeFile(LPCSTR szCommand, LPSTR szResponse,
	DWORD cchResponse, PDM_CMDCONT pdmcc)
{
	if(!pdmcc)
		return E_FAIL;

	if(!FGetNamedDwParam(szCommand, "count", &pdmcd->cch, szResponse))
		return E_FAIL;

	pdmcc->BufferSize = 0x4000 + pdmcd->cch * 4;
	pdmcc->Buffer = DmAllocatePoolWithTag(pdmcc->BufferSize, 'bdbd');

	if(!pdmcc->Buffer)
		return E_OUTOFMEMORY;

	ZeroMemory(pdmcc->Buffer, pdmcc->BufferSize);

	pdmcd->rgb = (char*)pdmcc->Buffer;

	pdmcc->HandlingFunction = HrRecieveVolumeFileData;
	pdmcc->BytesRemaining = 0x20;

	pdmcd->cchBuf = pdmcc->BufferSize;
	pdmcd->vfile.remain = 0;
	pdmcd->vfile.step = 0;
	pdmcd->h = INVALID_HANDLE_VALUE;

	return XBDM_READYFORBIN;
}

DMHRAPI HrHwInfo(LPCSTR szCommand, LPSTR szResponse,
	DWORD cchResponse, PDM_CMDCONT pdmcc)
{
	if(!pdmcc)
		return E_FAIL;

	RtlSnprintf(szResponse, cchResponse, 
		"Hardware Info Follows\r\n"
		"Flags              : 0x%08x\r\n"
		"NumberOfProcessors : 0x%02x\r\n"
		"PCIBridgeRevisionID: 0x%02x\r\n"
		"Reserved Bytes     : 0x %02x %02x %02x %02x %02x %02x\r\n"
		"BldrMagic          : 0x%04x\r\n"
		"BldrFlags          : 0x%04x\r\n"
		".",
		XboxHardwareInfo->Flags, XboxHardwareInfo->NumberOfProcessors,
		XboxHardwareInfo->PCIBridgeRevisionID,
		XboxHardwareInfo->Reserved[0], XboxHardwareInfo->Reserved[1],
		XboxHardwareInfo->Reserved[2], XboxHardwareInfo->Reserved[3],
		XboxHardwareInfo->Reserved[4], XboxHardwareInfo->Reserved[5],
		XboxHardwareInfo->BldrMagic, XboxHardwareInfo->BldrFlags);

	return XBDM_NOERR;
}

DMHRAPI HrObjList(LPCSTR szCommand, LPSTR szResponse,
	DWORD cchResponse, PDM_CMDCONT pdmcc)
{
	PDMCONN pdmc;

	if(!pdmcc)
		return E_FAIL;

	pdmc = CONTAINING_RECORD(pdmcc, DMCONN, dmcc);

	//DumpAllObjects("\\", pdmc->s);

	return XBDM_NOERR;
}

DMHRAPI HrSetDumpMode(LPCSTR szCommand, LPSTR szResponse,
	DWORD cchResponse, PDM_CMDCONT pdmcc)
{
	int i;

	for(i = 0;i <= DM_DUMPMODE_DISABLED;i++)
	{
		if(PchGetParam(szCommand, rgszDumpMode[i], FALSE))
			break;
	}

	if(i > DM_DUMPMODE_DISABLED)
		return XBDM_NOERR;

	DmSetDumpMode(i);

	strcpy_s(szResponse, cchResponse, rgszDumpMode[i]);
	return XBDM_NOERR;
}

DMHRAPI HrNotify(LPCSTR szCommand, LPSTR szResponse,
	DWORD cchResponse, PDM_CMDCONT pdmcc)
{
	DWORD dwPort;
	PDMCONN conn;

	if(!FGetNamedDwParam(szCommand, "reconnectport", &dwPort, szResponse))
		return E_FAIL;

	conn = CONTAINING_RECORD(pdmcc, DMCONN, dmcc);

	FConvertToNotifySock(conn, dwPort);

	return XBDM_NOERR;
}

DMHRAPI HrNotifyAt(LPCSTR szCommand, LPSTR szResponse,
	DWORD cchResponse, PDM_CMDCONT pdmcc)
{
	DWORD dw;

	if(!FGetNamedDwParam(szCommand, "port", &dw, szResponse))
		return E_FAIL;
	if(!PchGetParam(szCommand, "drop", FALSE))
		return E_FAIL;

	return FDropNotifySock(dw);
}

DMHRAPI HrAttachDebugger(LPCSTR szCommand, LPSTR szResponse,
	DWORD cchResponse, PDM_CMDCONT pdmcc)
{
	DWORD dwPort;
	BOOL fOverride;

	fOverride = (BOOL)PchGetParam(szCommand, "override", FALSE);

	if(PchGetParam(szCommand, "connect", FALSE))
	{
		if(g_dmGlobals.bDebugging && !fOverride)
			return XBDM_ALREADYEXISTS;

		g_dmGlobals.dwDebugPort = 0;
		ZeroMemory(g_dmGlobals.rgchDebuggerName, sizeof(g_dmGlobals.rgchDebuggerName));
		ZeroMemory(g_dmGlobals.rgchDebuggerUser, sizeof(g_dmGlobals.rgchDebuggerUser));

		FGetDwParam(szCommand, "port", &g_dmGlobals.dwDebugPort);
		FGetSzParam(szCommand, "name", g_dmGlobals.rgchDebuggerName, sizeof(g_dmGlobals.rgchDebuggerName));
		FGetSzParam(szCommand, "user", g_dmGlobals.rgchDebuggerUser, sizeof(g_dmGlobals.rgchDebuggerUser));

		g_dmGlobals.bDebugging = TRUE;
	}
	else if(PchGetParam(szCommand, "disconnect", FALSE))
	{
		if((g_dmGlobals.dwDebugPort == 0)
			|| (FGetDwParam(szCommand, "port", &dwPort) && dwPort == g_dmGlobals.dwDebugPort)
			|| fOverride)
		{
			ZeroMemory(g_dmGlobals.rgchDebuggerName, sizeof(g_dmGlobals.rgchDebuggerName));
			ZeroMemory(g_dmGlobals.rgchDebuggerUser, sizeof(g_dmGlobals.rgchDebuggerUser));
			g_dmGlobals.bDebugging = FALSE;
		}
		else
			return XBDM_CANNOTACCESS;
	}
	else
	{
		strcpy_s(szResponse, cchResponse, "no command");
		return E_FAIL;
	}

	return XBDM_NOERR;
}

DMHRAPI HrIsDebuggerAttached(LPCSTR szCommand, LPSTR szResponse,
	DWORD cchResponse, PDM_CMDCONT pdmcc)
{
	const char *sz1, *sz2, *sz3, *sz4, *sz5, *sz6;

	if(!pdmcc)
		return E_FAIL;

	if(!g_dmGlobals.bDebugging)
		return XBDM_NOERR;

	if(g_dmGlobals.rgchDebuggerUser[0])
	{
		sz1 = "user=\"";
		sz2 = g_dmGlobals.rgchDebuggerUser;
		sz3 = "\"";
	}
	else
	{
		sz1 = "";
		sz2 = "";
		sz3 = "";
	}

	if(g_dmGlobals.rgchDebuggerName[0])
	{
		sz4 = "name=\"";
		sz5 = g_dmGlobals.rgchDebuggerName;
		sz6 = "\"";
	}
	else
	{
		sz4 = "";
		sz5 = "";
		sz6 = "";
	}

	RtlSnprintf(szResponse, cchResponse, "%s%s%s%s%s%s%s",
		sz1, sz2, sz3,
		(sz1[0] && sz4[0]) ? " " : "",
		sz4, sz5, sz6);

	return XBDM_ALREADYEXISTS;
}

DMHRAPI HrReportSystemInfo(PDM_CMDCONT pdmcc, LPSTR szResponse, DWORD cchResponse)
{
	char *sz;

	switch(pdmcc->BytesRemaining)
	{
	case 1:
		strcpy_s((char*)pdmcc->Buffer, pdmcc->BufferSize, "HDD=");
		if(XboxHardwareInfo->Flags & 0x20)
			strcat_s((char*)pdmcc->Buffer, pdmcc->BufferSize, "Enabled");
		else
			strcat_s((char*)pdmcc->Buffer, pdmcc->BufferSize, "Disabled");
		break;
	case 2:
		strcpy_s((char*)pdmcc->Buffer, pdmcc->BufferSize, "Type=");
		if(XboxHardwareInfo->Flags & 0x02000000)
			sz = "TestKit";
		else
			sz = "DevKit";
		strcat_s((char*)pdmcc->Buffer, pdmcc->BufferSize, sz);
		break;
	case 3:
		strcpy_s((char*)pdmcc->Buffer, pdmcc->BufferSize, "Platform=");
		switch(XboxHardwareInfo->Flags & 3)
		{
		case 0:
			sz = "Alpha";
			break;
		case 1:
			sz = "Mongrel";
			break;
		case 2:
			sz = "Shiva";
			break;
		case 3:
			sz = "Waternoose";
			break;
		default:
			sz = "Unknown";
			break;
		}
		strcat_s((char*)pdmcc->Buffer, pdmcc->BufferSize, sz);
		strcat_s((char*)pdmcc->Buffer, pdmcc->BufferSize, " System=");
		switch((XboxHardwareInfo->Flags >> 28) & 0xF)
		{
		case 0:
			sz = "Xenon";
			break;
		case 1:
			sz = "Zephyr";
			break;
		case 2:
			sz = "Falcon";
			break;
		case 3:
			sz = "Jasper";
			break;
		case 4:
			sz = "Trinity";
			break;
		case 5:
			sz = "Corona";
			break;
		case 6:
			sz = "Winchester";
			break;
		default:
			sz = "Unknown";
			break;
		}
		strcat_s((char*)pdmcc->Buffer, pdmcc->BufferSize, sz);
		break;
	case 4:
		RtlSnprintf((char*)pdmcc->Buffer, pdmcc->BufferSize, "BaseKrnl=%d.%d.%d.%d Krnl=%d.%d.%d.%d XDK=2.0.20353.0",
			XboxKrnlBaseVersion->Major, XboxKrnlBaseVersion->Minor, XboxKrnlBaseVersion->Build,
			(XboxKrnlBaseVersion->ApprovalType << 8) + XboxKrnlBaseVersion->QFE,
			XboxKrnlVersion->Major, XboxKrnlVersion->Minor, XboxKrnlVersion->Build,
			(XboxKrnlVersion->ApprovalType << 8) + XboxKrnlVersion->QFE);
		break;
	case 5:
		return XBDM_ENDOFLIST;
	}

	pdmcc->BytesRemaining++;

	return XBDM_NOERR;
}

DMHRAPI HrGetSystemInfo(LPCSTR szCommand, LPSTR szResponse,
	DWORD cchResponse, PDM_CMDCONT pdmcc)
{
	if(!pdmcc)
		return E_FAIL;

	pdmcc->HandlingFunction = HrReportSystemInfo;
	pdmcc->BytesRemaining = 1;

	return XBDM_MULTIRESPONSE;
}

VOID PcregNext(DMCR* Context)
{
	for(;;)
	{
		if(Context->CurrentRegister == cchregs)
		{
			Context->CurrentRegister = 0;
			Context->Register = NULL;
			return;
		}

		Context->Register = &rgbregs[Context->CurrentRegister];
		Context->CurrentRegister++;

		if(Context->Context.ContextFlags & Context->Register->Context)
			break;
	}
}

DMHRAPI HrReportContext(PDM_CMDCONT pdmcc, LPSTR szResponse, DWORD cchResponse)
{
	int i;
	DMCR *context = ((DMCR*)pdmcc->CustomData);

	if(!context->Register)
	{
		DmFreePool(pdmcc->CustomData);
		return XBDM_ENDOFLIST;
	}

	pdmcc->DataSize = 0;
	for(i = 0;i < 4;i++)
	{
		if(context->Register->Size == 4)
		{
			pdmcc->DataSize += RtlSprintf((char*)pdmcc->Buffer + pdmcc->DataSize, "%s=0x%08x\r\n",
				context->Register->Name, *(LPDWORD)((char*)&context->Context + context->Register->Offset));
		}
		else if(context->Register->Size == 8)
		{
			pdmcc->DataSize += RtlSprintf((char*)pdmcc->Buffer + pdmcc->DataSize, "%s=0q%016I64x\r\n",
				context->Register->Name, *(QWORD*)((char*)&context->Context + context->Register->Offset));
		}
		else if(context->Register->Size == 16)
		{
			pdmcc->DataSize += RtlSprintf((char*)pdmcc->Buffer + pdmcc->DataSize, "%s=0x%08x,0x%08x,0x%08x,0x%08x\r\n",
				context->Register->Name,
				(LPDWORD)((char*)&context->Context + context->Register->Offset)[0],
				(LPDWORD)((char*)&context->Context + context->Register->Offset)[1],
				(LPDWORD)((char*)&context->Context + context->Register->Offset)[2],
				(LPDWORD)((char*)&context->Context + context->Register->Offset)[3]);
		}

		PcregNext(context);

		if(!context->Register)
			break;
	}

	return XBDM_NOERR;
}

DMHRAPI HrGetContext(LPCSTR szCommand, LPSTR szResponse,
	DWORD cchResponse, PDM_CMDCONT pdmcc)
{
	XCONTEXT context;
	DWORD dwThreadId;
	HRESULT hr;

	if(!pdmcc)
		return E_FAIL;

	if(!FGetNamedDwParam(szCommand, "thread", &dwThreadId, szResponse))
		return E_FAIL;

	context.ContextFlags = 0;
	if(PchGetParam(szCommand, "control", FALSE))
		context.ContextFlags |= CONTEXT_CONTROL;
	if(PchGetParam(szCommand, "int", FALSE))
		context.ContextFlags |= CONTEXT_INTEGER;
	if(PchGetParam(szCommand, "fp", FALSE))
		context.ContextFlags |= CONTEXT_FLOATING_POINT;
	if(PchGetParam(szCommand, "vr", FALSE))
		context.ContextFlags |= CONTEXT_VECTOR;
	if(PchGetParam(szCommand, "full", FALSE))
		context.ContextFlags |= CONTEXT_FULL;

	hr = DmGetThreadContext(dwThreadId, &context);

	if(FAILED(hr))
		return hr;

	pdmcc->CustomData = DmAllocatePoolWithTag(sizeof(DMCR), 'dmcr');
	
	if(!pdmcc->CustomData)
		return E_OUTOFMEMORY;

	((DMCR*)pdmcc->CustomData)->CurrentRegister = 0;
	((DMCR*)pdmcc->CustomData)->Register = NULL;
	memcpy(pdmcc->CustomData, &context, sizeof(XCONTEXT));

	PcregNext(((DMCR*)pdmcc->CustomData));
	pdmcc->HandlingFunction = HrReportContext;

	return XBDM_MULTIRESPONSE;
}

DMHRAPI HrSetContext(LPCSTR szCommand, LPSTR szResponse,
	DWORD cchResponse, PDM_CMDCONT pdmcc)
{
	DMCR dmcr;
	DWORD dwThreadId;
	HRESULT hr;
	BOOL bCopy;

	char sz[0x10];

	if(!pdmcc)
		return E_FAIL;

	if(!FGetNamedDwParam(szCommand, "thread", &dwThreadId, szResponse))
		return E_FAIL;

	ZeroMemory(&dmcr, sizeof(DMCR));

	dmcr.Context.ContextFlags = CONTEXT_FULL;
	dmcr.CurrentRegister = 0;
	dmcr.Register = NULL;

	hr = DmGetThreadContext(dwThreadId, &dmcr.Context);

	if(FAILED(hr))
		return hr;

	for(;;)
	{
		PcregNext(&dmcr);

		if(dmcr.Register == NULL)
			break;

		if(dmcr.Register->Size == 4)
			bCopy = FGetDwParam(szCommand, dmcr.Register->Name, (DWORD*)sz);
		else if(dmcr.Register->Size == 8)
			bCopy = FGetQwordParam(szCommand, dmcr.Register->Name, (ULARGE_INTEGER*)sz);
		else if(dmcr.Register->Size == 0x10)
			bCopy = FGetVectorParam(szCommand, dmcr.Register->Name, (float*)sz);
		else
			bCopy = FALSE;

		if(bCopy)
			memcpy((char*)&dmcr.Context + dmcr.Register->Offset, sz, dmcr.Register->Size);
	}

	hr = DmSetThreadContext(dwThreadId, &dmcr.Context);

	return hr;
}

DMHRAPI HrReportThreadList(PDM_CMDCONT pdmcc, LPSTR szResponse, DWORD cchResponse)
{
	if(pdmcd->cch == pdmcd->ib)
	{
		DmFreePool(pdmcd->rgb);
		return XBDM_ENDOFLIST;
	}

	pdmcc->DataSize = 0;

	while((pdmcc->DataSize + 0x10 < pdmcc->BufferSize)
		&& (pdmcd->cch != pdmcd->ib))
	{
		pdmcc->DataSize += RtlSprintf((char*)pdmcc->Buffer + pdmcc->DataSize, "%d\r\n", ((LPDWORD)pdmcd->rgb)[pdmcd->ib]);
		pdmcd->ib++;
	}
	return XBDM_NOERR;
}

DMHRAPI HrListThreads(LPCSTR szCommand, LPSTR szResponse,
	DWORD cchResponse, PDM_CMDCONT pdmcc)
{
	HRESULT hr;

	if(!pdmcc)
		return E_FAIL;

	pdmcd->rgb = (char*)DmAllocatePoolWithTag(0x400, 'xbdm');
	pdmcd->cch = 0x100;
	
	if(!pdmcd->rgb)
		return E_OUTOFMEMORY;

	hr = DmGetThreadList((LPDWORD)pdmcd->rgb, &pdmcd->cch);

	if(FAILED(hr))
	{
		if(hr == XBDM_BUFFER_TOO_SMALL)
			hr = E_UNEXPECTED;

		DmFreePool(pdmcd->rgb);
	}
	else
	{
		hr = XBDM_MULTIRESPONSE;
		strcpy_s(szResponse, cchResponse, "thread list follows");

		pdmcc->HandlingFunction = HrReportThreadList;
		pdmcd->ib = 0;
	}

	return hr;
}

DMHRAPI HrReportThreadListEx(PDM_CMDCONT pdmcc, LPSTR szResponse, DWORD cchResponse)
{
	if(pdmcd->cch == pdmcd->ib)
	{
		DmFreePool(pdmcd->rgb);
		return XBDM_ENDOFLIST;
	}

	pdmcc->DataSize = 0;

	while((pdmcc->DataSize + 0x10 < pdmcc->BufferSize)
		&& (pdmcd->cch != pdmcd->ib))
	{
		pdmcc->DataSize += RtlSprintf((char*)pdmcc->Buffer + pdmcc->DataSize, "%08X\r\n", ((LPDWORD)pdmcd->rgb)[pdmcd->ib]);
		pdmcd->ib++;
	}
	return XBDM_NOERR;
}

DMHRAPI HrListThreadsEx(LPCSTR szCommand, LPSTR szResponse,
	DWORD cchResponse, PDM_CMDCONT pdmcc)
{
	HRESULT hr;

	if(!pdmcc)
		return E_FAIL;

	pdmcd->rgb = (char*)DmAllocatePoolWithTag(0x400, 'xbdm');
	pdmcd->cch = 0x100;
	
	if(!pdmcd->rgb)
		return E_OUTOFMEMORY;

	hr = DmGetThreadList((LPDWORD)pdmcd->rgb, &pdmcd->cch);

	if(FAILED(hr))
	{
		if(hr == XBDM_BUFFER_TOO_SMALL)
			hr = E_UNEXPECTED;

		DmFreePool(pdmcd->rgb);
	}
	else
	{
		hr = XBDM_MULTIRESPONSE;
		strcpy_s(szResponse, cchResponse, "thread list follows");

		pdmcc->HandlingFunction = HrReportThreadListEx;
		pdmcd->ib = 0;
	}

	return hr;
}

DMHRAPI HrGetCpuKey(LPCSTR szCommand, LPSTR szResponse,
	DWORD cchResponse, PDM_CMDCONT pdmcc)
{
	QWORD fuses[12];

	HvGetFuses(fuses);

	RtlSnprintf(szResponse, cchResponse, "%016I64X%016I64X", fuses[3], fuses[5]);
	return XBDM_NOERR;
}

DMHRAPI HrContinueThread(LPCSTR szCommand, LPSTR szResponse,
	DWORD cchResponse, PDM_CMDCONT pdmcc)
{
	DWORD dwThreadId;

	if(!FGetNamedDwParam(szCommand, "thread", &dwThreadId, szResponse))
		return E_FAIL;

	return DmContinueThread(dwThreadId, (BOOL)PchGetParam(szCommand, "exception", FALSE));
}

DMHRAPI HrDoStopOn(LPCSTR szCommand, LPSTR szResponse,
	DWORD cchResponse, BOOL fStop)
{
	DWORD dw = 0;

	if(PchGetParam(szCommand, "all", FALSE))
		dw = -1;
	else
	{
		if(PchGetParam(szCommand, "fce", FALSE))
			dw |= DMSTOP_FCE;
		if(PchGetParam(szCommand, "debugstr", FALSE))
			dw |= DMSTOP_DEBUGSTR;
		if(PchGetParam(szCommand, "createthread", FALSE))
			dw |= DMSTOP_CREATETHREAD;
		if(PchGetParam(szCommand, "stacktrace", FALSE))
			dw |= DMSTOP_STACKTRACE;
		if(PchGetParam(szCommand, "modload", FALSE))
			dw |= DMSTOP_MODLOAD;
	}

	return DmStopOn(dw, fStop);
}

DMHRAPI HrStopOn(LPCSTR szCommand, LPSTR szResponse,
	DWORD cchResponse, PDM_CMDCONT pdmcc)
{
	return HrDoStopOn(szCommand, szResponse, cchResponse, TRUE);
}

DMHRAPI HrNoStopOn(LPCSTR szCommand, LPSTR szResponse,
	DWORD cchResponse, PDM_CMDCONT pdmcc)
{
	return HrDoStopOn(szCommand, szResponse, cchResponse, FALSE);
}

DMHRAPI HrIsThreadStopped(LPCSTR szCommand, LPSTR szResponse,
	DWORD cchResponse, PDM_CMDCONT pdmcc)
{
	DM_THREADSTOP dmts;
	DWORD dwThreadId;
	HRESULT hr;

	if(!pdmcc)
		return E_FAIL;

	if(!FGetNamedDwParam(szCommand, "thread", &dwThreadId, szResponse))
		return E_FAIL;

	hr = DmIsThreadStopped(dwThreadId, &dmts);

	if(FAILED(hr))
		return hr;

	if(dmts.NotifiedReason == DM_ASSERT)
		RtlSnprintf(szResponse, cchResponse, "assert thread=0x%08x straddr=0x%08x strlen=0x%08x",
		dmts.u.DebugStr.ThreadId, dmts.u.DebugStr.String, dmts.u.DebugStr.Length);
	else if(dmts.NotifiedReason == DM_DEBUGSTR)
		RtlSnprintf(szResponse, cchResponse, "debugstr thread=0x%08x stop", dmts.u.DebugStr.ThreadId);
	else if(!FGetNotifySz(dmts.NotifiedReason, (ULONG_PTR)&dmts.u, szResponse, cchResponse))
		strcpy_s(szResponse, cchResponse, "stopped");

	return XBDM_NOERR;
}

DMHRAPI HrSuspendThread(LPCSTR szCommand, LPSTR szResponse,
	DWORD cchResponse, PDM_CMDCONT pdmcc)
{
	DWORD dwThreadId;

	if(!pdmcc)
		return E_FAIL;

	if(!FGetNamedDwParam(szCommand, "thread", &dwThreadId, szResponse))
		return FALSE;

	return DmSuspendThread(dwThreadId);
}

DMHRAPI HrResumeThread(LPCSTR szCommand, LPSTR szResponse,
	DWORD cchResponse, PDM_CMDCONT pdmcc)
{
	DWORD dwThreadId;

	if(!pdmcc)
		return E_FAIL;

	if(!FGetNamedDwParam(szCommand, "thread", &dwThreadId, szResponse))
		return FALSE;

	return DmResumeThread(dwThreadId);
}

DMHRAPI HrReportThreadInfo(PDM_CMDCONT pdmcc, LPSTR szResponse, DWORD cchResponse)
{
	if(pdmcc->BytesRemaining == 2)
		return XBDM_ENDOFLIST;

	pdmcc->BytesRemaining++;

	RtlSnprintf((char*)pdmcc->Buffer, pdmcc->BufferSize,
		"suspend=%d priority=%d tlsbase=0x%08x start=0x%08x base=0x%08x limit=0x%08x slack=0x%08x createhi=0x%08x createlo=0x%08x nameaddr=0x%08x namelen=0x%08x proc=0x%02X lasterr=0x%08x",
		pdmcd->dmti.SuspendCount, pdmcd->dmti.Priority, pdmcd->dmti.TlsBase, pdmcd->dmti.StartAddress,
		pdmcd->dmti.StackBase, pdmcd->dmti.StackLimit, pdmcd->dmti.StackSlackSpace, pdmcd->dmti.CreateTime.dwHighDateTime,
		pdmcd->dmti.CreateTime.dwLowDateTime, pdmcd->dmti.ThreadNameAddress,
		pdmcd->dmti.ThreadNameLength, pdmcd->dmti.CurrentProcessor, pdmcd->dmti.LastError);

	return XBDM_NOERR;
}

DMHRAPI HrGetThreadInfo(LPCSTR szCommand, LPSTR szResponse,
	DWORD cchResponse, PDM_CMDCONT pdmcc)
{
	DWORD dwThreadId;
	HRESULT hr;

	if(!pdmcc)
		return E_FAIL;

	if(!FGetNamedDwParam(szCommand, "thread", &dwThreadId, szResponse))
		return FALSE;

	pdmcd->dmti.Size = sizeof(DM_THREADINFOEX);
	hr = DmGetThreadInfoEx(dwThreadId, &pdmcd->dmti);

	if(FAILED(hr))
		return hr;

	pdmcc->HandlingFunction = HrReportThreadInfo;
	pdmcc->BytesRemaining = 1;

	strcpy_s(szResponse, cchResponse, "thread info follows");

	return XBDM_MULTIRESPONSE;
}

DMHRAPI HrReportModuleSections(PDM_CMDCONT pdmcc, LPSTR szResponse, DWORD cchResponse)
{
	if(pdmcc->BytesRemaining == 3)
		return XBDM_ENDOFLIST;

	RtlSnprintf((char*)pdmcc->Buffer, pdmcc->BufferSize, "name=\"%s\" base=0x%08x size=0x%08x index=%d flags=%d",
		pdmcd->dmsl.Name, pdmcd->dmsl.BaseAddress, pdmcd->dmsl.Size, pdmcd->dmsl.Index, pdmcd->dmsl.Flags);

	if(pdmcc->BytesRemaining == 2)
		pdmcc->BytesRemaining++;
	else if(FAILED(DmWalkModuleSections((PDM_WALK_MODSECT*)&pdmcd->rgb, pdmcd->sz, &pdmcd->dmsl)))
	{
		pdmcc->BytesRemaining++;
		DmCloseModuleSections((PDM_WALK_MODSECT)pdmcd->rgb);
	}

	return XBDM_NOERR;
}

DMHRAPI HrListModuleSections(LPCSTR szCommand, LPSTR szResponse,
	DWORD cchResponse, PDM_CMDCONT pdmcc)
{
	if(!pdmcc)
		return E_FAIL;

	if(!FGetSzParam(szCommand, "name", pdmcd->sz, sizeof(pdmcd->sz)))
	{
		strcpy_s(szResponse, cchResponse, "missing name");
		return E_FAIL;
	}

	pdmcd->rgb = NULL;
	pdmcc->HandlingFunction = HrReportModuleSections;
	pdmcc->BytesRemaining = 1;

	if(NT_SUCCESS(DmWalkModuleSections((PDM_WALK_MODSECT*)&pdmcd->rgb, pdmcd->sz, &pdmcd->dmsl)))
		return XBDM_MULTIRESPONSE;

	return XBDM_NOSUCHFILE;
}

DMHRAPI HrGetProcessId(LPCSTR szCommand, LPSTR szResponse,
	DWORD cchResponse, PDM_CMDCONT pdmcc)
{
	ULARGE_INTEGER time;

	if(dwExecState == DMN_EXEC_PENDING)
		return XBDM_NOTHREAD;

	while(g_dmGlobals.dwPid == 0)
	{
		KeQuerySystemTime(&time);
		g_dmGlobals.dwPid = time.LowPart + __mftb32();
	}

	RtlSnprintf(szResponse, cchResponse, "pid=0x%08x", g_dmGlobals.dwPid);

	return XBDM_NOERR;
}

DMHRAPI HrReportXexField(PDM_CMDCONT pdmcc, LPSTR szResponse, DWORD cchResponse)
{
	if(pdmcc->BytesRemaining == 3)
		return XBDM_ENDOFLIST;

	if(pdmcc->BytesRemaining == 1)
	{
		pdmcc->BytesRemaining++;
		RtlSnprintf((char*)pdmcc->Buffer, pdmcc->BufferSize, "fieldsize=0x%08x", 4);
	}
	else if(pdmcc->BytesRemaining == 2)
	{
		pdmcc->BytesRemaining++;
		RtlSnprintf((char*)pdmcc->Buffer, pdmcc->BufferSize, "%08X", (DWORD)pdmcd->rgb);
	}

	return XBDM_NOERR;
}

DMHRAPI HrGetXexField(LPCSTR szCommand, LPSTR szResponse,
	DWORD cchResponse, PDM_CMDCONT pdmcc)
{
	PLDR_DATA_TABLE_ENTRY pldte;
	char sz[MAX_PATH];
	DWORD dw;
	HRESULT hr;

	if(!pdmcc)
		return E_FAIL;

	if(!FGetSzParam(szCommand, "module", sz, sizeof(sz)))
	{
		strcpy_s(szResponse, cchResponse, "missing module");
		return E_FAIL;
	}

	if(!FGetNamedDwParam(szCommand, "field", &dw, szResponse))
		return E_FAIL;

	if(dw != 0x00010100)
	{
		DbgPrint("[xbdm] unknown command \"%s\"\n", szCommand);
		return XBDM_INVALIDCMD;
	}

	hr = FGetModuleHandle(sz, &pldte, TRUE);

	if(!pldte)
		return XBDM_NOSUCHFILE;

	pdmcd->rgb = (char*)RtlImageXexHeaderField(pldte->XexHeaderBase, dw);
	pdmcc->HandlingFunction = HrReportXexField;
	pdmcc->BytesRemaining = 1;

	if(pdmcd->rgb)
		return XBDM_MULTIRESPONSE;
	else
		return XBDM_FIELDNOTPRESENT;
}

DMHRAPI HrGetExecState(LPCSTR szCommand, LPSTR szResponse,
	DWORD cchResponse, PDM_CMDCONT pdmcc)
{
	char *sz;

	switch(dwExecState)
	{
	case DMN_EXEC_START:
		sz = "start";
		break;
	case DMN_EXEC_STOP:
		sz = "stop";
		break;
	case DMN_EXEC_PENDING:
		sz = "pending";
		break;
		case DMN_EXEC_REBOOT:
			sz = "reboot";
		break;
	case DMN_EXEC_PENDING_TITLE:
		sz = "pending_title";
		break;
	case DMN_EXEC_REBOOT_TITLE:
		sz = "reboot_title";
		break;
	}

	RtlSnprintf(szResponse, cchResponse, "%s", sz);

	return XBDM_NOERR;
}

DMHRAPI HrGetConsoleId(LPCSTR szCommand, LPSTR szResponse,
	DWORD cchResponse, PDM_CMDCONT pdmcc)
{
	char sz[0xD];
	NTSTATUS st;

	ZeroMemory(sz, sizeof(sz));
	st = XeKeysGetConsoleID(NULL, sz);

	if(FAILED(st))
		return (HRESULT)(st | 0x10000000);
	
	RtlSnprintf(szResponse, cchResponse, "consoleid=%s", sz);
	return XBDM_NOERR;
}

DMHRAPI HrBreak(LPCSTR szCommand, LPSTR szResponse,
	DWORD cchResponse, PDM_CMDCONT pdmcc)
{
	HRESULT hr = XBDM_NOERR;
	BOOL bClear;
	DWORD dwAddr;
	DWORD dwFlags;
	DWORD dwSize;

	if(PchGetParam(szCommand, "now", FALSE))
	{
		Sleep(250);
		__emit(BREAKPOINT_BREAK);
	}
	else if(PchGetParam(szCommand, "start", FALSE))
	{
		if(FAILED(hr = DmSetInitialBreakpoint()))
			strcpy_s(szResponse, cchResponse, "execution not pending");
	}
	else if(PchGetParam(szCommand, "clearall", FALSE))
		DmRemoveAllBreakpoints();
	else
	{
		bClear = (BOOL)PchGetParam(szCommand, "clear", FALSE);
		if(FGetNamedDwParam(szCommand, "addr", &dwAddr, szResponse))
		{
			if(bClear)
				DmRemoveBreakpoint((PVOID)dwAddr);
			else
				DmSetBreakpoint((PVOID)dwAddr);
		}
		else
		{
			if(FGetDwParam(szCommand, "read", &dwAddr))
				dwFlags = DMBREAK_READ;
			else if(FGetDwParam(szCommand, "write", &dwAddr))
				dwFlags = DMBREAK_WRITE;
			else if(FGetDwParam(szCommand, "readwrite", &dwAddr))
				dwFlags = DMBREAK_READWRITE;
			else if(FGetDwParam(szCommand, "execute", &dwAddr))
				dwFlags = DMBREAK_EXECUTE;
			else
				hr = E_FAIL;

			if(NT_SUCCESS(hr))
			{
				if(bClear)
					dwFlags = DMBREAK_NONE;
				else if(!FGetNamedDwParam(szCommand, "size", &dwSize, szResponse))
					hr = E_FAIL;

				if(NT_SUCCESS(hr))
					DmSetDataBreakpoint((PVOID)dwAddr, dwFlags, dwSize);
			}
		}
	}

	if(NT_SUCCESS(hr))
		szResponse[0] = 0;

	return hr;
}

DMHRAPI HrGetDebuggerVersion(LPCSTR szCommand, LPSTR szResponse,
	DWORD cchResponse, PDM_CMDCONT pdmcc)
{
	strcpy_s(szResponse, cchResponse, "2.0.20353.0");
	return XBDM_NOERR;
}

DMHRAPI HrKhoungDm(LPCSTR szCommand, LPSTR szResponse,
	DWORD cchResponse, PDM_CMDCONT pdmcc)
{
	VdDisplayFatalError(69);
	return XBDM_NOERR;
}

DMHRAPI HrWhoMadeThis(LPCSTR szCommand, LPSTR szResponse,
	DWORD cchResponse, PDM_CMDCONT pdmcc)
{
	strcpy_s(szResponse, cchResponse, "Natelx did, of course");
	return XBDM_NOERR;
}

// Please keep in alphabetical order!
// And use these permission defines when adding commands!
/*
#define DMPL_PRIV_READ For reading from the console
#define DMPL_PRIV_WRITE For writing to the console (files)
#define DMPL_PRIV_CONTROL For controlling the console (must have this to do ANYTHING debug related!!!)
#define DMPL_PRIV_CONFIGURE For configuring the console
#define DMPL_PRIV_MANAGE For managing the console (must have this to edit accounts!!!)
#define DMPL_PRIV_HVX For ANYTHING that has to do with the hypervisor expansion(s)
*/
DMCMD rgbcmd[] =
{
	{ "altaddr",				DMPL_PRIV_READ,						HrGetAltAddr			}, // Gets the title ip address
	{ "break",					DMPL_PRIV_CONTROL,					HrBreak					}, // Manages breakpoints
	{ "bye",					0,									HrEndConversation		}, // Ends the connection
	{ "consolefeatures",		DMPL_PRIV_READ,						HrGetConsoleFeatures	}, // Gets the console features (debug, ram)
	{ "consoletype",			DMPL_PRIV_READ,						HrGetConsoleType		}, // Gets the console type (test, dev)
	{ "continue",				DMPL_PRIV_CONTROL,					HrContinueThread		}, // Continues a thread
	{ "dbgname",				DMPL_PRIV_READ,						HrDbgName				}, // Gets the console name
	{ "debugger",				DMPL_PRIV_CONTROL,					HrAttachDebugger		}, // Signals that a debugger has been attached or deattached
	{ "delete",					DMPL_PRIV_WRITE,					HrDelete				}, // Deletes a file or directory
	{ "dirlist",				DMPL_PRIV_READ,						HrGetDirList			}, // Gets a list of items in a folder
	{ "dmversion",				DMPL_PRIV_CONTROL,					HrGetDebuggerVersion	}, // Gets the debugger version
	{ "drivefreespace",			DMPL_PRIV_READ,						HrGetDriveFreeSpace		}, // Gets some stats about the drive's volume size
	{ "drivelist",				DMPL_PRIV_READ,						HrGetDriveList			}, // Gets the list of connected drives
	{ "drivemap",				DMPL_PRIV_CONTROL,					HrDrivemap				}, // Sets if FLASH:\\ is visible in the drive browser
	{ "dumpmode",				DMPL_PRIV_CONFIGURE,				HrSetDumpMode			}, // Configures the crash dump mode
	{ "dvdeject",				DMPL_PRIV_CONTROL,					HrDvdEject				}, // Opens or closes the dvd tray
	{ "getconsoleid",			DMPL_PRIV_CONTROL,					HrGetConsoleId			}, // Gets the console id
	{ "getcontext",				DMPL_PRIV_CONTROL,					HrGetContext			}, // Gets a thread context
	{ "getcpukey",				DMPL_PRIV_HVX,						HrGetCpuKey				}, // Gets the cpu key
	{ "getexecstate",			DMPL_PRIV_CONTROL,					HrGetExecState			}, // Displays the execution state
	{ "getfile",				DMPL_PRIV_READ,						HrGetFile				}, // Xbox->PC transfer
	{ "getfileattributes",		DMPL_PRIV_READ,						HrGetFileAttr			}, // Gets file attributes
	{ "getmem",					DMPL_PRIV_CONTROL,					HrGetMemory				}, // Gets memory
	{ "getmemex",				DMPL_PRIV_CONTROL,					HrGetMemoryEx			}, // Gets memory in data
	{ "getpid",					DMPL_PRIV_CONTROL,					HrGetProcessId			}, // Gets the process id
	{ "go",						DMPL_PRIV_CONTROL,					HrGo					}, // Continues all threads
	{ "help",					0,									HrHelp					}, // Gets info on every command
	{ "hwinfo",					0,									HrHwInfo				}, // Does some listing of stuff for cOz
	{ "khoungdm",				DMPL_PRIV_CONTROL,					HrKhoungDm				}, // E69
	{ "isdebugger",				DMPL_PRIV_CONTROL,					HrIsDebuggerAttached	}, // Gets info on the current debugger
	{ "isstopped",				DMPL_PRIV_CONTROL,					HrIsThreadStopped		}, // Returns information on a stopped thread
	{ "magicboot",				DMPL_PRIV_CONTROL,					HrMagicReboot			}, // Changes the currently running title, and/or reboots the console
	{ "mkdir",					DMPL_PRIV_WRITE,					HrCreateDirectory		}, // Creates a folder
	{ "modsections",			DMPL_PRIV_WRITE,					HrListModuleSections	}, // Lists the module sections
	{ "modules",				DMPL_PRIV_CONTROL,					HrGetModules			}, // Returns a list of all the loaded modules (exe, dll)
	{ "nostopon",				DMPL_PRIV_CONTROL,					HrNoStopOn				}, // Changes what we stop on
	{ "notify",					DMPL_PRIV_CONTROL,					HrNotify				}, // Creates a notification channel
	{ "notifyat",				DMPL_PRIV_CONTROL,					HrNotifyAt				}, // Manages a notification channel
	{ "objlist",				0,									HrObjList				}, // Lists objects for cOz
	{ "rename",					DMPL_PRIV_WRITE,					HrRenameFile			}, // Renames a file or directory
	{ "resume",					DMPL_PRIV_CONTROL,					HrResumeThread			}, // Resumes a thread
	{ "screenshot",				DMPL_PRIV_CONTROL,					HrScreenshot			}, // Takes a screenshot
	{ "sendfile",				DMPL_PRIV_WRITE,					HrSendFile				}, // PC->Xbox transfer
	{ "sendvfile",				DMPL_PRIV_WRITE,					HrSendVolumeFile		}, // PC->Xbox transfer with several files
	{ "setcolor",				DMPL_PRIV_CONTROL,					HrSetColor				}, // Sets the color of the console in neighborhood
	{ "setcontext",				DMPL_PRIV_CONTROL,					HrSetContext			}, // Sets a thread context
	{ "setfileattributes",		DMPL_PRIV_WRITE,					HrSetFileAttr			}, // Sets file attributes
	{ "setmem",					DMPL_PRIV_CONTROL,					HrSetMemory				}, // Sets memory
	{ "setsystime",				DMPL_PRIV_CONFIGURE,				HrSetSystemTime			}, // Sets the system time
	{ "shutdown",				DMPL_PRIV_CONTROL,					HrShutdown				}, // Shuts down the console
	{ "stop",					DMPL_PRIV_CONTROL,					HrStop					}, // Stops all threads
	{ "stopon",					DMPL_PRIV_CONTROL,					HrStopOn				}, // Changes what we stop on
	{ "spew",					DMPL_PRIV_CONTROL,					HrSpew					}, // Spews debug output
	{ "suspend",				DMPL_PRIV_CONTROL,					HrSuspendThread			}, // Suspends a thread
	{ "systeminfo",				DMPL_PRIV_READ,						HrGetSystemInfo			}, // Gets system info
	{ "systime",				DMPL_PRIV_CONFIGURE,				HrGetSystemTime			}, // Sets the system time
	{ "threadex",				DMPL_PRIV_CONTROL,					HrListThreadsEx			}, // Lists threads in a different format
	{ "threadinfo",				DMPL_PRIV_CONTROL,					HrGetThreadInfo			}, // Returns info on a thread
	{ "threads",				DMPL_PRIV_CONTROL,					HrListThreads			}, // Gets a list of threads
	{ "xbeinfo",				DMPL_PRIV_READ,						HrGetXbeInfo			}, // Gets information on the running executable
	{ "xexfield",				DMPL_PRIV_CONTROL,					HrGetXexField			}, // Gets an xex field
	{ "walkmem",				DMPL_PRIV_CONTROL,					HrWalkMemory			}, // Lists memory and protection pages
	{ "whomadethis",			DMPL_PRIV_CONTROL,					HrWhoMadeThis			}, // Guess who
};
int cchcmd = (sizeof(rgbcmd) / sizeof(DMCMD));
