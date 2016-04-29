SET(lib_dir ../../libs)
SET(include_dir ../../include)
INCLUDE_DIRECTORIES(${lib_dir} ${include_dir})

AUX_SOURCE_DIRECTORY(. src_files)
ADD_LIBRARY(libshdrtest ${src_files})
#TARGET_LINK_LIBRARIES(libvmbase libminiz)
