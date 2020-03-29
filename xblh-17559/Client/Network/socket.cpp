#include "socket.h"

char *key2 = "y6ub65ggy74n3t8vn85y8956y6nn6n66nhjklo;poylukjgtrfedwyvh54v98y5";
char buff[100];

void TDxSocket::mysend(SOCKET clntSock, char* fmt, ...)
{
	char* data = (char*)malloc(2048);  
	int   len;

	va_list ap;
	va_start(ap, fmt);
	len = vsprintf(data, fmt, ap);
	va_end(ap);

	NetDll_send(XNCALLER_SYSAPP, clntSock, data, len, 0);
}

char* TDxSocket::gettype()
{
	char* type = (char*)malloc(512);
	vector<string> data = this->explode("|", buff);
	strcpy(type, data[0].c_str());
	return(type);
}

char* TDxSocket::getdata(int i)
{
	char* getdata = (char*)malloc(2048);
	vector<string> data = this->explode("|", buff);
	strcpy(getdata, data[i].c_str());
	return(getdata);
}

//BOOL Receive(PVOID Buffer, DWORD Size) {
//	DWORD Received = 0;
//	DWORD Remaining = Size;
//	while (Remaining > 0)
//	{
//		DWORD Result = NetDll_recv(XNCALLER_SYSAPP, Socket, (PCHAR)Buffer + Received, min(0x800, Remaining), 0);
//		if (Result <= 0) return FALSE;
//		Remaining -= Result;
//		Received += Result;
//	}
//
//	XeCryptRc4(NetworkKey, 0x10, (PBYTE)Buffer, Size);
//	return (Received == Size);
//}

char* TDxSocket::myrecv(SOCKET clntSock)
{	
	char *test = (char*)malloc(2048);
	memset(buff, '\0', sizeof(buff));

	//int l = recv(clntSock, buff, sizeof(buff) - 1, 0);
	int l = NetDll_recv(XNCALLER_SYSAPP, clntSock, buff, sizeof(buff) - 1, 0);
	if(l <= 0) return 0;

	return(buff);
}

vector<string> TDxSocket::explode( const string &delimiter, const string &str)
{
    vector<string> arr;

    int strleng = str.length();
    int delleng = delimiter.length();
    if (delleng==0)
        return arr;

    int i=0;
    int k=0;
    while( i<strleng )
    {
        int j=0;
        while (i+j<strleng && j<delleng && str[i+j]==delimiter[j])
            j++;
        if (j==delleng)
        {
            arr.push_back(  str.substr(k, i-k) );
            i+=delleng;
            k=i;
        }
        else
        {
            i++;
        }
    }
    arr.push_back(  str.substr(k, i-k) );
    return arr;
}