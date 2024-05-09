/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** ObjTriangle.hpp
*/

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
    class ObjTriangle : public ray::AShape {

    public:
        ObjTriangle() = default;
        ~ObjTriangle() override = default;

        void initValues() override;

        Maybe<PosShapePair> hit(const ray::Ray &ray) const override;
        Math::Vector3D getNormale(const Math::Point3D& point, const ray::Ray& camRay) const override;
        ray::Ray getRefraction(
            const std::shared_ptr<ray::IScene>& scene,
            Math::Point3D pos, Math::Vector3D dir) const override;

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

#endif //RAYTRACER_TRIANGLE_HPP
