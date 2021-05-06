# project specific logic here.

cmake_minimum_required (VERSION 3.19)

project (C_Dynamics_Examples)

find_package(PkgConfig REQUIRED)
find_package( OpenCV REQUIRED )

pkg_search_module(UUID REQUIRED uuid)

include_directories(~/Hamiltonian-Mathematics/)
include_directories(~/C-Geometry/)
include_directories(~/C-Dynamics)

# Add source to this project's executable.

add_executable(two_body_simulation two_body/source.cpp includes.hpp)

target_link_libraries(two_body_simulation ${UUID_LIBRARIES} ${OpenCV_LIBS})