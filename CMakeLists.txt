project(many_particle_verlet)

set(CMAKE_CXX_STANDARD_11)

set(SOURCE_FILES
  many_particle_verlet.cpp
  many_particle_verlet.h)
add_executable(many_particle_verlet ${SOURCE_FILES})
