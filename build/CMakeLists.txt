#
# project name: shader
#
PROJECT(shader)
CMAKE_MINIMUM_REQUIRED (VERSION 2.6)

# all the header files dir
SET(include_dir ../include)
SET(shdrtest_dir ../src/test)

INCLUDE_DIRECTORIES(${include_dir} ${shdrtest_dir})

# source directory
SET(src_dir ../src)

#libimage
SET(libimage_dir ${src_dir}/image)
ADD_SUBDIRECTORY(${libimage_dir} ./image)

# librenderer
SET(librenderer_dir ${src_dir}/renderer)
ADD_SUBDIRECTORY(${librenderer_dir} ./renderer)

# libshadertest
SET(libshdrtest_dir ${src_dir}/test)
ADD_SUBDIRECTORY(${libshdrtest_dir} ./test)

# project src files
AUX_SOURCE_DIRECTORY(${src_dir} src_files)

# shader
ADD_EXECUTABLE(shader ${src_dir}/main.cpp)
TARGET_LINK_LIBRARIES(shader librenderer)
