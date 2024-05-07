cmake_minimum_required(VERSION 3.20)
project(raytracer)

set(CMAKE_SHARED_LIBRARY_SUFFIX ".so")

set(CMAKE_CXX_STANDARD 20)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -Wall -Wextra -Werror -pedantic -Wmissing-include-dirs -g3 -O0")
endif()

include_directories(include)

add_executable(raytracer
        src/main/main.cpp
        include/Ray.hpp
        src/math/Point3D.cpp
        src/math/Vector3D.cpp
        src/main/main.cpp
        src/scenes/IScene.hpp
        src/math/Vector2D.cpp
        src/math/Rectangle3D.cpp
        src/scenes/base/Scene.cpp
        src/utils/getClosest.cpp
        src/utils/ANode.cpp
        src/utils/ANode.hpp
        src/cameras/base/Camera.cpp
        src/main/renderer/Renderer.cpp
        src/cameras/ICamera.hpp
        src/main/parser/NodeBuilder.hpp
        src/main/parser/NodeBuilder.cpp
)

target_link_libraries(raytracer sfml-graphics sfml-window sfml-system config++)

# Plugins

set(MATH_SOURCES
        src/math/Point3D.cpp
        src/math/Vector3D.cpp
        src/math/Vector2D.cpp
        src/math/Rectangle3D.cpp
        src/utils/getClosest.cpp
)

set(SCENE_SOURCES
        src/scenes/base/Scene.cpp
)

set(NODE_SOURCES
        src/utils/ANode.cpp
)

set(LIGHT_SOURCES
        src/lights/ALight.cpp
)

set(MATERIAL_SOURCES
        src/materials/AMaterial.cpp
        src/materials/Phong.cpp
)

set(TRANSFORMATION_SOURCES
        src/transformations/ATransform.cpp
)

set(SHAPES_SOURCES
        src/shapes/AShape.cpp
)

set(CAMERA_SOURCES
        src/cameras/ACamera.cpp
        src/cameras/ACamera.hpp
)

add_library(lights_point SHARED ${LIGHT_SOURCES} ${NODE_SOURCES} ${SCENE_SOURCES} ${MATH_SOURCES} src/lights/point/PointLight.cpp)
add_library(lights_directional SHARED ${LIGHT_SOURCES} ${NODE_SOURCES} ${SCENE_SOURCES} ${MATH_SOURCES} src/lights/directional/DirectionalLight.cpp)
add_library(materials_basic SHARED ${MATERIAL_SOURCES} ${NODE_SOURCES} ${SCENE_SOURCES} ${MATH_SOURCES} src/materials/basic/BasicMaterial.cpp)
add_library(transformations_rotation SHARED ${TRANSFORMATION_SOURCES} ${NODE_SOURCES} ${SCENE_SOURCES} ${MATH_SOURCES} src/transformations/rotation/Rotation.cpp)
add_library(transformations_scale SHARED ${TRANSFORMATION_SOURCES} ${NODE_SOURCES} ${SCENE_SOURCES} ${MATH_SOURCES} src/transformations/scale/Scale.cpp)
add_library(transformations_translation SHARED ${TRANSFORMATION_SOURCES} ${NODE_SOURCES} ${SCENE_SOURCES} ${MATH_SOURCES} src/transformations/translation/Translation.cpp)
add_library(shapes_sphere SHARED ${SHAPES_SOURCES} ${NODE_SOURCES} ${SCENE_SOURCES} ${MATH_SOURCES} src/shapes/sphere/Sphere.cpp)
add_library(shapes_plane SHARED ${SHAPES_SOURCES} ${NODE_SOURCES} ${SCENE_SOURCES} ${MATH_SOURCES} src/shapes/plane/Plane.cpp)
add_library(cameras_base SHARED ${CAMERA_SOURCES} ${NODE_SOURCES} ${SCENE_SOURCES} ${MATH_SOURCES} src/cameras/base/Camera.cpp)
add_library(scenes_base SHARED ${SCENE_SOURCES} ${NODE_SOURCES} ${SCENE_SOURCES} ${MATH_SOURCES} src/scenes/base/sceneCreate.cpp)
add_library(shapes_cone SHARED ${SHAPES_SOURCES} ${NODE_SOURCES} ${SCENE_SOURCES} ${MATH_SOURCES} src/shapes/cone/Cone.cpp)
add_library(shapes_cylinder SHARED ${SHAPES_SOURCES} ${NODE_SOURCES} ${SCENE_SOURCES} ${MATH_SOURCES} src/shapes/cylinder/Cylinder.cpp)

set_target_properties(lights_point PROPERTIES
        PREFIX ""
        OUTPUT_NAME "lights_point"
        LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/plugins")
set_target_properties(lights_directional PROPERTIES
        PREFIX ""
        OUTPUT_NAME "lights_directional"
        LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/plugins")
set_target_properties(materials_basic PROPERTIES
        PREFIX ""
        OUTPUT_NAME "materials_basic"
        LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/plugins")
set_target_properties(transformations_rotation PROPERTIES
        PREFIX ""
        OUTPUT_NAME "transformations_rotation"
        LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/plugins")
set_target_properties(transformations_scale PROPERTIES
        PREFIX ""
        OUTPUT_NAME "transformations_scale"
        LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/plugins")
set_target_properties(transformations_translation PROPERTIES
        PREFIX ""
        OUTPUT_NAME "transformations_translation"
        LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/plugins")
set_target_properties(shapes_sphere PROPERTIES
        PREFIX ""
        OUTPUT_NAME "shapes_sphere"
        LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/plugins")
set_target_properties(shapes_plane PROPERTIES
        PREFIX ""
        OUTPUT_NAME "shapes_plane"
        LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/plugins")
set_target_properties(cameras_base PROPERTIES
        PREFIX ""
        OUTPUT_NAME "cameras_base"
        LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/plugins")
set_target_properties(shapes_cone PROPERTIES
        PREFIX ""
        OUTPUT_NAME "shapes_cone"
        LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/plugins")
set_target_properties(scenes_base PROPERTIES
        PREFIX ""
        OUTPUT_NAME "scenes_base"
        LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/plugins")
set_target_properties(shapes_cylinder PROPERTIES
        PREFIX ""
        OUTPUT_NAME "shapes_cylinder"
        LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/plugins")

add_dependencies(raytracer
        lights_point
        lights_directional
        materials_basic
        transformations_rotation
        transformations_scale
        transformations_translation
        shapes_sphere
        shapes_plane
        cameras_base
        scenes_base
        shapes_cone
        shapes_cylinder
)
