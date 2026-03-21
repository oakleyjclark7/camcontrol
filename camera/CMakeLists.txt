add_library(camera)

target_sources(camera
	PRIVATE "src/streaming.cpp"
)
target_include_directories(camera
	PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include
)
find_package(OpenCV REQUIRED)
target_link_libraries(camera
	PUBLIC opencv_videoio
)

if(BUILD_CAMERA_STREAMING_EXAMPLE)
	add_executable(camera_streaming_example)
	target_sources(camera_streaming_example
		PRIVATE "src/camera_streaming_example.cpp"
	)
	target_include_directories(camera_streaming_example
		PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include
	)
	target_link_libraries(camera_streaming_example
		PRIVATE camera
		PRIVATE opencv_videoio
		PRIVATE opencv_highgui
	)
endif()