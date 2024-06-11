include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../common)

file(GLOB 5GAKA_src_files
    ${CMAKE_CURRENT_SOURCE_DIR}/../common/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

add_library (SECU STATIC
	${5GAKA_src_files})
