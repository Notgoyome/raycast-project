//
// Created by Guillaume Tran on 25/04/2024.
//

#ifndef B_OOP_400_MPL_4_1_RAYTRACER_ROBIN_GLAUDE_SPHERE_HPP
#define B_OOP_400_MPL_4_1_RAYTRACER_ROBIN_GLAUDE_SPHERE_HPP

#include "../../../src/shapes/AShape.hpp"
#include "../../materials/IMaterial.hpp"
#include "../../../include/Maybe.hpp"
#include "Ray.hpp"
#include <cmath>
#include <map>
#include <memory>

namespace ray {

    class Sphere : public ray::AShape {
    private:
        double radius = -1;
        Math::Point3D center;

        void setRadius();
        void setPosition();
    public:
        // CONSTR DESTRUCT
        Sphere() = default;
        ~Sphere() override = default;

        // INIT
        void initValues() override;

        // RUNTIME
        Maybe<Math::Point3D> hit(const ray::Ray& ray) const override;
        Math::Vector3D getNormale(const Math::Point3D& point, const ray::Ray& camRay) const override;
        Math::Vector2D getUVMapping(Math::Vector3D coords) const override;
    };

}

extern "C" ray::INode *create(const std::map<std::string, std::string> &attributes);

#endif //B_OOP_400_MPL_4_1_RAYTRACER_ROBIN_GLAUDE_SPHERE_HPP
