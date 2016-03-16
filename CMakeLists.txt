cmake_minimum_required (VERSION 3.2)

set (PROJ_NAME "Algorithms")

project (${PROJ_NAME})

include_directories(
	${CMAKE_CURRENT_BINARY_DIR}
	include/
	)

set (HEADERS
	)

set (SOURCES
	source/main.cpp
	)

set (ALL_FILES
	 ${HEADERS}
	 ${SOURCES}
	 )

add_executable (${PROJ_NAME} ${ALL_FILES})

source_group (include FILES ${HEADERS})
source_group (source FILES ${SOURCES})

