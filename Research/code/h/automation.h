#pragma once

/*++

Copyright (c) Microsoft Corporation

Module Name:

    Automation.h

Abstract:

    This module contains the code to interact with the test automation
    framework.  This consists of providing the hooks into the system for
    recording the interaction between the title and the system for future
    playback and the spoofing of function calls for unit testing UI or 
    to unit test functions by directly altering input parameters.

    The majority of the work is accomplished by coordinating with the 
    TestXex application for manipulating the message.  This coordination
    is done synchronously and should not be too expensive.  Unfortunately
    making it asynchronous (even for async messaging) isn't an option if 
    we need to spoof the hr or other parameters.
--*/

// More useful and descriptive definitions to work with for code readers.
#define AUTO_PROCEED                    false       // Corresponds to a result of S_FALSE
#define AUTO_SKIP                       true        // Corresponds to a result of S_OK

#define AUTO_PRESEND                    true
#define AUTO_POSTSEND                   false

#if TESTAUTOMATION

/* There are three states of interest to automation:
        1.  I didn't do anything, proceed as normal
        2.  I altered the parameters proceed as normal
        3.  I altered the results skip the remaining operations
   From a behaviour point of view the 1st and 2nd can be rolled into 
   each other.  
*/

typedef HRESULT (WINAPI *SetupOverlappedFunction)(
    PXOVERLAPPED pOverlapped,
    PXASYNCMESSAGE pMsg
    );

bool
WINAPI
AutomationSetNotification(
    DWORD *pdwMessage,     
    ULONG_PTR *ppParam,
    DWORD *pdwUser,
    HRESULT *phr
    );

bool
WINAPI
AutomationSendAsyncMessage(
    HXAMAPP hxamapp,
    PXASYNCMESSAGE pMsg,
    HRESULT *phr
    );

bool
WINAPI
AutomationSendMessage(
    bool fIsPresend,
    HXAMAPP hxamapp,
    DWORD dwMessage,
    UINT_PTR *ppParam1,
    UINT_PTR *ppParam2,
    HRESULT *phr
    );

bool
WINAPI
AutomationSendAppLoadMessage(
    LPCSTR pszSysApp
    );

VOID
WINAPI
AutomationInitialize();

VOID
WINAPI
AutomationCleanup();

VOID
WINAPI
AutomationTitleShutdown();

BOOL
WINAPI
AutomationAsyncMessageInProgress(
    PXASYNCMESSAGE pMsg
    );

BOOL 
WINAPI
AutomationInputGetState(
    IN DWORD dwUserIndex,
    IN OUT XINPUT_STATE *pXInputState
    );

#else // !TESTAUTOMATION
#define g_fAutomation                               FALSE
#define AutomationInitialize()
#define AutomationCleanup()
#define AutomationTitleShutdown()

#define AutomationSetNotification(A, B, C, D)       AUTO_PROCEED
#define AutomationSendAsyncMessage(A, B, C)         FALSE
#define AutomationSendMessage(A, B, C, D, E, F)     AUTO_PROCEED
#define AutomationAsyncMessageInProgress(A)         FALSE
#define AutomationInputGetState(A, B)               FALSE
#define AutomationSendAppLoadMessage(A)             AUTO_PROCEED
#endif // TESTAUTOMATION