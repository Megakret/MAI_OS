add_executable(main_lab1 parent.c)
add_executable(child_lab1 task.c) 
#хедеры
target_include_directories(main_lab1 PRIVATE ${INCLUDES})
target_include_directories(child_lab1 PRIVATE ${INCLUDES})
#линковка
target_link_libraries(main_lab1 PRIVATE os)
target_link_libraries(child_lab1 PRIVATE os)
