/************************************
 * file name:	Log.h
 * description:	define log utility 
 * author:		kari.zhang
 * date:		2016-4-29
 ***********************************/

#ifndef LOG__H__
#define LOG__H__

#include <stdarg.h>
#include <stdio.h>

class Log {
    public:
        static void e(const char* format, ...) {
            va_list args;
            va_start(args, format);
            vprintf(format, args);
            va_end(args);
            printf(" %s:%d\n", __FILE__, __LINE__);
        }

        static void d(const char* format, ...) {
#ifdef DEBUG
            va_list args;
            va_start(args, format);
            vprintf(format, args);
            va_end(args);
#endif
        }

    protected:
        static void trace(const char *format, ...) {
            va_list args;
            va_start(args, format);
            vprintf(format, args);
            va_end(args);
        }
};

#endif
