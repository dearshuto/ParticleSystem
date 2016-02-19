PROJECT(ParticleSystem)

cmake_minimum_required(VERSION 3.0)
add_definitions("-Wall -std=c++11")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
include_directories(${CMAKE_SOURCE_DIR}/include)

FILE(GLOB_RECURSE particle_systems
	${CMAKE_SOURCE_DIR}/include/ParticleSystem/*.hpp
	${CMAKE_SOURCE_DIR}/include/ParticleSystem/*.h
	${CMAKE_SOURCE_DIR}/src/*.cpp
)

FILE(GLOB_RECURSE particles
	${CMAKE_SOURCE_DIR}/include/ParticleSystem/particle/*.hpp
	${CMAKE_SOURCE_DIR}/include/ParticleSystem/particle/*.h
	${CMAKE_SOURCE_DIR}/src/particle/*.cpp
)

FILE(GLOB_RECURSE types
	${CMAKE_SOURCE_DIR}/include/ParticleSystem/type/*.hpp
	${CMAKE_SOURCE_DIR}/include/ParticleSystem/type/*.h
	${CMAKE_SOURCE_DIR}/src/type/*.cpp
)

SOURCE_GROUP(particle_system FILES ${particle_systems})
SOURCE_GROUP(particle FILES ${particles})
SOURCE_GROUP(type FILES ${types})

add_library(particle_system STATIC
	${particle_systems}
	${particles}
	${types}
)

add_subdirectory(examples)