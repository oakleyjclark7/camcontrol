add_library(files INTERFACE)
target_include_directories(files
    INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include
)
target_link_libraries(files
    INTERFACE Qt6::Core
)