#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "../stdafx.h"

using namespace std;

#pragma once
class TDxSocket {
private:

public:
	void mysend(SOCKET clntSock, char* fmt, ...);
	char* myrecv(SOCKET clntSock);
	char* gettype();
	char* getdata(int i);
	vector<string> explode( const string &delimiter, const string &explodeme);
};





