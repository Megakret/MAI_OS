cmake_minimum_required(VERSION 3.16)
project(MAI_OS)
#Дать clangd знать о cmake файлу
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "-pthread")
#хедеры
set(INCLUDES ${CMAKE_SOURCE_DIR}/includes)

add_subdirectory(os_wrapper)
add_subdirectory(lab2_var18)
