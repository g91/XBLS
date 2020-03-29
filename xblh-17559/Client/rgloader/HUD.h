
#pragma once

#ifndef HUD_H
#define HUD_H

#include "stdafx.h"
#include <xbdm.h>
#include <stdio.h>
//#include "xecrypt.h"
#include "utilities.h"
#include "XexLoadImage.h"
#include "OffsetManager.h"

#define HUD_FamilySettings_String  "Launch XShell"
#define HUD_FamilySettings_Len     15

int patch_HUD_ReturnToXshell(void);

typedef DWORD (*HUD_FILLLAUNCHDATA)(DWORD* XDashLaunchData ,DWORD r4, DWORD selection);
//static HUD_FILLLAUNCHDATA HUD_FillLaunchData = (HUD_FILLLAUNCHDATA)HUD_FillLaunchData_Func;*/

typedef DWORD (*HUD_BOOTTODASHHELPER)(DWORD* _XUIOBJ, _XDASHLAUNCHDATA* LaunchData , DWORD* cstr, DWORD* r6, DWORD* r7);
//static HUD_BOOTTODASHHELPER HUD_BootToDashHelper = (HUD_BOOTTODASHHELPER)HUD_BootToDashHelper_Func;


//BootToDashHelper(DWORD* _XUIOBJ, DWORD* _XDASHLAUNCHDATA , DWORD* cstr, DWORD* r6, DWORD* r7)
//DWORD HUD_FillLaunchData_Hook(DWORD* XDashLaunchData ,DWORD r4, DWORD selection);
DWORD HUD_BootToDashHelper_Hook(DWORD* _XUIOBJ, _XDASHLAUNCHDATA* LaunchData , DWORD* cstr, DWORD* r6, DWORD* r7);


static BOOL testhud=false;

#endif