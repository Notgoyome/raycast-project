//
// Created by Guillaume Tran on 28/04/2024.
//

#include <iostream>
#include "Configuration.hpp"
#include "Image.hpp"
#include "INode.hpp"
#include "../src/lights/point_light/PointLight.hpp"
#include "../include/Configuration.hpp"
#include "../src/transformations/Transform.hpp"
#include "../src/shapes/sphere/Sphere.hpp"
#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <criterion/new/assert.h>

//make criterion function test hello world

Test(tests, test_hello_world)
{
    cr_assert_eq(1, 1);
}

Test(sphere, test_sphere)
{
    bool test = true;
    std::shared_ptr<Raytracer::Sphere> sphere =
            std::make_shared<Raytracer::Sphere>(1,
                                                Math::Point3D{0, 0, 0});
    std::shared_ptr<ray::Transform> transform = std::make_shared<ray::Transform>(
            Math::Point3D{0, -1.6, 0},
            Math::Vector3D{0, 0, 0},
            Math::Vector3D{1, 1, 1});
    std::shared_ptr<Raytracer::Ray> ray = std::make_shared<Raytracer::Ray>(
            Math::Point3D{0, 0, 0},
            Math::Vector3D{-0.25, 0.84, 0.59});
    sphere->setParent(transform);
    sphere->applyMatrix();
    Maybe<Math::Point3D> point = sphere->hit(*ray);
    if (point.has_value()) {
        if (point.value().X > -0.20 || point.value().X < -0.26)
            test = false;
        if (point.value().Y < -0.80 || point.value().Y > -0.75)
            test = false;
        if (point.value().Z < 0.55 || point.value().Z > 0.60)
            test = false;
    }
    cr_assert_eq(test, true, "ray must hit the sphere");
}