PROJECT(shader)
CMAKE_MINIMUM_REQUIRED (VERSION 2.6)

# release
SET(CMAKE_BUILD_TYPE RELEASE)
SET(CMAKE_C_FLAGS "-O2")

# all the header files dir
SET(libs_dir ../libs)
SET(include_dir ../include)
SET(shdrtest_dir ../src/test)

INCLUDE_DIRECTORIES(${libs_dir} ${include_dir} ${shdrtest_dir})

# libjpg
#SET(libjpg_dir ../libs/jpeg-9a)
#ADD_SUBDIRECTORY(${libjpg_dir} ./libs)

# librenderer
SET(librenderer_dir ../src/renderer)
ADD_SUBDIRECTORY(${librenderer_dir} ./renderer)

# libshadertest
SET(libshdrtest_dir ../src/test)
ADD_SUBDIRECTORY(${libshdrtest_dir} ./test)

# project src files
AUX_SOURCE_DIRECTORY(../src src_files)

# source directory
SET(src_dir ../src)

# shader
ADD_EXECUTABLE(shader ${src_dir}/main.cpp)
#TARGET_LINK_LIBRARIES(shader libjpg librenderer)
TARGET_LINK_LIBRARIES(shader librenderer)
