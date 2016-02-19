PROJECT(ParticleSystem)

add_executable(particle_system_demo particle_system_demo.cpp)

target_link_libraries( particle_system_demo
	particle_system
)