PROJECT(ParticleSystem)

cmake_minimum_required(VERSION 3.0)
add_definitions("-Wall -std=c++11")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
include_directories(${CMAKE_SOURCE_DIR}/include)

FILE(GLOB_RECURSE headers
	${CMAKE_SOURCE_DIR}/include/*.hpp
)

FILE(GLOB_RECURSE particles
	${CMAKE_SOURCE_DIR}/src/particle/*.cpp
)

FILE(GLOB_RECURSE types
	${CMAKE_SOURCE_DIR}/src/type/*.cpp
)

SOURCE_GROUP(header FILES ${headers})
SOURCE_GROUP(particle FILES ${particles})
SOURCE_GROUP(type FILES ${types})

add_library(particle_system STATIC
	${headers}
	${particles}
	${types}
)

add_subdirectory(examples)