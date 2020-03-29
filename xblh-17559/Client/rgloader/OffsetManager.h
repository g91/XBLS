#pragma once

#include "..\stdafx.h"

struct XAMOffsets
{
	DWORD live_siflc;
	DWORD live_piflc;
	DWORD live_notice;
	DWORD live_xexds;
	DWORD live_xetgs;
	DWORD live_xeas;
	DWORD live_xemacs;
};

struct XBDMOffsets
{
	DWORD map_internal_check;  //nop check drivemap internal=1 
	DWORD mass0_obname_ptr; //ptr of device name
	DWORD mass0_enable;
	DWORD mass0_obname; //device name obj

	DWORD mass1_obname_ptr; //ptr of device name
	DWORD mass1_enable;
	DWORD mass1_obname; //device name obj

	DWORD mass2_obname_ptr; //ptr of device name
	DWORD mass2_enable;
	DWORD mass2_obname; //device name obj

	DWORD flash_obname_ptr; //ptr of device name
	DWORD flash_enable;
	DWORD flash_obname; //device name obj

	DWORD hddsysext_obname_ptr; //ptr of device name
	DWORD hddsysext_enable;
	DWORD hddsysext_obname; //device name obj

	DWORD intusbsysext_obname_ptr; //ptr of device name
	DWORD intusbsysext_enable;
	DWORD intusbsysext_obname; //device name obj
};

struct SIGNINOffsets
{
	DWORD NoSignNotice;
};

struct XSHELLOffsets
{
	DWORD loc1, loc2, loc3, loc4;
};

struct HUDOffsets
{
	DWORD FamilySettings_LaunchStr;
	DWORD BootToDashHelper_Jump;
	DWORD LaunchData_FamilySettings;
	DWORD BootToDashHelper_Func;
	//Use xextool to dump resources from hud.xex.  Search for "Family Settings"
	//NOTE: New string cannot be longer than the old one
	DWORD FamilySettings_Str1;
	DWORD FamilySettings_Str2;
};

class OffsetManager
{
public:
	OffsetManager();
	XBDMOffsets* getXbdmOffsets();
	XAMOffsets* getXamOffsets();
	SIGNINOffsets* getSigninOffsets();
	XSHELLOffsets* getXshellOffsets();
	HUDOffsets* getHudOffsets();
private:
	short getKernelVersion();
	short _kernel;
};