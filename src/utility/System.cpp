/***************************************
 * file name:	System.cpp
 * description:	implement system utility
 * author:		kari.zhang
 * date:		2016-5-18
 **************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "System.h"

uint64_t System :: current() {
	struct timeval tv;
	if (gettimeofday(&tv, NULL) < 0) {
		printf("Failed in System::current\n");
		exit(1);
		return 0;
	}
	return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}
