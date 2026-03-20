add_library(camera)

target_sources(camera
	PRIVATE "src/camera_image.cpp"
)

target_include_directories(camera
	PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include
)

find_package(OpenCV REQUIRED)

target_link_libraries(camera
	PRIVATE opencv_videoio
)