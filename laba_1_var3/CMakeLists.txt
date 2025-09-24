cmake_minimum_required(VERSION 3.16)
project(Laba1_Var3)
#Дать clangd знать о cmake файлу
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_COMPILER )
    message("CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")
add_executable(main parent.c)
add_executable(child task.c) 
#хедеры
set(INCLUDES ${CMAKE_SOURCE_DIR}/includes)
target_include_directories(child PRIVATE ${INCLUDES})
target_include_directories(main PRIVATE ${INCLUDES})
#линковка
add_subdirectory(os_wrapper)
target_link_libraries(main PRIVATE os)
target_link_libraries(child PRIVATE os)