/*++

Copyright (c)  Microsoft Corporation

Module Name:

    xinput.h

Abstract:

    This module defines xinput structures

--*/

#ifndef _XINPUT_H
#define _XINPUT_H

//
// Define the values for HID keycodes
//

#define USBHID_KEYCODE_A                0x04
#define USBHID_KEYCODE_Z                0x1D

#define USBHID_KEYCODE_1                0x1E
#define USBHID_KEYCODE_9                0x26
#define USBHID_KEYCODE_0                0x27

#define USBHID_KEYCODE_RETURN           0x28

#define USBHID_KEYCODE_QUESTION         0x38
#define USBHID_KEYCODE_CAPSLOCK         0x39

#define USBHID_KEYCODE_KEYPADNUMLOCK    0x53
#define USBHID_KEYCODE_KEYPADBACKSLASH  0x54
#define USBHID_KEYCODE_KEYPADDECIMAL    0x63

#define USBHID_KEYCODE_LCONTROL         0xE0
#define USBHID_KEYCODE_LSHIFT           0xE1
#define USBHID_KEYCODE_LALT             0xE2
#define USBHID_KEYCODE_LGUI             0xE3
#define USBHID_KEYCODE_RCONTROL         0xE4
#define USBHID_KEYCODE_RSHIFT           0xE5
#define USBHID_KEYCODE_RALT             0xE6
#define USBHID_KEYCODE_RGUI             0xE7

//
// Define the values for HID key modifier
//

#define USBHID_MODIFIER_LCTRL           0x01
#define USBHID_MODIFIER_LSHIFT          0x02
#define USBHID_MODIFIER_LALT            0x04
#define USBHID_MODIFIER_LGUI            0x08
#define USBHID_MODIFIER_RCTRL           0x10
#define USBHID_MODIFIER_RSHIFT          0x20
#define USBHID_MODIFIER_RALT            0x40
#define USBHID_MODIFIER_RGUI            0x80

//
// Define the values for HID LEDs
//

#define USBHID_LED_NUMLOCK              0x01
#define USBHID_LED_CAPSLOCK             0x02
#define USBHID_LED_SCROLLLOCK           0x04

//
// Internal state needed by the API
//

#define INTERNAL_STATE_INDEX_SYSAPP        0
#define INTERNAL_STATE_INDEX_TITLE         1


typedef struct _GAMEPAD_STATE_DATA {
    DWORD   LastPacketNumber;
    UCHAR   AnalogPressedState;
    WORD    ButtonPressedState;
    WORD    LeftThumbPressedState;
    WORD    RightThumbPressedState;
} GAMEPAD_STATE_DATA, *PGAMEPAD_STATE_DATA;

typedef struct _INTERNAL_KEYSTROKE_QUEUE {
    XINPUT_KEYSTROKE Data[10];  // worst possible case, 6 real keys + 4 modifiers
    UCHAR Size;
    UCHAR Count;
    UCHAR InIndex;
    UCHAR OutIndex;
} INTERNAL_KEYSTROKE_QUEUE, *PINTERNAL_KEYSTROKE_QUEUE;

//
//  Language Support for Keyboards.  Each language
//  is implemented as an XINPUT_LANGUAGE_SERVICE.
//

#define MAX_LANGUAGE_SERVICE_AREA 8
typedef BOOL  (*PFNXINPUTPROCESSLANG)(PXINPUT_KEYSTROKE pKeystroke, PVOID pvStateArea);
typedef DWORD (*PFNXINPUTRESETLANGSTATEAREA)(PVOID pvStateArea);
typedef BOOL  (*PFNXINPUTLANGISKEYPENDING)(PVOID pvStateArea);

typedef struct _XINPUT_LANGUAGE_SERVICE
{
    DWORD                            dwLanguage;
    PFNXINPUTRESETLANGSTATEAREA      pfnResetStateArea;
    PFNXINPUTPROCESSLANG             pfnProcess;
    PFNXINPUTLANGISKEYPENDING        pfnIsKeyPending;
    WORD                             wSupportedModifiers;
} XINPUT_LANGUAGE_SERVICE, *PXINPUT_LANGUAGE_SERVICE;

//
//  Languages
//
#ifdef __cplusplus
extern "C" {
#endif

extern XINPUT_LANGUAGE_SERVICE XAM_EnglishLanguageSupport;
extern XINPUT_LANGUAGE_SERVICE XAM_EnglishUKLanguageSupport;
extern XINPUT_LANGUAGE_SERVICE XAM_JapaneseLanguageSupport;
extern XINPUT_LANGUAGE_SERVICE XAM_GermanLanguageSupport;
extern XINPUT_LANGUAGE_SERVICE XAM_FrenchLanguageSupport;
extern XINPUT_LANGUAGE_SERVICE XAM_FrenchCanadaLanguageSupport;
extern XINPUT_LANGUAGE_SERVICE XAM_ItalianLanguageSupport;
extern XINPUT_LANGUAGE_SERVICE XAM_SpanishLanguageSupport;
extern XINPUT_LANGUAGE_SERVICE XAM_ChineseBopomofoLanguageSupport;
extern XINPUT_LANGUAGE_SERVICE XAM_ChineseChajeiLanguageSupport;
extern XINPUT_LANGUAGE_SERVICE XAM_KoreanLanguageSupport;
extern XINPUT_LANGUAGE_SERVICE XAM_SwedishLanguageSupport;
extern XINPUT_LANGUAGE_SERVICE XAM_PortuguesePTLanguageSupport;
extern XINPUT_LANGUAGE_SERVICE XAM_PortugueseBRLanguageSupport;

#ifdef __cplusplus
}
#endif

typedef struct _INTERNAL_STATE_DATA {

    //
    // these are 256-bit arrays that reflect the per-process
    // state of the keyboard as last reported
    //

    UCHAR                     DownHIDKeys[32];      // snapshot of keys held down (using USB HIDs)
    UCHAR                     DownVirtualKeys[32];  // snapshot of keys held down (using VK_* codes)
    INTERNAL_KEYSTROKE_QUEUE  PendingKeystrokes;    // actual keystrokes (key up and down events)

    GAMEPAD_STATE_DATA  GamepadState[XUSER_MAX_COUNT];
    DWORD               LastReturnedPacketNumber[XUSER_MAX_COUNT];
    UCHAR               LastReturnedConnectedState[XUSER_MAX_COUNT];
    DWORD               LastKeyTime;
    WORD                LastKeyDown;
    WORD                LastKeyFlags;
    UCHAR               LastKeyDownHidCode;
    UCHAR               LastKeyDevice;  // 0: None, 1: Gamepad, 2: Keyboard
    UCHAR               SlowRepeat;
} INTERNAL_STATE_DATA, *PINTERNAL_STATE_DATA;

//
//  Per-keyboard, as oppose to per-process per-keyboard state.
//  Basically, the language settings, and the lock flags.
//

typedef struct _INTERNAL_KEYBOARD_STATE {
  PXINPUT_LANGUAGE_SERVICE  pLanguageService;
  UCHAR                     LanguageStateArea[MAX_LANGUAGE_SERVICE_AREA];
  WORD                      wLockFlags;
} INTERNAL_KEYBOARD_STATE, *PINTERNAL_KEYBOARD_STATE;


typedef struct _INTERNAL_IR_STATE {
    KSPIN_LOCK          SpinLock;
    ULONG               ButtonCode;
    ULONG               LastToggle;
    ULONG               SendUpButtonCode;
    ULONG               LastSMCNotificationTime;
    ULONG               LastKeyDownTime;
    UCHAR               SlowRepeat;
} INTERNAL_IR_STATE, *PINTERNAL_IR_STATE;

#endif // _XINPUT_H
