/******************************
 * file name:	Bitmap.h
 * description:	define Bitmap 
 * author:		kari.zhang
 * date:		2016-04-29
 *****************************/

#ifndef BITMAP__H__
#define BITMAP__H__

/*
 * pixel color format
 */
typedef enum {
	GRAY   = 1,			// gray scale
	RGB16  = 2,			// rgb 5-6-6
	RGB24  = 3,			// rgb 8-8-8
	RGBA32 = 4			// rgba 8-8-8-8
} PixFmt;

class Bitmap {
	public:
		static Bitmap* create(int width, int height, PixFmt fmt);
		static Bitmap* load(const char* path);
		bool save(const char* path);
		void recycle();
		int getWidth();
		int getHeight();
		PixFmt getFmt();
		const char* const getBlock();
		~Bitmap();

	protected:
		int mWidth;
		int mHeight;
		PixFmt mFmt;
		char *mBlock;
	
	private:
		// forbid extending me
		Bitmap(int width, int height, PixFmt fmt);

		// load the specified file
		static Bitmap* readJpg(const char *path);
		static Bitmap* readPng(const char *path);

		bool writeJpg(const char *path);
		bool writePng(const char* path);
};

#endif
