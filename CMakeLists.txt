cmake_minimum_required(VERSION 3.27)
project(B_OOP_400_MPL_4_1_raytracer_robin_glaude)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(B_OOP_400_MPL_4_1_raytracer_robin_glaude
        include/Main.hpp
        src/main/main.cpp
        include/Ray.hpp
        src/math/Point3D.cpp
        src/math/Vector3D.cpp
        src/main/main.cpp)
