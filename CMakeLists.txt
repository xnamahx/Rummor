cmake_minimum_required(VERSION 3.0)

include(${CMAKE_CURRENT_SOURCE_DIR}/../../min-api/script/min-pretarget.cmake)

include_directories( 
	"${C74_INCLUDES}"
)

include_directories(
        "${CMAKE_CURRENT_SOURCE_DIR}/VultModules/src/"
)

set(VULT_SRC
       VultModules/src/VultEngine.cpp
       VultModules/src/vultin.c
       )

add_library(VultTrummorLib ${VULT_SRC} )

add_library( 
	${PROJECT_NAME} 
	MODULE
	${PROJECT_NAME}.cpp
)

target_link_libraries(${PROJECT_NAME} VultTrummorLib)

include(${CMAKE_CURRENT_SOURCE_DIR}/../../min-api/script/min-posttarget.cmake)
