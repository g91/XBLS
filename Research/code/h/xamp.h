

#ifndef __XAMP_H__
#define __XAMP_H__

typedef ULONG XMSG_HANDLE;

#include <windef.h>
#include <winbase.h>
#include <kernelp.h>
#include <KernelExports.h>
#include "xboxp.h"
#include "xdbg.h"
#include "xamdbg.h"

#include "winsockx.h"
#include "xonlinep.h"
#include "xex.h"
#include "xecrypt.h"
#include "xcabinet.h"
#include "contentpkg.h"
#include "xamcache.h"

//
// Define NTSTATUS if it's not already defined
//

#if !defined(_NTDEF_)
typedef LONG NTSTATUS;
#endif

//
// Force a reference to the kernel build number
//

#pragma comment(linker, "/include:XboxKrnlBuildNumber")

#pragma warning(push)
#pragma warning(disable: 4201)  // unnamed struct/union


#ifdef __cplusplus
extern "C" {
#endif

#define APPSZ_TESTXEX                           ("testxex.xex")
#define APPSZ_CERT                              ("cert.xex")
#define APPSZ_HUDUI                             ("hud.xex")

// App IDs
// Apps that load UI resource should have a unique id
// that helps XUI cache resources across dll loads
#define XAM_APP_ID_NONE             (~0u)
#define XAM_APP_ID_HUD              0
#define XAM_APP_ID_FRIENDS          1
#define XAM_APP_ID_DEVICESELECTOR   2
#define XAM_APP_ID_SIGNIN           3
#define XAM_APP_ID_TEMPAPP          4
#define XAM_APP_ID_TESTXEX          5
#define XAM_APP_ID_FEEDBACK         6
#define XAM_APP_ID_MARKETPLACE      7
#define XAM_APP_ID_MUSICPLAYER      8
#define XAM_APP_ID_VOICEMAIL        9
#define XAM_APP_ID_QUICKCHAT        10
#define XAM_APP_ID_VK               11
#define XAM_APP_ID_UPDATER          12
#define XAM_APP_ID_GAMEPROFILE      13
#define XAM_APP_ID_CREATEPROFILE    14
#define XAM_APP_ID_MINIMUSICPLAYER  15
#define XAM_APP_ID_CERT             16
#define HXAMAPP_TESTXEX                         ((HXAMAPP)0x000000F9)
#define HXAMAPP_CERT                            ((HXAMAPP)0x000000F8)

// Returns true if the xam app's xex image doesn't always have to be
// loaded in the xam.
#define XAMAPP_OPTIONAL(h)                      ( ((h) == HXAMAPP_TESTXEX) || ((h) == HXAMAPP_CERT) )

#define MSGAREA_TESTXEX                         (0x0006)
#define XM_SYS_STORAGEDEVICECHANGE              MSGID(MSGAREA_SYSTEM, 0x000F)
#define IsLiveBaseCustomProcessingMsg(msg)      (MSG_NUMBER(msg) & 0x8000)

//
// NOTE: these are duplicated in \private\inc\xonp.h for codegen
//

#define XM_LIVEBASE_LOGONCONNECT                MSGID(MSGAREA_XLIVEBASE, 0x8001)
#define XM_LIVEBASE_LOGONGETSERVICEINFO         MSGID(MSGAREA_XLIVEBASE, 0x8007)
#define XM_LIVEBASE_PRESENCEGETSEQNUM           MSGID(MSGAREA_XLIVEBASE, 0x8017)
#define XM_LIVEBASE_PRESENCESET                 MSGID(MSGAREA_XLIVEBASE, 0x8018)
#define XM_LIVEBASE_PRESENCEENUMCREATE          MSGID(MSGAREA_XLIVEBASE, 0x8019)
#define XM_LIVEBASE_PRESENCEENUM                MSGID(MSGAREA_XLIVEBASE, 0x801A)
#define XM_LIVEBASE_PRESENCEENUMCLOSE           MSGID(MSGAREA_XLIVEBASE, 0x801B)
#define XM_LIVEBASE_PRESENCEGETSTATE            MSGID(MSGAREA_XLIVEBASE, 0x801C)
#define XM_LIVEBASE_PRESENCESETSTATE            MSGID(MSGAREA_XLIVEBASE, 0x801D)
#define XM_LIVEBASE_PRESENCESUBSCRIBE           MSGID(MSGAREA_XLIVEBASE, 0x801E)
#define XM_LIVEBASE_PRESENCEUNSUBSCRIBE         MSGID(MSGAREA_XLIVEBASE, 0x801F)
#define XM_LIVEBASE_FRIENDSENUMCREATE           MSGID(MSGAREA_XLIVEBASE, 0x8020)
#define XM_LIVEBASE_FRIENDSENUM                 MSGID(MSGAREA_XLIVEBASE, 0x8021)
#define XM_LIVEBASE_FRIENDSENUMCLOSE            MSGID(MSGAREA_XLIVEBASE, 0x8022)
#define XM_LIVEBASE_INVITEGETINFO               MSGID(MSGAREA_XLIVEBASE, 0x8023)
#define XM_LIVEBASE_MSGENUMERATE                MSGID(MSGAREA_XLIVEBASE, 0x8024)
#define XM_LIVEBASE_MSGGETSUMMARY               MSGID(MSGAREA_XLIVEBASE, 0x8025)
#define XM_LIVEBASE_MSGCREATE                   MSGID(MSGAREA_XLIVEBASE, 0x8026)
#define XM_LIVEBASE_MSGDESTROY                  MSGID(MSGAREA_XLIVEBASE, 0x8027)
#define XM_LIVEBASE_MSGSETPROP                  MSGID(MSGAREA_XLIVEBASE, 0x8028)
#define XM_LIVEBASE_MSGGETPROP                  MSGID(MSGAREA_XLIVEBASE, 0x8029)
#define XM_LIVEBASE_MSGGETDETAILS               MSGID(MSGAREA_XLIVEBASE, 0x802A)
#define XM_LIVEBASE_MSGGETDETAILSSUMMARY        MSGID(MSGAREA_XLIVEBASE, 0x802B)
#define XM_LIVEBASE_MSGGETDETAILSPROPERTY       MSGID(MSGAREA_XLIVEBASE, 0x802C)
#define XM_LIVEBASE_MSGSETFLAGS                 MSGID(MSGAREA_XLIVEBASE, 0x802D)
#define XM_LIVEBASE_MSGDELETE                   MSGID(MSGAREA_XLIVEBASE, 0x802E)
#define XM_LIVEBASE_MSGINVITESEND               MSGID(MSGAREA_XLIVEBASE, 0x802F)
#define XM_LIVEBASE_MSGINVITEANSWER             MSGID(MSGAREA_XLIVEBASE, 0x8030)
#define XM_LIVEBASE_MSGINVITEREVOKE             MSGID(MSGAREA_XLIVEBASE, 0x8031)
#define XM_LIVEBASE_GETTASKPROGRESS             MSGID(MSGAREA_XLIVEBASE, 0x8032)
#define XM_LIVEBASE_GETREQUESTTHROTTLE          MSGID(MSGAREA_XLIVEBASE, 0x8033)
#define XM_LIVEBASE_SETREQUESTTHROTTLE          MSGID(MSGAREA_XLIVEBASE, 0x8034)
#define XM_LIVEBASE_STORAGEBUILDSERVERPATH      MSGID(MSGAREA_XLIVEBASE, 0x8035)
#define XM_LIVEBASE_EXPIREMARKETPLACECOUNTSCACHE MSGID(MSGAREA_XLIVEBASE, 0x8036)
#define XM_LIVEBASE_PRESENCEINITIALIZE          MSGID(MSGAREA_XLIVEBASE, 0x8037)
#define XM_LIVEBASE_CONTENTGETINPROGRESSMETADATA MSGID(MSGAREA_XLIVEBASE, 0x8038)
#define XM_BASE_DEVICEFORMAT                    MSGID(MSGAREA_XBASE, 0x000B)
#define XM_BASE_CONTENTCOPYMOVE                 MSGID(MSGAREA_XBASE, 0x000C)
#define XM_BASE_DEVICERENAME                    MSGID(MSGAREA_XBASE, 0x000D)
#define XM_BASE_CONTENTAGGREGATEENUMERATE       MSGID(MSGAREA_XBASE, 0x000E)
#define XM_BASE_CONTENAGGREGATETCREATEENUM      MSGID(MSGAREA_XBASE, 0x000F)
#define XM_BASE_CONTENTAGGREGATECLOSEENUM       MSGID(MSGAREA_XBASE, 0x0010)
#define XM_BASE_CONTENTGETMETADATA              MSGID(MSGAREA_XBASE, 0x0011)
#define XM_BASE_CONTENTSETTHUMBNAIL             MSGID(MSGAREA_XBASE, 0x0012)
#define XM_BASE_CONTENTGETTHUMBNAIL             MSGID(MSGAREA_XBASE, 0x0013)
#define XM_BASE_CONTENTGETCREATOR               MSGID(MSGAREA_XBASE, 0x0014)
#define XM_BASE_DEVICEGETSTATE                  MSGID(MSGAREA_XBASE, 0x0015)
#define XM_BASE_CONTENTRESOLVE                  MSGID(MSGAREA_XBASE, 0x0016)
#define XM_BASE_CONTENTGETLICENSEMASK           MSGID(MSGAREA_XBASE, 0x0017)
#define XM_BASE_CONTENTFLUSH                    MSGID(MSGAREA_XBASE, 0x0018)
#define XM_BASE_CONTENTINSTALL                  MSGID(MSGAREA_XBASE, 0x0019)
#define XM_BASE_CONTENTGETATTRIBUTES            MSGID(MSGAREA_XBASE, 0x001A)
#define XM_BASE_PROFILEENUMERATE                MSGID(MSGAREA_XBASE, 0x3001)
#define XM_BASE_PROFILECREATEENUM               MSGID(MSGAREA_XBASE, 0x3002)
#define XM_BASE_PROFILECLOSEENUM                MSGID(MSGAREA_XBASE, 0x3003)
#define XM_BASE_PROFILELOAD                     MSGID(MSGAREA_XBASE, 0x3004)
#define XM_BASE_PROFILESAVE                     MSGID(MSGAREA_XBASE, 0x3005)
#define XM_BASE_PROFILEDELETE                   MSGID(MSGAREA_XBASE, 0x3006)
#define XM_BASE_PROFILERENAME                   MSGID(MSGAREA_XBASE, 0x3007)

//
// TestXEX Messages
//

#define XM_TEST_PRESENDMESSAGE                  MSGID(MSGAREA_TESTXEX, 0x0001)
#define XM_TEST_POSTSENDMESSAGE                 MSGID(MSGAREA_TESTXEX, 0x0002)
#define XM_TEST_SENDASYNCMESSAGE                MSGID(MSGAREA_TESTXEX, 0x0003)
#define XM_TEST_SENDNOTIFICATION                MSGID(MSGAREA_TESTXEX, 0x0004)
#define XM_TEST_ASYNCMESSAGEINUSE               MSGID(MSGAREA_TESTXEX, 0x0005)
#define XM_TEST_SETMEDIACODE                    MSGID(MSGAREA_TESTXEX, 0x0006)
#define XM_TEST_ENABLEUITIMING                  MSGID(MSGAREA_TESTXEX, 0x0007)
#define XM_TEST_DUMPUITIMING                    MSGID(MSGAREA_TESTXEX, 0x0008)
#define XM_TEST_UIAPPLOAD                       MSGID(MSGAREA_TESTXEX, 0x0009)

#define XM_TEST_ENABLEAUTOMATION                MSGID(MSGAREA_TESTXEX, 0x0011)
#define XM_TEST_DISABLEAUTOMATION               MSGID(MSGAREA_TESTXEX, 0x0012)
#define XM_TEST_STARTSCRIPTENGINE               MSGID(MSGAREA_TESTXEX, 0x0013)
#define XM_TEST_STOPSCRIPTENGINE                MSGID(MSGAREA_TESTXEX, 0x0014)
#define XM_TEST_RUNSCRIPT                       MSGID(MSGAREA_TESTXEX, 0x0015)
#define XM_TEST_SETTITLESTARTUPSCRIPT           MSGID(MSGAREA_TESTXEX, 0x0016)
#define XM_TEST_SETDLLENGINEPATH                MSGID(MSGAREA_TESTXEX, 0x0017)
#define XM_TEST_UPDATETESTCOMMAND               MSGID(MSGAREA_TESTXEX, 0x0018)

#define XM_TEST_STARTMESSAGESPOOF               MSGID(MSGAREA_TESTXEX, 0x0021)
#define XM_TEST_STOPMESSAGESPOOF                MSGID(MSGAREA_TESTXEX, 0x0022)
#define XM_TEST_STARTASYNCMESSAGESPOOF          MSGID(MSGAREA_TESTXEX, 0x0023)
#define XM_TEST_STOPASYNCMESSAGESPOOF           MSGID(MSGAREA_TESTXEX, 0x0024)

#define XM_TEST_STARTMESSAGETIMER               MSGID(MSGAREA_TESTXEX, 0x0031)
#define XM_TEST_STOPMESSAGETIMER                MSGID(MSGAREA_TESTXEX, 0x0032)
#define XM_TEST_STARTMESSAGELOG                 MSGID(MSGAREA_TESTXEX, 0x0033)
#define XM_TEST_STOPMESSAGELOG                  MSGID(MSGAREA_TESTXEX, 0x0034)

#define XM_TEST_OCCLUSIONQUERYBEGIN             MSGID(MSGAREA_TESTXEX, 0x0040)
#define XM_TEST_OCCLUSIONQUERYEND               MSGID(MSGAREA_TESTXEX, 0x0041)
#define XM_TEST_OCCLUSIONQUERYGETDATA           MSGID(MSGAREA_TESTXEX, 0x0042)

#define XM_TEST_CHANGEXEXINFO                   MSGID(MSGAREA_TESTXEX, 0x0051)
#define XM_TEST_DELETESPAFILE                   MSGID(MSGAREA_TESTXEX, 0x0052)
#define XM_TEST_RESETFILECACHE                  MSGID(MSGAREA_TESTXEX, 0x0053)

#define TEST_SPA_FILENAME_SIZE 64

typedef struct
{
    DWORD                                       dwTitleID;
    CHAR                                        szSpaFilename[TEST_SPA_FILENAME_SIZE];
} TEST_CHANGEXEXINFO_MSG, *PTEST_CHANGEXEXINFO_MSG;


//
// XGI
//

#define XM_XGI_RECOVERTITLE                     MSGID(MSGAREA_XGI, 0x0003)
#define XM_XGI_SYNC                             MSGID(MSGAREA_XGI, 0x0004)
#define XM_XGI_CONTENTOPENED                    MSGID(MSGAREA_XGI, 0x0005)
#define XM_XGI_USERSETCONTEXT                   MSGID(MSGAREA_XGI, 0x0006)
#define XM_XGI_USERSETPROPERTY                  MSGID(MSGAREA_XGI, 0x0007)

#define XM_XGI_WRITEACHIEVEMENT                 MSGID(MSGAREA_XGI, 0x0008)
#define XM_XGI_CREATEENUM                       MSGID(MSGAREA_XGI, 0x0009)
#define XM_XGI_ACHIEVEMENTENUMERATE             MSGID(MSGAREA_XGI, 0x000A)
#define XM_XGI_CLOSEENUM                        MSGID(MSGAREA_XGI, 0x000B)
#define XM_XGI_READSETTINGS                     MSGID(MSGAREA_XGI, 0x000C)
#define XM_XGI_WRITESETTINGS                    MSGID(MSGAREA_XGI, 0x000D)

#define XM_XGI_SESSIONCREATE                    MSGID(MSGAREA_XGI, 0x0010)
#define XM_XGI_SESSIONDELETE                    MSGID(MSGAREA_XGI, 0x0011)
#define XM_XGI_SESSIONJOIN                      MSGID(MSGAREA_XGI, 0x0012)
#define XM_XGI_SESSIONLEAVE                     MSGID(MSGAREA_XGI, 0x0013)
#define XM_XGI_SESSIONSTART                     MSGID(MSGAREA_XGI, 0x0014)
#define XM_XGI_SESSIONEND                       MSGID(MSGAREA_XGI, 0x0015)
#define XM_XGI_SESSIONSEARCH                    MSGID(MSGAREA_XGI, 0x0016)
#define XM_XGI_SESSIONCONFIG                    MSGID(MSGAREA_XGI, 0x0017)
#define XM_XGI_SESSIONMODIFY                    MSGID(MSGAREA_XGI, 0x0018)
#define XM_XGI_SESSIONINVITE                    MSGID(MSGAREA_XGI, 0x0019)
#define XM_XGI_SESSIONARBITRATE                 MSGID(MSGAREA_XGI, 0x001A)
#define XM_XGI_SESSIONSEARCHBYID                MSGID(MSGAREA_XGI, 0x001B)
#define XM_XGI_SESSIONSEARCHEX                  MSGID(MSGAREA_XGI, 0x001C)

#define XM_XGI_VIEWRESET                        MSGID(MSGAREA_XGI, 0x0020)
#define XM_XGI_STATSREAD                        MSGID(MSGAREA_XGI, 0x0021)
#define XM_XGI_STATSENUMCREATE                  MSGID(MSGAREA_XGI, 0x0022)
#define XM_XGI_STATSENUMERATE                   MSGID(MSGAREA_XGI, 0x0023)
#define XM_XGI_STATSCLOSEENUM                   MSGID(MSGAREA_XGI, 0x0024)
#define XM_XGI_STATSWRITE                       MSGID(MSGAREA_XGI, 0x0025)
#define XM_XGI_STATSFLUSH                       MSGID(MSGAREA_XGI, 0x0026)

#define XM_XGI_READTILE                         MSGID(MSGAREA_XGI, 0x0030)
#define XM_XGI_WRITETILE                        MSGID(MSGAREA_XGI, 0x0031)
#define XM_XGI_READTILETOTEXTURE                MSGID(MSGAREA_XGI, 0x0032)
#define XM_XGI_WRITEGAMERTILE                   MSGID(MSGAREA_XGI, 0x0033)
#define XM_XGI_PREPAREGAMERTILES                MSGID(MSGAREA_XGI, 0x0034)
#define XM_XGI_INITFLASHTILES                   MSGID(MSGAREA_XGI, 0x0035)
#define XM_XGI_INVALIDATEGAMERTILECACHE         MSGID(MSGAREA_XGI, 0x0036)

#define XM_XGI_READSTRING                       MSGID(MSGAREA_XGI, 0x0038)

#define XM_XGI_TITLEENUMERATE                   MSGID(MSGAREA_XGI, 0x0050)
#define XM_XMP_PLAYUSERCONTENT                      MSGID(MSGAREA_XMP, 0x0001)
#define XM_XMP_PLAYTITLEPLAYLIST                    MSGID(MSGAREA_XMP, 0x0002)
#define XM_XMP_CONTINUE                             MSGID(MSGAREA_XMP, 0x0003)
#define XM_XMP_STOP                                 MSGID(MSGAREA_XMP, 0x0004)
#define XM_XMP_PAUSE                                MSGID(MSGAREA_XMP, 0x0005)
#define XM_XMP_NEXT                                 MSGID(MSGAREA_XMP, 0x0006)
#define XM_XMP_PREVIOUS                             MSGID(MSGAREA_XMP, 0x0007)
#define XM_XMP_SETPLAYBACKBEHAVIOR                  MSGID(MSGAREA_XMP, 0x0008)
#define XM_XMP_GETSTATUS                            MSGID(MSGAREA_XMP, 0x0009)
#define XM_XMP_MOVESONG                             MSGID(MSGAREA_XMP, 0x000A)
#define XM_XMP_GETVOLUME                            MSGID(MSGAREA_XMP, 0x000B)
#define XM_XMP_SETVOLUME                            MSGID(MSGAREA_XMP, 0x000C)
#define XM_XMP_CREATETITLEPLAYLIST                  MSGID(MSGAREA_XMP, 0x000D)
#define XM_XMP_GETNOWPLAYING                        MSGID(MSGAREA_XMP, 0x000E)
#define XM_XMP_ADDSONGS                             MSGID(MSGAREA_XMP, 0x0011)
#define XM_XMP_REMOVESONGS                          MSGID(MSGAREA_XMP, 0x0012)
#define XM_XMP_DELETETITLEPLAYLIST                  MSGID(MSGAREA_XMP, 0x0013)
#define XM_XMP_CREATESONGENUMERATOR                 MSGID(MSGAREA_XMP, 0x0014)
#define XM_XMP_ENUMERATESONG                        MSGID(MSGAREA_XMP, 0x0015)
#define XM_XMP_CLOSESONGENUMERATOR                  MSGID(MSGAREA_XMP, 0x0016)
#define XM_XMP_CREATETITLEPLAYLISTENUMERATOR        MSGID(MSGAREA_XMP, 0x0017)
#define XM_XMP_ENUMERATETITLEPLAYLIST               MSGID(MSGAREA_XMP, 0x0018)
#define XM_XMP_CLOSETITLEPLAYLISTENUMERATOR         MSGID(MSGAREA_XMP, 0x0019)
#define XM_XMP_SETPLAYBACKCONTROLLER                MSGID(MSGAREA_XMP, 0x001A)
#define XM_XMP_GETPLAYBACKCONTROLLER                MSGID(MSGAREA_XMP, 0x001B)
#define XM_XMP_CREATEMEDIACONTAINERENUMERATOR       MSGID(MSGAREA_XMP, 0x001C)
#define XM_XMP_ENUMERATEMEDIACONTAINER              MSGID(MSGAREA_XMP, 0x001D)
#define XM_XMP_CLOSEMEDIACONTAINERENUMERATOR        MSGID(MSGAREA_XMP, 0x001E)
#define XM_XMP_CREATEPHOTOENUMERATOR                MSGID(MSGAREA_XMP, 0x001F)
#define XM_XMP_ENUMERATEPHOTO                       MSGID(MSGAREA_XMP, 0x0020)
#define XM_XMP_CLOSEPHOTOENUMERATOR                 MSGID(MSGAREA_XMP, 0x0021)
#define XM_XMP_CREATEVIDEOENUMERATOR                MSGID(MSGAREA_XMP, 0x0022)
#define XM_XMP_ENUMERATEVIDEO                       MSGID(MSGAREA_XMP, 0x0023)
#define XM_XMP_CLOSEVIDEOENUMERATOR                 MSGID(MSGAREA_XMP, 0x0024)
#define XM_XMP_CREATEUSERPLAYLISTENUMERATOR         MSGID(MSGAREA_XMP, 0x0025)
#define XM_XMP_ENUMERATEUSERPLAYLIST                MSGID(MSGAREA_XMP, 0x0026)
#define XM_XMP_CLOSEUSERPLAYLISTENUMERATOR          MSGID(MSGAREA_XMP, 0x0027)
#define XM_XMP_EMPTYPLAYLIST                        MSGID(MSGAREA_XMP, 0x0028)
#define XM_XMP_GETPLAYBACKBEHAVIOR                  MSGID(MSGAREA_XMP, 0x0029)
#define XM_XMP_GETTOTALNUMBEROFITEMS                MSGID(MSGAREA_XMP, 0x002A)
#define XM_XMP_GETMEDIASOURCES                      MSGID(MSGAREA_XMP, 0x002B)
#define XM_XMP_GETMEDIASTREAM                       MSGID(MSGAREA_XMP, 0x002C)
#define XM_XMP_GETPHOTOTHUMBNAILSTREAM              MSGID(MSGAREA_XMP, 0x002D)
#define XM_XMP_GETTITLEPLAYLISTBUFFERSIZE           MSGID(MSGAREA_XMP, 0x002E)
#define XM_XMP_DASHINIT                             MSGID(MSGAREA_XMP, 0x002F)
#define XM_XMP_GETTITLEINFO                         MSGID(MSGAREA_XMP, 0x0030)
#define XM_XMP_GETNUMSONGSINTITLEPLAYLIST           MSGID(MSGAREA_XMP, 0x0031)
#define XM_XMP_IMPORTALBUM                          MSGID(MSGAREA_XMP, 0x0032)
#define XM_XMP_GETBEATEFFECTOUTPUT                  MSGID(MSGAREA_XMP, 0x0033)
#define XM_XMP_EDITALBUM                            MSGID(MSGAREA_XMP, 0x0034)
#define XM_XMP_EDITTRACK                            MSGID(MSGAREA_XMP, 0x0035)
#define XM_XMP_DELETEMEDIA                          MSGID(MSGAREA_XMP, 0x0036)
#define XM_XMP_DELETECONTAINER                      MSGID(MSGAREA_XMP, 0x0037)
#define XM_XMP_GETMEDIASOURCEINFO                   MSGID(MSGAREA_XMP, 0x0038)
#define XM_XMP_COMMITPLAYLIST                       MSGID(MSGAREA_XMP, 0x0039)
#define XM_XMP_CHANGEWMCSERVER                      MSGID(MSGAREA_XMP, 0x003A)
#define XM_XMP_PLAYMEDIACONTAINER                   MSGID(MSGAREA_XMP, 0x003B)
#define XM_XMP_RENAMECONTAINER                      MSGID(MSGAREA_XMP, 0x003C)
#define XM_XMP_CAPTUREOUTPUT                        MSGID(MSGAREA_XMP, 0x003D)
#define XM_XMP_CREATEMEDIAOBJECTENUMERATOR          MSGID(MSGAREA_XMP, 0x003E)
#define XM_XMP_ENUMERATEMEDIAOBJECT                 MSGID(MSGAREA_XMP, 0x003F)
#define XM_XMP_CLOSEMEDIAOBJECTENUMERATOR           MSGID(MSGAREA_XMP, 0x0040)
#define XM_XMP_CREATETITLEPLAYLISTSONGENUMERATOR    MSGID(MSGAREA_XMP, 0x0041)
#define XM_XMP_ENUMERATETITLEPLAYLISTSONG           MSGID(MSGAREA_XMP, 0x0042)
#define XM_XMP_CLOSETITLEPLAYLISTSONGENUMERATOR     MSGID(MSGAREA_XMP, 0x0043)
#define XM_XMP_SETMEDIASOURCEWORKSPACE              MSGID(MSGAREA_XMP, 0x0044)
#define XM_XMP_GETNUMTITLEPLAYLISTS                 MSGID(MSGAREA_XMP, 0x0045)
#define XM_XMP_GETMEDIASOURCE                       MSGID(MSGAREA_XMP, 0x0046)
#define XM_XMP_DELETEALLLOCALMUSIC                  MSGID(MSGAREA_XMP, 0x0047)
#define XM_XMP_REMOVESONGSWITHSOURCE                MSGID(MSGAREA_XMP, 0x0048)
#define XM_XMP_RESTARTPLAYBACK                      MSGID(MSGAREA_XMP, 0x0049)
#define XM_XMP_SETDASHNOWPLAYINGQUEUEMODE           MSGID(MSGAREA_XMP, 0x004A)
#define XM_XMP_GETDASHNOWPLAYINGQUEUEMODE           MSGID(MSGAREA_XMP, 0x004B)
#define XM_XMP_ENTERCDRIPPINGMODE                   MSGID(MSGAREA_XMP, 0x004C)
#define XM_XMP_LEAVECDRIPPINGMODE                   MSGID(MSGAREA_XMP, 0x004D)

//
// UVBase Messages
//

#define XM_UVBASE_REQUESTVOICECHAT              MSGID(MSGAREA_UVBASE, 0x0001)
#define XM_UVBASE_QUITVOICECHAT                 MSGID(MSGAREA_UVBASE, 0x0002)
#define XM_UVBASE_ENUMERATEVOICECHATS           MSGID(MSGAREA_UVBASE, 0x0003)
#define XM_UVBASE_SWITCHTOVOICECHAT             MSGID(MSGAREA_UVBASE, 0x0004)
#define XM_UVBASE_CONNECTTOVOICECHAT            MSGID(MSGAREA_UVBASE, 0x0005)
#define XM_UVBASE_CALLBACKUSERTOVOICECHAT       MSGID(MSGAREA_UVBASE, 0x0006)
#define XM_UVBASE_CREATEVOICEMAIL               MSGID(MSGAREA_UVBASE, 0x0007)
#define XM_UVBASE_RECORDVOICEMAIL               MSGID(MSGAREA_UVBASE, 0x0008)
#define XM_UVBASE_PLAYVOICEMAIL                 MSGID(MSGAREA_UVBASE, 0x0009)
#define XM_UVBASE_STOPVOICEMAIL                 MSGID(MSGAREA_UVBASE, 0x000A)
#define XM_UVBASE_CLOSEVOICEMAIL                MSGID(MSGAREA_UVBASE, 0x000B)
#define XM_UVBASE_ENUMERATECHANNELS             MSGID(MSGAREA_UVBASE, 0x000C)
//
// We reverse the RSHOULDER and LSHOULDER constants to be consistent with old
// Xbox1 input that had the order BLACK then WHITE.
//
#define VK_PAD_XE                       0x5808
#define VK_PAD_BINDING                  0x5809
//
// Combination codes reserved by XUI input processing.
// Do not define conflicting public values.
//
// #define VK_PAD_A_OR_START            0x5840
// #define VK_PAD_B_OR_BACK             0x5841
// #define VK_NONE                      0x5842
// ...
// Reserved through                     0x584F
//

//------------------------------------------------------------------------------
// Debug instrumentation
//

XBOXAPI
VOID
WINAPI
XamDbgSetOutputLevel(
    IN      HXAMAPP                     hxamapp             OPTIONAL,
    IN      ULONG                       ulLevel
    );

XBOXAPI
VOID
WINAPI
XamDbgSetBreakLevel(
    IN      HXAMAPP                     hxamapp             OPTIONAL,
    IN      ULONG                       ulLevel
    );

XBOXAPI
BOOL
WINAPI
XamDbgPrint(
    IN      ULONG                       ulLevel,
    IN      LPCSTR                      pszFormat,
    ...
    );
typedef struct _TESTXEXMESSAGE
{
    HXAMAPP                             hxamapp;
    DWORD                               dwMessage;
    UINT_PTR                            pParam1;
    UINT_PTR                            pParam2;
    HRESULT                             hr;
} TESTXEXMESSAGE, *PTESTXEXMESSAGE;

typedef struct _TESTXEXXUILOCK
{
    BOOL                                fWait;
    DWORD                               dwTime;
} TESTXEXXUILOCK, *PTESTXEXXUILOCK;

typedef struct _TESTXEXSYSINFO
{
    DWORD                               dwBuildVer;
    DWORD                               dwBuildFlags;
    DWORD                               dwHardwareVer;
} TESTXEXSYSINFO, *PTESTXEXSYSINFO;

BOOL
WINAPI
XamSetAutomation(
    IN      BOOL                        fAutomation
    );

#ifndef XUIElementPropVal
typedef struct XUIElementPropVal        XUIElementPropVal;
#endif

HRESULT
WINAPI
XamApplySkin(
    IN      DWORD                       dwUserIndex,
    IN      LPCSTR                      pszSkinModule,      OPTIONAL
    IN      CONST XUIElementPropVal*    pPropBkgnd          OPTIONAL
    );

HRESULT
WINAPI
XamGetBkgndDefault(
    OUT     XUIElementPropVal*          pPropBkgnd
    );

HRESULT
WINAPI
XamGetDefaultSystemImage(
    OUT     PBYTE*                      ppbImage,
    OUT     PDWORD                      pcbImage            OPTIONAL
    );

typedef enum
{
    XAM_DEFAULT_IMAGE_SYSTEM        = 0,
    XAM_DEFAULT_IMAGE_DASHICON      = 1,

    XAM_DEFAULT_IMAGE_ID_COUNT      = 2
} XAM_DEFAULT_IMAGE_ID;

HRESULT
WINAPI
XamGetDefaultImage(
    IN      XAM_DEFAULT_IMAGE_ID        dwImageId,
    OUT     PBYTE*                      ppbImage,
    OUT     PDWORD                      pcbImage            OPTIONAL
    );

#ifndef HXUIBRUSH
typedef struct _XUIBRUSH*               HXUIBRUSH;
#endif

VOID
XamSendMessageToLoadedApps(
    IN      DWORD                       dwMessage,
    IN      UINT_PTR                    pParam1,
    IN      UINT_PTR                    pParam2
    );

DWORD
WINAPI
XamFormatMessage(
    OUT     LPWSTR                      pszOut,
    IN      DWORD                       cchOut,
    IN      LPCWSTR                     pszTemplate,
    ...
    );

typedef enum
{
    XAMDATEFORMAT_dMyyyy = 0,
    XAMDATEFORMAT_dMMyyyy,
    XAMDATEFORMAT_ddMMyyyy,
    XAMDATEFORMAT_Mdyyyy,
    XAMDATEFORMAT_yyyyMd,
    XAMDATEFORMAT_yyyyMMdd,
    XAMDATEFORMAT_MMyy,
} XAMDATEFORMAT;

XAMDATEFORMAT XamGetLocaleDateFormat(
    IN      DWORD                       dwCountry
    );

VOID
WINAPI
XamFormatTimeString(
    IN      DWORD                       dwUserIndex,
    IN      FILETIME                    ft,
    OUT     LPWSTR                      pszBuff,
    IN      ULONG                       cchBuff
    );

VOID
WINAPI
XamFormatDateString(
    IN      DWORD                       dwUserIndex,
    IN      FILETIME                    ft,
    OUT     LPWSTR                      pszBuff,
    IN      ULONG                       cchBuff
    );

INT
WINAPI
XamUniSortCmpString(
    LPCWSTR pszString1,
    LPCWSTR pszString2,
    UINT nMaxLen
    );

#ifndef HXUIOBJ
typedef struct _XUIOBJ*                 HXUIOBJ;
#endif

HRESULT
WINAPI
XamGetRootObj(
    OUT     HXUIOBJ*                    phRootObj
    );

typedef enum
{
    XHUDOPENSTATE_NONE                  = 0,
    XHUDOPENSTATE_HALF,
    XHUDOPENSTATE_FULL,
    XHUDOPENSTATE_ERROR,
    //-----------------
    XHUDOPENSTATE_COUNT
} XHUDOPENSTATE, *PXHUDOPENSTATE;

typedef VOID (CALLBACK *PFNMSGBOXRETURN)(
    IN      INT                         iButtonPressed,
    OUT     PXHUDOPENSTATE              pHudRestoreState
    );

HRESULT
WINAPI
XamShowMessageBox(
    IN OPTIONAL HXUIOBJ                 hOwner,             //  HXUIOBJ to be notified on Completion. (optional)
    IN          LPCWSTR                 pszTitle,           //  Title text.
    IN          LPCWSTR                 pszText,            //  Message text.
    IN          DWORD                   cButtons,           //  Count of buttons in rgButtons.
    IN          LPCWSTR*                rgButtons,          //  Array of text strings for buttons.
    IN          DWORD                   dwFocusButton,      //  Set focus to a button with this index,
    IN OPTIONAL PFNMSGBOXRETURN         pfnMsgBoxReturn,    //  Callback function called on Completion. (optional)
    IN          DWORD                   dwFlags             //  Flags
    );

#define MAX_RESOURCE_PATH               128

HRESULT
WINAPI
XamBuildResourceLocator(
    IN OPTIONAL HINSTANCE               hInstance,          //  HINSTANCE of the module from which to load resources.
    IN          LPCWSTR                 pszContainer,       //  Resource container name (i.e. section name or package name)
    IN OPTIONAL LPCWSTR                 pszResource,        //  Resource name
    OUT         LPWSTR                  pszResourceLocator, //  Sting buffer to recieve the locator string.
    IN          DWORD                   cchResourceLocator  //  Count of characters in pszResourceLocator.
    );


HRESULT
WINAPI
XamBuildSharedSystemResourceLocator(
    IN          LPCWSTR                 pszResource,        //  Resource name
    OUT         LPWSTR                  pszResourceLocator, //  Sting buffer to recieve the locator string.
    IN          DWORD                   cchResourceLocator  //  Count of characters in pszResourceLocator.
    );

HRESULT
WINAPI
XamBuildGamercardResourceLocator(
    IN          LPCWSTR                 pszResource,        //  Resource name
    OUT         LPWSTR                  pszResourceLocator, //  Sting buffer to recieve the locator string.
    IN          DWORD                   cchResourceLocator  //  Count of characters in pszResourceLocator.
    );

HRESULT
WINAPI
XamBuildDynamicResourceLocator(
    IN          DWORD                   dwAppId,            // Unique application id
    IN OPTIONAL HINSTANCE               hInstance,          //  HINSTANCE of the module from which to load resources.
    IN          LPCWSTR                 pszContainer,       //  Resource container name (i.e. section name or package name)
    IN OPTIONAL LPCWSTR                 pszResource,        //  Resource name
    OUT         LPWSTR                  pszResourceLocator, //  Sting buffer to recieve the locator string.
    IN          DWORD                   cchResourceLocator  //  Count of characters in pszResourceLocator.
    );

DWORD
WINAPI
XamCustomSetBannerImage(
    IN  const VOID *                    pvTexture,
    IN  const VOID *                    pvBits,
    IN  DWORD                           dwFlags
    );

BOOL
WINAPI
XAutomationpBindController(
    IN      DWORD                       dwUserIndex
    );

BOOL
WINAPI
XAutomationpUnbindController(
    IN      DWORD                       dwUserIndex
    );

BOOL
WINAPI
XAutomationpInputXenonButton(
    IN      DWORD                       dwUserIndex
    );

BOOL
WINAPI
XAutomationpInputSetState(
    IN      DWORD                       dwUserIndex,
    IN      PXINPUT_GAMEPAD             pXGamepad
    );

BOOL
WINAPI
XAutomationpInputPress(
    IN      DWORD                       dwUserIndex,
    IN      DWORD                       dwVkey
    );

BOOL
WINAPI
XamEnableOverdraw(
    IN      BOOL                        fEnable
    );

#define XAMINLINE                       FORCEINLINE

//
// Crt initialization for system apps
//
BOOL WINAPI _CrtInit();
VOID WINAPI _CrtTerm();
BOOL WINAPI _CrtThreadInit();
VOID WINAPI _CrtThreadTerm();

//
// XamApp SPIs
//

DWORD
WINAPI
XamNavigate(
    IN      DWORD                       dwUserIndex,
    IN      LPCSTR                      pszShortcut,
    IN      ULONGLONG                   qwParam1,
    IN      DWORD                       dwParam2
    );

BOOL
WINAPI
XamAppRequestLoad(
    VOID
    );

BOOL
WINAPI
XamAppRequestLoadEx(
    XHUDOPENSTATE OpenState
    );

VOID
WINAPI
XamAppUnrequestLoad(
    VOID
    );


HRESULT
WINAPI
XamAppUnloadStack(
    IN      BOOL                        fWaitForCompletion          // specified whether the call should block until the app stack is fully unloaded
    );


HRESULT
WINAPI
XamAppLoad(
    IN      LPCSTR                      pszSysApp,
    IN      DWORD                       dwUserIndex,                // user index from which the app will accept input.
    IN      PVOID                       pvAppParams     OPTIONAL,   // params that will be passed to the app as the first param of XM_SET_PARAMS
    IN      DWORD                       cbAppParams     OPTIONAL,   // size of data pointed to by pvAppParams
    IN      PXOVERLAPPED                pxoverlapped    OPTIONAL,   // xoverlapped struct to signal when the operation is completed
    OUT     PHXAMAPP                    phxamapp        OPTIONAL
    );

void
WINAPI
XamAppUnloadSelf();

#define XSYSLOADINPUT_NONE              0x00000000
#define XSYSLOADINPUT_FIRSTLOAD         0x00000001
#define XSYSLOADINPUT_RELOAD            0x00000002

typedef struct _XSYSLOADINPUT
{
    DWORD                               dwFlags;        // See XSYSLOADINPUT_*
    PVOID                               pvParam;
    HINSTANCE                           hInstance;
    DWORD                               dwUserIndex;
} XSYSLOADINPUT, *PXSYSLOADINPUT;

typedef struct _XSYSLOADOUTPUT
{
    DWORD                               cbPersist;
} XSYSLOADOUTPUT;

//
// XM_SYS_STORAGEDEVICECHANGE
//

typedef enum
{
    DEVICESTATE_NONE                = 0,
    DEVICESTATE_ADD,
    DEVICESTATE_REMOVE,
    DEVICESTATE_IDLE,
    DEVICESTATE_UNFORMATTED,
    DEVICESTATE_IGNORE,
    DEVICESTATE_FORCE_DWORD         = 0xFFFFFFFF
} DEVICESTATE;

typedef struct XSTORAGEDEVICECHANGE_PARAMS
{
    CHAR                                szDevicePath[MAX_PATH];
    BOOL                                fRemoved;
    DWORD                               deviceType;
    DWORD                               deviceId;
    DEVICESTATE                         eState;
} XSTORAGEDEVICECHANGE_PARAMS, *PXSTORAGEDEVICECHANGE_PARAMS;


DWORD
WINAPI
XamRegisterSysApp(
    IN      HINSTANCE                   hInstance,
    IN      HXAMAPP                     hXamApp,
    IN      PMESSAGEPROC                pfnMessageProc,
    IN      DWORD                       dwAppId
    );


DWORD
WINAPI
XamUnregisterSysApp(
    IN      HINSTANCE                   hInstance,
    IN      HXAMAPP                     hXamApp,
    IN      DWORD                       dwAppId
    );



typedef enum
{
    XCODEC_TYPE_AAC                  = 0,
    //-----------------
    XCODEC_TYPE_COUNT
} XCODEC_TYPE, *PXCODEC_TYPE;

#define XCODEC_TYPE_AAC_TITLE_ID     0xFFFE07DF
#define XCODEC_TYPE_AAC_CONTENTTYPE  XCONTENTTYPE_MARKETPLACE

typedef
PVOID
(*PFN_CREATE_CODEC_INSTANCE)();

VOID
WINAPI
XMPRegisterCodec(
    IN XCODEC_TYPE xcodectype,
    IN PFN_CREATE_CODEC_INSTANCE pfnCreateCodec
    );

PFN_CREATE_CODEC_INSTANCE
XMPGetCodecCreationFunction(
    IN XCODEC_TYPE xcodectype
    );



DECLSPEC_NORETURN
VOID
XamTerminateTitle(
    VOID
    );


//------------------------------------------------------------------------------
// XAM Scheduler
//------------------------------------------------------------------------------
typedef HRESULT (WINAPI *PXAMTASKPROC)(
    IN      PVOID                       pvParam
    );

typedef PVOID                           HXAMTASK, *PHXAMTASK;
typedef PVOID                           HXAMTASKQUEUE, *PHXAMTASKQUEUE;
typedef PVOID                           HXAMTASKOBJ, *PHXAMTASKOBJ; // Generic handle, either XAMTASK or XAMTASKQUEUE

// Type of task
#define XAMPROPERTY_TYPE_WAIT           0x00000001      // waits on a kernel handle and calls taskproc when signaled
#define XAMPROPERTY_TYPE_DEDICATED      0x00000002      // dedicated thread, will do work and exit
#define XAMPROPERTY_TYPE_POOLED         0x00000004      // reuse some kind of thread pool
#define XAMPROPERTY_TYPE_PERIODIC       0x00000008      // reuse some kind of thread pool, run at regular intervals
#define XAMPROPERTY_TYPE_UI             0x00000010
#define _XAMPROPERTY_TYPE_MASK_         0x0000001F

// When this task wakes up and does processing
#define XAMPROPERTY_WAKEUP_IO           0x00000100      // burst of CPU usage but mostly waiting on I/O
#define XAMPROPERTY_WAKEUP_NETWORK      0x00000200      // burst of CPU usage but mostly waiting on N/W
#define XAMPROPERTY_WAKEUP_OFTENWAIT    0x00000400      // calling WaitFor*Object* often
#define _XAMPROPERTY_WAKEUP_MASK_       0x00000700

// Task CPU usage
#define XAMPROPERTY_CPUUSAGE_LO         0x00001000      // e.g.: waiting and processing notifications
#define XAMPROPERTY_CPUUSAGE_HI         0x00002000      // e.g.: CODEC, encrypting, animations?
#define _XAMPROPERTY_CPUUSAGE_MASK_     0x00003000

// Duration
#define XAMPROPERTY_DURATION_VERYSHORT  0x00010000
#define XAMPROPERTY_DURATION_SHORT      0x00020000
#define XAMPROPERTY_DURATION_LONG       0x00040000
//                                      0x00080000      // Taken below
#define _XAMPROPERTY_DURATION_MASK_     0x00070000

// Priority
#define XAMPROPERTY_PRI_LO              0x00100000
#define XAMPROPERTY_PRI_NORMAL          0x00200000
#define XAMPROPERTY_PRI_HI              0x00400000
#define XAMPROPERTY_PRI_BACKGROUND      0x00800000
#define XAMPROPERTY_PRI_FOREGROUND      0x00080000
#define _XAMPROPERTY_PRI_LOHIMASK_      0x00700000
#define _XAMPROPERTY_PRI_XGROUNDMASK_   0x00880000
#define _XAMPROPERTY_PRI_MASK_          0x00F80000

// Misc
#define XAMPROPERTY_MISC_FIREONCE       0x01000000
#define XAMPROPERTY_MISC_ONTITLEBEHALF  0x02000000
#define XAMPROPERTY_MISC_ONSYSTEMBEHALF 0x04000000
#define XAMPROPERTY_MISC_WAITONHANDLE   0x08000000      // By default, we expect a waitable kernel object (e.g. KEVENT)
#define XAMPROPERTY_MISC_SERIALQUEUE    0x10000000      // hxamtaskqueue needs to be set
#define XAMPROPERTY_MISC_FORCE_GROUND   0x20000000      // forces _XAMPROPERTY_PRI_XGROUNDMASK_ to be followed.  Do not use this except in extreme cases!

#define _XAMPROPERTY_MISC_BEHALFMASK_   0x06000000
#define _XAMPROPERTY_MISC_MASK_         0x1F000000

typedef struct _XAMTASKATTRIBUTES
{
    DWORD                               dwProperties;   // Zero or more XAMPROPERTY_*

    union
    {
        // mandatory for XAMPROPERTY_TYPE_PERIODIC
        DWORD                           dwPeriod;       // Period in millisec, only for XAMPROPERTY_TYPE_PERIODIC

        // mandatory to have one of these for XAMPROPERTY_TYPE_WAIT
        PVOID                           pvWaitable;     // Pointer to waitable kernel object, e.g.: KEVENT
        HANDLE                          hWaitable;      // (1) HANDLE to waitable object, requires XAMPROPERTY_MISC_WAITONHANDLE
                                                        // (2) Make sure to DuplicateHandle it!  CloseHandle will automatically
                                                        //      get called on it when the task is deleted.
                                                        // (3) If using this rather than hWaitable, then the task scheduling can
                                                        //      fail if the HANDLE is invalid.  That would be a caller error.
                                                        // (4) The HANDLE needs to be a system process HANDLE.

        // optionally for XAMPROPERTY_TYPE_POOLED (which is mutually exclusive with XAMPROPERTY_TYPE_WAIT)
        HXAMTASKQUEUE                   hxamtaskqueue;
    };
} XAMTASKATTRIBUTES, *PXAMTASKATTRIBUTES;

HRESULT
XamTaskSchedule(
    IN      PXAMTASKPROC                pxamtaskproc,
    IN      PVOID                       pvParam,
    IN      PXAMTASKATTRIBUTES          pxamtaskattribs OPTIONAL,   // If NULL, default properties will be used
    OUT     PHXAMTASK                   phxamtask
    );

// Usage
//  Create a task using XamTaskCreate, can fail if out of memory
//  Modify it using XamTaskModify, this cannot fail
//  Schedule it using XamTaskReschedule, this cannot fail
HRESULT
XamTaskCreate(
    OUT     PHXAMTASK                   phxamtask
    );

VOID
XamTaskReschedule(
    IN      HXAMTASK                    hxamtask
    );

HRESULT
XamTaskSchedulerInitialize(
    VOID
    );

VOID
XamTaskCloseHandle(
    IN      HXAMTASKOBJ                 hxamtaskobj
    );

VOID
XamTaskCancel(
    IN      HXAMTASK                    hxamtask
    );

// Wait for task to be "done" or "cancelled"
VOID
XamTaskWaitOnCompletion(
    IN      HXAMTASK                    hxamtask
    );

// S_OK: completed
// E_PENDING: not completed
HRESULT
XamTaskGetStatus(
    IN      HXAMTASK                    hxamtask
    );

BOOL
XamTaskShouldExit(
    VOID
    );

#define XAMTASKMODIFY_NONE              0x00000000
#define XAMTASKMODIFY_TASKPROC          0x00000001
#define XAMTASKMODIFY_PVPARAM           0x00000002
#define XAMTASKMODIFY_ATTRIBUTES        0x00000004

VOID
XamTaskModify(
    IN      HXAMTASK                    hxamtask,
    IN      DWORD                       dwFlags,
    IN      PXAMTASKPROC                pxamtaskproc,
    IN      PVOID                       pvParam,
    IN      PXAMTASKATTRIBUTES          pxamtaskattribs
    );

VOID
XamTaskActivateXenonButtonHandler(
    IN      DWORD                       dwPortInput
    );

HXAMTASK
XamTaskGetCurrentTask(
    VOID
    );

DWORD
XamTaskQueryProperty(
    IN      HXAMTASK                    hxamtask,
    IN      DWORD                       dwPropertyMask
    );

HRESULT
XamTaskGetAttributes(
    IN      HXAMTASK                    hxamtask,
    IN OUT  PXAMTASKATTRIBUTES          pxamtaskattribs
    );

HRESULT
XamTaskGetWaitableObject(
    IN      HXAMTASK                    hxamtask,
    OUT     PHANDLE                     ph
    );

HRESULT
XamTaskCreateQueue(
    OUT     PHXAMTASKQUEUE              phxamtaskqueue
    );

HRESULT
XamTaskGetCompletionStatus(
    IN      HXAMTASK                    hxamtask
    );

// Not XamTask function, but close enough
BOOL
XamExecutingOnBehalfOfTitle(
    VOID
    );

#define XNFLAG_INTERNAL                 (0x80000000)
#define XNMASK_AREA                     (0x7e000000)
#define XNMASK_VERSION                  (0x01FF0000)
#define XNID_INTERNAL(Version, Area, Index)(DWORD)(XNID(Version, Area, Index) | XNFLAG_INTERNAL)

//
// This version number needs to be bumped up each time we add a notification
// after a final release.  When a game links to an xdk, this version number
// is linked into the game and only notifications with version less than or
// equal to XNID_CURRENTVERSION will be send to the title.  This scheme will
// help keep new notitifications from breaking existing titles.
//
#define XNID_CURRENTVERSION             (0)
#define XNOTIFY_FEEDBACK                (0x00000010)
#define _XNAREA_FEEDBACK                (4)
#define XN_SYS_TITLELOAD                XNID_INTERNAL(0, _XNAREA_SYSTEM, 0x0001)
#define XN_SYS_TIMEZONE                 XNID_INTERNAL(0, _XNAREA_SYSTEM, 0x0002)
#define XN_SYS_LANGUAGE                 XNID_INTERNAL(0, _XNAREA_SYSTEM, 0x0003)
#define XN_SYS_VIDEOFLAGS               XNID_INTERNAL(0, _XNAREA_SYSTEM, 0x0004)
#define XN_SYS_AUDIOFLAGS               XNID_INTERNAL(0, _XNAREA_SYSTEM, 0x0005)
#define XN_SYS_PARENTALCONTROLGAMES     XNID_INTERNAL(0, _XNAREA_SYSTEM, 0x0006)
#define XN_SYS_PARENTALCONTROLPASSWORD  XNID_INTERNAL(0, _XNAREA_SYSTEM, 0x0007)
#define XN_SYS_PARENTALCONTROLMOVIES    XNID_INTERNAL(0, _XNAREA_SYSTEM, 0x0008)
#define XN_SYS_DASHCONTEXTCHANGED       XNID_INTERNAL(0, _XNAREA_SYSTEM, 0x000c)
#define XN_SYS_DISCMEDIACHANGED         XNID_INTERNAL(0, _XNAREA_SYSTEM, 0x000d)
#define XN_SYS_THEMECHANGED             XNID_INTERNAL(0, _XNAREA_SYSTEM, 0x000f)
#define XN_SYS_SYSTEMUPDATECHANGED      XNID_INTERNAL(0, _XNAREA_SYSTEM, 0x0010)
#define XN_LIVE_INVITE_RECEIVED         XNID_INTERNAL(0, _XNAREA_LIVE, 0x0004)
#define XN_LIVE_INVITE_ANSWER_RECEIVED  XNID_INTERNAL(0, _XNAREA_LIVE, 0x0005)
#define XN_LIVE_MESSAGE_LIST_CHANGED    XNID_INTERNAL(0, _XNAREA_LIVE, 0x0006)
#define XN_LIVE_POINTS_BALANCE_CHANGED  XNID_INTERNAL(0, _XNAREA_LIVE, 0x000B)
#define XN_LIVE_PLAYERSLIST_CHANGED     XNID_INTERNAL(0, _XNAREA_LIVE, 0x000C)
#define XN_LIVE_ITEM_PURCHASED          XNID_INTERNAL(0, _XNAREA_LIVE, 0x000D)
#define XN_FRIENDS_REQUEST_RECEIVED     XNID_INTERNAL(0, _XNAREA_FRIENDS, 0x0004)
#define XN_FRIENDS_ANSWER_RECEIVED      XNID_INTERNAL(0, _XNAREA_FRIENDS, 0x0005)
#define XN_FRIENDS_REQUEST_RESULT       XNID_INTERNAL(0, _XNAREA_FRIENDS, 0x0006)

//
// Feedback notifications
//

#define XN_FEEDBACK_FIRST               XNID(0, _XNAREA_FEEDBACK, 0x0001)
#define XN_FEEDBACK_COMPLAINT_SENT      XNID_INTERNAL(0, _XNAREA_FEEDBACK, 0x0001)
#define XN_FEEDBACK_PR_SENT             XNID_INTERNAL(0, _XNAREA_FEEDBACK, 0x0002)
#define XN_FEEDBACK_PR_CHANGED          XNID_INTERNAL(0, _XNAREA_FEEDBACK, 0x0003)
#define XN_FEEDBACK_LAST                XNID(0, _XNAREA_FEEDBACK, 0x0004)

#define XN_XMP_MEDIASOURCECONNECTIONCHANGED    XNID_INTERNAL(0, _XNAREA_XMP, 0x0004)
#define XN_XMP_TITLEPLAYLISTCONTENTCHANGED     XNID_INTERNAL(0, _XNAREA_XMP, 0x0005)
#define XN_XMP_LOCALMEDIACONTENTCHANGED        XNID_INTERNAL(0, _XNAREA_XMP, 0x0006)
#define XN_XMP_DASHNOWPLAYINGQUEUEMODECHANGED  XNID_INTERNAL(0, _XNAREA_XMP, 0x0007)
HANDLE
WINAPI
XamNotifyCreateListener(
    IN      ULONGLONG                   qwAreas,
    IN      DWORD                       dwVersion
    );

HANDLE
WINAPI
XamNotifyCreateListenerInternal(
    IN     ULONGLONG                    qwAreas,
    IN     BOOL                         fReceiveInternalNotifications,
    IN     DWORD                        dwVersion
    );

#define XNotifyCreateListenerInternal(qwAreas, fReceiveInternalNotifications) \
        XamNotifyCreateListenerInternal(qwAreas, fReceiveInternalNotifications, XNID_CURRENTVERSION)

VOID
WINAPI
XNotifyBroadcast(
    IN      DWORD                       dwNotificationId,
    IN      ULONG_PTR                   param
    );

HRESULT
WINAPI
XNotifyRegisterArea(
    IN      ULONGLONG                   qwArea,
    IN      DWORD                       dwMinGlobalMessage,
    IN      DWORD                       dwMaxGlobalMessage
    );

VOID
WINAPI
XNotifyResetGlobalListener();

VOID
WINAPI
XNotifyFreeTitleHandles();

VOID
WINAPI
XNotifyFreeUIAppHandles();

VOID
WINAPI
XNotifyTitleStartup();


#define XNOTIFYUI_TYPE_FRIENDONLINE         0
#define XNOTIFYUI_TYPE_GAMEINVITE           1
#define XNOTIFYUI_TYPE_FRIENDREQUEST        2
#define XNOTIFYUI_TYPE_GENERIC              3
#define XNOTIFYUI_TYPE_MULTIPENDING         4
#define XNOTIFYUI_TYPE_PERSONALMESSAGE      5
#define XNOTIFYUI_TYPE_SIGNEDOUT            6
#define XNOTIFYUI_TYPE_SIGNEDIN             7
#define XNOTIFYUI_TYPE_SIGNEDINLIVE         8
#define XNOTIFYUI_TYPE_SIGNEDINNEEDPASS     9
#define XNOTIFYUI_TYPE_CHATREQUEST          10
#define XNOTIFYUI_TYPE_CONNECTIONLOST       11
#define XNOTIFYUI_TYPE_DOWNLOADCOMPLETE     12
#define XNOTIFYUI_TYPE_SONGPLAYING          13
#define XNOTIFYUI_TYPE_PREFERRED_REVIEW     14
#define XNOTIFYUI_TYPE_AVOID_REVIEW         15
#define XNOTIFYUI_TYPE_COMPLAINT            16
#define XNOTIFYUI_TYPE_CHATCALLBACK         17
#define XNOTIFYUI_TYPE_REMOVEDMU            18
#define XNOTIFYUI_TYPE_REMOVEDGAMEPAD       19
#define XNOTIFYUI_TYPE_CHATJOIN             20
#define XNOTIFYUI_TYPE_CHATLEAVE            21
#define XNOTIFYUI_TYPE_GAMEINVITESENT       22
#define XNOTIFYUI_TYPE_CANCELPERSISTENT     23
#define XNOTIFYUI_TYPE_CHATCALLBACKSENT     24
#define XNOTIFYUI_TYPE_MULTIFRIENDONLINE    25
#define XNOTIFYUI_TYPE_ONEFRIENDONLINE      26
#define XNOTIFYUI_TYPE_ACHIEVEMENT          27
#define XNOTIFYUI_TYPE_HYBRIDDISC           28
#define XNOTIFYUI_TYPE_MAX                  28


#define XNOTIFYUI_PRIORITY_LOW          0
#define XNOTIFYUI_PRIORITY_DEFAULT      1
#define XNOTIFYUI_PRIORITY_HIGH         2
#define XNOTIFYUI_PRIORITY_PERSISTENT   3

VOID
WINAPI
XNotifyUISetOptions(
    BOOL                                fShow,
    BOOL                                fPlaySound
    );

VOID
WINAPI
XNotifyUIGetOptions(
    BOOL*                               pfShow,
    BOOL*                               pfPlaySound
    );

DWORD
WINAPI
XamInputGetState(
    IN      DWORD                       dwUserIndex,
    IN      DWORD                       dwFlags,
    OUT     PXINPUT_STATE               pState
    );

DWORD
WINAPI
XamInputGetCapabilities(
    IN      DWORD                       dwUserIndex,
    IN      DWORD                       dwFlags,
    OUT     PXINPUT_CAPABILITIES        pCapabilities
    );

DWORD
WINAPI
XamInputSetState(
    IN      DWORD                       dwUserIndex,
    IN      DWORD                       dwFlags,
    IN      PXINPUT_VIBRATION           pVibration,
    IN      BYTE                        bAmplitude      OPTIONAL,
    IN      BYTE                        bFrequency      OPTIONAL,
    IN      BYTE                        bOffset         OPTIONAL
    );

DWORD
WINAPI
XamInputGetDeviceStats(
    IN      DWORD                       dwUserIndex,
    OUT     PXINPUT_DEVICE_STATS        pDeviceStats
    );

DWORD
WINAPI
XamInputGetKeystroke(
    IN      DWORD                       dwUserIndex,
    IN      DWORD                       dwFlags,
    OUT     PXINPUT_KEYSTROKE           pKeystroke
    );

DWORD
WINAPI
XamInputGetKeystrokeEx(
    IN OUT  PDWORD                      pdwUserIndex,
    IN      DWORD                       dwFlags,
    OUT     PXINPUT_KEYSTROKE           pKeystroke
    );

DWORD
WINAPI
XamInputGetKeystrokeHud(
    IN      DWORD                       dwUserIndex,
    OUT     PXINPUT_KEYSTROKE           pKeystroke
    );

DWORD
WINAPI
XamInputSetLayoutKeyboard(
    IN      DWORD                       dwUserIndex,
    IN      DWORD                       dwLanguage
    );

DWORD
WINAPI
XamInputResetLayoutKeyboard(
    IN      DWORD                       dwUserIndex
    );

WORD
WINAPI
XamInputToggleKeyLocks(
    IN      DWORD                       dwUserIndex,
    IN      WORD                        wToggleMask
    );

VOID
XamInputEnableAutobind(
    IN      BOOL                        Enable
    );

DWORD
XamEnableSystemAppInput(
    IN      DWORD                       dwUserIndex,
    IN      BOOL                        Enable
    );

#define XDASHCONTEXT_NONE               0
#define XDASHCONTEXT_TROUBLESHOOTER     1
#define XDASHCONTEXT_ACCOUNTRECOVERY    2
#define XDASHCONTEXT_OOBE               3

VOID
XamSetDashContext(
    IN      DWORD                       dwDashContext
    );

DWORD
XamGetDashContext(
    VOID
    );

DWORD
XamGetCurrentTitleId(
    VOID
    );

BOOL
WINAPI
XamIsCurrentTitleDash(
    VOID
    );

XBOXAPI
ULONG
WINAPI
XamGetSystemVersion(
    VOID
    );

XBOXAPI
NTSTATUS
WINAPI
XamGetGameRatings(
    OUT     PUCHAR*                     ppGameRatings,
    OUT     PULONG                      pcGameRatings
    );

XBOXAPI
DWORD
WINAPI
XamGetWCNConfigFile(
    OUT     LPSTR                       pszFile,
    IN      DWORD                       cchFile
    );

DECLSPEC_NORETURN
XBOXAPI
VOID
WINAPI
XamLaunchNewImage(
    IN      LPCSTR                      pszImagePath,
    IN      DWORD                       dwFlags
    );


//------------------------------------------------------------------------------
// XVoice APIs
//------------------------------------------------------------------------------
#ifdef  __XVOICE_H__
XBOXAPI
HRESULT
WINAPI
XamVoiceCreate(
    IN      DWORD                       dwUserIndex,
    IN      DWORD                       dwMaxAttachedPackets,
    OUT     PXVOICE_HANDLE              phHandle
    );

XBOXAPI
BOOL
WINAPI
XamVoiceHeadsetPresent(
    IN      XVOICE_HANDLE               hObject
    );

XBOXAPI
HRESULT
WINAPI
XamVoiceSubmitPacket(
    IN      XVOICE_HANDLE               hObject,
    IN      BOOL                        fInput,
    IN OUT  PXMEDIAPACKET               Packet
    );

XBOXAPI
BOOL
WINAPI
XamVoiceClose(
    IN      XVOICE_HANDLE               hObject
    );
#endif  __XVOICE_H__

#define XA_NONE                         0x00000000
#define XA_REVIEW                       0x00000000  // Tag XamAlloc callswith
                                                    // this if you're not sure
                                                    // what flags to use
#define XA_DEFAULT                      0x00000000

// Type of memory
#define XA_WORKSPACE                    0x10000000
#define XA_HEAP                         0x20000000
#define XA_PHYSICAL                     0x40000000
#define XA_XMP                          0x80000000
#define _XA_TYPE_MASK_                  0xF0000000

// Modifiers
#define XA_PERMANENT                    0x01000000
#define XA_UIRUNTIME                    0x02000000
#define XA_CHARGESYSTEM                 0x04000000
#define XA_CHARGETITLE                  0x08000000

// By default all allocations thru XamAlloc are zero'ed out, pass this flag in to
// avoid that.
#define XA_NOZEROMEMORY                 0x00100000

// Internalto XamAlloc use only, do not use
#define _XA_DEBUGHEAP_                  0x00010000

#define _XA_CHARGE_MASK_                0x0C000000
#define _XA_LIFETIME_MASK_              0x03000000
#define _XA_MODIFIER_MASK_              0x0F100000

// Don't touch the _HXAMAPP_MASK_ values!
//#define XA_DONTTOUCH_                 _HXAMAPP_MASK_

HRESULT
WINAPI
XamAlloc(
    IN      DWORD                       dwFlags,
    IN      DWORD                       cb,
    OUT     PVOID*                      ppv
    );

// Use only for physical allocs
HRESULT
WINAPI
XamAllocEx(
    IN      DWORD                       dwFlagsEx,
    IN      DWORD                       dwFlags,
    IN      DWORD                       cb,
    OUT     PVOID*                      ppv
    );

VOID
WINAPI
XamFree(
    IN      PVOID                       pv
    );

SIZE_T
WINAPI
XamAllocSize(
    IN      PVOID                       pv
    );



//------------------------------------------------------------------------------
// Session handle helpers
//------------------------------------------------------------------------------

DWORD
WINAPI
XamSessionCreateHandle(HANDLE* ph);

DWORD
WINAPI
XamSessionRefObjByHandle(HANDLE h, void** ppSessionStruct);


//------------------------------------------------------------------------------
DWORD
XamGetOverlappedResult(
    IN      PXOVERLAPPED                lpXOverlapped,
    OUT     LPDWORD                     pdwResult,
    IN      BOOL                        bWait
    );

DWORD
XamGetOverlappedExtendedError(
    IN      PXOVERLAPPED                lpXOverlapped
    );

DWORD
XamEnumerate(
    IN      HANDLE                      hEnum,
    IN      DWORD                       dwFlags,
    IN      PVOID                       pvBuffer,
    IN      DWORD                       cbBuffer,
    OUT     PDWORD                      pcItemsReturned     OPTIONAL,
    IN OUT  PXOVERLAPPED                pOverlapped         OPTIONAL
    );

DWORD
XamContentCreate(
    IN      DWORD                       dwUserIndex,
    IN      LPCSTR                      pszRootName,
    IN      CONST XCONTENT_DATA*        pcd,
    IN      DWORD                       dwContentFlags,
    OUT     PDWORD                      pdwDisposition      OPTIONAL,
    OUT     PDWORD                      pdwLicenseMask      OPTIONAL,
    IN OUT  PXOVERLAPPED                pOverlapped         OPTIONAL
    );

DWORD
XamContentCreateEx(
    IN      DWORD                       dwUserIndex,
    IN      LPCSTR                      pszRootName,
    IN      CONST XCONTENT_DATA*        pcd,
    IN      DWORD                       dwContentFlags,
    OUT     PDWORD                      pdwDisposition      OPTIONAL,
    OUT     PDWORD                      pdwLicenseMask      OPTIONAL,
    IN      DWORD                       dwFileCacheSize,
    IN      ULARGE_INTEGER              uliContentSize,
    IN OUT  PXOVERLAPPED                pOverlapped         OPTIONAL
    );

DWORD
XamContentCreateInternal(
    IN      LPCSTR                      pszRootName,
    IN      CONST XCONTENT_DATA_INTERNAL* pcdi,
    IN      DWORD                       dwContentFlags,
    OUT     PDWORD                      pdwDisposition      OPTIONAL,
    OUT     PDWORD                      pdwLicenseMask      OPTIONAL,
    IN      DWORD                       dwFileCacheSize,
    IN      ULARGE_INTEGER              uliContentSize,
    IN OUT  PXOVERLAPPED                pOverlapped         OPTIONAL
    );

DWORD
XamContentOpenFile(
    IN      DWORD                       dwUserIndex,
    IN      LPCSTR                      pszRootName,
    IN      LPCSTR                      pszFileName,
    IN      DWORD                       dwContentFlags,
    IN      DWORD                       dwFileCacheSize,
    OUT     PDWORD                      pdwLicenseMask      OPTIONAL,
    IN OUT  PXOVERLAPPED                pOverlapped         OPTIONAL
    );

DWORD
XamContentOpenFileInternal(
    IN      DWORD                       dwUserIndex,
    IN      LPCSTR                      pszRootName,
    IN      LPCSTR                      pszFileName,
    IN      DWORD                       dwContentFlags,
    IN      DWORD                       dwFileCacheSize,
    OUT     PXCONTENT_DATA_INTERNAL     pcdi                OPTIONAL,
    OUT     PDWORD                      pdwLicenseMask      OPTIONAL,
    IN OUT  PXOVERLAPPED                pOverlapped         OPTIONAL
    );

DWORD
XamContentInstall(
    IN      DWORD                       dwUserIndex,
    IN      XCONTENTDEVICEID            DeviceID,
    IN      LPCSTR                      pszFileName,
    IN OUT  PXOVERLAPPED                pOverlapped         OPTIONAL
    );

DWORD
XamContentDelete(
    IN      DWORD                       dwUserIndex,
    IN      CONST XCONTENT_DATA*        pcd,
    IN OUT  PXOVERLAPPED                pOverlapped         OPTIONAL
    );

DWORD
XamContentDeleteInternal(
    IN      CONST XCONTENT_DATA_INTERNAL* pcdi,
    IN OUT  PXOVERLAPPED                  pOverlapped         OPTIONAL
    );


DWORD
XamContentResolve(
    IN      DWORD                       dwUserIndex,
    IN      CONST XCONTENT_DATA*        pcd,
    OUT     LPSTR                       pszPath,
    IN      DWORD                       cchPath,
    IN      BOOL                        fCreateDir,
    IN      LPCSTR                      pszRootName,        OPTIONAL
    IN OUT  PXOVERLAPPED                pOverlapped         OPTIONAL
    );

DWORD
XamContentResolveInternal(
    IN      CONST XCONTENT_DATA_INTERNAL* pcdi,
    OUT     LPSTR                       pszPath,
    IN      DWORD                       cchPath,
    IN      BOOL                        fCreateDir,
    IN      LPCSTR                      pszRootName,        OPTIONAL
    IN OUT  PXOVERLAPPED                pOverlapped         OPTIONAL
    );

DWORD
XamContentGetAttributes(
    IN      DWORD                       dwUserIndex,
    IN      CONST XCONTENT_DATA*        pcd,
    OUT     LPWIN32_FILE_ATTRIBUTE_DATA pfad,
    IN OUT  PXOVERLAPPED                pOverlapped         OPTIONAL
    );

DWORD
XamContentGetAttributesInternal(
    IN      CONST XCONTENT_DATA_INTERNAL* pcdi,
    OUT     LPWIN32_FILE_ATTRIBUTE_DATA pfad,
    IN OUT  PXOVERLAPPED                pOverlapped         OPTIONAL
    );

DWORD
XamContentCopyInternal(
    IN      CONST XUID*                     pXuidDst,       OPTIONAL
    IN      CONST XCONTENTDEVICEID*         pDeviceIdDst,   OPTIONAL
    IN      CONST XCONTENT_DATA_INTERNAL*   pcdi,
    IN OUT  PXOVERLAPPED                    pOverlapped     OPTIONAL
    );

DWORD
XamContentMoveInternal(
    IN      CONST XUID*                     pXuidDst,       OPTIONAL
    IN      CONST XCONTENTDEVICEID*         pDeviceIdDst,   OPTIONAL
    IN      CONST XCONTENT_DATA_INTERNAL*   pcdi,
    IN OUT  PXOVERLAPPED                    pOverlapped     OPTIONAL
    );

#define XCONTENT_COPYFLAG_NONE              0x00000000
#define XCONTENT_COPYFLAG_DELETESOURCE      0x00000001
#define XCONTENT_COPYFLAG_DEVICETRANSFER    0x00000002
#define XCONTENT_COPYFLAG_PROFILETRANSFER   0x00000004

DWORD
XamContentClose(
    IN      LPCSTR                      pszRootName,
    IN OUT  PXOVERLAPPED                pOverlapped         OPTIONAL
    );

DWORD
XamContentFlush(
    IN      LPCSTR                      pszRootName,
    IN      PXOVERLAPPED                pOverlapped         OPTIONAL
    );

DWORD
XamContentCreateEnumerator(
    IN      DWORD                       dwUserIndex,
    IN      XCONTENTDEVICEID            DeviceID,
    IN      DWORD                       dwContentType,
    IN      DWORD                       dwContentFlags,
    IN      DWORD                       cItem,
    OUT     PDWORD                      pcbBuffer,          OPTIONAL
    OUT     PHANDLE                     phEnum
    );

DWORD
XamContentCreateEnumeratorInternal(
    IN      XUID                        xuid,
    IN      XCONTENTDEVICEID            dwDeviceId,
    IN      DWORD                       dwContentType,
    IN      DWORD                       dwTitleId,
    IN      DWORD                       dwContentFlags,
    IN      DWORD                       cItem,
    OUT     PDWORD                      pcbBuffer,          OPTIONAL
    OUT     PHANDLE                     phEnum
    );

DWORD
XamContentCreateDeviceEnumerator(
    IN      DWORD                       dwContentTypes,
    IN      DWORD                       dwFlags,
    IN      DWORD                       cItem,
    OUT     PDWORD                      pcbBuffer           OPTIONAL,
    OUT     PHANDLE                     phEnum
    );



#define COMMONUSER_XUID                 ((XUID) -1)

DWORD
XamContentAggregateCreateEnumerator(
    IN      XUID                        xuid,
    IN      XCONTENTDEVICEID            DeviceId,
    IN      DWORD                       dwContentType,
    IN      DWORD                       dwTitleId,
    OUT     PHANDLE                     phEnum
    );

DWORD
XamContentGetDeviceState(
    IN      XCONTENTDEVICEID            DeviceID,
    IN OUT  PXOVERLAPPED                pOverlapped
    );

DWORD
XamContentGetDeviceData(
    IN      XCONTENTDEVICEID            DeviceID,
    OUT     PXDEVICE_DATA               pDeviceData
    );

DWORD
XamContentGetDeviceName(
    IN      XCONTENTDEVICEID            DeviceID,
    OUT     LPWSTR                      pwszName,
    IN      DWORD                       cchName
    );

DWORD
XamContentGetMetaDataInternal(
    IN      CONST XCONTENT_DATA_INTERNAL*   pcdi,
    OUT     XCONTENT_METADATA*              pContentMetaData,
    IN OUT  PXOVERLAPPED                    pOverlapped     OPTIONAL
    );

DWORD
XamContentSetThumbnail(
    IN      DWORD                           dwUserIndex,
    IN      CONST XCONTENT_DATA*            pcd,
    IN      CONST BYTE*                     pbThumbnail,
    IN      DWORD                           cbThumbnail,
    IN OUT  PXOVERLAPPED                    pOverlapped     OPTIONAL
    );

DWORD
XamContentGetThumbnail(
    IN      DWORD                           dwUserIndex,
    IN      CONST XCONTENT_DATA*            pContentData,
    OUT     PBYTE                           pbThumbnail,    OPTIONAL
    IN OUT  PDWORD                          pcbThumbnail,
    IN OUT  PXOVERLAPPED                    pOverlapped     OPTIONAL
    );

DWORD
XamContentGetCreator(
    IN      DWORD                           dwUserIndex,
    IN      CONST XCONTENT_DATA*            pContentData,
    OUT     BOOL*                           pfUserIsCreator,
    OUT     PXUID                           pxuid,          OPTIONAL
    IN OUT  PXOVERLAPPED                    pOverlapped     OPTIONAL
    );

DWORD
XamContentSetThumbnailInternal(
    IN      CONST XCONTENT_DATA_INTERNAL*   pcdi,
    IN      CONST BYTE*                     pbThumbnail,
    IN      DWORD                           cbThumbnail,
    IN OUT  PXOVERLAPPED                    pOverlapped     OPTIONAL
    );

DWORD
XamContentGetLicenseMask(
    OUT     DWORD*                          pdwLicenseMask,
    IN OUT  PXOVERLAPPED                    pOverlapped     OPTIONAL
    );

#define XCONTENT_PACKAGE_FS_DEVICE_PREFIX                   "\\Device\\Package_"
#define XCONTENT_MAX_PACKAGE_FS_DEVICE_NAME                 64

#define XCONTENT_PKGFLAG_KEEP_OPEN_ON_TITLE_TERMINATE       0x00000001
#define XCONTENT_PKGFLAG_DONT_UPDATE_DIGESTS_ON_CLOSE       0x00000002

#define COMMON_XCONTENT_PKGFLAGS                            (XCONTENT_PKGFLAG_KEEP_OPEN_ON_TITLE_TERMINATE | \
                                                             XCONTENT_PKGFLAG_DONT_UPDATE_DIGESTS_ON_CLOSE)

typedef struct _XCONTENT_MOUNTED_PACKAGE
{
    PVOID                                   pvFsDeviceObject;
    PVOID                                   pvFsBlockCache;
    LIST_ENTRY                              leMountedPackages;
    DWORD                                   dwFlags;
    HANDLE                                  hPackageFile;
    DWORD                                   dwOpenRefCount;
    RTL_CRITICAL_SECTION                    csHeaderLock;
    XCONTENT_HEADER                         ContentHeader;
    XCONTENT_METADATA                       ContentMetaData;
    PBYTE                                   pbOtherMetaData;
    DWORD                                   dwOtherMetaDataSize;
    XCONTENTDEVICEID                        DeviceIDLocked;
    CHAR                                    szFsDeviceName[XCONTENT_MAX_PACKAGE_FS_DEVICE_NAME];
    CHAR                                    szPackageFilePath[MAX_PATH];
} XCONTENT_MOUNTED_PACKAGE, *PXCONTENT_MOUNTED_PACKAGE;

#define XCONTENT_CREATEPKG_KEEP_OPEN_ON_TITLE_TERMINATE     XCONTENT_PKGFLAG_KEEP_OPEN_ON_TITLE_TERMINATE
#define XCONTENT_CREATEPKG_DONT_UPDATE_DIGESTS_ON_CLOSE     XCONTENT_PKGFLAG_DONT_UPDATE_DIGESTS_ON_CLOSE
#define XCONTENT_CREATEPKG_OVERWRITE                        0x00010000

#define VALID_XCONTENT_CREATEPKG_FLAGS                      (XCONTENT_CREATEPKG_KEEP_OPEN_ON_TITLE_TERMINATE | \
                                                             XCONTENT_CREATEPKG_DONT_UPDATE_DIGESTS_ON_CLOSE | \
                                                             XCONTENT_CREATEPKG_OVERWRITE)

DWORD
XamContentCreateAndMountPackage(
    IN      LPCSTR                          szPackagePath,
    IN      HANDLE                          hFileToUse              OPTIONAL,
    IN      CONST XCONTENT_METADATA*        pMetaData,
    IN      CONST BYTE*                     pbOtherMetaData         OPTIONAL,
    IN      DWORD                           dwOtherMetaDataSize,
    IN      DWORD                           dwFlags,
    IN      XCONTENTDEVICEID                DeviceIDToLock,
    OUT     PXCONTENT_MOUNTED_PACKAGE*      ppMountedPackage
    );

#define XCONTENT_OPENPKG_DONT_VERIFY_SIGNATURE              0x00010000
#define XCONTENT_OPENPKG_COPY_EXISTING_HANDLE               0x00020000

#define VALID_XCONTENT_OPENPKG_FLAGS                        (XCONTENT_OPENPKG_DONT_VERIFY_SIGNATURE | \
                                                             XCONTENT_OPENPKG_COPY_EXISTING_HANDLE)

DWORD
XamContentOpenPackageFile(
    IN      LPCSTR                          szPackagePath,
    IN      DWORD                           dwContentType,
    IN      DWORD                           dwFlags,
    OUT     HANDLE *                        phPackageFile,
    OUT     PXCONTENT_MOUNTED_PACKAGE*      ppExistingMountedPackage,
    OUT     XCONTENT_HEADER *               pContentHeader,
    OUT     XCONTENT_METADATA *             pContentMetaData,
    OUT     BYTE *                          pbOtherMetaData         OPTIONAL,
    IN OUT  DWORD *                         pdwOtherMetaDataSize    OPTIONAL
    );

#define XCONTENT_MOUNTPKG_KEEP_OPEN_ON_TITLE_TERMINATE      XCONTENT_PKGFLAG_KEEP_OPEN_ON_TITLE_TERMINATE
#define XCONTENT_MOUNTPKG_DONT_UPDATE_DIGESTS_ON_CLOSE      XCONTENT_PKGFLAG_DONT_UPDATE_DIGESTS_ON_CLOSE

#define VALID_XCONTENT_MOUNTPKG_FLAGS                       (XCONTENT_MOUNTPKG_KEEP_OPEN_ON_TITLE_TERMINATE | \
                                                             XCONTENT_MOUNTPKG_DONT_UPDATE_DIGESTS_ON_CLOSE)

DWORD
XamContentMountPackage(
    IN      HANDLE                          hPackageFile,
    IN      LPCSTR                          szPackagePath,
    IN      const XCONTENT_HEADER *         pContentHeader,
    IN      const XCONTENT_METADATA *       pContentMetaData,
    IN      const BYTE *                    pbOtherMetaData         OPTIONAL,
    IN      DWORD                           dwOtherMetaDataSize,
    IN      DWORD                           dwFlags,
    IN      XCONTENTDEVICEID                DeviceIDToLock,
    OUT     PXCONTENT_MOUNTED_PACKAGE *     ppMountedPackage
    );

DWORD
XamContentWritePackageHeader(
    IN      XCONTENT_MOUNTED_PACKAGE *      pMountedPackage
    );

DWORD
XamContentFlushPackage(
    IN      XCONTENT_MOUNTED_PACKAGE *      pMountedPackage
    );

DWORD
XamContentDismountAndClosePackage(
    IN      XCONTENT_MOUNTED_PACKAGE *      pMountedPackage
    );

DWORD
XamContentClosePackageFile(
    IN      HANDLE                          hPackageFile
    );

DWORD
XamContentLockUnlockPackageHeaders(
    IN      XCONTENT_MOUNTED_PACKAGE *      pMountedPackage,
    IN      BOOL                            fLock
    );

DWORD
XamContentEstimatePackageSize(
    IN      DWORD                           cbContentSize
    );

#define XamContentReferencePackage(pkg)         ObReferenceObject((pkg)->pvFsDeviceObject)
#define XamContentDereferencePackage(pkg)       ObDereferenceObject((pkg)->pvFsDeviceObject)
#define XamContentSetPackageFlags(pkg, flags)   ((DWORD) InterlockedOr((LONG*) (&(pkg)->dwFlags), (LONG) (flags)))
#define XamContentClearPackageFlags(pkg, flags) ((DWORD) InterlockedAnd((LONG*) (&(pkg)->dwFlags), (LONG) (~(flags))))


DWORD
XamContentLaunchImage(
    IN      DWORD                           dwUserIndex,
    IN      CONST XCONTENT_DATA*            pContentData,
    IN      LPCSTR                          pszImagePath
);


DWORD
XamContentLaunchImageInternal(
    IN      CONST XCONTENT_DATA_INTERNAL*   pContentData,
    IN      LPCSTR                          pszImagePath
    );

typedef struct _XDEVICERENAMEPARAM
{
    XCONTENTDEVICEID                        DeviceID;
    LPCWSTR                                 pwszName;
    DWORD                                   cchName;
} XDEVICERENAMEPARAM, *PXDEVICERENAMEPARAM;

//------------------------------------------------------------------------------
// XamUser functions and flags
//------------------------------------------------------------------------------
#define XAMUSER_NONE                                    0x00000000
#define XAMUSER_XUID_OFFLINE                            0x00000001
#define XAMUSER_XUID_ONLINE                             0x00000002
#define XAMUSER_XUID_GUEST                              0x00000004
#define XAMUSER_RECOVER_ACCOUNT                         0x80000000

#define XAMUSERLOGON_OFFLINEONLY                        0x00000001
#define XAMUSERLOGON_FORCELIVELOGOFF                    0x00000002  // requires XAMUSERLOGON_OFFLINEONLY
#define XAMUSERLOGON_ADDUSERS                           0x00000004
#define XAMUSERLOGON_REMOVEUSERS                        0x00000008
#define XAMUSERLOGON_FOREGROUNDPRI                      0x00000010
#define XAMUSERLOGON_NOPOPUPNOTIFICATION                0x00000020
#define XAMUSERLOGON_DONTWAITFORCOMPLETION              0x00000040
#define XAMUSERLOGON_ALLOWMACHINEACCOUNTONLY            0x00000080
#define XAMUSERLOGON_CHECKONLINETICKETSONLY             0x00000100
#define XAMUSERLOGON_ALLOWDEFAULTUSER                   0x00000200
#define XAMUSERLOGON_ALLOWUSERSWITHREQUIREDMESSAGE      0x00000400
#define XAMUSERLOGON_RESTRICTEDPOPUPNOTIFICATION        0x00000800


HRESULT
WINAPI
XamUserGetXUID(
    IN      DWORD                       dwUserIndex,
    IN      DWORD                       dwFlags,            // XAMUSER_XUID_ONLINE, OFFLINE or EITHER
    OUT     PXUID                       pxuid
    );

HRESULT
WINAPI
XamUserGetIndexFromXUID(
    IN      XUID                        xuid,
    IN      DWORD                       dwFlags,
    OUT     PDWORD                      pdwUserIndex
    );

HRESULT
WINAPI
XamUserGetGamerTag(
    IN      DWORD                       dwUserIndex,
    OUT     LPWSTR                      pszGamerTag,
    IN      DWORD                       cchGamerTag
    );

HRESULT
WINAPI
XamUserLogon(
    IN      CONST XUID*                 rgUsers,
    IN      DWORD                       dwFlags,
    IN      PXOVERLAPPED                pOverlapped         OPTIONAL
    );

#ifndef PROFILEENUMRESULT
typedef struct _PROFILEENUMRESULT PROFILEENUMRESULT;
#endif

HRESULT
WINAPI
XamUserLogonEx(
    IN      CONST PROFILEENUMRESULT*    rgUsers,
    IN      DWORD                       dwFlags,
    IN      PXOVERLAPPED                pOverlapped         OPTIONAL
    );

HRESULT
WINAPI
XamUserFlushLogonQueue(
    IN      PXOVERLAPPED                pOverlapped         OPTIONAL
    );

DWORD
WINAPI
XamUserGetUserIndexMask(
    IN      DWORD                       dwFlags             // See XAMUSER_
    );

DWORD
WINAPI
XamUserGetRequestedUserIndexMask(
    IN      DWORD                       dwFlags             // See XAMUSER_
    );


DWORD
WINAPI
XamGetUserPresetPresenceState(
    IN      DWORD                       dwUserIndex
    );

VOID
WINAPI
XamSetUserPresetPresenceState(
    IN      DWORD                       dwUserIndex,
    IN      DWORD                       dwStateFlags
    );

BOOL
WINAPI
XamUserIsOnlineEnabled(
    IN      DWORD                       dwUserIndex
    );

DWORD
WINAPI
XamUserGetUserFlags(
    IN      DWORD                       dwUserIndex
    );

DWORD
WINAPI
XamUserGetUserFlagsFromXUID(
    IN      XUID                        xuid
    );

DWORD
WINAPI
XamUserGetCachedUserFlags(
    IN      DWORD                       dwUserIndex
    );

BYTE
WINAPI
XamUserGetOnlineCountryFromXUID(
    IN      XUID                        xuid
    );

BYTE
WINAPI
XamUserGetMembershipTier(
    IN      DWORD                       dwUserIndex
    );

BYTE
WINAPI
XamUserGetMembershipTierFromXUID(
    IN      XUID                        xuid
    );

BOOL
WINAPI
XamUserIsGuest(
    IN      DWORD                       dwUserIndex
    );



// Macros to use with XamUserGetUserIndexMask.  Given a user index and a bit
// mask, tells if a user index bit is on or off.
#define XAMUSER_MASK_USERINDEX_X(__dwUserIndex__, __dw__) (!!((__dw__) & (1 << (__dwUserIndex__))))

#define XAMUSER_MASK_USERINDEX_0(__dw__) XAMUSER_USERINDEX_X(0, __dw__)
#define XAMUSER_MASK_USERINDEX_1(__dw__) XAMUSER_USERINDEX_X(1, __dw__)
#define XAMUSER_MASK_USERINDEX_2(__dw__) XAMUSER_USERINDEX_X(2, __dw__)
#define XAMUSER_MASK_USERINDEX_3(__dw__) XAMUSER_USERINDEX_X(3, __dw__)

HRESULT
WINAPI
XamUserGetDeviceContext(
    IN      DWORD                       dwUserIndex,
    IN      UCHAR                       ucDeviceCategory,
    OUT     PULONG_PTR                  pulDeviceContext
    );

HRESULT
WINAPI
XamUserLookupDevice(
    IN      ULONG_PTR                   ulDeviceContext,
    IN      UCHAR                       ucDeviceCategory,
    OUT     PDWORD                      pdwUserIndex
    );

HRESULT
WINAPI
XamUserBindDeviceCallback(
    IN      ULONG_PTR                   ulUserIdentifier,
    IN      ULONG_PTR                   ulDeviceContext,
    IN      UCHAR                       ucDeviceCategory,
    IN      BOOLEAN                     fUnbindUser,
    OUT     PUCHAR                      pucAssignedUser
    );

DWORD
WINAPI
XamUserCheckPrivilege(
    IN      DWORD                       dwUserIndex,
    IN      DWORD                       PrivilegeType,
    OUT     PBOOL                       pfResult
    );

DWORD
WINAPI
XamUserAreUsersFriends(
    IN      DWORD                       dwUserIndex,
    IN      PXUID                       pXuids,
    IN      DWORD                       dwXuidCount,
    OUT     PBOOL                       pfResult            OPTIONAL,
    IN OUT  PXOVERLAPPED                pOverlapped         OPTIONAL
    );


// Defines for XAMACCOUNTINFO's dwMask, indicate valid fields.
// Keep these bits packed together as much as possible.  Might use some
// remaining bits for versioning at a later time.
#define XAMPROFILE_NONE                         0x00000000
#define XAMPROFILE_PASSCODE                     0x10000000          // set if password field is valid
#define XAMPROFILE_ONLINEENABLED                0x20000000          // set if account is online enabled

#define XAMPROFILE_VERSIONMASK                  0x000000FF

#define XAMPROFILE_VERSION1                     1

#define XAMPROFILE_CURRENTVERSION               XAMPROFILE_VERSION1

#define XAMPROFILE_MAX_HD                       32
#define XAMPROFILE_MAX_MU                       8

#define XAMACCOUNT_LIVEFLAG_ACCTREQUIRESMGMT    0x00000001


#define XAMACCOUNT_PASSCODELENGTH               4
#define XAMACCOUNT_ONLINEDOMAINSIZE             20
#define XAMACCOUNT_ONLINEKERBEROSREALMSIZE      24
#define XAMACCOUNT_ONLINEKEYLENGTH              16
#define XAMACCOUNT_USERPASSPORTMEMBERNAMESIZE   (113 + 1)
#define XAMACCOUNT_USERPASSPORTPASSWORDSIZE     (16 + 16)
#define XAMACCOUNT_OWNERPASSPORTMEMBERNAMESIZE  XAMACCOUNT_USERPASSPORTMEMBERNAMESIZE


#define XAMUSER_ISTEAMXUID              IsTeamXUID
#define XAMUSER_ISOFFLINEXUID           IsOfflineXUID
#define XAMUSER_ISONLINEXUID            IsOnlineXUID
#define XAMUSER_ISGUESTXUID             IsGuestXUID

#pragma pack(push, 1)

typedef struct _XAMACCOUNTINFO
{
    DWORD                               dwReserved;         // Don't touch outside of XamProfile* functions
    DWORD                               dwLiveFlags;
    WCHAR                               szGamerTag[XUSER_NAME_SIZE];
    XUID                                xuidOnline;
    DWORD                               dwCachedUserFlags;
    DWORD                               dwOnlineServiceNetworkID;
    BYTE                                rgbPasscode[XAMACCOUNT_PASSCODELENGTH];
    CHAR                                szOnlineDomain[XAMACCOUNT_ONLINEDOMAINSIZE];
    CHAR                                szOnlineKerberosRealm[XAMACCOUNT_ONLINEKERBEROSREALMSIZE];
    BYTE                                rgbOnlineKey[XAMACCOUNT_ONLINEKEYLENGTH];
    CHAR                                szUserPassportMembername[XAMACCOUNT_USERPASSPORTMEMBERNAMESIZE];
    CHAR                                rgcUserPassportPassword[XAMACCOUNT_USERPASSPORTPASSWORDSIZE];
    CHAR                                szOwnerPassportMembername[XAMACCOUNT_OWNERPASSPORTMEMBERNAMESIZE];
} XAMACCOUNTINFO, *PXAMACCOUNTINFO;

#pragma pack(pop)

typedef struct _USER_PAYMENT_INFO       USER_PAYMENT_INFO, *PUSER_PAYMENT_INFO;
typedef struct _PASSPORT_SESSION_TOKEN  PASSPORT_SESSION_TOKEN;

HRESULT
WINAPI
XamProfileCreate(
    IN      DWORD                       dwFlags,            // XAMUSER_XUID_ONLINE, OFFLINE or both
    IN OUT  PXCONTENTDEVICEID           pDeviceID,
    IN      XUID                        xuidOffline,
    IN      CONST XAMACCOUNTINFO*       paccountinfo,
    IN      CONST USER_PAYMENT_INFO*    puserpaymentinfo,
    IN      CONST PASSPORT_SESSION_TOKEN* puserPassportToken,
    IN      CONST PASSPORT_SESSION_TOKEN* pownerPassportToken,
    OUT     PVOID*                      ppvContext
    );

HRESULT
WINAPI
XamProfileGetCreationStatus(
    IN      PVOID                       pvContext,
    OUT     PXUID                       pxuidOffline
    );

HRESULT
WINAPI
XamProfileDelete(
    IN      XCONTENTDEVICEID            DeviceID,
    IN      XUID                        xuidOffline
    );

typedef struct _PROFILEENUMRESULT
{
    XUID                xuidOffline;
    XAMACCOUNTINFO      xai;
    XCONTENTDEVICEID    DeviceID;
} PROFILEENUMRESULT, *PPROFILEENUMRESULT;

DWORD
WINAPI
XamProfileCreateEnumerator(
    IN      XCONTENTDEVICEID            DeviceID,
    OUT     PHANDLE                     phEnum
    );

DWORD
WINAPI
XamProfileEnumerate(
    IN      HANDLE                      hEnum,
    IN      DWORD                       dwFlags,
    OUT     PPROFILEENUMRESULT          pProfileEnumResult,
    IN OUT  PXOVERLAPPED                pOverlapped         OPTIONAL
    );

DWORD
WINAPI
XamProfileFindAccount(
    IN      XUID                        xuidOffline,
    OUT     PXAMACCOUNTINFO             pAccountInfo,
    OUT     PXCONTENTDEVICEID           pDeviceID           OPTIONAL
    );

DWORD
WINAPI
XamProfileRenameAccount(
    IN      XUID                        xuidOffline,
    IN      LPCWSTR                     pszName
    );

DWORD
WINAPI
XamProfileOpen(
    IN      XUID                        xuidOffline,
    IN      LPCSTR                      pszRootName,
    IN      DWORD                       dwFlags,
    OUT     PXCONTENT_DATA_INTERNAL     pcdi                OPTIONAL
    );


DWORD
WINAPI
XamProfileClose(
    IN      LPCSTR                      pszRootName
    );


HRESULT
WINAPI
XamProfileLoadAccountInfo(
    IN      XCONTENTDEVICEID            DeviceID,
    IN      XUID                        xuidOffline,
    OUT     PXAMACCOUNTINFO             pAccountInfo
    );

HRESULT
WINAPI
XamProfileSaveAccountInfo(
    IN      XCONTENTDEVICEID            DeviceID,
    IN      XUID                        xuidOffline,
    IN      XAMACCOUNTINFO *            pAccountInfo
    );


__inline
BOOL
XamProfileIsParentalControlled(
    IN      CONST XAMACCOUNTINFO*       pAccountInfo
    )
{
    return ((pAccountInfo->dwCachedUserFlags & XONLINE_USER_PARENTAL_CONTROLLED) != 0);
}

BOOL
WINAPI
XamAreMixedAccountsSignedIn(
    );


//
// Contains information need to process an async message.  This structure
// is pointed to by the InternalContext field from the XOVERLAPPED structure.
// In some cases, when some user data needs to be associated with the message,
// memory for the user data and this structure is allocated in a single
// allocation.
//

typedef struct _XASYNCMESSAGE
{
    HXAMAPP                             hxamapp;
    DWORD                               dwMessage;
    PXOVERLAPPED                        pOverlapped;
    PVOID                               pBuffer;
    PVOID                               UserEvent;
    PVOID                               Apc;
    HXAMTASK                            hXamTask;
} XASYNCMESSAGE, *PXASYNCMESSAGE;

//
// XAM Boot Data
//
// This is shared between XAM and XBDM, so be sure to keep it backward
// compatible.
//

typedef enum _XAM_BOOT_REASON
{
    XAM_BOOT_SYSTEM_START               = 0,
    XAM_BOOT_LAUNCH_MEDIA,
    XAM_BOOT_LAUNCH_NEW_IMAGE,
    XAM_BOOT_USER_REQUEST,
    XAM_BOOT_DEBUG_REQUEST,
    XAM_BOOT_RECOVERY,
    XAM_BOOT_MFG_LOADER,
    XAM_BOOT_DUMP,
    XAM_BOOT_LAUNCH_DASHBOARD,
    XAM_BOOT_LAUNCH_ANY_DASHBOARD,
} XAM_BOOT_REASON;


#define XAM_MAX_LAUNCH_PATH                     256
#define XAM_BOOT_DATA_FLAG_TITLE                0x00000001
#define XAM_BOOT_DATA_FLAG_UNLOAD_HUD           0x00000002
#define XAM_BOOT_DATA_FLAG_BOUND_PATH           0x00000004
#define XAM_BOOT_DATA_FLAG_ASSUME_DVD           0x00000010
#define XAM_BOOT_DATA_FLAG_DASH_ARCADE          0x00000020
#define XAM_BOOT_DATA_FLAG_HYBRID_FORCE_DVD     0x00000040
#define XAM_BOOT_DATA_FLAG_HYBRID_FORCE_GAME    0x00000080
#define XAM_BOOT_DATA_FLAG_HYBRID_NO_NOTIFY     0x00000100

#pragma pack(push, 4)

typedef struct _XAM_BOOT_DATA_BLOCK
{
    //
    // Base (1888) structure
    //

    XAM_BOOT_REASON                     Reason;
    DWORD                               Flags;
    PVOID                               ImagePhysicalBase;
    ULONG                               ImageSize;
    CHAR                                ImageName[XAM_MAX_LAUNCH_PATH];
    CHAR                                DDrive[XAM_MAX_LAUNCH_PATH];
    CHAR                                CommandLine[XAM_MAX_LAUNCH_PATH];

    //
    // Fields added after build 1888
    //

    DWORD                               MinVersion;
} XAM_BOOT_DATA_BLOCK;

#pragma pack(pop)


HRESULT
WINAPI
XMsgAcquireAsyncMessageFromOverlapped(
    IN      PXOVERLAPPED                pOverlapped,
    OUT     PXASYNCMESSAGE*             ppMsg
    );

HRESULT
WINAPI
XMsgReleaseAsyncMessageToOverlapped(
    IN      PXASYNCMESSAGE              pMsg,
    IN      PXOVERLAPPED                pOverlapped
    );


//------------------------------------------------------------------------------
// System-defined string ids used in the SPA file
//------------------------------------------------------------------------------

#define X_STRINGID_TITLE                0x8000


typedef struct
{
    DWORD                               dwTitleId;
    ULONGLONG                           qwId;
    DWORD                               dwUserIndex;
    WCHAR*                              pwsz;
    PDWORD                              pcch;
} XGI_READSTRING_MSG;


//------------------------------------------------------------------------------
// Tiles/Images/Pictures
//------------------------------------------------------------------------------


typedef enum
{
    XTILETYPE_ACHIEVEMENT               = 0,
    XTILETYPE_GAME_ICON                 = 1,
    XTILETYPE_GAMER_TILE                = 2,
    XTILETYPE_GAMER_TILE_SMALL          = 3,
    XTILETYPE_LOCAL_GAMER_TILE          = 4,
    XTILETYPE_LOCAL_GAMER_TILE_SMALL    = 5,
    XTILETYPE_BKGND                     = 6,
    XTILETYPE_AWARDED_GAMER_TILE        = 7,
    XTILETYPE_AWARDED_GAMER_TILE_SMALL  = 8,
    XTILETYPE_GAMER_TILE_BY_IMAGE_ID    = 9,
} XTILETYPE;


#define X_IMAGEID_FLAGS_LARGE           0x00020000
#define X_IMAGEID_FLAGS_SMALL           0x00010000

// number of tiles available to users to pick
#define NUM_FLASH_TILES                 12

// total number of tiles available, including one for xbox 1 users
#define NUM_FLASH_TILES_ALL             NUM_FLASH_TILES + 1

//
// System defined image ids
//

#define X_IMAGEID_DEFAULT_TITLEID       XENON_DASH_TITLE_ID
#define X_IMAGEID_DEFAULT_TILE          0x0 + X_IMAGEID_FLAGS_LARGE
#define X_IMAGEID_DEFAULT_TILE_SMALL    0x0 + X_IMAGEID_FLAGS_SMALL

#define X_IMAGEID_GAME                  0x8000
#define X_IMAGEID_GAMER                 0x8001
#define X_IMAGEID_GAMER_SMALL           0x8002
#define X_IMAGEID_BKGND                 0x8003
#define X_IMAGEID_GAME_MARKETPLACE      0x8004

typedef struct
{
    DWORD                               dwUserIndex;
    DWORD                               dwNumXuids;
    CONST XUID*                         rgXuids;
} XGI_PREPAREGAMERTILES_MSG;

typedef struct
{
    XTILETYPE                           eTileType;
    DWORD                               dwTitleId;              // Used for game tile and achievements
    ULONGLONG                           qwImageId;
    DWORD                               dwUserIndex;            // Used for achievements
    PBYTE                               pbImage;
    PDWORD                              pcbBuffer;
    DWORD                               cbBuffer;
    DWORD                               dwPitch;
    DWORD                               dwHeight;
} XGI_READWRITETILE_MSG;

typedef struct
{
    BOOL                                fForEnumerate;          // Making available for enumeration, or making it the gamer's tile?
    DWORD                               dwUserIndex;
    DWORD                               dwTitleId;              // Title id of the granting title
    DWORD                               dwImageId;              // Image id of the 64x64 tile
    DWORD                               dwImageIdSmall;         // Image id of the 32x32 tile
    BOOL                                fUpdateSetting;         // Update profile setting as a part of writing tile? (only if fForEnumeate = false)
} XGI_WRITEGAMERTILE_MSG;


XBOXAPI
DWORD
WINAPI
XamUserCreateAchievementEnumerator(
    IN      DWORD                       dwTitleId,              // A title in your family or 0 for the current title
    IN      DWORD                       dwUserIndex,            // User index of locally signed-in user making the request
    IN      XUID                        xuidRequestee,          // XUID of remote user whose titles are enumerated (or INVALID_XUID for a local enumeration)
    IN      DWORD                       dwDetailFlags,          // Get the descriptions, etc.
    IN      DWORD                       dwStartingIndex,        // Number of achievements to skip before enumerating
    IN      DWORD                       cItem,                  // Number of achievements to retrieve per enumeration
    OUT     PDWORD                      pcbBuffer,              // Size of buffer needed to enumerate
    OUT     PHANDLE                     ph                      // Handle to created enumerator
    );


XBOXAPI
DWORD
WINAPI
XamUserCreateStatsEnumerator(
    IN      DWORD                       dwTitleId,              // Title id to read stats for, 0 if current
    IN      XGI_STATS_ENUMERATOR_TYPE   enumType,               // Type of enumeration to be performed
    IN      ULONGLONG                   qwPivot,                // Rank, rating to start from, or user to pivot around, depending on type
    IN      DWORD                       dwNumRows,              // Number of rows to retrieve
    IN      DWORD                       dwNumStatsSpecs,        // Number of specs in the pSpecs parameter
    IN      CONST XUSER_STATS_SPEC*     pSpecs,                 // Array of stats specs to retrieve
    OUT     PDWORD                      pcbBuffer,              // Size of buffer needed to enumerate
    OUT     PHANDLE                     ph                      // Handle to created enumerator
    );


XBOXAPI
DWORD
WINAPI
XamUserCreateTitlesPlayedEnumerator(
    IN      DWORD                       dwTitleId,              // A title in your family or 0 for the current title
    IN      DWORD                       dwUserIndex,            // User index of locally signed-in user making the request
    IN      XUID                        xuid,                   // XUID of remote user whose titles are enumerated (or INVALID_XUID for a local enumeration)
    IN      DWORD                       dwStartingIndex,        // Number to skip before enumerating
    IN      DWORD                       cItem,                  // Number to retrieve per enumeration
    OUT     PDWORD                      pcbBuffer,              // Size of buffer needed to enumerate
    OUT     PHANDLE                     ph                      // Handle to created enumerator
    );

void
XamInitFlashTiles(void);

XBOXAPI
DWORD
WINAPI
XamPrepareGamerTiles(
    IN      DWORD                       dwUserIndex,            // User index of user reading gamer tiles
    IN      DWORD                       dwNumXuids,             // number of xuids in rgXuids
    IN      CONST XUID*                 rgXuids                 // List of users to prepare tiles for
    );


XBOXAPI
DWORD
WINAPI
XamReadTile(
    IN      XTILETYPE                   eTileType,
    IN      DWORD                       dwTitleId,
    IN      ULONGLONG                   qwImageId,
    IN      DWORD                       dwUserIndex,            // User index of profile to search in
    IN      PBYTE                       pbImage,
    IN OUT  PDWORD                      pcbBuffer,
    IN OUT  PXOVERLAPPED                pXOverlapped        OPTIONAL
    );


XBOXAPI
DWORD
WINAPI
XamReadTileToTexture(
    IN      XTILETYPE                   eTileType,
    IN      DWORD                       dwTitleId,
    IN      ULONGLONG                   qwImageId,
    IN      DWORD                       dwUserIndex,            // User index of profile to search in
    IN OUT  PBYTE                       pbTextureBuffer,
    IN      DWORD                       dwPitch,
    IN      DWORD                       dwHeight,
    IN OUT  PXOVERLAPPED                pXOverlapped        OPTIONAL
    );


XBOXAPI
DWORD
WINAPI
XamWriteGamerTile(
    IN      DWORD                       dwUserIndex,
    IN      DWORD                       dwTitleId,
    IN      DWORD                       dwImageId,
    IN      DWORD                       dwImageIdSmall,
    IN      BOOL                        fForEnumeration,
    IN OUT  PXOVERLAPPED                pXOverlapped        OPTIONAL
    );


XBOXAPI
DWORD
WINAPI
XamWriteTile(
    IN      XTILETYPE                   eTileType,
    IN      DWORD                       dwTitleId,
    IN      ULONGLONG                   qwImageId,
    IN      DWORD                       dwUserIndex,
    IN      PBYTE                       pbImage,
    IN OUT  DWORD                       cbImage,
    IN OUT  PXOVERLAPPED                pXOverlapped        OPTIONAL
    );


DWORD
WINAPI
XamParseGamerTileKey(
    IN      PXUSER_DATA                 pKey,
    OUT     PDWORD                      pdwTitleId,
    OUT     PDWORD                      pdwImageId,
    OUT     PDWORD                      pdwImageIdSmall
    );


XBOXAPI
DWORD
WINAPI
XamReadString(
    IN      DWORD                       dwTitleId,
    IN      ULONGLONG                   qwStringId,
    IN      DWORD                       dwUserIndex,            // User index of profile to search in
    IN      WCHAR*                      pwsz,
    IN OUT  PDWORD                      pcch,
    IN OUT  PXOVERLAPPED                pXOverlapped        OPTIONAL
    );


XBOXAPI
DWORD
XamGetCachedTitleName(
    IN      DWORD                       dwTitleId,
    OUT     LPWSTR                      pwsz,
    IN OUT  PDWORD                      pcch
    );

XBOXAPI
DWORD
XamGetCachedGamerTag(
    IN      XUID                        xuid,
    OUT     LPSTR                       psz,
    IN OUT  PDWORD                      pcch
    );

XBOXAPI
DWORD
XamGetCachedGamerTagW(
    IN      XUID                        xuid,
    OUT     LPWSTR                      pwsz,
    IN OUT  PDWORD                      pcch
    );

XBOXAPI
HRESULT
WINAPI
XamReadImage(
    IN      DWORD                       dwTileFlags,
    IN      DWORD                       dwTitleId,
    IN      DWORD                       dwUserIndex,
    IN      ULONGLONG                   qwImageId,
    OUT     HXUIBRUSH*                  phBrush
    );


XBOXAPI
HRESULT
WINAPI
XamDecompressPNGToTexture(
    IN      PBYTE                       pbPng,
    IN      DWORD                       cbPng,
    IN      PBYTE                       pbTexture,
    IN      DWORD                       dwPitch,
    IN      DWORD                       dwHeight
    );


//------------------------------------------------------------------------------
// Server synchronization (profile settings, achievements, title list, etc.)
//------------------------------------------------------------------------------

typedef struct
{
    DWORD                               dwUserIndexMask;
} XGI_SYNC_MSG;


XBOXAPI
DWORD
WINAPI
XamUserProfileSync(
    IN      DWORD                       dwUserIndexMask,        // Who to sync (bitmap of user indexes (LSB == user index 0))
    IN OUT  PXOVERLAPPED                pXOverlapped        OPTIONAL
    );


//------------------------------------------------------------------------------
// Title tracking and recovery
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Titles-played list
//------------------------------------------------------------------------------

// The XUSER_TITLE_PLAYED structure defines the info stored for each title
// ever played.  It's used in both the SPIs and as the format stored in a profile
// file.
//
// If this format changes then all existing title records in all profiles will
// be invalidated. That's why there are unused members for adding new info later.
// Just be sure that the size of the structure (including alignment packing)
// remains the same!

typedef struct tagXUSER_TITLE_PLAYED
{
    DWORD                               dwTitleId;

    DWORD                               dwAchievementsPossible;
    DWORD                               dwAchievementsEarned;

    DWORD                               dwCredPossible;
    DWORD                               dwCredEarned;

    DWORD                               dwUnused1;
    DWORD                               dwUnused2;
    DWORD                               dwUnused3;

    FILETIME                            ftLastLoaded;       // Only changed if online

    WCHAR                               wszTitleName[64];   // Includes null-terminator
} XUSER_TITLE_PLAYED;


typedef struct
{
    DWORD                               dwUserIndex;
    CONST XUSER_TITLE_PLAYED*           pTitleToRecover;
} XGI_RECOVERTITLE_MSG;


XBOXAPI
DWORD
WINAPI
XamProfileRecoverTitle(
    IN          DWORD                   dwUserIndex,
    IN CONST    XUSER_TITLE_PLAYED*     pTitleToRecover,
    IN OUT      PXOVERLAPPED            pXOverlapped        OPTIONAL
    );


//------------------------------------------------------------------------------
// Profile settings
//------------------------------------------------------------------------------

XBOXAPI
DWORD
WINAPI
XamUserReadProfileSettings(
    IN      DWORD                       dwTitleId,              // A title in your family or 0 for the current title
    IN      DWORD                       dwUserIndexRequester,   // User index of requesting user.  Used for permission checking.
    IN      DWORD                       dwNumFor,               // Count of XUIDs in pxuidFor
    IN      CONST XUID*                 pxuidFor,               // Pointer to array of XUIDs to request settings for
    IN      DWORD                       dwNumSettingIds,        // Count of setting ids in pdwSettingIds
    IN      CONST DWORD*                pdwSettingIds,          // Pointer to array of settings to retrieve
    IN OUT  DWORD*                      pcbResults,             // Size of pResults buffer.  If *pchResults is 0 then required size is returned.
    IN OUT  PXUSER_READ_PROFILE_SETTING_RESULT pResults,
    IN OUT  PXOVERLAPPED                pXOverlapped        OPTIONAL
    );


XBOXAPI
DWORD
WINAPI
XamUserWriteProfileSettings(
    IN      DWORD                       dwTitleId,
    IN      DWORD                       dwUserIndex,            // User index of player whose settings are written
    IN      DWORD                       dwNumSettings,          // Count of settings in pSettings
    IN      CONST PXUSER_PROFILE_SETTING pSettings,             // Pointer to array of settings to set
    IN      PXOVERLAPPED                pXOverlapped        OPTIONAL
    );


//------------------------------------------------------------------------------
// Messaging UI APIs
//------------------------------------------------------------------------------

XBOXAPI
DWORD
WINAPI
XamShowMessageComposeUI(
    IN      DWORD                       dwUserIndex,
    IN      CONST XUID*                 pXuidRecipients     OPTIONAL,
    IN      UINT                        cRecipients,
    IN      LPCWSTR                     pszText             OPTIONAL
    );

XBOXAPI
DWORD
WINAPI
XamShowGameInviteUI(
    IN      DWORD                       dwUserIndex,
    IN      CONST XUID*                 pXuidRecipients     OPTIONAL,
    IN      UINT                        cRecipients,
    IN      LPCWSTR                     pszText             OPTIONAL
    );

XBOXAPI
DWORD
WINAPI
XamShowFriendRequestUI(
    IN      DWORD                       dwUserIndex,
    IN      XUID                        xuidUser
    );

XBOXAPI
DWORD
WINAPI
XamShowPrivateChatInviteUI(
    IN      DWORD                       dwUserIndex,
    IN      DWORD                       dwChannel
    );


//------------------------------------------------------------------------------
// Virtual keyboard API
//------------------------------------------------------------------------------

typedef struct _XVIRTUALKBDUI_PARAMS
{
    DWORD                               dwUserIndex;
    DWORD                               cchResultText;
    DWORD                               dwFlags;
    LPCWSTR                             pDefaultText;
    LPCWSTR                             pTitleText;
    LPCWSTR                             pDescriptionText;
    LPWSTR                              pResultText;
    PXOVERLAPPED                        pOverlapped;
} XVIRTUALKBDUI_PARAMS, *PXVIRTUALKBDUI_PARAMS;

XBOXAPI
DWORD
WINAPI
XamShowKeyboardUI(
    IN      DWORD                       dwUserIndex,
    IN      DWORD                       dwFlags,
    IN      LPCWSTR                     pDefaultText,
    IN      LPCWSTR                     pTitleText,
    IN      LPCWSTR                     pDescriptionText,
    OUT     LPWSTR                      pResultText,
    IN      DWORD                       cchResultText,
    IN OUT  PXOVERLAPPED                pOverlapped
    );

//------------------------------------------------------------------------------
// QuickChat UI API
//------------------------------------------------------------------------------

typedef struct _XSHOWQUICKCHATUI_PARAMS
{
    DWORD                               dwUserIndex;
} XSHOWQUICKCHATUI_PARAMS, *PXSHOWQUICKCHATUI_PARAMS;

XBOXAPI
DWORD
WINAPI
XamShowQuickChatUI(
    IN      DWORD                       dwUserIndex
    );

//------------------------------------------------------------------------------
// VoiceMail application API
//------------------------------------------------------------------------------
#define XSHOWVOICEMAILUI_RESULTS_NONE           0x00000000
#define XSHOWVOICEMAILUI_RESULTS_RECORDED       0x00000001
#define XSHOWVOICEMAILUI_RESULTS_ACCEPTED       0x00000002

typedef struct _XVOICEMAILUI_RESULTS
{
    DWORD                               dwResults;
    DWORD                               cbRecordedBufferSize;
} XVOICEMAILUI_RESULTS, *PXVOICEMAILUI_RESULTS;

#define XSHOWVOICEMAILUI_FLAGS_PLAYVOICE        0x00000001
#define XSHOWVOICEMAILUI_FLAGS_RECORDVOICE      0x00000002
#define XSHOWVOICEMAILUI_FLAGS_RESERVED1        0x00000004
#define XSHOWVOICEMAILUI_FLAGS_RESERVED2        0x00000008

typedef struct _XVOICEMAILUI_PARAMS
{
    DWORD                               dwUserIndex;
    DWORD                               dwFlags;
    PBYTE                               pbBuffer;
    DWORD                               cbBufferSize;
    DWORD                               cbRecordedBufferSize;
    WORD                                wCodec;
    PXVOICEMAILUI_RESULTS               pResults;
} XVOICEMAILUI_PARAMS, *PXVOICEMAILUI_PARAMS;

XBOXAPI
DWORD
WINAPI
XamShowVoiceMailUI(
    IN      DWORD                       dwUserIndex,
    IN      DWORD                       dwFlags,
    IN      PBYTE                       pbBuffer,
    IN      DWORD                       cbBufferSize,
    IN      DWORD                       cbRecordedBufferSize,
    IN      WORD                        wCodec,
    OUT     PXVOICEMAILUI_RESULTS       pResults
    );


//------------------------------------------------------------------------------
// GamerProfile application API types
//------------------------------------------------------------------------------

#define XGAMERPROFILE_MODE_GAMERCARD    0x00
#define XGAMERPROFILE_MODE_GAMES        0x01
#define XGAMERPROFILE_MODE_ACHIEVEMENTS 0x02
#define XGAMERPROFILE_MODE_EDIT         0x03

typedef struct _XGAMERPROFILE_PARAMS
{
    DWORD                               dwUserIndex;
    DWORD                               dwMode;
    XUID                                xuidTarget;
    DWORD                               dwTitleId;
} XGAMERPROFILE_PARAMS, *PXGAMERPROFILE_PARAMS;

//------------------------------------------------------------------------------
// GamerProfile application APIs
//------------------------------------------------------------------------------

XBOXAPI
DWORD
WINAPI
XamShowGamerCardUI(
    IN      DWORD                       dwUserIndex
    );

XBOXAPI
DWORD
WINAPI
XamShowGamerCardUIForXUID(
    IN      DWORD                       dwUserIndex,
    IN      XUID                        xuidPlayer,
    IN      BOOL                        fDisableChatButton
    );

//
// API to show the Achievements UI
//

XBOXAPI
DWORD
WINAPI
XamShowAchievementsUI(
    IN      DWORD                       dwUserIndex,
    IN      DWORD                       dwTitleId
    );

XBOXAPI
DWORD
WINAPI
XamShowGamesUI(
    IN      DWORD                       dwUserIndex,
    IN      XUID                        xuidTarget
    );

typedef struct _XSHOWFRIENDSUI_PARAMS
{
    DWORD                               dwUserIndex;
    DWORD                               dwFlags;
    XUID                                rgXuidRecipients[100];
    UINT                                cRecipients;
    WCHAR                               szText[256];
    ULONGLONG                           qwParam;
    DWORD                               dwChannel;
} XSHOWFRIENDSUI_PARAMS, *PXSHOWFRIENDSUI_PARAMS;

#define XSHOWFRIENDSUI_FLAGS_SHOWMESSAGES           (0x01)
#define XSHOWFRIENDSUI_FLAGS_COMPOSEMESSAGE         (0x02)
#define XSHOWFRIENDSUI_FLAGS_GAMEINVITE             (0x04)
#define XSHOWFRIENDSUI_FLAGS_FRIENDREQUEST          (0x08)
#define XSHOWFRIENDSUI_FLAGS_SHOWPLAYERS            (0x10)
#define XSHOWFRIENDSUI_FLAGS_GAMERPROFILE           (0x20)
#define XSHOWFRIENDSUI_FLAGS_QUICKCHAT              (0x40)
#define XSHOWFRIENDSUI_FLAGS_DISABLECHAT            (0x80)
#define XSHOWFRIENDSUI_FLAGS_PRIVATECHATINVITE      (0x100)
#define XSHOWFRIENDSUI_FLAGS_SHOWRECENTMESSAGE      (0x200)
#define XSHOWFRIENDSUI_FLAGS_PRIVATECHATCHANNEL     (0x400)
#define XSHOWFRIENDSUI_FLAGS_INVOKEDBYPRIVATECHAT   (0x800)


XBOXAPI
DWORD
WINAPI
XamShowFriendsUI(
    IN      DWORD                       dwUserIndex
    );

XBOXAPI
DWORD
WINAPI
XamShowPlayersUI(
    IN      DWORD                       dwUserIndex
    );

XBOXAPI
DWORD
WINAPI
XamShowMessagesUI(
    IN      DWORD                       dwUserIndex
    );

XBOXAPI
DWORD
WINAPI
XamShowMessagesUIEx(
    IN      DWORD                       dwUserIndex,
    IN      DWORD                       dwFlags
    );    

XBOXAPI
DWORD
WINAPI
XamShowRecentMessageUI(
    IN      DWORD                       dwUserIndex,
    IN      ULONGLONG                   qwParam
    );

XBOXAPI
DWORD
WINAPI
XamShowRecentMessageUIEx(
    IN      DWORD                       dwFlags,
    IN      DWORD                       dwUserIndex,
    IN      ULONGLONG                   qwParam,
    IN      DWORD                       dwChannel
    );    

XBOXAPI
DWORD
WINAPI
XamShowFriendsUIp(
    IN      DWORD                       dwUserIndex,
    IN      DWORD                       dwFlags
    );

typedef struct _XSHOWSIGNINUI_PARAMS
{
    DWORD                               dwUserIndex;
    DWORD                               cPanes;
    DWORD                               dwFlags;
    PXOVERLAPPED                        pOverlapped;
} XSHOWSIGNINUI_PARAMS, *PXSHOWSIGNINUI_PARAMS;

XBOXAPI
DWORD
WINAPI
XamShowSigninUI(
    IN      DWORD                       cPanes,
    IN      DWORD                       dwFlags
    );

XBOXAPI
DWORD
WINAPI
XamShowSigninUIEx(
    IN      DWORD                       cPanes,
    IN      DWORD                       dwFlags,
    IN OUT  PXOVERLAPPED                pxov
    );

XBOXAPI
DWORD
WINAPI
XamShowSigninUIp(
    IN      DWORD                       dwUserIndex,
    IN      DWORD                       cPanes,
    IN      DWORD                       dwFlags
    );

XBOXAPI
DWORD
WINAPI
XamShowPasscodeVerifyUI(
    IN      DWORD                       dwUserIndex,
    OUT     PMESSAGEBOX_RESULT          pResult,
    IN OUT  PXOVERLAPPED                pOverlapped
    );

XBOXAPI
DWORD
WINAPI
XamShowDirtyDiscErrorUI(
    IN      DWORD                       dwUserIndex
    );

//------------------------------------------------------------------------------
// Feedback application APIs
//------------------------------------------------------------------------------

//
// Feedback API
//

#define FEEDBACK_ENTRYPOINT_PLAYERREVIEW    0
#define FEEDBACK_ENTRYPOINT_COMPLAINT       1
#define FEEDBACK_ENTRYPOINT_REPUTATION      2

typedef struct _XSHOWFEEDBACKUI_PARAMS
{
    DWORD                               dwUserIndex;
    XUID                                _xuidFeedbackTarget;
    DWORD                               _dEntryPoint;
} XSHOWFEEDBACKUI_PARAMS, *PXSHOWFEEDBACKUI_PARAMS;

//
// API to show the feedback UI
//

XBOXAPI
DWORD
WINAPI
XamShowPlayerReviewUI(
    IN      DWORD                       dwUserIndex,
    IN      XUID                        XuidFeedbackTarget
    );


XBOXAPI
DWORD
WINAPI
XamShowComplaintUI(
    IN      DWORD                       dwUserIndex,
    IN      XUID                        XuidFeedbackTarget
    );


XBOXAPI
DWORD
WINAPI
XamShowReputationUI(
    IN      DWORD                       dwUserIndex
    );

XBOXAPI
DWORD
WINAPI
XamContentGetMarketplaceCounts(
    IN      DWORD                       dwUserIndex,
    IN      DWORD                       dwContentCategories,
    IN      DWORD                       cbResults,
    IN OUT  XOFFERING_CONTENTAVAILABLE_RESULT*  pResults,
    IN      PXOVERLAPPED                pXOverlapped        OPTIONAL
    );

#define XSHOWMARKETPLACEUI_ACTIVETITLEID    0

typedef struct _MP_BILLING_ACCOUNT_INFO
{
    BOOL fEditMode;
    BYTE bPaymentTypeId;
    WCHAR wszPaymentInstrumentId[MAX_INSTANCE_ID_LENGTH];

    WCHAR wszStreet1[MAX_STREET_SIZE];
    WCHAR wszStreet2[MAX_STREET_SIZE];
    WCHAR wszCity[MAX_CITY_SIZE];
    WCHAR wszDistrict[MAX_DISTRICT_SIZE];
    WCHAR wszState[MAX_STATE_SIZE];
    WCHAR wszPostalCode[MAX_POSTALCODE_SIZE];

    WCHAR wszPhonePrefix[MAX_PHONE_PREFIX_SIZE];
    WCHAR wszPhoneNumber[MAX_PHONE_NUMBER_SIZE];
    WCHAR wszPhoneExtension[MAX_PHONE_EXTENSION_SIZE];

    BYTE bCardTypeId;
    WCHAR wszCreditAccountHolderName[MAX_CC_NAME_SIZE];
    WCHAR wszCreditAccountNumber[MAX_CC_NUMBER_SIZE];
    WCHAR wszCreditCCVNumber[MAX_CC_CCV_NUMBER_SIZE];
    FILETIME ftExpirationDate;

    WCHAR wszDebitAccountHolderName[MAX_DD_NAME_SIZE];
    WCHAR wszDebitAccountNumber[MAX_DD_NUMBER_SIZE];
    WCHAR wszDebitBankCode[MAX_DD_BANK_CODE_SIZE];
    WCHAR wszDebitBranchCode[MAX_DD_BRANCH_CODE_SIZE];
    WCHAR wszDebitCheckDigits[MAX_DD_CHECK_DIGITS_SIZE];
} MP_BILLING_ACCOUNT_INFO, *PMP_BILLING_ACCOUNT_INFO;

typedef struct _XSHOWMARKETPLACEUI_PARAMS
{
    DWORD                               dwUserIndex;
    XUID                                UserXuid;
    DWORD                               dwEntryPoint;
    ULONGLONG                           qwOfferID;
    DWORD                               dwOfferType;
    DWORD                               dwContentCategories;
    DWORD                               dwTitleId;

    BYTE                                bOnlineCountry;
    PMP_BILLING_ACCOUNT_INFO            pBillingInfo;
    PXOVERLAPPED                        pOverlapped;
} XSHOWMARKETPLACEUI_PARAMS, *PXSHOWMARKETPLACEUI_PARAMS;

//
// XamShowMarketplaceUI     - This is a private SPI that will be called by the Dashboard
//                            and the public XShowMarketplaceUI to display and
//                            enumerate content specific to the title specified by the
//                            dwTitleId parameter.
//
//   dwUserIndex            - The index of the currently signed in user for which content
//                            should be displayed
//   dwEntryPoint           - The starting location of the Marketplace HUD UI (See the
//                            XSHOWMARKETPLACEUI_ENTRYPOINTS enum)
//   qwOfferID              - If the entry point is specific to an offer the offering
//                            ID needs to be provided, otherwise this can be 0.
//   dwOfferType            - This can be used to filter the content list by offer type.
//   dwContentCategories    - If the title wishes to display only certain types of
//                            items (i.e. cars, maps, weapons, etc), they can use
//                            this category bit filter.
//   dwTitleId              - The Title Id of the the title that the content should be
//                            displayed for.
//

XBOXAPI
DWORD
WINAPI
XamShowMarketplaceUI(
    IN      DWORD                       dwUserIndex,
    IN      DWORD                       dwEntryPoint,
    IN      ULONGLONG                   qwOfferID,
    IN      DWORD                       dwOfferType,
    IN      DWORD                       dwContentCategories,
    IN      DWORD                       dwTitleId
    );

XBOXAPI
DWORD
WINAPI
XamShowForcedNameChangeUI(
    IN      DWORD                       dwUserIndex
    );

XBOXAPI
DWORD
WINAPI
XamShowSignupCreditCardUI(
    IN      BYTE                        bOnlineCountry,
    IN OUT  PMP_BILLING_ACCOUNT_INFO    pCreditCardInfo,
    IN      BOOL                        fParentCreditCard,
    IN OUT  PXOVERLAPPED                pOverlapped
    );

typedef struct _XSHOWDEVICESELECTORUI_PARAMS
{
    DWORD                               dwUserIndex;
    DWORD                               dwContentType;
    DWORD                               dwContentFlags;
    ULARGE_INTEGER                      uliBytesRequested;
    PXCONTENTDEVICEID                   pDeviceID;
    PXOVERLAPPED                        pOverlapped;
} XSHOWDEVICESELECTORUI_PARAMS, *PXSHOWDEVICESELECTORUI_PARAMS;

XBOXAPI
DWORD
WINAPI
XamShowDeviceSelectorUI(
    IN      DWORD                       dwUserIndex,
    IN      DWORD                       dwContentType,
    IN      DWORD                       dwContentFlags,
    IN      ULARGE_INTEGER              uliBytesRequested,
    OUT     PXCONTENTDEVICEID           pDeviceID,
    IN OUT  PXOVERLAPPED                pOverlapped
    );


//------------------------------------------------------------------------------
// Updater application APIs
//------------------------------------------------------------------------------

#define XSHOWUPDATER_UPDATESOURCE_LIVE      0x00000001
#define XSHOWUPDATER_UPDATESOURCE_GAMEDISC  0x00000002
#define XSHOWUPDATER_UPDATESOURCE_STORAGE   0x00000003
#define XSHOWUPDATER_UPDATESOURCE_CACHE     0x00000004
#define XSHOWUPDATER_UPDATESOURCEMASK       0x0000000F
#define XSHOWUPDATER_LAUNCHING_DASH         0x00000010

typedef struct _XSHOWUPDATERUI_PARAMS
{
    DWORD                               dwUserIndex;
    DWORD                               dwUpdateFlags;
    char                                szUpdatePath[MAX_PATH];
    XEX_EXECUTION_ID                    ExecutionId;
    char                                szTitleToLaunchWhenDone[XAM_MAX_LAUNCH_PATH];
    char                                szTitleToLaunchDDrive[XAM_MAX_LAUNCH_PATH];
} XSHOWUPDATERUI_PARAMS, *PXSHOWUPDATERUI_PARAMS;

XBOXAPI
DWORD
WINAPI
XamShowUpdaterUI(
    IN      DWORD                       dwUserIndex,
    IN      DWORD                       dwUpdateFlags,
    IN      LPCSTR                      pszUpdatePath               OPTIONAL,
    IN      CONST XEX_EXECUTION_ID*     pExecutionId                OPTIONAL,
    IN      LPCSTR                      pszTitleToLaunchWhenDone    OPTIONAL,
    IN      LPCSTR                      pszTitleToLaunchDDrive      OPTIONAL
    );

XBOXAPI
HRESULT
WINAPI
XamUpdateStart(
    IN      CONST CHAR*                 pszUpdatePath               OPTIONAL,
    IN      DWORD                       dwShowUpdaterFlags,
    IN      CONST XEX_EXECUTION_ID*     pExecutionId                OPTIONAL,
    IN      CONST CHAR*                 pszTitleToLaunchWhenDone    OPTIONAL,
    IN      CONST CHAR*                 pszTitleToLaunchDDrive      OPTIONAL,
    OUT     PHANDLE                     phUpdate
    );

XBOXAPI
HRESULT
WINAPI
XamUpdateGetProgress(
    IN      HANDLE                      hUpdate,
    OUT     PDWORD                      pdwUpdateStateId            OPTIONAL,
    OUT     PDWORD                      pdwPercentComplete          OPTIONAL,
    OUT     ULONGLONG*                  pqwNumerator                OPTIONAL,
    OUT     ULONGLONG*                  pqwDenominator              OPTIONAL
    );

XBOXAPI
void
WINAPI
XamUpdateGetExtenderInstance(
    IN      HANDLE                      hUpdate,
    IN      CONST CHAR*                 szSectionName,
    OUT     HINSTANCE*                  phInstance
    );

XBOXAPI
void
WINAPI
XamUpdateFinish(
    IN      HANDLE                      hUpdate
    );

XBOXAPI
HRESULT
WINAPI
XamUpdateAllocateExtenderBuffer(
    IN      HANDLE                      hUpdate,
    IN      DWORD                       dwExtenderSize,
    OUT     BYTE**                      ppbBuffer
    );

XBOXAPI
HRESULT
WINAPI
XamUpdateAttachExtenderInstance(
    IN      HANDLE                      hUpdate,
    IN      HINSTANCE                   hInstance
    );

XBOXAPI
VOID
WINAPI
XamRestartTitleLoadAfterUpdate(
    VOID
    );

XBOXAPI
VOID
WINAPI
XamUIThreadDisableFontPatching(
    VOID
    );

XBOXAPI
VOID
WINAPI
XamUIThreadEnableFontPatching(
    VOID
    );

XBOXAPI
DWORD
WINAPI
XamUpdateGetBaseSystemVersion(
    VOID
    );

XBOXAPI
DWORD
WINAPI
XamUpdateGetCurrentSystemVersion(
    VOID
    );


//------------------------------------------------------------------------------
// MessageBox and Live Upsell UI APIs (both are provided by the HUD sysapp)
//------------------------------------------------------------------------------

#define MESSAGEBOX_OPTION_MESSAGEBOX    0
#define MESSAGEBOX_OPTION_LIVEUPSELL    1

#define XMB_TITLEMAX                    32
#define XMB_TEXTMAX                     256
#define XMB_BUTTONTEXTMAX               32

typedef struct _MESSAGEBOX_PARAMS
{
    DWORD                               dwOption;
    DWORD                               dwUserIndex;
    WCHAR                               szTitle[XMB_TITLEMAX];
    WCHAR                               szText[XMB_TEXTMAX];
    DWORD                               cButtons;
    WCHAR                               rgButtons[XMB_MAXBUTTONS][XMB_BUTTONTEXTMAX];
    DWORD                               dwFocusButton;
    DWORD                               dwFlags;
    PMESSAGEBOX_RESULT                  pResult;
    PXOVERLAPPED                        pOverlapped;
} MESSAGEBOX_PARAMS, *PMESSAGEBOX_PARAMS;

XBOXAPI
DWORD
WINAPI
XamShowMessageBoxUI(
    IN      DWORD                       dwUserIndex,
    IN      LPCWSTR                     pszTitle,
    IN      LPCWSTR                     pszText,
    IN      DWORD                       cButtons,
    IN      LPCWSTR*                    rgButtons,
    IN      DWORD                       dwFocusButton,
    IN      DWORD                       dwFlags,
    OUT     PMESSAGEBOX_RESULT          pResult,
    IN OUT  PXOVERLAPPED                pOverlapped
    );

#define MESSAGEBOXEX_ID_PAL50_INCOMPATIBLE      1

XBOXAPI
DWORD
WINAPI
XamShowMessageBoxUIEx(
    IN      DWORD                       dwUserIndex,
    IN      LPCWSTR                     pszTitle,
    IN      LPCWSTR                     pszText,
    IN      DWORD                       cButtons,
    IN      LPCWSTR*                    rgButtons,
    IN      DWORD                       dwFocusButton,
    IN      DWORD                       dwFlags,
    IN      DWORD                       dwMessageID,
    OUT     PMESSAGEBOX_RESULT          pResult,
    IN OUT  PXOVERLAPPED                pOverlapped
    );

XBOXAPI
DWORD
WINAPI
XamShowLiveUpsellUI(
    VOID
    );


//------------------------------------------------------------------------------
// Create Profile UI API
//------------------------------------------------------------------------------

#define XCREATEPROFILE_MODE_CREATENEW   0x00
#define XCREATEPROFILE_MODE_SIGNUP      0x01
#define XCREATEPROFILE_MODE_RECOVER     0x02

typedef struct _XCREATEPROFILEUI_PARAMS
{
    DWORD                               dwUserIndex;
    DWORD                               dwMode;
    XUID                                xuid;
} XCREATEPROFILEUI_PARAMS, *PXSHOWCREATEPROFILEUI_PARAMS;

#define XENON_SIGNUP_TITLE_ID           0xFFFE07DE

XBOXAPI
DWORD
WINAPI
XamShowCreateProfileUI(
    IN      DWORD                       dwUserIndex
    );

XBOXAPI
DWORD
WINAPI
XamShowLiveSignupUI(
    IN      DWORD                       dwUserIndex,
    IN      BOOL                        fRecoverAccount
    );


//------------------------------------------------------------------------------
// RecentPlayers Cache APIs
//------------------------------------------------------------------------------

XBOXAPI
DWORD
WINAPI
XamUserAddRecentPlayer(
    IN      DWORD                       dwUserIndex,
    IN      XUID                        pUser,
    IN      DWORD                       dwFlags,
    IN      DWORD                       dwTitleID,
    IN      DWORD                       dwRating,
    IN      LPCSTR                      szGamertag
    );


XBOXAPI
DWORD
WINAPI
XamUserUpdateRecentPlayer(
    IN      DWORD                       dwUserIndex,
    IN      XUID                        xuidUser,
    IN      DWORD                       dwFlags,
    IN      DWORD                       dwRating,
    IN      LPCSTR                      szGamertag
    );


XBOXAPI
DWORD
WINAPI
XamUserCreatePlayerEnumerator(
    IN      DWORD                       dwUserIndex,
    IN      DWORD                       dwStartingIndex,
    IN      DWORD                       cItem,
    OUT     PDWORD                      pcbBuffer,
    OUT     PHANDLE                     ph
    );

//------------------------------------------------------------------------------
// Error code helpers
//------------------------------------------------------------------------------

__inline
DWORD
Win32FromHRESULT(
    IN      HRESULT                     hr
    )
{
    DWORD dw;

    if (SUCCEEDED(hr))
    {
        dw = ERROR_SUCCESS;
    }

    else if (FACILITY_WIN32 == HRESULT_FACILITY(hr))
    {
        dw = (hr & ~0xFFFF0000);
    }

    else
    {
        dw = ERROR_FUNCTION_FAILED;
    }

    return dw;
}

//------------------------------------------------------------------------------
// XN_SYS_DISCMEDIACHANGED parameter and support API
//------------------------------------------------------------------------------

#define XDISCMEDIATYPE_NONE             0
#define XDISCMEDIATYPE_GAMEDISC         1
#define XDISCMEDIATYPE_XBOXGAME         2
#define XDISCMEDIATYPE_UNKNOWN          3
#define XDISCMEDIATYPE_DVDA             4
#define XDISCMEDIATYPE_DVD              5
#define XDISCMEDIATYPE_VCD              6
#define XDISCMEDIATYPE_CDAUDIO          7
#define XDISCMEDIATYPE_CDDATA           8
#define XDISCMEDIATYPE_GAMEDVDHYBRID    9

#define MAX_TITLE_TILE                  16384
#define MAX_TITLE_NAME                  23  // Includes null-terminator

typedef struct _XGAMEINFO
{
    DWORD dwTitleId;
    WCHAR wszTitleName[MAX_TITLE_NAME];
} XGAMEINFO, *PXGAMEINFO;

HRESULT
WINAPI
XamGetGameInfo(
    OUT     PXGAMEINFO                  pGameDiscInfo
    );

XBOXAPI
VOID
WINAPI
XamGetMediaInfo(
    DWORD* pdwMediaType,
    DWORD* pdwTitleId
    );

//------------------------------------------------------------------------------
// Inactivity settings SPI
//------------------------------------------------------------------------------

#define XAMINACTIVITY_SCREENSAVER       0
#define XAMINACTIVITY_AUTOSHUTOFF       1
#define XAMINACTIVITY_COUNT             2

#define XAMSCREENSAVER_OFFVALUE         4096
#define XAMSCREENSAVER_ONVALUE          10

HRESULT
WINAPI
XamEnableInactivityProcessing(
    IN      DWORD                       InactivityIndex,
    IN      BOOL                        Enable
    );

HRESULT
WINAPI
XamSetInactivityTime(
    IN      DWORD                       InactivityIndex,
    IN      DWORD                       Minutes
    );

VOID
WINAPI
XamSetInactivityTimeFromConfig(
    DWORD InactivityIndex
    );

VOID
XamResetInactivity(
    VOID
    );

XBOXAPI
BOOL
WINAPI
XamIsSysUiInvokedByXenonButton(
    VOID
    );

XBOXAPI
BOOL
WINAPI
XamIsSysUiInvokedByTitle(
    VOID
    );

XBOXAPI
BOOL
WINAPI
XamIsUIActive(
    VOID
    );

XBOXAPI
VOID
WINAPI
XamSysUiDisableAutoClose(
    BOOL fLeaveOpen
    );

//------------------------------------------------------------------------------
// Power Management SPI
//------------------------------------------------------------------------------

typedef enum _XAMPOWERMODE
{
    XAMPOWERMODE_QUIET                  = 0,
    XAMPOWERMODE_FULL,
} XAMPOWERMODE, *PXAMPOWERMODE;

XBOXAPI
DWORD
WINAPI
XamSetPowerMode(
    IN      XAMPOWERMODE                PowerMode
    );

//------------------------------------------------------------------------------
// Challenge Response SPI
//------------------------------------------------------------------------------

XBOXAPI
DWORD
WINAPI
XamExecuteChallenge(
    IN      PBYTE                       Image,
    IN      DWORD                       ImageSize,
    IN      PBYTE                       Arguments,
    IN      DWORD                       ArgumentsSize,
    IN      PBYTE                       ResultBuffer,
    IN      DWORD                       ResultBufferSize
    );

//-----------------------------------------------------------------------------
// Internal Utility methods that are NOT exported via DLL.
//-----------------------------------------------------------------------------

NTSTATUS
XamQuerySymbolicLink(
    LPCSTR SymbolicLinkName,
    LPSTR  DeviceNameBuffer,
    DWORD  DeviceNameBufferSize
    );


#ifdef __cplusplus
};
#endif


#pragma warning(pop)

#endif // __XAMP_H__
