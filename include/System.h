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
		 * return current time in milisecond
		 */
		static uint64_t current();

};

#endif
