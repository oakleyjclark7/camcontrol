add_executable(blink_test)
target_sources(blink_test
    PRIVATE blink_test.cpp
)
target_link_libraries(blink_test
    pico_stdlib
)
pico_add_extra_outputs(blink_test)