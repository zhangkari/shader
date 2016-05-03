/************************************
 * file name:	Log.h
 * description:	define log utility 
 * author:		kari.zhang
 * date:		2016-4-29
 ***********************************/

#ifndef LOG__H__
#define LOG__H__

#include <stdio.h>

#ifdef DEBUG
#define print_log(...) printf(...)
#else 
#define rpint_log(fmt, args...)
#endif

class Log {
	public:
		static void e(...) {
//			print_log(...);
		}

		static void d(...) {
//			print_log(...);
		}
};

#endif
