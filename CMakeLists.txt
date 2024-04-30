cmake_minimum_required(VERSION 3.27)
project(raytracer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -Wall -Wextra -Werror -pedantic -Wmissing-include-dirs")

include_directories(include)

add_custom_target(
        BuildPrimitives ALL
        COMMAND make plugins -C ${CMAKE_SOURCE_DIR}
        COMMENT "Building primitives libraries"
)

add_executable(raytracer
        src/main/main.cpp
        include/Ray.hpp
        src/math/Point3D.cpp
        src/math/Vector3D.cpp
        src/main/main.cpp)

target_link_libraries(raytracer sfml-graphics sfml-window sfml-system config++)
add_dependencies(raytracer BuildPrimitives)
