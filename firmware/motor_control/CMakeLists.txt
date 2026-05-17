add_library(motor_control)
target_sources(motor_control
    PRIVATE src/motor_control.cpp
)
target_include_directories(motor_control
	PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include
)
target_link_libraries(motor_control
    pico_stdlib
    hardware_pwm
)

# test executable
add_executable(motor_test)
target_sources(motor_test
    PRIVATE src/motors_test.cpp
)
target_link_libraries(motor_test
    PUBLIC motor_control
    hardware_pwm
)
pico_add_extra_outputs(motor_test)