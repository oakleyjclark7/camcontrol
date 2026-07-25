cmake_minimum_required(VERSION 3.8)

include(pico_sdk_import.cmake)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.2.0)
set(toolchainVersion 14_2_Rel1)
set(picotoolVersion 2.2.0-a4)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================

project(camcontrol-firmware C CXX ASM)

# Set this to where the pico sdk is installed on your computer
set(PICO_SDK_PATH "C:/Users/OakleyClark/.pico-sdk/sdk/2.2.0")
set(PICO_BOARD pico)
set(PICO_COMPILER pico_arm_cortex_m0plus_gcc)

pico_sdk_init()

# Test executable to blink the default LED
add_subdirectory(blink_test)

# Build libraries
add_subdirectory(motor_control)
add_subdirectory(comms)