SET(lib_jpg_dir ../../libs/jpeg-9a)
SET(lib_png_dir ../../libs/libpng-1.6.17)
SET(include_dir ../../include)
INCLUDE_DIRECTORIES(${lib_jpg_dir} ${lib_png_dir} ${include_dir})

AUX_SOURCE_DIRECTORY(. src_files)
ADD_LIBRARY(libimage ${src_files})
TARGET_LINK_LIBRARIES(libimage png jpeg)
