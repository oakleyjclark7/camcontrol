# To use this library you will need to configure with
# pico_enable_stdio_usb(my_executable 1)
# pico_enable_stdio_uart(my_executable 0)

add_library(comms)
target_sources(comms
    PRIVATE src/read_command.cpp
)
target_include_directories(comms
    PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include
)
target_link_libraries(comms
    PUBLIC pico_stdlib
)

# Test executable - parsing commands
add_executable(comms_test)
target_sources(comms_test
    PRIVATE src/comms_test.cpp
)
target_link_libraries(comms_test
    PUBLIC comms
    PUBLIC pico_stdlib
)
pico_add_extra_outputs(comms_test)
pico_enable_stdio_usb(comms_test 1)
pico_enable_stdio_uart(comms_test 0)
