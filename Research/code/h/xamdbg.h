/*++

Copyright (c) Microsoft Corporation

Module Name:

    xamdbg.h

Abstract:

    This module defines the debug and logging APIs used by XAM applications

--*/

#include <stdarg.h>
#include <stdio.h>

#ifndef __XAMDBG_H__
#define __XAMDBG_H__

#ifdef __cplusplus
extern "C" {
#endif

#if DBG
#define XAM_FEATURE_ASSERT              1
#define XAM_FEATURE_TRACE               1
#else   // DBG
#define XAM_FEATURE_ASSERT              0
#define XAM_FEATURE_TRACE               0
#endif  // !DBG

//
// XAM debug flags enable granular control over the debug output made by
// applications
//

#define XAMDBG_PRINT_LEVEL_MASK         0x0000000F
#define XAMDBG_BREAK_LEVEL_MASK         0x000000F0
#define XAMDBG_FLAG_ENABLED             0x00000100

#define XAMDBG_PRINT_LEVEL_SHIFT        0
#define XAMDBG_BREAK_LEVEL_SHIFT        4

#define XAMDBG_LEVEL_TRACE              XDBG_TRACE
#define XAMDBG_LEVEL_WARNING            XDBG_WARNING
#define XAMDBG_LEVEL_ERROR              XDBG_ERROR

#define XAMDBG_TAG(P, B, F)             ((P << XAMDBG_PRINT_LEVEL_SHIFT) | (B << XAMDBG_BREAK_LEVEL_SHIFT) | F)
#define XAMDBG_TAG_PRINT_LEVEL(X)       ((X & XAMDBG_PRINT_LEVEL_MASK) >> XAMDBG_PRINT_LEVEL_SHIFT)
#define XAMDBG_TAG_BREAK_LEVEL(X)       ((X & XAMDBG_BREAK_LEVEL_MASK) >> XAMDBG_BREAK_LEVEL_SHIFT)

//
// Inline breakpoint
//

#ifndef DbgBreak
#ifdef XAM_FEATURE_ASSERT
#define XamDbgBreak()  __debugbreak()
#else
#define XamDbgBreak()
#endif
#endif

//
// The print macro is used by other macros to wrap XamDbgPrint
//

#if !defined(_PREFAST_)

#if XAM_FEATURE_TRACE
#define XAMPRINT(b, lvl, sz, ...)        do { BOOL f = XamDbgPrint(lvl, sz, ##__VA_ARGS__); if(f && b) { XamDbgBreak(); } } while (0);
#else   // XAM_FEATURE_TRACE
#define XAMPRINT(b, lvl, sz, ...)
#endif  // !XAM_FEATURE_TRACE

#else   // _PREFAST_

#define XAMPRINT(b, lvl, sz)
#define XAMPRINT(b, lvl, sz, a1)
#define XAMPRINT(b, lvl, sz, a1, a2)
#define XAMPRINT(b, lvl, sz, a1, a2, a3)
#define XAMPRINT(b, lvl, sz, a1, a2, a3, a4)
#define XAMPRINT(b, lvl, sz, a1, a2, a3, a4, a5)
#define XAMPRINT(b, lvl, sz, a1, a2, a3, a4, a5, a6)
#define XAMPRINT(b, lvl, sz, a1, a2, a3, a4, a5, a6, a7)
#define XAMPRINT(b, lvl, sz, a1, a2, a3, a4, a5, a6, a7, a8)
#define XAMPRINT(b, lvl, sz, a1, a2, a3, a4, a5, a6, a7, a8, a9)
#define XAMPRINT(b, lvl, sz, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10)

#endif  // _PREFAST_

//
// Trace macros print out a debug message if the system app's debug level is
// sufficiently low
//

#if !defined(_PREFAST_)

#if XAM_FEATURE_TRACE
#define XAMTRCLINE()                    do { XAMPRINT(TRUE, XDBG_TRACE, __FILE__ " @ " __LINE__ "\n"); } while(0)
#define XAMTRC(tag, sz, ...)            do { XAMPRINT(TRUE, XDBG_TRACE, sz, ##__VA_ARGS__); } while(0);
#define XAMWRN(tag, sz, ...)            do { XAMPRINT(TRUE, XDBG_WARNING, sz, ##__VA_ARGS__); } while(0);
#define XAMERR(tag, sz, ...)            do { XAMPRINT(TRUE, XDBG_ERROR, sz, ##__VA_ARGS__); } while(0);
#else   // XAM_FEATURE_TRACE
#define XAMTRCLINE()
#define XAMTRC(tag, sz, ...)
#define XAMWRN(tag, sz, ...)
#define XAMERR(tag, sz, ...)
#endif  // !XAM_FEATURE_TRACE

#else   // _PREFAST_

#define XAMTRC(tag, sz)
#define XAMTRC(tag, sz, a1)
#define XAMTRC(tag, sz, a1, a2)
#define XAMTRC(tag, sz, a1, a2, a3)
#define XAMTRC(tag, sz, a1, a2, a3, a4)
#define XAMTRC(tag, sz, a1, a2, a3, a4, a5)
#define XAMTRC(tag, sz, a1, a2, a3, a4, a5, a6)
#define XAMTRC(tag, sz, a1, a2, a3, a4, a5, a6, a7)
#define XAMTRC(tag, sz, a1, a2, a3, a4, a5, a6, a7, a8)
#define XAMTRC(tag, sz, a1, a2, a3, a4, a5, a6, a7, a8, a9)
#define XAMTRC(tag, sz, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10)

#define XAMWRN(tag, sz)
#define XAMWRN(tag, sz, a1)
#define XAMWRN(tag, sz, a1, a2)
#define XAMWRN(tag, sz, a1, a2, a3)
#define XAMWRN(tag, sz, a1, a2, a3, a4)
#define XAMWRN(tag, sz, a1, a2, a3, a4, a5)
#define XAMWRN(tag, sz, a1, a2, a3, a4, a5, a6)
#define XAMWRN(tag, sz, a1, a2, a3, a4, a5, a6, a7)
#define XAMWRN(tag, sz, a1, a2, a3, a4, a5, a6, a7, a8)
#define XAMWRN(tag, sz, a1, a2, a3, a4, a5, a6, a7, a8, a9)
#define XAMWRN(tag, sz, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10)

#define XAMERR(tag, sz)
#define XAMERR(tag, sz, a1)
#define XAMERR(tag, sz, a1, a2)
#define XAMERR(tag, sz, a1, a2, a3)
#define XAMERR(tag, sz, a1, a2, a3, a4)
#define XAMERR(tag, sz, a1, a2, a3, a4, a5)
#define XAMERR(tag, sz, a1, a2, a3, a4, a5, a6)
#define XAMERR(tag, sz, a1, a2, a3, a4, a5, a6, a7)
#define XAMERR(tag, sz, a1, a2, a3, a4, a5, a6, a7, a8)
#define XAMERR(tag, sz, a1, a2, a3, a4, a5, a6, a7, a8, a9)
#define XAMERR(tag, sz, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10)

#endif  // _PREFAST_

//
// Traps causes a debugger to be broken into
//

#if !defined(_PREFAST_)

#if XAM_FEATURE_ASSERT
#define XAMTRAPLINE()                   do { XAMPRINT(FALSE, XDBG_TRACE, __FILE__ " @ " __LINE__ "\n"); DbgBreak(); } while(0);
#define XAMTRAP(sz, ...)                do { XAMPRINT(FALSE, XDBG_TRACE, sz, ##__VA_ARGS__); } while(0);
#else   // XAM_FEATURE_ASSERT
#define XAMTRAPLINE()
#define XAMTRAP(sz, ...)
#endif  // !XAM_FEATURE_ASSERT

#else   // _PREFAST_

#define XAMTRAP(sz)
#define XAMTRAP(sz, a1)
#define XAMTRAP(sz, a1, a2)
#define XAMTRAP(sz, a1, a2, a3)
#define XAMTRAP(sz, a1, a2, a3, a4)
#define XAMTRAP(sz, a1, a2, a3, a4, a5)
#define XAMTRAP(sz, a1, a2, a3, a4, a5, a6)
#define XAMTRAP(sz, a1, a2, a3, a4, a5, a6, a7)
#define XAMTRAP(sz, a1, a2, a3, a4, a5, a6, a7, a8)
#define XAMTRAP(sz, a1, a2, a3, a4, a5, a6, a7, a8, a9)
#define XAMTRAP(sz, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10)

#endif  // _PREFAST_

//
// Compatibility with prior XAM debug instrumentation
//

#define TraceSz0                        XAMTRC
#define TraceSz1                        XAMTRC
#define TraceSz2                        XAMTRC
#define TraceSz3                        XAMTRC
#define TraceSz4                        XAMTRC
#define TraceSz5                        XAMTRC
#define TraceSz6                        XAMTRC
#define TraceSz7                        XAMTRC
#define TraceSz8                        XAMTRC
#define TraceSz9                        XAMTRC
#define TraceSz10                       XAMTRC

#define WarnSz0                         XAMWRN
#define WarnSz1                         XAMWRN
#define WarnSz2                         XAMWRN
#define WarnSz3                         XAMWRN
#define WarnSz4                         XAMWRN
#define WarnSz5                         XAMWRN
#define WarnSz6                         XAMWRN
#define WarnSz7                         XAMWRN
#define WarnSz8                         XAMWRN
#define WarnSz9                         XAMWRN
#define WarnSz10                        XAMWRN

#define ErrorSz0                        XAMERR
#define ErrorSz1                        XAMERR
#define ErrorSz2                        XAMERR
#define ErrorSz3                        XAMERR
#define ErrorSz4                        XAMERR
#define ErrorSz5                        XAMERR
#define ErrorSz6                        XAMERR
#define ErrorSz7                        XAMERR
#define ErrorSz8                        XAMERR
#define ErrorSz9                        XAMERR
#define ErrorSz10                       XAMERR

#define TrapSz0                         XAMTRAP
#define TrapSz1                         XAMTRAP
#define TrapSz2                         XAMTRAP
#define TrapSz3                         XAMTRAP
#define TrapSz4                         XAMTRAP
#define TrapSz5                         XAMTRAP
#define TrapSz6                         XAMTRAP
#define TrapSz7                         XAMTRAP
#define TrapSz8                         XAMTRAP
#define TrapSz9                         XAMTRAP
#define TrapSz10                        XAMTRAP

#define Assert                          NT_ASSERT

#ifdef __cplusplus
};
#endif

#endif // __XAMDBG_H__
