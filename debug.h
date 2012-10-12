//
//  debug.h
//
//  Created by youknowone on 12. 10. 2..
//  Copyright 2012 youknowone.org All rights reserved.
//

/*	Debug tools
 *
 *	To take benefit of this feature, do one of below:
 *	1. Insert #define DEBUG 1
 *  2. Add compiler option DDEBUG
 *  
 *  Defile options if you don't like default
 *  1. DEBUG_WITH_FILE for __FILE__ macro
 *  2. DEBUG_WITH_LINE for __LINE__ macro
 *  3. DEBUG_WITH_TIME for runtime timestamp
 *  4. DEBUG_NEWLINE for default newline insertion
 *  5. DEBUG_LOGLEVEL for dlog trigger level
 *  6. DEBUG_LOGTEST(LV) for dlog trigger test. Default is LV >= DEBUG_LOGLEVEL
 *  7. DEBUG_ASSERT for real assert in dassert
 *  8. DEBUG_PRINTF for printf function
 *  9. DEBUG_USE_NSLOG for auto NSLog flag for objc
 */

#include <stdio.h>

#ifndef DEBUG_WITH_FILE
    #define DEBUG_WITH_FILE 1
#endif

#ifndef DEBUG_WITH_LINE
    #define DEBUG_WITH_LINE 1
#endif

#ifndef DEBUG_NEWLINE
    #define DEBUG_NEWLINE 1
#endif

#ifndef DEBUG_LOGLEVEL
    #define DEBUG_LOGLEVEL 1
#endif

#ifndef DEBUG_LOGTEST
    #define DEBUG_LOGTEST(LV) ((LV) >= DEBUG_LOGLEVEL)
#endif

#ifndef DEBUG_ASSERT
    #define DEBUG_ASSERT 1
#endif

#ifndef DEBUG_USE_NSLOG
    #define DEBUG_USE_NSLOG 1
#endif

#ifndef DEBUG_WITH_TIME
    #if __OBJC__ && DEBUG_USE_NSLOG
        #define DEBUG_WITH_TIME 0
    #else
        #define DEBUG_WITH_TIME 1
    #endif
#endif

#if __OBJC__ && DEBUG_USE_NSLOG
    #import <Foundation/Foundation.h>
    #define DEBUG_DEFAULT_PRINT NSLog
#else
    #define DEBUG_DEFAULT_PRINT printf
#endif

#ifndef DEBUG_PRINTF
    #define DEBUG_PRINTF DEBUG_DEFAULT_PRINT
#endif

#ifndef NO_DEBUG
	#if defined(DEBUG) || defined(CONFIG_Debug) || defined(CONFIG_Development)
		#define _DEBUG 1
	#else
		#define _DEBUG 0
	#endif
#endif

#if DEBUG_WITH_TIME
    #include <time.h>
#endif

#if DEBUG_WITH_TIME
    #define __dprint_time { \
        char timestr[20];   \
        time_t timestamp;   \
        struct tm* timeinfo;\
        time(&timestamp);   \
        timeinfo = localtime(&timestamp); \
        strftime(timestr, 20, "%d %H:%M:%S", timeinfo); \
        printf("%s ", timestr); \
    }
#else
    #define __dprint_time
#endif

#if DEBUG_WITH_FILE || DEBUG_WITH_LINE
    #if DEBUG_WITH_FILE && DEBUG_WITH_LINE
        #define __dprint_file_line { printf("[%16s:%4d] ", __FILE__, __LINE__); }
    #elif DEBUG_WITH_FILE
        #define __dprint_file_line { printf("[%16s] ", __FILE__); }
    #elif DEBUG_WITH_LINE
        #define __dprint_file_line { printf("ln%4d ", __LINE__); }
    #else
        #define __dprint_file_line
    #endif
#endif

#if DEBUG_ASSERT
    #define __do_assert(COND) assert(COND)
#else
    #define __do_assert(COND)
#endif

#if _DEBUG
    #define dprintfnoln(...)        { __dprint_time __dprint_file_line DEBUG_PRINTF(__VA_ARGS__); }
    #define dassertnoln(COND, ...)  { if (!(COND)) { dprintfnoln(__VA_ARGS__); __do_assert(COND);  } }
    #define dlognoln(LEVEL, ...)    { if (DEBUG_LOGTEST(LEVEL)) dprintfnoln(__VA_ARGS__); }

    #define dprintfln(...)          { dprintfnoln(__VA_ARGS__); puts(""); }
    #define dassertln(COND, ...)    { if (!(COND)) { dprintfln(__VA_ARGS__); __do_assert(COND);  } }
    #define dlogln(LEVEL, ...)      { if (DEBUG_LOGTEST(LEVEL)) dprintfln(__VA_ARGS__); }
#else
    #define dprintfnoln(...)
    #define dassertnoln(COND, ...)
    #define dlognoln(LEVEL, ...)

    #define dprintfln(...)
    #define dassertln(COND, ...)
    #define dlogln(LEVEL, ...)
#endif

#define dprintfln(...) { dprintfnoln(__VA_ARGS__); puts(""); }


#if DEBUG_NEWLINE
    #define dprintf(...)            dprintfln(__VA_ARGS__)
    #define dassert(COND, ...)      dassertln(COND, __VA_ARGS__)
    #define dlog(LEVEL, ...)        dlogln(LEVEL, __VA_ARGS__)
#else
    #define dprintf(...)            dprintfnoln(__VA_ARGS__)
    #define dassert(COND, ...)      dassertnoln(COND, __VA_ARGS__)
    #define dlog(LEVEL, ...)        dlognoln(LEVEL, __VA_ARGS__)
#endif

