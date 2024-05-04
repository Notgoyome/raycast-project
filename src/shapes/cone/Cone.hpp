//
// Created by Guillaume Tran on 02/05/2024.
//

#ifndef RAYTRACER_CONE_HPP
#define RAYTRACER_CONE_HPP

#include "../AShape.hpp"
#include "Ray.hpp"
#include "../../../include/Maybe.hpp"
#include <cmath>
#include <memory>
#include <map>
#include "../../scenes/base/Scene.hpp"

namespace ray {
    class Cone : public ray::AShape {
    public:
        Cone();
        ~Cone() override = default;
        Maybe<Math::Point3D> hit(const ray::Ray &ray) override;
        Math::Vector3D getNormale(const Math::Point3D& point, const ray::Ray& camRay) override;
        void setPosition();
        void setRadius(float radius);
        void setHeight(float height);
        Math::Vector3D getAxis();

    private:
        bool _transform;
        Math::Point3D center;
        float _height;
        float _radius;
    };
}

extern "C" ray::INode *create(std::map<std::string, std::string>& properties);

#endif //RAYTRACER_CONE_HPP
