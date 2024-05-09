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
    Maybe<PosShapePair> hit(const ray::Ray &ray) const override;
    Math::Vector3D getNormale(const Math::Point3D& point, const ray::Ray& camRay) const override;

    void initNormale();
    void setPoint(Math::Point3D p1, Math::Point3D p2, Math::Point3D p3);
    void setp1(Math::Point3D p1);
    void setp2(Math::Point3D p2);
    void setp3(Math::Point3D p3);
    void setMaterial(std::shared_ptr<ray::IMaterial> material);

    Math::Point3D getp1() const { return _p1;}
    Math::Point3D getp2() const { return _p2;}
    Math::Point3D getp3() const { return _p3;}
private:
    Math::Point3D _p1;
    Math::Point3D _p2;
    Math::Point3D _p3;

    Math::Vector3D _normal;
    Math::Vector3D _direction;
};

}

Math::Point3D StringToPoint3D(std::string str);
extern "C" ray::INode *create(std::map<std::string, std::string>& properties);

//std::ostream& operator<<(std::ostream& os, const ray::Triangle& triangle) {
//    os << "Triangle:" << std::endl;
//    os << "p1: " << triangle.getp1().X << " " << triangle.getp1().Y << " " << triangle.getp1().Z << std::endl;
//    os << "p2: " << triangle.getp2().X << " " << triangle.getp2().Y << " " << triangle.getp2().Z << std::endl;
//    os << "p3: " << triangle.getp3().X << " " << triangle.getp3().Y << " " << triangle.getp3().Z << std::endl;
//    return os;
//}

#endif //RAYTRACER_TRIANGLE_HPP
