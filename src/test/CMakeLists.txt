SET(include_dir ../../include)
INCLUDE_DIRECTORIES(${include_dir})

AUX_SOURCE_DIRECTORY(. src_files)
ADD_LIBRARY(libshdrtest ${src_files})
#TARGET_LINK_LIBRARIES(libvmbase libminiz)
