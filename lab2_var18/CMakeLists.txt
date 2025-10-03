add_executable(task task.c)
target_include_directories(task PRIVATE ${INCLUDES})
target_link_libraries(task PRIVATE os)
