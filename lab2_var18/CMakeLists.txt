add_executable(task task.cpp)
target_include_directories(task PRIVATE ${INCLUDES})
target_link_libraries(task PRIVATE threads)
