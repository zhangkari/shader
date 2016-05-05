AUX_SOURCE_DIRECTORY(. src_files)
ADD_LIBRARY(libimage ${src_files})
TARGET_LINK_LIBRARIES(libimage png jpeg)
