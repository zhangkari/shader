/************************************
 * file name:	Log.h
 * description:	define log utility 
 * author:		kari.zhang
 * date:		2016-4-29
 ***********************************/

#ifndef LOG__H__
#define LOG__H__

#include <stdio.h>

class Log {
	public:
		static void e(...) {
#if 0
			printf(__VA_ARGS__); 
#endif
		}

		static void d(...) {
#if 0
			printf(__VA_ARGS__);
#endif
		}
};

#endif
