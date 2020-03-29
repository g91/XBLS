#include "HUD.h"
#include "KernelExports.h"

OffsetManager offsetmanager;

HANDLE searchForHandle(const char* mName){

	PLDR_DATA_TABLE_ENTRY curTab = (PLDR_DATA_TABLE_ENTRY)GetModuleHandle("xboxkrnl.exe");
	PXEX_HEADER_STRING peName;

	curTab = (PLDR_DATA_TABLE_ENTRY)curTab->InLoadOrderLinks.Flink;

	while(curTab != NULL)
	{
		//printf("Current handle: %08X\n", curTab);
		peName = (PXEX_HEADER_STRING)RtlImageXexHeaderField(curTab->XexHeaderBase, 0x000183FF);

		//if((curTab->BaseDllName.Buffer != NULL) && (curTab->BaseDllName.Buffer[0] != 0))
			//printf("\tBaseName       : %S\r\n", curTab->BaseDllName.Buffer);

		if((peName != NULL) && (peName->Data[0] != 0)){
			if(stricmp((char*)peName->Data, mName) == 0){
				HANDLE ret = (HANDLE)curTab;
				//printf("Found module %s:  %08X\n", mName, ret);
				return ret;
			}
		}
		curTab = (PLDR_DATA_TABLE_ENTRY)curTab->InLoadOrderLinks.Flink;
	}
	return INVALID_HANDLE_VALUE;
}


void replaceHudString( const char* newtext, DWORD addr, int length){

	char* temp = new char[length+1];
	for(int i=0; i<length; i++) temp[i]=' ';
	temp[length]='\0';

	int nLen=strlen(newtext);
	for(int i=0; i<nLen; i++)temp[i]=newtext[i];

	DmSetMemory((LPVOID)addr, length+1, temp, 0);
}

void patchHUDStrings(void){

	HANDLE hModule = searchForHandle( "hud.dll" );
	if(hModule == INVALID_HANDLE_VALUE){
		printf("\nERROR: Unable to get handle to hud.dll\n");
	}

	VOID* pSectionData;
	DWORD dwSectionSize;
	if( !XGetModuleSection(hModule ,"hud", &pSectionData, &dwSectionSize ) ){
		printf("\nERROR: Unable to get module section data from hud.dll\n");
	}

	HUDOffsets* offsets = offsetmanager.getHudOffsets();

	if(offsets)
	{
		replaceHudString(HUD_FamilySettings_String, (DWORD)pSectionData + offsets->FamilySettings_Str1, HUD_FamilySettings_Len);
		replaceHudString(HUD_FamilySettings_String, (DWORD)pSectionData + offsets->FamilySettings_Str2, HUD_FamilySettings_Len);
	}
}


DWORD HUD_BootToDashHelper_Hook(DWORD* _XUIOBJ, _XDASHLAUNCHDATA* LaunchData , DWORD* cstr, DWORD* r6, DWORD* r7){
	/*printf("\n\n ***RGLoader.xex*** \n");
	printf("  -LaunchData- \n");
    printf("      dwVersion: 0x%X\n", LaunchData->dwVersion);
	printf("      dwCommand: 0x%X\n", LaunchData->dwCommand);
	printf("      dwUserIndex: 0x%X\n", LaunchData->dwUserIndex);*/

	HUDOffsets* offsets = offsetmanager.getHudOffsets();
	if(!offsets)
		return -1;

	if(LaunchData->dwCommand==(DWORD)offsets->LaunchData_FamilySettings){
		printf("\n[RGLOADER]: Jumping back to xshell!\n");
		//printf("[RGLOADER]: System thread, attempting to launch xshell.\n");
		XSetLaunchData( NULL, 0 );
		XAMLOADLAUNCHTITLEEX XamLoaderLaunchTitleEx = (XAMLOADLAUNCHTITLEEX)resolveFunct("xam.xex", 421);
		//XamLoaderLaunchTitleEx("\\Device\\Harddisk0\\Partition1\\DEVKIT\\Utilities\\DashSelector\\DashSelector.xex", "\\Device\\Harddisk0\\Partition1\\DEVKIT\\Utilities\\DashSelector", NULL, 0);
		XamLoaderLaunchTitleEx("\\SystemRoot\\xshell.xex", "\\SystemRoot", NULL, 0);
		//close HUD menu
		setmemdm((DWORD)((unsigned long)0x60 + (unsigned long)r7), 0);
		setmemdm((DWORD)((unsigned long)0x5C + (unsigned long)r7), 0);
		return 0;
	}
	else {
		
		return ((HUD_BOOTTODASHHELPER)offsets->BootToDashHelper_Func)(_XUIOBJ, LaunchData , cstr, r6,  r7);
	}
}



BOOL HUDPatchInJump(DWORD destination, BOOL linked=false){

	HUDOffsets* offsets = offsetmanager.getHudOffsets();
	if(!offsets)
		return -1;

	setmemdm( offsets->BootToDashHelper_Jump, makeBranch( offsets->BootToDashHelper_Jump, (offsets->FamilySettings_LaunchStr)+0x4, true));
	//setmem( HUD_BootToDashHelper_Jump, 0x60000000);

	//setmem(HUD_FamilySettings_LaunchStr, 0x4800001C);
	setmemdm( offsets->FamilySettings_LaunchStr, 0x4E800020); //blr
	BYTE data[0x10];
	patchInJump((PDWORD)data, (DWORD)destination, linked);
	HRESULT hr;
	hr = DmSetMemory((PDWORD)((offsets->FamilySettings_LaunchStr)+4), 0x10, (LPCVOID)data, 0);
	//return hr;
	return 1;
}


int patch_HUD_ReturnToXshell(){
	
	char* newLabel= "RGLoader\0\0";

	//rename labels
	//DmSetMemory((LPVOID)0x914142C0, (DWORD)9, newLabel, 0);//14719 str1
	//DmSetMemory((LPVOID)0x91414311, (DWORD)9, newLabel, 0);//14719 str2
	//DmSetMemory((LPVOID)0x914145E7, (DWORD)9, newLabel, 0);//14719 str3
	//DmSetMemory((LPVOID)0x91414638, (DWORD)9, newLabel, 0);//14719 str4
	
	HUDPatchInJump((DWORD)HUD_BootToDashHelper_Hook);
	patchHUDStrings();


	//patch_unhook_xexload();

	
	return 1;
}