PROJECT(ParticleSystem)

add_executable(fine_particle_demo fine_particle_demo.cpp)
target_link_libraries( fine_particle_demo
	particle_system
)

add_executable(fluid_particle_demo fine_particle_demo.cpp)
target_link_libraries( fluid_particle_demo
	particle_system
)

add_executable(blood_demo blood_demo.cpp)
target_link_libraries( blood_demo
	particle_system
)