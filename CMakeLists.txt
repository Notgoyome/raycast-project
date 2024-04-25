cmake_minimum_required(VERSION 3.27)
project(raytracer)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_custom_target(
        BuildPrimitives ALL
        COMMAND make -C ${CMAKE_SOURCE_DIR}/lib/primitives
        COMMENT "Building primitives libraries"
)

add_executable(raytracer
        include/Main.hpp
        src/main/main.cpp
        include/Ray.hpp
        src/math/Point3D.cpp
        src/math/Vector3D.cpp
        src/main/main.cpp
        src/main/parser/Configuration.cpp
        src/main/manager/pluginManager.hpp
        src/main/manager/pluginManager.cpp
        src/lights/ILight.hpp
        src/lights/ALight.hpp
        src/lights/ALight.cpp
        src/cameras/ICamera.hpp
        src/cameras/ACamera.hpp
        src/cameras/ACamera.cpp
        src/main/renderer/Renderer.cpp
        src/scenes/AScene.cpp
        src/scenes/IScene.hpp
        src/shapes/AShape.cpp
        src/transformations/ATransform.cpp
        src/shapes/AShape.hpp
        src/scenes/AScene.hpp
        src/transformations/ATransform.hpp
        src/shapes/IShape.hpp
        src/transformations/ITransform.hpp
        src/materials/IMaterial.hpp
        src/materials/AMaterial.hpp
        src/materials/AMaterial.cpp
        include/Configuration.hpp
        include/INode.hpp
        include/parsing.hpp
        include/Point3D.hpp
        include/Renderer.hpp
        include/Vector3D.hpp)

target_link_libraries(raytracer sfml-graphics sfml-window sfml-system)
add_dependencies(raytracer BuildPrimitives)
