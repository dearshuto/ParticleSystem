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

FILE(GLOB_RECURSE particle_managers
	${CMAKE_SOURCE_DIR}/include/ParticleSystem/particle_manager/*.hpp
	${CMAKE_SOURCE_DIR}/include/ParticleSystem/particle_manager/*.h
	${CMAKE_SOURCE_DIR}/src/particle_manager/*.cpp
)

FILE(GLOB_RECURSE solvers
	${CMAKE_SOURCE_DIR}/include/ParticleSystem/solver/*.hpp
	${CMAKE_SOURCE_DIR}/include/ParticleSystem/solver/*.h
	${CMAKE_SOURCE_DIR}/src/solver/*.cpp
)

FILE(GLOB_RECURSE surface_constructions
	${CMAKE_SOURCE_DIR}/include/ParticleSystem/surface_construction/*.hpp
	${CMAKE_SOURCE_DIR}/include/ParticleSystem/surface_construction/*.h
	${CMAKE_SOURCE_DIR}/src/surface_construction/*.cpp
)

FILE(GLOB_RECURSE collision_dispatchers
	${CMAKE_SOURCE_DIR}/include/ParticleSystem/collision_dispatcher/*.hpp
	${CMAKE_SOURCE_DIR}/include/ParticleSystem/collision_dispatcher/*.h
	${CMAKE_SOURCE_DIR}/src/collision_dispatcher/*.cpp
)

FILE(GLOB_RECURSE types
	${CMAKE_SOURCE_DIR}/include/ParticleSystem/type/*.hpp
	${CMAKE_SOURCE_DIR}/include/ParticleSystem/type/*.h
	${CMAKE_SOURCE_DIR}/src/type/*.cpp
)

FILE(GLOB_RECURSE bb_algorithms
	${CMAKE_SOURCE_DIR}/include/ParticleSystem/bb_algorithm/*.hpp
	${CMAKE_SOURCE_DIR}/include/ParticleSystem/bb_algorithm/*.h
	${CMAKE_SOURCE_DIR}/src/bb_algorithm/*.cpp
)

FILE(GLOB_RECURSE external_math_sources
	${CMAKE_SOURCE_DIR}/external/FUJI-Math/src/type/*.cpp
)


SOURCE_GROUP(particle_system FILES ${particle_systems})
SOURCE_GROUP(particle FILES ${particles})
SOURCE_GROUP(particle_manager FILES ${particle_managers})
SOURCE_GROUP(solver FILES ${solvers})
SOURCE_GROUP(surface_construction FILES ${surface_constructions})
SOURCE_GROUP(collision_dispatcher FILES ${collision_dispatchers})
SOURCE_GROUP(type FILES ${types})
SOURCE_GROUP(bb_algorithm FILES ${bb_algorithms})

SOURCE_GROUP(external_math FILES ${external_math_sources})

add_library(particle_system STATIC
	${particle_systems}
	${particles}
	${particle_managers}
	${solver}
	${surface_constructions}
	${collision_dispatchers}
	${types}
	${bb_algorithms}
	${external_math_sources}
)

add_subdirectory(examples)