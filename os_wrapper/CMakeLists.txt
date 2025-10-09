add_library(threads ${CMAKE_CURRENT_SOURCE_DIR}/threads_unix.cpp)
target_include_directories(threads PRIVATE ${INCLUDES})
