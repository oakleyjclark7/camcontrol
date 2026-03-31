add_library(camera)

target_sources(camera
	PRIVATE "src/streaming.cpp"
	PRIVATE "src/find_faces.cpp"
)
target_include_directories(camera
	PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include
)
find_package(OpenCV REQUIRED)
target_link_libraries(camera
	PUBLIC opencv_videoio
	PUBLIC opencv_objdetect
	PUBLIC files
)

if(BUILD_CAMERA_STREAMING_EXAMPLE)
	add_executable(camera_streaming_example)
	target_sources(camera_streaming_example
		PRIVATE "camera_streaming_example.cpp"
	)
	target_include_directories(camera_streaming_example
		PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include
	)
	target_link_libraries(camera_streaming_example
		PRIVATE camera
		PRIVATE opencv_videoio
		PRIVATE opencv_highgui
	)
	copy_resources_to_target(camera_streaming_example)
endif()

if(BUILD_FACE_DETECTION_EXAMPLE)
	add_executable(face_detection_example)
	target_sources(face_detection_example
		PRIVATE "face_detection_example.cpp"
	)
	target_include_directories(face_detection_example
		PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include
	)
	target_link_libraries(face_detection_example
		PRIVATE camera
		PRIVATE opencv_videoio
		PRIVATE opencv_highgui
	)
	copy_resources_to_target(face_detection_example)
endif()