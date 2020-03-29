#include "OffsetManager.h"

XBDMOffsets xbdm_14719_15574 = {
	0x91F32594, //nop drivemap internal=1
	0x91F95F68, //mass0
	0x91F95F90,
	0x91F00970,
	0x91F95F94, //mass1
	0x91F95FBC,
	0x91F00980,
	0x91F95FC0, //mass2
	0x91F95FE8,
	0x91F00990,
	0x91F95EE4, //flash
	(0x91F95EE4 + 0x28),
	0x91F00960,
	0x91F96044, //hddsysext
	(0x91F96044 + 0x28) ,
	0x91F009F8,
	0x91F960C8, //intusbsysext
	(0x91F960C8 + 0x28) ,
	0x91F00A8C
};

//0x91F32974
//0x91F96F68
XBDMOffsets xbdm_16197_16202 = {
	0x91F3295C, //check
	0x91F96F68, //mass0
	0x91F96F90,
	0x91F00980,
	0x91F96F94, //mass1
	0x91F96FBC,
	0x91F00990,
	0x91F96FC0, //mass2
	0x91F96FE8,
	0x91F009A0,
	0x91F96EE4, //flash
	(0x91F96EE4 + 0x28),
	0x91F00970,
	0x91F97044, //hddsysext
	(0x91F97044 + 0x28) ,
	0x91F00A08,
	0x91F970C8, //intusbsysext
	(0x91F970C8 + 0x28) ,
	0x91F00A9C
};

XBDMOffsets xbdm_16537 = {
	0x91F329DC, //check
	0x91F96F68, //mass0
	0x91F96F90,
	0x91F00980,
	0x91F96F94, //mass1
	0x91F96FBC,
	0x91F00990,
	0x91F96FC0, //mass2
	0x91F96FE8,
	0x91F009A0,
	0x91F96EE4, //flash
	(0x91F96EE4 + 0x28),
	0x91F00970,
	0x91F97044, //hddsysext
	(0x91F97044 + 0x28) ,
	0x91F00A08,
	0x91F970C8, //intusbsysext
	(0x91F970C8 + 0x28) ,
	0x91F00A9C
};

//NOTE: Search for .com
XAMOffsets xam_14719 = {
	NULL, //siflc
	0x81623CAC, //piflc
	0x81623CC4, //notice
	0x81623CD8, //xexds
	0x81623CF0, //xetgs
	0x81623D08, //xeas
	0x81623D1C, //xemacs
};

XAMOffsets xam_15574 = {
	0x81622AC4, //siflc
	0x81622ADC, //piflc
	0x81622AF4, //notice
	0x81622B08, //xexds
	0x81622B20, //xetgs
	0x81622B38, //xeas
	0x81622B4C, //xemacs
};

XAMOffsets xam_16202 = {
	0x8161C604, //siflc
	0x8161C61C, //piflc
	0x8161C634, //notice
	0x8161C648, //xexds
	0x8161C660, //xetgs
	0x8161C678, //xeas
	0x8161C68C //xemacs
};

XAMOffsets xam_16537 = {
	0x8161D8A4, //siflc
	0x8161D8BC, //piflc
	0x8161D8D4, //notice
	0x8161D8E8, //xexds
	0x8161D900, //xetgs
	0x8161D918, //xeas
	0x8161D92C //xemacs
};

//.rdata:8161EB14 00000015 C SIFLC. % sXBOXLIVE.COM
//.rdata : 8161EB2C 00000015 C PIFLC. % sXBOXLIVE.COM
//.rdata : 8161EB44 00000012 C NOTICE. % sXBOX.COM
//.rdata : 8161EB58 00000015 C XEXDS. % sXBOXLIVE.COM
//.rdata : 8161EB70 00000015 C XETGS. % sXBOXLIVE.COM
//.rdata : 8161EB88 00000014 C XEAS. % sXBOXLIVE.COM
//.rdata : 8161EB9C 00000016 C XEMACS. % sXBOXLIVE.COM

XAMOffsets xam_17489 = {
	0x8161EB14, //siflc
	0x8161EB2C, //piflc
	0x8161EB44, //notice
	0x8161EB58, //xexds
	0x8161EB70, //xetgs
	0x8161EB88, //xeas
	0x8161EB9C, //xemacs
};

//_HandleError_CLogonErrorChainOfResponsibility in CSigninModel::SignInProfiles  -> 38600000 li r3, 0
SIGNINOffsets signin_14719 = {
	0x90114E68
};
SIGNINOffsets signin_15574 = {
	0x901153E8
};
SIGNINOffsets signin_16202 = {
	0x9011752C
};
SIGNINOffsets signin_16537 = {
	0x9011846C
};
SIGNINOffsets signin_17489 = {
	0x9011869C
};

/*Search for:
	lis       r11, ((aDash_xex+0x10000)@h) # "dash.xex"
	lis       r10, ((aSystemroot+0x10000)@h) # "\\SystemRoot"
*/
//patch all references

XSHELLOffsets xshell_14719 = {
	0x9203BBB4,
	0x9204A7CC,
	0x9204756C,
	0x92060A2C
};

XSHELLOffsets xshell_15574 = {
	0x9203DB1C,
	0x92049524,
	0x9204C76C,
	0x920644A4,
};

XSHELLOffsets xshell_16202 = {
	0x9203EBFC,
	0x9204A52C,
	0x9204D74C,
	0x92065454,
};

XSHELLOffsets xshell_16537 = {
	0x9203EBC4,
	0x9204A4FC,
	0x9204D71C,
	0x92065324,
};

XSHELLOffsets xshell_17489 = {
	0x9203EC14,
	0x9204A564,
	0x9204D734,
	0x92065454,
};

HUDOffsets hud_14719 = {
	0x913F1B58, //FamilySettings_LaunchStr looks like: lis       r11, aGuideSettingsF@h # "Guide/Settings/FamilySettings/"
	0x913E6E9C, //BootToDashHelper_Jump 
	0x14, //LaunchData_FAMILYSETTINGS
	0x913E6CD0, //HUD_BootToDashHelper_Func
	10152, //FamilySettings_Str1
	10157, //FamilySettings_Str2
};

HUDOffsets hud_15574 = {
	0x913F1BC0, //FamilySettings_LaunchStr
	0x913E6EF4, //BootToDashHelper_Jump 
	0x14, //LaunchData_FAMILYSETTINGS
	0x913E6D28, //HUD_BootToDashHelper_Func
	0x10033, //FamilySettings_Str1
	0x1035A, //FamilySettings_Str2
};

HUDOffsets hud_16202 = {
	0x913F0124, //FamilySettings_LaunchStr
	0x913E64E0, //BootToDashHelper_Jump 
	0x14, //LaunchData_FAMILYSETTINGS
	0x913E6318, //HUD_BootToDashHelper_Func
	0xFF12, //FamilySettings_Str1
	0x10239, //FamilySettings_Str2
};

HUDOffsets hud_16537 = {
	0x913F00A4, //FamilySettings_LaunchStr
	0x913E6340, //BootToDashHelper_Jump 
	0x14, //LaunchData_FAMILYSETTINGS
	0x913E6168, //HUD_BootToDashHelper_Func
	0x119C7, //FamilySettings_Str1
	0x11F11, //FamilySettings_Str2
};

//0x913F12D4
//0x913E7498
//0x913E72C0

HUDOffsets hud_17489 = {
  0x913F12D4, //FamilySettings_LaunchStr  
  0x913E7498, //BootToDashHelper_Jump 
  0x14, //LaunchData_FAMILYSETTINGS  
  0x913E72C0, //HUD_BootToDashHelper_Func 
  0x119B8, //FamilySettings_Str1 
  0x11F02, //FamilySettings_Str2
};

HUDOffsets hud_17559 = {
  0x913F035C, //FamilySettings_LaunchStr  
  0x913E64A0, //BootToDashHelper_Jump 
  0x14, //LaunchData_FAMILYSETTINGS  
  0x913E62C8, //HUD_BootToDashHelper_Func 
  0x119B8, //FamilySettings_Str1 
  0x11F02, //FamilySettings_Str2
};


const short kernels = 7;
const short kernelversions[kernels] = { 14719, 15574, 16197, 16202, 16537, 17489, 17559 };
XBDMOffsets* xbdmoffsets[kernels] = { &xbdm_14719_15574, &xbdm_14719_15574, &xbdm_16197_16202, &xbdm_16197_16202, &xbdm_16537, NULL, NULL };
XAMOffsets* xamoffsets[kernels] = { &xam_14719, &xam_15574, NULL, &xam_16202, &xam_16537, &xam_17489, &xam_17489 };
SIGNINOffsets* signinoffsets[kernels] = { &signin_14719, &signin_15574, NULL, &signin_16202, &signin_16537, &signin_17489, NULL };
XSHELLOffsets* xshelloffsets[kernels] = { &xshell_14719, &xshell_15574, NULL, &xshell_16202, &xshell_16537, &xshell_17489, &xshell_17489 };
HUDOffsets* hudoffsets[kernels] = { &hud_14719, &hud_15574, NULL, &hud_16202, &hud_16537, &hud_17489, &hud_17559 };

OffsetManager::OffsetManager()
{
	_kernel = getKernelVersion();
}

short OffsetManager::getKernelVersion()
{
	__asm
	{
		li r0, 0
		sc
		srwi r3, r3, 16
	}
}

XBDMOffsets* OffsetManager::getXbdmOffsets()
{
	for(int i = 0; i < kernels; i++)
	{
		if(kernelversions[i] == _kernel)
		{
			return xbdmoffsets[i];
		}
	}
	return NULL;
}

XAMOffsets* OffsetManager::getXamOffsets()
{
	for(int i = 0; i < kernels; i++)
	{
		if(kernelversions[i] == _kernel)
		{
			return xamoffsets[i];
		}
	}
	return NULL;
}

SIGNINOffsets* OffsetManager::getSigninOffsets()
{
	for(int i = 0; i < kernels; i++)
	{
		if(kernelversions[i] == _kernel)
		{
			return signinoffsets[i];
		}
	}
	return NULL;
}

XSHELLOffsets* OffsetManager::getXshellOffsets()
{
	for(int i = 0; i < kernels; i++)
	{
		if(kernelversions[i] == _kernel)
		{
			return xshelloffsets[i];
		}
	}
	return NULL;
}

HUDOffsets* OffsetManager::getHudOffsets()
{
	for(int i = 0; i < kernels; i++)
	{
		if(kernelversions[i] == _kernel)
		{
			return hudoffsets[i];
		}
	}
	return NULL;
}