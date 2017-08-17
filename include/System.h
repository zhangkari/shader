/************************************
 * file name:	System.h
 * description:	define system utility 
 * author:		kari.zhang
 * date:		2016-5-18
 ***********************************/

#ifndef SYSTEM__H__
#define SYSTEM__H__

#include <stdint.h>

class System {

	public:
		/*
		 * return current time in millisecond
		 */
		static uint64_t current();

		/*
		 * return current time in microsecond
		 */
		static uint64_t moment();

        /*
         * Remember call free() to release memory ! 
         */
        static char* loadTextFile(const char* path);
};

#endif
