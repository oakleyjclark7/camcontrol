cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

# Use C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(DEBUG)
endif()

project ("camcontrol")

# Copy resources
function(copy_resources_to_target TARGET_NAME)
	add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory 
	${CMAKE_SOURCE_DIR}/resources
	$<TARGET_FILE_DIR:${TARGET_NAME}>/resources 
	COMMENT "Resources will be copied for ${TARGET_NAME}"
	) 
endfunction()

# external libraries
find_package(Qt6Core)

# libraries
add_subdirectory(camera)
add_subdirectory(files)

# First test executable
add_executable (camcontrol)
target_sources(camcontrol
	PRIVATE "main.cpp"
)
target_link_libraries(camcontrol
	PRIVATE camera
)
copy_resources_to_target(camcontrol)

# Optional targets
option(BUILD_CAMERA_STREAMING_EXAMPLE "BUILD_CAMERA_STREAMING_EXAMPLE" ON)
option(BUILD_FACE_DETECTION_EXAMPLE "BUILD_FACE_DETECTION_EXAMPLE" ON)
