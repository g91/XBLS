

/*
 * Version 1.1859
 *
 * xonlinep.h
 *
 * This module contains the private definitions for Xbox Live
 *
 * Created on 11/19/05 at 04:36:34.
 */

#ifndef __XONLINEP__
#define __XONLINEP__

#ifdef __cplusplus
extern "C" {
#endif

#include <xonline.h>

//
// Temporary method used to identify titles.  Must be called prior to
// logging on.
//
void
WINAPI
XNetLogonSetTitleID(
    IN DWORD dwTitleID
    );

//
// Internal error codes to forward info within the client logon process
//
#define XONLINE_E_LOGON_NO_IP_ADDRESS                  _HRESULT_TYPEDEF_(0x80151901L)
#define XONLINE_E_LOGON_NO_DNS_SERVICE                 _HRESULT_TYPEDEF_(0x80151902L)
#define XONLINE_E_LOGON_DNS_LOOKUP_FAILED              _HRESULT_TYPEDEF_(0x80151903L)
#define XONLINE_E_LOGON_DNS_LOOKUP_TIMEDOUT            _HRESULT_TYPEDEF_(0x80151904L)
#define XONLINE_E_LOGON_INVALID_XBOX_ONLINE_INFO       _HRESULT_TYPEDEF_(0x80151905L)
#define XONLINE_E_LOGON_MACS_FAILED                    _HRESULT_TYPEDEF_(0x80151906L)
#define XONLINE_E_LOGON_MACS_TIMEDOUT                  _HRESULT_TYPEDEF_(0x80151907L)
#define XONLINE_E_LOGON_AUTHENTICATION_FAILED          _HRESULT_TYPEDEF_(0x80151908L)
#define XONLINE_E_LOGON_AUTHENTICATION_TIMEDOUT        _HRESULT_TYPEDEF_(0x80151909L)
#define XONLINE_E_LOGON_AUTHORIZATION_FAILED           _HRESULT_TYPEDEF_(0x8015190AL)
#define XONLINE_E_LOGON_AUTHORIZATION_TIMEDOUT         _HRESULT_TYPEDEF_(0x8015190BL)
#define XONLINE_E_LOGON_XBOX_ACCOUNT_INVALID           _HRESULT_TYPEDEF_(0x8015190CL)
#define XONLINE_E_LOGON_XBOX_ACCOUNT_BANNED            _HRESULT_TYPEDEF_(0x8015190DL)
#define XONLINE_E_LOGON_SG_SERVICE_FAILED              _HRESULT_TYPEDEF_(0x8015190EL)
#define XONLINE_E_LOGON_PRESENCE_SERVICE_FAILED        _HRESULT_TYPEDEF_(0x8015190FL)
#define XONLINE_E_LOGON_PRESENCE_SERVICE_TIMEDOUT      _HRESULT_TYPEDEF_(0x80151910L)
#define XONLINE_E_LOGON_TIMEDOUT                       _HRESULT_TYPEDEF_(0x80151911L)
#define XONLINE_E_LOGON_UNKNOWN_TITLE                  _HRESULT_TYPEDEF_(0x80151912L)
#define XONLINE_E_LOGON_INTERNAL_ERROR                 _HRESULT_TYPEDEF_(0x80151913L)
#define XONLINE_E_LOGON_MACHINE_AUTHENTICATION_FAILED  _HRESULT_TYPEDEF_(0x80151914L)
#define XONLINE_E_LOGON_TGT_REVOKED                    _HRESULT_TYPEDEF_(0x80151915L)
#define XONLINE_E_LOGON_CACHE_MISS                     _HRESULT_TYPEDEF_(0x80151916L)
#define XONLINE_E_LOGON_NOT_UPNP_NAT                   _HRESULT_TYPEDEF_(0x80151917L)
#define XONLINE_E_LOGON_INCONCLUSIVE_UPNP_NAT          _HRESULT_TYPEDEF_(0x80151918L)
#define XONLINE_E_LOGON_UPNP_NAT_HARD_FAILURE          _HRESULT_TYPEDEF_(0x80151919L)
#define XONLINE_E_LOGON_UPNP_PORT_UNAVAILABLE          _HRESULT_TYPEDEF_(0x8015191AL)

#define XOnlineIsPrivateLogonHR( hr ) (((hr) & 0xFFFFFF00L) == 0x80151900L)

// XUID compatibility macros
#define XOnlineIsUserGuest                              IsGuestXUID

//
// Xbox Live Service ID
//

#define XONLINE_PRESENCE_SERVICE                1
#define XONLINE_STRING_SERVICE                  2
#define XONLINE_AUTO_UPDATE_SERVICE             3
#define XONLINE_CONTENT_AVAILABLE_SERVICE       4
#define XONLINE_BASE_SUBSCRIPTION_SERVICE       XONLINE_CONTENT_AVAILABLE_SERVICE
#define XONLINE_USER_ACCOUNT_SERVICE            5
#define XONLINE_MATCHMAKING_SERVICE             6
#define XONLINE_STATISTICS_SERVICE              7
#define XONLINE_FEEDBACK_SERVICE                8
#define XONLINE_BILLING_OFFERING_SERVICE        9
#define XONLINE_NICKNAME_VERIFICATION_SERVICE   XONLINE_BILLING_OFFERING_SERVICE
#define XONLINE_DIAGNOSTIC_LOGGING_SERVICE      10
#define XONLINE_TOU_SERVICE                     11
#define XONLINE_SIGNATURE_SERVICE               12
#define XONLINE_QUERY_SERVICE                   13
#define XONLINE_NAME_RESOLUTION_SERVICE         14
#define XONLINE_STORAGE_SERVICE                 15
#define XONLINE_ARBITRATION_SERVICE             16
#define XONLINE_USAGE_DATA_SERVICE              17
#define XONLINE_MESSAGING_SERVICE               18
#define XONLINE_TEAM_SERVICE                    19
#define XONLINE_NAT_TYPE_DETECTION_SERVICE      20
#define XONLINE_DRM_SERVICE                     21

// These services are for testing against the SGs
#define XONLINE_SG_SITE_1_AUTH_SERVICE          129
#define XONLINE_SG_SITE_2_AUTH_SERVICE          130
#define XONLINE_SG_SITE_1_TEST_SERVICE          129
#define XONLINE_SG_SITE_2_TEST_SERVICE          130

#define XONLINE_UPNP_NAT_SERVICE                0xFFFFFFFF
#define XONLINE_MAX_SERVICE                     21
#define XONLINE_INVALID_SERVICE                 0

#define XONLINE_S_LOGON_USER_MESSAGE_ENUMERATION_NEEDED _HRESULT_TYPEDEF_(0x001512F1L)

//
// Service info
//
#define XNET_LOGON_SERVICE_INFO_INSECURE        0x0001 // service IP & port is insecure

#pragma pack(push, 4)
typedef struct _XNET_LOGON_SERVICE_INFO
{
    DWORD          dwServiceID;
    IN_ADDR        inaService;
    WORD           wServicePort;
    WORD           wFlags;
} XNET_LOGON_SERVICE_INFO, *PXNET_LOGON_SERVICE_INFO;
#pragma pack(pop)


//
// Logon flags
//
#define XNET_LOGON_FLAG_GET_NEW_TICKETS_ONLY    0x00000001
#define XNET_LOGON_FLAG_UPDATE_SERVICE_ONLY     0x00000002
#define XNET_LOGON_FLAG_REFRESH_TICKETS_ONLY    0x00010000


#define XONLINE_MAX_LOGON_USERS             4

#define XONLINE_GAMERTAG_SIZE               16
#define XONLINE_MAX_GAMERTAG_LENGTH         (XONLINE_GAMERTAG_SIZE - 1)
#define XONLINE_PASSCODE_LENGTH             4
#define XONLINE_USERDOMAIN_SIZE             20
#define XONLINE_MAX_USERDOMAIN_LENGTH       (XONLINE_USERDOMAIN_SIZE - 1)
#define XONLINE_KERBEROSREALM_SIZE          24
#define XONLINE_MAX_KERBEROSREALM_LENGTH    (XONLINE_KERBEROSREALM_SIZE - 1)
#define XONLINE_KEY_LENGTH                  16

//
// A structure that contains the 64-bit XUID plus the user flags
//
#pragma pack(push, 4)
typedef struct _XUIDWITHFLAGS {
    XUID                                qwUserID;
    DWORD                               dwUserFlags;
} XUIDWITHFLAGS, *PXUIDWITHFLAGS;
#pragma pack(pop)

//
// Used in dwUserFlags in XUIDWITHFLAGS
//
#define XONLINE_USER_GUEST_MASK                 0x00000003
#define XONLINE_USER_NOSHOW_RATING_MASK         0x0000001C
#define XONLINE_USER_DISCONNECT_RATING_MASK     0x000000E0
#define XONLINE_USER_COUNTRY_MASK               0x0000ff00
#define XONLINE_USER_VOICE_NOT_ALLOWED          0x00010000
#define XONLINE_USER_PURCHASE_NOT_ALLOWED       0x00020000
#define XONLINE_USER_NICKNAME_NOT_ALLOWED       0x00040000
#define XONLINE_USER_SHARED_CONTENT_NOT_ALLOWED 0x00080000
#define XONLINE_USER_PARENTAL_CONTROLLED        0x01000000

#define XONLINE_USER_MEMBERSHIP_TIER_MASK       0x00F00000

#define XOnlineUserFlagsMembershipTier(dwUserFlags)             ((BYTE)(((dwUserFlags) & XONLINE_USER_MEMBERSHIP_TIER_MASK) >> 20))
#define XOnlineUserFlagsCountryId(dwUserFlags)                  ((BYTE)(((dwUserFlags) & XONLINE_USER_COUNTRY_MASK) >> 8))
#define XOnlineUserFlagsGuestNumber(dwUserFlags)                ((dwUserFlags) & XONLINE_USER_GUEST_MASK)
#define XOnlineUserFlagsSetGuestNumber(dwUserFlags,guestNumber) ((dwUserFlags) = ((dwUserFlags) & ~XONLINE_USER_GUEST_MASK) | (guestNumber & XONLINE_USER_GUEST_MASK))
#define XOnlineUserFlagsIsUserGuest(dwUserFlags)                (((dwUserFlags) & XONLINE_USER_GUEST_MASK) != 0)

//
// Compatibility macros
//
#define XOnlineUserCountryId                    XamUserGetOnlineCountryFromXUID
#define XOnlineUserMembershipTier               XamUserGetMembershipTierFromXUID

//
// Used in dwUserOptions in XNET_LOGON_USER
//
#define XNET_LOGON_USER_OPTION_REQUIRE_PASSCODE 0x00000001

#pragma pack(push, 4)
typedef struct _XNET_LOGON_USER
{
    XUIDWITHFLAGS   xuid;
    DWORD           dwServiceNetworkID;
    CHAR            szGamertag[XONLINE_GAMERTAG_SIZE];
    DWORD           dwUserOptions;
    BYTE            passcode[XONLINE_PASSCODE_LENGTH];
    CHAR            domain[XONLINE_USERDOMAIN_SIZE];
    CHAR            kerberosRealm[XONLINE_KERBEROSREALM_SIZE];
    BYTE            key[XONLINE_KEY_LENGTH];
    HRESULT         hr;
} XNET_LOGON_USER, *PXNET_LOGON_USER;
#pragma pack(pop)

typedef enum _XNET_LOGON_NAT_TYPE
{
    XNET_LOGON_NAT_TYPE_OPEN = 1,
    XNET_LOGON_NAT_TYPE_MODERATE,
    XNET_LOGON_NAT_TYPE_STRICT
} XNET_LOGON_NAT_TYPE;

typedef enum _XNET_LOGON_DNS_TYPE
{
    XNET_LOGON_DNS_MACS,
    XNET_LOGON_DNS_AS,
    XNET_LOGON_DNS_TGS,
    XNET_LOGON_DNS_XDS,
    XNET_LOGON_DNS_MAINTENANCE,
    NUM_XNET_LOGON_DNS_TYPES
} XNET_LOGON_DNS_TYPE;

#define XNET_LOGON_MAX_DNS_NAME_LENGTH  80 // 80 characters, including NULL termination


//
// If 2 or 3 bits are used in any status flag, then the meaning is as follows
//
#define XNET_LOGON_STATUS_INITIAL                       0x0
#define XNET_LOGON_STATUS_START                         0x1
#define XNET_LOGON_STATUS_SUCCESS                       0x2
#define XNET_LOGON_STATUS_FAIL                          0x3
#define XNET_LOGON_STATUS_SOCKET_FAIL                   0x4
#define XNET_LOGON_STATUS_RECV_FAIL                     0x5
#define XNET_LOGON_STATUS_MEMORY_FAIL                   0x6
#define XNET_LOGON_STATUS_TIMEOUT_FAIL                  0x7

//
// Meaning of bits on the Online Logon Status DWORD
//
#define XNET_LOGON_STATUS_XNET_FAILED                   0x00000001
#define XNET_LOGON_STATUS_EEPROM_FAILED                 0x00000002
#define XNET_LOGON_STATUS_GENEALOGY_FAILED              0x00000004
#define XNET_LOGON_STATUS_OUT_OF_MEMORY                 0x00000008
#define XNET_LOGON_STATUS_USER_KEY_INCORRECT            0x00000010

#define XNET_LOGON_STATUS_UPNP_EXCHANGE                 0x00000060
#define XNET_LOGON_STATUS_UPNP_EXCHANGE_SHIFT           5

#define XNET_LOGON_STATUS_MACS_EXCHANGE                 0x00000380
#define XNET_LOGON_STATUS_MACS_EXCHANGE_SHIFT           7

#define XNET_LOGON_STATUS_AS_EXCHANGE                   0x00001C00
#define XNET_LOGON_STATUS_AS_EXCHANGE_SHIFT             10

#define XNET_LOGON_STATUS_TGS_EXCHANGE                  0x0000E000
#define XNET_LOGON_STATUS_TGS_EXCHANGE_SHIFT            13

#define XNET_LOGON_STATUS_MACS_DNS_LOOKUP               0x00030000
#define XNET_LOGON_STATUS_MACS_DNS_LOOKUP_SHIFT         16

#define XNET_LOGON_STATUS_AS_DNS_LOOKUP                 0x000C0000
#define XNET_LOGON_STATUS_AS_DNS_LOOKUP_SHIFT           18

#define XNET_LOGON_STATUS_TGS_DNS_LOOKUP                0x00300000
#define XNET_LOGON_STATUS_TGS_DNS_LOOKUP_SHIFT          20

#define XNET_LOGON_STATUS_MACHINE_ACCOUNT_LOOKUP        0x00C00000
#define XNET_LOGON_STATUS_MACHINE_ACCOUNT_LOOKUP_SHIFT  22

#define XNET_LOGON_STATUS_COMBINED_TICKET_CACHE         0x03000000
#define XNET_LOGON_STATUS_COMBINED_TICKET_CACHE_SHIFT   24

#define XNET_LOGON_STATUS_SERVICE_TICKET_CACHE          0x0C000000
#define XNET_LOGON_STATUS_SERVICE_TICKET_CACHE_SHIFT    26

#define XNET_LOGON_STATUS_SG_EXCHANGE                   0x30000000
#define XNET_LOGON_STATUS_SG_EXCHANGE_SHIFT             28

//
// The following values are not reported with Xbox 360.
//
#define XONLINE_LOGON_STATUS_PRESENCE_EXCHANGE          0xC0000000
#define XONLINE_LOGON_STATUS_PRESENCE_EXCHANGE_SHIFT    30

//
// Macros to get/set a logon status field
//
#define XNetLogonSetStatus(dwStatus, field, status)     (dwStatus = ((dwStatus) & ~(field)) | ((status) << field##_SHIFT));
#define XNetLogonGetStatus(dwStatus, field)             (((dwStatus) & (field)) >> field##_SHIFT)



//
// To load any override information for our live services
//
HRESULT
WINAPI
XNetLogonInitOverrideInfo();

HRESULT
WINAPI
XNetLogonTaskStart(
    IN const XNET_LOGON_USER * pUsers,
    IN DWORD dwFlags
    );

HRESULT
WINAPI
XNetLogonTaskContinue(
    );

void
WINAPI
XNetLogonTaskClose(
    );

XNET_LOGON_USER *
WINAPI
XNetLogonGetLoggedOnUsers(
    );

HRESULT
WINAPI
XNetLogonGetNatType(
    OUT XNET_LOGON_NAT_TYPE * pNatType
    );

HRESULT
WINAPI
XNetLogonGetServiceInfo(
    IN DWORD dwServiceID,
    OUT PXNET_LOGON_SERVICE_INFO pServiceInfo
    );

DWORD *
WINAPI
XNetLogonGetUserPrivileges(
    IN ULONGLONG qwUserId
    );

//
// Override console certificate passed up to Live (devkit only).
// The buffer is expected to contain an XE_CONSOLE_CERTIFICATE structure.
//
BOOL
WINAPI
XNetLogonSetConsoleCertificate(
    IN const BYTE * pbConsoleCertificate,
    IN DWORD dwConsoleCertificateSize
    );

HRESULT
WINAPI
XNetLogonGetMachineID(
    IN OUT ULONGLONG * pqwMachineID
    );

DWORD
WINAPI
XNetLogonGetTitleID(
    IN DWORD dwServiceID
    );

DWORD
WINAPI
XNetLogonGetTitleVersion(
    );

DWORD
WINAPI
XNetLogonGetServiceNetworkID();

void
WINAPI
XNetLogonGetDnsString(
    IN XNET_LOGON_DNS_TYPE DnsType,
    IN OUT char * pszBuffer,
    IN DWORD dwBufferLength
    );

void
WINAPI
XNetLogonGetExtendedStatus(
    OUT DWORD * pdwStatus,
    OUT DWORD * pdwStatusError
    );

BOOL
WINAPI
XNetLogonClearTicketCaches(
    IN DWORD dwFlags
    );

#define XONLINE_SERVICE_INFO_INSECURE       0x0001  // reserved flag, service IP & port is insecure
#define XONLINE_SERVICE_INFO_HOSTNAME_PTR   0x0002  // reserved flag, dwServiceID is a pointer to a hostname string instead

// ====================================================================
// XOnline Teams
//

//
// Team/Team Member structure flags
//

#define XONLINE_TEAM_MSG_RECRUIT                0x00000001
#define XONLINE_TEAM_MSG_GAME_INVITE            0x00000002
#define XONLINE_TEAM_MEMBER_RECRUITED           0x00000004

//
// XOnlineTeamMembersEnumerate flags
//

#define XONLINE_TEAM_SHOW_RECRUITS              0x00000001

typedef enum {
    XONLINE_TEAM_DELETE                    = 0x00000001,
    XONLINE_TEAM_MODIFY_DATA               = 0x00000002,
    XONLINE_TEAM_MODIFY_MEMBER_PERMISSIONS = 0x00000004,
    XONLINE_TEAM_DELETE_MEMBER             = 0x00000008,
    XONLINE_TEAM_RECRUIT_MEMBERS           = 0x00000010,

    XONLINE_TEAM_LIVE_PERMISSIONS_ALL = 0xFFFFFFFF
} XONLINE_TEAM_LIVE_PERMISSIONS;

// for some reason, xlivegen doesn't recgonize double
// or DOUBLE types natively.
typedef double __XLIVEGEN_DOUBLE;


// These settings are neither readable nor writable by titles
#define XPROFILE_PERMISSIONS                                XPROFILEID( XUSER_DATA_TYPE_INT32,      sizeof(DWORD),          0)
#define XPROFILE_GAMER_TYPE                                 XPROFILEID( XUSER_DATA_TYPE_INT32,      sizeof(DWORD),          1)
#define XPROFILE_GAMER_PRESENCE_USER_STATE                  XPROFILEID( XUSER_DATA_TYPE_INT32,      sizeof(DWORD),          7)
#define XPROFILE_GAMERCARD_TIER                             XPROFILEID( XUSER_DATA_TYPE_INT32,      sizeof(DWORD),          58)

// This constant is used to verify a title doesn't try to write to an invalid
// setting id.  BE SURE TO UPDATE THIS IF YOU ADD ANY MORE PROFILE SETTING IDS!
#define XPROFILE_MAX_SETTING_ID                 59

// This is an approximation of the total size of all profile settings.  It's
// important that this size remains smaller than the size of the response
// buffer in SettingsTracker::Sync or the server won't be able to return all
// the settings in one shot.  Until the protocol supports multiple round trips
// to read all the settings this is a limitation we must live with even if it
// means not adding any more settings.
#define XPROFILE_MAX_AGGREGATE_SIZE             ((3 * XPROFILE_SETTING_MAX_SIZE) + \
                                                XPROFILE_SETTING_MAX_PICTURE_KEY_PATH + \
                                                XPROFILE_SETTING_MAX_GAMERCARD_MOTTO + \
                                                (40 * sizeof(DWORD)))

// XPROFILE_GAMERCARD_TIER_OPTIONS == XONLINE_TIER_TYPE.  Do not redefine the values.

// XPROFILE_GAMERCARD_TIER_OPTIONS == XONLINE_TIER_TYPE.  Do not redefine the values.

DWORD
WINAPI
XSessionGetInvitationData (
    IN DWORD                dwUserIndex,
    OUT PXSESSION_INFO      pSessionInfo
    );


//-----------------------------------------------------------------------------
//  Private Session API message structures
//-----------------------------------------------------------------------------

// This struct is stored in a session handle
// It only contains a pointer to the SessionTracker object allocated in
// XGI for now, but I've defined a struct for ease of expansion and for
// more legible code.
typedef struct tagSESSION_STRUCT
{
    void*           pSessionTracker;
} SESSION_STRUCT;

typedef struct
{
    SESSION_STRUCT* pSessionStruct;
    DWORD           dwFlags;
    DWORD           dwMaxPublicSlots;
    DWORD           dwMaxPrivateSlots;
    DWORD           dwUserIndex;
    PXSESSION_INFO  pSessionInfo;
    ULONGLONG*      pqwSessionNonce;
} XGI_SESSIONCREATE_MSG;

typedef struct
{
    SESSION_STRUCT* pSessionStruct;
    DWORD           dwFlags;
    DWORD           dwMaxPublicSlots;
    DWORD           dwMaxPrivateSlots;
} XGI_SESSIONMODIFY_MSG;

typedef struct
{
    SESSION_STRUCT* pSessionStruct;
    DWORD           dwUsers;
    const XUID*     pXuids;
    const DWORD*    pdwUserIndexes;
    const BOOL*     pfPrivateSlots;
} XGI_SESSIONMANAGE_MSG;

typedef struct
{
    SESSION_STRUCT* pSessionStruct;
    DWORD           dwFlags;
    ULONGLONG       qwSessionNonce;
} XGI_SESSIONSTATE_MSG;

typedef struct
{
    SESSION_STRUCT* pSessionStruct;
    DWORD           dwFlags;
    ULONGLONG       qwSessionNonce;
    DWORD           dwSessionDurationSec;
    DWORD           cbResultsBuffer;
    PXSESSION_REGISTRATION_RESULTS pResults;
} XGI_SESSIONREGISTER_MSG;

typedef struct
{
    DWORD           dwProcedureIndex;
    DWORD           dwUserIndex;
    DWORD           dwNumResults;
    WORD            wNumProperties;
    WORD            wNumContexts;
    PXUSER_PROPERTY pSearchProperties;
    PXUSER_CONTEXT  pSearchContexts;
    DWORD           cbResultsBuffer;
    PXSESSION_SEARCHRESULT_HEADER pSearchResults;
} XGI_SESSIONSEARCH_MSG;

typedef struct
{
    DWORD           dwProcedureIndex;
    DWORD           dwUserIndex;
    DWORD           dwNumResults;
    WORD            wNumProperties;
    WORD            wNumContexts;
    PXUSER_PROPERTY pSearchProperties;
    PXUSER_CONTEXT  pSearchContexts;
    DWORD           cbResultsBuffer;
    PXSESSION_SEARCHRESULT_HEADER pSearchResults;
    DWORD           dwNumUsers;
} XGI_SESSIONSEARCHEX_MSG;

typedef struct
{
    DWORD           dwUserIndex;
    XNKID           sessionID;
    DWORD           cbResultsBuffer;
    PXSESSION_SEARCHRESULT_HEADER pSearchResults;
} XGI_SESSIONSEARCHBYID_MSG;

typedef struct
{
    DWORD           dwUserIndex;
    PXSESSION_INFO  pSessionInfo;
} XGI_SESSIONINVITE_MSG;

typedef struct
{
    SESSION_STRUCT*                 pSessionStruct;
    XUID                            xuid;
    DWORD                           dwNumViews;
    CONST XSESSION_VIEW_PROPERTIES* pViews;
} XGI_STATSWRITE_MSG;


//-----------------------------------------------------------------------------
//  Session APIs
//-----------------------------------------------------------------------------

#define XSESSION_SEARCH_BY_ID_PROC          0xFFFFFFFF  // Global query to find a session by session ID. Available in all titles. Param 0 must be SessionID

#define XSESSION_CREATE_PRIVATE_MODIFIERS_MASK          0x00001000
#define XSESSION_CREATE_PRIVATE_FORCE_UDP               0x00001000  // Arbitrated session results will only be reported in udp


//-----------------------------------------------------------------------------
//  Mute List APIs
//-----------------------------------------------------------------------------


typedef struct _XUSER_MUTELIST_REQUEST
{
    DWORD        dwUserIndex;
    XUID         Xuid;
    DWORD        dwResult;
} XUSER_MUTELIST_REQUEST;

XBOXAPI
DWORD
WINAPI
XUserpMuteListAdd(
    DWORD       dwUserIndex,
    XUID        XuidRemoteTalker
    );

XBOXAPI
DWORD
WINAPI
XUserpMuteListRemove(
    DWORD       dwUserIndex,
    XUID        XuidRemoteTalker
    );


//-----------------------------------------------------------------------------
//  Private Arbitration APIs
//-----------------------------------------------------------------------------


#define XARB_FLAG_IS_TOURNAMENT                     0x0001
#define XARB_FLAG_CAN_EXTEND_TIME                   0x0002
#define XARB_FLAG_USES_SESSION_HOST                 0x0004
#define XARB_FLAG_FOR_TEAMS                         0x0008
#define XARB_FLAG_FFA                               0x0010
#define XARB_FLAG_IS_PUBLISHER_TOURNAMENT           0x0020

#define XARB_FLAG_I_VOLUNTARILY_QUIT                0x8000
#define XARB_FLAG_I_WAS_HOST                        0x4000
#define XARB_FLAG_LOST_CONNECTIVITY                 0x2000
#define XARB_FLAG_LOST_CONNECTIVITY_SUBMITTED       0x1000
#define XARB_FLAG_TYPE_1_SUSPICIOUS_INFO_SUBMITTED  0x0800
#define XARB_FLAG_TYPE_2_SUSPICIOUS_INFO_SUBMITTED  0x0400
#define XARB_FLAG_TYPE_3_SUSPICIOUS_INFO_SUBMITTED  0x0200
#define XARB_FLAG_STATS_BUNDLE_SUBMITTED            0x0100
#define XARB_FLAG_TOURNAMENT_BUNDLE_SUBMITTED       0x0080

extern const CHAR *rgszFunctionNames[];

#define ORDINAL_0206_XFriendsCreateEnumerator                 (WORD)0x0206
#define ORDINAL_0586_XInviteGetAcceptedInfo                   (WORD)0x0586
#define ORDINAL_0583_XInviteSend                              (WORD)0x0583
#define ORDINAL_000b_XPresenceCreateEnumerator                (WORD)0x000b
#define ORDINAL_0010_XPresenceInitialize                      (WORD)0x0010
#define ORDINAL_000d_XPresenceSubscribe                       (WORD)0x000d
#define ORDINAL_000e_XPresenceUnsubscribe                     (WORD)0x000e
#define ORDINAL_0e15_XStorageDelete                           (WORD)0x0e15
#define ORDINAL_0e11_XStorageDownloadToMemory                 (WORD)0x0e11
#define ORDINAL_0e14_XStorageEnumerate                        (WORD)0x0e14
#define ORDINAL_0e13_XStorageUploadFromMemory                 (WORD)0x0e13
#define ORDINAL_0801_XStringVerify                            (WORD)0x0801
#define ORDINAL_0914_XContentDownload                         (WORD)0x0914
#define ORDINAL_0917_XContentDownloadGetInProgressMetadata    (WORD)0x0917
#define ORDINAL_0913_XContentGetReferral                      (WORD)0x0913
#define ORDINAL_0916_XContentRefreshLicense                   (WORD)0x0916
#define ORDINAL_0915_XContentRefreshLicenseSubTask            (WORD)0x0915
#define ORDINAL_0207_XFriendsRequestWorker                    (WORD)0x0207
#define ORDINAL_0584_XInviteAnswer                            (WORD)0x0584
#define ORDINAL_0585_XInviteRevoke                            (WORD)0x0585
#define ORDINAL_0587_XInviteSendMessage                       (WORD)0x0587
#define ORDINAL_0800_XLookupTitleName                         (WORD)0x0800
#define ORDINAL_0506_XMessageCreate                           (WORD)0x0506
#define ORDINAL_0511_XMessageDelete                           (WORD)0x0511
#define ORDINAL_0505_XMessageDeleteWorker                     (WORD)0x0505
#define ORDINAL_0507_XMessageDestroy                          (WORD)0x0507
#define ORDINAL_050f_XMessageDetailsGetProperty               (WORD)0x050f
#define ORDINAL_050e_XMessageDetailsGetSummary                (WORD)0x050e
#define ORDINAL_05a1_XMessageDownloadAttachmentToMemory       (WORD)0x05a1
#define ORDINAL_0501_XMessageEnumerate                        (WORD)0x0501
#define ORDINAL_0513_XMessageEnumerateWorker                  (WORD)0x0513
#define ORDINAL_050d_XMessageGetDetails                       (WORD)0x050d
#define ORDINAL_0503_XMessageGetDetailsWorker                 (WORD)0x0503
#define ORDINAL_0509_XMessageGetProperty                      (WORD)0x0509
#define ORDINAL_0502_XMessageGetSummary                       (WORD)0x0502
#define ORDINAL_0514_XMessageGetSummaryWorker                 (WORD)0x0514
#define ORDINAL_0581_XMessageInviteAnswerWorker               (WORD)0x0581
#define ORDINAL_0582_XMessageInviteRevokeWorker               (WORD)0x0582
#define ORDINAL_0580_XMessageInviteSendWorker                 (WORD)0x0580
#define ORDINAL_050b_XMessageRevoke                           (WORD)0x050b
#define ORDINAL_0512_XMessageSend                             (WORD)0x0512
#define ORDINAL_050a_XMessageSendWorker                       (WORD)0x050a
#define ORDINAL_0510_XMessageSetFlags                         (WORD)0x0510
#define ORDINAL_0504_XMessageSetFlagsWorker                   (WORD)0x0504
#define ORDINAL_0508_XMessageSetProperty                      (WORD)0x0508
#define ORDINAL_0100_XOnlineMatchCreate                       (WORD)0x0100
#define ORDINAL_0102_XOnlineMatchDelete                       (WORD)0x0102
#define ORDINAL_0006_XOnlineMatchRegisterSession              (WORD)0x0006
#define ORDINAL_0104_XOnlineMatchSearch                       (WORD)0x0104
#define ORDINAL_0101_XOnlineMatchUpdate                       (WORD)0x0101
#define ORDINAL_0300_XOnlineQueryAdd                          (WORD)0x0300
#define ORDINAL_0306_XOnlineQueryFindFromIds                  (WORD)0x0306
#define ORDINAL_0301_XOnlineQueryRemove                       (WORD)0x0301
#define ORDINAL_0302_XOnlineQueryRemoveId                     (WORD)0x0302
#define ORDINAL_0305_XOnlineQuerySearch                       (WORD)0x0305
#define ORDINAL_0307_XOnlineQuerySelect                       (WORD)0x0307
#define ORDINAL_0303_XOnlineQueryUpdate                       (WORD)0x0303
#define ORDINAL_0304_XOnlineQueryUpdateId                     (WORD)0x0304
#define ORDINAL_0400_XOnlineTeamCreate                        (WORD)0x0400
#define ORDINAL_0401_XOnlineTeamDelete                        (WORD)0x0401
#define ORDINAL_0407_XOnlineTeamEnumerate                     (WORD)0x0407
#define ORDINAL_0408_XOnlineTeamEnumerateByUserXUID           (WORD)0x0408
#define ORDINAL_0404_XOnlineTeamJoin                          (WORD)0x0404
#define ORDINAL_0402_XOnlineTeamMemberRecruit                 (WORD)0x0402
#define ORDINAL_0403_XOnlineTeamMemberRecruitByName           (WORD)0x0403
#define ORDINAL_0405_XOnlineTeamMemberRemove                  (WORD)0x0405
#define ORDINAL_0406_XOnlineTeamMemberSetProperties           (WORD)0x0406
#define ORDINAL_0409_XOnlineTeamMembersEnumerate              (WORD)0x0409
#define ORDINAL_040a_XOnlineTeamSetProperties                 (WORD)0x040a
#define ORDINAL_0203_XOnlinepFriendsAcceptRequest             (WORD)0x0203
#define ORDINAL_0204_XOnlinepFriendsRejectRequest             (WORD)0x0204
#define ORDINAL_0202_XOnlinepFriendsRemove                    (WORD)0x0202
#define ORDINAL_0200_XOnlinepFriendsRequest                   (WORD)0x0200
#define ORDINAL_0201_XOnlinepFriendsRequestByName             (WORD)0x0201
#define ORDINAL_0a00_XOnlinepMuteListAdd                      (WORD)0x0a00
#define ORDINAL_0a01_XOnlinepMuteListRemove                   (WORD)0x0a01
#define ORDINAL_0003_XOnlinepNotificationSendDequeue          (WORD)0x0003
#define ORDINAL_0009_XOnlinepPeerSubscribe                    (WORD)0x0009
#define ORDINAL_000a_XOnlinepPeerUnsubscribe                  (WORD)0x000a
#define ORDINAL_0600_XOnlinepSetUserSettings2                 (WORD)0x0600
#define ORDINAL_0008_XPresenceGetLocalSession                 (WORD)0x0008
#define ORDINAL_0007_XPresenceGetPeerSession                  (WORD)0x0007
#define ORDINAL_000c_XPresenceGetState                        (WORD)0x000c
#define ORDINAL_0002_XPresenceSendAlives                      (WORD)0x0002
#define ORDINAL_000f_XPresenceSendDeadUsers                   (WORD)0x000f
#define ORDINAL_0004_XPresenceSetState                        (WORD)0x0004
#define ORDINAL_0005_XPresenceUpdateStateFlags                (WORD)0x0005
#define ORDINAL_0d01_XResolveName                             (WORD)0x0d01
#define ORDINAL_0c02_XSignatureCheckRevocation                (WORD)0x0c02
#define ORDINAL_0c01_XSignatureVerify                         (WORD)0x0c01
#define ORDINAL_0e04_XStorageDeleteWorker                     (WORD)0x0e04
#define ORDINAL_0e10_XStorageDownloadToDirectoryInternal      (WORD)0x0e10
#define ORDINAL_0e01_XStorageDownloadWorker                   (WORD)0x0e01
#define ORDINAL_0e03_XStorageEnumerateWorker                  (WORD)0x0e03
#define ORDINAL_0e12_XStorageUploadFromDirectoryInternal      (WORD)0x0e12
#define ORDINAL_0e02_XStorageUploadWorker                     (WORD)0x0e02
#define ORDINAL_0802_XStringLookup                            (WORD)0x0802
#define ORDINAL_0952_XUpdateDownload                          (WORD)0x0952
#define ORDINAL_0951_XUpdateGetReferral                       (WORD)0x0951
#define ORDINAL_0b00_XUserAddAffiliate                        (WORD)0x0b00
#define ORDINAL_1003_XUserEnumerateReceivedReviews            (WORD)0x1003
#define ORDINAL_1002_XUserEnumerateSentReviews                (WORD)0x1002
#define ORDINAL_0a02_XUserFindUser                            (WORD)0x0a02
#define ORDINAL_1004_XUserGetAggregateReviews                 (WORD)0x1004
#define ORDINAL_0b01_XUserIsAffiliate                         (WORD)0x0b01
#define ORDINAL_0b02_XUserQueryAffiliate                      (WORD)0x0b02
#define ORDINAL_1005_XUserSubmitComplaint                     (WORD)0x1005
#define ORDINAL_1001_XUserSubmitPlayerReview                  (WORD)0x1001
#define ORDINAL_0621__XAccountAcceptTermsOfUse                (WORD)0x0621
#define ORDINAL_061f__XAccountAcknowledgeDowngrade            (WORD)0x061f
#define ORDINAL_060c__XAccountAddPaymentInstrument            (WORD)0x060c
#define ORDINAL_061a__XAccountChangeGamertag                  (WORD)0x061a
#define ORDINAL_061c__XAccountChangeSubscriptionPaymentInstrument (WORD)0x061c
#define ORDINAL_061b__XAccountCreateLiveAccount               (WORD)0x061b
#define ORDINAL_060a__XAccountCreateLiveAccountOld            (WORD)0x060a
#define ORDINAL_0611__XAccountGetAccountInfo                  (WORD)0x0611
#define ORDINAL_0627__XAccountGetAccountInfoFromPassport      (WORD)0x0627
#define ORDINAL_060e__XAccountGetLinkedGamertag               (WORD)0x060e
#define ORDINAL_060b__XAccountGetPaymentInstruments           (WORD)0x060b
#define ORDINAL_0602__XAccountGetPointsBalance                (WORD)0x0602
#define ORDINAL_0614__XAccountGetPostalCode                   (WORD)0x0614
#define ORDINAL_0604__XAccountGetUserInfo                     (WORD)0x0604
#define ORDINAL_0616__XAccountGetUserSubscriptionDetails      (WORD)0x0616
#define ORDINAL_0624__XAccountGetUserType                     (WORD)0x0624
#define ORDINAL_0625__XAccountLinkXbox1Account                (WORD)0x0625
#define ORDINAL_0618__XAccountMigrateXbox1User                (WORD)0x0618
#define ORDINAL_0626__XAccountMigrateXboxComUser              (WORD)0x0626
#define ORDINAL_0620__XAccountQuery                           (WORD)0x0620
#define ORDINAL_0605__XAccountRecoverAccount                  (WORD)0x0605
#define ORDINAL_060d__XAccountRemovePaymentInstrument         (WORD)0x060d
#define ORDINAL_0619__XAccountReserveGamertag                 (WORD)0x0619
#define ORDINAL_0610__XAccountSetAccountInfo                  (WORD)0x0610
#define ORDINAL_0622__XAccountSetStatus                       (WORD)0x0622
#define ORDINAL_061e__XAccountTroubleshoot                    (WORD)0x061e
#define ORDINAL_0601__XAccountUpdateParentalControls          (WORD)0x0601
#define ORDINAL_0615__XAccountUpdatePaymentInstrument         (WORD)0x0615
#define ORDINAL_0623__XAccountVerifyBillingInfo               (WORD)0x0623
#define ORDINAL_0617__XAccountVerifyBillingToken              (WORD)0x0617
#define ORDINAL_061d__XAccountVerifyParentCreditCard          (WORD)0x061d
#define ORDINAL_0909__XBannerGetHotList                       (WORD)0x0909
#define ORDINAL_0908__XBannerGetList                          (WORD)0x0908
#define ORDINAL_0902__XOfferingContentAvailable               (WORD)0x0902
#define ORDINAL_0901__XOfferingContentDetails                 (WORD)0x0901
#define ORDINAL_0900__XOfferingContentEnumerate               (WORD)0x0900
#define ORDINAL_0912__XOfferingEnumerateGenres                (WORD)0x0912
#define ORDINAL_0911__XOfferingEnumerateTitlesByFilter        (WORD)0x0911
#define ORDINAL_0910__XOfferingGetTitleDetails                (WORD)0x0910
#define ORDINAL_0903__XOfferingInternalUpdateAccessTimes      (WORD)0x0903
#define ORDINAL_0906__XOfferingPurchase                       (WORD)0x0906
#define ORDINAL_0907__XOfferingPurchaseGamertag               (WORD)0x0907
#define ORDINAL_0905__XOfferingSubscriptionDetails            (WORD)0x0905
#define ORDINAL_0904__XOfferingSubscriptionEnumerate          (WORD)0x0904
#define ORDINAL_0f00__XOnlineArbitrationRegister              (WORD)0x0f00
#define ORDINAL_0f02__XOnlineArbitrationReportResult          (WORD)0x0f02
#define ORDINAL_0f01__XOnlineArbitrationTimeExtend            (WORD)0x0f01
#define ORDINAL_070e__XOnlineStatsEnumerateByRank             (WORD)0x070e
#define ORDINAL_070f__XOnlineStatsEnumerateByRating           (WORD)0x070f
#define ORDINAL_070d__XOnlineStatsEnumerateByXuid             (WORD)0x070d
#define ORDINAL_0705__XOnlineStatsPost                        (WORD)0x0705
#define ORDINAL_0703__XOnlineStatsRead                        (WORD)0x0703
#define ORDINAL_0706__XOnlineStatsReset                       (WORD)0x0706
#define ORDINAL_0609__XPassportChangePasswordInternal         (WORD)0x0609
#define ORDINAL_0607__XPassportCreateInternal                 (WORD)0x0607
#define ORDINAL_0606__XPassportGetEncryptedProxyParameters    (WORD)0x0606
#define ORDINAL_0613__XPassportGetMemberName                  (WORD)0x0613
#define ORDINAL_060f__XPassportGetSecretQuestions             (WORD)0x060f
#define ORDINAL_0612__XPassportGetUserData                    (WORD)0x0612
#define ORDINAL_0608__XPassportLoginInternal                  (WORD)0x0608
#define ORDINAL_0709__XProfileClearTitle                      (WORD)0x0709
#define ORDINAL_070b__XProfileEnumAchievements                (WORD)0x070b
#define ORDINAL_0708__XProfileEnumTitles                      (WORD)0x0708
#define ORDINAL_0711__XProfileReadOnlineSettings              (WORD)0x0711
#define ORDINAL_070a__XProfileSyncAchievements                (WORD)0x070a
#define ORDINAL_0710__XProfileSyncOnlineSettings              (WORD)0x0710
#define ORDINAL_0707__XProfileSyncTitles                      (WORD)0x0707

#define X_ATTRIBUTE_DATATYPE_MASK                        0x00f00000
#define X_ATTRIBUTE_DATATYPE_INTEGER                     0x00000000
#define X_ATTRIBUTE_DATATYPE_STRING                      0x00100000
#define X_ATTRIBUTE_DATATYPE_BLOB                        0x00200000
#define X_MAX_STRING_ATTRIBUTE_LEN                       400
#define X_MAX_BLOB_ATTRIBUTE_LEN                         800
#define XONLINE_MATCH_MAX_ATTRIBUTES                     64
#define XONLINE_MATCH_MAX_SEARCH_RESULTS                 50
#define MAX_GAMERTAG_SIZE                                16
#define MAX_FRIENDS                                      100
#define MAX_MUTELISTUSERS                                250
#define NOTIF_NUM_NOTIFICATIONS                          12
#define NOTIF_MAX_QVAL                                   16
#define NOTIF_MAX_TITLE_STATE_BYTES                      8
#define NOTIF_MAX_NICKNAME_BYTES                         24
#define NOTIF_MAX_RICH_PRESENCE_BYTES                    128
#define MAX_TITLE_STATE_BYTES                            256
#define PQUEUE_BUDDY_REQ                                 0
#define PQUEUE_LIST_CHANGE                               1
#define PQUEUE_PRESENCE                                  2
#define PQUEUE_INVITE                                    3
#define PQUEUE_INVITE_ANSWER                             4
#define PQUEUE_PEER_PRESENCE                             6
#define PQUEUE_PRESENCE_2                                7
#define PQUEUE_LOCAL_INVITED                             16
#define PQUEUE_LOCAL_INVITE_ANSWERED                     17
#define PQUEUE_LOCAL_INVITE_REVOKED                      18
#define XONLINE_MAX_PARENTAL_CONTROL_SOURCE_NAME_LENGTH  100
#define MAX_FIRSTNAME_SIZE                               64
#define MAX_LASTNAME_SIZE                                64
#define MAX_EMAIL_SIZE                                   129
#define MAX_PHONE_PREFIX_SIZE                            12
#define MAX_PHONE_NUMBER_SIZE                            12
#define MAX_PHONE_EXTENSION_SIZE                         12
#define MAX_STREET_SIZE                                  128
#define MAX_CITY_SIZE                                    64
#define MAX_DISTRICT_SIZE                                64
#define MAX_STATE_SIZE                                   64
#define MAX_POSTALCODE_SIZE                              16
#define MAX_CC_NAME_SIZE                                 64
#define MAX_CC_NUMBER_SIZE                               24
#define MAX_CC_CCV_NUMBER_SIZE                           4
#define MAX_DD_NAME_SIZE                                 64
#define MAX_DD_NUMBER_SIZE                               24
#define MAX_DD_BANK_CODE_SIZE                            64
#define MAX_DD_BRANCH_CODE_SIZE                          64
#define MAX_DD_CHECK_DIGITS_SIZE                         64
#define MAX_TOKEN_SIZE                                   26
#define MAX_INSTANCE_ID_LENGTH                           17
#define XONLINE_USERDOMAIN_SIZE                          20
#define XONLINE_REALM_NAME_SIZE                          24
#define XONLINE_KEY_LENGTH                               16
#define XONLINE_PASSPORT_MEMBER_NAME_MAX_LEN             113
#define XONLINE_PASSPORT_SECRET_QUESTION_MIN_LEN         5
#define XONLINE_PASSPORT_SECRET_QUESTION_MAX_LEN         64
#define XONLINE_PASSPORT_LOGIN_TOKEN_REQUEST_MAX_LEN     2000
#define XONLINE_PASSPORT_PUBLIC_KEY_MODULUS_MAX_LEN      128
#define XONLINE_PASSPORT_ENCRYPTED_PASSWORD_MAX_LEN      384
#define XONLINE_PASSPORT_ENCRYPTED_SESSION_KEY_MAX_LEN   128
#define XONLINE_PASSPORT_SECRET_QUESTION_MAX_COUNT       10
#define XONLINE_XUACS_MAX_PAYMENT_INSTRUMENTS            10
#define XONLINE_XUACS_MAX_POSTAL_CODE_MATCHES            20
#define XONLINE_XUACS_MAX_SUBSCRIPTION_DESCRIPTION_LENGTH 500
#define XONLINE_XUACS_MAX_SUBSCRIPTION_FRIENDLY_NAME_LENGTH 50
#define XONLINE_XUACS_MAX_ISO_CODE_LENGTH                3
#define XONLINE_XUACS_MAX_FORMATTED_PRICE_LENGTH         20
#define XONLINE_XBOS_MAX_OFFER_PRICE_TEXT_LENGTH         50
#define XONLINE_XBOS_MAX_OFFER_NAME_LENGTH               100
#define XONLINE_XBOS_MAX_PRICES_PER_OFFER                10
#define XONLINE_XBOS_MAX_OFFERS_ENUMERATED               100
#define XONLINE_XBOS_MAX_TITLES_ENUMERATED               100
#define XONLINE_XBOS_MAX_OFFER_SELL_TEXT_LENGTH          1000
#define XONLINE_XBOS_MAX_TITLE_NAME_LENGTH               100
#define XONLINE_CONTENT_ID_LEN                           20
#define XONLINE_XBOS_MAX_TITLE_TITLE_LENGTH              60
#define XONLINE_XBOS_MAX_TITLE_SELL_TEXT_LENGTH          1000
#define XONLINE_XBOS_MAX_TITLE_DEVELOPER_LENGTH          60
#define XONLINE_XBOS_MAX_TITLE_PUBLISHER_LENGTH          60
#define XONLINE_XBOS_MAX_TITLE_GENRE_LENGTH              60
#define XONLINE_XBOS_MAX_GENRE_NAME_LENGTH               255
#define XONLINE_XBOS_MAX_GENRES_ENUMERATED               50
#define XONLINE_BANNER_MAX_COUNT                         128
#define XONLINE_BANNER_MAX_PATH                          128
#define XONLINE_BANNER_MAX_TITLE_NAME                    200
#define XONLINE_BANNER_MAX_OFFER_NAME                    200
#define XONLINE_QUERY_MAX_ATTRIBUTES                     32
#define XONLINE_QUERY_MAX_STRING_ATTRIBUTE_LEN           128
#define XONLINE_QUERY_MAX_BLOB_ATTRIBUTE_LEN             128
#define XONLINE_QUERY_MAX_FIND_NUM_ENTITYIDS             10
#define XONLINE_MAX_TEAM_COUNT                           8
#define XONLINE_MAX_TEAM_MEMBER_COUNT                    64
#define XONLINE_MAX_TEAM_NAME_SIZE                       16
#define XONLINE_MAX_TEAM_DESCRIPTION_SIZE                256
#define XONLINE_MAX_TEAM_MOTTO_SIZE                      256
#define XONLINE_MAX_TEAM_URL_SIZE                        256
#define XONLINE_MAX_TEAM_NAME_BYTES                      32
#define XONLINE_MAX_TEAM_DESCRIPTION_BYTES               512
#define XONLINE_MAX_TEAM_MOTTO_BYTES                     512
#define XONLINE_MAX_TEAM_URL_BYTES                       512
#define XONLINE_MAX_TEAM_DATA_SIZE                       100
#define XONLINE_MAX_TEAM_MEMBER_DATA_SIZE                100
#define XPROFILE_SETTING_MAX_COUNT                       32
#define XPROFILE_SETTING_MAX_READ_USERS                  16
#define XPROFILE_SETTING_MAX_RETURN_SETTINGS             512
#define XPROFILE_MAX_SYNC_SETTINGS_REQUEST               32
#define XPROFILE_MAX_SYNC_SETTINGS_RESULTS               128
#define XPROFILE_SETTING_MAX_SIZE                        1000
#define XONLINE_STAT_ATTRS_IN_SPEC                       64
#define XONLINE_STAT_MAX_PROCEDURE_COUNT                 100
#define XONLINE_STAT_MAX_PARAM_COUNT                     256
#define XONLINE_STAT_MAX_SPECS                           64
#define XONLINE_MAX_STATS_USER_COUNT                     101
#define XONLINE_MAX_STATS_ROW_COUNT                      100
#define XSTAT_PROC_DATA_TYPE_NULL                        0
#define XSTAT_PROC_DATA_TYPE_INT8                        1
#define XSTAT_PROC_DATA_TYPE_INT16                       2
#define XSTAT_PROC_DATA_TYPE_INT32                       3
#define XSTAT_PROC_DATA_TYPE_INT64                       4
#define XSTAT_PROC_DATA_TYPE_DOUBLE                      5
#define XSTAT_PROC_DATA_TYPE_PUID                        7
#define XPROFILE_MAX_TITLE_NAME_LEN                      23
#define XPROFILE_MAX_SYNC_TITLES_REQUEST                 32
#define XPROFILE_MAX_SYNC_TITLES_RESULTS                 32
#define XPROFILE_MAX_ENUM_TITLE                          32
#define XPROFILE_MAX_REPLACE_IDS                         10
#define XPROFILE_MAX_NEXT_IDS                            10
#define XPROFILE_MAX_ACHIEVEMENT_NAME_LEN                32
#define XPROFILE_MAX_ACHIEVEMENT_DESC_LEN                100
#define XPROFILE_MAX_ACHIEVEMENT_HOWTO_LEN               100
#define XPROFILE_MAX_SYNC_ACHIEVEMENTS_REQUEST           32
#define XPROFILE_MAX_SYNC_ACHIEVEMENTS_RESULTS           32
#define XPROFILE_MAX_ENUM_ACHIEVEMENTS                   200
#define XMSG_MAX_NUM_MESSAGES                            125
#define XMSG_MAX_PROPS                                   256
#define XMSG_MAX_DETAILS                                 4096
#define XONLINE_LIVE_SIGNATURE_SIZE                      100
#define XSIGNATURE_MAX_SIGNATURES_TO_VERIFY              1
#define XSIGNATURE_MAX_CONTENT_TUPLES                    32
#define XONLINE_MAX_PATHNAME_DOMAIN_LENGTH               63
#define XSTORAGE_MAX_SIGNATURE_SIZE                      20
#define XSTORAGE_MAX_ATTRIBUTES_SIZE                     256
#define XSTORAGE_DOWNLOAD_WORKER_EXTRA_OBJECT_SIZE       256
#define XSTORAGE_UPLOAD_WORKER_EXTRA_OBJECT_SIZE         256
#define XSTORAGE_MISC_WORKER_EXTRA_OBJECT_SIZE           256
#define XSTORAGE_MAX_DISPLAYNAME                         128
#define XSTORAGE_DOWNLOAD_TO_DIRECTORY_EXTRA_OBJECT_SIZE_INTERNAL 200000
#define XSTORAGE_UPLOAD_FROM_DIRECTORY_EXTRA_OBJECT_SIZE 80000
#define XMESSAGE_SEND_EXTRA_OBJECT_SIZE                  1500
#define XMESSAGE_DOWNLOAD_ATTACH_TO_MEM_EXTRA_OBJECT_SIZE 1024
#define XFRIENDS_REQUEST_EXTRA_OBJECT_SIZE               1500
#define XREFERRAL_MAX_URL_SIZE                           500
#define XCONTENT_REFERRAL_MAX_URL_COUNT                  10
#define XCONTENT_MAX_PATH                                256
#define XCONTENT_HEADER_MAX_SIZE                         2048
#define XCONTENT_DOWNLOAD_EXTRA_OBJECT_SIZE              250000
#define XUPDATE_DOWNLOAD_EXTRA_OBJECT_SIZE               250000
#define XARB_MAX_REGISTRANTS_IN_SESSION                  64
#define XARB_MAX_USERS_IN_SESSION                        4
#define XARB_MAX_SUSPICIOUS_INFO_MESSAGE_LENGTH          256
#define XARB_MAX_COMP_BUNDLE_BYTES                       0
#define FB_REVIEW_MAX_TYPE                               10
#define XFB_MAX_ENUM_REVIEW_RESULTS                      100
#define XFB_MAX_AGG_REVIEW_RESULTS                       FB_REVIEW_MAX_TYPE

//
// Note: these must be kept in sync with the same list in
// xonline\main\private\common\genx\xon\inc\xonline.x:
//
#define XONLINE_FRIENDSTATE_ENUM_RESERVED1         0x00030000
#define XONLINE_FRIENDSTATE_ENUM_RESERVED2         0x00040000
#define XONLINE_FRIENDSTATE_ENUM_RESERVED3         0x00050000
#define XONLINE_FRIENDSTATE_ENUM_RESERVED4         0x00060000

C_ASSERT(XONLINE_MAX_LOGON_USERS == XUSER_MAX_COUNT);
C_ASSERT(XONLINE_GAMERTAG_SIZE == XUSER_NAME_SIZE);


#define DASH_TITLE_ID                   0xFFFE0000
#define XENON_DASH_TITLE_ID             0xFFFE07D1


// ====================================================================
// Logon related
//

#define XONLINE_S_LOGON_USER_MESSAGE_ENUMERATION_NEEDED _HRESULT_TYPEDEF_(0x001512F1L)

XAMINLINE
BOOL
XNetLogonTitleIDIsSamePublisher(
    IN DWORD dwServiceID,
    IN DWORD dwTitleID
    )
{
    return HIWORD(dwTitleID) == HIWORD(XNetLogonGetTitleID(dwServiceID));
}


// ====================================================================
// XOnline Task Throttling
//

#define XONLINE_THROTTLE_FLAG_DELAY             0x00000001 // delay starting each new operation until the throttle delay period expires, must always be specified for Xenon
#define XONLINE_THROTTLE_FLAG_FAIL              0x00000002 // return XONLINE_E_TASK_THROTTLED for new tasks that are started during the throttle delay period
#define XONLINE_THROTTLE_FLAG_CANCEL_PREVIOUS   0x00000004 // force the previous task of the same type to fail with XONLINE_E_TASK_ABORTED_BY_DUPLICATE when possible
#define XONLINE_THROTTLE_FLAG_RIP               0x00000008 // RIP in debug, not supported on Xenon
#define XONLINE_THROTTLE_FLAG_IGNORE_SERVER     0x00000010 // ignore any changes in the delay or flags that the server requests, debug/devkit only
#define XONLINE_THROTTLE_FLAG_FROM_END          0x00000020 // throttle time is enforced from when the last task finished instead of started, not supported on Xbox 1

#define XONLINE_VALID_THROTTLE_FLAGS            (XONLINE_THROTTLE_FLAG_DELAY | \
                                                 XONLINE_THROTTLE_FLAG_FAIL | \
                                                 XONLINE_THROTTLE_FLAG_CANCEL_PREVIOUS | \
                                                 XONLINE_THROTTLE_FLAG_RIP | \
                                                 XONLINE_THROTTLE_FLAG_IGNORE_SERVER | \
                                                 XONLINE_THROTTLE_FLAG_FROM_END)

typedef struct _XONLINE_REQUEST_THROTTLE_SETTINGS
{
    DWORD   dwThrottleDelayMs; // delay enforced between tasks, in milliseconds
    DWORD   dwThrottleFlags;   // throttle flags in use, see XONLINE_THROTTLE_FLAG_xxx
} XONLINE_REQUEST_THROTTLE_SETTINGS, *PXONLINE_REQUEST_THROTTLE_SETTINGS;



// ====================================================================
// XOnline Matchmaking
//

typedef enum
{
    MATCH_OP_CREATE = 0,
    MATCH_OP_SEARCH,
    MATCH_OP_INVALID

} MATCH_OP;

#define DW_LEN_HTTP_RESP_HDR    200
#define DW_LEN_SENDBUFFER       (400 + DW_LEN_HTTP_RESP_HDR)

#define X_ATTRIBUTE_TYPE_MASK              0x0F000000
#define X_ATTRIBUTE_TYPE_SESSION           0x00000000
#define X_ATTRIBUTE_TYPE_PARAM             0x02000000
#define X_ATTRIBUTE_TYPE_BUILTIN           0x03000000
#define X_ATTRIBUTE_TYPE_CONSTANT          0x05000000

#define X_ATTRIBUTE_RESERVED               ~(X_ATTRIBUTE_SCOPE_MASK | \
                                             X_ATTRIBUTE_DATATYPE_MASK | \
                                             X_ATTRIBUTE_TYPE_MASK | \
                                             X_ATTRIBUTE_ID_MASK)

// NOTE: Changing these values impacts both the client and the server.
#define X_MATCH_MAX_QUERY_PARAMS           20
#define X_MATCH_MAX_QUERY_RESULTS          50
#define X_MATCH_MAX_TITLE_SCHEMA_ATTRS     40
#define X_MATCH_MAX_ATTRIBUTE_DATA         4096

#define X_ATTRIBUTE_SCOPE_MASK              0x80000000
#define X_ATTRIBUTE_SCOPE_GLOBAL            0x80000000

#define X_ATTRIBUTE_RESERVED1_MASK          0x70000000
#define X_ATTRIBUTE_RESERVED2_MASK          0x000F0000
#define X_ATTRIBUTE_RESERVED3_MASK          0x0F000000

#define X_MATCH_PROTOCOL_VERSION            0x01000000 // 1.0.0000
#define X_MIN_SEARCH_RESULT_COLUMNS         8

//
//  Reserved title search sproc indices
//
#define X_SSINDEX_GET_SESSION               (DWORD)-1   // special sproc to retrieve session by session id
#define XMATCH_QUERYID_FLAG_SUMMARY_QUERY 0x80000000
#define XMATCH_QUERYID_FLAG_RESERVED        0x7FFF0000

//
//  This structure defines a session.  When used on the client, will be
//  included in a larger structure pre-pended with an async task struct.
//  The following structure is identical to the host advertisement wire
//  protocol.
//  The raw data for session title, application data and attributes will
//  typically follow this structure in the same area of memory, and on the
//  wire.
//
typedef struct _XMATCH_SESSION
{
    DWORD               dwMessageLength;
    XNKID               SessionID;
    DWORD               dwTitleID;
    XNADDR              HostAddress;
    DWORD               dwPublicOpen;
    DWORD               dwPrivateOpen;
    DWORD               dwPublicFilled;
    DWORD               dwPrivateFilled;
    DWORD               dwNumAttributes;
} XMATCH_SESSION, *PXMATCH_SESSION;

//
//  This structure is passed up to delete a session.
//
typedef struct _XMATCH_SESSION_DELETE
{
    DWORD               dwMessageLength;
    XNKID               SessionID;
    DWORD               dwTitleID;
} XMATCH_SESSION_DELETE, *PXMATCH_SESSION_DELETE;

//
//  This structure defines the information passed to the server
//  to initiate a search for a game session.
//

#define XONLINE_MATCH_FLAG_NAT_TYPE_MASK 0x0003
#define XONLINE_MATCH_FLAGS_RESERVED     0xFFFC

typedef struct _XMATCH_SEARCH
{
    DWORD                dwMessageLength;
    DWORD                dwTitleID;
    DWORD                dwProcedureIndex;
    XNADDR               ClientAddress;
    WORD                 wNumUsers;
    WORD                 wFlags;
    DWORD                dwNumParameters;
} XMATCH_SEARCH, *PXMATCH_SEARCH;

// ====================================================================
// SGADDR

#pragma pack(push, 1)

typedef struct _SGADDR {
    IN_ADDR         inaSg;              // IP address of the SG for the client
    DWORD           dwSpiSg;            // Pseudo-random identifier assigned by the SG
    ULONGLONG       qwXboxID;           // Unique identifier of client machine account
    BYTE            abReserved[4];      // Reserved (must be zero)
} SGADDR;

#pragma pack(pop)

//
//  This structure is the body of dead xbox requests.
//

typedef struct _XMATCH_DEAD_XBOX
{
    DWORD               dwMessageLength;
    SGADDR              sgaddr;
    DWORD               dwTitleID;
    DWORD               dwTitleRegion;
    ULONGLONG           aqwUserID[XONLINE_MAX_LOGON_USERS];
} XMATCH_DEAD_XBOX, *PXMATCH_DEAD_XBOX;

//
//  This structure is the body of dead SG requests.
//

typedef struct _XMATCH_DEAD_SG
{
    DWORD               dwMessageLength;
    SGADDR              sgaddr;
} XMATCH_DEAD_SG, *PXMATCH_DEAD_SG;

#pragma pack(push, 1)

// NOTE: The client doesn't use this at all
typedef struct _XMATCH_SEARCHRESULT_HEADER
{
    DWORD               dwMessageLength;
    USHORT              nNumSearchResults;
    USHORT              fFlags;             // Unused, always zero
    DWORD               dwLoggingThreshold; // Unused, always zero
} XMATCH_SEARCHRESULT_HEADER, *PXMATCH_SEARCHRESULT_HEADER;

typedef struct _XMATCH_SEARCHRESULT
{
    DWORD     dwResultLength;
    XNKID     SessionID;
    XNADDR    HostAddress;
    XNKEY     KeyExchangeKey;
    DWORD     dwPublicOpen;
    DWORD     dwPrivateOpen;
    DWORD     dwPublicFilled;
    DWORD     dwPrivateFilled;
    DWORD     dwNumAttributes;
} XMATCH_SEARCHRESULT, *PXMATCH_SEARCHRESULT;

#pragma pack(pop)


//
// Notifications
//

typedef enum P_MSG_TYPES
{
    // Incoming messages
    PMSG_MIN_REQ_TYPE                   = 1000,
    PMSG_HELLO                          = 1000,
    PMSG_ALIVE                          = 1001,
    PMSG_SYNC                           = 1002,
    PMSG_REFRESH                        = 1003,
    PMSG_ADD                            = 1004,
    PMSG_DELETE                         = 1005,
    PMSG_ACCEPT                         = 1006,
    PMSG_REJECT                         = 1007,
    PMSG_BLOCK                          = 1008,
    PMSG_UNBLOCK                        = 1009,
    PMSG_INVITE                         = 1010,
    PMSG_CANCEL                         = 1011,
    PMSG_INVITE_ANSWER                  = 1012,
    PMSG_NICKNAME                       = 1013,
    PMSG_STATE                          = 1014,
    PMSG_DEAD_XBOX                      = 1015,
    PMSG_DEAD_SG                        = 1016,
    PMSG_ANNOUNCE                       = 1017,
    PMSG_SUBSCRIBED                     = 1018,
    PMSG_UNSUBSCRIBE                    = 1019,
    PMSG_ADDED                          = 1020,
    PMSG_ACCEPTED                       = 1021,
    PMSG_REMOVED                        = 1022,
    PMSG_KICK                           = 1023,
    PMSG_DEAD_USER                      = 1024,
    PMSG_ALIVE_2                        = 1025,
    PMSG_WEB_FRIENDS                    = 1026,
    PMSG_WEB_ALIVE                      = 1027,
    PMSG_WEB_ANNOUNCE                   = 1028,
    PMSG_WEB_SUBSCRIBED                 = 1029,
    PMSG_WEB_UNSUBSCRIBE                = 1030,
    PMSG_PEER_SESSION                   = 1031,
    PMSG_TEAM_LIST_TEAMS                = 1032,
    PMSG_TEAM_LIST_MEMBERS              = 1033,
    PMSG_TEAM_CREATE                    = 1034,
    PMSG_TEAM_DELETE                    = 1035,
    PMSG_TEAM_REMOVE                    = 1036,
    PMSG_TEAM_MANAGE_TEAM               = 1037,
    PMSG_TEAM_MANAGE_MEMBER             = 1038,
    PMSG_TEAM_RECRUIT                   = 1039,
    PMSG_TEAM_JOIN                      = 1040,
    PMSG_TEAM_GET_TICKET                = 1041,
    PMSG_PEER_SUBSCRIBE                 = 1042,
    PMSG_PEER_UNSUBSCRIBE               = 1043,
    PMSG_WATCH_START                    = 1044,
    PMSG_WATCH_STOP                     = 1045,
    PMSG_ADD_2                          = 1046,
    PMSG_INVITE_2                       = 1047,
    PMSG_ALIVE_INTERNAL                 = 1048,
    PMSG_STATE_2                        = 1049,
    PMSG_GET_STATE                      = 1050,
    PMSG_TEAM_CREATE_XE                 = 1051,
    PMSG_TEAM_MANAGE_TEAM_XE            = 1052,
    PMSG_ADD_AFFILIATES                 = 1053,
    PMSG_IS_AFFILIATE                   = 1054,
    PMSG_QUERY_AFFILIATES               = 1055,
    PMSG_GET_PRESENCE_INFO              = 1056,
    PMSG_PRESENCE_INFO_REPLY            = 1057,
    PMSG_INVALIDATE_USER                = 1058,
    PMSG_FIND_USER                      = 1059,
    PMSG_CHECK_TITLE_MESSAGES           = 1060,
    PMSG_TEAM_LIST_USER_TEAMS           = 1061,
    PMSG_MAX_REQ_TYPE                   = 1061,

    // Outgoing messages
    PMSG_MIN_REPLY_TYPE                 = 1101,
    PMSG_ALIVE_REPLY                    = 1101,
    PMSG_SYNC_REPLY                     = 1102,
    PMSG_WEB_FRIENDS_REPLY              = 1103,
    PMSG_WEB_ALIVE_REPLY                = 1104,
    PMSG_PEER_SESSION_REPLY             = 1105,
    PMSG_INVITE_REPLY                   = 1106,
    PMSG_TEAM_LIST_TEAMS_REPLY          = 1107,
    PMSG_TEAM_LIST_MEMBERS_REPLY        = 1108,
    PMSG_TEAM_CREATE_REPLY              = 1109,
    PMSG_TEAM_DELETE_REPLY              = 1110,
    PMSG_TEAM_REMOVE_REPLY              = 1111,
    PMSG_TEAM_MANAGE_TEAM_REPLY         = 1112,
    PMSG_TEAM_MANAGE_MEMBER_REPLY       = 1113,
    PMSG_TEAM_RECRUIT_REPLY             = 1114,
    PMSG_TEAM_JOIN_REPLY                = 1115,
    PMSG_TEAM_GET_TICKET_REPLY          = 1116,
    PMSG_PEER_SUBSCRIBE_REPLY           = 1117,
    PMSG_PEER_UNSUBSCRIBE_REPLY         = 1118,
    PMSG_GET_STATE_REPLY                = 1119,
    PMSG_IS_AFFILIATE_REPLY             = 1120,
    PMSG_QUERY_AFFILIATES_REPLY         = 1121,
    PMSG_FIND_USER_REPLY                = 1122,
    PMSG_CHECK_TITLE_MESSAGES_REPLY     = 1123,
    PMSG_TEAM_LIST_USER_TEAMS_REPLY     = 1124,
    PMSG_MAX_REPLY_TYPE                 = 1124

};

#define P_STATE_MASK_NONE           0x0000
#define P_STATE_MASK_ONLINE         0x0001 // Set if online
#define P_STATE_MASK_PLAYING        0x0002 // Set if playing a game
#define P_STATE_MASK_CLOAKED        0x0004 // Set to fake being offline
#define P_STATE_MASK_VOICE          0x0008 // Set if supports voice
#define P_STATE_MASK_JOINABLE       0x0010 // Set if session is joinable
#define P_STATE_MASK_GUESTS         0x0060
#define P_STATE_MASK_RESERVED0      0x0080
#define P_STATE_MASK_SENTREQUEST     0x40000000
#define P_STATE_MASK_RECEIVEDREQUEST 0x80000000

#define P_BUDDY_STATUS_OK      0 // Mutualy accepted buddy
#define P_BUDDY_STATUS_PENDING 1 // Buddy request pending accetance
#define P_BUDDY_STATUS_REQUEST 2 // Buddy request to accept or reject

// Internal cloaked state
#define XONLINE_FRIENDSTATE_FLAG_CLOAKED           0x00000004

// Used by all Presence and Notification protocols that accept an answer member
typedef enum P_INVITE_REPLIES
{
    PINVITE_REPLY_NO    = 0,
    PINVITE_REPLY_YES   = 1,
    PINVITE_REPLY_NEVER = 2
};

typedef enum Q_MSG_TYPES
{
    //
    // Incoming messages
    //
    QMSG_MIN_REQ_TYPE                   =  0,
    QMSG_HELLO                          =  0,
    QMSG_USER_INFO                      =  1,
    QMSG_ADD                            =  2,
    QMSG_DELETE                         =  3,
    QMSG_DELETE_MATCHES                 =  4,
    QMSG_DEAD_XBOX                      =  5,
    QMSG_DEAD_SG                        =  6,
    QMSG_LIST                           =  7,
    QMSG_DEQUEUE                        =  8,
    QMSG_DEAD_USER                      =  9,
    QMSG_WEB_USER_INFO                  = 10,
    QMSG_WEB_PRESENCE                   = 11,
    QMSG_WEB_LIST                       = 12,
    QMSG_ENUM_MESSAGES                  = 13,
    QMSG_MESSAGE_SUMMARY                = 14,
    QMSG_MESSAGE_DETAILS                = 15,
    QMSG_DELETE_MESSAGE                 = 16,
    QMSG_SEND_MESSAGE                   = 17,
    QMSG_REVOKE_MESSAGE                 = 18,
    QMSG_DELETE_TITLE                   = 19,
    QMSG_ENUM_TITLES                    = 20,
    QMSG_MESSAGE_FLAGS                  = 21,
    QMSG_ENUM_SYSTEM_MESSAGES           = 22,
    QMSG_SYSTEM_MESSAGE_DETAILS         = 23,
    QMSG_DELETE_SYSTEM_MESSAGE          = 24,
    QMSG_SEND_SYSTEM_MESSAGE            = 25,
    QMSG_REVOKE_MESSAGE_EX              = 26,
    QMSG_ENUM_MESSAGES_2                = 27,
    QMSG_MESSAGE_SUMMARY_2              = 28,
    QMSG_MAX_REQ_TYPE                   = 28,

    //
    // Outgoing messages
    //
    QMSG_MIN_REPLY_TYPE                 = 100,
    QMSG_LIST_REPLY                     = 100,
    QMSG_WEB_LIST_REPLY                 = 101,
    QMSG_ENUM_MESSAGES_REPLY            = 102,
    QMSG_MESSAGE_SUMMARY_REPLY          = 103,
    QMSG_MESSAGE_DETAILS_REPLY          = 104,
    QMSG_DELETE_MESSAGE_REPLY           = 105,
    QMSG_SEND_MESSAGE_REPLY             = 106,
    QMSG_REVOKE_MESSAGE_REPLY           = 107,
    QMSG_DELETE_TITLE_REPLY             = 108,
    QMSG_ENUM_TITLES_REPLY              = 109,
    QMSG_MESSAGE_FLAGS_REPLY            = 110,
    QMSG_ENUM_SYSTEM_MESSAGES_REPLY = 111,
    QMSG_SYSTEM_MESSAGE_DETAILS_REPLY = 112,
    QMSG_DELETE_SYSTEM_MESSAGE_REPLY = 113,
    QMSG_SEND_SYSTEM_MESSAGE_REPLY      = 114,
    QMSG_ENUM_MESSAGES_2_REPLY          = 115,
    QMSG_MESSAGE_SUMMARY_2_REPLY        = 116,
    QMSG_MAX_REPLY_TYPE                 = 116
};


#define XONLINE_FRIENDSTATE_MASK_REQUESTFLAGS      (XONLINE_FRIENDSTATE_FLAG_RECEIVEDREQUEST | XONLINE_FRIENDSTATE_FLAG_SENTREQUEST)
#define XONLINE_FRIENDSTATE_MASK_CLIENTFLAGS       (XONLINE_FRIENDSTATE_MASK_REQUESTFLAGS | XONLINE_FRIENDSTATE_FLAG_INVITEREJECTED | XONLINE_FRIENDSTATE_FLAG_INVITEACCEPTED | XONLINE_FRIENDSTATE_FLAG_RECEIVEDINVITE | XONLINE_FRIENDSTATE_FLAG_SENTINVITE)

// Errors returned by Presence/Notification             = 0x801520XX
#define XONLINE_E_NOTIFICATION_SERVER_BUSY              _HRESULT_TYPEDEF_(0x80152001L)
#define XONLINE_E_NOTIFICATION_LIST_FULL                _HRESULT_TYPEDEF_(0x80152002L)
#define XONLINE_E_NOTIFICATION_BLOCKED                  _HRESULT_TYPEDEF_(0x80152003L)
#define XONLINE_E_NOTIFICATION_FRIEND_PENDING           _HRESULT_TYPEDEF_(0x80152004L)
#define XONLINE_E_NOTIFICATION_FLUSH_TICKETS            _HRESULT_TYPEDEF_(0x80152005L)
#define XONLINE_E_NOTIFICATION_TOO_MANY_REQUESTS        _HRESULT_TYPEDEF_(0x80152006L)
#define XONLINE_E_NOTIFICATION_USER_ALREADY_EXISTS      _HRESULT_TYPEDEF_(0x80152007L)
#define XONLINE_E_NOTIFICATION_USER_NOT_FOUND           _HRESULT_TYPEDEF_(0x80152008L)
#define XONLINE_E_NOTIFICATION_OTHER_LIST_FULL          _HRESULT_TYPEDEF_(0x80152009L)
#define XONLINE_E_NOTIFICATION_SELF                     _HRESULT_TYPEDEF_(0x8015200AL)
#define XONLINE_E_NOTIFICATION_SAME_TITLE               _HRESULT_TYPEDEF_(0x8015200BL)
#define XONLINE_E_NOTIFICATION_NO_TASK                  _HRESULT_TYPEDEF_(0x8015200CL)
#define XONLINE_E_NOTIFICATION_NOT_INITIALIZED          _HRESULT_TYPEDEF_(0x8015200DL)
#define XONLINE_E_NOTIFICATION_TOO_MANY_SUBS            _HRESULT_TYPEDEF_(0x8015200EL)

#define XONLINE_S_NOTIFICATION_NO_PEER_SUBSCRIBE        _HRESULT_TYPEDEF_(0x0015200EL)

// Errors returned by teams                             = 0x801521XX
#define XONLINE_E_TEAMS_SERVER_BUSY                     _HRESULT_TYPEDEF_(0x80152100L)
#define XONLINE_E_TEAMS_TEAM_FULL                       _HRESULT_TYPEDEF_(0x80152101L)
#define XONLINE_E_TEAMS_MEMBER_PENDING                  _HRESULT_TYPEDEF_(0x80152102L)
#define XONLINE_E_TEAMS_TOO_MANY_REQUESTS               _HRESULT_TYPEDEF_(0x80152103L)
#define XONLINE_E_TEAMS_USER_ALREADY_EXISTS             _HRESULT_TYPEDEF_(0x80152104L)
#define XONLINE_E_TEAMS_USER_NOT_FOUND                  _HRESULT_TYPEDEF_(0x80152105L)
#define XONLINE_E_TEAMS_USER_TEAMS_FULL                 _HRESULT_TYPEDEF_(0x80152106L)
#define XONLINE_E_TEAMS_SELF                            _HRESULT_TYPEDEF_(0x80152107L)
#define XONLINE_E_TEAMS_NO_TASK                         _HRESULT_TYPEDEF_(0x80152108L)
#define XONLINE_E_TEAMS_TOO_MANY_TEAMS                  _HRESULT_TYPEDEF_(0x80152109L)
#define XONLINE_E_TEAMS_TEAM_ALREADY_EXISTS             _HRESULT_TYPEDEF_(0x8015210AL)
#define XONLINE_E_TEAMS_TEAM_NOT_FOUND                  _HRESULT_TYPEDEF_(0x8015210BL)
#define XONLINE_E_TEAMS_INSUFFICIENT_PRIVILEGES         _HRESULT_TYPEDEF_(0x8015210CL)
#define XONLINE_E_TEAMS_NAME_CONTAINS_BAD_WORDS         _HRESULT_TYPEDEF_(0x8015210DL)
#define XONLINE_E_TEAMS_DESCRIPTION_CONTAINS_BAD_WORDS  _HRESULT_TYPEDEF_(0x8015210EL)
#define XONLINE_E_TEAMS_MOTTO_CONTAINS_BAD_WORDS        _HRESULT_TYPEDEF_(0x8015210FL)
#define XONLINE_E_TEAMS_URL_CONTAINS_BAD_WORDS          _HRESULT_TYPEDEF_(0x80152110L)
#define XONLINE_E_TEAMS_NOT_A_MEMBER                    _HRESULT_TYPEDEF_(0x80152111L)
#define XONLINE_E_TEAMS_NO_ADMIN                        _HRESULT_TYPEDEF_(0x80152112L)

// Errors returned by offering service                  = 0x801530XX + 0x801531XX
#define XONLINE_S_OFFERING_NEW_CONTENT                  _HRESULT_TYPEDEF_(0x00153101L)  // new content is available
#define XONLINE_S_OFFERING_NO_NEW_CONTENT               _HRESULT_TYPEDEF_(0x00153102L)  // no new content is available
#define XONLINE_E_OFFERING_BAD_REQUEST                  _HRESULT_TYPEDEF_(0x80153001L)  // server received incorrectly formatted request
#define XONLINE_E_OFFERING_INVALID_USER                 _HRESULT_TYPEDEF_(0x80153002L)  // cannot find account for this user
#define XONLINE_E_OFFERING_INVALID_OFFER_ID             _HRESULT_TYPEDEF_(0x80153003L)  // offer does not exist
#define XONLINE_E_OFFERING_INELIGIBLE_FOR_OFFER         _HRESULT_TYPEDEF_(0x80153004L)  // )] private /title not allowed to purchase offer
#define XONLINE_E_OFFERING_OFFER_EXPIRED                _HRESULT_TYPEDEF_(0x80153005L)  // offer no longer available
#define XONLINE_E_OFFERING_SERVICE_UNREACHABLE          _HRESULT_TYPEDEF_(0x80153006L)  // apparent connectivity problems
#define XONLINE_E_OFFERING_PURCHASE_BLOCKED             _HRESULT_TYPEDEF_(0x80153007L)  // this user is not allowed to make purchases
#define XONLINE_E_OFFERING_PURCHASE_DENIED              _HRESULT_TYPEDEF_(0x80153008L)  // this user's payment is denied by billing provider
#define XONLINE_E_OFFERING_BILLING_SERVER_ERROR         _HRESULT_TYPEDEF_(0x80153009L)  // nonspecific billing provider error
#define XONLINE_E_OFFERING_OFFER_NOT_CANCELABLE         _HRESULT_TYPEDEF_(0x8015300AL)  // either this offer doesn't exist, or it's marked as un-cancelable
#define XONLINE_E_OFFERING_NOTHING_TO_CANCEL            _HRESULT_TYPEDEF_(0x8015300BL)  // this user doesn't have one of these anyways
#define XONLINE_E_OFFERING_ALREADY_OWN_MAX              _HRESULT_TYPEDEF_(0x8015300CL)  // this user already owns the maximum allowed
#define XONLINE_E_OFFERING_NO_CHARGE                    _HRESULT_TYPEDEF_(0x8015300DL)  // this is a free offer; no purchase is necessary
#define XONLINE_E_OFFERING_PERMISSION_DENIED            _HRESULT_TYPEDEF_(0x8015300EL)  // permission denied
#define XONLINE_E_OFFERING_NAME_TAKEN                   _HRESULT_TYPEDEF_(0x8015300FL)  // Name given to XOnlineVerifyNickname is taken (dosen't vet)

// DMP-specific client XBOS/XUACS HRESULTS              = 0x801534XX

#define XONLINE_E_DMP_E_UNKNOWN_ERROR                   _HRESULT_TYPEDEF_(0x80153410L)  // Generic DMP error.  See server event log for specific details about what went wrong.
#define XONLINE_E_DMP_E_REQUEST_CANNOT_BE_COMPLETED     _HRESULT_TYPEDEF_(0x80153411L)  // The request cannot be completed due to user state. If the user is disabled then AddPromotionalBalance cannot be called upon that user.
#define XONLINE_E_DMP_E_INSUFFICIENT_BALANCE            _HRESULT_TYPEDEF_(0x80153412L)  // There is not sufficient balance to support this transaction
#define XONLINE_E_DMP_E_MAX_BALANCE_EXCEEDED            _HRESULT_TYPEDEF_(0x80153413L)  // The result point balance will exceed the policy max balance
#define XONLINE_E_DMP_E_MAX_ACQUISITION_EXCEEDED        _HRESULT_TYPEDEF_(0x80153414L)  // The point amount exceeds the policy max acquisition limit per transaction
#define XONLINE_E_DMP_E_MAX_CONSUMPTION_EXCEEDED        _HRESULT_TYPEDEF_(0x80153415L)  // The user consumption per period of time would exceed the policy limit
#define XONLINE_E_DMP_E_NO_MORE_PROMO_POINTS            _HRESULT_TYPEDEF_(0x80153416L)  // There are no more points to distribute for this tenant sku combination. All the promo points for this partner's promotional SKU are gone already!
#define XONLINE_E_DMP_E_PROMOTION_LIMIT_LIFE_MAX        _HRESULT_TYPEDEF_(0x80153417L)  // The promotional points user obtained would exceed the sku limit. There is a configurable per user limit on each promotion. The partner sets it in offer modeling time
#define XONLINE_E_DMP_E_PROMO_EXPIRED                   _HRESULT_TYPEDEF_(0x80153418L)  // The promotional SKU has expired. The enddate for a promo is a configured limit set by the partner. If a request comes in after that configured deadline then the request is rejected

//  Errors returned by xcbk service                     = 0x801535XX

//  Errors returned by uacs service                     = 0x801540XX
#define XONLINE_S_ACCOUNTS_NAME_TAKEN                   _HRESULT_TYPEDEF_(0x00000010L)

#define XONLINE_E_ACCOUNTS_NAME_TAKEN                   _HRESULT_TYPEDEF_(0x80154000L)
#define XONLINE_E_ACCOUNTS_INVALID_USER                 _HRESULT_TYPEDEF_(0x80154002L)
#define XONLINE_E_ACCOUNTS_BAD_CREDIT_CARD              _HRESULT_TYPEDEF_(0x80154003L)
#define XONLINE_E_ACCOUNTS_BAD_BILLING_ADDRESS          _HRESULT_TYPEDEF_(0x80154004L)
#define XONLINE_E_ACCOUNTS_ACCOUNT_BANNED               _HRESULT_TYPEDEF_(0x80154005L)
#define XONLINE_E_ACCOUNTS_PERMISSION_DENIED            _HRESULT_TYPEDEF_(0x80154006L)
#define XONLINE_E_ACCOUNTS_INVALID_VOUCHER              _HRESULT_TYPEDEF_(0x80154007L)
#define XONLINE_E_ACCOUNTS_DATA_CHANGED                 _HRESULT_TYPEDEF_(0x80154008L) // unexpected modifications made during request.  commit is aborted to avoid overwriting modifcations.
#define XONLINE_E_ACCOUNTS_VOUCHER_ALREADY_USED         _HRESULT_TYPEDEF_(0x80154009L)
#define XONLINE_E_ACCOUNTS_OPERATION_BLOCKED            _HRESULT_TYPEDEF_(0x8015400AL)
#define XONLINE_E_ACCOUNTS_POSTAL_CODE_REQUIRED         _HRESULT_TYPEDEF_(0x8015400BL)
#define XONLINE_E_ACCOUNTS_TRY_AGAIN_LATER              _HRESULT_TYPEDEF_(0x8015400CL)
#define XONLINE_E_ACCOUNTS_NOT_A_RENEWAL_OFFER          _HRESULT_TYPEDEF_(0x8015400DL)
#define XONLINE_E_ACCOUNTS_RENEWAL_IS_LOCKED            _HRESULT_TYPEDEF_(0x8015400EL)
#define XONLINE_E_ACCOUNTS_VOUCHER_REQUIRED             _HRESULT_TYPEDEF_(0x8015400FL)
#define XONLINE_E_ACCOUNTS_ALREADY_DEPROVISIONED        _HRESULT_TYPEDEF_(0x80154010L)
#define XONLINE_E_ACCOUNTS_INVALID_PRIVILEGE            _HRESULT_TYPEDEF_(0x80154011L)
#define XONLINE_E_ACCOUNTS_INVALID_SIGNED_PASSPORT_PUID    _HRESULT_TYPEDEF_(0x80154012L)
#define XONLINE_E_ACCOUNTS_PASSPORT_ALREADY_LINKED      _HRESULT_TYPEDEF_(0x80154013L)
#define XONLINE_E_ACCOUNTS_MIGRATE_NOT_XBOX1_USER       _HRESULT_TYPEDEF_(0x80154014L)
#define XONLINE_E_ACCOUNTS_MIGRATE_BAD_SUBSCRIPTION     _HRESULT_TYPEDEF_(0x80154015L)
#define XONLINE_E_ACCOUNTS_PASSPORT_NOT_LINKED          _HRESULT_TYPEDEF_(0x80154016L)
#define XONLINE_E_ACCOUNTS_NOT_XENON_USER               _HRESULT_TYPEDEF_(0x80154017L)
#define XONLINE_E_ACCOUNTS_CREDIT_CARD_REQUIRED         _HRESULT_TYPEDEF_(0x80154018L)
#define XONLINE_E_ACCOUNTS_MIGRATE_NOT_XBOXCOM_USER     _HRESULT_TYPEDEF_(0x80154019L)
#define XONLINE_E_ACCOUNTS_NOT_A_VOUCHER_OFFER          _HRESULT_TYPEDEF_(0x8015401AL)
#define XONLINE_E_ACCOUNTS_REACHED_TRIAL_OFFER_LIMIT    _HRESULT_TYPEDEF_(0x8015401BL) 
#define XONLINE_E_ACCOUNTS_XBOX1_MANAGEMENT_BLOCKED     _HRESULT_TYPEDEF_(0x8015401CL) 
#define XONLINE_E_ACCOUNTS_OFFLINE_XUID_ALREADY_USED    _HRESULT_TYPEDEF_(0x8015401DL) 
#define XONLINE_E_ACCOUNTS_BILLING_PROVIDER_TIMEOUT     _HRESULT_TYPEDEF_(0x8015401EL) 
#define XONLINE_E_ACCOUNTS_MIGRATION_OFFER_NOT_FOUND    _HRESULT_TYPEDEF_(0x8015401FL) 

// Errors returned by Notification                      = 0x801550XX
#define XONLINE_E_NOTIFICATION_BAD_CONTENT_TYPE         _HRESULT_TYPEDEF_(0x80155000L)
#define XONLINE_E_NOTIFICATION_REQUEST_TOO_SMALL        _HRESULT_TYPEDEF_(0x80155001L)
#define XONLINE_E_NOTIFICATION_INVALID_MESSAGE_TYPE     _HRESULT_TYPEDEF_(0x80155002L)
#define XONLINE_E_NOTIFICATION_NO_ADDRESS               _HRESULT_TYPEDEF_(0x80155003L)
#define XONLINE_E_NOTIFICATION_INVALID_PUID             _HRESULT_TYPEDEF_(0x80155004L)
#define XONLINE_E_NOTIFICATION_NO_CONNECTION            _HRESULT_TYPEDEF_(0x80155005L)
#define XONLINE_E_NOTIFICATION_SEND_FAILED              _HRESULT_TYPEDEF_(0x80155006L)
#define XONLINE_E_NOTIFICATION_RECV_FAILED              _HRESULT_TYPEDEF_(0x80155007L)
#define XONLINE_E_NOTIFICATION_MESSAGE_TRUNCATED        _HRESULT_TYPEDEF_(0x80155008L)
#define XONLINE_E_NOTIFICATION_INVALID_TITLE_ID         _HRESULT_TYPEDEF_(0x80155009L)
#define XONLINE_E_NOTIFICATION_NO_DATA                  _HRESULT_TYPEDEF_(0x8015200DL)
#define XONLINE_S_NOTIFICATION_NO_PEER_SUBSCRIBE        _HRESULT_TYPEDEF_(0x0015200EL)

// Errors returned by Messages                          = 0x80155AXX
#define XONLINE_E_MESSAGE_INVALID_MESSAGE_ID            _HRESULT_TYPEDEF_(0x80155A01L)  // the specified message was not found
#define XONLINE_E_MESSAGE_PROPERTY_DOWNLOAD_REQUIRED    _HRESULT_TYPEDEF_(0x80155A02L)  // the property was too large to fit into the details block, it must be retrieved separately using XOnlineMessageDownloadAttachmentxxx
#define XONLINE_E_MESSAGE_PROPERTY_NOT_FOUND            _HRESULT_TYPEDEF_(0x80155A03L)  // the specified property tag was not found
#define XONLINE_E_MESSAGE_NO_VALID_SENDS_TO_REVOKE      _HRESULT_TYPEDEF_(0x80155A04L)  // no valid sends to revoke were found
#define XONLINE_E_MESSAGE_NO_MESSAGE_DETAILS            _HRESULT_TYPEDEF_(0x80155A05L)  // the specified message does not have any details
#define XONLINE_E_MESSAGE_INVALID_TITLE_ID              _HRESULT_TYPEDEF_(0x80155A06L)  // an invalid title ID was specified
#define XONLINE_E_MESSAGE_SENDER_BLOCKED                _HRESULT_TYPEDEF_(0x80155A07L)  // a send failed because the recipient has blocked the sender
#define XONLINE_E_MESSAGE_MAX_DETAILS_SIZE_EXCEEDED     _HRESULT_TYPEDEF_(0x80155A08L)  // the property couldn't be added because the maximum details size would be exceeded
#define XONLINE_E_MESSAGE_INVALID_MESSAGE_TYPE          _HRESULT_TYPEDEF_(0x80155A09L)
#define XONLINE_E_MESSAGE_USER_OPTED_OUT                _HRESULT_TYPEDEF_(0x80155A0AL)  // a send failed because the message is marketing and the recipient has opted-out for the sending title
// Success codes returned by Messages                   = 0x00155AXX
#define XONLINE_S_MESSAGE_PENDING_SYNC                  _HRESULT_TYPEDEF_(0x00155A01L)  // updated message list is currently being retrieved (after logon or disabling summary refresh), returned results may be out of date


// Errors returned by uodb procs                        = 0x801560XX
#define XONLINE_E_UODB_KEY_ALREADY_EXISTS               _HRESULT_TYPEDEF_(0x80156000L)  // service key already exists when attempting to insert key


// Errors returned by billing services                      = 0x80162XXX - 0x8016EXXX
#define XONLINE_E_BILLING_AUTHORIZATION_FAILED              _HRESULT_TYPEDEF_(0x80167611) // Credit card authorization failed; user should update credit card info in Dash.
#define XONLINE_E_BILLING_CREDIT_CARD_EXPIRED               _HRESULT_TYPEDEF_(0x80167531) // The credit card has expired or will expire this month; user should update card info in Dash.
#define XONLINE_E_BILLING_NON_ACTIVE_ACCOUNT                _HRESULT_TYPEDEF_(0x80169d94) // The account specified is no longer active; user should call customer service
#define XONLINE_E_BILLING_INVALID_PAYMENT_INSTRUMENT_STATUS _HRESULT_TYPEDEF_(0x80169e7f) // User's payment instrument is in a bad state. They should call customer service to rectify the issue.

// generated from xonline/private/common/mc/sps25/imperr/imperr.pl
#define XONLINE_E_BILLING_BAN_NULL_INPUT_PARAMETER                 _HRESULT_TYPEDEF_(0x80167594) // Null input parameter passed to a Ban API
#define XONLINE_E_BILLING_ALREADY_BANNED                           _HRESULT_TYPEDEF_(0x80167599) // Already banned
#define XONLINE_E_BILLING_NOT_BANNED                               _HRESULT_TYPEDEF_(0x8016759e) // Not banned
#define XONLINE_E_BILLING_BANNEDPERSON                             _HRESULT_TYPEDEF_(0x801675bc) // This account is banned
#define XONLINE_E_BILLING_COUNTRY_CURRENCY_PI_MISMATCH             _HRESULT_TYPEDEF_(0x801675c1) // There is a country/currency/payment instrument type mismatch
#define XONLINE_E_BILLING_INVALID_PAYMENT_INSTRUMENT_TYPE          _HRESULT_TYPEDEF_(0x801675c8) // The payment instrument type specified is invalid
#define XONLINE_E_BILLING_INVALID_CREDIT_CARD_TYPE                 _HRESULT_TYPEDEF_(0x801675cb) // The credit card type specified is invalid
#define XONLINE_E_BILLING_DECRYPTION_FAILURE                       _HRESULT_TYPEDEF_(0x801675d0) // There was a failure during decryption.  Make sure data is encrypted correctly
#define XONLINE_E_BILLING_BANNED_PAYMENT_INSTRUMENT                _HRESULT_TYPEDEF_(0x801675c6) // The payment instrument specified is banned.
#define XONLINE_E_BILLING_INVALID_DD_ACCOUNT                       _HRESULT_TYPEDEF_(0x801675e4) // Direct Debit account validation failed
#define XONLINE_E_BILLING_DD_CONCATENATED_STRING_LENGTH_EXCEEDS_24 _HRESULT_TYPEDEF_(0x801675e9) // The concatenated DD account number exceeds 24.
#define XONLINE_E_BILLING_INVALID_CREDIT_CARD_NUMBER               _HRESULT_TYPEDEF_(0x80167530) // The credit card number is invalid
#define XONLINE_E_BILLING_AVS_FAILED                               _HRESULT_TYPEDEF_(0x8016760c) // Address verification failed
#define XONLINE_E_BILLING_PAYMENT_PROVIDER_CONNECTION_FAILED       _HRESULT_TYPEDEF_(0x8016761b) // Unable to connect to payment provider
#define XONLINE_E_BILLING_DD_INVALID_COUNTRY                       _HRESULT_TYPEDEF_(0x8016762f) // Invalid country code.
#define XONLINE_E_BILLING_DD_INVALID_ACCOUNT_FORMAT                _HRESULT_TYPEDEF_(0x80167634) // Invalid account format.
#define XONLINE_E_BILLING_DD_INVALID_BANKCODE_FORMAT               _HRESULT_TYPEDEF_(0x80167639) // Invalid bank code format.
#define XONLINE_E_BILLING_DD_INVALID_BRANCHCODE_FORMAT             _HRESULT_TYPEDEF_(0x8016763e) // Invalid branch code format.
#define XONLINE_E_BILLING_DD_INVALID_CHECKDIGIT_FORMAT             _HRESULT_TYPEDEF_(0x80167643) // Invalid check digit format.
#define XONLINE_E_BILLING_DD_ACCOUNT_MISSING                       _HRESULT_TYPEDEF_(0x80167648) // account missing.
#define XONLINE_E_BILLING_DD_BANKCODE_MISSING                      _HRESULT_TYPEDEF_(0x8016764d) // bank code missing.
#define XONLINE_E_BILLING_DD_BRANCHCODE_MISSING                    _HRESULT_TYPEDEF_(0x80167652) // branch code missing.
#define XONLINE_E_BILLING_DD_CHECKDIGIT_MISSING                    _HRESULT_TYPEDEF_(0x80167657) // check digit missing.
#define XONLINE_E_BILLING_DD_ERROR_IN_FIELDS                       _HRESULT_TYPEDEF_(0x8016765c) // There are fields errors.
#define XONLINE_E_BILLING_DD_INVALID_ACCOUNT_VALUE                 _HRESULT_TYPEDEF_(0x80167661) // Invalid account VALUE.
#define XONLINE_E_BILLING_DD_INVALID_BANKCODE_VALUE                _HRESULT_TYPEDEF_(0x80167666) // Invalid bank code VALUE.
#define XONLINE_E_BILLING_DD_INVALID_BRANCHCODE_VALUE              _HRESULT_TYPEDEF_(0x8016766b) // Invalid branch code VALUE.
#define XONLINE_E_BILLING_DD_INVALID_CHECKDIGIT_VALUE              _HRESULT_TYPEDEF_(0x80167670) // Invalid check digit VALUE.
#define XONLINE_E_BILLING_DD_INVALID_ACCOUNT_HOLDER_NAME           _HRESULT_TYPEDEF_(0x8016767a) // A direct debit account holder name can't be longer than 35 characters.
#define XONLINE_E_BILLING_PAYMENT_PROVIDER_CONNECTION_TIMEOUT      _HRESULT_TYPEDEF_(0x8016767f) // Payment provider connection timed out
#define XONLINE_E_BILLING_ALREADY_IN_SPECIFIED_STATE               _HRESULT_TYPEDEF_(0x80169c41) // The object is already in the desired state.
#define XONLINE_E_BILLING_REQUIRED_FIELD_MISSING                   _HRESULT_TYPEDEF_(0x80169c45) // Required field missing
#define XONLINE_E_BILLING_ACTIVE_SUBSCRIPTIONS                     _HRESULT_TYPEDEF_(0x80169c46) // The account has subscriptions on it.
#define XONLINE_E_BILLING_INVALID_ACCOUNT_SOUCE                    _HRESULT_TYPEDEF_(0x80169c4d) // Account source is not valid.
#define XONLINE_E_BILLING_INVALID_CREATION_DATE                    _HRESULT_TYPEDEF_(0x80169c4e) // Creation date cannot be later than current time.
#define XONLINE_E_BILLING_EXCEEDING_TAX_EXEMPT_LIMITS              _HRESULT_TYPEDEF_(0x80169c55) // No more tax exemptions allowed for this account.
#define XONLINE_E_BILLING_GENERATE_NEXT_ID                         _HRESULT_TYPEDEF_(0x80169c59) // Generating next id
#define XONLINE_E_BILLING_INVALID_STATE_FOR_COUNTRY                _HRESULT_TYPEDEF_(0x80169c5f) // The specified state for the country is invalid
#define XONLINE_E_BILLING_INVALID_BILLABLE_ACCOUNT_ID              _HRESULT_TYPEDEF_(0x80169cc2) // Invalid account
#define XONLINE_E_BILLING_INVALID_BILLABLE_ACCOUNT_STATUS_ID       _HRESULT_TYPEDEF_(0x80169cc7) // The account status specified is invalid
#define XONLINE_E_BILLING_INVALID_PHONE_TYPE                       _HRESULT_TYPEDEF_(0x80169cd6) // Invalid Phone Type
#define XONLINE_E_BILLING_INVALID_OFFERING_ID                      _HRESULT_TYPEDEF_(0x80169ce5) // Invalid Offering was specified
#define XONLINE_E_BILLING_INVALID_COUNTRY_CODE                     _HRESULT_TYPEDEF_(0x80169cea) // The country code specified is not valid
#define XONLINE_E_BILLING_INVALID_ADDRESS_ID                       _HRESULT_TYPEDEF_(0x80169cef) // The address id specified is not valid.
#define XONLINE_E_BILLING_INVALID_PAYMENT_METHOD_ID                _HRESULT_TYPEDEF_(0x80169cf9) // The payment instrument ID specified is invalid.
#define XONLINE_E_BILLING_SUBSCRIPTION_ALREADY_CANCELED            _HRESULT_TYPEDEF_(0x80169d08) // The subscription has already been cancelled.
#define XONLINE_E_BILLING_INVALID_SUBSCRIPTION_ID                  _HRESULT_TYPEDEF_(0x80169d0d) // The subscription id specified is invalid
#define XONLINE_E_BILLING_INVALID_PERIOD_TO_PROCESS                _HRESULT_TYPEDEF_(0x80169d2b) // An invalid period was specified.
#define XONLINE_E_BILLING_INVALID_SUBSCRIPTION_STATUS              _HRESULT_TYPEDEF_(0x80169d3a) // An invalid subscription status was specified or the state of the specified subscription does not allow this operation.
#define XONLINE_E_BILLING_VATID_DOESNOTHAVEEXPDATE                 _HRESULT_TYPEDEF_(0x80169d95) // VATIDs do not have an expiration date
#define XONLINE_E_BILLING_TAXID_EXPDATE                            _HRESULT_TYPEDEF_(0x80169d96) // Expiration date was not specified
#define XONLINE_E_BILLING_INVALID_TAX_EXEMPT_TYPE                  _HRESULT_TYPEDEF_(0x80169d97) // Invalid Tax Exempt specified
#define XONLINE_E_BILLING_NO_ACTIVE_SUBSCRIPTION                   _HRESULT_TYPEDEF_(0x80169d99) // No active subscription for adding service instance
#define XONLINE_E_BILLING_INVALID_SERVICE_INSTANCE                 _HRESULT_TYPEDEF_(0x80169d9e) // Invalid service instance for adding new user
#define XONLINE_E_BILLING_ADD_USER_TO_SERVICE_INSTANCE             _HRESULT_TYPEDEF_(0x80169da3) // Failed to add a new user to a service instance
#define XONLINE_E_BILLING_INVALID_BILLABLEACCTSTATUS               _HRESULT_TYPEDEF_(0x80169da8) // The attempted status change operation is inappropriate
#define XONLINE_E_BILLING_SERVICE_INSTANCES_NONE                   _HRESULT_TYPEDEF_(0x80169dbc) // No service instances available for specified billable account
#define XONLINE_E_BILLING_ACCOUNT_CLOSED                           _HRESULT_TYPEDEF_(0x80169dd1) // The Account is already closed
#define XONLINE_E_BILLING_BILLINGPERIOD_PAST                       _HRESULT_TYPEDEF_(0x80169dd6) // This period occurs in the past
#define XONLINE_E_BILLING_INVALID_ADJUSTMENTGUID                   _HRESULT_TYPEDEF_(0x80169dd7) // Invalid AdjustmentGUID
#define XONLINE_E_BILLING_INVALID_ADJUSMENT_FOR_PERIOD             _HRESULT_TYPEDEF_(0x80169dd8) // This Adjustment not applicable to the specified period
#define XONLINE_E_BILLING_ADJUSTMENT_TOOBIG                        _HRESULT_TYPEDEF_(0x80169dd9) // Adjustment amount is too big
#define XONLINE_E_BILLING_ADJUSTMENT_TOOSMALL                      _HRESULT_TYPEDEF_(0x80169ddb) // Adjustment amount is too small
#define XONLINE_E_BILLING_INVALID_LOCALE                           _HRESULT_TYPEDEF_(0x80169de5) // Locale string is not a valid locale
#define XONLINE_E_BILLING_INVALID_CUSTOMER_TYPE                    _HRESULT_TYPEDEF_(0x80169de6) // Customer type is not valid
#define XONLINE_E_BILLING_INVALID_CURRENCY                         _HRESULT_TYPEDEF_(0x80169de7) // Currency string is not a valid currency
#define XONLINE_E_BILLING_DATE_EXPIRED                             _HRESULT_TYPEDEF_(0x80169de8) // The date is already expired
#define XONLINE_E_BILLING_GUID_EXISTS                              _HRESULT_TYPEDEF_(0x80169de9) // The guid passed in already exists in the system
#define XONLINE_E_BILLING_INVALID_VIOLATION_ID                     _HRESULT_TYPEDEF_(0x80169dec) // The specified Violation Id is invalid
#define XONLINE_E_BILLING_MISSING_VIOLATION_ID                     _HRESULT_TYPEDEF_(0x80169ded) // The Violation Id is required
#define XONLINE_E_BILLING_NEEDTODEPROVISION                        _HRESULT_TYPEDEF_(0x80169def) // You should deprovision some serviceinstances to proceed
#define XONLINE_E_BILLING_PARTIALCONV_INITIATED                    _HRESULT_TYPEDEF_(0x80169df0) // Partial Conversion is already initiated.
#define XONLINE_E_BILLING_PARTIALCONV_EXPECTED                     _HRESULT_TYPEDEF_(0x80169df2) // The subscription is expected to be in the partial state.
#define XONLINE_E_BILLING_INVALID_CATEGORY_NAME                    _HRESULT_TYPEDEF_(0x80169df3) // Category string is not a valid catergory
#define XONLINE_E_BILLING_OFFERING_NOT_PURCHASEABLE                _HRESULT_TYPEDEF_(0x80169df5) // Offering is not purchaseable at this time
#define XONLINE_E_BILLING_OFFERING_ACCOUNT_CURRENCY_MISMATCH       _HRESULT_TYPEDEF_(0x80169df6) // The offering currency does not match the account currency
#define XONLINE_E_BILLING_OFFERING_PAYMENT_INSTRUMENT_MISMATCH     _HRESULT_TYPEDEF_(0x80169df7) // The specified offering does not support the given payment instrument type
#define XONLINE_E_BILLING_INVALID_DATE                             _HRESULT_TYPEDEF_(0x80169df8) // A date specified is not a valid date.
#define XONLINE_E_BILLING_CANNOT_EXCEED_MAX_OWNERSHIP              _HRESULT_TYPEDEF_(0x80169df9) // Cannot exceed max ownership for this offering
#define XONLINE_E_BILLING_INVALID_RESOURCE_ID                      _HRESULT_TYPEDEF_(0x80169e02) // Invalid resource ID.
#define XONLINE_E_BILLING_UNIT_OF_MEASURE_MISMATCH                 _HRESULT_TYPEDEF_(0x80169e03) // The unit of measure reported in the usage event doesn't match the one configed in billing system.
#define XONLINE_E_BILLING_INVALID_OFFERING_FOR_LOCALE              _HRESULT_TYPEDEF_(0x80169e05) // Offering doesn't exist for this Locale.
#define XONLINE_E_BILLING_NOT_A_BASE_OFFERING                      _HRESULT_TYPEDEF_(0x80169e06) // Offering is not a base offering.
#define XONLINE_E_BILLING_INVALID_ACCOUNT_STATUS                   _HRESULT_TYPEDEF_(0x80169e16) // Account state does not allow this operation.
#define XONLINE_E_BILLING_ACTIVE_SUBSCRIPTIONS_EXIST               _HRESULT_TYPEDEF_(0x80169e1b) // Active subscriptions exist on this payment instrument.
#define XONLINE_E_BILLING_PRIMARY_PHONE_REQUIRED                   _HRESULT_TYPEDEF_(0x80169e25) // Primary phone required for payment instruments.
#define XONLINE_E_BILLING_EMAIL_REQUIRED                           _HRESULT_TYPEDEF_(0x80169e2a) // An Email address on the account is required for this operation.
#define XONLINE_E_BILLING_ACCOUNT_NOT_CLOSED                       _HRESULT_TYPEDEF_(0x80169e2b) // The account should be in CLOSED state to perform this operation.
#define XONLINE_E_BILLING_INVALID_VIOLATION                        _HRESULT_TYPEDEF_(0x80169e13) // Violation is invalid.
#define XONLINE_E_BILLING_SUBSCRIPTION_IS_CANCELLED                _HRESULT_TYPEDEF_(0x80169e14) // The subscription is cancelled, and cannot change status.
#define XONLINE_E_BILLING_NO_VIOLATION                             _HRESULT_TYPEDEF_(0x80169e15) // No violation exists on this subscription.
#define XONLINE_E_BILLING_EXISTS_VIOLATION                         _HRESULT_TYPEDEF_(0x80169e17) // There are violations on this subscription.
#define XONLINE_E_BILLING_END_DATE_IN_THE_PAST                     _HRESULT_TYPEDEF_(0x80169e33) // The end date passed in is in the past.
#define XONLINE_E_BILLING_END_DATE_BEYOND_MAX                      _HRESULT_TYPEDEF_(0x80169e34) // The end date passed in is beyond the maximum allowable end date for this subscription.
#define XONLINE_E_BILLING_VIOLATION_ALREADY_SET                    _HRESULT_TYPEDEF_(0x80169e3e) // The violation is already set.
#define XONLINE_E_BILLING_NO_VIOLATION_SET                         _HRESULT_TYPEDEF_(0x80169e43) // No violation of this ID is set.
#define XONLINE_E_BILLING_INVALID_CONVERSION                       _HRESULT_TYPEDEF_(0x80169e4d) // This conversion path is not allowed.
#define XONLINE_E_BILLING_SUBS_NOT_INTERMEDIATE                    _HRESULT_TYPEDEF_(0x80169e4e) // The subscription is not in the partial state.
#define XONLINE_E_BILLING_OFFERING_NOT_PUBLISHED                   _HRESULT_TYPEDEF_(0x80169e52) // The Offering is not published.
#define XONLINE_E_BILLING_CONVERSION_NEEDTODEPROVISION             _HRESULT_TYPEDEF_(0x80169e53) // Some ServiceInstances need to be deprovisioned inorder to continue.
#define XONLINE_E_BILLING_INVALID_MANDATE_STATUS                   _HRESULT_TYPEDEF_(0x80169e57) // The mandate status specified is not valid.
#define XONLINE_E_BILLING_PI_ALREADY_GOOD                          _HRESULT_TYPEDEF_(0x80169e61) // Payment instrument status is already GOOD.
#define XONLINE_E_BILLING_PI_ALREADY_DECLINED                      _HRESULT_TYPEDEF_(0x80169e66) // Payment instrument status is already DECLINED.
#define XONLINE_E_BILLING_PI_IS_DISABLED                           _HRESULT_TYPEDEF_(0x80169e6b) // Payment instrument status is DISABLED and cannot be changed to any other status.
#define XONLINE_E_BILLING_INVALID_OFFERING_GUID                    _HRESULT_TYPEDEF_(0x80169e84) // Invalid Offering GUID.
#define XONLINE_E_BILLING_OFFERING_REQUIRES_PI                     _HRESULT_TYPEDEF_(0x80169e89) // The offering specified requires a payment instrument to be specified.
#define XONLINE_E_BILLING_DELAYED_PROVISIONING_COMPONENTS_EXIST    _HRESULT_TYPEDEF_(0x80169e93) // The offering cannot be purchased because it has delayed provisioning components.
#define XONLINE_E_BILLING_INVALID_AMOUNT_FOR_CURRENCY              _HRESULT_TYPEDEF_(0x80169e99) // Amount cannot be adjusted because it does not follow guideline of Currency (JPY or KRW).
#define XONLINE_E_BILLING_INVALID_EMAIL_ADDRESS                    _HRESULT_TYPEDEF_(0x80169ea2) // The email address specified is not a valid email address.
#define XONLINE_E_BILLING_INVALID_TAX_EXEMPT_STATUS                _HRESULT_TYPEDEF_(0x80169eac) // The tax exemption status specified is invalid.
#define XONLINE_E_BILLING_INVALID_OLD_PAYMENT_INSTRUMENT_STATUS    _HRESULT_TYPEDEF_(0x80169eb6) // The status of the old payment instrument does not allow this operation.
#define XONLINE_E_BILLING_LAST_ADMIN_ROLE                          _HRESULT_TYPEDEF_(0x8016c3c3) // It is illegal to remove the last administrator role on the account.
#define XONLINE_E_BILLING_UPDATING_MEMBERNAME                      _HRESULT_TYPEDEF_(0x8016c3c8) // Error updating membername.
#define XONLINE_E_BILLING_OBJECT_ROLE_LIMIT_EXCEEDED               _HRESULT_TYPEDEF_(0x8016c3cd) // This object has exceeded it's role limit of 100.
#define XONLINE_E_BILLING_MALFORMED_REQUEST                        _HRESULT_TYPEDEF_(0x8016ab7d) // Provision.dll: Provision request malformed
#define XONLINE_E_BILLING_WRONG_INPUT_PARAMETERS                   _HRESULT_TYPEDEF_(0x8016ab7e) // Provision.dll: Wrong input parameters
#define XONLINE_E_BILLING_MPF_CALL_FAILED                          _HRESULT_TYPEDEF_(0x8016ab7f) // Provision.dll: Microsoft Provisioning Framework call failed. %1
#define XONLINE_E_BILLING_XML_OPERATION_ERROR                      _HRESULT_TYPEDEF_(0x8016ab80) // Provision.dll: Error during XML manipulation. %1
#define XONLINE_E_BILLING_MPF_CREATE                               _HRESULT_TYPEDEF_(0x8016ab81) // Provision.dll: MPF client instantiation failed. %1
#define XONLINE_E_BILLING_CREATION                                 _HRESULT_TYPEDEF_(0x8016ab82) // Provision.dll: General error in sturtup code. %1
#define XONLINE_E_BILLING_INCREMENT_TOTAL                          _HRESULT_TYPEDEF_(0x80164e39) // Cannot update total as requested.
#define XONLINE_E_BILLING_RES_NOT_BELONG_TO_OBJECT                 _HRESULT_TYPEDEF_(0x80164e57) // The resource doesn't belong to this service instance.
#define XONLINE_E_BILLING_DECLINING_BALANCE                        _HRESULT_TYPEDEF_(0x80164e5c) // The payment instrument on the current subscription has a declining balance
#define XONLINE_E_BILLING_DUPLICATE_TRACKING_GUID                  _HRESULT_TYPEDEF_(0x80164e75) // Attempted to insert Duplicate Tracking Guid into detail_event table.
#define XONLINE_E_BILLING_INVALID_EXPIRATION_DATE                  _HRESULT_TYPEDEF_(0x80164ea7) // The credit card expiration date specified is invalid
#define XONLINE_E_BILLING_UNKNOWN_MANDATE_STATUS                   _HRESULT_TYPEDEF_(0x80164eac) // The mandate status specified is invalid
#define XONLINE_E_BILLING_INVALID_CURRENCY2                        _HRESULT_TYPEDEF_(0x80164ec0) // The input currency is incorrect.
#define XONLINE_E_BILLING_INVALID_BILLING_PERIOD                   _HRESULT_TYPEDEF_(0x80164f42) // Invalid billing period passed
#define XONLINE_E_BILLING_INVALID_ANNIV                            _HRESULT_TYPEDEF_(0x80164f9c) // Invalid billing anniversary date passed in as argument.
#define XONLINE_E_BILLING_INVALID_LINEITEM_ID                      _HRESULT_TYPEDEF_(0x80164ff6) // Invalid line item id
#define XONLINE_E_BILLING_LINE_ITEM_ID_NOT_OPEN                    _HRESULT_TYPEDEF_(0x80165046) // the specified line_item_id is not associated with a open record
#define XONLINE_E_BILLING_LINEITEM_ALREADY_OFFSET                  _HRESULT_TYPEDEF_(0x8016504b) // The line item has already been offset!
#define XONLINE_E_BILLING_INVALID_OFFSET_AMOUNT                    _HRESULT_TYPEDEF_(0x80165050) // Offset amount must be greater than 0 but no greater than original amount!
#define XONLINE_E_BILLING_CANNOT_OFFSET_HARD_SOFT_DECLINED         _HRESULT_TYPEDEF_(0x80165055) // cannot offset line item which is soft/hard declined!
#define XONLINE_E_BILLING_AMOUNT_NOT_COLLECTED_YET                 _HRESULT_TYPEDEF_(0x8016505a) // Amount has not been collected yet, cannot be offset and immediately settled.
#define XONLINE_E_BILLING_CANNOT_OFFSET_ZERO_AMOUNT                _HRESULT_TYPEDEF_(0x8016505f) // Cannot offset zero amount
#define XONLINE_E_BILLING_AMOUNT_IN_PROCESS                        _HRESULT_TYPEDEF_(0x80165064) // Amount in the process of being sent to the bank, cannot offset.
#define XONLINE_E_BILLING_INVALID_CREDIT_AMOUNT                    _HRESULT_TYPEDEF_(0x80165082) // Credit amount should not be 0.
#define XONLINE_E_BILLING_OFFSET_IMM_SETTLE_IN_PROG                _HRESULT_TYPEDEF_(0x8016509b) // It's not allowed to offset line item which is immediate_settle_in_progress state.
#define XONLINE_E_BILLING_SA_IN_STATE_UNOFFSETABLE                 _HRESULT_TYPEDEF_(0x801650a5) // The status of the settlement amount containing the line item indicates that the item can't be offset.
#define XONLINE_E_BILLING_OFFSET_AMOUNT_GREATER_THAN_ORIGINAL      _HRESULT_TYPEDEF_(0x801650aa) // The offset amount should never be greater than the original item amount.
#define XONLINE_E_BILLING_RES_BALANCE_CHANGE_ON_NONACTIVE_SUBS     _HRESULT_TYPEDEF_(0x801650af) // It's not allowed to change a resource balance for a nonactive subscription.
#define XONLINE_E_BILLING_PMN_INSERT_FAILURE                       _HRESULT_TYPEDEF_(0x801661bc) // The member name for this passport could not be added.
#define XONLINE_E_BILLING_BADSAMECARDUSEDMULTIPLETIMES             _HRESULT_TYPEDEF_(0x801661d0) // The same payment card number has been used for multiple times.
#define XONLINE_E_BILLING_PI_ALREADY_ON_ACCOUNT                    _HRESULT_TYPEDEF_(0x801661df) // The same payment instrument is already on the given account
#define XONLINE_E_BILLING_PUID_ROLE_LIMIT_EXCEEDED                 _HRESULT_TYPEDEF_(0x801661e4) // This Passport ID has exceeded it's role limit of 100.
#define XONLINE_E_BILLING_XPATHOBJECT_NOTFOUND                     _HRESULT_TYPEDEF_(0x80162710) // A select node operation failed.
#define XONLINE_E_BILLING_NOPERMISSION                             _HRESULT_TYPEDEF_(0x80162711) // Access Denied
#define XONLINE_E_BILLING_CANNOT_REMOVE_SELF                       _HRESULT_TYPEDEF_(0x80162712) // Cannot remove self from object
#define XONLINE_E_BILLING_BADXML                                   _HRESULT_TYPEDEF_(0x80162713) // The XML passed in may be malformed or may not meet the SPK requirements for this API
#define XONLINE_E_BILLING_INVALIDCOMMENTSIZE                       _HRESULT_TYPEDEF_(0x80162714) // Comment text length must be 1 to 512
#define XONLINE_E_BILLING_BADCANCELMODE                            _HRESULT_TYPEDEF_(0x80162715) // The cancel mode specified is invalid
#define XONLINE_E_BILLING_INVALID_BUF_SIZE                         _HRESULT_TYPEDEF_(0x80162716) // The input parameter has a wrong size
#define XONLINE_E_BILLING_INVALID_ROLE                             _HRESULT_TYPEDEF_(0x80162717) // The role specified is invalid
#define XONLINE_E_BILLING_INVALID_PPORT_ID                         _HRESULT_TYPEDEF_(0x80162718) // The passport id specified is invalid
#define XONLINE_E_BILLING_INVALID_ARG                              _HRESULT_TYPEDEF_(0x8016271a) // The argument specified is invalid
#define XONLINE_E_BILLING_UNKNOWN_SERVER_FAILURE                   _HRESULT_TYPEDEF_(0x8016271f) // Unknown server failure.
#define XONLINE_E_BILLING_INVALID_STATUS_VALUE                     _HRESULT_TYPEDEF_(0x80162720) // Invalid Status.  Must be ENABLED or SUSPENDED.
#define XONLINE_E_BILLING_INVALID_FILTER                           _HRESULT_TYPEDEF_(0x80162721) // The filter field is invalid.  It must be one of "Base", "Upgrade", "Downgrade", or "Renewal", or leave the filter empty.
#define XONLINE_E_BILLING_MISSING_CATEGORY                         _HRESULT_TYPEDEF_(0x80162722) // The Category field is missing.
#define XONLINE_E_BILLING_FIELD_TOO_SHORT                          _HRESULT_TYPEDEF_(0x80162723) // The input field is too short.
#define XONLINE_E_BILLING_FIELD_TOO_LONG                           _HRESULT_TYPEDEF_(0x80162724) // The input field is too long.
#define XONLINE_E_BILLING_BADZIP                                   _HRESULT_TYPEDEF_(0x80162725) // The specified zip code is incorrect
#define XONLINE_E_BILLING_ONLYONENODE                              _HRESULT_TYPEDEF_(0x80162726) // Only one of these nodes should be passed in.
#define XONLINE_E_BILLING_CSR_AUTHZ_FAILED                         _HRESULT_TYPEDEF_(0x80162728) // Only CSR callers can invoke this API.
#define XONLINE_E_BILLING_NOT_ACCOUNT_ADMIN                        _HRESULT_TYPEDEF_(0x80162729) // The caller is not an administrator of the specified account.
#define XONLINE_E_BILLING_DELEGATE_ID_UNSPECIFIED                  _HRESULT_TYPEDEF_(0x8016272a) // The delegate passport id must be specified for CSR callers.
#define XONLINE_E_BILLING_REQUESTER_ID_UNSPECIFIED                 _HRESULT_TYPEDEF_(0x8016272b) // The requester passport id must be specified.
#define XONLINE_E_BILLING_INVALID_FLAG_VALUE                       _HRESULT_TYPEDEF_(0x8016272c) // Boolean Value must be 0, 1
#define XONLINE_E_BILLING_PROVISIONING_INACTIVE_SUBSCRIPTION       _HRESULT_TYPEDEF_(0x8016272d) // Provisioning service instance for subscription status being different than active
#define XONLINE_E_BILLING_INVALID_OBJECT_ID                        _HRESULT_TYPEDEF_(0x8016272e) // The Object specified is invalid.
#define XONLINE_E_BILLING_PARTNERNOTINBILLING                      _HRESULT_TYPEDEF_(0x80162738) // The calling partner is not registered in our database.
#define XONLINE_E_BILLING_RATING_FAILURE                           _HRESULT_TYPEDEF_(0x8016273d) // A rating error has occurred, check the event log and the tracer.
#define XONLINE_S_BILLING_SVR2_STARTED                             _HRESULT_TYPEDEF_(0x80162742) // BDKSVR2 started.
#define XONLINE_S_BILLING_CSR_API_CALL_MADE                        _HRESULT_TYPEDEF_(0x80162743) // CSR call made.
#define XONLINE_E_BILLING_CSR_CALL_FROM_NONCSR                     _HRESULT_TYPEDEF_(0x80162744) // CSR call ATTEMPT BY NON CSR CALLER
#define XONLINE_E_BILLING_TRANS_BALANCE_MISMATCHING_ACCTS          _HRESULT_TYPEDEF_(0x8016274c) // from and to PI not on the same account in TransferBalance
#define XONLINE_E_BILLING_TRANS_BALANCE_TO_PI_INVALID              _HRESULT_TYPEDEF_(0x80162751) // transfer-to PI not in good status in TransferBalance
#define XONLINE_E_BILLING_TRANS_BALANCE_TO_SAME_PI                 _HRESULT_TYPEDEF_(0x80162756) // transfer-to same PI in TransferBalance
#define XONLINE_E_BILLING_TRANS_BALANCE_NOT_ALLOW                  _HRESULT_TYPEDEF_(0x8016275b) // Transferring a balance between the Payment Instrument types is not allowed
#define XONLINE_E_BILLING_INTERNAL_ERROR                           _HRESULT_TYPEDEF_(0x80162760) // Internal database inconsistencies were detected.
#define XONLINE_E_BILLING_OUTSTANDING_BALANCE                      _HRESULT_TYPEDEF_(0x80162765) // A outstanding balance exists on this payment instrument.
#define XONLINE_E_BILLING_INVALID_REFERRALDATA_XML                 _HRESULT_TYPEDEF_(0x8016276a) // Invalid ReferralData XML.  Check to make sure it exists, is between 1 and 1024 characters, and is valid xml.
#define XONLINE_E_BILLING_INVALID_GUID                             _HRESULT_TYPEDEF_(0x8016276f) // The guid specified is invalid
#define XONLINE_E_BILLING_UNSUPPORTED_PAYMENT_INSTRUMENT           _HRESULT_TYPEDEF_(0x80162774) // unsupported payment instrument type for settlebalance
#define XONLINE_E_BILLING_SUBSCRIPTION_INACTIVE                    _HRESULT_TYPEDEF_(0x80162779) // The subscription is not active.
#define XONLINE_E_BILLING_INVALID_PM_FOR_STOP_PAYMENTS             _HRESULT_TYPEDEF_(0x8016277e) // Cannot stop payments for Qwest payment method type.
#define XONLINE_E_BILLING_EXCEEDS_MAX_NUMBER_OF_USAGE_EVENTS       _HRESULT_TYPEDEF_(0x80162783) // The number of usage events reported through one ReportUsageEvent() call exceeds the maximum system can handle.
#define XONLINE_E_BILLING_FIELD_NOT_UPDATEABLE                     _HRESULT_TYPEDEF_(0x80162788) // A field specified is not updateable.
#define XONLINE_E_BILLING_DEFERRED_COMPUTE_ONLY_NOT_SUPPORTED      _HRESULT_TYPEDEF_(0x8016278d) // Calling CancelSubscription with an end date and in compute only mode is not supported.
#define XONLINE_E_BILLING_SETTLE_SHOULD_BE_THE_LAST_EVENT          _HRESULT_TYPEDEF_(0x8016278e) // The SETTLE type event should be the last one in the event list of importsettlebillingitems.
#define XONLINE_E_BILLING_PAYMENT_METHOD_NO_LONGER_VALID           _HRESULT_TYPEDEF_(0x8016278f) // The payment method used to pay for the line item is no long valid.
#define XONLINE_E_BILLING_PROCESS_USAGE_EVENTS                     _HRESULT_TYPEDEF_(0x80162790) // Failed to process some of the usage events.
#define XONLINE_E_BILLING_WRONG_OBJECT_ID_TYPE                     _HRESULT_TYPEDEF_(0x80162791) // The object ID does not contain account, subscription info.
#define XONLINE_E_BILLING_INVALID_PHONE_VALUE                      _HRESULT_TYPEDEF_(0x80162792) // The field contains invalid characters for a phone number
#define XONLINE_E_BILLING_INVALID_AMOUNT_VALUE                     _HRESULT_TYPEDEF_(0x80162797) // Amount value is invalid
#define XONLINE_E_BILLING_MISMATCH_ACCTID_IN_CLOSEBALANCE          _HRESULT_TYPEDEF_(0x80162793) // The Payment InstrumentId and the Line Item Id do not match
#define XONLINE_E_BILLING_INTERNAL_ADD_COMMENT_FAILED              _HRESULT_TYPEDEF_(0x80162794) // InternalAddComment failed. This needs to be escalated to SPG development.
#define XONLINE_E_BILLING_INVALID_IMMEDIATE_SETTLE_VALUE           _HRESULT_TYPEDEF_(0x80162795) // Only FALSE is supported for the immediate settle flag.
#define XONLINE_E_BILLING_NO_RECORDS_FOR_STOP_PAYMENTS             _HRESULT_TYPEDEF_(0x8016279c) // No eligible records were found for StopPayments API call.
#define XONLINE_E_BILLING_TAXWARE_FAILURE                          _HRESULT_TYPEDEF_(0x8016ea60) // A taxware error has occurred, check the event log and the tracer.
#define XONLINE_E_BILLING_ADDRESS_VALIDATION_FAILURE               _HRESULT_TYPEDEF_(0x8016ea61) // An error has occurred while validating address, check the event log and the tracer.
#define XONLINE_E_BILLING_ZIP_INVALID                              _HRESULT_TYPEDEF_(0x8016ea6b) // VERAZIP: ZIP Code has not been found in the database.
#define XONLINE_E_BILLING_STATE_INVALID                            _HRESULT_TYPEDEF_(0x8016ea6c) // VERAZIP: Invalid State Code passed.
#define XONLINE_E_BILLING_ZIP_CITY_MISSING                         _HRESULT_TYPEDEF_(0x8016ea6d) // VERAZIP: No Zip Code or City Name passed.
#define XONLINE_E_BILLING_STATE_ZIP_INVALID                        _HRESULT_TYPEDEF_(0x8016ea6e) // VERAZIP: State Code/ZIP Code combination passed has not been found.
#define XONLINE_E_BILLING_STATE_CITY_INVALID                       _HRESULT_TYPEDEF_(0x8016ea6f) // VERAZIP: State Code/City Name combination passed has not been found.
#define XONLINE_E_BILLING_STATE_ZIP_CITY_INVALID                   _HRESULT_TYPEDEF_(0x8016ea70) // VERAZIP: State Code/ZIP Code/City Name combination passed has not been found. Neither State Code/ZIP Code combination nor State Code/City Name combination could be found. Currently BDK doesn't return any data, this text is from VeraZip documentation.
#define XONLINE_E_BILLING_STATE_ZIP_CITY_INVALID2                  _HRESULT_TYPEDEF_(0x8016ea71) // VERAZIP: State Code, ZIP Code and City Name combination passed has not been found. Returned all ZIP codes associated with State Code/City Name combination. Currently BDK doesn't return any data, this text is from VeraZip documentation.
#define XONLINE_E_BILLING_STATE_ZIP_CITY_INVALID3                  _HRESULT_TYPEDEF_(0x8016ea72) // VERAZIP: State Code, ZIP Code and City Name combination passed has not been found. Returned all City Names and ZIP Code Extensions associated with State Code/ Zip Code combination. Currently BDK doesn't return any data, this text is from VeraZip documentation.
#define XONLINE_E_BILLING_STATE_ZIP_CITY_INVALID4                  _HRESULT_TYPEDEF_(0x8016ea73) // VERAZIP: State Code, ZIP Code and City Name combination passed has not been found. The error could be because you didn't pass in the state code.
#define XONLINE_E_BILLING_MULTIPLE_COUNTIES_FOUND                  _HRESULT_TYPEDEF_(0x8016ea7d) // VERAZIP: Two or more counties were found for State Code, ZIP Code and City Name combination. Returned all County Codes. Currently BDK doesn't return any data, this text is from VeraZip documentation.
#define XONLINE_E_BILLING_ZIP_INVALID_FOR_ENTERED_STATE            _HRESULT_TYPEDEF_(0x8016ea7e) // VERAZIP: Zip Code not valid for State Code entered.  Defaulted to State Code that matches ZIP Code entered.
#define XONLINE_E_BILLING_STATE_ZIP_COVERS_MULTIPLE_CITIES         _HRESULT_TYPEDEF_(0x8016ea89) // VERAZIP: Valid State Code and Zip Code passed, but the Zip Code covers multiple City Names. Returned all City Names for this ZIP Code. Currently BDK doesn't return any data, this text is from VeraZip documentation.
#define XONLINE_E_BILLING_MULTIPLE_CITIES_FOUND                    _HRESULT_TYPEDEF_(0x8016ea8a) // VERAZIP: Valid State Code and City Name passed, but the city has multiple ZIP Codes. Returned all ZIP Codes for this city. Currently BDK doesn't return any data, this text is from VeraZip documentation.
#define XONLINE_E_BILLING_BAD_CITYNAME_LENGTH                      _HRESULT_TYPEDEF_(0x8016ea8b) // City name length is incorrect.
#define XONLINE_E_BILLING_BAD_COUNTRYCODE_LENGTH                   _HRESULT_TYPEDEF_(0x8016ea8c) // Country code length is incorrect.
#define XONLINE_E_BILLING_BAD_STATECODE_LENGTH                     _HRESULT_TYPEDEF_(0x8016ea8d) // State/Province code length is incorrect.
#define XONLINE_E_BILLING_BAD_ZIPCODE_LENGTH                       _HRESULT_TYPEDEF_(0x8016ea8e) // Zip code length is incorrect.
#define XONLINE_E_BILLING_BAD_PRODUCTCODE_LENGTH                   _HRESULT_TYPEDEF_(0x8016ea8f) // Product code length is incorrect.
#define XONLINE_E_BILLING_BAD_BUSINESSLOCATIONCODE_LENGTH          _HRESULT_TYPEDEF_(0x8016ea90) // Business location code length is incorrect.
#define XONLINE_E_BILLING_BAD_TRANSACTIONDATE_LENGTH               _HRESULT_TYPEDEF_(0x8016ea91) // Transaction date length is incorrect.
#define XONLINE_E_BILLING_BAD_VATREGISTRATION_LENGTH               _HRESULT_TYPEDEF_(0x8016ea92) // VAT registration length is incorrect.
#define XONLINE_E_BILLING_BAD_CURRENCYCODE_LENGTH                  _HRESULT_TYPEDEF_(0x8016ea93) // Currency code length is incorrect.
#define XONLINE_E_BILLING_BAD_WTCODE_LENGTH                        _HRESULT_TYPEDEF_(0x8016ea94) // WorldTax code length is incorrect.
#define XONLINE_E_BILLING_INVALID_INPUT_TO_TAXWARE_OR_VERAZIP      _HRESULT_TYPEDEF_(0x8016ea95) // Invalid input parameter was passed to TaxWare or the VeraZip system.
#define XONLINE_E_BILLING_UNSUPPORTED_CHAR_EXIST                   _HRESULT_TYPEDEF_(0x8016ea9c) // There are unsupported characters or sequences of characters existing in the input BSTR or XML.
#define XONLINE_E_BILLING_PI_IN_DECLINE                            _HRESULT_TYPEDEF_(0x801650c8) // the payment instrument already has declines on it, transferbalance not allowed


//
// Macro for detecting error status.
// Error codes start at 400 (HTTP_STATUS_BAD_REQUEST).
//
#define XONLINE_HTTPSTATUS_ANYERROR(status)     ((status >= 400) ? TRUE : FALSE)

//
// HRs for _XPassport* APIs
//

#define XONLINE_E_PASSPORT_NAME_ALREADY_TAKEN                      _HRESULT_TYPEDEF_(0x8015d001) // Failed to create passport: name already taken
#define XONLINE_E_PASSPORT_WRONG_NAME_OR_PASSWORD                  _HRESULT_TYPEDEF_(0x8015d002) // Wrong password and/or membername dose not exist.
#define XONLINE_E_PASSPORT_LOCKED_OUT                              _HRESULT_TYPEDEF_(0x8015d003) // The credential is locked out.
#define XONLINE_E_PASSPORT_FORCE_RENAME                            _HRESULT_TYPEDEF_(0x8015d004) // The credential is in a forced renamed state
#define XONLINE_E_PASSPORT_FORCE_CHANGE_PASSWORD                   _HRESULT_TYPEDEF_(0x8015d005) // The password has to be changed.
#define XONLINE_E_PASSPORT_FORCE_CHANGE_SQ_SA                      _HRESULT_TYPEDEF_(0x8015d006) // The secret question and answer has to be changed.
#define XONLINE_E_PASSPORT_PASSWORD_EXPIRED                        _HRESULT_TYPEDEF_(0x8015d007) // The password for the account has expired.
#define XONLINE_E_PASSPORT_REQUIRE_EMAIL_VALIDATION                _HRESULT_TYPEDEF_(0x8015d008) // The account is blocked pending email address validation.
#define XONLINE_E_FORBIDDEN_WORD                                   _HRESULT_TYPEDEF_(0x8015d009) // String contained words that are forbidden by namespace administrator, examine input.
#define XONLINE_E_PASSWORD_BLANK                                   _HRESULT_TYPEDEF_(0x8015d00a) // The password is blank.
#define XONLINE_E_PASSWORD_TOO_SHORT                               _HRESULT_TYPEDEF_(0x8015d00b) // The password is too short
#define XONLINE_E_PASSWORD_TOO_LONG                                _HRESULT_TYPEDEF_(0x8015d00c) // The password is too long
#define XONLINE_E_PASSWORD_CONTAINS_MEMBER_NAME                    _HRESULT_TYPEDEF_(0x8015d00d) // The password contains the member name.
#define XONLINE_E_PASSWORD_CONTAINS_INVALID_CHARACTERS             _HRESULT_TYPEDEF_(0x8015d00e) // The password contains invalid characters.
#define XONLINE_E_SQ_CONTAINS_PASSWORD                             _HRESULT_TYPEDEF_(0x8015d00f) // The secret question contains the password.
#define XONLINE_E_SA_CONTAINS_PASSWORD                             _HRESULT_TYPEDEF_(0x8015d010) // The answer for the secret question contains the password.
#define XONLINE_E_PASSWORD_CONTAINS_SA                             _HRESULT_TYPEDEF_(0x8015d011) // The password validation code detected the answer to the secret question in the password.
#define XONLINE_E_SQ_CONTAINS_SA                                   _HRESULT_TYPEDEF_(0x8015d015) // The secret question contains the answer.
#define XONLINE_E_SA_TOO_SHORT                                     _HRESULT_TYPEDEF_(0x8015d017)
#define XONLINE_E_SA_CONTAINS_SQ                                   _HRESULT_TYPEDEF_(0x8015d018) // The answer to the secret question contains that question.
#define XONLINE_E_SA_CONTAINS_MEMBER_NAME                          _HRESULT_TYPEDEF_(0x8015d019) // The answer for the secret question contains the member name.
#define XONLINE_E_MEMBER_NAME_TOO_SHORT                            _HRESULT_TYPEDEF_(0x8015d01a) // The signin name is too short.
#define XONLINE_E_MEMBER_NAME_INVALID                              _HRESULT_TYPEDEF_(0x8015d01b) // The signin name is incomplete or has invalid characters.
#define XONLINE_E_PASSPORT_INVALID_DOMAIN                          _HRESULT_TYPEDEF_(0x8015d01c) // Cannot create EASI passport on reserved domain (e.g. hotmail.com)
#define XONLINE_E_PASSPORT_INVALID_POSTAL_CODE                     _HRESULT_TYPEDEF_(0x8015d01d) // The postal code specified is invalid

//
// Values used in passcodes
//

typedef enum {
    XONLINE_PASSCODE_DPAD_UP = 1,
    XONLINE_PASSCODE_DPAD_DOWN,
    XONLINE_PASSCODE_DPAD_LEFT,
    XONLINE_PASSCODE_DPAD_RIGHT,
    XONLINE_PASSCODE_GAMEPAD_X,
    XONLINE_PASSCODE_GAMEPAD_Y,
    XONLINE_PASSCODE_GAMEPAD_LEFT_TRIGGER = 9,
    XONLINE_PASSCODE_GAMEPAD_RIGHT_TRIGGER,
    XONLINE_PASSCODE_GAMEPAD_LEFT_SHOULDER,
    XONLINE_PASSCODE_GAMEPAD_RIGHT_SHOULDER
} XONLINE_PASSCODE_TYPE;

#pragma pack(push, 1)
typedef struct _USER_ACCOUNT_STATUS_INFO
{
    // Xbox Live user policy

    BOOL       bNewTermsOfService;
    BOOL       bForcedNameChangeRequired;
    FILETIME   ftSuspendedUntil;
    WORD       wTotalDaysSuspended;
    FILETIME   ftVoiceBannedUntil;
    WORD       wTotalDaysVoiceBanned;

    // Billing-related information

    HRESULT    hrBillingAccountStatus;
} USER_ACCOUNT_STATUS_INFO;
#pragma pack(pop)


//
// Define maximum sizes for various fields in the request
//

#define MAX_FIRSTNAME_SIZE       64
#define MAX_LASTNAME_SIZE        64
#define MAX_EMAIL_SIZE           129
#define MAX_PHONE_PREFIX_SIZE    12
#define MAX_PHONE_NUMBER_SIZE    12
#define MAX_PHONE_EXTENSION_SIZE 12
#define MAX_STREET_SIZE          128
#define MAX_CITY_SIZE            64
#define MAX_DISTRICT_SIZE        64
#define MAX_STATE_SIZE           64
#define MAX_COUNTRYCODE_SIZE      2
#define MAX_POSTALCODE_SIZE      16
#define MAX_CC_NAME_SIZE         64
#define MAX_CC_TYPE_SIZE         32
#define MAX_CC_NUMBER_SIZE       24
#define MAX_CC_EXPIRATION_SIZE    6
#define MAX_CC_CCV_NUMBER_SIZE    4
#define MAX_DD_BANK_CODE_SIZE    64
#define MAX_DD_BRANCH_CODE_SIZE  64
#define MAX_DD_CHECK_DIGITS_SIZE 64
#define ACCOUNT_PIN_LENGTH        4
#define VOUCHER_LENGTH           25
#define MAX_VOUCHER_SIZE         VOUCHER_LENGTH+1
#define MAX_BILLING_TOKEN_SIZE   MAX_VOUCHER_SIZE

#define PRIVILEGES_DWORD_LENGTH   8
#define MAX_PRIVILEGE_BITS      256

//
// Privilege bits (also defined in server tree's xonline.x)
//

#define XONLINE_PRIVILEGE_MAX                                   255

// Add Friends
#define XONLINE_PRIVILEGE_ADD_FRIEND                            255 // private, internal only - on|off

// Sessions
#define XONLINE_PRIVILEGE_MULTIPLAYER_SESSIONS                  254 // on|off (on is modified by FRIENDS_ONLY)
#define XONLINE_PRIVILEGE_MULTIPLAYER_ENABLED_BY_TIER           253 // private, internal only - on|off

// Communications
#define XONLINE_PRIVILEGE_COMMUNICATIONS                        252 // on|off (on is modified by FRIENDS_ONLY)
#define XONLINE_PRIVILEGE_COMMUNICATIONS_FRIENDS_ONLY           251 // on=friends only | off=everyone
// Sending video messages is restricted by tier and needs a second bit
#define XONLINE_PRIVILEGE_VIDEO_MESSAGING_SEND                  250 // private, internal only - on|off

// Profile
#define XONLINE_PRIVILEGE_PROFILE_VIEWING                       249 // on|off (on is modified by FRIENDS_ONLY)
#define XONLINE_PRIVILEGE_PROFILE_VIEWING_FRIENDS_ONLY          248 // on=friends only | off=everyone

// Viewing of User Created Content
#define XONLINE_PRIVILEGE_USER_CREATED_CONTENT                  247 // on|off (on is modified by FRIENDS_ONLY)
#define XONLINE_PRIVILEGE_USER_CREATED_CONTENT_FRIENDS_ONLY     246 // sharing on=friends only | off=everyone

// Premium Content Purchases
#define XONLINE_PRIVILEGE_PURCHASE_CONTENT                      245 // on|off

// Presence
#define XONLINE_PRIVILEGE_PRESENCE                              244 // on|off (on is modified by FRIENDS_ONLY)
#define XONLINE_PRIVILEGE_PRESENCE_FRIENDS_ONLY                 243 // on=friends only | off=everyone

// Backward Compatibility
#define XONLINE_PRIVILEGE_XBOX1_LIVE_ACCESS                     242 // private, internal only - on|off

#define XONLINE_PRIVILEGE_MIN                                   242


typedef enum {
    XONLINE_PARENTAL_CONTROL_GROUP_OPEN         = 0,
    XONLINE_PARENTAL_CONTROL_GROUP_MEDIUM       = 1,
    XONLINE_PARENTAL_CONTROL_GROUP_RESTRICTED   = 2
} XONLINE_PARENTAL_CONTROL_GROUP_TYPE;

typedef enum {
    XONLINE_PAYMENT_INSTRUMENT_NONE             = 0,
    XONLINE_PAYMENT_INSTRUMENT_CREDIT_CARD      = 1,
    XONLINE_PAYMENT_INSTRUMENT_DIRECT_DEBIT     = 2
} XONLINE_PAYMENT_INSTRUMENT_TYPE;

typedef enum {
    XONLINE_CREDIT_CARD_VISA                    = 0,
    XONLINE_CREDIT_CARD_MASTER_CARD             = 1,
    XONLINE_CREDIT_CARD_AMEX                    = 2,
    XONLINE_CREDIT_CARD_DISCOVER                = 3,
    XONLINE_CREDIT_CARD_JCB                     = 4,
    XONLINE_CREDIT_CARD_DINERS                  = 5,
    XONLINE_CREDIT_CARD_KLCC                    = 6
} XONLINE_CREDIT_CARD_TYPE;

typedef enum {
    XONLINE_TIER_INVALID                        = 0,
    XONLINE_TIER_BRONZE                         = 3,
    XONLINE_TIER_SILVER                         = 6
} XONLINE_TIER_TYPE;

typedef enum {
    XONLINE_SUBSCRIPTION_PENDING                = 0,
    XONLINE_SUBSCRIPTION_ENABLED                = 1,
    XONLINE_SUBSCRIPTION_SUSPENDED              = 2,
    XONLINE_SUBSCRIPTION_EXPIRED                = 3,
    XONLINE_SUBSCRIPTION_CANCELED               = 4,
    XONLINE_SUBSCRIPTION_EXPIRED_NO_VIOLATIONS  = 128
} XONLINE_SUBSCRIPTION_STATUS_TYPE;

typedef enum {
    XONLINE_GENRE_BASE = 0,
    XONLINE_GENRE_XARCADE = 116000000
} XONLINE_GENRE_TYPE;

typedef enum {
    XONLINE_DMP_STATUS_ACTIVE               = 0,
    XONLINE_DMP_STATUS_DISABLED             = 1,
    XONLINE_DMP_STATUS_CLOSED               = 2
} XONLINE_DMP_STATUS_TYPE;

typedef enum {
    XONLINE_GET_POINTS_BALANCE_RESPONSE_ABOVE_LOW_BALANCE           = 0x0001
} XONLINE_GET_POINTS_BALANCE_RESPONSE_FLAGS;

typedef enum {
    XONLINE_GET_POINTS_BALANCE_DETAILS_RESPONSE_ABOVE_LOW_BALANCE   = 0x0001
} XONLINE_GET_POINTS_BALANCE_DETAILS_RESPONSE_FLAGS;

typedef enum {
    XONLINE_OFFERING_TYPE_SUBSCRIPTION              = 0x00000001,
    XONLINE_OFFERING_TYPE_CONTENT                   = 0x00000002,
    XONLINE_OFFERING_TYPE_RENEWAL                   = 0x00000004,
    XONLINE_OFFERING_TYPE_POINTS_BUNDLE             = 0x00000008,
    XONLINE_OFFERING_TYPE_GAMERTAG_CHANGE           = 0x00000010,
    XONLINE_OFFERING_TYPE_GAME_DEMO                 = 0x00000020,
    XONLINE_OFFERING_TYPE_GAME_TRAILER              = 0x00000040,
    XONLINE_OFFERING_TYPE_THEME                     = 0x00000080,
    XONLINE_OFFERING_TYPE_GAMEPLAY                  = 0x00000100,
    XONLINE_OFFERING_TYPE_FULL_GAME                 = 0x00000200,
    XONLINE_OFFERING_TYPE_PROMO_POINTS              = 0x00000400,
    XONLINE_OFFERING_TYPE_TILE                      = 0x00000800,
    XONLINE_OFFERING_TYPE_ARCADE                    = 0x00002000
} XONLINE_OFFERING_TYPE;

typedef enum {
    XONLINE_TAX_TYPE_NO_TAX                         = 0,
    XONLINE_TAX_TYPE_DEFAULT                        = 1,
    XONLINE_TAX_TYPE_GST                            = 2,
    XONLINE_TAX_TYPE_VAT                            = 3,
    XONLINE_TAX_TYPE_NOT_APPLICABLE                 = 4
} XONLINE_TAX_TYPE;

typedef enum {
    XONLINE_OFFERING_FREQUENCY_ONE_TIME_CHARGE      = 0,
    XONLINE_OFFERING_FREQUENCY_MONTHLY              = 1,
    XONLINE_OFFERING_FREQUENCY_QUARTERLY            = 2,
    XONLINE_OFFERING_FREQUENCY_BIANNUALLY           = 3,
    XONLINE_OFFERING_FREQUENCY_ANNUALLY             = 4
} XONLINE_OFFERING_FREQUENCY;

typedef enum {
    XONLINE_OFFERING_RELATION_NONE                  = 1,
    XONLINE_OFFERING_RELATION_BASE                  = 0,
    XONLINE_OFFERING_RELATION_RENEWAL               = 3
} XONLINE_OFFERING_RELATION;

typedef enum {
    XONLINE_PAYMENT_TYPE_CREDIT_CARD                = 0x00000001,
    XONLINE_PAYMENT_TYPE_TOKEN                      = 0x00000002,
    XONLINE_PAYMENT_TYPE_POINTS                     = 0x00000004
} XONLINE_PAYMENT_TYPE;

typedef enum {
    XONLINE_CONTENT_ENUMERATE_USER_PLAYED_GAME_FILTER       = 0x0001,
    XONLINE_CONTENT_ENUMERATE_USER_HAS_PURCHASED_FILTER     = 0x0002,
    XONLINE_CONTENT_ENUMERATE_NEW_CONTENT_ONLY_FILTER       = 0x0004
} XONLINE_CONTENT_ENUMERATE_FLAGS;

typedef enum {
    XONLINE_BASIC_CONTENT_INFO_USER_HAS_PURCHASED           = 0x0001,
    XONLINE_BASIC_CONTENT_INFO_USER_HAS_VIEWED              = 0x0002,
    XONLINE_BASIC_CONTENT_INFO_IS_UNRESTRICTED              = 0x0004
} XONLINE_BASIC_CONTENT_INFO_FLAGS;

typedef enum {
    XONLINE_SUBSCRIPTION_QUERY_FOR_NEW                   = 0x0001,
    XONLINE_SUBSCRIPTION_QUERY_FOR_RENEWALS              = 0x0002,
    XONLINE_SUBSCRIPTION_QUERY_FOR_CURRENT               = 0x0004,
    XONLINE_SUBSCRIPTION_QUERY_FOR_EXPIRED               = 0x0008
} XONLINE_SUBSCRIPTION_ENUMERATE_FLAGS;

typedef enum {
    XONLINE_BASIC_CONTENT_INFO_USER_IS_SUBSCRIBED        = 0x0001
} XONLINE_BASIC_SUBSCRIPTION_INFO_FLAGS;

typedef enum {
    XONLINE_SUBSCRIPTION_CONVERT_MODE_CONVERT               = 0,
    XONLINE_SUBSCRIPTION_CONVERT_MODE_RENEW                 = 1,
    XONLINE_SUBSCRIPTION_CONVERT_MODE_INVALID               = 2
} XONLINE_SUBSCRIPTION_CONVERT_MODE;

typedef enum {
    XONLINE_TITLE_QUERY_FOR_NEW                          = 0x0001,
    XONLINE_TITLE_QUERY_FOR_PLAYED                       = 0x0002
} XONLINE_TITLE_ENUMERATE_FLAGS;

#define XONLINE_OFFERING_BITFILTER_ALL              = 0xFFFFFFFF;

#pragma pack(push, 4)

typedef struct _USER_XNAME
{
    WCHAR    wszGamerTag[XONLINE_GAMERTAG_SIZE];
} USER_XNAME;


typedef struct _USER_ACCOUNT_INFO
{
    USER_XNAME  xname;
    BYTE        rgbPasscode[XONLINE_PASSCODE_LENGTH];
    FILETIME    ftBirthdate;
} USER_ACCOUNT_INFO;


typedef struct _USER_PAYMENT_INFO
{
    WCHAR    wszFirstName[MAX_FIRSTNAME_SIZE];
    WCHAR    wszLastName[MAX_LASTNAME_SIZE];
    WCHAR    wszStreet1[MAX_STREET_SIZE];
    WCHAR    wszStreet2[MAX_STREET_SIZE];
    WCHAR    wszDistrict[MAX_STREET_SIZE];
    WCHAR    wszCity[MAX_CITY_SIZE];
    WCHAR    wszState[MAX_STATE_SIZE];
    BYTE     bCountryId;
    WORD     wLanguageId;
    WCHAR    wszPostalCode[MAX_POSTALCODE_SIZE];
    WCHAR    wszPhonePrefix[MAX_PHONE_PREFIX_SIZE];
    WCHAR    wszPhoneNumber[MAX_PHONE_NUMBER_SIZE];
    WCHAR    wszPhoneExtension[MAX_PHONE_EXTENSION_SIZE];

    BYTE     bPaymentTypeId;
    WCHAR    wszCardHolder[MAX_CC_NAME_SIZE];
    BYTE     bCardTypeId;
    WCHAR    wszCardNumber[MAX_CC_NUMBER_SIZE];
    FILETIME ftCardExpiration;

    WCHAR    wszEmail[MAX_EMAIL_SIZE];
    WCHAR    wszBankCode[MAX_DD_BANK_CODE_SIZE];
    WCHAR    wszBranchCode[MAX_DD_BRANCH_CODE_SIZE];
    WCHAR    wszCheckDigits[MAX_DD_CHECK_DIGITS_SIZE];

    WCHAR    wszVoucher[MAX_VOUCHER_SIZE];

    BYTE     bMsftOptIn;
    BYTE     bPartnerOptIn;
    ULONGLONG   qwOfferId;
    FILETIME ftBirthdate;
} USER_PAYMENT_INFO;

#pragma pack(pop)


//
// Calculate the maximum request buffer size * 3 for UTF8 conversion
//

#define MAX_CREATE_OWNER_ACCT_STRINGS  (3 * ( \
    XONLINE_GAMERTAG_SIZE + \
    MAX_FIRSTNAME_SIZE + \
    MAX_LASTNAME_SIZE + \
    MAX_STREET_SIZE + \
    MAX_STREET_SIZE + \
    MAX_DISTRICT_SIZE + \
    MAX_CITY_SIZE + \
    MAX_STATE_SIZE + \
    MAX_POSTALCODE_SIZE + \
    MAX_PHONE_PREFIX_SIZE + \
    MAX_PHONE_NUMBER_SIZE + \
    MAX_PHONE_EXTENSION_SIZE + \
    MAX_CC_NAME_SIZE + \
    MAX_CC_NUMBER_SIZE + \
    MAX_EMAIL_SIZE + \
    MAX_DD_BANK_CODE_SIZE + \
    MAX_DD_BRANCH_CODE_SIZE + \
    MAX_DD_CHECK_DIGITS_SIZE + \
    MAX_VOUCHER_SIZE))


#pragma pack(push, 1)
struct CREATE_OWNER_ACCT_REQUEST
{
    ULONGLONG   qwMachinePuid;
    DWORD       dwTitleId;
    FILETIME    ftBirthdate;
    BYTE        bMSSpam;
    BYTE        bPartnerSpam;
    BYTE        bCountryId;
    WORD        wLanguageId;
    BYTE        bCardTypeId;
    FILETIME    ftCardExpiration;
    BYTE        rgbData[MAX_CREATE_OWNER_ACCT_STRINGS];
};

struct CREATE_OWNER_ACCT_RESPONSE
{
    ULONGLONG   qwUserID;
    BYTE        rgbKey[XONLINE_KEY_LENGTH];
    CHAR        szDomain[XONLINE_USERDOMAIN_SIZE];
    CHAR        szRealm[XONLINE_KERBEROSREALM_SIZE];
};

#pragma pack(pop)

#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif

#ifndef _countof
#define _countof(array)     (sizeof(array)/sizeof(array[0]))
#endif


typedef DWORD MSGTIME;
#define FT_MSGTIME_BEGIN 0x01C2B128BA2B4000 // 1/1/2003 - used for conversion between FILETIME and MSGTIME
#define FileTimeToMsgTime( pFileTime ) (MSGTIME)( ( *((ULONGLONG*)(pFileTime)) - FT_MSGTIME_BEGIN ) / 10000000 )

XAMINLINE
FILETIME
MsgTimeToFileTime(    MSGTIME mt)
{
    ULONGLONG ull = ((ULONGLONG)(mt) * 10000000 + FT_MSGTIME_BEGIN);
    return *((FILETIME*)&ull);
}


//
// Game Invites
//
typedef enum
{
    XMSG_INVITE_ANSWER_NO = 0,
    XMSG_INVITE_ANSWER_YES = 1,
    XMSG_INVITE_ANSWER_NEVER = 2,
    XMSG_INVITE_ANSWER_INVALID = 3

} XMSG_INVITE_ANSWER_TYPE;

#pragma pack(push, 1)

typedef union _XMSG_PROPERTY_DATA
{
    WORD            wPropOffset;
    WORD            wData;
    BYTE            bData;

} XMSG_PROPERTY_DATA, *PXMSG_PROPERTY_DATA;

typedef struct _XMSG_PROPERTY
{
    WORD                    wPropTag;
    XMSG_PROPERTY_DATA      Data;

} XMSG_PROPERTY, *PXMSG_PROPERTY;

typedef struct _XMSG_PROPERTY_INTERNAL
{
    WORD            wPropTag;   // This property's type and unique identifier
    union
    {
        WORD    wPropOffset;    // The offset from the start of rgbData of this property's data
        WORD    wData;          // For type XONLINE_MSG_PROP_TYPE_I2 this contains the actual data
        BYTE    bData;          // For type XONLINE_MSG_PROP_TYPE_I1 and XONLINE_MSG_PROP_TYPE_BOOL this contains the actual data
    };
} XMSG_PROPERTY_INTERNAL, *PXMSG_PROPERTY_INTERNAL;

typedef struct _XMSG_DETAILS_INTERNAL
{
    WORD                        wPropCount;
    WORD                        cbData;

    // XMSG_PROPERTY_INTERNAL     rgProperties[wPropCount]
    // BYTE                       rgbData[cbData]

} XMSG_DETAILS_INTERNAL, *PXMSG_DETAILS_INTERNAL;

typedef WORD XMSG_PROPERTY_STRING_INTERNAL;
typedef WORD XMSG_PROPERTY_BINARY_INTERNAL;

typedef struct _XMSG_PROPERTY_ATTACHMENT_INTERNAL
{
    DWORD           cbAttach;
    DWORD           dwAttachFlags;
    DWORD           cbAttachUrl;
} XMSG_PROPERTY_ATTACHMENT_INTERNAL;

typedef struct _P_ALIVE_2_MSG_INTERNAL
{
    DWORD               dwMsgType;
    DWORD               dwMsgLen;
    DWORD               dwSeqNum;
    SGADDR              sgaddr;

    ULONGLONG           qwUserID;
    WORD                cbAcctName;
    XNADDR              xnaddr;
    XNKID               xnkid;
    XNKEY               xnkey;
    DWORD               dwBuddyListVersion;
    DWORD               dwBlockListVersion;

    //XBOX_LIBRARY_VERSION clientVersion;
    WORD                wMajorVersion;
    WORD                wMinorVersion;
    WORD                wBuildNumber;
    WORD                wQFENumber;

    DWORD               dwTitleID;
    DWORD               dwTitleVersion;
    DWORD               dwTitleRegion;
    WORD                ipportI;
    IN_ADDR             ipaI;
    ULONGLONG           liNonce;
    ULONGLONG           liTimeInit;

    // CHAR               szAcctName[cbAcctName]
} P_ALIVE_2_MSG_INTERNAL;

typedef struct _P_DEAD_USER_MSG_INTERNAL
{
    DWORD               dwMsgType;
    DWORD               dwMsgLen;
    DWORD               dwSeqNum;
    SGADDR              sgaddr;

    ULONGLONG           qwUserID;
} P_DEAD_USER_MSG_INTERNAL;

typedef struct _P_ADD_2_MSG_INTERNAL
{
    DWORD       dwMsgType;
    DWORD       dwMsgLen;
    DWORD       dwSeqNum;
    SGADDR      sgaddr;

    ULONGLONG   qwSenderID;
    ULONGLONG   qwBuddyID;
    DWORD       dwMessageFlags;
    WORD        cbDetails;
    CHAR        szBuddyAcctName[XONLINE_GAMERTAG_SIZE];

    // BYTE rgbDetails[cbDetails];
}P_ADD_2_MSG_INTERNAL;

typedef struct _P_INVITE_2_MSG_INTERNAL
{
    DWORD       dwMsgType;
    DWORD       dwMsgLen;
    DWORD       dwSeqNum;
    SGADDR      sgaddr;

    ULONGLONG   qwUserID;
    ULONGLONG   qwSenderContext;
    DWORD       dwTitleID;
    DWORD       dwMessageFlags;
    WORD        cInvitees;
    WORD        cbDetails;

    // ULONGLONG rgqwInvitees[cInvitees];
    // BYTE pbDetails[cbDetails];
} P_INVITE_2_MSG_INTERNAL;

typedef struct _P_INVITE_ANSWER_MSG_INTERNAL
{
    DWORD       dwMsgType;
    DWORD       dwMsgLen;
    DWORD       dwSeqNum;
    SGADDR      sgaddr;

    ULONGLONG   qwUserID;
    ULONGLONG   qwHostID;
    XNKID       MatchSessionID;
    WORD        wAnswer;
} P_INVITE_ANSWER_MSG_INTERNAL;

typedef struct _P_CANCEL_MSG_INTERNAL
{
    DWORD           dwMsgType;
    DWORD           dwMsgLen;
    DWORD           dwSeqNum;
    SGADDR          sgaddr;

    ULONGLONG       qwUserID;
    XNKID           SessionID;
    WORD            cInvitees;

    // ULONGLONG      rgqwInviteeIDs[cInvitees];
} P_CANCEL_MSG_INTERNAL;

typedef struct _P_FIND_USER_MSG_INTERNAL
{
    DWORD       dwMsgType;
    DWORD       dwMsgLen;
    DWORD       dwSeqNum;
    SGADDR      sgaddr;

    ULONGLONG   qwUserID;
    ULONGLONG   qwFindID;
    CHAR        szSenderName[XONLINE_GAMERTAG_SIZE];
} P_FIND_USER_MSG_INTERNAL;

typedef struct _Q_DEQUEUE_MSG_INTERNAL
{
    DWORD           dwMsgType;
    DWORD           dwMsgLen;
    DWORD           dwSeqNum;
    SGADDR          sgaddr;

    ULONGLONG       qwUserID;
    WORD            wQType;
    DWORD           dwStartItemID;
    WORD            wMaxItems;
    DWORD           dwMaxTotalItemDataSize;
} Q_DEQUEUE_MSG_INTERNAL;

typedef struct _Q_SEND_MESSAGE_MSG_INTERNAL
{
    DWORD           dwMsgType;
    DWORD           dwMsgLen;
    DWORD           dwSeqNum;
    SGADDR          sgaddr;

    ULONGLONG       qwUserID;
    ULONGLONG       qwSenderContext;
    DWORD           dwMessageFlags;
    DWORD           dwSenderTitleID;
    WORD            wExpireMinutes;
    WORD            cbDetails;
    WORD            cRecipients;
    BYTE            bMessageType;
    CHAR            szSenderName[15];

    // ULONGLONG      rgqwRecipientIDs[cRecipients];
    // XMSG_DETAILS   Details;
} Q_SEND_MESSAGE_MSG_INTERNAL;

#pragma pack(pop)

typedef struct _XMSG_PROPERTY_BINARY
{
    WORD            cbData;
    BYTE            *rgbData;

} XMSG_PROPERTY_BINARY, *PXMSG_PROPERTY_BINARY;

typedef struct _XMSG_PROPERTY_STRING
{
    WORD            cbString;
    WCHAR           *szString;

} XMSG_PROPERTY_STRING, *PXMSG_PROPERTY_STRING;

typedef struct _XMSG_PROPERTY_ATTACHMENT
{
    DWORD           cbAttach;
    DWORD           dwAttachFlags;
    DWORD           cbAttachUrl;
    CHAR            szAttachUrl;

} XMSG_PROPERTY_ATTACHMENT, *PXMSG_PROPERTY_ATTACHMENT;

#define XONLINE_MSG_MAX_SUMMARY_NEEDED_IDS          4
#define XONLINE_MAX_ALTERNATE_TITLE_ID              4


typedef struct _XUSER_PRIVILEGE_MSG
{
    XUID                xuidUser;
    PXUID               pXuids;
    DWORD               dwXuidCount;
    BOOL                fResult;
    DWORD               dwPrivilege;
    PXOVERLAPPED        pOverlapped;
} XUSER_PRIVILEGE_MSG, *PXUSER_PRIVILEGE_MSG;



#define X_AFFILIATE_INDEX_TO_FLAG(dwIndex) (1 << dwIndex)
#define X_AFFILIATE_FLAG_TO_INDEX(dwFlag) \
    (dwFlag) == X_AFFILIATE_INDEX_TO_FLAG(X_AFFILIATE_ENCOUNTERED_INDEX) ? X_AFFILIATE_ENCOUNTERED_INDEX : \
    (dwFlag) == X_AFFILIATE_INDEX_TO_FLAG(X_AFFILIATE_COMPLETED_GAME_INDEX) ? X_AFFILIATE_COMPLETED_GAME_INDEX : \
    (dwFlag) == X_AFFILIATE_INDEX_TO_FLAG(X_AFFILIATE_POSITIVE_FEEDBACK_INDEX) ? X_AFFILIATE_POSITIVE_FEEDBACK_INDEX : \
    (dwFlag) == X_AFFILIATE_INDEX_TO_FLAG(X_AFFILIATE_NEGATIVE_FEEDBACK_INDEX) ? X_AFFILIATE_NEGATIVE_FEEDBACK_INDEX : \
    (dwFlag) == X_AFFILIATE_INDEX_TO_FLAG(X_AFFILIATE_AVOIDING_ME_INDEX) ? X_AFFILIATE_AVOIDING_ME_INDEX : \
    (dwFlag) == X_AFFILIATE_INDEX_TO_FLAG(X_AFFILIATE_FRIEND_INDEX) ? X_AFFILIATE_FRIEND_INDEX : \
    (dwFlag) == X_AFFILIATE_INDEX_TO_FLAG(X_AFFILIATE_BLOCK_INDEX) ? X_AFFILIATE_BLOCK_INDEX : \
    (dwFlag) == X_AFFILIATE_INDEX_TO_FLAG(X_AFFILIATE_MUTE_INDEX) ? X_AFFILIATE_MUTE_INDEX : X_AFFILIATE_INDEX_ERROR

#define X_AFFILIATE_CLIENT_FLAGS        \
    (X_AFFILIATE_INDEX_TO_FLAG(X_AFFILIATE_COMPLETED_GAME_INDEX) | X_AFFILIATE_INDEX_TO_FLAG(X_AFFILIATE_ENCOUNTERED_INDEX))


typedef struct _XUSER_PLAYERLIST_USER
{
    ULONGLONG   qwPlayerID;
    DWORD       dwFlags;
    DWORD       dwTitleID;
    MSGTIME     mtUpdated;
    DWORD       dwRating;
    CHAR        szGamertag[XONLINE_GAMERTAG_SIZE];
    BOOLEAN     fPendingAdd;
    WORD        wNextPending;

} XUSER_PLAYERLIST_USER;

typedef struct _XUSER_PLAYERLIST_ITEM
{
    XUID                xuidUser;
    DWORD               dwFlags;
    DWORD               dwTitleID;
    DWORD               dwRating;
    char                szGamertag[XONLINE_GAMERTAG_SIZE];

} XUSER_PLAYERLIST_ITEM;

typedef struct _XUSER_ADDPLAYER_MSG
{
    DWORD               dwUserIndex;
    DWORD               dwResult;
    XUSER_PLAYERLIST_ITEM item;

} XUSER_ADDPLAYER_MSG;

typedef struct _XUSER_PLAYER_ENUM
{
    DWORD               dwUserIndex;
    DWORD               dwStartingIndex;
    DWORD               cItem;

} XUSER_PLAYER_ENUM;

typedef struct _XUSER_ENUMPLAYER_MSG
{
    DWORD               dwUserIndex;
    DWORD               dwStartingIndex;
    DWORD               cItem;
    XUSER_PLAYER_ENUM*  pxenum;

} XUSER_ENUMPLAYER_MSG;

//[end_import_internal(STRUCTS)]

//[begin_import]
DWORD
XUserCreatePlayerEnumerator(
    IN  DWORD           dwUserIndex,
    IN  DWORD           dwStartingIndex,
    IN  DWORD           cItem,
    OUT DWORD *         pcbBuffer,
    OUT HANDLE *        ph
    );

//[end_import]


//-----------------------------------------------------------------------------
// Update download structures
//-----------------------------------------------------------------------------

typedef HRESULT (WINAPI * PFNDOWNLOADINSTALLNEWFILE)(IN void * pvUserData,
                                                     IN const char * szFileName,
                                                     IN DWORD dwFileDataSize,
                                                     IN BOOL bResume);
typedef HRESULT (WINAPI * PFNDOWNLOADINSTALLFILEDATABEGIN)(IN void * pvUserData,
                                                           IN const char * szFileName,
                                                           IN BOOL bResume);
typedef HRESULT (WINAPI * PFNDOWNLOADINSTALLPROCESSDATA)(IN void * pvUserData,
                                                         IN const BYTE * pbData,
                                                         IN DWORD dwDataSize,
                                                         IN HANDLE hFile,
                                                         IN LARGE_INTEGER * pliFileOffset,
                                                         IN BOOL bResume);
typedef HRESULT (WINAPI * PFNDOWNLOADINSTALLFILEDATAEND)(IN void * pvUserData,
                                                         IN BOOL bResume);

typedef struct _DOWNLOAD_INSTALLER
{
    void *                              pvUserData;                      // user context pointer associated with download task
    PFNDOWNLOADINSTALLNEWFILE           pfnDownloadInstallNewFile;       // download installer new file handler
    PFNDOWNLOADINSTALLFILEDATABEGIN     pfnDownloadInstallFileDataBegin; // download installer file data begin handler
    PFNDOWNLOADINSTALLPROCESSDATA       pfnDownloadInstallProcessData;   // download installer file data processing function
    PFNDOWNLOADINSTALLFILEDATAEND       pfnDownloadInstallFileDataEnd;   // download installer file data end handler
} DOWNLOAD_INSTALLER;


#pragma pack(push, 1)

typedef struct _XONLINE_ATTRIBUTE_STRING
{
    WORD Length;
    WCHAR *lpValue;
} XONLINE_ATTRIBUTE_STRING, *PXONLINE_ATTRIBUTE_STRING;

typedef struct _XONLINE_ATTRIBUTE_BLOB
{
    WORD Length;
    BYTE *pbValue;
} XONLINE_ATTRIBUTE_BLOB, *PXONLINE_ATTRIBUTE_BLOB;

typedef union _XONLINE_ATTRIBUTE_DATA
{
    ULONGLONG integer;
    XONLINE_ATTRIBUTE_STRING string;
    XONLINE_ATTRIBUTE_BLOB blob;
} XONLINE_ATTRIBUTE_DATA, *PXONLINE_ATTRIBUTE_DATA;

typedef struct _XONLINE_ATTRIBUTE
{
    DWORD dwAttributeID;
    XONLINE_ATTRIBUTE_DATA info;
} XONLINE_ATTRIBUTE, *PXONLINE_ATTRIBUTE;

typedef struct _XONLINE_MATCH_SESSION_INFO
{
    XNKID SessionID;
    XNKEY KeyExchangeKey;
} XONLINE_MATCH_SESSION_INFO, *PXONLINE_MATCH_SESSION_INFO;

typedef struct _XONLINE_MATCH_SEARCHRESULT
{
    DWORD dwReserved;
    XNKID SessionID;
    XNADDR HostAddress;
    XNKEY KeyExchangeKey;
    DWORD dwPublicOpen;
    DWORD dwPrivateOpen;
    DWORD dwPublicFilled;
    DWORD dwPrivateFilled;
    DWORD dwNumAttributes;
    DWORD *pAttributeOffsets;
    XONLINE_ATTRIBUTE *pAttributes;
} XONLINE_MATCH_SEARCHRESULT, *PXONLINE_MATCH_SEARCHRESULT;

typedef struct _XONLINE_MATCH_SEARCHRESULT_HEADER
{
    DWORD dwReserved;
    USHORT NumSearchResults;
    USHORT Flags;
    DWORD LoggingThreshold;
    XONLINE_MATCH_SEARCHRESULT *pResults;
} XONLINE_MATCH_SEARCHRESULT_HEADER, *PXONLINE_MATCH_SEARCHRESULT_HEADER;

typedef struct _XMATCH_SESSION_CREATE_REQUEST
{
    DWORD dwMessageLength;
    XNKID SessionID;
    DWORD dwTitleID;
    XNADDR HostAddress;
    DWORD dwPublicOpen;
    DWORD dwPrivateOpen;
    DWORD dwPublicFilled;
    DWORD dwPrivateFilled;
    DWORD dwNumAttributes;
    DWORD *pAttributeOffsets;
    XONLINE_ATTRIBUTE *pAttributes;
    XONLINE_MATCH_SESSION_INFO *pSessionInfo;
} XMATCH_SESSION_CREATE_REQUEST;

typedef struct _XMATCH_SESSION_UPDATE_REQUEST
{
    DWORD dwMessageLength;
    XNKID SessionID;
    DWORD dwTitleID;
    XNADDR HostAddress;
    DWORD dwPublicOpen;
    DWORD dwPrivateOpen;
    DWORD dwPublicFilled;
    DWORD dwPrivateFilled;
    DWORD dwNumAttributes;
    DWORD *pAttributeOffsets;
    XONLINE_ATTRIBUTE *pAttributes;
} XMATCH_SESSION_UPDATE_REQUEST;

typedef struct _XMATCH_SESSION_DELETE_REQUEST
{
    DWORD dwMessageLength;
    XNKID SessionID;
    DWORD dwTitleID;
} XMATCH_SESSION_DELETE_REQUEST;

typedef struct _XMATCH_SEARCH_REQUEST
{
    DWORD dwMessageLength;
    DWORD dwTitleID;
    DWORD dwProcedureIndex;
    XNADDR HostAddress;
    WORD wNumUsers;
    WORD wFlags;
    DWORD dwNumAttributes;
    DWORD *pAttributeOffsets;
    XONLINE_ATTRIBUTE *pAttributes;
    XONLINE_MATCH_SEARCHRESULT_HEADER *pSearchResults;
} XMATCH_SEARCH_REQUEST;

typedef struct _STRING_LOOKUP_RESPONSE
{
    WORD wNumStrings;
    STRING_DATA *pStringData;
} STRING_LOOKUP_RESPONSE;

typedef struct _STRING_V1_TITLE_ID_REQUEST
{
    WORD wType;
    WORD wLanguage;
    WORD wNumTitles;
    DWORD *pTitleIDs;
    STRING_LOOKUP_RESPONSE *pResults;
} STRING_V1_TITLE_ID_REQUEST;

typedef struct _STRING_LOOKUP_2_REQUEST
{
    DWORD dwTitleID;
    WORD wNumStrings;
    WORD wLocaleLen;
    CHAR *szLocale;
    DWORD *pStringIDs;
    STRING_LOOKUP_RESPONSE *pResults;
} STRING_LOOKUP_2_REQUEST;

typedef struct _STRING_VERIFY_2_REQUEST
{
    DWORD dwTitleID;
    DWORD dwFlags;
    WORD wLocaleLen;
    WORD wNumStrings;
    CHAR *szLocale;
    STRING_DATA *pStringData;
    STRING_VERIFY_RESPONSE *pResults;
} STRING_VERIFY_2_REQUEST;

typedef struct _BASE_MSG_HEADER
{
    DWORD dwMsgType;
    DWORD dwMsgLen;
    DWORD dwSeqNum;
    SGADDR sgaddr;
} BASE_MSG_HEADER;

typedef struct _P_REPLY_BUDDY
{
    ULONGLONG qwBuddyID;
    WORD cbAcctName;
    BYTE bStatus;
    CHAR *szAcctName;
} P_REPLY_BUDDY;

typedef struct _P_REPLY_BLOCK
{
    ULONGLONG qwBlockID;
} P_REPLY_BLOCK;

typedef struct _P_ALIVE_REPLY_MSG
{
    BASE_MSG_HEADER MsgHeader;
    HRESULT hr;
    DWORD dwBuddyListVersion;
    WORD cBuddiesSent;
    DWORD dwBlockListVersion;
    WORD cBlocksSent;
    P_REPLY_BUDDY *pBuddies;
    P_REPLY_BLOCK *pBlocks;
} P_ALIVE_REPLY_MSG;

typedef struct _XPRESENCE_ALIVE_REPLY
{
    P_ALIVE_REPLY_MSG *pAliveReplies;
} XPRESENCE_ALIVE_REPLY, *PPRESENCE_ALIVE_REPLY;

typedef struct _XBOX_LIBRARY_VERSION
{
    WORD wMajorVersion;
    WORD wMinorVersion;
    WORD wBuildNumber;
    WORD wQFENumber;
} XBOX_LIBRARY_VERSION;

typedef struct _P_ALIVE_2_MSG
{
    BASE_MSG_HEADER MsgHeader;
    ULONGLONG qwUserID;
    WORD cbAcctName;
    XNADDR xnaddr;
    XNKID xnkid;
    XNKEY xnkey;
    DWORD dwBuddyListVersion;
    DWORD dwBlockListVersion;
    XBOX_LIBRARY_VERSION clientVersion;
    DWORD dwTitleID;
    DWORD dwTitleVersion;
    DWORD dwTitleRegion;
    WORD ipportI;
    IN_ADDR ipaI;
    ULONGLONG liNonce;
    ULONGLONG liTimeInit;
    CHAR *szAcctName;
} P_ALIVE_2_MSG;

typedef struct _XPRESENCE_SEND_ALIVE
{
    P_ALIVE_2_MSG *pAlives;
    XPRESENCE_ALIVE_REPLY *pAliveReply;
} XPRESENCE_SEND_ALIVE;

typedef struct _P_DEAD_USER_MSG
{
    BASE_MSG_HEADER MsgHeader;
    ULONGLONG qwUserID;
} P_DEAD_USER_MSG;

typedef struct _XPRESENCE_SEND_DEAD_USER
{
    P_DEAD_USER_MSG *pDeadUsers;
} XPRESENCE_SEND_DEAD_USER;

typedef struct _P_LIST_CHANGE_ITEM
{
    DWORD dwListVersion;
    ULONGLONG qwTargetID;
    WORD wOperationID;
    HRESULT hr;
    WORD cbTargetAcctName;
    CHAR *szTargetAcctName;
} P_LIST_CHANGE_ITEM;

typedef struct _P_PRESENCE_ITEM
{
    ULONGLONG qwBuddyID;
    DWORD dwTitleID;
    DWORD dwState;
    XNKID MatchSessionID;
    WORD cbNickname;
    WORD cbTitleStuff;
    BYTE *rgbNickName;
    BYTE *rgbTitleStuff;
} P_PRESENCE_ITEM;

typedef struct _P_PEER_PRESENCE_ITEM
{
    ULONGLONG qwUserID;
    DWORD dwTitleID;
    DWORD dwState;
    XNKID MatchSessionID;
    WORD cbTitleStuff;
    BYTE *rgbTitleStuff;
} P_PEER_PRESENCE_ITEM;

typedef struct _P_PRESENCE_2_ITEM
{
    ULONGLONG qwUserID;
    DWORD dwTitleID;
    DWORD dwState;
    XNKID MatchSessionID;
    MSGTIME mtUserTime;
    WORD cbRichPresence;
    WORD cbData;
    WCHAR *wszRichPresence;
    BYTE *rgbData;
} P_PRESENCE_2_ITEM;

typedef struct _P_INVITE_ACTION_ITEM
{
    ULONGLONG qwTargetID;
    DWORD dwContext;
    XNKID SessionID;
} P_INVITE_ACTION_ITEM;

typedef struct _P_INVITATION_ITEM
{
    ULONGLONG qwHostID;
    XNKID MatchSessionID;
    DWORD dwTitleID;
    FILETIME ftSent;
} P_INVITATION_ITEM;

typedef struct _P_INVITATION_ANSWER_ITEM
{
    ULONGLONG qwInviteeID;
    XNKID MatchSessionID;
    ULONGLONG ftSent;
    WORD wAnswer;
} P_INVITATION_ANSWER_ITEM;

typedef union _Q_REPLY_ITEM
{
    P_LIST_CHANGE_ITEM ChangeItem;
    P_PRESENCE_ITEM PresenceItem;
    P_INVITATION_ITEM InvitationItem;
    P_INVITATION_ANSWER_ITEM AnswerItem;
    P_PEER_PRESENCE_ITEM PeerPresenceItem;
    P_PRESENCE_2_ITEM RichPresenceItem;
    P_INVITE_ACTION_ITEM InviteActionItem;
} Q_REPLY_ITEM;

typedef struct _Q_LIST_ITEM
{
    DWORD dwItemID;
    WORD wItemLen;
    Q_REPLY_ITEM ReplyItem;
} Q_LIST_ITEM;

typedef struct _Q_LIST_REPLY_MSG
{
    BASE_MSG_HEADER MsgHeader;
    ULONGLONG qwUserID;
    WORD wQType;
    HRESULT hr;
    DWORD dwNextItemID;
    WORD wQLeft;
    WORD wNumItems;
    DWORD dwTotalItemDataSize;
    DWORD cdwQVals;
    DWORD *rgdwQVals;
    Q_LIST_ITEM *rgItems;
} Q_LIST_REPLY_MSG, *PQ_LIST_REPLY_MSG;

typedef struct _Q_DEQUEUE_MSG
{
    BASE_MSG_HEADER MsgHeader;
    ULONGLONG qwUserID;
    WORD wQType;
    DWORD dwStartItemID;
    WORD wMaxItems;
    DWORD dwMaxTotalItemDataSize;
} Q_DEQUEUE_MSG;

typedef struct _XNOTIFICATION_SEND_DEQUEUE
{
    Q_DEQUEUE_MSG pDequeueMsg[1];
    Q_LIST_REPLY_MSG *pReply;
} XNOTIFICATION_SEND_DEQUEUE;

typedef struct _PRESENCE_SET_STATE
{
    XUID UserXuid;
    DWORD dwStateFlags;
    XNKID sessionID;
    DWORD cbState;
    BYTE *pbState;
} PRESENCE_SET_STATE;

typedef struct _PRESENCE_GET_STATE
{
    XUID UserXuid;
    DWORD pdwStateFlags[1];
    XNKID pSessionID[1];
} PRESENCE_GET_STATE;

typedef struct _NOTIFICATION_UPDATE_STATE_FLAGS
{
    XUID UserXuid;
    DWORD dwStateFlagsSet;
    DWORD dwStateFlagsClear;
} NOTIFICATION_UPDATE_STATE_FLAGS;

typedef struct _PRESENCE_SET_GAME_SESSION
{
    XUID UserXuid;
    XNKID sessionID;
} PRESENCE_SET_GAME_SESSION;

typedef struct _GET_SESSION_RESULTS
{
    ULONGLONG qwHostUserID;
    DWORD dwTitleID;
    DWORD dwTitleVersion;
    DWORD dwTitleRegion;
    XNADDR xnaddr;
    XNKID xkid;
    XNKEY xnkey;
} GET_SESSION_RESULTS, *PGET_SESSION_RESULTS;

typedef struct _P_PEER_SESSION_MSG
{
    DWORD dwMsgType;
    DWORD dwMsgLen;
    DWORD dwSeqNum;
    SGADDR sgaddr;
    XUID qwUserID;
    XUID qwHostUserID;
    GET_SESSION_RESULTS *pResults;
} P_PEER_SESSION_MSG;

typedef struct _P_GET_PEER_SESSION
{
    GET_SESSION_RESULTS *pResults;
} P_GET_PEER_SESSION;

typedef struct _P_PEER_SUBSCRIBE_REPLY_MSG
{
    BYTE pbInternal[32];
    HRESULT hr;
} P_PEER_SUBSCRIBE_REPLY_MSG;

typedef struct _P_PEER_SUBSCRIBE_MSG
{
    DWORD dwMsgType;
    DWORD dwMsgLen;
    DWORD dwSeqNum;
    SGADDR sgaddr;
    XUID qwUserID;
    WORD cSrcUserIDs;
    ULONGLONG *rgqwSrcUserIDs;
    P_PEER_SUBSCRIBE_REPLY_MSG *pResults;
} P_PEER_SUBSCRIBE_MSG;

typedef struct _P_PEER_UNSUBSCRIBE_MSG
{
    DWORD dwMsgType;
    DWORD dwMsgLen;
    DWORD dwSeqNum;
    SGADDR sgaddr;
    XUID qwUserID;
} P_PEER_UNSUBSCRIBE_MSG;

typedef struct _P_PRESENCE_ENUM_CREATE_MSG
{
    DWORD dwUserIndex;
    DWORD cPeers;
    XUID *pPeers;
    DWORD dwStartingIndex;
    DWORD dwPeersToReturn;
    DWORD pcbBuffer[1];
    HANDLE ph[1];
} P_PRESENCE_ENUM_CREATE_MSG;

typedef struct _P_PRESENCE_SUBSCRIBE_MSG
{
    DWORD dwUserIndex;
    DWORD cPeers;
    XUID *pPeers;
} P_PRESENCE_SUBSCRIBE_MSG;

typedef struct _P_PRESENCE_INITIALIZE_MSG
{
    DWORD cPeerSubscriptions;
} P_PRESENCE_INITIALIZE_MSG;

typedef struct _SET_USER_SETTINGS2_REQUEST_STRUCT
{
    XUID qwUserId;
    WORD bTier;
    WORD dwUserFlags;
    DWORD rgPrivileges[8];
} SET_USER_SETTINGS2_REQUEST_STRUCT;

typedef struct _UPDATE_PARENTAL_CONTROLS_STRUCT
{
    XUID qwUserId;
    DWORD rgGrantPrivileges[8];
    DWORD rgRestrictPrivileges[8];
    WORD wSourceLength;
    WCHAR *wszSource;
} UPDATE_PARENTAL_CONTROLS_STRUCT;

typedef struct _GET_POINTS_BALANCE_RESPONSE
{
    DWORD dwPointsBalance;
    BYTE bDMPAccountStatus;
    BYTE bResponseFlags;
} GET_POINTS_BALANCE_RESPONSE;

typedef struct _GET_POINTS_BALANCE_REQUEST
{
    XUID qwUserId;
    ULONGLONG qwMachineId;
    GET_POINTS_BALANCE_RESPONSE *pResults;
} GET_POINTS_BALANCE_REQUEST;

typedef struct _PHONE_INFO
{
    WORD wPhonePrefixLength;
    WCHAR *wszPhonePrefix;
    WORD wPhoneNumberLength;
    WCHAR *wszPhoneNumber;
    WORD wPhoneExtensionLength;
    WCHAR *wszPhoneExtension;
} PHONE_INFO;

typedef struct _CREDIT_CARD_INFO
{
    BYTE bCardTypeId;
    WORD wAccountHolderNameLength;
    WCHAR *wszAccountHolderName;
    WORD wAccountNumberLength;
    WCHAR *wszAccountNumber;
    WORD wCCVNumberLength;
    WCHAR *wszCCVNumber;
    FILETIME ftExpirationDate;
} CREDIT_CARD_INFO;

typedef struct _DIRECT_DEBIT_INFO
{
    WORD wAccountHolderNameLength;
    WCHAR *wszAccountHolderName;
    WORD wAccountNumberLength;
    WCHAR *wszAccountNumber;
    WORD wBankCodeLength;
    WCHAR *wszBankCode;
    WORD wBranchCodeLength;
    WCHAR *wszBranchCode;
    WORD wCheckDigitsLength;
    WCHAR *wszCheckDigits;
} DIRECT_DEBIT_INFO;

typedef struct _CREATE_LIVE_ACCOUNT_RESPONSE
{
    ULONGLONG qwUserId;
    BYTE abXboxKey[16];
    BYTE abXenonKey[16];
} CREATE_LIVE_ACCOUNT_RESPONSE;

typedef struct _CREATE_LIVE_ACCOUNT_REQUEST_OLD
{
    ULONGLONG qwMachineId;
    ULONGLONG qwTitleId;
    WORD wFirstNameLength;
    WCHAR *wszFirstName;
    WORD wLastNameLength;
    WCHAR *wszLastName;
    WORD wGamertagLength;
    WCHAR *wszGamertag;
    ULONGLONG qwUserPassportPuid;
    ULONGLONG qwOwnerPassportPuid;
    ULONGLONG qwOfferId;
    WORD wBillingTokenLength;
    WCHAR *wszBillingToken;
    FILETIME ftBirthdate;
    WORD wEmailLength;
    WCHAR *wszEmail;
    WORD wLanguageId;
    BYTE bCountryId;
    DWORD dwParentalControlGroupId;
    BYTE bMsftOptIn;
    BYTE bPartnerOptIn;
    ADDRESS_INFO address;
    PHONE_INFO phone;
    BYTE bPaymentTypeId;
    CREDIT_CARD_INFO creditCard;
    DIRECT_DEBIT_INFO directDebit;
    CREATE_LIVE_ACCOUNT_RESPONSE *pResponse;
} CREATE_LIVE_ACCOUNT_REQUEST_OLD;

typedef struct _CREATE_LIVE_ACCOUNT_REQUEST
{
    ULONGLONG qwMachineId;
    ULONGLONG qwOfflineXuid;
    DWORD dwTitleId;
    WORD wFirstNameLength;
    WCHAR *wszFirstName;
    WORD wLastNameLength;
    WCHAR *wszLastName;
    WORD wGamertagLength;
    WCHAR *wszGamertag;
    BYTE abSignedUserPassportPuid[28];
    BYTE abSignedOwnerPassportPuid[28];
    ULONGLONG qwOfferId;
    WORD wBillingTokenLength;
    WCHAR *wszBillingToken;
    FILETIME ftBirthdate;
    WORD wEmailLength;
    WCHAR *wszEmail;
    WORD wLanguageId;
    BYTE bCountryId;
    DWORD dwParentalControlGroupId;
    BYTE bMsftOptIn;
    BYTE bPartnerOptIn;
    ADDRESS_INFO address;
    PHONE_INFO phone;
    BYTE bPaymentTypeId;
    CREDIT_CARD_INFO creditCard;
    DIRECT_DEBIT_INFO directDebit;
    WORD wReservedBytesLength;
    BYTE *pbReservedBytes;
    CREATE_LIVE_ACCOUNT_RESPONSE *pResponse;
} CREATE_LIVE_ACCOUNT_REQUEST;

typedef struct _GET_USER_INFO_REQUEST
{
    ULONGLONG qwUserId;
    ULONGLONG qwMachineId;
    DWORD dwTitleId;
    GET_USER_INFO_RESPONSE *pResponse;
} GET_USER_INFO_REQUEST;

typedef struct _RECOVER_ACCOUNT_RESPONSE
{
    ULONGLONG qwUserId;
    ULONGLONG qwOfflineXuid;
    BYTE pKey[16];
    WORD wGamertagLength;
    WCHAR *wszGamertag;
    WORD wDomainLength;
    WCHAR *wszDomain;
    WORD wRealmLength;
    WCHAR *wszRealm;
} RECOVER_ACCOUNT_RESPONSE;

typedef struct _RECOVER_ACCOUNT_REQUEST
{
    ULONGLONG qwMachineId;
    BYTE pSignedPuid[28];
    RECOVER_ACCOUNT_RESPONSE *pResponse;
} RECOVER_ACCOUNT_REQUEST;

typedef struct _PASSPORT_ENCRYPTED_PROXY_PARAMETERS
{
    WORD wLoginTokenRequestLength;
    BYTE *pbLoginTokenRequest;
    DWORD dwPublicKeyPublicExponent;
    WORD wPublicKeyModulusLength;
    BYTE *pbPublicKeyModulus;
    BYTE abPublicKeyDigest[20];
} PASSPORT_ENCRYPTED_PROXY_PARAMETERS;

typedef struct _PASSPORT_GET_ENCRYPTED_PROXY_PARAMETERS_REQUEST
{
    DWORD dwDummy;
    PASSPORT_ENCRYPTED_PROXY_PARAMETERS *pResponse;
} PASSPORT_GET_ENCRYPTED_PROXY_PARAMETERS_REQUEST;

typedef struct _PASSPORT_SESSION_TOKEN
{
    BYTE abSessionToken[28];
} PASSPORT_SESSION_TOKEN;

typedef struct _PASSPORT_CREATE_REQUEST
{
    WORD wPassportMemberNameLength;
    CHAR *szPassportMemberName;
    WORD wSecretQuestionLength;
    WCHAR *szSecretQuestion;
    WORD wEncryptedPasswordLength;
    BYTE *pbEncryptedPassword;
    PASSPORT_SESSION_TOKEN *pSessionToken;
} PASSPORT_CREATE_REQUEST;

typedef struct _PASSPORT_LOGIN_REQUEST
{
    WORD wPassportMemberNameLength;
    CHAR *szPassportMemberName;
    WORD wEncryptedSessionKeyLength;
    BYTE *pbencryptedSessionKey;
    WORD wEncryptedPasswordLength;
    BYTE *pbEncryptedPassword;
    WORD wEncryptedTokenRequestLength;
    BYTE *pbEncryptedTokenRequest;
    PASSPORT_SESSION_TOKEN *pSessionToken;
} PASSPORT_LOGIN_REQUEST;

typedef struct _PASSPORT_CHANGE_PASSWORD_REQUEST
{
    PASSPORT_SESSION_TOKEN pSessionToken[1];
    WORD wPassportMemberNameLength;
    CHAR *szPassportMemberName;
    WORD wEncryptedPasswordLength;
    BYTE *pbEncryptedPassword;
} PASSPORT_CHANGE_PASSWORD_REQUEST;

typedef struct _PAYMENT_INSTRUMENT_INFO
{
    WORD wPaymentInstrumentIdLength;
    WCHAR *wszPaymentInstrumentId;
    BYTE bPaymentTypeId;
    ADDRESS_INFO address;
    PHONE_INFO phone;
    CREDIT_CARD_INFO creditCard;
    DIRECT_DEBIT_INFO directDebit;
} PAYMENT_INSTRUMENT_INFO;

typedef struct _GET_PAYMENT_INSTRUMENTS_RESPONSE
{
    WORD wCount;
    PAYMENT_INSTRUMENT_INFO *pPaymentInstruments;
} GET_PAYMENT_INSTRUMENTS_RESPONSE;

typedef struct _GET_PAYMENT_INSTRUMENTS_REQUEST
{
    XUID qwUserId;
    ULONGLONG qwMachineId;
    WORD wMaxResults;
    GET_PAYMENT_INSTRUMENTS_RESPONSE *pResponse;
} GET_PAYMENT_INSTRUMENTS_REQUEST;

typedef struct _ADD_PAYMENT_INSTRUMENT_RESPONSE
{
    WORD wPaymentInstrumentIdLength;
    WCHAR *wszPaymentInstrumentId;
} ADD_PAYMENT_INSTRUMENT_RESPONSE;

typedef struct _ADD_PAYMENT_INSTRUMENT_REQUEST
{
    XUID qwUserId;
    ULONGLONG qwMachineId;
    ADDRESS_INFO addressInfo;
    PHONE_INFO phoneInfo;
    BYTE bPaymentTypeId;
    CREDIT_CARD_INFO creditCardInfo;
    DIRECT_DEBIT_INFO directDebitInfo;
    ADD_PAYMENT_INSTRUMENT_RESPONSE *pResponse;
} ADD_PAYMENT_INSTRUMENT_REQUEST;

typedef struct _REMOVE_PAYMENT_INSTRUMENT_REQUEST
{
    XUID qwUserId;
    ULONGLONG qwMachineId;
    WORD wPaymentInstrumentIdLength;
    WCHAR *wszPaymentInstrumentId;
} REMOVE_PAYMENT_INSTRUMENT_REQUEST;

typedef struct _UPDATE_PAYMENT_INSTRUMENT_REQUEST
{
    XUID qwUserId;
    ULONGLONG qwMachineId;
    WORD wPaymentInstrumentIdLength;
    WCHAR *wszPaymentInstrumentId;
    ADDRESS_INFO addressInfo;
    PHONE_INFO phoneInfo;
    CREDIT_CARD_INFO creditCardInfo;
    DIRECT_DEBIT_INFO directDebitInfo;
} UPDATE_PAYMENT_INSTRUMENT_REQUEST;

typedef struct _GET_LINKED_GAMERTAG_RESPONSE
{
    XUID qwUserPuid;
    WORD wGamertagLength;
    WCHAR *wszGamertag;
} GET_LINKED_GAMERTAG_RESPONSE;

typedef struct _GET_LINKED_GAMERTAG_REQUEST
{
    BYTE pSignedPuid[28];
    GET_LINKED_GAMERTAG_RESPONSE *pResponse;
} GET_LINKED_GAMERTAG_REQUEST;

typedef struct _PASSPORT_SECRET_QUESTION
{
    WORD wSecretQuestionLength;
    WCHAR *szSecretQuestion;
} PASSPORT_SECRET_QUESTION;

typedef struct _PASSPORT_GET_SECRET_QUESTION_RESPONSE
{
    WORD wSecretQuestionsCount;
    PASSPORT_SECRET_QUESTION *pSecretQuestions;
} PASSPORT_GET_SECRET_QUESTION_RESPONSE;

typedef struct _PASSPORT_GET_SECRET_QUESTIONS_REQUEST
{
    WORD wCountryId;
    WORD wLanguageId;
    PASSPORT_GET_SECRET_QUESTION_RESPONSE *pResult;
} PASSPORT_GET_SECRET_QUESTIONS_REQUEST;

typedef struct _SET_ACCOUNT_INFO_REQUEST
{
    XUID qwUserId;
    ULONGLONG qwMachineId;
    WORD wFirstNameLength;
    WCHAR *wszFirstName;
    WORD wLastNameLength;
    WCHAR *wszLastName;
    FILETIME ftBirthdate;
    WORD wEmailLength;
    WCHAR *wszEmail;
    ADDRESS_INFO address;
    PHONE_INFO phone;
    WORD wLanguageId;
    BYTE bMsftOptIn;
    BYTE bParterOptIn;
} SET_ACCOUNT_INFO_REQUEST;

typedef struct _GET_ACCOUNT_INFO_RESPONSE
{
    WORD wFirstNameLength;
    WCHAR *wszFirstName;
    WORD wLastNameLength;
    WCHAR *wszLastName;
    FILETIME ftBirthdate;
    WORD wEmailLength;
    WCHAR *wszEmail;
    ADDRESS_INFO addressInfo;
    PHONE_INFO phoneInfo;
    WORD wLanguageId;
    BYTE bCountryId;
    BYTE bMsftOptIn;
    BYTE bParterOptIn;
} GET_ACCOUNT_INFO_RESPONSE;

typedef struct _GET_ACCOUNT_INFO_REQUEST
{
    XUID qwUserId;
    ULONGLONG qwMachineId;
    DWORD dwTitleId;
    GET_ACCOUNT_INFO_RESPONSE *pResponse;
} GET_ACCOUNT_INFO_REQUEST;

typedef struct _PASSPORT_GET_USER_DATA_RESPONSE
{
    WORD wFirstNameLength;
    WCHAR *wszFirstName;
    WORD wLastNameLength;
    WCHAR *wszLastName;
    FILETIME ftBirthdate;
    ADDRESS_INFO address;
    PHONE_INFO phone;
    BYTE bCountryId;
    WORD wEmailLength;
    WCHAR *wszEmail;
} PASSPORT_GET_USER_DATA_RESPONSE;

typedef struct _PASSPORT_GET_USER_DATA_REQUEST
{
    PASSPORT_SESSION_TOKEN pSessionToken[1];
    PASSPORT_GET_USER_DATA_RESPONSE *pResult;
} PASSPORT_GET_USER_DATA_REQUEST;

typedef struct _PASSPORT_GET_MEMBER_NAME_RESPONSE
{
    WORD wUserPmnLength;
    WCHAR *wszUserPmn;
    WORD wParentPmnLength;
    WCHAR *wszParentPmn;
} PASSPORT_GET_MEMBER_NAME_RESPONSE;

typedef struct _PASSPORT_GET_MEMBER_NAME_REQUEST
{
    ULONGLONG qwUserId;
    PASSPORT_GET_MEMBER_NAME_RESPONSE *pResult;
} PASSPORT_GET_MEMBER_NAME_REQUEST;

typedef struct _POSTAL_CODE_MATCH
{
    WORD wPostalCodeLength;
    WCHAR *wszPostalCode;
    WORD wStateLength;
    WCHAR *wszState;
    WORD wCityLength;
    WCHAR *wszCity;
    WORD wStreetLength;
    WCHAR *wszStreet;
} POSTAL_CODE_MATCH;

typedef struct _GET_POSTAL_CODE_RESPONSE
{
    BYTE bCount;
    POSTAL_CODE_MATCH *pMatches;
} GET_POSTAL_CODE_RESPONSE;

typedef struct _GET_POSTAL_CODE_REQUEST
{
    BYTE bCountryId;
    WORD wPostalCodeLength;
    WCHAR *wszPostalCode;
    GET_POSTAL_CODE_RESPONSE *pResponse;
} GET_POSTAL_CODE_REQUEST;

typedef struct _GET_USER_SUBSCRIPTION_DETAILS_DATA
{
    DWORD dwWholePart;
    BYTE bFractionalPart;
    BYTE bCurrencyFormat;
    WORD wISOCodeLength;
    WCHAR *wszISOCode;
    WORD wFormattedPriceLength;
    WCHAR *wszFormattedPrice;
    DWORD dwOfferingDetails;
} GET_USER_SUBSCRIPTION_DETAILS_DATA;

typedef struct _GET_USER_SUBSCRIPTION_DETAILS_RESPONSE
{
    WORD wSubscriptionIdLength;
    WCHAR *wszSubscriptionId;
    WORD wDescriptionLength;
    WCHAR *wszDescription;
    BYTE bCurrentOfferStatus;
    WORD wFriendlyNameLength;
    WCHAR *wszFriendlyName;
    BYTE bAnniversaryDate;
    FILETIME ftPurchaseDate;
    FILETIME ftActivationDate;
    FILETIME ftEndDate;
    BYTE bHasViolations;
    DWORD dwRenewalGracePeriod;
    BYTE bRenewalOfferStatus;
    ULONGLONG qwRenewalOfferId;
    GET_USER_SUBSCRIPTION_DETAILS_DATA currentOfferDetails;
    GET_USER_SUBSCRIPTION_DETAILS_DATA renewalOfferDetails;
    PAYMENT_INSTRUMENT_INFO paymentInstrument;
} GET_USER_SUBSCRIPTION_DETAILS_RESPONSE;

typedef struct _GET_USER_SUBSCRIPTION_DETAILS_REQUEST
{
    XUID qwUserId;
    ULONGLONG qwMachineId;
    ULONGLONG qwOfferId;
    WORD wInstanceIdLength;
    WCHAR *wszInstanceId;
    GET_USER_SUBSCRIPTION_DETAILS_RESPONSE *pResponse;
} GET_USER_SUBSCRIPTION_DETAILS_REQUEST;

typedef struct _VERIFY_BILLING_TOKEN_RESPONSE
{
    ULONGLONG qwOfferId;
    DWORD dwOfferTypeId;
} VERIFY_BILLING_TOKEN_RESPONSE;

typedef struct _VERIFY_BILLING_TOKEN_REQUEST
{
    BYTE bCountryId;
    WORD wBillingTokenLength;
    WCHAR *wszBillingToken;
    VERIFY_BILLING_TOKEN_RESPONSE *pResponse;
} VERIFY_BILLING_TOKEN_REQUEST;

typedef struct _MIGRATE_XBOX1_USER_RESPONSE
{
    ULONGLONG qwUserId;
    BYTE abXenonKey[16];
    WORD wGamertagLength;
    WCHAR *wszGamertag;
    WORD wDomainLength;
    WCHAR *wszDomain;
    WORD wRealmLength;
    WCHAR *wszRealm;
    DWORD dwParentalControlGroupId;
    DWORD dwCultureId;
} MIGRATE_XBOX1_USER_RESPONSE;

typedef struct _MIGRATE_XBOX1_USER_REQUEST
{
    PASSPORT_SESSION_TOKEN pUserSessionToken[1];
    PASSPORT_SESSION_TOKEN pParentSessionToken[1];
    ULONGLONG qwOfflineXuid;
    WORD wUserPassportMemberNameLength;
    CHAR *szUserPassportMemberName;
    DWORD dwTitleId;
    ULONGLONG qwMachineId;
    WORD wLanguageId;
    WORD wReservedBytesLength;
    BYTE *pbReservedBytes;
    MIGRATE_XBOX1_USER_RESPONSE *pResponse;
} MIGRATE_XBOX1_USER_REQUEST;

typedef struct _OFFER_PRICE
{
    DWORD dwPaymentType;
    BYTE bTaxType;
    DWORD dwWholePrice;
    DWORD dwFractionalPrice;
    WORD wPriceTextLength;
    WCHAR *wszPriceText;
} OFFER_PRICE;

typedef struct _ACCOUNT_SUGGESTED_GAMERTAG
{
    WORD wGamertagLength;
    WCHAR *wszGamertag;
} ACCOUNT_SUGGESTED_GAMERTAG;

typedef struct _ACCOUNT_RESERVE_GAMERTAG_RESPONSE
{
    DWORD dwHresult;
    WORD wGamertagCount;
    ACCOUNT_SUGGESTED_GAMERTAG *pGamertags;
} ACCOUNT_RESERVE_GAMERTAG_RESPONSE;

typedef struct _ACCOUNT_RESERVE_GAMERTAG_REQUEST
{
    ULONGLONG qwMachineId;
    BYTE bCountryId;
    WORD wMaxSuggestedNames;
    WORD wGamertagLength;
    WCHAR *wszGamertag;
    ACCOUNT_RESERVE_GAMERTAG_RESPONSE *pResponse;
} ACCOUNT_RESERVE_GAMERTAG_REQUEST;

typedef struct _ACCOUNT_CHANGE_GAMERTAG_RESPONSE
{
    BYTE abKey[16];
} ACCOUNT_CHANGE_GAMERTAG_RESPONSE;

typedef struct _ACCOUNT_CHANGE_GAMERTAG_REQUEST
{
    ULONGLONG qwMachineId;
    ULONGLONG qwUserId;
    WORD wGamertagLength;
    WCHAR *wszGamertag;
    ACCOUNT_CHANGE_GAMERTAG_RESPONSE *pResponse;
} ACCOUNT_CHANGE_GAMERTAG_REQUEST;

typedef struct _CHANGE_SUBSCRIPTION_PAYMENT_INSTRUMENT_REQUEST
{
    XUID qwUserId;
    ULONGLONG qwMachineId;
    WORD wInstanceIdLength;
    WCHAR *wszInstanceId;
    WORD wPaymentInstrumentIdLength;
    WCHAR *wszPaymentInstrumentId;
} CHANGE_SUBSCRIPTION_PAYMENT_INSTRUMENT_REQUEST;

typedef struct _VERIFY_PARENT_CREDIT_CARD_REQUEST
{
    ULONGLONG qwMachineId;
    DWORD dwTitleId;
    PASSPORT_SESSION_TOKEN pParentSessionToken[1];
    WORD wParentPassportMemberNameLength;
    CHAR *szParentPassportMemberName;
    WORD wLanguageId;
    BYTE bCountryId;
    WORD wFirstNameLength;
    WCHAR *wszFirstName;
    WORD wLastNameLength;
    WCHAR *wszLastName;
    WORD wEmailLength;
    WCHAR *wszEmail;
    ADDRESS_INFO address;
    PHONE_INFO phone;
    CREDIT_CARD_INFO creditCardInfo;
} VERIFY_PARENT_CREDIT_CARD_REQUEST;

typedef struct _ACCOUNT_TROUBLESHOOT_RESPONSE
{
    BOOL fNewTOS;
    BOOL fNameChangeRequired;
    BOOL fDowngraded;
    FILETIME suspendedUntil;
    WORD wTotalDaysSuspended;
    FILETIME voiceBannedUntil;
    WORD wTotalDaysVoiceBanned;
    DWORD dwBillingHr;
    WORD wReservedBytesLength;
    BYTE *pbReservedBytes;
} ACCOUNT_TROUBLESHOOT_RESPONSE;

typedef struct _ACCOUNT_TROUBLESHOOT_REQUEST
{
    ULONGLONG qwUserId;
    ULONGLONG qwMachineId;
    WORD wReservedBytesLength;
    BYTE *pbReservedBytes;
    ACCOUNT_TROUBLESHOOT_RESPONSE *pResponse;
} ACCOUNT_TROUBLESHOOT_REQUEST;

typedef struct _ACCOUNT_ACKNOWLEDGE_DOWNGRADE_REQUEST
{
    ULONGLONG qwUserId;
} ACCOUNT_ACKNOWLEDGE_DOWNGRADE_REQUEST;

typedef struct _ACCOUNT_QUERY_RESPONSE
{
    WORD wResponseBytesLength;
    BYTE *pbResponseBytes;
} ACCOUNT_QUERY_RESPONSE;

typedef struct _ACCOUNT_QUERY_REQUEST
{
    DWORD dwRequestType;
    WORD wRequestBytesLength;
    BYTE *pbRequestBytes;
    ACCOUNT_QUERY_RESPONSE *pResults;
} ACCOUNT_QUERY_REQUEST;

typedef struct _ACCOUNT_ACCEPT_TOU_REQUEST
{
    XUID qwUserId;
    ULONGLONG qwMachineId;
} ACCOUNT_ACCEPT_TOU_REQUEST;

typedef struct _ACCOUNT_SET_STATUS_REQUEST
{
    XUID qwUserId;
    DWORD dwNewTermsOfService;
    DWORD dwForceNameChangeRequired;
    FILETIME ftSuspendedUntil;
    WORD wTotalDaysSuspended;
    FILETIME ftVoiceBannedUntil;
    WORD wTotalDaysVoiceBanned;
    DWORD dwBillingHr;
    DWORD dwResetPassword;
} ACCOUNT_SET_STATUS_REQUEST;

typedef struct _ACCOUNT_VERIFY_BILLING_INFO_RESPONSE
{
    XUID qwUserPuid;
    WORD wFirstNameLength;
    WCHAR *wszFirstName;
    WORD wLastNameLength;
    WCHAR *wszLastName;
    FILETIME ftBirthdate;
    WORD wEmailLength;
    WCHAR *wszEmail;
    ADDRESS_INFO addressInfo;
    PHONE_INFO phoneInfo;
    WORD wLanguageId;
    BYTE bCountryId;
    BYTE bMsftOptIn;
    BYTE bParterOptIn;
} ACCOUNT_VERIFY_BILLING_INFO_RESPONSE;

typedef struct _ACCOUNT_VERIFY_BILLING_INFO_REQUEST
{
    ULONGLONG qwMachineId;
    WORD wGamertagLength;
    WCHAR *wszGamertag;
    PHONE_INFO phone;
    WORD wPostalCodeLength;
    WCHAR *wszPostalCode;
    WORD wAccountHolderNameLength;
    WCHAR *wszAccountHolderName;
    WORD wAccountNumberLength;
    WCHAR *wszAccountNumber;
    ACCOUNT_VERIFY_BILLING_INFO_RESPONSE *pResponse;
} ACCOUNT_VERIFY_BILLING_INFO_REQUEST;

typedef struct _ACCOUNT_GET_USER_TYPE_RESPONSE
{
    BYTE bUserType;
} ACCOUNT_GET_USER_TYPE_RESPONSE;

typedef struct _ACCOUNT_GET_USER_TYPE_REQUEST
{
    ULONGLONG qwMachineId;
    WORD wGamertagLength;
    WCHAR *wszGamertag;
    ACCOUNT_GET_USER_TYPE_RESPONSE *pResponse;
} ACCOUNT_GET_USER_TYPE_REQUEST;

typedef struct _ACCOUNT_LINK_XBOX1_ACCOUNT_REQUEST
{
    ULONGLONG qwMachineId;
    DWORD dwTitleId;
    WORD wGamertagLength;
    WCHAR *wszGamertag;
    PASSPORT_SESSION_TOKEN pUserSessionToken[1];
    PASSPORT_SESSION_TOKEN pParentSessionToken[1];
    PHONE_INFO phoneInfo;
    WORD wPostalCodeLength;
    WCHAR *wszPostalCode;
    WORD wAccountHolderNameLength;
    WCHAR *wszAccountHolderName;
    WORD wAccountNumberLength;
    WCHAR *wszAccountNumber;
} ACCOUNT_LINK_XBOX1_ACCOUNT_REQUEST;

typedef struct _MIGRATE_XBOX_COM_USER_RESPONSE
{
    ULONGLONG qwUserId;
    BYTE abXenonKey[16];
    WORD wGamertagLength;
    WCHAR *wszGamertag;
    WORD wDomainLength;
    WCHAR *wszDomain;
    WORD wRealmLength;
    WCHAR *wszRealm;
    DWORD dwParentalControlGroupId;
    DWORD dwCultureId;
} MIGRATE_XBOX_COM_USER_RESPONSE;

typedef struct _MIGRATE_XBOX_COM_USER_REQUEST
{
    PASSPORT_SESSION_TOKEN pUserSessionToken[1];
    ULONGLONG qwOfflineXuid;
    DWORD dwTitleId;
    ULONGLONG qwMachineId;
    BYTE bCountryId;
    WORD wLanguageId;
    ULONGLONG qwOfferId;
    WORD wBillingTokenLength;
    WCHAR *wszBillingToken;
    WORD wFirstNameLength;
    WCHAR *wszFirstName;
    WORD wLastNameLength;
    WCHAR *wszLastName;
    WORD wEmailLength;
    WCHAR *wszEmail;
    ADDRESS_INFO address;
    PHONE_INFO phone;
    BYTE bPaymentTypeId;
    CREDIT_CARD_INFO creditCard;
    DIRECT_DEBIT_INFO directDebit;
    MIGRATE_XBOX_COM_USER_RESPONSE *pResponse;
} MIGRATE_XBOX_COM_USER_REQUEST;

typedef struct _GET_ACCOUNT_INFO_FROM_PASSPORT_REQUEST
{
    PASSPORT_SESSION_TOKEN pSessionToken[1];
    ULONGLONG qwMachineId;
    DWORD dwTitleId;
    GET_ACCOUNT_INFO_RESPONSE *pResponse;
} GET_ACCOUNT_INFO_FROM_PASSPORT_REQUEST;

typedef struct _BASIC_CONTENT_INFO
{
    ULONGLONG qwOfferID;
    WORD wOfferNameLength;
    WCHAR *wszOfferName;
    DWORD dwOfferType;
    BYTE contentId[20];
    DWORD dwTitleID;
    DWORD dwTitleCategory;
    WORD wTitleNameLength;
    WCHAR *wszTitleName;
    BYTE bTierRequired;
    WORD wGameRating;
    WORD wResponseFlags;
    DWORD dwPackageSize;
    DWORD dwInstallSize;
    DWORD dwSellTextLength;
    WCHAR *wszSellText;
    BYTE bPricesLength;
    OFFER_PRICE *pPrices;
} BASIC_CONTENT_INFO;

typedef struct _CONTENT_ENUMERATE_RESPONSE
{
    WORD wOffersReturned;
    BASIC_CONTENT_INFO *pInfos;
    DWORD dwOffersTotal;
} CONTENT_ENUMERATE_RESPONSE;

typedef struct _CONTENT_ENUMERATE_REQUEST
{
    XUID qwUserId;
    BYTE bCountryId;
    WORD wLanguageId;
    WORD wGameRating;
    DWORD dwOfferType;
    DWORD dwPaymentType;
    BYTE bTier;
    DWORD dwTitleId;
    DWORD dwTitleCategories;
    BYTE bRequestFlags;
    DWORD dwStartingIndex;
    DWORD dwMaxResults;
    CONTENT_ENUMERATE_RESPONSE *pResults;
} CONTENT_ENUMERATE_REQUEST;

typedef struct _CONTENT_DETAILS_RESPONSE
{
    BASIC_CONTENT_INFO basicInfo;
} CONTENT_DETAILS_RESPONSE;

typedef struct _CONTENT_DETAILS_REQUEST
{
    XUID qwUserId;
    BYTE bCountryId;
    WORD wLanguageId;
    ULONGLONG qwOfferID;
    DWORD dwPaymentType;
    BYTE bTierRequired;
    BYTE bRatingSystem;
    CONTENT_DETAILS_RESPONSE *pResults;
} CONTENT_DETAILS_REQUEST;

typedef struct _CONTENT_AVAILABLE_RESPONSE
{
    BYTE bNewOffersLength;
    DWORD *pdwNewOffers;
    BYTE bTotalOffersLength;
    DWORD *pdwTotalOffers;
} CONTENT_AVAILABLE_RESPONSE;

typedef struct _CONTENT_AVAILABLE_REQUEST
{
    XUID qwUserId;
    BYTE bCountryId;
    BYTE bTier;
    DWORD dwTitleId;
    CONTENT_AVAILABLE_RESPONSE *pResults;
} CONTENT_AVAILABLE_REQUEST;

typedef struct _UPDATE_ACCESS_TIMES_REQUEST
{
    XUID qwUserId;
    DWORD dwTitleId;
    DWORD dwTitleCategories;
} UPDATE_ACCESS_TIMES_REQUEST;

typedef struct _BASIC_SUBSCRIPTION_INFO
{
    ULONGLONG qwOfferID;
    WORD wOfferNameLength;
    WCHAR *wszOfferName;
    DWORD dwOfferType;
    BYTE bRelationType;
    BYTE bConvertMode;
    WORD wInstanceIdLength;
    WCHAR *wszInstanceId;
    DWORD dwTitleID;
    DWORD dwTitleCategories;
    WORD wTitleNameLength;
    WCHAR *wszTitleName;
    WORD wGameRating;
    BYTE bDuration;
    BYTE bFrequency;
    BYTE bTierProvided;
    BYTE bTierRequired;
    DWORD dwSellTextLength;
    WCHAR *wszSellText;
    ULONGLONG qwRelatedOfferID;
    WORD wResponseFlags;
    BYTE bPricesLength;
    OFFER_PRICE *pPrices;
} BASIC_SUBSCRIPTION_INFO;

typedef struct _SUBSCRIPTION_ENUMERATE_RESPONSE
{
    WORD wOffersReturned;
    BASIC_SUBSCRIPTION_INFO *pInfos;
    DWORD dwOffersTotal;
} SUBSCRIPTION_ENUMERATE_RESPONSE;

typedef struct _SUBSCRIPTION_ENUMERATE_REQUEST
{
    XUID qwUserId;
    ULONGLONG qwMachineId;
    BYTE bUserTier;
    BYTE bCountryId;
    WORD wLanguageId;
    WORD wGameRating;
    DWORD dwOfferType;
    DWORD dwPaymentType;
    DWORD dwTitleId;
    DWORD dwTitleCategories;
    WORD wRequestFlags;
    DWORD dwStartingIndex;
    DWORD dwMaxResults;
    SUBSCRIPTION_ENUMERATE_RESPONSE *pResults;
} SUBSCRIPTION_ENUMERATE_REQUEST;

typedef struct _SUBSCRIPTION_DETAILS_RESPONSE
{
    BASIC_SUBSCRIPTION_INFO basicInfo;
} SUBSCRIPTION_DETAILS_RESPONSE;

typedef struct _SUBSCRIPTION_DETAILS_REQUEST
{
    XUID qwUserId;
    ULONGLONG qwMachineId;
    BYTE bCountryId;
    WORD wLanguageId;
    ULONGLONG qwOfferID;
    DWORD dwPaymentType;
    BYTE bUserTier;
    BYTE bRatingSystem;
    SUBSCRIPTION_DETAILS_RESPONSE *pResults;
} SUBSCRIPTION_DETAILS_REQUEST;

typedef struct _OFFER_PURCHASE_REQUEST
{
    XUID qwUserId;
    BYTE bCountryId;
    WORD wLanguageId;
    BYTE bUserTier;
    ULONGLONG qwMachineId;
    ULONGLONG qwOfferID;
    DWORD dwPaymentType;
    WORD wPaymentInstrumentId;
    WCHAR *wszPaymentInstrumentId;
    WORD wTokenLength;
    WCHAR *wszToken;
} OFFER_PURCHASE_REQUEST;

typedef struct _OFFER_PURCHASE_GAMERTAG_RESPONSE
{
    BYTE bNewKeyLength;
    BYTE *pbNewKey;
} OFFER_PURCHASE_GAMERTAG_RESPONSE;

typedef struct _OFFER_PURCHASE_GAMERTAG_REQUEST
{
    XUID qwUserId;
    BYTE bCountryId;
    WORD wLanguageId;
    BYTE bUserTier;
    ULONGLONG qwMachineId;
    ULONGLONG qwOfferID;
    DWORD dwPaymentType;
    WORD wTokenLength;
    WCHAR *wszToken;
    WORD wGamertagLength;
    WCHAR *wszGamertag;
    OFFER_PURCHASE_GAMERTAG_RESPONSE *pResults;
} OFFER_PURCHASE_GAMERTAG_REQUEST;

typedef struct _TITLE_DETAILS_RESPONSE
{
    WORD wGameRating;
    WORD wTitleLength;
    WCHAR *wszTitle;
    WORD wSellTextLength;
    WCHAR *wszSellText;
    WORD wDeveloperLength;
    WCHAR *wszDeveloper;
    WORD wPublisherLength;
    WCHAR *wszPublisher;
    WORD wGenreLength;
    WCHAR *wszGenre;
    BYTE bSubscriptionContent;
    BYTE bThemeContent;
    BYTE bDemoContent;
    BYTE bTrailerContent;
    BYTE bPlayed;
} TITLE_DETAILS_RESPONSE;

typedef struct _TITLE_DETAILS_REQUEST
{
    XUID qwUserId;
    DWORD dwTitleId;
    BYTE bCountryId;
    WORD wLanguageId;
    BYTE bTierRequired;
    TITLE_DETAILS_RESPONSE *pResults;
} TITLE_DETAILS_REQUEST;

typedef struct _BASIC_TITLE_INFO
{
    WORD wTitleLength;
    WCHAR *wszTitle;
    DWORD dwTitleId;
    BYTE bPlayed;
    DWORD dwPurchasedContentCount;
    DWORD dwTotalContentCount;
    BYTE bNewContentExists;
} BASIC_TITLE_INFO;

typedef struct _ENUMERATE_TITLES_BY_FILTER_RESPONSE
{
    DWORD dwTitlesReturned;
    BASIC_TITLE_INFO *pInfos;
    DWORD dwTotalTitleCount;
} ENUMERATE_TITLES_BY_FILTER_RESPONSE;

typedef struct _ENUMERATE_TITLES_BY_FILTER_REQUEST
{
    XUID qwUserId;
    BYTE bCountryId;
    WORD wLanguageId;
    DWORD dwStartingIndex;
    DWORD dwMaxResults;
    WORD wGameRating;
    BYTE bTierRequired;
    DWORD dwGenreId;
    DWORD dwOfferType;
    WORD wRequestFlags;
    ENUMERATE_TITLES_BY_FILTER_RESPONSE *pResults;
} ENUMERATE_TITLES_BY_FILTER_REQUEST;

typedef struct _BASIC_GENRE_INFO
{
    DWORD dwGenreId;
    WORD wGenreNameLength;
    WCHAR *wszGenreName;
} BASIC_GENRE_INFO;

typedef struct _ENUMERATE_GENRES_RESPONSE
{
    WORD wGenresReturned;
    BASIC_GENRE_INFO *pInfos;
    DWORD dwTotalGenreCount;
} ENUMERATE_GENRES_RESPONSE;

typedef struct _ENUMERATE_GENRES_REQUEST
{
    BYTE bCountryId;
    WORD wLanguageId;
    DWORD dwStartingIndex;
    DWORD dwMaxResults;
    WORD wGameRating;
    BYTE bTierRequired;
    DWORD dwOfferType;
    DWORD dwParentGenreId;
    ENUMERATE_GENRES_RESPONSE *pResults;
} ENUMERATE_GENRES_REQUEST;

typedef struct _BANNER_LIST_ENTRY
{
    BYTE bBannerType;
    BYTE isMyGame;
    WORD wWidth;
    WORD wHeight;
    WORD cbPath;
    WCHAR *wszPath;
} BANNER_LIST_ENTRY;

typedef struct _BANNER_LIST_RESULT
{
    FILETIME ftExpiry;
    DWORD dwCultureId;
    WORD wBannerCountTotal;
    WORD wCount;
    BANNER_LIST_ENTRY *bannerList;
} BANNER_LIST_RESULT;

typedef struct _BANNER_GET_LIST_REQUEST
{
    ULONGLONG qwUserId;
    DWORD dwLangId;
    BYTE bLevel;
    DWORD dwStartingIndex;
    DWORD dwMaxResults;
    BANNER_LIST_RESULT *pResult;
} BANNER_GET_LIST_REQUEST;

typedef struct _BANNER_HOTLIST_ENTRY
{
    BYTE bBannerType;
    BYTE isMyGame;
    WORD wWidth;
    WORD wHeight;
    WORD cbPath;
    WCHAR *wszPath;
    DWORD dwTitleId;
    WORD cbTitleName;
    WCHAR *wszTitleName;
    ULONGLONG qwOfferId;
    WORD cbOfferName;
    WCHAR *wszOfferName;
    OFFER_PRICE offerPrice;
    FILETIME ftDateApproved;
} BANNER_HOTLIST_ENTRY;

typedef struct _BANNER_HOTLIST_RESULT
{
    FILETIME ftExpiry;
    DWORD dwCultureId;
    WORD wBannerCountTotal;
    WORD wCount;
    BANNER_HOTLIST_ENTRY *bannerList;
} BANNER_HOTLIST_RESULT;

typedef struct _BANNER_GET_HOTLIST_REQUEST
{
    ULONGLONG qwUserId;
    DWORD dwLangId;
    BYTE bLevel;
    DWORD dwStartingIndex;
    DWORD dwMaxResults;
    BANNER_HOTLIST_RESULT *pResult;
} BANNER_GET_HOTLIST_REQUEST;

typedef struct _P_BLOCK_MSG
{
    DWORD dwMsgType;
    DWORD dwMsgLen;
    DWORD dwSeqNum;
    SGADDR sgaddr;
    XUID qwUserID;
    XUID qwBlockID;
} P_BLOCK_MSG;

typedef struct _P_UNBLOCK_MSG
{
    DWORD dwMsgType;
    DWORD dwMsgLen;
    DWORD dwSeqNum;
    SGADDR sgaddr;
    XUID qwUserID;
    XUID qwBlockID;
} P_UNBLOCK_MSG;

typedef struct _P_FIND_USER_REPLY_MSG
{
    ULONGLONG qwFoundID;
    CHAR szGamerTag[16];
} P_FIND_USER_REPLY_MSG;

typedef struct _P_FIND_USER_MSG
{
    DWORD dwMsgType;
    DWORD dwMsgLen;
    DWORD dwSeqNum;
    SGADDR sgaddr;
    XUID qwUserID;
    XUID qwFindID;
    CHAR szSenderName[16];
    P_FIND_USER_REPLY_MSG *pResults;
} P_FIND_USER_MSG;

typedef struct _XONLINE_QUERY_ATTRIBUTE_INTEGER
{
    DWORD Length;
    ULONGLONG qwValue;
} XONLINE_QUERY_ATTRIBUTE_INTEGER, *PXONLINE_QUERY_ATTRIBUTE_INTEGER;

typedef struct _XONLINE_QUERY_ATTRIBUTE_STRING
{
    DWORD Length;
    WCHAR *lpValue;
} XONLINE_QUERY_ATTRIBUTE_STRING, *PXONLINE_QUERY_ATTRIBUTE_STRING;

typedef struct _XONLINE_QUERY_ATTRIBUTE_BLOB
{
    DWORD Length;
    BYTE *pbValue;
} XONLINE_QUERY_ATTRIBUTE_BLOB, *PXONLINE_QUERY_ATTRIBUTE_BLOB;

typedef union _XONLINE_QUERY_ATTRIBUTE_DATA
{
    XONLINE_QUERY_ATTRIBUTE_INTEGER integer;
    XONLINE_QUERY_ATTRIBUTE_STRING string;
    XONLINE_QUERY_ATTRIBUTE_BLOB blob;
} XONLINE_QUERY_ATTRIBUTE_DATA, *PXONLINE_QUERY_ATTRIBUTE_DATA;

typedef struct _XONLINE_QUERY_ATTRIBUTE
{
    DWORD dwAttributeID;
    XONLINE_QUERY_ATTRIBUTE_DATA info;
} XONLINE_QUERY_ATTRIBUTE, *PXONLINE_QUERY_ATTRIBUTE;

typedef struct _XONLINE_QUERY_ATTRIBUTE_SPEC
{
    DWORD dwType;
    DWORD dwLength;
} XONLINE_QUERY_ATTRIBUTE_SPEC, *PXONLINE_QUERY_ATTRIBUTE_SPEC;

typedef struct _QUERY_ADD_RESULT
{
    ULONGLONG entityId;
} QUERY_ADD_RESULT, *PQUERY_ADD_RESULT;

typedef struct _QUERY_ADD_REQUEST
{
    DWORD dwTitleId;
    XUID qwUserId;
    ULONGLONG qwTeamId;
    DWORD dwDatasetId;
    DWORD dwNumAttributes;
    XONLINE_QUERY_ATTRIBUTE *pAttributes;
    QUERY_ADD_RESULT *pEntityId;
} QUERY_ADD_REQUEST;

typedef struct _QUERY_REMOVE_REQUEST
{
    DWORD dwTitleId;
    XUID qwUserId;
    ULONGLONG qwTeamId;
    DWORD dwDatasetId;
    DWORD dwProcIndex;
    DWORD dwNumAttributes;
    XONLINE_QUERY_ATTRIBUTE *pAttributes;
} QUERY_REMOVE_REQUEST;

typedef struct _QUERY_REMOVEID_REQUEST
{
    DWORD dwTitleId;
    XUID qwUserId;
    ULONGLONG qwTeamId;
    DWORD dwDatasetId;
    ULONGLONG qwEntityId;
} QUERY_REMOVEID_REQUEST;

typedef struct _QUERY_UPDATE_REQUEST
{
    DWORD dwTitleId;
    XUID qwUserId;
    ULONGLONG qwTeamId;
    DWORD dwDatasetId;
    DWORD dwProcIndex;
    DWORD dwNumAttributes;
    XONLINE_QUERY_ATTRIBUTE *pAttributes;
} QUERY_UPDATE_REQUEST;

typedef struct _QUERY_UPDATEID_REQUEST
{
    DWORD dwTitleId;
    XUID qwUserId;
    ULONGLONG qwTeamId;
    DWORD dwDatasetId;
    DWORD dwProcIndex;
    ULONGLONG qwEntityId;
    DWORD dwNumAttributes;
    XONLINE_QUERY_ATTRIBUTE *pAttributes;
} QUERY_UPDATEID_REQUEST;

typedef struct _QUERY_SEARCH_RESULT
{
    DWORD dwTotalResults;
    DWORD dwReturnedResults;
    DWORD dwNumResultAttributes;
    XONLINE_QUERY_ATTRIBUTE *pAttributes;
} QUERY_SEARCH_RESULT, *PQUERY_SEARCH_RESULT;

typedef struct _QUERY_SEARCH_REQUEST
{
    DWORD dwTitleId;
    DWORD dwDatasetId;
    DWORD dwProcIndex;
    DWORD dwPage;
    DWORD dwResultsPerPage;
    DWORD dwNumResultSpecs;
    DWORD dwNumAttributes;
    XONLINE_QUERY_ATTRIBUTE_SPEC *pSpecs;
    XONLINE_QUERY_ATTRIBUTE *pAttributes;
    QUERY_SEARCH_RESULT *pResults;
} QUERY_SEARCH_REQUEST;

typedef struct _QUERY_FINDFROMIDS_RESULT
{
    DWORD dwReturnedResults;
    DWORD dwNumResultAttributes;
    XONLINE_QUERY_ATTRIBUTE *pAttributes;
} QUERY_FINDFROMIDS_RESULT, *PQUERY_FINDFROMIDS_RESULT;

typedef struct _QUERY_FINDFROMIDS_REQUEST
{
    DWORD dwTitleId;
    DWORD dwDatasetId;
    DWORD dwProcIndex;
    DWORD dwNumResultSpecs;
    DWORD dwNumIds;
    XONLINE_QUERY_ATTRIBUTE_SPEC *pSpecs;
    ULONGLONG *pqwEntityIds;
    QUERY_FINDFROMIDS_RESULT *pResults;
} QUERY_FINDFROMIDS_REQUEST;

typedef struct _QUERY_SELECT_REQUEST
{
    DWORD dwTitleId;
    XUID qwUserId;
    ULONGLONG qwTeamId;
    DWORD dwDatasetId;
    ULONGLONG qwEntityId;
    DWORD dwActionId;
    DWORD dwNumAttributes;
    XONLINE_QUERY_ATTRIBUTE *pAttributes;
} QUERY_SELECT_REQUEST;

typedef struct _XONLINE_TEAM
{
    ULONGLONG qwTeamID;
    DWORD dwNumMembers;
    WORD cbTeamName;
    WORD cbTeamDescription;
    WORD cbTeamMotto;
    WORD cbTeamURL;
    WORD cbTeamData;
    ULONGLONG ftCreated;
    WCHAR *wszTeamName;
    WCHAR *wszTeamDescription;
    WCHAR *wszTeamMotto;
    WCHAR *wszTeamURL;
    BYTE *pbTeamData;
} XONLINE_TEAM, *PXONLINE_TEAM;

typedef struct _XONLINE_USER_TEAM
{
    ULONGLONG qwTeamID;
    BOOL fMember;
    WORD cbTeamName;
    WCHAR *wszTeamName;
} XONLINE_USER_TEAM, *PXONLINE_USER_TEAM;

typedef struct _XONLINE_TEAM_MEMBER
{
    ULONGLONG qwMemberID;
    BYTE cbMemberName;
    BOOL fMember;
    DWORD dwMemberPriv;
    WORD cbMemberData;
    ULONGLONG ftJoined;
    CHAR *szMemberName;
    BYTE *pbMemberData;
} XONLINE_TEAM_MEMBER;

typedef struct _TEAM_ENUM_RESULTS
{
    DWORD cTeams;
    XONLINE_TEAM *rgsTeams;
} TEAM_ENUM_RESULTS, *PTEAM_ENUM_RESULTS;

typedef struct _TEAM_ENUM_BY_XUID_RESULTS
{
    DWORD cTeams;
    XONLINE_USER_TEAM *rgsTeams;
} TEAM_ENUM_BY_XUID_RESULTS, *PTEAM_ENUM_BY_XUID_RESULTS;

typedef struct _P_TEAM_LIST_TEAMS_MSG
{
    DWORD dwMsgType;
    DWORD dwMsgLen;
    DWORD dwSeqNum;
    SGADDR sgaddr;
    XUID qwUserID;
    DWORD dwTitleID;
    DWORD dwTeamCount;
    ULONGLONG *rgqwTeamIDs;
    TEAM_ENUM_RESULTS *pvResults;
} P_TEAM_LIST_TEAMS_MSG;

typedef struct _P_TEAM_LIST_TEAMS_MSG_XUID
{
    DWORD dwMsgType;
    DWORD dwMsgLen;
    DWORD dwSeqNum;
    SGADDR sgaddr;
    XUID qwUserID;
    DWORD dwTitleID;
    TEAM_ENUM_BY_XUID_RESULTS *pvResults;
} P_TEAM_LIST_TEAMS_MSG_XUID;

typedef struct _TEAM_MEM_ENUM_RESULTS
{
    ULONGLONG qwTeamID;
    WORD cMembers;
    XONLINE_TEAM_MEMBER *rgsMembers;
} TEAM_MEM_ENUM_RESULTS, *PTEAM_MEM_ENUM_RESULTS;

typedef struct _P_TEAM_LIST_MEMBERS_MSG
{
    DWORD dwMsgType;
    DWORD dwMsgLen;
    DWORD dwSeqNum;
    SGADDR sgaddr;
    XUID qwUserID;
    DWORD dwTitleID;
    ULONGLONG qwTeamID;
    BOOL fShowRecruits;
    TEAM_MEM_ENUM_RESULTS *pvResults;
} P_TEAM_LIST_MEMBERS_MSG;

typedef struct _TEAM_CREATE_RESULTS
{
    ULONGLONG qwTeamID;
    ULONGLONG ftCreated;
} TEAM_CREATE_RESULTS, *PTEAM_CREATE_RESULTS;

typedef struct _P_TEAM_CREATE_MSG
{
    DWORD dwMsgType;
    DWORD dwMsgLen;
    DWORD dwSeqNum;
    SGADDR sgaddr;
    XUID qwUserID;
    DWORD dwTitleID;
    DWORD dwMaxMembers;
    WORD cbTeamName;
    WORD cbTeamDescription;
    WORD cbTeamMotto;
    WORD cbTeamURL;
    WORD cbTeamData;
    WORD cbCreatorData;
    WCHAR *wszTeamName;
    WCHAR *wszTeamDescription;
    WCHAR *wszTeamMotto;
    WCHAR *wszTeamURL;
    BYTE *pbTeamData;
    BYTE *pbCreatorData;
    TEAM_CREATE_RESULTS *pvResults;
} P_TEAM_CREATE_MSG;

typedef struct _P_TEAM_DELETE_MSG
{
    DWORD dwMsgType;
    DWORD dwMsgLen;
    DWORD dwSeqNum;
    SGADDR sgaddr;
    XUID qwUserID;
    DWORD dwTitleID;
    ULONGLONG qwTeamID;
} P_TEAM_DELETE_MSG;

typedef struct _P_TEAM_REMOVE_MSG
{
    DWORD dwMsgType;
    DWORD dwMsgLen;
    DWORD dwSeqNum;
    SGADDR sgaddr;
    XUID qwUserID;
    DWORD dwTitleID;
    ULONGLONG qwTeamID;
    XUID qwMemberID;
} P_TEAM_REMOVE_MSG;

typedef struct _P_TEAM_MANAGE_TEAM_MSG
{
    DWORD dwMsgType;
    DWORD dwMsgLen;
    DWORD dwSeqNum;
    SGADDR sgaddr;
    XUID qwUserID;
    DWORD dwTitleID;
    ULONGLONG qwTeamID;
    WORD cbTeamName;
    WORD cbTeamDescription;
    WORD cbTeamMotto;
    WORD cbTeamURL;
    WORD cbTeamData;
    WCHAR *wszTeamName;
    WCHAR *wszTeamDescription;
    WCHAR *wszTeamMotto;
    WCHAR *wszTeamURL;
    BYTE *pbTeamData;
} P_TEAM_MANAGE_TEAM_MSG;

typedef struct _P_TEAM_MANAGE_MEMBER_MSG
{
    DWORD dwMsgType;
    DWORD dwMsgLen;
    DWORD dwSeqNum;
    SGADDR sgaddr;
    XUID qwUserID;
    DWORD dwTitleID;
    ULONGLONG qwTeamID;
    XUID qwMemberID;
    DWORD dwMemberPriv;
    WORD cbMemberData;
    BYTE *pbMemberData;
} P_TEAM_MANAGE_MEMBER_MSG;

typedef struct _P_TEAM_RECRUIT_MSG_XUID
{
    DWORD dwMsgType;
    DWORD dwMsgLen;
    DWORD dwSeqNum;
    SGADDR sgaddr;
    XUID qwUserID;
    DWORD dwTitleID;
    ULONGLONG qwTeamID;
    XUID qwMemberID;
    CHAR szMemberName[16];
    DWORD dwMemberPriv;
    DWORD dwMessageFlags;
    WORD cbMemberData;
    WORD cbDetails;
    BYTE *pbMemberData;
} P_TEAM_RECRUIT_MSG_XUID;

typedef struct _P_TEAM_RECRUIT_MSG_NAME
{
    DWORD dwMsgType;
    DWORD dwMsgLen;
    DWORD dwSeqNum;
    SGADDR sgaddr;
    XUID qwUserID;
    DWORD dwTitleID;
    ULONGLONG qwTeamID;
    ULONGLONG qwMemberID;
    CHAR szMemberName[16];
    DWORD dwMemberPriv;
    DWORD dwMessageFlags;
    WORD cbMemberData;
    WORD cbDetails;
    BYTE *pbMemberData;
} P_TEAM_RECRUIT_MSG_NAME;

typedef struct _P_TEAM_JOIN_MSG
{
    DWORD dwMsgType;
    DWORD dwMsgLen;
    DWORD dwSeqNum;
    SGADDR sgaddr;
    XUID qwUserID;
    DWORD dwTitleID;
    ULONGLONG qwTeamID;
    DWORD dwRecruitMsgID;
    BYTE bAnswer;
} P_TEAM_JOIN_MSG;

typedef struct _XUSER_ONLINE_PROFILE_SETTING
{
    DWORD source;
    ULONGLONG qwUserId;
    DWORD dwSettingId;
    WORD cbSize;
    BYTE *pbValue;
} XUSER_ONLINE_PROFILE_SETTING, *PXUSER_ONLINE_PROFILE_SETTING;

typedef struct _XPROFILE_SETTING_SYNC_RESULT
{
    FILETIME ftVersion;
    WORD wTotalSettings;
    WORD wSettingsLen;
    XUSER_ONLINE_PROFILE_SETTING *pSettings;
} XPROFILE_SETTING_SYNC_RESULT, *PXPROFILE_SETTING_SYNC_RESULT;

typedef struct _XPROFILE_SETTING_SYNC_REQUEST
{
    DWORD dwTitleId;
    XUID qwUserId;
    FILETIME ftVersion;
    WORD wStartingIndex;
    WORD wSettingsLen;
    XUSER_ONLINE_PROFILE_SETTING *pSettings;
    XPROFILE_SETTING_SYNC_RESULT *pResults;
} XPROFILE_SETTING_SYNC_REQUEST;

typedef struct _XPROFILE_SETTING_READ_RESULT
{
    WORD wSettingsLen;
    XUSER_ONLINE_PROFILE_SETTING *pSettings;
} XPROFILE_SETTING_READ_RESULT, *PXPROFILE_SETTING_READ_RESULT;

typedef struct _XPROFILE_SETTING_READ_REQUEST
{
    DWORD dwTitleId;
    XUID qwUserId;
    WORD wForUserIdsLen;
    ULONGLONG *pqwUserIds;
    WORD wSettingIdsLen;
    DWORD *pdwSettingIds;
    XPROFILE_SETTING_READ_RESULT *pResults;
} XPROFILE_SETTING_READ_REQUEST;

typedef union _XSTAT_PROC_DATA
{
    BYTE bNull;
    BYTE bData;
    SHORT sData;
    LONG nData;
    LONGLONG i64Data;
    __XLIVEGEN_DOUBLE dblData;
    ULONGLONG qwPuid;
} XSTAT_PROC_DATA;

typedef struct _XSTAT_PROC_PARAM
{
    BYTE bType;
    XSTAT_PROC_DATA Value;
} XSTAT_PROC_PARAM;

typedef struct _XSTAT_PROC
{
    WORD wProcId;
    WORD wParamCount;
    XSTAT_PROC_PARAM *pParams;
} XSTAT_PROC;

typedef struct _XSTATS_POST_REQUEST
{
    DWORD dwTitleId;
    WORD wNumProcs;
    XSTAT_PROC *pProcs;
} XSTATS_POST_REQUEST;

typedef struct _XONLINE_STATS_SPEC
{
    DWORD dwViewId;
    DWORD dwNumColumnIds;
    WORD *pAttrId;
} XONLINE_STATS_SPEC;

typedef struct _XONLINE_STATS_COLUMN
{
    WORD wColumnId;
    BYTE bType;
    XSTAT_PROC_DATA Value;
} XONLINE_STATS_COLUMN;

typedef struct _XONLINE_STATS_ROW
{
    XUID xuid;
    DWORD dwRank;
    LONGLONG i64Rating;
    DWORD cbGamerTag;
    CHAR *pszGamerTag;
    DWORD dwNumColumns;
    XONLINE_STATS_COLUMN *pColumns;
} XONLINE_STATS_ROW;

typedef struct _XONLINE_STATS_VIEW
{
    ULONGLONG qwViewId;
    DWORD dwViewSize;
    DWORD dwRowCount;
    XONLINE_STATS_ROW *pRows;
} XONLINE_STATS_VIEW;

typedef struct _XONLINE_STATS_READ_RESULTS
{
    DWORD dwNumViews;
    XONLINE_STATS_VIEW *pViews;
} XONLINE_STATS_READ_RESULTS;

typedef struct _XONLINE_STATS_READ_REQUEST
{
    DWORD dwTitleId;
    DWORD dwNumXuids;
    XUID *pXuids;
    DWORD dwNumSpecs;
    XONLINE_STATS_SPEC *pSpecs;
    XONLINE_STATS_READ_RESULTS *pResults;
} XONLINE_STATS_READ_REQUEST;

typedef struct _XONLINE_STATS_ENUM_RESULTS
{
    WORD wNumViews;
    XONLINE_STATS_VIEW *pViews;
} XONLINE_STATS_ENUM_RESULTS;

typedef struct _XONLINE_STATS_ENUM_BY_USER_REQUEST
{
    DWORD dwTitleId;
    XUID Xuid;
    DWORD dwPageSize;
    DWORD dwNumSpecs;
    XONLINE_STATS_SPEC *pSpecs;
    XONLINE_STATS_ENUM_RESULTS *pResults;
} XONLINE_STATS_ENUM_BY_USER_REQUEST;

typedef struct _XONLINE_STATS_ENUM_BY_RANK_REQUEST
{
    DWORD dwTitleId;
    ULONGLONG qwRank;
    DWORD dwPageSize;
    DWORD dwNumSpecs;
    XONLINE_STATS_SPEC *pSpecs;
    XONLINE_STATS_ENUM_RESULTS *pResults;
} XONLINE_STATS_ENUM_BY_RANK_REQUEST;

typedef struct _XONLINE_STATS_ENUM_BY_RATING_REQUEST
{
    DWORD dwTitleId;
    LONGLONG i64Rating;
    DWORD dwPageSize;
    DWORD dwNumSpecs;
    XONLINE_STATS_SPEC *pSpecs;
    XONLINE_STATS_ENUM_RESULTS *pResults;
} XONLINE_STATS_ENUM_BY_RATING_REQUEST;

typedef struct _XSTATS_RESET_REQUEST
{
    DWORD dwTitleId;
    ULONGLONG qwUserId;
    DWORD dwLeaderBoardId;
} XSTATS_RESET_REQUEST;

typedef struct _XPROFILE_TITLE
{
    DWORD dwTitleId;
    WORD cbTitleName;
    WCHAR *pszTitleName;
    FILETIME ftLastPlayed;
    DWORD dwCredEarned;
    WORD wAchievementsEarned;
    WORD wAchievementsPossible;
    DWORD dwCredPossible;
    DWORD dwSequence;
    DWORD dwMinutesPlayedOnline;
} XPROFILE_TITLE;

typedef struct _XPROFILE_SYNC_TITLES_RESULT
{
    FILETIME ftVersion;
    WORD wTotalTitles;
    WORD wNumTitles;
    XPROFILE_TITLE *pTitles;
} XPROFILE_SYNC_TITLES_RESULT;

typedef struct _XPROFILE_SYNC_TITLES_REQUEST
{
    XUID qwUserId;
    WORD wLocaleId;
    WORD wStartingIndex;
    FILETIME ftLastSync;
    WORD wNumTitles;
    XPROFILE_TITLE *pTitles;
    XPROFILE_SYNC_TITLES_RESULT *pResults;
} XPROFILE_SYNC_TITLES_REQUEST;

typedef struct
{
    WORD wNumTitles;
    XPROFILE_TITLE *pTitles;
} XPROFILE_ENUM_TITLES_RESULT, XPROFILE_ENUM_TITLES_RESULT;

typedef struct _XPROFILE_ENUM_TITLES_REQUEST
{
    XUID qwUserId;
    XUID qwForUserId;
    WORD wLocaleId;
    WORD wStartingIndex;
    WORD wMaxTitles;
    XPROFILE_ENUM_TITLES_RESULT *pResults;
} XPROFILE_ENUM_TITLES_REQUEST;

typedef struct _XPROFILE_CLEAR_TITLE_REQUEST
{
    XUID qwUserId;
    DWORD dwTitleId;
} XPROFILE_CLEAR_TITLE_REQUEST;

typedef struct _XPROFILE_ACHIEVEMENT
{
    DWORD dwAchievementId;
    FILETIME ftAchieved;
    DWORD dwSequence;
    DWORD dwFlags;
    BYTE bType;
    DWORD dwCred;
    DWORD dwImageId;
    BYTE cbTitleLen;
    WCHAR *pszTitle;
    BYTE cbDescriptionLen;
    WCHAR *pszDescription;
    BYTE cbHowToLen;
    WCHAR *pszHowTo;
    BYTE bNextIdsLen;
    DWORD *pdwNextIds;
    BYTE bReplaceIdsLen;
    DWORD *pdwReplaceIds;
} XPROFILE_ACHIEVEMENT;

typedef struct _XPROFILE_ACHIEVEMENT_SYNC_REQUEST
{
    DWORD dwAchievementId;
    FILETIME ftAchieved;
    DWORD dwSequence;
    DWORD dwFlags;
    BYTE bType;
    DWORD dwCred;
    DWORD dwImageId;
    BYTE cbTitleLen;
    WCHAR *pszTitle;
    BYTE cbDescriptionLen;
    WCHAR *pszDescription;
    BYTE cbHowToLen;
    WCHAR *pszHowTo;
    BYTE bNextIdsLen;
    DWORD *pdwNextIds;
    BYTE bReplaceIdsLen;
    DWORD *pdwReplaceIds;
} XPROFILE_ACHIEVEMENT_SYNC_REQUEST;

typedef struct _XPROFILE_SYNC_ACHIEVEMENTS_RESULT
{
    FILETIME ftVersion;
    WORD wTotalAchievements;
    WORD wAchievementCount;
    XPROFILE_ACHIEVEMENT *pAchievements;
} XPROFILE_SYNC_ACHIEVEMENTS_RESULT;

typedef struct _XPROFILE_SYNC_ACHIEVEMENTS_REQUEST
{
    DWORD dwTitleId;
    XUID qwUserId;
    FILETIME ftVersion;
    WORD wLocaleId;
    WORD wStartingIndex;
    WORD wAchievementCount;
    XPROFILE_ACHIEVEMENT_SYNC_REQUEST *pAchievements;
    XPROFILE_SYNC_ACHIEVEMENTS_RESULT *pResult;
} XPROFILE_SYNC_ACHIEVEMENTS_REQUEST;

typedef struct _XPROFILE_ENUM_ACHIEVEMENTS_RESULT
{
    WORD wAchievementsCount;
    XPROFILE_ACHIEVEMENT *pAchievements;
} XPROFILE_ENUM_ACHIEVEMENTS_RESULT;

typedef struct _XPROFILE_ENUM_ACHIEVEMENTS_REQUEST
{
    DWORD dwTitleId;
    XUID qwUserId;
    ULONGLONG qwForPuid;
    WORD wLocaleId;
    WORD wStartingIndex;
    WORD wMaxAchievements;
    XPROFILE_ENUM_ACHIEVEMENTS_RESULT *pResult;
} XPROFILE_ENUM_ACHIEVEMENTS_REQUEST;

typedef struct _XMSG_DETAILS
{
    WORD wPropCount;
    WORD cbData;
    XMSG_PROPERTY *rgProperties;
    BYTE *rgbData;
} XMSG_DETAILS, *PXMSG_DETAILS;

typedef struct _Q_MESSAGE_SUMMARY
{
    ULONGLONG qwSenderID;
    ULONGLONG qwSenderContext;
    MSGTIME mtSentTime;
    DWORD dwMessageID;
    DWORD dwMessageFlags;
    DWORD dwSenderTitleID;
    WORD wExpireMinutes;
    WORD cbDetails;
    BYTE bMessageType;
    CHAR szSenderName[15];
} Q_MESSAGE_SUMMARY;

typedef struct _Q_MESSAGE_SUMMARY_2
{
    ULONGLONG qwSenderID;
    ULONGLONG qwSenderContext;
    MSGTIME mtSentTime;
    DWORD dwMessageID;
    DWORD dwMessageFlags;
    DWORD dwSenderTitleID;
    WORD wExpireMinutes;
    WORD cbDetails;
    BYTE bMessageType;
    CHAR szSenderName[15];
    WCHAR szSubject[20];
} Q_MESSAGE_SUMMARY_2;

typedef struct _XMSG_SUMMARY
{
    ULONGLONG qwSenderID;
    ULONGLONG qwMessageContext;
    FILETIME ftSentTime;
    DWORD dwMessageID;
    DWORD dwMessageFlags;
    DWORD dwSenderTitleID;
    WORD wExpireMinutes;
    WORD cbDetails;
    BYTE bMsgType;
    CHAR szSenderName[15];
    WCHAR szSubject[20];
} XMSG_SUMMARY, *PXMSG_SUMMARY;

typedef struct _XMSG_SEND_RECIPIENT_RESULT
{
    ULONGLONG qwUserID;
    DWORD dwResult;
} XMSG_SEND_RECIPIENT_RESULT, *PXMSG_SEND_RECIPIENT_RESULT;

typedef struct _XMSG_ENUMERATE_REQUEST
{
    XUID XuidUser;
    DWORD pcMsgSummaries[1];
    XMSG_SUMMARY pMsgSummaries[1];
} XMSG_ENUMERATE_REQUEST;

typedef struct _XMSG_SUMMARY_REQUEST
{
    XUID XuidUser;
    DWORD dwMessageID;
    XMSG_SUMMARY pMsgSummary[1];
} XMSG_SUMMARY_REQUEST, *PXMSG_SUMMARY_REQUEST;

typedef struct _XMSG_CREATE_REQUEST
{
    DWORD dwMsgType;
    DWORD cProperties;
    ULONGLONG qwMessageContext;
    DWORD dwMessageFlags;
    DWORD dwExpireMinutes;
    XMSG_HANDLE phMsg[1];
} XMSG_CREATE_REQUEST, *PXMSG_CREATE_REQUEST;

typedef struct _XMSG_DESTROY
{
    XMSG_HANDLE hMsg;
} XMSG_DESTROY, *PXMSG_DESTROY;

typedef struct _XMSG_SET_PROP_REQUEST
{
    XMSG_HANDLE hMsg;
    WORD wPropTag;
    DWORD dwPropValueSize;
    BYTE pbPropValue[1];
    DWORD dwAttachmentFlags;
} XMSG_SET_PROP_REQUEST, *PXMSG_SET_PROP_REQUEST;

typedef struct _XMSG_GET_PROP_REQUEST
{
    XMSG_HANDLE hMsg;
    WORD wPropTag;
    DWORD dwPropValueBufferSize;
    BYTE pbPropValue[1];
    DWORD pcbPropValue[1];
    DWORD pdwAttachmentFlags[1];
} XMSG_GET_PROP_REQUEST, *PXMSG_GET_PROP_REQUEST;

typedef struct _XMSG_ENUM_RESULTS
{
    WORD cMessages;
    Q_MESSAGE_SUMMARY_2 *pMessages;
} XMSG_ENUM_RESULTS, *PXMSG_ENUM_RESULTS;

typedef struct _Q_ENUM_MESSAGES_MSG
{
    DWORD dwMsgType;
    DWORD dwMsgLen;
    DWORD dwSeqNum;
    SGADDR sgaddr;
    ULONGLONG qwUserID;
    XMSG_ENUM_RESULTS *pResults;
} Q_ENUM_MESSAGES_MSG;

typedef struct _Q_MESSAGE_SUMMARY_REPLY_MSG
{
    Q_MESSAGE_SUMMARY_2 summary;
} Q_MESSAGE_SUMMARY_REPLY_MSG;

typedef struct _Q_MESSAGE_SUMMARY_MSG
{
    DWORD dwMsgType;
    DWORD dwMsgLen;
    DWORD dwSeqNum;
    SGADDR sgaddr;
    ULONGLONG qwUserID;
    DWORD dwMessageID;
    Q_MESSAGE_SUMMARY_REPLY_MSG *pResults;
} Q_MESSAGE_SUMMARY_MSG;

typedef struct _XMSG_DETAILS_RESULTS
{
    Q_MESSAGE_SUMMARY summary;
    XMSG_DETAILS details;
} XMSG_DETAILS_RESULTS, *PXMSG_DETAILS_RESULTS;

typedef struct _XMSG_DETAILS_BLOB
{
    BYTE rgbDetailsBlob[4096];
} XMSG_DETAILS_BLOB, *PXMSG_DETAILS_BLOB;

typedef struct _XMSG_DETAILS_REQUEST
{
    XUID XuidUser;
    DWORD dwMessageID;
    DWORD dwFlagsToSet;
    DWORD dwFlagsToClear;
    DWORD cbResults;
    XMSG_DETAILS_BLOB pResults[1];
    XOVERLAPPED pXOverlapped[1];
} XMSG_DETAILS_REQUEST;

typedef struct _Q_MESSAGE_DETAILS_MSG
{
    DWORD dwMsgType;
    DWORD dwMsgLen;
    DWORD dwSeqNum;
    SGADDR sgaddr;
    XUID qwUserID;
    DWORD dwMessageID;
    DWORD dwFlagsToSet;
    DWORD dwFlagsToClear;
    XMSG_DETAILS_BLOB *pResults;
} Q_MESSAGE_DETAILS_MSG;

typedef struct _XMSG_DETAILS_GET_SUMMARY
{
    XMSG_DETAILS_BLOB pDetails[1];
    XMSG_SUMMARY pMsgSummary[1];
    DWORD pcProperties[1];
    ULONGLONG pqwAttachmentsSize[1];
} XMSG_DETAILS_GET_SUMMARY;

typedef struct _XMSG_DETAILS_GET_PROPERTY
{
    XMSG_DETAILS_BLOB pDetails[1];
    WORD wPropTag;
    DWORD cbPropValueBuffer;
    BYTE pbPropValue[1];
    DWORD pcbPropValue[1];
    DWORD pdwAttachmentFlags[1];
} XMSG_DETAILS_GET_PROPERTY;

typedef struct _XMSG_DELETE_REQUEST
{
    XUID XuidUser;
    DWORD dwMessageID;
    BOOL fBlockSender;
    XOVERLAPPED pXOverlapped[1];
} XMSG_DELETE_REQUEST;

typedef struct _Q_DELETE_MESSAGE_MSG
{
    DWORD dwMsgType;
    DWORD dwMsgLen;
    DWORD dwSeqNum;
    SGADDR sgaddr;
    XUID qwUserID;
    DWORD dwMessageID;
    DWORD dwFlags;
} Q_DELETE_MESSAGE_MSG;

typedef struct _XMSG_SEND_RESULT
{
    WORD cRecipients;
    XMSG_SEND_RECIPIENT_RESULT *pRecipients;
} XMSG_SEND_RESULT;

typedef struct _Q_SEND_MESSAGE_MSG
{
    DWORD dwMsgType;
    DWORD dwMsgLen;
    DWORD dwSeqNum;
    SGADDR sgaddr;
    ULONGLONG qwUserID;
    ULONGLONG qwSenderContext;
    DWORD dwMessageFlags;
    DWORD dwSenderTitleID;
    WORD wExpireMinutes;
    WORD cbDetails;
    WORD cRecipients;
    BYTE bMessageType;
    CHAR szSenderName[15];
    ULONGLONG *qwRecipientIDs;
    XMSG_DETAILS *pDetails;
    XMSG_SEND_RESULT *pResults;
} Q_SEND_MESSAGE_MSG;

typedef struct _Q_REVOKE_MESSAGE_MSG
{
    DWORD dwMsgType;
    DWORD dwMsgLen;
    DWORD dwSeqNum;
    SGADDR sgaddr;
    XUID qwUserID;
    ULONGLONG qwSenderContext;
    WORD cRecipients;
    BYTE bMessageType;
    XMSG_SEND_RECIPIENT_RESULT *pRecipients;
} Q_REVOKE_MESSAGE_MSG;

typedef struct _XMSG_FLAGS_REQUEST
{
    XUID XuidUser;
    DWORD dwMessageID;
    DWORD dwFlagsToSet;
    DWORD dwFlagsToClear;
    XOVERLAPPED pXOverlapped[1];
} XMSG_FLAGS_REQUEST;

typedef struct _Q_MESSAGE_FLAGS_MSG
{
    DWORD dwMsgType;
    DWORD dwMsgLen;
    DWORD dwSeqNum;
    SGADDR sgaddr;
    XUID qwUserID;
    DWORD dwMessageID;
    DWORD dwSetFlags;
    DWORD dwUnsetFlags;
} Q_MESSAGE_FLAGS_MSG;

typedef struct _P_ADD_2_MSG
{
    DWORD dwMsgType;
    DWORD dwMsgLen;
    DWORD dwSeqNum;
    SGADDR sgaddr;
    ULONGLONG qwSenderID;
    ULONGLONG qwBuddyID;
    DWORD dwMessageFlags;
    WORD cbDetails;
    CHAR *szBuddyAcctName;
    XMSG_DETAILS *pDetails;
} P_ADD_2_MSG;

typedef struct _P_DELETE_MSG
{
    DWORD dwMsgType;
    DWORD dwMsgLen;
    DWORD dwSeqNum;
    SGADDR sgaddr;
    XUID qwSenderID;
    XUID qwBuddyID;
} P_DELETE_MSG;

typedef struct _P_ACCEPT_REQUEST_MSG
{
    DWORD dwMsgType;
    DWORD dwMsgLen;
    DWORD dwSeqNum;
    SGADDR sgaddr;
    XUID qwSenderID;
    XUID qwBuddyID;
} P_ACCEPT_REQUEST_MSG;

typedef struct _P_REJECT_REQUEST_MSG
{
    DWORD dwMsgType;
    DWORD dwMsgLen;
    DWORD dwSeqNum;
    SGADDR sgaddr;
    XUID qwSenderID;
    XUID qwBuddyID;
    BOOL Block;
} P_REJECT_REQUEST_MSG;

typedef struct _P_FRIENDS_ENUM_CREATE_MSG
{
    DWORD dwUserIndex;
    DWORD dwStartingIndex;
    DWORD dwFriendsToReturn;
    DWORD pcbBuffer[1];
    HANDLE ph[1];
} P_FRIENDS_ENUM_CREATE_MSG;

typedef struct _P_INVITE_2_MSG
{
    DWORD dwMsgType;
    DWORD dwMsgLen;
    DWORD dwSeqNum;
    SGADDR sgaddr;
    ULONGLONG qwUserID;
    ULONGLONG qwSenderContext;
    DWORD dwTitleID;
    DWORD dwMessageFlags;
    WORD cInvitees;
    WORD cbDetails;
    ULONGLONG *pqwInviteeIDs;
    XMSG_DETAILS *pDetails;
} P_INVITE_2_MSG;

typedef struct _XMSG_GAME_INVITE_CANCEL
{
    XUID XuidUser;
    WORD cInvitees;
    XUID *pXuidInvitees;
    XNKID SessionID;
    XOVERLAPPED pXOverlapped[1];
} XMSG_GAME_INVITE_CANCEL;

typedef struct _P_CANCEL_MSG
{
    DWORD dwMsgType;
    DWORD dwMsgLen;
    DWORD dwSeqNum;
    SGADDR sgaddr;
    ULONGLONG qwUserID;
    XNKID SessionID;
    WORD cInvitees;
    ULONGLONG *pqwInviteeIDs;
} P_CANCEL_MSG;

typedef struct _XMSG_GAMEINVITE_ANSWER_INFO
{
    XUID xuidInvitingUser;
    DWORD dwTitleID;
    XNKID sessionID;
    XNADDR xnaddrHost;
    XNKEY xnkeyHost;
} XMSG_GAMEINVITE_ANSWER_INFO, *PXMSG_GAMEINVITE_ANSWER_INFO;

typedef struct _XMSG_GAME_INVITE_ANSWER
{
    XUID XuidUser;
    XMSG_GAMEINVITE_ANSWER_INFO pAnswerInfo[1];
    XMSG_INVITE_ANSWER_TYPE Answer;
    BOOL fFromGameInvite;
    XOVERLAPPED pXOverlapped[1];
} XMSG_GAME_INVITE_ANSWER;

typedef struct _P_INVITE_ANSWER_MSG
{
    DWORD dwMsgType;
    DWORD dwMsgLen;
    DWORD dwSeqNum;
    SGADDR sgaddr;
    ULONGLONG qwUserID;
    ULONGLONG qwHostID;
    XNKID MatchSessionID;
    WORD wAnswer;
} P_INVITE_ANSWER_MSG;

typedef struct _XMSG_GAME_INVITE_GET_ACCEPTED
{
    DWORD dwUserIndex;
    XINVITE_INFO pInfo[1];
} XMSG_GAME_INVITE_GET_ACCEPTED;

typedef struct _P_ADD_AFFILIATES_MSG
{
    DWORD dwMsgType;
    DWORD dwMsgLen;
    DWORD dwSeqNum;
    SGADDR sgaddr;
    ULONGLONG qwUserID;
    DWORD dwListFlags;
    DWORD dwTitleID;
    WORD cwAffiliates;
    ULONGLONG *pqwAfilliateIDs;
} P_ADD_AFFILIATES_MSG;

typedef struct _P_IS_AFFILIATE_REPLY_MSG
{
    HRESULT hr;
    ULONGLONG qwAffiliateID;
    DWORD dwListFlags;
} P_IS_AFFILIATE_REPLY_MSG;

typedef struct _P_IS_AFFILIATE_MSG
{
    DWORD dwMsgType;
    DWORD dwMsgLen;
    DWORD dwSeqNum;
    SGADDR sgaddr;
    ULONGLONG qwUserID;
    ULONGLONG qwAffiliateID;
    P_IS_AFFILIATE_REPLY_MSG *pReply;
} P_IS_AFFILIATE_MSG;

typedef struct _P_QUERY_AFFILIATES_REPLY_DATA_MSG
{
    ULONGLONG qwAffiliateID;
    DWORD dwListFlags;
    DWORD dwTitleID;
    ULONGLONG qwSessionID;
    MSGTIME mtDateUpdated;
    CHAR szGamerTag[16];
} P_QUERY_AFFILIATES_REPLY_DATA_MSG;

typedef struct _P_QUERY_AFFILIATES_REPLY_MSG
{
    HRESULT hr;
    DWORD cdwResults;
    P_QUERY_AFFILIATES_REPLY_DATA_MSG *rgResults;
} P_QUERY_AFFILIATES_REPLY_MSG;

typedef struct _P_QUERY_AFFILIATES_MSG
{
    DWORD dwMsgType;
    DWORD dwMsgLen;
    DWORD dwSeqNum;
    SGADDR sgaddr;
    ULONGLONG qwUserID;
    DWORD dwListFlags;
    DWORD cdwLimit;
    DWORD dwOnlineTitleID;
    P_QUERY_AFFILIATES_REPLY_MSG *pReply;
} P_QUERY_AFFILIATES_MSG;

typedef struct _XSIGNATURE_TO_VERIFY
{
    BYTE rgbDigest[20];
    BYTE rgbOnlineSignature[100];
} XSIGNATURE_TO_VERIFY;

typedef struct _XSIGNATURE_VERIFY_RESPONSE
{
    HRESULT hrResult;
} XSIGNATURE_VERIFY_RESPONSE;

typedef struct _XSIGNATURE_VERIFY_REQUEST
{
    XSIGNATURE_TO_VERIFY *pSignaturesToVerify;
    XSIGNATURE_VERIFY_RESPONSE *pResponse;
} XSIGNATURE_VERIFY_REQUEST;

typedef struct _XSIGNATURE_CONTENT_TUPLE
{
    DWORD dwTitleId;
    DWORD dwTitleVersion;
    ULONGLONG qwConsolePuid;
    BYTE pConsoleId[5];
    ULONGLONG pUserPuids[4];
    BYTE pDigest[20];
} XSIGNATURE_CONTENT_TUPLE;

typedef struct _XSIGNATURE_CHECK_REVOCATION_RESPONSE
{
    DWORD dwNumHrs;
    HRESULT *pHrs;
} XSIGNATURE_CHECK_REVOCATION_RESPONSE;

typedef struct _XSIGNATURE_CHECK_REVOCATION_REQUEST
{
    DWORD dwNumContentTuples;
    XSIGNATURE_CONTENT_TUPLE *pTuples;
    XSIGNATURE_CHECK_REVOCATION_RESPONSE *pResponse;
} XSIGNATURE_CHECK_REVOCATION_REQUEST;

typedef struct _XSTORAGE_ENDPOINT
{
    IN_ADDR inaPrimaryAddress;
    WORD wPrimaryPort;
    IN_ADDR inaAlternateAddress;
    WORD wAlternatePort;
} XSTORAGE_ENDPOINT;

typedef struct _XRESOLVE_DOMAIN_STRING
{
    WORD wNumStringChars;
    WCHAR *pwszString;
} XRESOLVE_DOMAIN_STRING;

typedef struct _XRESOLVE_NAME_RESPONSE
{
    XSTORAGE_ENDPOINT StorageEndpoint;
    FILETIME ftExpiration;
    XRESOLVE_DOMAIN_STRING ResolveDomainStringRule;
} XRESOLVE_NAME_RESPONSE;

typedef struct _XRESOLVE_NAME_REQUEST
{
    XRESOLVE_DOMAIN_STRING pResolveString[1];
    XRESOLVE_NAME_RESPONSE *pResponse;
} XRESOLVE_NAME_REQUEST;

typedef struct _XSTORAGE_PATH_STRING
{
    WORD wNumPathChars;
    WCHAR *pwszPath;
} XSTORAGE_PATH_STRING;

typedef struct _XSTORAGE_ACCESS_TOKEN
{
    WORD wOperation;
    WORD wAccessTokenVersion;
    DWORD dwServiceId;
    DWORD dwFlags;
    ULONGLONG qwUserId;
    ULONGLONG qwXboxId;
} XSTORAGE_ACCESS_TOKEN;

typedef struct _XSTORAGE_ACCESS_TOKEN_READ
{
    FILETIME ftTokenExpirationDate;
    WORD wSignatureSize;
    BYTE *prgbSignature;
} XSTORAGE_ACCESS_TOKEN_READ;

typedef struct _XSTORAGE_ACCESS_TOKEN_WRITE
{
    FILETIME ftTokenExpirationDate;
    FILETIME ftFileExpirationDate;
    DWORD dwMaxFileSize;
    WORD wSignatureSize;
    BYTE *prgbSignature;
} XSTORAGE_ACCESS_TOKEN_WRITE;

typedef struct _XSTORAGE_DOWNLOAD_RESPONSE
{
    DWORD dwTitleId;
    DWORD dwTitleVersion;
    ULONGLONG qwOwnerId;
    BYTE bCountryId;
    ULONGLONG qwXboxId;
    BYTE bCompressionType;
    DWORD dwContentType;
    BYTE rgbLiveSignature[100];
    DWORD dwInstallSize;
    FILETIME ftCreated;
    WORD wAttributesSize;
    DWORD dwPackageSize;
    BYTE *prgbAttributes;
} XSTORAGE_DOWNLOAD_RESPONSE;

typedef struct _XSTORAGE_DOWNLOAD_REQUEST
{
    XSTORAGE_ACCESS_TOKEN pStorageAccessToken[1];
    XSTORAGE_PATH_STRING pStoragePathString[1];
    XSTORAGE_ACCESS_TOKEN_READ pStorageAccessTokenRead[1];
    DWORD dwTitleId;
    DWORD dwTitleVersion;
    BYTE bCountryId;
    DWORD dwRangeStart;
    DWORD dwRangeEnd;
    FILETIME pftLastModified[1];
    XSTORAGE_DOWNLOAD_RESPONSE *pResponse;
} XSTORAGE_DOWNLOAD_REQUEST;

typedef struct _XSTORAGE_UPLOAD_REQUEST
{
    XSTORAGE_ACCESS_TOKEN pStorageAccessToken[1];
    XSTORAGE_PATH_STRING pStoragePathString[1];
    XSTORAGE_ACCESS_TOKEN_WRITE pStorageAccessTokenWrite[1];
    DWORD dwTitleId;
    DWORD dwTitleVersion;
    BYTE bCountryId;
    BYTE bCompressionType;
    DWORD dwContentType;
    BYTE *prgbDigest;
    BYTE *prgbLiveSignature;
    DWORD dwInstallSize;
    WORD wAttributesSize;
    DWORD dwPackageSize;
    BYTE *prgbAttributes;
} XSTORAGE_UPLOAD_REQUEST;

typedef struct _XSTORAGE_ENUMERATE_REQUEST
{
    XSTORAGE_ACCESS_TOKEN pStorageAccessToken[1];
    XSTORAGE_PATH_STRING pStoragePathString[1];
    XSTORAGE_ACCESS_TOKEN_READ pStorageAccessTokenRead[1];
    DWORD dwTitleId;
    DWORD dwTitleVersion;
    BYTE bCountryId;
    DWORD dwStartingIndex;
    DWORD dwEndingIndex;
    FILETIME ftLastModified;
    XSTORAGE_ENUMERATE_RESULTS *pResults;
} XSTORAGE_ENUMERATE_REQUEST;

typedef struct _XSTORAGE_DELETE_REQUEST
{
    XSTORAGE_ACCESS_TOKEN pStorageAccessToken[1];
    XSTORAGE_PATH_STRING pStoragePathString[1];
    XSTORAGE_ACCESS_TOKEN_READ pStorageAccessTokenRead[1];
    DWORD dwTitleId;
    DWORD dwTitleVersion;
} XSTORAGE_DELETE_REQUEST;

typedef struct _XSTORAGE_DOWNLOAD_TO_DIRECTORY_RESULTS_INTERNAL
{
    XCONTENT_DATA ContentData;
} XSTORAGE_DOWNLOAD_TO_DIRECTORY_RESULTS_INTERNAL;

typedef struct _XSTORAGE_DOWNLOAD_TO_DIRECTORY_PARAMS_INTERNAL
{
    DWORD dwUserIndex;
    DWORD dwServerPathLength;
    WCHAR *wszServerPath;
    DWORD dwDisplayNameLength;
    WCHAR *wszDisplayName;
    XCONTENTDEVICEID DeviceID;
    XSTORAGE_DOWNLOAD_TO_DIRECTORY_RESULTS_INTERNAL *pResults;
} XSTORAGE_DOWNLOAD_TO_DIRECTORY_PARAMS_INTERNAL;

typedef struct _XSTORAGE_DOWNLOAD_TO_MEMORY_PARAMS
{
    DWORD dwUserIndex;
    DWORD dwServerPathLength;
    WCHAR *wszServerPath;
    DWORD dwBufferSize;
    DWORD dwBufferPointer;
    XSTORAGE_DOWNLOAD_TO_MEMORY_RESULTS *pResults;
} XSTORAGE_DOWNLOAD_TO_MEMORY_PARAMS;

typedef struct _XSTORAGE_UPLOAD_FROM_DIRECTORY_PARAMS_INTERNAL
{
    DWORD dwUserIndex;
    DWORD dwServerPathLength;
    WCHAR *wszServerPath;
    DWORD dwLocalPathLength;
    CHAR *szLocalPath;
} XSTORAGE_UPLOAD_FROM_DIRECTORY_PARAMS_INTERNAL;

typedef struct _XSTORAGE_UPLOAD_FROM_MEMORY_PARAMS
{
    DWORD dwUserIndex;
    DWORD dwServerPathLength;
    WCHAR *wszServerPath;
    DWORD dwBufferSize;
    DWORD dwBufferPointer;
} XSTORAGE_UPLOAD_FROM_MEMORY_PARAMS;

typedef struct _XSTORAGE_ENUMERATE_PARAMS
{
    DWORD dwUserIndex;
    DWORD dwServerPathLength;
    WCHAR *wszServerPath;
    DWORD dwStartingIndex;
    DWORD dwMaxResultsToReturn;
    XSTORAGE_ENUMERATE_RESULTS *pResults;
} XSTORAGE_ENUMERATE_PARAMS;

typedef struct _XSTORAGE_DELETE_PARAMS
{
    DWORD dwUserIndex;
    DWORD dwServerPathLength;
    WCHAR *wszServerPath;
} XSTORAGE_DELETE_PARAMS;

typedef struct _XMSG_SEND_PARAMS
{
    XUID XuidSender;
    XMSG_HANDLE hMsg;
    DWORD cRecipients;
    XUID *pXuidRecipients;
    XMSG_SEND_RESULT *pResults;
} XMSG_SEND_PARAMS;

typedef struct _XMSG_DOWNLOAD_ATTACH_TO_MEM_PARAMS
{
    XUID XuidUser;
    DWORD dwDetailsBlobsPointer;
    DWORD dwPropTag;
    DWORD dwBufferSize;
    DWORD dwBufferPointer;
} XMSG_DOWNLOAD_ATTACH_TO_MEM_PARAMS;

typedef struct _XFRIENDS_REQUEST_PARAMS
{
    XUID XuidFromUser;
    XUID qwBuddyID;
    DWORD dwUserNameSize;
    XMSG_HANDLE hMsg;
} XFRIENDS_REQUEST_PARAMS;

typedef struct _XFRIENDS_REQUEST_BY_NAME_PARAMS
{
    XUID XuidFromUser;
    XUID qwBuddyID;
    DWORD dwUserNameSize;
    CHAR *szUserName;
    XMSG_HANDLE hMsg;
} XFRIENDS_REQUEST_BY_NAME_PARAMS;

typedef struct _XMSG_INVITE_SEND_PARAMS
{
    DWORD dwUserIndex;
    DWORD dwNumInvitees;
    XUID *pXuidInvitees;
    DWORD cchText;
    WCHAR *pszText;
    XMSG_HANDLE hMsg;
} XMSG_INVITE_SEND_PARAMS;

typedef struct _XMSG_INVITE_SEND_MESSAGE_PARAMS
{
    DWORD dwUserIndex;
    DWORD dwNumInvitees;
    XUID *pXuidInvitees;
    DWORD cchText;
    WCHAR *pszText;
    XMSG_HANDLE hMsg;
} XMSG_INVITE_SEND_MESSAGE_PARAMS;

typedef struct _XREFERRAL_LOCATION
{
    WORD wRank;
    WORD wUrlSize;
    CHAR *pszUrl;
} XREFERRAL_LOCATION;

typedef struct _XCONTENT_REFERRAL_RESPONSE
{
    DWORD dwPackageSize;
    DWORD dwInstallSize;
    BYTE rgbSymKey[16];
    BYTE rgbPubKey[284];
    WORD wNumLocations;
    XREFERRAL_LOCATION *pReferralLocations;
} XCONTENT_REFERRAL_RESPONSE;

typedef struct _XCONTENT_REFERRAL_REQUEST
{
    ULONGLONG qwUserId;
    BYTE abContentId[20];
    XCONTENT_REFERRAL_RESPONSE *pResults;
} XCONTENT_REFERRAL_REQUEST;

typedef struct _XCONTENT_REFRESH_LICENSE_RESPONSE
{
    WORD wContentHeaderLength;
    BYTE *pbContentHeader;
} XCONTENT_REFRESH_LICENSE_RESPONSE;

typedef struct _XCONTENT_REFRESH_LICENSE_REQUEST
{
    ULONGLONG qwUserId;
    ULONGLONG qwMachineId;
    WORD wContentHeaderLength;
    BYTE *pbContentHeader;
    XCONTENT_REFRESH_LICENSE_RESPONSE *pResults;
} XCONTENT_REFRESH_LICENSE_REQUEST;

typedef struct _XCONTENT_DOWNLOAD_PARAMS
{
    DWORD dwUserIndex;
    BYTE *pbContentId;
    DWORD dwTargetDirectoryLength;
    CHAR *szTargetDirectory;
    DWORD dwFlags;
} XCONTENT_DOWNLOAD_PARAMS;

typedef struct _XCONTENT_DOWNLOAD_GET_INPROGRESS_METADATA
{
    DWORD dwUserIndex;
    BYTE *pbContentId;
    DWORD dwTargetDirectoryLength;
    CHAR *szTargetDirectory;
    BYTE pContentHeader[1];
    BYTE pContentMetaData[1];
    BYTE pbOtherMetaData[1];
    DWORD pdwOtherMetaDataSize[1];
} XCONTENT_DOWNLOAD_GET_INPROGRESS_METADATA;

typedef struct _XUPDATE_REFERRAL_RESPONSE
{
    WORD wFlags;
    WORD wNumLocations;
    DWORD dwPackageSize;
    DWORD dwInstallSize;
    DWORD dwVersion;
    BYTE rgbSymKey[16];
    BYTE rgbPubKey[284];
    XREFERRAL_LOCATION *pReferralLocations;
} XUPDATE_REFERRAL_RESPONSE;

typedef struct _XUPDATE_REFERRAL_REQUEST
{
    ULONGLONG qwMachineId;
    DWORD dwTitleId;
    DWORD dwVersion;
    XUPDATE_REFERRAL_RESPONSE *pResults;
} XUPDATE_REFERRAL_REQUEST;

typedef struct _XUPDATE_DOWNLOAD_RESULTS
{
    CHAR szPackagePath[260];
} XUPDATE_DOWNLOAD_RESULTS;

typedef struct _XUPDATE_DOWNLOAD_PARAMS
{
    DWORD dwTitleId;
    DWORD dwVersion;
    XUPDATE_DOWNLOAD_RESULTS *pResults;
} XUPDATE_DOWNLOAD_PARAMS;

typedef struct _XUID_AND_FLAGS
{
    XUID xuid;
    DWORD dwUserFlags;
} XUID_AND_FLAGS;

typedef struct _XARB_REGISTRANT
{
    ULONGLONG qwMachineID;
    BYTE bTrustworthiness;
    BYTE bNumUsers;
    XUID_AND_FLAGS *rgUsers;
} XARB_REGISTRANT;

typedef struct _XARB_REGISTER_REPLY
{
    WORD wNumRegistrants;
    XARB_REGISTRANT *rgRegistrants;
} XARB_REGISTER_REPLY;

typedef struct _XARB_REGISTER_REQUEST
{
    WORD wProtocolVersion;
    WORD wFlags;
    DWORD dwTitleId;
    ULONGLONG qwSessionId;
    ULONGLONG qwSessionNonce;
    WORD wMaxSessionSeconds;
    XARB_REGISTER_REPLY *pReply;
} XARB_REGISTER_REQUEST;

typedef struct _XARB_TIMEEXTEND_REQUEST
{
    WORD wProtocolVersion;
    WORD wRequestFlags;
    DWORD dwTitleID;
    ULONGLONG qwSessionID;
    ULONGLONG qwSessionNonce;
    WORD wMaxSessionSecondsFromNow;
} XARB_TIMEEXTEND_REQUEST;

typedef struct _XARB_REPORT_LOST_MACHINES
{
    BYTE bNumLostConnectivityMachineIDs;
    ULONGLONG *pLostConnectivityMachineIDs;
} XARB_REPORT_LOST_MACHINES;

typedef struct _XARB_REPORT_SUSPICIOUS_INFO
{
    BYTE bMessageLength;
    CHAR *pszMessage;
    BYTE bNumRelatedMachineIDs;
    ULONGLONG *pRelatedMachineIDs;
    BYTE bNumRelatedUsers;
    ULONGLONG *pRelatedUsers;
} XARB_REPORT_SUSPICIOUS_INFO;

typedef struct _XARB_REPORT_BYTE_BUNDLE
{
    DWORD cbBundle;
    BYTE *pBundle;
} XARB_REPORT_BYTE_BUNDLE;

typedef struct _XARB_REPORT_STATS_BUNDLE
{
    DWORD cbStats;
    XSTATS_POST_REQUEST Stats;
} XARB_REPORT_STATS_BUNDLE;

typedef struct _XARB_REPORT_REQUEST
{
    WORD wProtocolVersion;
    WORD wFlags;
    DWORD dwTitleID;
    ULONGLONG qwSessionID;
    ULONGLONG qwSessionNonce;
    XARB_REPORT_LOST_MACHINES *pLostMachines;
    XARB_REPORT_SUSPICIOUS_INFO *pSuspiciousInfo;
    XARB_REPORT_STATS_BUNDLE *pStatsBundle;
    XARB_REPORT_BYTE_BUNDLE *pCompsBundle;
} XARB_REPORT_REQUEST;

typedef struct _FB_PLAYER_REVIEW
{
    ULONGLONG qwSenderID;
    ULONGLONG qwTargetID;
    DWORD dwTitleID;
    DWORD dwType;
    ULONGLONG qwContext;
    ULONGLONG ftSubmitted;
} FB_PLAYER_REVIEW;

typedef struct _FB_AGGREGATE_REVIEW
{
    ULONGLONG qwTargetID;
    DWORD dwCount;
    DWORD dwType;
} FB_AGGREGATE_REVIEW;

typedef struct _FB_PLAYER_REVIEW_REQUEST
{
    ULONGLONG qwSenderID;
    ULONGLONG qwTargetID;
    DWORD dwTitleID;
    DWORD dwType;
    ULONGLONG qwContext;
} FB_PLAYER_REVIEW_REQUEST;

typedef struct _FB_ENUM_REVIEWS_RESPONSE
{
    DWORD hr;
    DWORD cReviews;
    FB_PLAYER_REVIEW *pReviews;
} FB_ENUM_REVIEWS_RESPONSE;

typedef struct _FB_ENUM_SENT_REVIEWS_REQUEST
{
    ULONGLONG qwSenderID;
    DWORD dwPageID;
    DWORD dwResultsPerPage;
    FB_ENUM_REVIEWS_RESPONSE *pResults;
} FB_ENUM_SENT_REVIEWS_REQUEST;

typedef struct _FB_ENUM_RECD_REVIEWS_REQUEST
{
    ULONGLONG qwTargetID;
    DWORD dwPageID;
    DWORD dwResultsPerPage;
    FB_ENUM_REVIEWS_RESPONSE *pResults;
} FB_ENUM_RECD_REVIEWS_REQUEST;

typedef struct _FB_GET_AGG_REVIEWS_RESPONSE
{
    DWORD hr;
    DWORD cAggReviews;
    FB_AGGREGATE_REVIEW *pAggReviews;
} FB_GET_AGG_REVIEWS_RESPONSE;

typedef struct _FB_GET_AGG_REVIEWS_REQUEST
{
    ULONGLONG qwTargetID;
    FB_GET_AGG_REVIEWS_RESPONSE *pResults;
} FB_GET_AGG_REVIEWS_REQUEST;

typedef struct _FB_SUBMIT_COMPAINT_REQUEST
{
    ULONGLONG qwSenderID;
    ULONGLONG qwTargetID;
    DWORD dwTitleID;
    DWORD dwType;
    ULONGLONG qwContext;
} FB_SUBMIT_COMPAINT_REQUEST;

#pragma pack(pop)


XBOXAPI
DWORD
WINAPI
_XOfferingUpdateAccessTimes(
    IN DWORD dwUserIndex,
    IN DWORD dwTitleId,
    IN DWORD dwTitleContentCategories,
    OUT XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
_XOfferingExpireMarketplaceCountsCache(
    IN DWORD dwUserIndex,
    OUT XOVERLAPPED *pXOverlapped
    );

XAMINLINE
WORD
WINAPI
_XOfferConstructRating(WORD wRatingSystem, WORD wRating)
{
    return (WORD) ((wRatingSystem << 8) | wRating);
}

XAMINLINE
DWORD
WINAPI
_XOfferPriceSizeMax()
{
    return sizeof(OFFER_PRICE) +
        (XONLINE_XBOS_MAX_OFFER_PRICE_TEXT_LENGTH * sizeof(WCHAR));
}

XAMINLINE
DWORD
WINAPI
_XOfferBasicContentInfoSizeMax(DWORD dwNumPrices)
{
    return sizeof(BASIC_CONTENT_INFO) +
        (XONLINE_XBOS_MAX_OFFER_NAME_LENGTH * sizeof(WCHAR)) +
        (XONLINE_XBOS_MAX_TITLE_NAME_LENGTH * sizeof(WCHAR)) +
        (XONLINE_XBOS_MAX_OFFER_SELL_TEXT_LENGTH * sizeof(WCHAR)) +
        (dwNumPrices * _XOfferPriceSizeMax());
}

XAMINLINE
DWORD
WINAPI
_XOfferBasicSubscriptionInfoSizeMax(DWORD dwNumPrices)
{
    return sizeof(BASIC_SUBSCRIPTION_INFO) +
        (XONLINE_XBOS_MAX_OFFER_NAME_LENGTH * sizeof(WCHAR)) +
        (XONLINE_XBOS_MAX_TITLE_NAME_LENGTH * sizeof(WCHAR)) +
        (XONLINE_XBOS_MAX_OFFER_SELL_TEXT_LENGTH * sizeof(WCHAR)) +
        (dwNumPrices * _XOfferPriceSizeMax());
}

XAMINLINE
DWORD
WINAPI
_XOfferContentEnumerateResponseSize(DWORD dwMaxOffersReturned, DWORD dwNumPrices)
{
    return sizeof(CONTENT_ENUMERATE_RESPONSE) +
        (dwMaxOffersReturned * _XOfferBasicContentInfoSizeMax(dwNumPrices));
}

XAMINLINE
DWORD
WINAPI
_XOfferSubscriptionEnumerateResponseSize(DWORD dwMaxOffersReturned, DWORD dwNumPrices)
{
    return sizeof(SUBSCRIPTION_ENUMERATE_RESPONSE) +
        (dwMaxOffersReturned * _XOfferBasicSubscriptionInfoSizeMax(dwNumPrices));
}

XAMINLINE
DWORD
WINAPI
_XOfferContentDetailsResponseSize(DWORD dwNumPrices)
{
    return sizeof(CONTENT_DETAILS_RESPONSE) + _XOfferBasicContentInfoSizeMax(dwNumPrices);
}

XAMINLINE
DWORD
WINAPI
_XOfferSubscriptionDetailsResponseSize(DWORD dwNumPrices)
{
    return sizeof(SUBSCRIPTION_DETAILS_RESPONSE) + _XOfferBasicSubscriptionInfoSizeMax(dwNumPrices);
}

XAMINLINE
DWORD
WINAPI
_XOfferBasicTitleInfoResponseSize()
{
    return sizeof(BASIC_TITLE_INFO) +
        (XONLINE_XBOS_MAX_TITLE_TITLE_LENGTH * sizeof(WCHAR));
}

XAMINLINE
DWORD
WINAPI
_XOfferEnumerateTitlesByFilterResponseSize(DWORD dwNumResults)
{
    return sizeof(ENUMERATE_TITLES_BY_FILTER_RESPONSE) + (dwNumResults * _XOfferBasicTitleInfoResponseSize());
}

XAMINLINE
DWORD
WINAPI
_XOfferGetTitleDetailsResponseSize()
{
    return sizeof(TITLE_DETAILS_RESPONSE) +
        (XONLINE_XBOS_MAX_TITLE_TITLE_LENGTH * sizeof(WCHAR)) +
        (XONLINE_XBOS_MAX_TITLE_SELL_TEXT_LENGTH * sizeof(WCHAR)) +
        (XONLINE_XBOS_MAX_TITLE_DEVELOPER_LENGTH * sizeof(WCHAR)) +
        (XONLINE_XBOS_MAX_TITLE_PUBLISHER_LENGTH * sizeof(WCHAR)) +
        (XONLINE_XBOS_MAX_TITLE_GENRE_LENGTH * sizeof(WCHAR));
}

XAMINLINE
DWORD
WINAPI
_XOfferBasicGenreInfoResponseSize()
{
    return sizeof(BASIC_GENRE_INFO) +
        (XONLINE_XBOS_MAX_GENRE_NAME_LENGTH * sizeof(WCHAR));
}

XAMINLINE
DWORD
WINAPI
_XBannerGetListResponseSize(int entries)
{
    const int cbEntrySizeMax = sizeof(BANNER_LIST_ENTRY)
                    + XONLINE_BANNER_MAX_PATH * sizeof(WCHAR);  // wszPath

    return sizeof(BANNER_LIST_RESULT)
                    + entries * cbEntrySizeMax;   // bannerList
}

XAMINLINE
DWORD
WINAPI
_XBannerGetHotListResponseSize(int entries)
{
    const int cbEntrySizeMax = sizeof(BANNER_HOTLIST_ENTRY)
                    + XONLINE_BANNER_MAX_PATH * sizeof(WCHAR)        // wszPath
                    + XONLINE_BANNER_MAX_TITLE_NAME * sizeof(WCHAR)  // wszTitleName
                    + XONLINE_BANNER_MAX_OFFER_NAME * sizeof(WCHAR)  // wszOfferName
                    + XONLINE_XBOS_MAX_OFFER_PRICE_TEXT_LENGTH * sizeof(WCHAR);  // offerPrice.wszPriceText

    return sizeof(BANNER_HOTLIST_RESULT)
                    + entries * cbEntrySizeMax;   // bannerList
}

XAMINLINE
DWORD
WINAPI
_XAccountGetPointsBalanceResponseSize()
{
    return sizeof(GET_POINTS_BALANCE_RESPONSE);
}

XAMINLINE
DWORD
WINAPI
_XOfferPurchaseGamertagResponseSize()
{
    return sizeof(OFFER_PURCHASE_GAMERTAG_RESPONSE) + (XONLINE_KEY_LENGTH * sizeof(BYTE));
}

XAMINLINE
DWORD
WINAPI
_XOfferEnumerateGenresResponseSize(DWORD dwNumResults)
{
    return sizeof(ENUMERATE_GENRES_RESPONSE) + (dwNumResults * _XOfferBasicGenreInfoResponseSize());
}

XAMINLINE
DWORD
WINAPI
_XAccountGetCreateLiveAccountResponseSize()
{
    return sizeof(CREATE_LIVE_ACCOUNT_RESPONSE);
}

XAMINLINE
DWORD
WINAPI
_XAccountGetUserInfoResponseSize()
{
    return sizeof(GET_USER_INFO_RESPONSE) +
        (MAX_FIRSTNAME_SIZE * sizeof(WCHAR)) +
        (MAX_LASTNAME_SIZE * sizeof(WCHAR)) +
        (MAX_EMAIL_SIZE * sizeof(WCHAR)) +
        (MAX_STREET_SIZE * sizeof(WCHAR)) +     // street1
        (MAX_STREET_SIZE * sizeof(WCHAR)) +     // street2
        (MAX_CITY_SIZE * sizeof(WCHAR)) +
        (MAX_DISTRICT_SIZE * sizeof(WCHAR)) +
        (MAX_STATE_SIZE * sizeof(WCHAR)) +
        (MAX_POSTALCODE_SIZE * sizeof(WCHAR));
}

XAMINLINE
DWORD
WINAPI
_XAccountRecoverAccountResponseSize()
{
    return sizeof(RECOVER_ACCOUNT_RESPONSE) +
        (XONLINE_KEY_LENGTH * sizeof(BYTE)) +
        (XONLINE_GAMERTAG_SIZE * sizeof(WCHAR)) +
        (XONLINE_USERDOMAIN_SIZE * sizeof(WCHAR)) +
        (XONLINE_REALM_NAME_SIZE * sizeof(WCHAR));
}

XAMINLINE
DWORD
WINAPI
_XAccountGetAddPaymentInstrumentResponseSize()
{
    return sizeof(ADD_PAYMENT_INSTRUMENT_RESPONSE) +
        ((MAX_INSTANCE_ID_LENGTH) * sizeof(WCHAR));
}

XAMINLINE
DWORD
WINAPI
_XAccountGetPaymentInstrumentsResponseSize()
{
    return sizeof(GET_PAYMENT_INSTRUMENTS_RESPONSE) +
        (XONLINE_XUACS_MAX_PAYMENT_INSTRUMENTS *
         (sizeof(PAYMENT_INSTRUMENT_INFO) +
          (MAX_INSTANCE_ID_LENGTH * sizeof(WCHAR)) +
          // ADDRESS_INFO strings
          (MAX_STREET_SIZE * sizeof(WCHAR)) +     // street1
          (MAX_STREET_SIZE * sizeof(WCHAR)) +     // street2
          (MAX_CITY_SIZE * sizeof(WCHAR)) +
          (MAX_DISTRICT_SIZE * sizeof(WCHAR)) +
          (MAX_STATE_SIZE * sizeof(WCHAR)) +
          (MAX_POSTALCODE_SIZE * sizeof(WCHAR)) +
          // PHONE_INFO strings
          (MAX_PHONE_PREFIX_SIZE * sizeof(WCHAR)) +
          (MAX_PHONE_NUMBER_SIZE * sizeof(WCHAR)) +
          (MAX_PHONE_EXTENSION_SIZE * sizeof(WCHAR)) +
          // CREDIT_CARD_INFO strings
          (MAX_CC_NAME_SIZE * sizeof(WCHAR)) +
          (MAX_CC_NUMBER_SIZE * sizeof(WCHAR)) +
          (MAX_CC_CCV_NUMBER_SIZE * sizeof(WCHAR)) +
          // DIRECT_DEBIT_INFO strings
          (MAX_DD_NAME_SIZE * sizeof(WCHAR)) +
          (MAX_DD_NUMBER_SIZE * sizeof(WCHAR)) +
          (MAX_DD_BANK_CODE_SIZE * sizeof(WCHAR)) +
          (MAX_DD_BRANCH_CODE_SIZE * sizeof(WCHAR)) +
          (MAX_DD_CHECK_DIGITS_SIZE * sizeof(WCHAR))
          ));
}

XAMINLINE
DWORD
WINAPI
_XAccountGetAccountInfoResponseSize()
{
    return sizeof(GET_ACCOUNT_INFO_RESPONSE) +
        (MAX_FIRSTNAME_SIZE * sizeof(WCHAR)) +
        (MAX_LASTNAME_SIZE * sizeof(WCHAR)) +
        (MAX_EMAIL_SIZE * sizeof(WCHAR)) +
        (MAX_STREET_SIZE * sizeof(WCHAR)) +     // street1
        (MAX_STREET_SIZE * sizeof(WCHAR)) +     // street2
        (MAX_CITY_SIZE * sizeof(WCHAR)) +
        (MAX_DISTRICT_SIZE * sizeof(WCHAR)) +
        (MAX_STATE_SIZE * sizeof(WCHAR)) +
        (MAX_POSTALCODE_SIZE * sizeof(WCHAR)) +
        (MAX_PHONE_PREFIX_SIZE * sizeof(WCHAR)) +
        (MAX_PHONE_NUMBER_SIZE * sizeof(WCHAR)) +
        (MAX_PHONE_EXTENSION_SIZE * sizeof(WCHAR));
}

XAMINLINE
DWORD
WINAPI
_XAccountGetAccountInfoFromPassportResponseSize()
{
    return sizeof(GET_ACCOUNT_INFO_RESPONSE) +
        (MAX_FIRSTNAME_SIZE * sizeof(WCHAR)) +
        (MAX_LASTNAME_SIZE * sizeof(WCHAR)) +
        (MAX_EMAIL_SIZE * sizeof(WCHAR)) +
        (MAX_STREET_SIZE * sizeof(WCHAR)) +     // street1
        (MAX_STREET_SIZE * sizeof(WCHAR)) +     // street2
        (MAX_CITY_SIZE * sizeof(WCHAR)) +
        (MAX_DISTRICT_SIZE * sizeof(WCHAR)) +
        (MAX_STATE_SIZE * sizeof(WCHAR)) +
        (MAX_POSTALCODE_SIZE * sizeof(WCHAR)) +
        (MAX_PHONE_PREFIX_SIZE * sizeof(WCHAR)) +
        (MAX_PHONE_NUMBER_SIZE * sizeof(WCHAR)) +
        (MAX_PHONE_EXTENSION_SIZE * sizeof(WCHAR));
}

XAMINLINE
DWORD
WINAPI
_XAccountGetPostalCodeResponseSize()
{
    return sizeof(GET_POSTAL_CODE_RESPONSE) +
        (XONLINE_XUACS_MAX_POSTAL_CODE_MATCHES *
         (sizeof(POSTAL_CODE_MATCH) +
          (MAX_POSTALCODE_SIZE * sizeof(WCHAR)) +
          (MAX_STATE_SIZE * sizeof(WCHAR)) +
          (MAX_CITY_SIZE * sizeof(WCHAR)) +
          (MAX_STREET_SIZE * sizeof(WCHAR))));
}

XAMINLINE
DWORD
WINAPI
_XAccountGetUserSubscriptionDetailsResponseSize()
{
    return sizeof(GET_USER_SUBSCRIPTION_DETAILS_RESPONSE) +
        (MAX_INSTANCE_ID_LENGTH * sizeof(WCHAR)) +
        (XONLINE_XUACS_MAX_SUBSCRIPTION_DESCRIPTION_LENGTH * sizeof(WCHAR)) +
        (XONLINE_XUACS_MAX_SUBSCRIPTION_FRIENDLY_NAME_LENGTH * sizeof(WCHAR)) +
        // GET_USER_SUBSCRIPTION_DETAILS_DATA strings
        (XONLINE_XUACS_MAX_ISO_CODE_LENGTH * sizeof(WCHAR)) +
        (XONLINE_XUACS_MAX_FORMATTED_PRICE_LENGTH * sizeof(WCHAR)) +
        // GET_USER_SUBSCRIPTION_DETAILS_DATA strings
        (XONLINE_XUACS_MAX_ISO_CODE_LENGTH * sizeof(WCHAR)) +
        (XONLINE_XUACS_MAX_FORMATTED_PRICE_LENGTH * sizeof(WCHAR)) +
        // PAYMENT_INSTRUMENT_INFO strings
        (MAX_INSTANCE_ID_LENGTH * sizeof(WCHAR)) +
        // ADDRESS_INFO strings
        (MAX_STREET_SIZE * sizeof(WCHAR)) +     // street1
        (MAX_STREET_SIZE * sizeof(WCHAR)) +     // street2
        (MAX_CITY_SIZE * sizeof(WCHAR)) +
        (MAX_DISTRICT_SIZE * sizeof(WCHAR)) +
        (MAX_STATE_SIZE * sizeof(WCHAR)) +
        (MAX_POSTALCODE_SIZE * sizeof(WCHAR)) +
        // PHONE_INFO strings
        (MAX_PHONE_PREFIX_SIZE * sizeof(WCHAR)) +
        (MAX_PHONE_NUMBER_SIZE * sizeof(WCHAR)) +
        (MAX_PHONE_EXTENSION_SIZE * sizeof(WCHAR)) +
        // CREDIT_CARD_INFO strings
        (MAX_CC_NAME_SIZE * sizeof(WCHAR)) +
        (MAX_CC_NUMBER_SIZE * sizeof(WCHAR)) +
        (MAX_CC_CCV_NUMBER_SIZE * sizeof(WCHAR)) +
        // DIRECT_DEBIT_INFO strings
        (MAX_DD_NAME_SIZE * sizeof(WCHAR)) +
        (MAX_DD_NUMBER_SIZE * sizeof(WCHAR)) +
        (MAX_DD_BANK_CODE_SIZE * sizeof(WCHAR)) +
        (MAX_DD_BRANCH_CODE_SIZE * sizeof(WCHAR)) +
        (MAX_DD_CHECK_DIGITS_SIZE * sizeof(WCHAR));
}

XAMINLINE
DWORD
WINAPI
_XAccountGetVerifyBillingTokenResponseSize()
{
    return sizeof(VERIFY_BILLING_TOKEN_RESPONSE);
}

XAMINLINE
DWORD
WINAPI
_XAccountGetMigrateXbox1UserResponseSize()
{
    return sizeof(MIGRATE_XBOX1_USER_RESPONSE) +
        (MAX_GAMERTAG_SIZE * sizeof(WCHAR)) +
        (XONLINE_USERDOMAIN_SIZE * sizeof(WCHAR)) +
        (XONLINE_REALM_NAME_SIZE * sizeof(WCHAR));
}

XAMINLINE
DWORD
WINAPI
_XAccountGetMigrateXboxComUserResponseSize()
{
    return sizeof(MIGRATE_XBOX_COM_USER_RESPONSE) +
        (MAX_GAMERTAG_SIZE * sizeof(WCHAR)) +
        (XONLINE_USERDOMAIN_SIZE * sizeof(WCHAR)) +
        (XONLINE_REALM_NAME_SIZE * sizeof(WCHAR));
}

XAMINLINE
DWORD
WINAPI
_XAccountReserveGamertagResponseSize(DWORD dwNumResults)
{
    return sizeof(ACCOUNT_RESERVE_GAMERTAG_RESPONSE) +
        (dwNumResults * (sizeof(ACCOUNT_SUGGESTED_GAMERTAG) +
                         ((MAX_GAMERTAG_SIZE+1) * sizeof(WCHAR))));
}

XAMINLINE
DWORD
WINAPI
_XAccountVerifyBillingInfoResponseSize()
{
    return sizeof(ACCOUNT_VERIFY_BILLING_INFO_RESPONSE) +
        (MAX_FIRSTNAME_SIZE * sizeof(WCHAR)) +
        (MAX_LASTNAME_SIZE * sizeof(WCHAR)) +
        (MAX_EMAIL_SIZE * sizeof(WCHAR)) +
        (MAX_STREET_SIZE * sizeof(WCHAR)) +     // street1
        (MAX_STREET_SIZE * sizeof(WCHAR)) +     // street2
        (MAX_CITY_SIZE * sizeof(WCHAR)) +
        (MAX_DISTRICT_SIZE * sizeof(WCHAR)) +
        (MAX_STATE_SIZE * sizeof(WCHAR)) +
        (MAX_POSTALCODE_SIZE * sizeof(WCHAR)) +
        (MAX_PHONE_PREFIX_SIZE * sizeof(WCHAR)) +
        (MAX_PHONE_NUMBER_SIZE * sizeof(WCHAR)) +
        (MAX_PHONE_EXTENSION_SIZE * sizeof(WCHAR));
}

XAMINLINE
DWORD
WINAPI
_XPassportGetEncryptedProxyParametersResponseSize()
{
    return sizeof(PASSPORT_ENCRYPTED_PROXY_PARAMETERS) +
        (XONLINE_PASSPORT_LOGIN_TOKEN_REQUEST_MAX_LEN * sizeof(BYTE)) +
        (XONLINE_PASSPORT_PUBLIC_KEY_MODULUS_MAX_LEN * sizeof(BYTE));
}

XAMINLINE
DWORD
WINAPI
_XPassportGetSecretQuestionsResponseSize()
{
    return sizeof(PASSPORT_GET_SECRET_QUESTION_RESPONSE) +
        (XONLINE_PASSPORT_SECRET_QUESTION_MAX_COUNT *
            (sizeof(PASSPORT_SECRET_QUESTION) +
            (XONLINE_PASSPORT_SECRET_QUESTION_MAX_LEN+1) * sizeof(WCHAR))
        );
}

XAMINLINE
DWORD
WINAPI
_XPassportGetUserDataResponseSize()
{
    return sizeof(PASSPORT_GET_USER_DATA_RESPONSE) +
        ((MAX_FIRSTNAME_SIZE+1)       * sizeof(WCHAR)) +
        ((MAX_LASTNAME_SIZE+1)        * sizeof(WCHAR)) +
        ((MAX_STREET_SIZE+1)          * sizeof(WCHAR)) +
        ((MAX_STREET_SIZE+1)          * sizeof(WCHAR)) +
        ((MAX_CITY_SIZE+1)            * sizeof(WCHAR)) +
        ((MAX_DISTRICT_SIZE+1)        * sizeof(WCHAR)) +
        ((MAX_STATE_SIZE+1)           * sizeof(WCHAR)) +
        ((MAX_POSTALCODE_SIZE+1)      * sizeof(WCHAR)) +
        ((MAX_PHONE_PREFIX_SIZE+1)    * sizeof(WCHAR)) +
        ((MAX_PHONE_NUMBER_SIZE+1)    * sizeof(WCHAR)) +
        ((MAX_PHONE_EXTENSION_SIZE+1) * sizeof(WCHAR));
}

XAMINLINE
DWORD
WINAPI
_XPassportGetMemberNameResponseSize()
{
    return sizeof(PASSPORT_GET_MEMBER_NAME_RESPONSE) +
        ((XONLINE_PASSPORT_MEMBER_NAME_MAX_LEN+1) * sizeof(CHAR)) +
        ((XONLINE_PASSPORT_MEMBER_NAME_MAX_LEN+1) * sizeof(CHAR));
}

XBOXAPI
DWORD
WINAPI
_XPassportCreate(
    IN PASSPORT_ENCRYPTED_PROXY_PARAMETERS* pProxyParameters,
    IN CHAR *szPassportMemberName,
    IN CHAR *szPassword,
    IN WCHAR *szSecretQuestion,
    IN WCHAR *szSecretAnswer,
    IN DWORD cbSessionToken,
    OUT PASSPORT_SESSION_TOKEN *pSessionToken,
    IN OPTIONAL XOVERLAPPED *pXOverlapped);

XBOXAPI
DWORD
WINAPI
_XPassportChangePassword(
    IN PASSPORT_ENCRYPTED_PROXY_PARAMETERS* pProxyParameters,
    IN PASSPORT_SESSION_TOKEN* pSessionToken,
    IN CHAR *szPassportMemberName,
    IN CHAR *szOldPassword,
    IN CHAR *szPassword,
    IN WCHAR *szSecretQuestion,
    IN WCHAR *szSecretAnswer,
    IN OPTIONAL XOVERLAPPED *pXOverlapped);

XBOXAPI
DWORD
WINAPI
_XPassportLogin(
    IN PASSPORT_ENCRYPTED_PROXY_PARAMETERS* pProxyParameters,
    IN CHAR* szPassportMemberName,
    IN CHAR* szPassword,
    OUT PASSPORT_SESSION_TOKEN *pSessionToken,
    IN OPTIONAL XOVERLAPPED *pXOverlapped);

#define XONLINE_LOGON_FLAG_TICKETS_ONLY         0x00000001
#define XONLINE_LOGON_FLAG_UPDATE_SERVICE_ONLY  0x00000002

XBOXAPI
DWORD
XOnlineLogon(
    IN  const XNET_LOGON_USER   *rgLogonUsers,
    IN  DWORD                   dwFlags,
    OUT XOVERLAPPED             *pXOverlapped   OPTIONAL
    );

XBOXAPI
DWORD
XOnlineLogoff(
    OUT XOVERLAPPED             *pXOverlapped   OPTIONAL
    );

XAMINLINE
HRESULT
WINAPI
XOnlineGetLogonHR(
    VOID
    )
{
    return XMsgInProcessCall(HXAMAPP_XLIVEBASE, XM_LIVEBASE_LOGONGETHR,
        (UINT_PTR)NULL, (UINT_PTR)NULL);
}

XAMINLINE
HRESULT
WINAPI
XOnlineGetLogonUsers(PXNET_LOGON_USER pUsers)
{
    return XMsgInProcessCall(HXAMAPP_XLIVEBASE, XM_LIVEBASE_LOGONGETUSERS, (UINT_PTR)pUsers, (UINT_PTR)NULL);
}


XAMINLINE
DWORD
WINAPI
XOnlineGetLogonID(
    VOID
    )
{
    DWORD dwID;
    if (FAILED(XMsgInProcessCall(HXAMAPP_XLIVEBASE, XM_LIVEBASE_LOGONGETID, (UINT_PTR)&dwID, (UINT_PTR)NULL)))
    {
        dwID = 0;
    }
    return dwID;
}

XBOXAPI
DWORD
WINAPI
XStorageDownloadToDirectoryGetProgress(
    IN XOVERLAPPED *pXOverlapped,
    OUT OPTIONAL DWORD *pdwPercentComplete,
    OUT OPTIONAL ULONGLONG *pqwNumerator,
    OUT OPTIONAL ULONGLONG *pqwDenominator
    );

XBOXAPI
DWORD
WINAPI
XStorageUploadFromDirectoryGetProgress(
    IN XOVERLAPPED *pXOverlapped,
    OUT OPTIONAL DWORD *pdwPercentComplete,
    OUT OPTIONAL ULONGLONG *pqwNumerator,
    OUT OPTIONAL ULONGLONG *pqwDenominator
    );


XBOXAPI
DWORD
WINAPI
XMessageSendGetProgress(
    IN XOVERLAPPED *pXOverlapped,
    OUT OPTIONAL DWORD *pdwPercentComplete,
    OUT OPTIONAL ULONGLONG *pqwNumerator,
    OUT OPTIONAL ULONGLONG *pqwDenominator
    );

XBOXAPI
DWORD
WINAPI
XMessageDownloadAttachmentToMemoryGetProgress(
    IN XOVERLAPPED *pXOverlapped,
    OUT OPTIONAL DWORD *pdwPercentComplete,
    OUT OPTIONAL ULONGLONG *pqwNumerator,
    OUT OPTIONAL ULONGLONG *pqwDenominator
    );

XBOXAPI
DWORD
WINAPI
XContentDownloadGetProgress(
    IN XOVERLAPPED *pXOverlapped,
    OUT OPTIONAL DWORD *pdwPercentComplete,
    OUT OPTIONAL ULONGLONG *pqwNumerator,
    OUT OPTIONAL ULONGLONG *pqwDenominator
    );

XBOXAPI
DWORD
WINAPI
XUpdateDownloadGetProgress(
    IN XOVERLAPPED *pXOverlapped,
    OUT OPTIONAL DWORD *pdwPercentComplete,
    OUT OPTIONAL ULONGLONG *pqwNumerator,
    OUT OPTIONAL ULONGLONG *pqwDenominator
    );

//
// Generic online task progress monitoring
//
XBOXAPI
DWORD
WINAPI
XOnlineGetTaskProgress(
    IN XOVERLAPPED *pXOverlapped,
    OUT OPTIONAL DWORD *pdwPercentComplete,
    OUT OPTIONAL ULONGLONG *pqwNumerator,
    OUT OPTIONAL ULONGLONG *pqwDenominator
    );


//
// Throttle setting access (debug only)
//

XBOXAPI
DWORD
WINAPI
XOnlineGetRequestThrottleSettings(
    IN DWORD dwOrdinal,
    OUT XONLINE_REQUEST_THROTTLE_SETTINGS *pRequestThrottleSettings
    );

XBOXAPI
DWORD
WINAPI
XOnlineSetRequestThrottleSettings(
    IN DWORD dwOrdinal,
    IN const XONLINE_REQUEST_THROTTLE_SETTINGS *pRequestThrottleSettings
    );


//
// Privileges
//

XAMINLINE
BOOL
WINAPI
XOnlineCheckUserPrivilege(
    IN      XUID                        xuidUser,
    IN      DWORD                       dwPrivilege
    )
{
    XUSER_PRIVILEGE_MSG Msg;

    ZeroMemory(&Msg, sizeof(XUSER_PRIVILEGE_MSG));
    Msg.xuidUser = xuidUser;
    Msg.dwPrivilege = dwPrivilege;

    if (FAILED(XMsgInProcessCall(HXAMAPP_XLIVEBASE, XM_LIVEBASE_LOGONCHECKUSERPRIVILEGE,
        (UINT_PTR)&Msg, (UINT_PTR)NULL) ))
    {
        Msg.fResult = FALSE;
    }

    return Msg.fResult;
}


XAMINLINE
BOOL
WINAPI
XOnlineAreUsersFriends(
    IN      XUID                        xuidUser,
    IN      PXUID                       pXuids,
    IN      DWORD                       dwXuidCount,
    IN OUT  PXOVERLAPPED                pOverlapped     OPTIONAL
    )
{
    XUSER_PRIVILEGE_MSG Msg;

    ZeroMemory(&Msg, sizeof(XUSER_PRIVILEGE_MSG));
    Msg.xuidUser = xuidUser;
    Msg.pXuids = pXuids;
    Msg.dwXuidCount = dwXuidCount;
    Msg.pOverlapped = pOverlapped;

    if (FAILED(XMsgInProcessCall(HXAMAPP_XLIVEBASE, XM_LIVEBASE_AREUSERSFRIENDS,
        (UINT_PTR)&Msg, (UINT_PTR)NULL) ))
    {
        Msg.fResult = FALSE;
    }

    return Msg.fResult;
}


//
// UACS helper functions
//

BOOL
WINAPI
XOnlinepGetPrivilegeBit(
    DWORD *rgPrivileges,
    DWORD dwPrivilegeBit
    );

void
WINAPI
XOnlinepSetPrivilegeBit(
    DWORD *rgPrivileges,
    DWORD dwPrivilegeBit,
    BOOL bValue
    );

XBOXAPI
DWORD
WINAPI
XContentDownload(
    IN DWORD dwUserIndex,
    IN const BYTE *pbContentId,
    IN const CHAR *szTargetDirectory,
    IN DWORD dwFlags,
    IN PBYTE pbWorkspaceToUse,
    IN OUT DWORD * pcbWorkspaceToUse,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
XContentDownloadGetInProgressMetadata(
    IN DWORD dwUserIndex,
    IN const BYTE *pbContentId,
    IN const CHAR *szTargetDirectory,
    OUT BYTE *pContentHeader,
    OUT BYTE *pContentMetaData,
    OUT BYTE *pbOtherMetaData,
    OUT DWORD *pdwOtherMetaDataSize
    );

XBOXAPI
HRESULT
WINAPI
XContentGetReferral_GetContextSize(
    OUT DWORD *pcbContextSize,
    OUT DWORD *pcbRequestWireBuffer,
    OUT DWORD *pcbResponseWireBuffer
    );

XBOXAPI
HRESULT
WINAPI
XContentGetReferral_Setup(
    IN ULONGLONG qwUserId,
    IN const BYTE *abContentId,
    IN DWORD cbResults,
    OUT XCONTENT_REFERRAL_RESPONSE *pResults,
    IN PVOID pvParentTask,
    IN PBYTE pbSubTask,
    IN DWORD cbSubTask,
    IN PBYTE pbRequestWireBuffer,
    IN DWORD cbRequestWireBuffer,
    IN PBYTE pbResponseWireBuffer,
    IN DWORD cbResponseWireBuffer
    );

XBOXAPI
DWORD
WINAPI
XContentRefreshLicense(
    IN ULONGLONG qwUserId,
    IN WORD wContentHeaderLength,
    IN const BYTE *pbContentHeader,
    IN DWORD cbResults,
    OUT XCONTENT_REFRESH_LICENSE_RESPONSE *pResults,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
HRESULT
WINAPI
XContentRefreshLicenseSubTask_GetContextSize(
    OUT DWORD *pcbContextSize,
    OUT DWORD *pcbRequestWireBuffer,
    OUT DWORD *pcbResponseWireBuffer
    );

XBOXAPI
HRESULT
WINAPI
XContentRefreshLicenseSubTask_Setup(
    IN ULONGLONG qwUserId,
    IN WORD wContentHeaderLength,
    IN const BYTE *pbContentHeader,
    IN DWORD cbResults,
    OUT XCONTENT_REFRESH_LICENSE_RESPONSE *pResults,
    IN PVOID pvParentTask,
    IN PBYTE pbSubTask,
    IN DWORD cbSubTask,
    IN PBYTE pbRequestWireBuffer,
    IN DWORD cbRequestWireBuffer,
    IN PBYTE pbResponseWireBuffer,
    IN DWORD cbResponseWireBuffer
    );

XBOXAPI
HRESULT
WINAPI
XFriendsRequestWorker_GetContextSize(
    OUT DWORD *pcbContextSize,
    OUT DWORD *pcbRequestWireBuffer,
    OUT DWORD *pcbResponseWireBuffer
    );

XBOXAPI
HRESULT
WINAPI
XFriendsRequestWorker_Setup(
    IN ULONGLONG qwSenderID,
    IN ULONGLONG qwBuddyID,
    IN DWORD dwMessageFlags,
    IN WORD cbDetails,
    IN DWORD dwBuddyAcctNameSize,
    IN const CHAR *szBuddyAcctName,
    IN const XMSG_DETAILS *pDetails,
    IN PVOID pvParentTask,
    IN PBYTE pbSubTask,
    IN DWORD cbSubTask,
    IN PBYTE pbRequestWireBuffer,
    IN DWORD cbRequestWireBuffer,
    IN PBYTE pbResponseWireBuffer,
    IN DWORD cbResponseWireBuffer
    );

XBOXAPI
DWORD
WINAPI
XInviteAnswer(
    IN XUID XuidUser,
    IN const XMSG_GAMEINVITE_ANSWER_INFO *pAnswerInfo,
    IN XMSG_INVITE_ANSWER_TYPE Answer,
    IN BOOL fFromGameInvite,
    OUT XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
XInviteRevoke(
    IN XUID XuidUser,
    IN WORD cInvitees,
    IN const XUID *pXuidInvitees,
    IN XNKID SessionID,
    OUT XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
XInviteSendMessage(
    IN DWORD dwUserIndex,
    IN DWORD dwNumInvitees,
    IN const XUID *pXuidInvitees,
    IN const WCHAR *pszText,
    IN XMSG_HANDLE hMsg,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
XLookupTitleName(
    IN DWORD dwType,
    IN DWORD dwNumTitles,
    IN const DWORD *pTitleIDs,
    IN DWORD dwLanguage,
    IN DWORD cbResults,
    OUT STRING_LOOKUP_RESPONSE *pResults,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
XMessageCreate(
    IN DWORD dwMsgType,
    IN DWORD cProperties,
    IN ULONGLONG qwMessageContext,
    IN DWORD dwMessageFlags,
    IN DWORD dwExpireMinutes,
    OUT XMSG_HANDLE *phMsg
    );

XBOXAPI
DWORD
WINAPI
XMessageDelete(
    IN XUID XuidUser,
    IN DWORD dwMessageID,
    IN BOOL fBlockSender,
    OUT XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
XMessageDeleteWorker(
    IN XUID qwUserID,
    IN DWORD dwMessageID,
    IN DWORD dwFlags,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
XMessageDestroy(
    IN XMSG_HANDLE hMsg
    );

XBOXAPI
DWORD
WINAPI
XMessageDetailsGetProperty(
    IN const XMSG_DETAILS_BLOB *pDetails,
    IN WORD wPropTag,
    IN DWORD cbPropValueBuffer,
    OUT BYTE *pbPropValue,
    OUT DWORD *pcbPropValue,
    OUT DWORD *pdwAttachmentFlags
    );

XBOXAPI
DWORD
WINAPI
XMessageDetailsGetSummary(
    IN const XMSG_DETAILS_BLOB *pDetails,
    OUT XMSG_SUMMARY *pMsgSummary,
    OUT DWORD *pcProperties,
    OUT ULONGLONG *pqwAttachmentsSize
    );

XBOXAPI
DWORD
WINAPI
XMessageDownloadAttachmentToMemory(
    IN XUID XuidUser,
    IN const XMSG_DETAILS_BLOB *pDetailsBlob,
    IN DWORD dwPropTag,
    IN DWORD dwBufferSize,
    IN const BYTE *pbBuffer,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
XMessageEnumerate(
    IN XUID XuidUser,
    OUT DWORD *pcMsgSummaries,
    OUT XMSG_SUMMARY *pMsgSummaries
    );

XBOXAPI
DWORD
WINAPI
XMessageEnumerateWorker(
    IN ULONGLONG qwUserID,
    IN DWORD cbResults,
    OUT XMSG_ENUM_RESULTS *pResults,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
XMessageGetDetails(
    IN XUID XuidUser,
    IN DWORD dwMessageID,
    IN DWORD dwFlagsToSet,
    IN DWORD dwFlagsToClear,
    IN DWORD cbResults,
    OUT XMSG_DETAILS_BLOB *pResults,
    OUT XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
XMessageGetDetailsWorker(
    IN XUID qwUserID,
    IN DWORD dwMessageID,
    IN DWORD dwFlagsToSet,
    IN DWORD dwFlagsToClear,
    IN DWORD cbResults,
    OUT XMSG_DETAILS_BLOB *pResults,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
XMessageGetProperty(
    IN XMSG_HANDLE hMsg,
    IN WORD wPropTag,
    IN DWORD dwPropValueBufferSize,
    OUT BYTE *pbPropValue,
    OUT DWORD *pcbPropValue,
    OUT DWORD *pdwAttachmentFlags
    );

XBOXAPI
DWORD
WINAPI
XMessageGetSummary(
    IN XUID XuidUser,
    IN DWORD dwMessageID,
    OUT XMSG_SUMMARY *pMsgSummary
    );

XBOXAPI
DWORD
WINAPI
XMessageGetSummaryWorker(
    IN ULONGLONG qwUserID,
    IN DWORD dwMessageID,
    IN DWORD cbResults,
    OUT Q_MESSAGE_SUMMARY_REPLY_MSG *pResults,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
XMessageInviteAnswerWorker(
    IN DWORD dwMsgLen,
    IN ULONGLONG qwUserID,
    IN ULONGLONG qwHostID,
    IN XNKID MatchSessionID,
    IN WORD wAnswer,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
XMessageInviteRevokeWorker(
    IN DWORD dwMsgLen,
    IN ULONGLONG qwUserID,
    IN XNKID SessionID,
    IN WORD cInvitees,
    IN const ULONGLONG *pqwInviteeIDs,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
HRESULT
WINAPI
XMessageInviteSendWorker_GetContextSize(
    OUT DWORD *pcbContextSize,
    OUT DWORD *pcbRequestWireBuffer,
    OUT DWORD *pcbResponseWireBuffer
    );

XBOXAPI
HRESULT
WINAPI
XMessageInviteSendWorker_Setup(
    IN DWORD dwMsgLen,
    IN ULONGLONG qwUserID,
    IN ULONGLONG qwSenderContext,
    IN DWORD dwMessageFlags,
    IN WORD cInvitees,
    IN WORD cbDetails,
    IN const ULONGLONG *pqwInviteeIDs,
    IN const XMSG_DETAILS *pDetails,
    IN PVOID pvParentTask,
    IN PBYTE pbSubTask,
    IN DWORD cbSubTask,
    IN PBYTE pbRequestWireBuffer,
    IN DWORD cbRequestWireBuffer,
    IN PBYTE pbResponseWireBuffer,
    IN DWORD cbResponseWireBuffer
    );

XBOXAPI
DWORD
WINAPI
XMessageRevoke(
    IN XUID qwUserID,
    IN WORD cRecipients,
    IN const XMSG_SEND_RECIPIENT_RESULT *pRecipients,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
XMessageSend(
    IN XUID XuidSender,
    IN XMSG_HANDLE hMsg,
    IN DWORD cRecipients,
    IN const XUID *pXuidRecipients,
    IN DWORD cbResults,
    OUT XMSG_SEND_RESULT *pResults,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
HRESULT
WINAPI
XMessageSendWorker_GetContextSize(
    OUT DWORD *pcbContextSize,
    OUT DWORD *pcbRequestWireBuffer,
    OUT DWORD *pcbResponseWireBuffer
    );

XBOXAPI
HRESULT
WINAPI
XMessageSendWorker_Setup(
    IN DWORD dwMsgLen,
    IN ULONGLONG qwUserID,
    IN ULONGLONG qwSenderContext,
    IN DWORD dwMessageFlags,
    IN WORD wExpireMinutes,
    IN WORD cbDetails,
    IN WORD cRecipients,
    IN BYTE bMessageType,
    IN const CHAR *szSenderName,
    IN const ULONGLONG *qwRecipientIDs,
    IN const XMSG_DETAILS *pDetails,
    IN DWORD cbResults,
    OUT XMSG_SEND_RESULT *pResults,
    IN PVOID pvParentTask,
    IN PBYTE pbSubTask,
    IN DWORD cbSubTask,
    IN PBYTE pbRequestWireBuffer,
    IN DWORD cbRequestWireBuffer,
    IN PBYTE pbResponseWireBuffer,
    IN DWORD cbResponseWireBuffer
    );

XBOXAPI
DWORD
WINAPI
XMessageSetFlags(
    IN XUID XuidUser,
    IN DWORD dwMessageID,
    IN DWORD dwFlagsToSet,
    IN DWORD dwFlagsToClear,
    OUT XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
XMessageSetFlagsWorker(
    IN XUID qwUserID,
    IN DWORD dwMessageID,
    IN DWORD dwSetFlags,
    IN DWORD dwUnsetFlags,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
XMessageSetProperty(
    IN XMSG_HANDLE hMsg,
    IN WORD wPropTag,
    IN DWORD dwPropValueSize,
    IN const BYTE *pbPropValue,
    IN DWORD dwAttachmentFlags
    );

XBOXAPI
DWORD
WINAPI
XOnlineMatchCreate(
    IN DWORD dwPublicFilled,
    IN DWORD dwPublicOpen,
    IN DWORD dwPrivateFilled,
    IN DWORD dwPrivateOpen,
    IN DWORD dwNumAttributes,
    IN const XONLINE_ATTRIBUTE *pAttributes,
    IN DWORD cbMinRequest,
    IN DWORD cbResults,
    OUT XONLINE_MATCH_SESSION_INFO *pResults,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
XOnlineMatchDelete(
    IN XNKID SessionID,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
XOnlineMatchRegisterSession(
    IN XUID UserXuid,
    IN XNKID sessionID
    );

XBOXAPI
DWORD
WINAPI
XOnlineMatchSearch(
    IN DWORD dwProcedureIndex,
    IN DWORD dwNumResults,
    IN DWORD dwNumAttributes,
    IN const XONLINE_ATTRIBUTE *pAttributes,
    IN DWORD cbMinRequest,
    IN WORD wNumUsers,
    IN DWORD cbResults,
    OUT XONLINE_MATCH_SEARCHRESULT_HEADER *pResults,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
XOnlineMatchUpdate(
    IN XNKID SessionID,
    IN DWORD dwPublicFilled,
    IN DWORD dwPublicOpen,
    IN DWORD dwPrivateFilled,
    IN DWORD dwPrivateOpen,
    IN DWORD dwNumAttributes,
    IN const XONLINE_ATTRIBUTE *pAttributes,
    IN DWORD cbMinRequest,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
XOnlineQueryAdd(
    IN XUID qwUserId,
    IN ULONGLONG qwTeamId,
    IN DWORD dwDatasetId,
    IN DWORD dwNumAttributes,
    IN const XONLINE_QUERY_ATTRIBUTE *pAttributes,
    IN DWORD cbResults,
    OUT QUERY_ADD_RESULT *pResults,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
XOnlineQueryFindFromIds(
    IN DWORD dwDatasetId,
    IN DWORD dwProcIndex,
    IN DWORD dwNumResultSpecs,
    IN const XONLINE_QUERY_ATTRIBUTE_SPEC *pSpecs,
    IN DWORD dwNumIds,
    IN const ULONGLONG *pqwEntityIds,
    IN DWORD cbResults,
    OUT QUERY_FINDFROMIDS_RESULT *pResults,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
XOnlineQueryRemove(
    IN XUID qwUserId,
    IN ULONGLONG qwTeamId,
    IN DWORD dwDatasetId,
    IN DWORD dwProcIndex,
    IN DWORD dwNumAttributes,
    IN const XONLINE_QUERY_ATTRIBUTE *pAttributes,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
XOnlineQueryRemoveId(
    IN XUID qwUserId,
    IN ULONGLONG qwTeamId,
    IN DWORD dwDatasetId,
    IN ULONGLONG qwEntityId,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
XOnlineQuerySearch(
    IN DWORD dwDatasetId,
    IN DWORD dwProcIndex,
    IN DWORD dwPage,
    IN DWORD dwResultsPerPage,
    IN DWORD dwNumResultSpecs,
    IN const XONLINE_QUERY_ATTRIBUTE_SPEC *pSpecs,
    IN DWORD dwNumAttributes,
    IN const XONLINE_QUERY_ATTRIBUTE *pAttributes,
    IN DWORD cbResults,
    OUT QUERY_SEARCH_RESULT *pResults,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
XOnlineQuerySelect(
    IN XUID qwUserId,
    IN ULONGLONG qwTeamId,
    IN DWORD dwDatasetId,
    IN ULONGLONG qwEntityId,
    IN DWORD dwActionId,
    IN DWORD dwNumAttributes,
    IN const XONLINE_QUERY_ATTRIBUTE *pAttributes,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
XOnlineQueryUpdate(
    IN XUID qwUserId,
    IN ULONGLONG qwTeamId,
    IN DWORD dwDatasetId,
    IN DWORD dwProcIndex,
    IN DWORD dwNumAttributes,
    IN const XONLINE_QUERY_ATTRIBUTE *pAttributes,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
XOnlineQueryUpdateId(
    IN XUID qwUserId,
    IN ULONGLONG qwTeamId,
    IN DWORD dwDatasetId,
    IN DWORD dwProcIndex,
    IN ULONGLONG qwEntityId,
    IN DWORD dwNumAttributes,
    IN const XONLINE_QUERY_ATTRIBUTE *pAttributes,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
XOnlineTeamCreate(
    IN XUID qwUserID,
    IN const WCHAR *wszTeamName,
    IN const WCHAR *wszTeamDescription,
    IN const WCHAR *wszTeamMotto,
    IN const WCHAR *wszTeamURL,
    IN WORD cbTeamData,
    IN const BYTE *pbTeamData,
    IN WORD cbCreatorData,
    IN const BYTE *pbCreatorData,
    IN DWORD cbResults,
    OUT TEAM_CREATE_RESULTS *pResults,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
XOnlineTeamDelete(
    IN XUID qwUserID,
    IN ULONGLONG qwTeamID,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
XOnlineTeamEnumerate(
    IN XUID qwUserID,
    IN DWORD dwTeamCount,
    IN const ULONGLONG *rgqwTeamIDs,
    IN DWORD cbResults,
    OUT TEAM_ENUM_RESULTS *pResults,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
XOnlineTeamEnumerateByUserXUID(
    IN XUID qwUserID,
    IN DWORD cbResults,
    OUT TEAM_ENUM_BY_XUID_RESULTS *pResults,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
XOnlineTeamJoin(
    IN XUID qwUserID,
    IN ULONGLONG qwTeamID,
    IN BYTE bAnswer,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
XOnlineTeamMemberRecruit(
    IN XUID qwUserID,
    IN ULONGLONG qwTeamID,
    IN XUID qwMemberID,
    IN DWORD dwMemberPriv,
    IN WORD cbMemberData,
    IN const BYTE *pbMemberData,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
XOnlineTeamMemberRecruitByName(
    IN XUID qwUserID,
    IN ULONGLONG qwTeamID,
    IN const CHAR *szMemberName,
    IN DWORD dwMemberPriv,
    IN WORD cbMemberData,
    IN const BYTE *pbMemberData,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
XOnlineTeamMemberRemove(
    IN XUID qwUserID,
    IN ULONGLONG qwTeamID,
    IN XUID qwMemberID,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
XOnlineTeamMemberSetProperties(
    IN XUID qwUserID,
    IN ULONGLONG qwTeamID,
    IN XUID qwMemberID,
    IN DWORD dwMemberPriv,
    IN WORD cbMemberData,
    IN const BYTE *pbMemberData,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
XOnlineTeamMembersEnumerate(
    IN XUID qwUserID,
    IN ULONGLONG qwTeamID,
    IN BOOL fShowRecruits,
    IN DWORD cbResults,
    OUT TEAM_MEM_ENUM_RESULTS *pResults,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
XOnlineTeamSetProperties(
    IN XUID qwUserID,
    IN ULONGLONG qwTeamID,
    IN const WCHAR *wszTeamName,
    IN const WCHAR *wszTeamDescription,
    IN const WCHAR *wszTeamMotto,
    IN const WCHAR *wszTeamURL,
    IN WORD cbTeamData,
    IN const BYTE *pbTeamData,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
XOnlinepFriendsAcceptRequest(
    IN XUID qwSenderID,
    IN XUID qwBuddyID,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
XOnlinepFriendsRejectRequest(
    IN XUID qwSenderID,
    IN XUID qwBuddyID,
    IN BOOL Block,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
XOnlinepFriendsRemove(
    IN XUID qwSenderID,
    IN XUID qwBuddyID,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
XOnlinepFriendsRequest(
    IN XUID XuidFromUser,
    IN XUID qwBuddyID,
    IN XMSG_HANDLE hMsg,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
XOnlinepFriendsRequestByName(
    IN XUID XuidFromUser,
    IN const CHAR *szUserName,
    IN XMSG_HANDLE hMsg,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
XOnlinepMuteListAdd(
    IN XUID qwUserID,
    IN XUID qwBlockID,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
XOnlinepMuteListRemove(
    IN XUID qwUserID,
    IN XUID qwBlockID,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
XOnlinepNotificationSendDequeue(
    IN const Q_DEQUEUE_MSG *pDequeueMsg,
    IN DWORD cbResults,
    OUT Q_LIST_REPLY_MSG *pResults,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
XOnlinepPeerSubscribe(
    IN XUID qwUserID,
    IN WORD cSrcUserIDs,
    IN const ULONGLONG *rgqwSrcUserIDs,
    IN DWORD cbResults,
    OUT P_PEER_SUBSCRIBE_REPLY_MSG *pResults,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
XOnlinepPeerUnsubscribe(
    IN XUID qwUserID,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
XOnlinepSetUserSettings2(
    IN XUID qwUserId,
    IN WORD bTier,
    IN WORD dwUserFlags,
    IN const DWORD *rgPrivileges,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
XPresenceGetLocalSession(
    IN DWORD cbResults,
    OUT GET_SESSION_RESULTS *pResults
    );

XBOXAPI
DWORD
WINAPI
XPresenceGetPeerSession(
    IN XUID qwUserID,
    IN XUID qwHostUserID,
    IN DWORD cbResults,
    OUT GET_SESSION_RESULTS *pResults,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
XPresenceGetState(
    IN XUID UserXuid,
    OUT DWORD *pdwStateFlags,
    OUT XNKID *pSessionID
    );

XBOXAPI
DWORD
WINAPI
XPresenceSendAlives(
    IN DWORD cAlivesToSend,
    IN const P_ALIVE_2_MSG *pAlives,
    IN DWORD cbResults,
    OUT XPRESENCE_ALIVE_REPLY *pResults,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
XPresenceSendDeadUsers(
    IN DWORD cDeadUsersToSend,
    IN const P_DEAD_USER_MSG *pDeadUsers,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
XPresenceSetState(
    IN XUID UserXuid,
    IN DWORD dwStateFlags,
    IN XNKID sessionID,
    IN DWORD cbState,
    IN const BYTE *pbState
    );

XBOXAPI
DWORD
WINAPI
XPresenceUpdateStateFlags(
    IN XUID UserXuid,
    IN DWORD dwStateFlagsSet,
    IN DWORD dwStateFlagsClear
    );

XBOXAPI
HRESULT
WINAPI
XResolveName_GetContextSize(
    OUT DWORD *pcbContextSize,
    OUT DWORD *pcbRequestWireBuffer,
    OUT DWORD *pcbResponseWireBuffer
    );

XBOXAPI
HRESULT
WINAPI
XResolveName_Setup(
    IN const XRESOLVE_DOMAIN_STRING *pResolveString,
    IN DWORD cbResults,
    OUT XRESOLVE_NAME_RESPONSE *pResults,
    IN PVOID pvParentTask,
    IN PBYTE pbSubTask,
    IN DWORD cbSubTask,
    IN PBYTE pbRequestWireBuffer,
    IN DWORD cbRequestWireBuffer,
    IN PBYTE pbResponseWireBuffer,
    IN DWORD cbResponseWireBuffer
    );

XBOXAPI
DWORD
WINAPI
XSignatureCheckRevocation(
    IN DWORD dwNumContentTuples,
    IN const XSIGNATURE_CONTENT_TUPLE *pTuples,
    IN DWORD cbResults,
    OUT XSIGNATURE_CHECK_REVOCATION_RESPONSE *pResults,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
HRESULT
WINAPI
XSignatureVerify_GetContextSize(
    OUT DWORD *pcbContextSize,
    OUT DWORD *pcbRequestWireBuffer,
    OUT DWORD *pcbResponseWireBuffer
    );

XBOXAPI
HRESULT
WINAPI
XSignatureVerify_Setup(
    IN DWORD dwNumSignaturesToVerify,
    IN const XSIGNATURE_TO_VERIFY *pSignaturesToVerify,
    IN DWORD cbResults,
    OUT XSIGNATURE_VERIFY_RESPONSE *pResults,
    IN PVOID pvParentTask,
    IN PBYTE pbSubTask,
    IN DWORD cbSubTask,
    IN PBYTE pbRequestWireBuffer,
    IN DWORD cbRequestWireBuffer,
    IN PBYTE pbResponseWireBuffer,
    IN DWORD cbResponseWireBuffer
    );

XBOXAPI
HRESULT
WINAPI
XStorageDeleteWorker_GetContextSize(
    OUT DWORD *pcbContextSize,
    OUT DWORD *pcbRequestWireBuffer,
    OUT DWORD *pcbResponseWireBuffer
    );

XBOXAPI
HRESULT
WINAPI
XStorageDeleteWorker_Setup(
    IN XUID UserXuid,
    IN const XSTORAGE_ACCESS_TOKEN *pStorageAccessToken,
    IN const XSTORAGE_PATH_STRING *pStoragePathString,
    IN const XSTORAGE_ACCESS_TOKEN_READ *pStorageAccessTokenRead,
    IN PVOID pvParentTask,
    IN PBYTE pbSubTask,
    IN DWORD cbSubTask,
    IN PBYTE pbRequestWireBuffer,
    IN DWORD cbRequestWireBuffer,
    IN PBYTE pbResponseWireBuffer,
    IN DWORD cbResponseWireBuffer
    );

XBOXAPI
DWORD
WINAPI
XStorageDownloadToDirectoryInternal(
    IN DWORD dwUserIndex,
    IN const WCHAR *wszServerPath,
    IN const WCHAR *wszDisplayName,
    IN XCONTENTDEVICEID DeviceID,
    IN DWORD cbResults,
    OUT XSTORAGE_DOWNLOAD_TO_DIRECTORY_RESULTS_INTERNAL *pResults,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
HRESULT
WINAPI
XStorageDownloadWorker_GetContextSize(
    OUT DWORD *pcbContextSize,
    OUT DWORD *pcbRequestWireBuffer,
    OUT DWORD *pcbResponseWireBuffer
    );

XBOXAPI
HRESULT
WINAPI
XStorageDownloadWorker_Setup(
    IN XUID UserXuid,
    IN const XSTORAGE_ACCESS_TOKEN *pStorageAccessToken,
    IN const XSTORAGE_PATH_STRING *pStoragePathString,
    IN const XSTORAGE_ACCESS_TOKEN_READ *pStorageAccessTokenRead,
    IN DWORD dwRangeStart,
    IN DWORD dwRangeEnd,
    IN const FILETIME *pftLastModified,
    IN DWORD cbResults,
    OUT XSTORAGE_DOWNLOAD_RESPONSE *pResults,
    IN PVOID pvParentTask,
    IN PBYTE pbSubTask,
    IN DWORD cbSubTask,
    IN PBYTE pbRequestWireBuffer,
    IN DWORD cbRequestWireBuffer,
    IN PBYTE pbResponseWireBuffer,
    IN DWORD cbResponseWireBuffer
    );

XBOXAPI
HRESULT
WINAPI
XStorageEnumerateWorker_GetContextSize(
    OUT DWORD *pcbContextSize,
    OUT DWORD *pcbRequestWireBuffer,
    OUT DWORD *pcbResponseWireBuffer
    );

XBOXAPI
HRESULT
WINAPI
XStorageEnumerateWorker_Setup(
    IN XUID UserXuid,
    IN const XSTORAGE_ACCESS_TOKEN *pStorageAccessToken,
    IN const XSTORAGE_PATH_STRING *pStoragePathString,
    IN const XSTORAGE_ACCESS_TOKEN_READ *pStorageAccessTokenRead,
    IN DWORD dwStartingIndex,
    IN DWORD dwEndingIndex,
    IN DWORD cbResults,
    OUT XSTORAGE_ENUMERATE_RESULTS *pResults,
    IN PVOID pvParentTask,
    IN PBYTE pbSubTask,
    IN DWORD cbSubTask,
    IN PBYTE pbRequestWireBuffer,
    IN DWORD cbRequestWireBuffer,
    IN PBYTE pbResponseWireBuffer,
    IN DWORD cbResponseWireBuffer
    );

XBOXAPI
DWORD
WINAPI
XStorageUploadFromDirectoryInternal(
    IN DWORD dwUserIndex,
    IN const WCHAR *wszServerPath,
    IN const CHAR *szLocalPath,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
HRESULT
WINAPI
XStorageUploadWorker_GetContextSize(
    OUT DWORD *pcbContextSize,
    OUT DWORD *pcbRequestWireBuffer,
    OUT DWORD *pcbResponseWireBuffer
    );

XBOXAPI
HRESULT
WINAPI
XStorageUploadWorker_Setup(
    IN XUID UserXuid,
    IN const XSTORAGE_ACCESS_TOKEN *pStorageAccessToken,
    IN const XSTORAGE_PATH_STRING *pStoragePathString,
    IN const XSTORAGE_ACCESS_TOKEN_WRITE *pStorageAccessTokenWrite,
    IN BYTE bCompressionType,
    IN DWORD dwContentType,
    IN DWORD dwDigestSize,
    IN const BYTE *prgbDigest,
    IN DWORD dwLiveSignatureSize,
    IN const BYTE *prgbLiveSignature,
    IN DWORD dwInstallSize,
    IN WORD wAttributesSize,
    IN DWORD dwPackageSize,
    IN const BYTE *prgbAttributes,
    IN PVOID pvParentTask,
    IN PBYTE pbSubTask,
    IN DWORD cbSubTask,
    IN PBYTE pbRequestWireBuffer,
    IN DWORD cbRequestWireBuffer,
    IN PBYTE pbResponseWireBuffer,
    IN DWORD cbResponseWireBuffer
    );

XBOXAPI
DWORD
WINAPI
XStringLookup(
    IN DWORD dwTitleID,
    IN const CHAR *szLocale,
    IN DWORD dwNumStrings,
    IN const DWORD *pStringIDs,
    IN DWORD cbResults,
    OUT STRING_LOOKUP_RESPONSE *pResults,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
XUpdateDownload(
    IN DWORD dwTitleId,
    IN DWORD dwVersion,
    IN DWORD cbResults,
    OUT XUPDATE_DOWNLOAD_RESULTS *pResults,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
HRESULT
WINAPI
XUpdateGetReferral_GetContextSize(
    OUT DWORD *pcbContextSize,
    OUT DWORD *pcbRequestWireBuffer,
    OUT DWORD *pcbResponseWireBuffer
    );

XBOXAPI
HRESULT
WINAPI
XUpdateGetReferral_Setup(
    IN DWORD dwTitleId,
    IN DWORD dwVersion,
    IN DWORD cbResults,
    OUT XUPDATE_REFERRAL_RESPONSE *pResults,
    IN PVOID pvParentTask,
    IN PBYTE pbSubTask,
    IN DWORD cbSubTask,
    IN PBYTE pbRequestWireBuffer,
    IN DWORD cbRequestWireBuffer,
    IN PBYTE pbResponseWireBuffer,
    IN DWORD cbResponseWireBuffer
    );

XBOXAPI
DWORD
WINAPI
XUserAddAffiliate(
    IN ULONGLONG qwUserID,
    IN DWORD dwListFlags,
    IN DWORD dwTitleID,
    IN WORD cwAffiliates,
    IN const ULONGLONG *pqwAfilliateIDs,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
XUserEnumerateReceivedReviews(
    IN ULONGLONG qwTargetID,
    IN DWORD dwPageID,
    IN DWORD dwResultsPerPage,
    IN DWORD cbResults,
    OUT FB_ENUM_REVIEWS_RESPONSE *pResults,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
XUserEnumerateSentReviews(
    IN ULONGLONG qwSenderID,
    IN DWORD dwPageID,
    IN DWORD dwResultsPerPage,
    IN DWORD cbResults,
    OUT FB_ENUM_REVIEWS_RESPONSE *pResults,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
XUserFindUser(
    IN XUID qwUserID,
    IN XUID qwFindID,
    IN const CHAR *szSenderName,
    IN DWORD cbResults,
    OUT P_FIND_USER_REPLY_MSG *pResults,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
XUserGetAggregateReviews(
    IN ULONGLONG qwTargetID,
    IN DWORD cbResults,
    OUT FB_GET_AGG_REVIEWS_RESPONSE *pResults,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
XUserIsAffiliate(
    IN ULONGLONG qwUserID,
    IN ULONGLONG qwAffiliateID,
    IN DWORD cbResults,
    OUT P_IS_AFFILIATE_REPLY_MSG *pResults,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
XUserQueryAffiliate(
    IN ULONGLONG qwUserID,
    IN DWORD dwListFlags,
    IN DWORD cdwLimit,
    IN DWORD dwOnlineTitleID,
    IN DWORD cbResults,
    OUT P_QUERY_AFFILIATES_REPLY_MSG *pResults,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
XUserSubmitComplaint(
    IN ULONGLONG qwSenderID,
    IN ULONGLONG qwTargetID,
    IN DWORD dwTitleID,
    IN DWORD dwType,
    IN ULONGLONG qwContext,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
XUserSubmitPlayerReview(
    IN ULONGLONG qwSenderID,
    IN ULONGLONG qwTargetID,
    IN DWORD dwTitleID,
    IN DWORD dwType,
    IN ULONGLONG qwContext,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
_XAccountAcceptTermsOfUse(
    IN XUID qwUserId,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
_XAccountAcknowledgeDowngrade(
    IN ULONGLONG qwUserId,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
_XAccountAddPaymentInstrument(
    IN XUID qwUserId,
    IN ADDRESS_INFO addressInfo,
    IN PHONE_INFO phoneInfo,
    IN BYTE bPaymentTypeId,
    IN CREDIT_CARD_INFO creditCardInfo,
    IN DIRECT_DEBIT_INFO directDebitInfo,
    IN DWORD cbResults,
    OUT ADD_PAYMENT_INSTRUMENT_RESPONSE *pResults,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
_XAccountChangeGamertag(
    IN DWORD dwUserIndex,
    IN const WCHAR *wszGamertag,
    IN DWORD cbResults,
    OUT ACCOUNT_CHANGE_GAMERTAG_RESPONSE *pResults,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
_XAccountChangeSubscriptionPaymentInstrument(
    IN XUID qwUserId,
    IN const WCHAR *wszInstanceId,
    IN const WCHAR *wszPaymentInstrumentId,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
_XAccountCreateLiveAccount(
    IN ULONGLONG qwOfflineXuid,
    IN const WCHAR *wszFirstName,
    IN const WCHAR *wszLastName,
    IN const WCHAR *wszGamertag,
    IN const BYTE *abSignedUserPassportPuid,
    IN const BYTE *abSignedOwnerPassportPuid,
    IN ULONGLONG qwOfferId,
    IN const WCHAR *wszBillingToken,
    IN FILETIME ftBirthdate,
    IN const WCHAR *wszEmail,
    IN WORD wLanguageId,
    IN BYTE bCountryId,
    IN DWORD dwParentalControlGroupId,
    IN BYTE bMsftOptIn,
    IN BYTE bPartnerOptIn,
    IN ADDRESS_INFO address,
    IN PHONE_INFO phone,
    IN BYTE bPaymentTypeId,
    IN CREDIT_CARD_INFO creditCard,
    IN DIRECT_DEBIT_INFO directDebit,
    IN WORD wReservedBytesLength,
    IN const BYTE *pbReservedBytes,
    IN DWORD cbResults,
    OUT CREATE_LIVE_ACCOUNT_RESPONSE *pResults,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
_XAccountCreateLiveAccountOld(
    IN const WCHAR *wszFirstName,
    IN const WCHAR *wszLastName,
    IN const WCHAR *wszGamertag,
    IN ULONGLONG qwUserPassportPuid,
    IN ULONGLONG qwOwnerPassportPuid,
    IN ULONGLONG qwOfferId,
    IN const WCHAR *wszBillingToken,
    IN FILETIME ftBirthdate,
    IN const WCHAR *wszEmail,
    IN WORD wLanguageId,
    IN BYTE bCountryId,
    IN DWORD dwParentalControlGroupId,
    IN BYTE bMsftOptIn,
    IN BYTE bPartnerOptIn,
    IN ADDRESS_INFO address,
    IN PHONE_INFO phone,
    IN BYTE bPaymentTypeId,
    IN CREDIT_CARD_INFO creditCard,
    IN DIRECT_DEBIT_INFO directDebit,
    IN DWORD cbResults,
    OUT CREATE_LIVE_ACCOUNT_RESPONSE *pResults,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
_XAccountGetAccountInfo(
    IN XUID qwUserId,
    IN DWORD cbResults,
    OUT GET_ACCOUNT_INFO_RESPONSE *pResults,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
_XAccountGetAccountInfoFromPassport(
    IN const PASSPORT_SESSION_TOKEN *pSessionToken,
    IN DWORD cbResults,
    OUT GET_ACCOUNT_INFO_RESPONSE *pResults,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
_XAccountGetLinkedGamertag(
    IN const BYTE *pSignedPuid,
    IN DWORD cbResults,
    OUT GET_LINKED_GAMERTAG_RESPONSE *pResults,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
_XAccountGetPaymentInstruments(
    IN XUID qwUserId,
    IN DWORD cbResults,
    OUT GET_PAYMENT_INSTRUMENTS_RESPONSE *pResults,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
_XAccountGetPointsBalance(
    IN XUID qwUserId,
    IN DWORD cbResults,
    OUT GET_POINTS_BALANCE_RESPONSE *pResults,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
_XAccountGetPostalCode(
    IN BYTE bCountryId,
    IN const WCHAR *wszPostalCode,
    IN DWORD cbResults,
    OUT GET_POSTAL_CODE_RESPONSE *pResults,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
_XAccountGetUserInfo(
    IN DWORD dwUserIndex,
    IN DWORD cbResults,
    OUT GET_USER_INFO_RESPONSE *pResults,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
_XAccountGetUserSubscriptionDetails(
    IN XUID qwUserId,
    IN ULONGLONG qwOfferId,
    IN const WCHAR *wszInstanceId,
    IN DWORD cbResults,
    OUT GET_USER_SUBSCRIPTION_DETAILS_RESPONSE *pResults,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
_XAccountGetUserType(
    IN const WCHAR *wszGamertag,
    IN DWORD cbResults,
    OUT ACCOUNT_GET_USER_TYPE_RESPONSE *pResults,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
_XAccountLinkXbox1Account(
    IN const WCHAR *wszGamertag,
    IN const PASSPORT_SESSION_TOKEN *pUserSessionToken,
    IN const PASSPORT_SESSION_TOKEN *pParentSessionToken,
    IN PHONE_INFO phoneInfo,
    IN const WCHAR *wszPostalCode,
    IN const WCHAR *wszAccountHolderName,
    IN const WCHAR *wszAccountNumber,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
_XAccountMigrateXbox1User(
    IN const PASSPORT_SESSION_TOKEN *pUserSessionToken,
    IN const PASSPORT_SESSION_TOKEN *pParentSessionToken,
    IN ULONGLONG qwOfflineXuid,
    IN const CHAR *szUserPassportMemberName,
    IN WORD wLanguageId,
    IN WORD wReservedBytesLength,
    IN const BYTE *pbReservedBytes,
    IN DWORD cbResults,
    OUT MIGRATE_XBOX1_USER_RESPONSE *pResults,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
_XAccountMigrateXboxComUser(
    IN const PASSPORT_SESSION_TOKEN *pUserSessionToken,
    IN ULONGLONG qwOfflineXuid,
    IN BYTE bCountryId,
    IN WORD wLanguageId,
    IN ULONGLONG qwOfferId,
    IN const WCHAR *wszBillingToken,
    IN const WCHAR *wszFirstName,
    IN const WCHAR *wszLastName,
    IN const WCHAR *wszEmail,
    IN ADDRESS_INFO address,
    IN PHONE_INFO phone,
    IN BYTE bPaymentTypeId,
    IN CREDIT_CARD_INFO creditCard,
    IN DIRECT_DEBIT_INFO directDebit,
    IN DWORD cbResults,
    OUT MIGRATE_XBOX_COM_USER_RESPONSE *pResults,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
_XAccountQuery(
    IN DWORD dwRequestType,
    IN WORD wRequestBytesLength,
    IN const BYTE *pbRequestBytes,
    IN DWORD cbResults,
    OUT ACCOUNT_QUERY_RESPONSE *pResults,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
_XAccountRecoverAccount(
    IN const BYTE *pSignedPuid,
    IN DWORD cbResults,
    OUT RECOVER_ACCOUNT_RESPONSE *pResults,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
_XAccountRemovePaymentInstrument(
    IN XUID qwUserId,
    IN const WCHAR *wszPaymentInstrumentId,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
_XAccountReserveGamertag(
    IN BYTE bCountryId,
    IN WORD wMaxSuggestedNames,
    IN const WCHAR *wszGamertag,
    IN DWORD cbResults,
    OUT ACCOUNT_RESERVE_GAMERTAG_RESPONSE *pResults,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
_XAccountSetAccountInfo(
    IN XUID qwUserId,
    IN const WCHAR *wszFirstName,
    IN const WCHAR *wszLastName,
    IN FILETIME ftBirthdate,
    IN const WCHAR *wszEmail,
    IN ADDRESS_INFO address,
    IN PHONE_INFO phone,
    IN WORD wLanguageId,
    IN BYTE bMsftOptIn,
    IN BYTE bParterOptIn,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
_XAccountSetStatus(
    IN XUID qwUserId,
    IN DWORD dwNewTermsOfService,
    IN DWORD dwForceNameChangeRequired,
    IN FILETIME ftSuspendedUntil,
    IN WORD wTotalDaysSuspended,
    IN FILETIME ftVoiceBannedUntil,
    IN WORD wTotalDaysVoiceBanned,
    IN DWORD dwBillingHr,
    IN DWORD dwResetPassword,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
_XAccountTroubleshoot(
    IN ULONGLONG qwUserId,
    IN WORD wReservedBytesLength,
    IN const BYTE *pbReservedBytes,
    IN DWORD cbResults,
    OUT ACCOUNT_TROUBLESHOOT_RESPONSE *pResults,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
_XAccountUpdateParentalControls(
    IN XUID qwUserId,
    IN const DWORD *rgGrantPrivileges,
    IN const DWORD *rgRestrictPrivileges,
    IN const WCHAR *wszSource,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
_XAccountUpdatePaymentInstrument(
    IN XUID qwUserId,
    IN const WCHAR *wszPaymentInstrumentId,
    IN ADDRESS_INFO addressInfo,
    IN PHONE_INFO phoneInfo,
    IN CREDIT_CARD_INFO creditCardInfo,
    IN DIRECT_DEBIT_INFO directDebitInfo,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
_XAccountVerifyBillingInfo(
    IN const WCHAR *wszGamertag,
    IN PHONE_INFO phone,
    IN const WCHAR *wszPostalCode,
    IN const WCHAR *wszAccountHolderName,
    IN const WCHAR *wszAccountNumber,
    IN DWORD cbResults,
    OUT ACCOUNT_VERIFY_BILLING_INFO_RESPONSE *pResults,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
_XAccountVerifyBillingToken(
    IN BYTE bCountryId,
    IN const WCHAR *wszBillingToken,
    IN DWORD cbResults,
    OUT VERIFY_BILLING_TOKEN_RESPONSE *pResults,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
_XAccountVerifyParentCreditCard(
    IN const PASSPORT_SESSION_TOKEN *pParentSessionToken,
    IN const CHAR *szParentPassportMemberName,
    IN WORD wLanguageId,
    IN BYTE bCountryId,
    IN const WCHAR *wszFirstName,
    IN const WCHAR *wszLastName,
    IN const WCHAR *wszEmail,
    IN ADDRESS_INFO address,
    IN PHONE_INFO phone,
    IN CREDIT_CARD_INFO creditCardInfo,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
_XBannerGetHotList(
    IN ULONGLONG qwUserId,
    IN DWORD dwLangId,
    IN DWORD dwStartingIndex,
    IN DWORD dwMaxResults,
    IN DWORD cbResults,
    OUT BANNER_HOTLIST_RESULT *pResults,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
_XBannerGetList(
    IN ULONGLONG qwUserId,
    IN DWORD dwLangId,
    IN DWORD cbResults,
    OUT BANNER_LIST_RESULT *pResults,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
_XOfferingContentAvailable(
    IN XUID qwUserId,
    IN BYTE bTier,
    IN DWORD dwTitleId,
    IN DWORD cbResults,
    OUT CONTENT_AVAILABLE_RESPONSE *pResults,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
_XOfferingContentDetails(
    IN XUID qwUserId,
    IN WORD wLanguageId,
    IN ULONGLONG qwOfferID,
    IN DWORD dwPaymentType,
    IN BYTE bRatingSystem,
    IN DWORD cbResults,
    OUT CONTENT_DETAILS_RESPONSE *pResults,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
_XOfferingContentEnumerate(
    IN XUID qwUserId,
    IN WORD wLanguageId,
    IN WORD wGameRating,
    IN DWORD dwOfferType,
    IN DWORD dwPaymentType,
    IN BYTE bTier,
    IN DWORD dwTitleId,
    IN DWORD dwTitleCategories,
    IN BYTE bRequestFlags,
    IN DWORD dwStartingIndex,
    IN DWORD dwMaxResults,
    IN DWORD cbResults,
    OUT CONTENT_ENUMERATE_RESPONSE *pResults,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
_XOfferingEnumerateGenres(
    IN XUID UserXuid,
    IN WORD wLanguageId,
    IN DWORD dwStartingIndex,
    IN DWORD dwMaxResults,
    IN WORD wGameRating,
    IN BYTE bTierRequired,
    IN DWORD dwOfferType,
    IN DWORD dwParentGenreId,
    IN DWORD cbResults,
    OUT ENUMERATE_GENRES_RESPONSE *pResults,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
_XOfferingEnumerateTitlesByFilter(
    IN XUID qwUserId,
    IN WORD wLanguageId,
    IN DWORD dwStartingIndex,
    IN DWORD dwMaxResults,
    IN WORD wGameRating,
    IN BYTE bTierRequired,
    IN DWORD dwGenreId,
    IN DWORD dwOfferType,
    IN WORD wRequestFlags,
    IN DWORD cbResults,
    OUT ENUMERATE_TITLES_BY_FILTER_RESPONSE *pResults,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
_XOfferingGetTitleDetails(
    IN XUID qwUserId,
    IN DWORD dwTitleId,
    IN BYTE bCountryId,
    IN WORD wLanguageId,
    IN BYTE bTierRequired,
    IN DWORD cbResults,
    OUT TITLE_DETAILS_RESPONSE *pResults,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
_XOfferingInternalUpdateAccessTimes(
    IN XUID qwUserId,
    IN DWORD dwTitleId,
    IN DWORD dwTitleCategories,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
_XOfferingPurchase(
    IN XUID qwUserId,
    IN WORD wLanguageId,
    IN BYTE bUserTier,
    IN ULONGLONG qwOfferID,
    IN DWORD dwPaymentType,
    IN const WCHAR *wszPaymentInstrumentId,
    IN const WCHAR *wszToken,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
_XOfferingPurchaseGamertag(
    IN XUID qwUserId,
    IN WORD wLanguageId,
    IN BYTE bUserTier,
    IN ULONGLONG qwOfferID,
    IN DWORD dwPaymentType,
    IN const WCHAR *wszToken,
    IN const WCHAR *wszGamertag,
    IN DWORD cbResults,
    OUT OFFER_PURCHASE_GAMERTAG_RESPONSE *pResults,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
_XOfferingSubscriptionDetails(
    IN XUID qwUserId,
    IN BYTE bCountryId,
    IN WORD wLanguageId,
    IN ULONGLONG qwOfferID,
    IN DWORD dwPaymentType,
    IN BYTE bUserTier,
    IN BYTE bRatingSystem,
    IN DWORD cbResults,
    OUT SUBSCRIPTION_DETAILS_RESPONSE *pResults,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
_XOfferingSubscriptionEnumerate(
    IN XUID qwUserId,
    IN BYTE bUserTier,
    IN BYTE bCountryId,
    IN WORD wLanguageId,
    IN WORD wGameRating,
    IN DWORD dwOfferType,
    IN DWORD dwPaymentType,
    IN DWORD dwTitleId,
    IN DWORD dwTitleCategories,
    IN WORD wRequestFlags,
    IN DWORD dwStartingIndex,
    IN DWORD dwMaxResults,
    IN DWORD cbResults,
    OUT SUBSCRIPTION_ENUMERATE_RESPONSE *pResults,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
_XOnlineArbitrationRegister(
    IN WORD wFlags,
    IN ULONGLONG qwSessionId,
    IN ULONGLONG qwSessionNonce,
    IN WORD wMaxSessionSeconds,
    IN DWORD cbResults,
    OUT XARB_REGISTER_REPLY *pResults,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
_XOnlineArbitrationReportResult(
    IN WORD wFlags,
    IN ULONGLONG qwSessionID,
    IN ULONGLONG qwSessionNonce,
    IN BYTE bReportLostMachines,
    IN const XARB_REPORT_LOST_MACHINES *pLostMachines,
    IN BYTE cSuspiciousInfo,
    IN const XARB_REPORT_SUSPICIOUS_INFO *pSuspiciousInfo,
    IN BYTE bSubmitStatsBundle,
    IN const XARB_REPORT_STATS_BUNDLE *pStatsBundle,
    IN BYTE bSubmitCompsBundle,
    IN const XARB_REPORT_BYTE_BUNDLE *pCompsBundle,
    IN DWORD cbMinRequest,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
_XOnlineArbitrationTimeExtend(
    IN ULONGLONG qwSessionID,
    IN ULONGLONG qwSessionNonce,
    IN WORD wMaxSessionSecondsFromNow,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
_XOnlineStatsEnumerateByRank(
    IN DWORD dwTitleId,
    IN ULONGLONG qwRank,
    IN DWORD dwPageSize,
    IN DWORD dwNumSpecs,
    IN const XONLINE_STATS_SPEC *pSpecs,
    IN DWORD cbResults,
    OUT XONLINE_STATS_ENUM_RESULTS *pResults,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
_XOnlineStatsEnumerateByRating(
    IN DWORD dwTitleId,
    IN LONGLONG i64Rating,
    IN DWORD dwPageSize,
    IN DWORD dwNumSpecs,
    IN const XONLINE_STATS_SPEC *pSpecs,
    IN DWORD cbResults,
    OUT XONLINE_STATS_ENUM_RESULTS *pResults,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
_XOnlineStatsEnumerateByXuid(
    IN DWORD dwTitleId,
    IN XUID Xuid,
    IN DWORD dwPageSize,
    IN DWORD dwNumSpecs,
    IN const XONLINE_STATS_SPEC *pSpecs,
    IN DWORD cbResults,
    OUT XONLINE_STATS_ENUM_RESULTS *pResults,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
_XOnlineStatsPost(
    IN WORD wNumProcs,
    IN const XSTAT_PROC *pProcs,
    IN DWORD cbMinRequest,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
_XOnlineStatsRead(
    IN DWORD dwTitleId,
    IN DWORD dwNumXuids,
    IN const XUID *pXuids,
    IN DWORD dwNumSpecs,
    IN const XONLINE_STATS_SPEC *pSpecs,
    IN DWORD cbResults,
    OUT XONLINE_STATS_READ_RESULTS *pResults,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
_XOnlineStatsReset(
    IN DWORD dwTitleId,
    IN ULONGLONG qwUserId,
    IN DWORD dwLeaderBoardId,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
_XPassportChangePasswordInternal(
    IN const PASSPORT_SESSION_TOKEN *pSessionToken,
    IN const CHAR *szPassportMemberName,
    IN WORD wEncryptedPasswordLength,
    IN const BYTE *pbEncryptedPassword,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
_XPassportCreateInternal(
    IN const CHAR *szPassportMemberName,
    IN const WCHAR *szSecretQuestion,
    IN WORD wEncryptedPasswordLength,
    IN const BYTE *pbEncryptedPassword,
    IN DWORD cbResults,
    OUT PASSPORT_SESSION_TOKEN *pResults,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
_XPassportGetEncryptedProxyParameters(
    IN DWORD dwDummy,
    IN DWORD cbResults,
    OUT PASSPORT_ENCRYPTED_PROXY_PARAMETERS *pResults,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
_XPassportGetMemberName(
    IN DWORD dwUserIndex,
    IN DWORD cbResults,
    OUT PASSPORT_GET_MEMBER_NAME_RESPONSE *pResults,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
_XPassportGetSecretQuestions(
    IN WORD wCountryId,
    IN WORD wLanguageId,
    IN DWORD cbResults,
    OUT PASSPORT_GET_SECRET_QUESTION_RESPONSE *pResults,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
_XPassportGetUserData(
    IN const PASSPORT_SESSION_TOKEN *pSessionToken,
    IN DWORD cbResults,
    OUT PASSPORT_GET_USER_DATA_RESPONSE *pResults,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
_XPassportLoginInternal(
    IN const CHAR *szPassportMemberName,
    IN WORD wEncryptedSessionKeyLength,
    IN const BYTE *pbencryptedSessionKey,
    IN WORD wEncryptedPasswordLength,
    IN const BYTE *pbEncryptedPassword,
    IN WORD wEncryptedTokenRequestLength,
    IN const BYTE *pbEncryptedTokenRequest,
    IN DWORD cbResults,
    OUT PASSPORT_SESSION_TOKEN *pResults,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
_XProfileClearTitle(
    IN XUID qwUserId,
    IN DWORD dwTitleId,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
_XProfileEnumAchievements(
    IN DWORD dwTitleId,
    IN XUID qwUserId,
    IN ULONGLONG qwForPuid,
    IN WORD wLocaleId,
    IN WORD wStartingIndex,
    IN WORD wMaxAchievements,
    IN DWORD cbResults,
    OUT XPROFILE_ENUM_ACHIEVEMENTS_RESULT *pResults,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
_XProfileEnumTitles(
    IN XUID qwUserId,
    IN XUID qwForUserId,
    IN WORD wLocaleId,
    IN WORD wStartingIndex,
    IN WORD wMaxTitles,
    IN DWORD cbResults,
    OUT XPROFILE_ENUM_TITLES_RESULT *pResults,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
_XProfileReadOnlineSettings(
    IN XUID qwUserId,
    IN WORD wForUserIdsLen,
    IN const ULONGLONG *pqwUserIds,
    IN WORD wSettingIdsLen,
    IN const DWORD *pdwSettingIds,
    IN DWORD cbResults,
    OUT XPROFILE_SETTING_READ_RESULT *pResults,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
_XProfileSyncAchievements(
    IN DWORD dwTitleId,
    IN XUID qwUserId,
    IN FILETIME ftVersion,
    IN WORD wLocaleId,
    IN WORD wStartingIndex,
    IN WORD wAchievementCount,
    IN const XPROFILE_ACHIEVEMENT_SYNC_REQUEST *pAchievements,
    IN DWORD cbResults,
    OUT XPROFILE_SYNC_ACHIEVEMENTS_RESULT *pResults,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
_XProfileSyncOnlineSettings(
    IN DWORD dwTitleId,
    IN XUID qwUserId,
    IN FILETIME ftVersion,
    IN WORD wStartingIndex,
    IN WORD wSettingsLen,
    IN const XUSER_ONLINE_PROFILE_SETTING *pSettings,
    IN DWORD cbMinRequest,
    IN DWORD cbResults,
    OUT XPROFILE_SETTING_SYNC_RESULT *pResults,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );

XBOXAPI
DWORD
WINAPI
_XProfileSyncTitles(
    IN XUID qwUserId,
    IN WORD wLocaleId,
    IN WORD wStartingIndex,
    IN FILETIME ftLastSync,
    IN WORD wNumTitles,
    IN const XPROFILE_TITLE *pTitles,
    IN DWORD cbResults,
    OUT XPROFILE_SYNC_TITLES_RESULT *pResults,
    IN OUT OPTIONAL XOVERLAPPED *pXOverlapped
    );



//
// Statistics
//

#define XUSER_STATS_SYSTEM_ATTRIBUTE_MASK       0x8000
#define XUSER_STATS_RANK                        ((WORD)0xFFFF)
#define XUSER_STATS_RATING                      ((WORD)0xFFFE)
#define XUSER_STATS_GAMERTAG                    ((WORD)0xFFFD)

#define XONLINE_STAT_COMPTYPE_EQUAL             1 // if the current stored stat value equals the specified value
#define XONLINE_STAT_COMPTYPE_GREATER           2 // if the current stored stat value is greater than the specified value
#define XONLINE_STAT_COMPTYPE_GREATER_OR_EQUAL  3 // if the current stored stat value is greater than or equal to the specified value
#define XONLINE_STAT_COMPTYPE_LESS              4 // if the current stored stat value is less than the specified value
#define XONLINE_STAT_COMPTYPE_LESS_OR_EQUAL     5 // if the current stored stat value is less than or equal to the specified value
#define XONLINE_STAT_COMPTYPE_EXISTS            6 // if the current stored stat value exists (specified value is ignored)
#define XONLINE_STAT_COMPTYPE_NOT_EXISTS        7 // if the current stored stat value does not exist (specified value is ignored)
#define XONLINE_STAT_COMPTYPE_NOT_EQUAL         8 // if the current stored stat value does not equal the specified value

#define XONLINE_STAT_PROCID_REPLACE             0x8001 // use XONLINE_STAT_UPDATE structure
#define XONLINE_STAT_PROCID_ADD                 0x8003 // use XONLINE_STAT_UPDATE structure
#define XONLINE_STAT_PROCID_CONDITIONAL         0x8007 // use XONLINE_STAT_CONDITIONAL structure
#define XONLINE_STAT_PROCID_MIN                 0x8009
#define XONLINE_STAT_PROCID_MAX                 0x800B
#define XONLINE_STAT_PROCID_MUSIGMA             0x800D // use XONLINE_STAT_CONDITIONAL structure

// Internal helper functions

DWORD XOnlinepStatsPostMinRequestSize(WORD wNumProcs, const XSTAT_PROC *pProcs);

DWORD XOnlinepArbReportMinRequestSize(
    int                             bReportLostMachines,
    XARB_REPORT_LOST_MACHINES       *pLostMachines,
    int                             cSuspiciousInfo,
    XARB_REPORT_SUSPICIOUS_INFO     *pSuspiciousInfo,
    int                             bSubmitStatsBundle,
    XARB_REPORT_STATS_BUNDLE        *pStatsBundle,
    int                             bSubmitCompsBundle,
    XARB_REPORT_BYTE_BUNDLE         *pCompsBundle);


//
// Competitions
//
//
// Attribute IDs
//
#define XONLINE_QUERY_ENTITY_ID                   0x80000000
#define XONLINE_QUERY_OWNER_PUID                  0x80000001

#define XONLINE_COMP_ATTR_ID                      0x80010000
#define XONLINE_COMP_ATTR_REG_OPEN                0x80010001
#define XONLINE_COMP_ATTR_REG_CLOSE               0x80010002
#define XONLINE_COMP_ATTR_COMP_START              0x80010003
#define XONLINE_COMP_ATTR_COMP_CLEANUP            0x80010004
#define XONLINE_COMP_ATTR_COMP_CLEANUP_DAYS       0x80010004
#define XONLINE_COMP_ATTR_ROUND_FREQUENCY         0x80010005
#define XONLINE_COMP_ATTR_ROUND_INTERVAL          0x80010006
#define XONLINE_COMP_ATTR_ROUND_DAY_MASK          0x80010007
#define XONLINE_COMP_ATTR_ROUNDS                  0x80010008
#define XONLINE_COMP_ATTR_CURRENT_ROUND           0x80010009
#define XONLINE_COMP_ATTR_CURRENT_ROUND_START     0x8001000A
#define XONLINE_COMP_ATTR_CURRENT_ROUND_END       0x8001000B
#define XONLINE_COMP_ATTR_ROUND_DURATION_MIN      0x8001000B
#define XONLINE_COMP_ATTR_ROUND_ONE_START         0x8001000C
#define XONLINE_COMP_ATTR_ROUND_ONE_END           0x8001000D
#define XONLINE_COMP_ATTR_AUTOPROGRESS_DEADLINE   0x8001000F
#define XONLINE_COMP_ATTR_IS_TEAM_COMP            0x80010010
#define XONLINE_COMP_ATTR_TEAM_SIZE               0x80010011
#define XONLINE_COMP_ATTR_MAX_PUBLIC_SLOTS        0x80010012
#define XONLINE_COMP_ATTR_MAX_PRIVATE_SLOTS       0x80010013
#define XONLINE_COMP_ATTR_MIN_SLOTS               0x80010014
#define XONLINE_COMP_ATTR_BYES                    0x80010016
#define XONLINE_COMP_ATTR_BYES_GRANTED            0x80010017
#define XONLINE_COMP_ATTR_PUBLIC_ENTRANTS         0x80010018
#define XONLINE_COMP_ATTR_PRIVATE_ENTRANTS        0x80010019
#define XONLINE_COMP_ATTR_REMINDER_MIN            0x8001001A
#define XONLINE_COMP_ATTR_PLAY_BEFORE_MIN         0x8001001B
#define XONLINE_COMP_ATTR_PLAY_AFTER_MIN          0x8001001C
#define XONLINE_COMP_ATTR_STATUS                  0x8001001D
#define XONLINE_COMP_ATTR_ROUND0_LEADERBOARD_ID   0x80010020
#define XONLINE_COMP_ATTR_DEBUG_ADVANCE_TIME      0x80010023

#define XONLINE_COMP_ATTR_NAME                    0x8011000E

#define XONLINE_COMP_ATTR_RESULTS                 0x80210000


#define XONLINE_COMP_ATTR_ENTRANT_PUID            0x80020000
#define XONLINE_COMP_ATTR_ENTRANT_STATUS          0x80020001
#define XONLINE_COMP_ATTR_ENTRANT_TRUST           0x80020002
#define XONLINE_COMP_ATTR_ENTRANT_CURRENT_ROUND   0x80020003
#define XONLINE_COMP_ATTR_ENTRANT_PRIVATE_SLOT    0x80020004
#define XONLINE_COMP_ATTR_ENTRANT_SEED            0x80020005
#define XONLINE_COMP_ATTR_ENTRANT_ELIMINATED      0x80020006
#define XONLINE_COMP_ATTR_ENTRANT_CURRENT_EVENT   0x80020007
#define XONLINE_COMP_ATTR_ENTRANT_CURRENT_START   0x80020008
#define XONLINE_COMP_ATTR_ENTRANT_COMP_SORT       0x80020009
#define XONLINE_COMP_ATTR_ENTRANT_CURRENT_INDEX   0x8002000a
#define XONLINE_COMP_ATTR_ENTRANT_HRESULT         0x8002000b
#define XONLINE_COMP_ATTR_ENTRANT_SCORE           0x8002000c


#define XONLINE_COMP_ATTR_EVENT_ENTITY_ID         0x80030000
#define XONLINE_COMP_ATTR_EVENT_TOPOLOGY_ID       0x80030001
#define XONLINE_COMP_ATTR_EVENT_ROUND             0x80030002
#define XONLINE_COMP_ATTR_EVENT_START             0x80030003
#define XONLINE_COMP_ATTR_EVENT_NEXT_ENTITY       0x80030006
#define XONLINE_COMP_ATTR_EVENT_NEXT_START        0x80030007
#define XONLINE_COMP_ATTR_EVENT_P1                0x80030008
#define XONLINE_COMP_ATTR_EVENT_P1_GAMERTAG       0x81130008
#define XONLINE_COMP_ATTR_EVENT_P1_CHECKIN        0x80030009
#define XONLINE_COMP_ATTR_EVENT_P1_TRUST          0x8023000A
#define XONLINE_COMP_ATTR_EVENT_P2                0x8003000B
#define XONLINE_COMP_ATTR_EVENT_P2_GAMERTAG       0x8113000B
#define XONLINE_COMP_ATTR_EVENT_P2_CHECKIN        0x8003000C
#define XONLINE_COMP_ATTR_EVENT_P2_TRUST          0x8023000D
#define XONLINE_COMP_ATTR_EVENT_WINNER            0x8003000E
#define XONLINE_COMP_ATTR_EVENT_LOSER             0x8003000F
#define XONLINE_COMP_ATTR_EVENT_MIN               0x80030010
#define XONLINE_COMP_ATTR_EVENT_MAX               0x80030011


#define XONLINE_COMP_ATTR_BRACKET_ID              0x80040001
#define XONLINE_COMP_ATTR_BRACKET_SLOTS           0x80040002
#define XONLINE_COMP_ATTR_BRACKET_ENTRANTS        0x80040003
#define XONLINE_COMP_ATTR_BRACKET_BYES            0x80040004
#define XONLINE_COMP_ATTR_BRACKET_BYES_GRANTED    0x80040005
#define XONLINE_COMP_ATTR_BRACKET_ROUND_START     0x80040006
#define XONLINE_COMP_ATTR_BRACKET_END             0x80040008
#define XONLINE_COMP_ATTR_BRACKET_START           0x80040009
#define XONLINE_COMP_ATTR_BRACKET_STATUS          0x8004000A
#define XONLINE_COMP_ATTR_BRACKET_APD             0x8004000B
#define XONLINE_COMP_ATTR_BRACKET_LEADERBOARD     0x8004000C

#define XONLINE_COMP_ATTR_BRACKET_MIN_ROUND       0x820400F0
#define XONLINE_COMP_ATTR_BRACKET_MAX_ROUND       0x820400F1


//
// Competition status codes
//
#define XONLINE_COMP_STATUS_PRE_INIT              0
#define XONLINE_COMP_STATUS_ACTIVE                1
#define XONLINE_COMP_STATUS_COMPLETE              2
#define XONLINE_COMP_STATUS_CANCELED              0xFFFFFFFF

//
// Entrant status codes
//
#define XONLINE_COMP_STATUS_ENTRANT_REGISTERED    0
#define XONLINE_COMP_STATUS_ENTRANT_PLAYING       1
#define XONLINE_COMP_STATUS_ENTRANT_FORFEIT       2
#define XONLINE_COMP_STATUS_ENTRANT_PASS          4
#define XONLINE_COMP_STATUS_ENTRANT_FINAL         5
#define XONLINE_COMP_STATUS_ENTRANT_ELIMINATED    0xFFFFFFFF

//
// Multilevel constants
//

// Use this value for the Entity ID when calling XOnlineCompeitionSubmitResults for a multi-level competition
#define XONLINE_COMP_MULTILEVEL_ENTITY_ID         0xffffffff

//
// Multilevel bracket status Codes
//
#define XONLINE_COMP_STATUS_BRACKET_PRE_INIT      0
#define XONLINE_COMP_STATUS_BRACKET_CHECKIN       1
#define XONLINE_COMP_STATUS_BRACKET_IN_PROGRESS 2
#define XONLINE_COMP_STATUS_BRACKET_COMPLETE      3
#define XONLINE_COMP_STATUS_BRACKET_FINAL         4

//
// Multilevel entrant procs
//
#define XONLINE_COMP_ML_ENTRANTS_SEARCH_ONE      0x10001
#define XONLINE_COMP_ML_ENTRANTS_SEARCH_PUID     0x10001
#define XONLINE_COMP_ML_ENTRANTS_SEARCH_STATUS   0x10002

//
// Multilevel update procs
//
#define XONLINE_COMP_ML_ENTRANTS_UPDATE_ROUND    0x10001
#define XONLINE_COMP_ML_ENTRANTS_UPDATE_STATUS   0x10002

//
// Multilevel bracket procs
//
#define XONLINE_COMP_ML_BRACKET_SEARCH_ROUND     0x10001
#define XONLINE_COMP_ML_BRACKET_UPDATEID_SLOT_INFO 0x10001

//
// Action IDs
//
#define XONLINE_COMP_ACTION_JOIN                  1
#define XONLINE_COMP_ACTION_JOIN_PRIVATE          2
#define XONLINE_COMP_ACTION_WITHDRAW              3
#define XONLINE_COMP_ACTION_CHECKIN               4
#define XONLINE_COMP_ACTION_REQUEST_BYE           5
#define XONLINE_COMP_ACTION_REQUEST_PASS          6
#define XONLINE_COMP_ACTION_SUBMIT_RESULTS        7
#define XONLINE_COMP_ACTION_FORFEIT               8
#define XONLINE_COMP_ACTION_CANCEL                9
#define XONLINE_COMP_ACTION_EJECT                 10
#define XONLINE_COMP_ACTION_DEBUG_ADVANCE_TIME    99


//
// Limits
//
#define XONLINE_COMP_MAX_FREQUENCY              60
#define XONLINE_COMP_MIN_DURATION_MINS          5
#define XONLINE_COMP_MIN_JOB_DELAY              1
#define XONLINE_COMP_CHECKIN_WIN_SECS           5 * 60
#define XONLINE_COMP_MIN_CLEANUP_DAYS           1
#define XONLINE_COMP_MAX_CLEANUP_DAYS           365
#define XONLINE_COMP_DEFAULT_CLEANUP_DAYS       5


//
// Defined types of competition intervals
//
typedef enum
{
    XONLINE_COMP_INTERVAL_MINUTE = 2,
    XONLINE_COMP_INTERVAL_HOUR = 3,
    XONLINE_COMP_INTERVAL_DAILY = 4,
    XONLINE_COMP_INTERVAL_WEEKLY = 5

} XONLINE_COMP_INTERVAL_UNIT;

// Day mask data type
typedef DWORD XONLINE_COMP_DAY_MASK;

//
// Day Mask Constants
//
#define XONLINE_COMP_DAY_MASK_ALL             0x007F
#define XONLINE_COMP_DAY_MASK_SUNDAY          0x0001
#define XONLINE_COMP_DAY_MASK_MONDAY          0x0002
#define XONLINE_COMP_DAY_MASK_TUESDAY         0x0004
#define XONLINE_COMP_DAY_MASK_WEDNESDAY       0x0008
#define XONLINE_COMP_DAY_MASK_THURSDAY        0x0010
#define XONLINE_COMP_DAY_MASK_FRIDAY          0x0020
#define XONLINE_COMP_DAY_MASK_SATURDAY        0x0040

typedef union
{
    DWORD                   dwUnitsOfTime;
    XONLINE_COMP_DAY_MASK   DayMask;

} XONLINE_COMP_UNITS_OR_MASK;

//
// User-friendly structure for Single Eliminations
//
typedef struct
{
    DWORD       dwPrivateSlots;
    DWORD       dwPublicSlots;
    DWORD       dwMinimumPlayers;

    FILETIME    ftRegistrationOpen;
    FILETIME    ftRegistrationClose;
    FILETIME    ftCompetitionStart;
    FILETIME    ftRoundOneStart;
    FILETIME    ftRoundOneEnd;

    DWORD       dwMatchReminderAdvanceMinutes;

    XONLINE_COMP_INTERVAL_UNIT      Interval;
    XONLINE_COMP_UNITS_OR_MASK      UnitOrMask; // Mask when Interval = Day, otherwise Units of time of type Interval

    BOOL        fTeamCompetition;
    DWORD       dwTeamSize;

} XONLINE_COMP_SINGLE_ELIMINATION_ATTRIBUTES;

typedef XONLINE_COMP_SINGLE_ELIMINATION_ATTRIBUTES *PXONLINE_COMP_SINGLE_ELIMINATION_ATTRIBUTES;

//
// Structure returning results for a created competition
//
typedef struct
{
    ULONGLONG   qwCompetitionID;

} XONLINE_COMP_CREATE_RESULTS;

typedef XONLINE_COMP_CREATE_RESULTS *PXONLINE_COMP_CREATE_RESULTS;

//
// Topology results structure
//
typedef struct
{
    DWORD   dwBaseWidth;
    DWORD   dwRoundsReturned;
    DWORD   dwTotalResultEntries;
    DWORD   dwResultsSize;
    PBYTE   pbResults;
    DWORD   dwNumResultAttributeSpecs;
    PXONLINE_QUERY_ATTRIBUTE_SPEC pResultAttributeSpecs;

} XONLINE_COMP_TOPOLOGY_SE_RESULTS;

typedef XONLINE_COMP_TOPOLOGY_SE_RESULTS *PXONLINE_COMP_TOPOLOGY_SE_RESULTS;

#define TOPOLOGY_ID(roundNumber, eventNumber) (((roundNumber) << 16) + (eventNumber))


XBOXAPI
DWORD
WINAPI
XOnlineCompetitionCreate(
            XUID UserXuid,
            DWORD dwTemplate,
            ULONGLONG qwTeamID,
            DWORD dwNumCompetitionAttributes,
            XONLINE_QUERY_ATTRIBUTE *pCompetitionAttributes,
            PXONLINE_COMP_CREATE_RESULTS *ppEntityId,
            PXOVERLAPPED pXOverlapped
            );


XBOXAPI
DWORD
WINAPI
XOnlineCompetitionCreateSingleElimination(
            XUID UserXuid,
            DWORD dwTemplate,
            ULONGLONG qwTeamID,
            const XONLINE_COMP_SINGLE_ELIMINATION_ATTRIBUTES *pDefaultAttributes,
            DWORD dwNumAdditionalAttributes,
            const XONLINE_QUERY_ATTRIBUTE *pAdditionalAttributes,
            PXONLINE_COMP_CREATE_RESULTS *ppEntityId,
            PXOVERLAPPED pXOverlapped
            );



XBOXAPI
DWORD
WINAPI
XOnlineCompetitionSearch(
            DWORD dwQueryID,
            DWORD dwDatasetID,
            DWORD dwPage,
            DWORD dwResultsPerPage,
            DWORD dwNumSearchAttributes,
            XONLINE_QUERY_ATTRIBUTE *pSearchAttributes,
            DWORD dwNumResultAttributeSpecs,
            XONLINE_QUERY_ATTRIBUTE_SPEC *pResultAttributeSpecs,
            PQUERY_SEARCH_RESULT *ppResults,
            PXOVERLAPPED pXOverlapped
            );


XBOXAPI
DWORD
WINAPI
XOnlineCompetitionManageEntrant(
            DWORD dwAction,
            XUID UserId,
            DWORD dwDatasetID,
            ULONGLONG qwTeamID,
            ULONGLONG qwCompetitionID,
            DWORD dwNumAttributes,
            XONLINE_QUERY_ATTRIBUTE *pAttributes,
            PVOID *ppvResults,
            PXOVERLAPPED pXOverlapped
            );


XBOXAPI
DWORD
WINAPI
XOnlineCompetitionCheckin(
            XUID UserXuid,
            DWORD dwDatasetID,
            ULONGLONG qwTeamID,
            ULONGLONG qwCompetitionID,
            ULONGLONG qwEventID,
            PVOID *ppvResults,
            PXOVERLAPPED pXOverlapped
            );



XBOXAPI
DWORD
WINAPI
XOnlineCompetitionCancel(
            XUID UserXuid,
            DWORD dwDatasetID,
            ULONGLONG qwTeamID,
            ULONGLONG qwCompetitionID,
            PVOID *ppvResults,
            PXOVERLAPPED pXOverlapped
            );



XBOXAPI
DWORD
WINAPI
XOnlineCompetitionSubmitResults(
            XUID UserId,
            DWORD dwDatasetID,
            ULONGLONG qwTeamId,
            ULONGLONG qwCompetitionID,
            ULONGLONG qwEventId,
            XUID WinnerXuid,
            XUID LoserXuid,
            PVOID *ppvResults,
            PXOVERLAPPED pXOverlapped
            );



XBOXAPI
DWORD
WINAPI
XOnlineCompetitionTopology(
            DWORD dwTemplate,
            ULONGLONG qwCompetitionID,
            DWORD dwPage,
            DWORD dwResultsPerPage,
            DWORD dwStartingEventTopologyID,
            DWORD dwEndingEventTopologyID,
            DWORD dwNumResultAttributeSpecs,
            XONLINE_QUERY_ATTRIBUTE_SPEC *pResultAttributeSpecs,
            PQUERY_SEARCH_RESULT *ppResults,
            PXOVERLAPPED pXOverlapped
            );


//
// Messaging
//

//DECLARE_HANDLE(XMSG_HANDLE);
//typedef XMSG_HANDLE* PXMSG_HANDLE;

//
// Message Flags
//
#define XONLINE_MSG_FLAG_REQUIRED               0x00000001 // The user is required to read this message
#define XONLINE_MSG_FLAG_RECOMMENDED            0x00000002 // The user has a system recommended message
#define XONLINE_MSG_FLAG_HAS_VOICE              0x00000004 // This message contains a voice attachment
#define XONLINE_MSG_FLAG_HAS_TEXT               0x00000008 // This message contains a text body
#define XONLINE_MSG_FLAG_READ                   0x00000010 // This message has been read
#define XONLINE_MSG_FLAG_NON_EXPORTABLE         0x00000020 // This message should only be displayed on Xbox consoles, not the web
#define XONLINE_MSG_FLAG_TEAM_CONTEXT           0x00000040 // This message's sender context refers to a team ID
#define XONLINE_MSG_FLAG_COMP_CONTEXT           0x00000080 // This message's sender context refers to a competition event or entity ID
#define XONLINE_MSG_FLAG_ALTERNATE_TITLE        0x00000100 // This message is from an alternate Title of the currently logged on title (only available on Xbox consoles)
#define XONLINE_MSG_FLAG_MARKETING              0x00000200 // Used on title-sent messages to indicate the message is marketing-related and opt-in settings should be checked
#define XONLINE_MSG_FLAGS_TITLE_RESERVED        0xFF000000 // Flags reserved for title custom messages
#define XONLINE_MSG_FLAG_SENDER_IS_FRIEND       0x00800000 // Used by Notification to detect invites that should go to V1 clients, also used by clients to allow cross-title invites
#define XONLINE_MSG_FLAG_RECV_DETAILS_NEEDED    0x00200000 // Used by the client on received summaries to indicate that the title has requested downloading details
#define XONLINE_MSG_FLAG_SEND_MSG_OWNED         0x00200000 // Used by the client on message sends to indicate that the message handle is owned by the Send operation
#define XONLINE_MSG_FLAGS_RESERVED              0x005FFC00 // Flags reserved for future use
#define XONLINE_MSG_FLAGS_VALID_SEND_MASK       ( XONLINE_MSG_FLAGS_TITLE_RESERVED | \
                                                  XONLINE_MSG_FLAG_NON_EXPORTABLE | \
                                                  XONLINE_MSG_FLAG_REQUIRED | \
                                                  XONLINE_MSG_FLAG_RECOMMENDED | \
                                                  XONLINE_MSG_FLAG_HAS_VOICE | \
                                                  XONLINE_MSG_FLAG_HAS_TEXT | \
                                                  XONLINE_MSG_FLAG_TEAM_CONTEXT | \
                                                  XONLINE_MSG_FLAG_COMP_CONTEXT | \
                                                  XONLINE_MSG_FLAG_MARKETING ) // Flags valid in a call to send a message
#define XONLINE_MSG_FLAGS_TITLE_SETABLE         ( XONLINE_MSG_FLAG_READ | \
                                                  XONLINE_MSG_FLAGS_TITLE_RESERVED ) // Flags a title is allowed to set on an already sent message
#define XONLINE_MSG_FLAGS_TITLE_CLEARABLE       ( XONLINE_MSG_FLAGS_TITLE_RESERVED ) // Flags a title is allowed to clear on an already sent message

//
// Message Property Types
//
#define XONLINE_MSG_PROP_TYPE_NULL         ((BYTE)  1) // The property contains no data
#define XONLINE_MSG_PROP_TYPE_I1           ((BYTE)  2) // The property value points to 8-bits of data
#define XONLINE_MSG_PROP_TYPE_I2           ((BYTE)  3) // The property value points to 16-bits of data
#define XONLINE_MSG_PROP_TYPE_I4           ((BYTE)  4) // The property value points to 32-bits of data
#define XONLINE_MSG_PROP_TYPE_I8           ((BYTE)  5) // The property value points to 64-bits of data
#define XONLINE_MSG_PROP_TYPE_STRING       ((BYTE)  6) // The property value points to a NULL-terminated wide character string
#define XONLINE_MSG_PROP_TYPE_FILETIME     ((BYTE)  7) // The property value points to a time value
#define XONLINE_MSG_PROP_TYPE_BINARY       ((BYTE)  8) // The property value points to a binary blob that fits in the message details
#define XONLINE_MSG_PROP_TYPE_ATTACHMENT   ((BYTE)  9) // The property value points to a binary blob (or directory path, depending on attachment flags) that will be uploaded to storage during XOnlineMessageSend
#define XONLINE_MSG_PROP_TYPE_BOOL         ((BYTE) 10) // The property value points to a boolean value (1=TRUE, 0=FALSE)
#define XONLINE_MSG_PROP_TYPE_STRING_ID    ((BYTE) 11) // The property value contains a string ID whose text can be requested from the string service

//
// Attachment Flags
//
#define XONLINE_MSG_ATTACHMENT_FLAG_NON_EXPORTABLE  0x00000001 // This attachment should not be visible when the message is displayed on the web
#define XONLINE_MSG_ATTACHMENT_FLAG_DIRECTORY       0x00000002 // The property value points to an ANSI path string to a local directory that will be uploaded to storage, instead of a binary blob
#define XONLINE_MSG_ATTACHMENT_FLAGS_RESERVED       0xFFFFFFFC // Flags reserved for future use


//
// Message Property Tags
// Property tags occupy a word where the upper byte indicates the property's data type, and
// the lower byte indicates a unique identifier for the property.  Property identifiers only
// need to be unique within a given message type.
//
#define XONLINE_MSG_PROP_TAG(type, id)      ((BYTE)(type) << 8 | (BYTE)(id))
#define XOnlineMessageGetPropId(tag)        (BYTE)((WORD)(tag) & 0xFF)
#define XOnlineMessageGetPropType(tag)      (BYTE)((WORD)(tag) >> 8)

//
// Message Property IDs
// Property IDs should adhere to the following ranges:
//
// Range           Purpose
// 0x00-0x7F       Reserved for use by titles
// 0x80-0xBF       Reserved for use by Microsoft for non-global properties
// 0xC0-0xFF       Reserved for use by Microsoft for properties that span all message types
#define XONLINE_MSG_PROP_ID_BUILTIN        0x80 // Used for properties defined by Microsoft
#define XONLINE_MSG_PROP_ID_GLOBAL         0x40 // Used for properties that can span all message types

//
// Message IDs
//
#define XONLINE_MSG_ID_SEND_FAILED         0x80000000 // NOTE: This high bit must not be used so that send can use it to return failed HRESULTs
#define XONLINE_MSG_ID_SYSTEM_MESSAGE      0x40000000 // A message sent by the Live service or a publisher
#define XONLINE_MSG_ID_TRANSIENT_MESSAGE   0x20000000 // A special type of message that goes away when the sender goes offline
#define XONLINE_MSG_ID_BASE_MASK           0x00FFFFFF
#define XONLINE_MSG_ID_RESERVED_MASK       0x1F000000

#define IsMsgTransient( msgid ) ( ( msgid ) & XONLINE_MSG_ID_TRANSIENT_MESSAGE )

//
// Message Notifications (Internal)
//
#define XONLINE_MSG_NOTIFICATION_FLAG_SAME_TITLE         0x000001
#define XONLINE_MSG_NOTIFICATION_FLAG_SAME_PUBLISHER     0x000002
#define XONLINE_MSG_NOTIFICATION_FLAG_INVITE_FROM_FRIEND 0x000004
#define XONLINE_MSG_NOTIFICATION_FLAG_HAS_VOICE          0x000008
#define XONLINE_MSG_NOTIFICATION_FLAG_HAS_TEXT           0x000010
#define XONLINE_MSG_NOTIFICATION_FLAG_ALT_TITLE          0x000020
#define XONLINE_MSG_NOTIFICATION_FLAG_TITLE_RESERVED     0xFF0000
#define XONLINE_MSG_NOTIFICATION_FLAG_RESERVED           0x00FFC0

#pragma pack(push, 1)
struct Q_MESSAGE_NOTIFICATION
{
    DWORD dwTypeAndFlags; // The upper byte is the message type
};

#define XOnlineMessageNotificationGetMsgType( dwTypeAndFlags ) (BYTE)( ( dwTypeAndFlags ) >> 24 )
#define XOnlineMessageNotificationGetFlags( dwTypeAndFlags ) (DWORD)( ( dwTypeAndFlags ) & 0x00FFFFFF )

typedef struct Q_MESSAGE_NOTIFICATION XONLINE_MESSAGE_NOTIFICATION;
#pragma pack(pop)

//
// Message Types
//
// A message type establishes the purpose of the message and the properties that
// are required for a message of that type.
//
#define XONLINE_MSG_TYPE_TITLE_CUSTOM           ((BYTE) 1) // context: title defined;    required props: title defined
#define XONLINE_MSG_TYPE_FRIEND_REQUEST         ((BYTE) 2) // context: 0;                required props: none
#define XONLINE_MSG_TYPE_GAME_INVITE            ((BYTE) 3) // context: see msg flags;    required props: XONLINE_MSG_PROP_SESSION_ID
#define XONLINE_MSG_TYPE_TEAM_RECRUIT           ((BYTE) 4) // context: inviting team ID; required props: none
#define XONLINE_MSG_TYPE_COMP_REMINDER          ((BYTE) 5) // context: comp event ID;    required props: XONLINE_MSG_PROP_COMP_NAME, XONLINE_MSG_PROP_COMP_EVENT_START
#define XONLINE_MSG_TYPE_COMP_REQUEST           ((BYTE) 6) // context: comp entity ID;   required props: XONLINE_MSG_PROP_COMP_NAME, XONLINE_MSG_PROP_COMP_START, XONLINE_MSG_PROP_COMP_REG_CLOSE
#define XONLINE_MSG_TYPE_LIVE_MESSAGE           ((BYTE) 7) // context: 0                 required props: XONLINE_MSG_PROP_SYSTEM_TEXT
#define XONLINE_MSG_TYPE_PERSONAL_MESSAGE       ((BYTE) 8) // context: 0                 required props: XONLINE_MSG_PROP_TEXT, XONLINE_MSG_PROP_VOICE_DATA.
#define XONLINE_MSG_TYPE_VIDEO_MESSAGE          ((BYTE) 9) // context: 0                 required props: XONLINE_MSG_PROP_TEXT, XONLINE_MSG_PROP_VIDEO_DATA
#define XONLINE_MSG_TYPE_QUICK_CHAT_INVITE      ((BYTE) 10) // context: 0

//
// Global property tags, allowed in any message type
//

// All message types can contain a voice attachment specified in the following properties.  All three
// of the following properties should be specified together.  The XONLINE_MSG_FLAG_HAS_VOICE message
// flag can be used to test for the presence of these properties before the message details have been
// retrieved.
#define XONLINE_MSG_PROP_VOICE_DATA               XONLINE_MSG_PROP_TAG(XONLINE_MSG_PROP_TYPE_ATTACHMENT, XONLINE_MSG_PROP_ID_GLOBAL | XONLINE_MSG_PROP_ID_BUILTIN | 1)
#define XONLINE_MSG_PROP_VOICE_DATA_CODEC         XONLINE_MSG_PROP_TAG(XONLINE_MSG_PROP_TYPE_I2,         XONLINE_MSG_PROP_ID_GLOBAL | XONLINE_MSG_PROP_ID_BUILTIN | 2)
#define XONLINE_MSG_PROP_VOICE_DATA_DURATION      XONLINE_MSG_PROP_TAG(XONLINE_MSG_PROP_TYPE_I4,         XONLINE_MSG_PROP_ID_GLOBAL | XONLINE_MSG_PROP_ID_BUILTIN | 3)

// All message types can contain a text summary specified in the following properties.  Both
// of the following properties should be specified together.  The XONLINE_MSG_FLAG_HAS_TEXT message
// flag can be used to test for the presence of these properties before the message details have been
// retrieved.  The text should be 256 characters or less and may be used by Live anywhere that a text
// summary of the message is useful, such as in a Messenger Alert, on the web, or in the Dashboard.
#define XONLINE_MSG_PROP_TEXT                     XONLINE_MSG_PROP_TAG(XONLINE_MSG_PROP_TYPE_STRING,     XONLINE_MSG_PROP_ID_GLOBAL | XONLINE_MSG_PROP_ID_BUILTIN | 4)
#define XONLINE_MSG_PROP_TEXT_LANGUAGE            XONLINE_MSG_PROP_TAG(XONLINE_MSG_PROP_TYPE_I4,         XONLINE_MSG_PROP_ID_GLOBAL | XONLINE_MSG_PROP_ID_BUILTIN | 5)


//
//Video Message Properties
//
#define XONLINE_MSG_PROP_VIDEO_FRAME_DATA         XONLINE_MSG_PROP_TAG(XONLINE_MSG_PROP_TYPE_ATTACHMENT, XONLINE_MSG_PROP_ID_BUILTIN | 1)
#define XONLINE_MSG_PROP_VIDEO_FRAME_CODEC        XONLINE_MSG_PROP_TAG(XONLINE_MSG_PROP_TYPE_I2,         XONLINE_MSG_PROP_ID_BUILTIN | 2)           //This defines the First Frame of the Video as JPG, BMP...etc if we wanted to show the First Frame of the Video in the HUD.
#define XONLINE_MSG_PROP_VIDEO_DATA               XONLINE_MSG_PROP_TAG(XONLINE_MSG_PROP_TYPE_ATTACHMENT, XONLINE_MSG_PROP_ID_BUILTIN | 3)
#define XONLINE_MSG_PROP_VIDEO_DATA_CODEC         XONLINE_MSG_PROP_TAG(XONLINE_MSG_PROP_TYPE_I2,         XONLINE_MSG_PROP_ID_BUILTIN | 4)
#define XONLINE_MSG_PROP_VIDEO_DATA_DURATION      XONLINE_MSG_PROP_TAG(XONLINE_MSG_PROP_TYPE_I4,         XONLINE_MSG_PROP_ID_BUILTIN | 5)

//
// Invite message properties
//
#define XONLINE_MSG_PROP_SESSION_ID               XONLINE_MSG_PROP_TAG(XONLINE_MSG_PROP_TYPE_I8,         XONLINE_MSG_PROP_ID_BUILTIN | 1)
#define XONLINE_MSG_PROP_SESSION_DESCRIPTION      XONLINE_MSG_PROP_TAG(XONLINE_MSG_PROP_TYPE_STRING,     XONLINE_MSG_PROP_ID_BUILTIN | 2)
#define XONLINE_MSG_PROP_SESSION_HOST_XNADDR      XONLINE_MSG_PROP_TAG(XONLINE_MSG_PROP_TYPE_BINARY,     XONLINE_MSG_PROP_ID_BUILTIN | 3)
#define XONLINE_MSG_PROP_SESSION_HOST_KEY         XONLINE_MSG_PROP_TAG(XONLINE_MSG_PROP_TYPE_BINARY,     XONLINE_MSG_PROP_ID_BUILTIN | 4)

//
// Live system message properties
//
#define XONLINE_MSG_PROP_SYSTEM_TEXT              XONLINE_MSG_PROP_TAG(XONLINE_MSG_PROP_TYPE_STRING_ID,  XONLINE_MSG_PROP_ID_BUILTIN | 1)

//
// Team Recruit message properties
//
#define XONLINE_MSG_PROP_TEAM_NAME                XONLINE_MSG_PROP_TAG(XONLINE_MSG_PROP_TYPE_STRING,     XONLINE_MSG_PROP_ID_BUILTIN | 1)

//
// Competitions message properties
//
#define XONLINE_MSG_PROP_COMP_DATASET             XONLINE_MSG_PROP_TAG(XONLINE_MSG_PROP_TYPE_I4,         XONLINE_MSG_PROP_ID_BUILTIN | 0x1 )
#define XONLINE_MSG_PROP_COMP_NAME                XONLINE_MSG_PROP_TAG(XONLINE_MSG_PROP_TYPE_STRING,     XONLINE_MSG_PROP_ID_BUILTIN | 0x2 )
#define XONLINE_MSG_PROP_COMP_START               XONLINE_MSG_PROP_TAG(XONLINE_MSG_PROP_TYPE_FILETIME,   XONLINE_MSG_PROP_ID_BUILTIN | 0x3 )
#define XONLINE_MSG_PROP_COMP_ROUND               XONLINE_MSG_PROP_TAG(XONLINE_MSG_PROP_TYPE_I2,         XONLINE_MSG_PROP_ID_BUILTIN | 0x4 )
#define XONLINE_MSG_PROP_COMP_OPPONENT            XONLINE_MSG_PROP_TAG(XONLINE_MSG_PROP_TYPE_STRING_ID,  XONLINE_MSG_PROP_ID_BUILTIN | 0x5 )
#define XONLINE_MSG_PROP_COMP_ADMIN               XONLINE_MSG_PROP_TAG(XONLINE_MSG_PROP_TYPE_I8,         XONLINE_MSG_PROP_ID_BUILTIN | 0x6 )
#define XONLINE_MSG_PROP_COMP_REG_CLOSE           XONLINE_MSG_PROP_TAG(XONLINE_MSG_PROP_TYPE_FILETIME,   XONLINE_MSG_PROP_ID_BUILTIN | 0x7 )
#define XONLINE_MSG_PROP_COMP_PRIVATE_SLOTS       XONLINE_MSG_PROP_TAG(XONLINE_MSG_PROP_TYPE_I2,         XONLINE_MSG_PROP_ID_BUILTIN | 0x8 )
#define XONLINE_MSG_PROP_COMP_PUBLIC_SLOTS        XONLINE_MSG_PROP_TAG(XONLINE_MSG_PROP_TYPE_I2,         XONLINE_MSG_PROP_ID_BUILTIN | 0x9 )
#define XONLINE_MSG_PROP_COMP_UNITS               XONLINE_MSG_PROP_TAG(XONLINE_MSG_PROP_TYPE_I2,         XONLINE_MSG_PROP_ID_BUILTIN | 0xA )
#define XONLINE_MSG_PROP_COMP_INTERVAL            XONLINE_MSG_PROP_TAG(XONLINE_MSG_PROP_TYPE_I2,         XONLINE_MSG_PROP_ID_BUILTIN | 0xB )
#define XONLINE_MSG_PROP_COMP_DAYMASK             XONLINE_MSG_PROP_TAG(XONLINE_MSG_PROP_TYPE_I2,         XONLINE_MSG_PROP_ID_BUILTIN | 0xC )
#define XONLINE_MSG_PROP_COMP_DESCRIPTION         XONLINE_MSG_PROP_TAG(XONLINE_MSG_PROP_TYPE_STRING,     XONLINE_MSG_PROP_ID_BUILTIN | 0xD )
#define XONLINE_MSG_PROP_COMP_URL                 XONLINE_MSG_PROP_TAG(XONLINE_MSG_PROP_TYPE_STRING,     XONLINE_MSG_PROP_ID_BUILTIN | 0xE )
#define XONLINE_MSG_PROP_COMP_EVENT_ID            XONLINE_MSG_PROP_TAG(XONLINE_MSG_PROP_TYPE_I8,         XONLINE_MSG_PROP_ID_BUILTIN | 0x10 )
#define XONLINE_MSG_PROP_COMP_EVENT_START         XONLINE_MSG_PROP_TAG(XONLINE_MSG_PROP_TYPE_FILETIME,   XONLINE_MSG_PROP_ID_BUILTIN | 0x11 )

//
// HUD message properties.  These properties act the same as game invite
// properties.  This is so that some day they may be merged.
//
#define XONLINE_HUD_MSG_PROP_SESSION_ID           XONLINE_MSG_PROP_TAG(XONLINE_MSG_PROP_TYPE_I8,         XONLINE_MSG_PROP_ID_BUILTIN | 1)
#define XONLINE_HUD_MSG_PROP_SESSION_DESCRIPTION  XONLINE_MSG_PROP_TAG(XONLINE_MSG_PROP_TYPE_STRING,     XONLINE_MSG_PROP_ID_BUILTIN | 2)
#define XONLINE_HUD_MSG_PROP_SESSION_HOST_XNADDR  XONLINE_MSG_PROP_TAG(XONLINE_MSG_PROP_TYPE_BINARY,     XONLINE_MSG_PROP_ID_BUILTIN | 3)
#define XONLINE_HUD_MSG_PROP_SESSION_HOST_KEY     XONLINE_MSG_PROP_TAG(XONLINE_MSG_PROP_TYPE_BINARY,     XONLINE_MSG_PROP_ID_BUILTIN | 4)
#define XONLINE_HUD_MSG_PROP_VOICECHAT_PORT       XONLINE_MSG_PROP_TAG(XONLINE_MSG_PROP_TYPE_I2,         XONLINE_MSG_PROP_ID_BUILTIN | 5)

//
// Voice Codec types (values for XONLINE_MSG_PROP_VOICE_DATA_CODEC)
//
#define XONLINE_PROP_VOICE_DATA_CODEC_WMAVOICE_V90      1
#define XONLINE_PROP_VOICE_DATA_CODEC_SASE3200          2


// Write to the global settings rather than title-specific settings.
// We use the Dash titleid for mysteries having to do with xbox.com.
#define XPROFILE_TITLEID_GLOBAL_SETTINGS        XENON_DASH_TITLE_ID

// Values for the stored Profile: User State
typedef enum _XPROFILE_GAMER_PRESENCE_USER_STATE_VALUE
{
    XPROFILE_GAMER_PRESENCE_USER_STATE_VALUE_ONLINE = 0,
    XPROFILE_GAMER_PRESENCE_USER_STATE_VALUE_AWAY,
    XPROFILE_GAMER_PRESENCE_USER_STATE_VALUE_BUSY,
    XPROFILE_GAMER_PRESENCE_USER_STATE_VALUE_APPEAROFFLINE

} XPROFILE_GAMER_PRESENCE_USER_STATE_VALUE;


typedef struct
{
    XOVERLAPPED*    pXOverlapped;
    DWORD           dwTitleId;                  // A title in your family or 0 for the current title
    DWORD           dwUserIndex;                // User index of the requesting user
    DWORD           dwNumFor;                   // Number of users (indexes or XUIDs) whose setings are read
    const XUID*     pxuidFor;                   // Pointer to array of XUIDs to request settings for
    DWORD           dwNumSettingIds;            // Number of settings in pSettingIds
    const DWORD*    pSettingIds;                // Settings to retrieve for list of users
    DWORD           cbResults;
    PXUSER_READ_PROFILE_SETTING_RESULT pResults;
} XGI_READSETTINGS_MSG;


typedef struct
{
    XOVERLAPPED*    pXOverlapped;
    DWORD           dwTitleId;
    DWORD           dwUserIndex;                // User index of the player whose settings are written
    DWORD           dwNumSettings;              // Number of settings in pSettings
    const XUSER_PROFILE_SETTING* pSettings;     // Settings to set
} XGI_WRITESETTINGS_MSG;


//-----------------------------------------------------------------------------
//  XBOS API structs
//-----------------------------------------------------------------------------

typedef struct
{
    DWORD   dwUserIndex;
    DWORD   dwTitleId;
    DWORD   dwContentCategories;
    XOFFERING_CONTENTAVAILABLE_RESULT *pResults;
} LIVEBASE_CONTENTAVAILABLE_MSG;


//-----------------------------------------------------------------------------
// XM_LIVEBASE_PRESENCESET message structures
//-----------------------------------------------------------------------------

typedef struct
{
    DWORD   dwContextId;
    DWORD   dwContextValue;
} PRESENCE_CONTEXT;


typedef struct
{
    DWORD   dwPropertyId;   // Includes type; use XPROPERTYTYPEFROMID
    DWORD   cbData;         // Count of bytes in pbData
    // BYTE    pbData;      // Property value starts here
                            // Strings and binary are prefixed with a WORD length.
                            // Strings are wide chars (UTF-16) and are not NULL-terminated.
} PRESENCE_PROPERTY;

// This is the maximum total number of bytes for contexts and properties
// that LiveBase will accept, cache and send up to the servers.
#define MAX_LIVEBASE_PRESENCE 256

typedef struct
{
    XUID                            xuidUser;           // UserID
    DWORD                           dwPresenceMode;     // The value of the presence mode context (X_CONTEXT_PRESENCE)
    DWORD                           dwNumContexts;      // Number PRESENCE_CONTEXTs at beginning of rgbPayload
    DWORD                           dwNumProperties;    // Number PRESENCE_PROPERTY after contexts in rgbPayload
    BYTE                            rgbPayload[MAX_LIVEBASE_PRESENCE];
} LIVEBASE_SETPRESENCE_MSG;

#ifdef __cplusplus
}
#endif

#endif  // __XONLINEP__

