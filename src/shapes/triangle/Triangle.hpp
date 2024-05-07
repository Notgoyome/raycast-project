//
// Created by Guillaume Tran on 07/05/2024.
//

#ifndef RAYTRACER_TRIANGLE_HPP
#define RAYTRACER_TRIANGLE_HPP

#include <map>
#include <cmath>
#include "Ray.hpp"
#include "../../../include/Maybe.hpp"
#include "../../scenes/base/Scene.hpp"
#include "../../../src/shapes/AShape.hpp"
#include "../../../include/math/Vector3D.hpp"

namespace ray {
class Triangle : public ray::AShape {

public:
    Triangle() = default;
    ~Triangle() override = default;

    void initValues() override;
    Maybe<Math::Point3D> hit(const ray::Ray &ray) const override;
    Math::Vector3D getNormale(const Math::Point3D& point, const ray::Ray& camRay) const override;
    void setPoint(Math::Point3D p1, Math::Point3D p2, Math::Point3D p3);
    void setp1(Math::Point3D p1);
    void setp2(Math::Point3D p2);
    void setp3(Math::Point3D p3);
private:
    Math::Point3D _p1;
    Math::Point3D _p2;
    Math::Point3D _p3;
    Math::Vector3D _normal;
    Math::Vector3D _direction;
};

}

extern "C" ray::INode *create(std::map<std::string, std::string>& properties);


#endif //RAYTRACER_TRIANGLE_HPP
