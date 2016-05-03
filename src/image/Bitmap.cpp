/******************************
 * file name:	Bitmap.cpp
 * description:	implement Bitmap 
 * author:		kari.zhang
 * date:		2016-04-29
 *****************************/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "jpeglib.h"
#include "png.h"
#include "Bitmap.h"
#include "Log.h"

Bitmap :: Bitmap(int width, int height, PixFmt fmt) {

	assert (width > 0 && height > 0);

	mWidth = width;
	mHeight = height;
	mFmt = fmt;
	mBlock = (char *)calloc(1, width * height * fmt);
	assert(NULL != mBlock);
}

void Bitmap :: recycle() {
	if (NULL != mBlock) {
		free (mBlock);
		mBlock = NULL;
	}
}

int Bitmap :: getWidth() {
	return mWidth;
}

int Bitmap :: getHeight() {
	return mHeight;
}

PixFmt Bitmap :: getFmt() {
	return mFmt;
}

const char * const Bitmap :: getBlock() {
	return mBlock;
}

static const char* getFilePostfix (const char* path) {

	if (NULL == path) {
		return NULL;
	}

	int len = strlen(path);
#define MIN_POSTFIX_LEN 5
	if (len < MIN_POSTFIX_LEN) {
		return NULL;
	}

	while (len--) {
		if ( *(path + len) == '.') {
			return path + len + 1;
		}
	}
}

/**
 * Load image
 * Parameters:
 *      path:   input path 
 * Return:
 *           0  OK
 *          -1  ERROR
 */
Bitmap* Bitmap :: load(const char *path) 
{
	if (path == 0) {
		return NULL;
	}

    const char *postfix = getFilePostfix (path);
    if (NULL == postfix) {
        printf("Failed getFilePostfix in loadImage\n");
        return NULL;
    }

	if (strcasecmp (postfix, "jpg") == 0 ||
			strcasecmp (postfix, "jpeg") == 0) {
		return readJpg (path);
	}
    else if (strcasecmp (postfix, "png") == 0) {
        return readPng (path);
    }
    else {
        printf("Invalid postfix name (%s) in loadImage\n", postfix);
        return NULL;
    }
}


/**
 * Save image
 * Parameters:
 *      path:   output path 
 * Return:
 *          true  OK
 *          false  ERROR
 */
bool Bitmap :: save(const char *path) 
{
	if (0 == path) {
		return false;
	}

    const char *postfix = getFilePostfix (path);
    if (NULL == postfix) {
        printf("Failed getFilePostfix in saveImage\n");
        return false;
    }

	if (strcasecmp (postfix, "jpg") == 0 ||
			strcasecmp (postfix, "jpeg") == 0) {
		return writeJpg (path);
	}
    else if (strcasecmp (postfix, "png") == 0) {
        return writePng (path);
    }
    else {
        printf("Invalid postfix name (%s) in saveImage\n", postfix);
        return false;
    }
}


/**
 * Read jpeg file to memory
 * Return:
 *		 0 OK
 *		-1 error
 */
Bitmap* Bitmap :: readJpg(const char *path)
{
	if (0 == path) {
		return NULL;
	}
    FILE *fp = fopen (path, "rb");
    if (NULL == fp) {
        printf("Failed open %s\n", path);
        return NULL;
    }

    struct jpeg_decompress_struct jds;
    struct jpeg_error_mgr jerr;
    jds.err = jpeg_std_error (&jerr);
    jpeg_create_decompress (&jds);
    jpeg_stdio_src (&jds, fp);
    jpeg_read_header (&jds, TRUE);

    printf("[%s %d x %d %d]\n", path, jds.image_width, jds.image_height, jds.num_components);

	PixFmt bpp = RGBA32;
	switch (jds.num_components) {
		case 3:
			bpp = RGB24;
			break;

		case 4:
			bpp = RGBA32;
	}

	Bitmap *bmp = new Bitmap(jds.image_width, jds.image_height, bpp);
    assert (NULL != bmp);

    jpeg_start_decompress (&jds); 
    JSAMPROW row_pointer[1];
    while (jds.output_scanline < jds.output_height) {
        row_pointer[0] = (JSAMPROW)(bmp->mBlock + (jds.output_height - jds.output_scanline - 1) * jds.image_width * jds.num_components);
        jpeg_read_scanlines (&jds, row_pointer, 1);
    }
    jpeg_finish_decompress (&jds);
    jpeg_destroy_decompress (&jds);
    fclose (fp);

    return bmp;
}

/**
 * Write jpeg data from memory to file
 * Return:
 *		 0 OK
 *		-1 error
 */
bool Bitmap :: writeJpg(const char *path)
{
	if (0 == path || 0 == mBlock) {
		return false;
	}

    FILE *fp = fopen (path, "wb");
    if (NULL == fp) {
        return false;
    }

    struct jpeg_compress_struct jcs;
    struct jpeg_error_mgr jerr;
    jcs.err = jpeg_std_error (&jerr);
    jpeg_create_compress (&jcs);
    jpeg_stdio_dest (&jcs, fp);
    jcs.image_width = mWidth;
    jcs.image_height = mHeight;

#ifdef _DEBUG_ 
    assert (mFmt >= GRAY && mFmt <= RGBA32);
    assert (mFmt != RGB16);
#endif

    int colorSpace = JCS_GRAYSCALE;
    int components = mFmt;
    if (components >= 3) {
        components = 3;
        colorSpace = JCS_RGB;
    }
    jcs.input_components = components;
    jcs.in_color_space = (J_COLOR_SPACE)colorSpace;

    jpeg_set_defaults (&jcs);
#define QUALITY 80
    jpeg_set_quality (&jcs, QUALITY, TRUE);
    jpeg_start_compress (&jcs, TRUE);
    JSAMPROW row_pointer[1];
    int row_stride = mWidth * mFmt;

    while ( jcs.next_scanline < jcs.image_height ) {
        row_pointer[0] = (JSAMPROW)(mBlock + jcs.next_scanline * row_stride);
        jpeg_write_scanlines (&jcs, row_pointer, 1);
    }
    jpeg_finish_compress (&jcs);
    jpeg_destroy_compress (&jcs);
    fclose (fp);
    return true;
}



/*
 * Read png file and store in memory
 * Return:
 *		 0		  OK
 *      negative  ERROR
 */
Bitmap* Bitmap :: readPng(const char *path)
{
	if (0 == path) {
		return NULL;
	}
    FILE *fp = fopen(path, "rb");
    if (NULL == fp) {
		return NULL;
    }

    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, 
            0, 0, 0);
    png_infop info_ptr = png_create_info_struct(png_ptr);
    setjmp(png_jmpbuf(png_ptr));
    png_init_io(png_ptr, fp);
    png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_EXPAND, 0);
    int width = png_get_image_width(png_ptr, info_ptr);
    int height = png_get_image_height(png_ptr,info_ptr);
    int type = png_get_color_type(png_ptr, info_ptr);
    png_bytep *row_pointers = png_get_rows(png_ptr, info_ptr);

    PixFmt bpp = RGBA32;
	switch (type) { 
        case PNG_COLOR_TYPE_GRAY:
            bpp = GRAY;
            break;

        case PNG_COLOR_TYPE_RGB:
            bpp = RGB24;
            break;

        case PNG_COLOR_TYPE_RGB_ALPHA:
            bpp = RGBA32;
            break;
    }

    if (bpp == 0) {
        printf("Failed get pixel format");
    }

    printf("[%s %d x %d bpp=%d]\n", path, width, height, bpp);

	Bitmap* bmp = new Bitmap(width, height, bpp);
	assert (bmp != 0);

    char *start = bmp->mBlock;
    int i, j;
    for (i = 0; i < height; ++i) {
        memcpy(start, row_pointers[i], width * bpp);
        start += width * bpp;
    }
    png_destroy_read_struct(&png_ptr, &info_ptr, 0);
    fclose(fp);
	return bmp;
}

/**
 * Write png to file
 * Return:
 *		0		 OK
 *		negative ERROR
 */
bool Bitmap :: writePng(const char *path)
{
	if (0 == path) {
		return false;
	}

    FILE *fp;
    png_structp png_ptr;
    png_infop info_ptr;
    png_colorp palette;

    fp = fopen(path, "wb");
    if (NULL == fp) {
        printf("Failed open file\n");
        return false;
    }

    png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (NULL == png_ptr) {
        fclose (fp);
        return false;
    }

    info_ptr = png_create_info_struct(png_ptr);
    if (NULL == info_ptr) {
        fclose (fp);
        png_destroy_write_struct(&png_ptr, NULL);
        return false;
    }

    if (setjmp(png_jmpbuf(png_ptr))) {
        printf("write file occur error");
        fclose(fp);
        png_destroy_write_struct(&png_ptr, &info_ptr);
        return false;
    }

    int form = PNG_COLOR_TYPE_RGB_ALPHA;
    int depth = 8;
    switch (mFmt) {
        case RGBA32:
            form = PNG_COLOR_TYPE_RGBA;
            break;

        case RGB24:
            form = PNG_COLOR_TYPE_RGB;
            break;

        case GRAY:
            form = PNG_COLOR_TYPE_GRAY;
            depth = 1;
            break;
    }

    png_init_io(png_ptr, fp);
    png_set_IHDR(png_ptr, info_ptr, mWidth, mHeight, depth, form, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
    png_write_info(png_ptr, info_ptr);
    png_bytep row_pointers[mHeight];
    int k;
    for (k = 0; k < mHeight; ++k) {
        row_pointers[k] = (png_bytep)mBlock + k * mWidth * mFmt;
    }
    png_write_image(png_ptr, row_pointers);
    png_write_end(png_ptr, info_ptr);
    png_destroy_write_struct(&png_ptr, &info_ptr);
    fclose (fp);

    return true;
}

