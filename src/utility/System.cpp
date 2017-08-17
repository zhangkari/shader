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

uint64_t System :: moment() {
    struct timeval tv;
    if (gettimeofday(&tv, NULL) < 0) {
        printf("Failed in System::current\n");
        exit(1);
        return 0;
    }
    return tv.tv_sec * 1000 * 1000 + tv.tv_usec;
}

char* System :: loadTextFile(const char* path) {
    if (NULL == path) {
        return NULL;
    }

    FILE* fp = fopen(path, "r");
    if (NULL == fp) {
        return NULL;
    }

    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    char* buf = (char *)calloc(1, size + 1);
    if (NULL == buf) {
        fclose(fp);
        return NULL;
    }
    rewind(fp);
    fread(buf, 1, size, fp); 
    fclose(fp);
    return buf;
}
