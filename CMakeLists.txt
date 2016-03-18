PROJECT(ParticleSystem)

cmake_minimum_required(VERSION 3.0)
add_definitions("-Wall -std=c++11")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/external/FUJI-Math/include)

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

FILE(GLOB_RECURSE neighbor_searches
	${CMAKE_SOURCE_DIR}/include/ParticleSystem/neighbor_search/*.hpp
	${CMAKE_SOURCE_DIR}/include/ParticleSystem/neighbor_search/*.h
	${CMAKE_SOURCE_DIR}/src/neighbor_search/*.cpp
)

FILE(GLOB_RECURSE types
	${CMAKE_SOURCE_DIR}/include/ParticleSystem/type/*.hpp
	${CMAKE_SOURCE_DIR}/include/ParticleSystem/type/*.h
	${CMAKE_SOURCE_DIR}/src/type/*.cpp
)

FILE(GLOB_RECURSE external_math_sources
	${CMAKE_SOURCE_DIR}/external/FUJI-Math/src/type/*.cpp
)


SOURCE_GROUP(particle_system FILES ${particle_systems})
SOURCE_GROUP(particle FILES ${particles})
SOURCE_GROUP(neighbor_search FILES ${neighbor_searches})
SOURCE_GROUP(type FILES ${types})

SOURCE_GROUP(external_math FILES ${external_math_sources})

add_library(particle_system STATIC
	${particle_systems}
	${particles}
	${neighbor_searches}
	${types}
	${external_math_sources}
)

add_subdirectory(examples)