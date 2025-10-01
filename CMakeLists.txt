cmake_minimum_required(VERSION 3.16)
project(MAI_OS)
#Дать clangd знать о cmake файлу
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_COMPILER )
    message("CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")
#хедеры
set(INCLUDES ${CMAKE_SOURCE_DIR}/includes)
#линковка
add_subdirectory(os_wrapper)
add_subdirectory(laba_1_var3)
