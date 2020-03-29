#include "xshell.h"

using namespace std;


VOID patchInDashStrings(DWORD* addr, DWORD xex, DWORD path){
	DWORD data[4];

	if(xex & 0x8000){ // If bit 16 is 1
		data[0] = 0x3D600000 + (((xex >> 16) & 0xFFFF) + 1); // lis 	%r11, dest>>16 + 1
	}else{
		data[0] = 0x3D600000 + ((xex >> 16) & 0xFFFF); // lis 	%r11, dest>>16
	}
	if(path & 0x8000){ // If bit 16 is 1
		data[1] = (DWORD)0x3D400000 + (((path >> 16) & 0xFFFF) + 1); // lis 	%r11, dest>>16 + 1
	}else{
		data[1] = (DWORD)0x3D400000 + ((path >> 16) & 0xFFFF); // lis 	%r11, dest>>16
	}

	data[2] = 0x388B0000 + (xex & 0xFFFF);
	data[3] = (DWORD)0x386A0000 + (DWORD)(path & 0xFFFF);

	//printf("[RGLOADER]: Patch data @ %X = %08X.%08X.%08X.%08X\n", addr, data[0], data[1], data[2], data[3]);
	
	DmSetMemory((LPVOID)addr, 0x10, (LPCVOID)data, 0);
}

int patch_Xshell_start_path(string nPath){

	//nPath = "\\Device\\Harddisk0\\Partition1\\DEVKIT\\Utilities\\DashSelector";
	//string xex = "DashSelector.xex";

	int backslash = nPath.rfind("\\");
	string xex = nPath.substr(backslash+1, nPath.length()-(backslash+1));
	nPath=nPath.substr(0, backslash);

	//xbox::utilities::DbgOut("[xblh] Setting xshell start button to: %s  %s !\n", nPath.c_str(), xex.c_str());

	startXex=new char[xex.length()];
	strcpy(startXex, xex.c_str());
	startPath=new char[nPath.length()];
	strcpy(startPath, nPath.c_str());

	OffsetManager om;
	XSHELLOffsets* offsets = om.getXshellOffsets();

	if(!offsets){
		//xbox::utilities::DbgOut("[xblh] Failed to load xshell offsets...\r\n");
		return -1;
	}

	patchInDashStrings((DWORD*)offsets->loc1 , (DWORD)startXex, (DWORD)startPath); 
	patchInDashStrings((DWORD*)offsets->loc2 , (DWORD)startXex, (DWORD)startPath); 
	patchInDashStrings((DWORD*)offsets->loc3 , (DWORD)startXex, (DWORD)startPath); 
	patchInDashStrings((DWORD*)offsets->loc4 , (DWORD)startXex, (DWORD)startPath);
	
	return 1;
}