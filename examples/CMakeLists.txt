# project specific logic here.

cmake_minimum_required (VERSION 3.19)

project (C_Dynamics_Examples)

find_package( OpenCV REQUIRED )

include_directories(~/Hamiltonian-Mathematics/)
include_directories(~/C-Geometry/)
include_directories(~/C-Dynamics)

# Add source to this project's executable.

add_executable(two_body_simulation two_body/source.cpp)

target_link_libraries(two_body_simulation ${OpenCV_LIBS})