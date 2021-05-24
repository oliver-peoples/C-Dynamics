# project specific logic here.

cmake_minimum_required (VERSION 3.19)

project (C_Dynamics_Examples)

find_package( OpenCV REQUIRED )

include_directories(~/Hamiltonian-Mathematics/)
include_directories(~/C-Geometry)
include_directories(~/C-Dynamics)

# Add source to this project's executable.

add_executable(two_body two_body/source.cpp)
add_executable(two_body_viz two_body_viz/source.cpp)
add_executable(three_body three_body/source.cpp)
add_executable(three_body_viz three_body_viz/source.cpp)
add_executable(soft_body soft_body/source.cpp)
add_executable(soft_body_viz soft_body_viz/source.cpp)

target_link_libraries(two_body_viz ${OpenCV_LIBS})
target_link_libraries(three_body_viz ${OpenCV_LIBS})
target_link_libraries(soft_body_viz ${OpenCV_LIBS})