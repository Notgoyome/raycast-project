/*
** EPITECH PROJECT, 2024
** B-OOP-400-MPL-4-1-raytracer-robin.glaude
** File description:
** IShape
*/


#ifndef ISHAPE_HPP_
#define ISHAPE_HPP_

#include "INode.hpp"
#include "Ray.hpp"
#include "Maybe.hpp"

namespace ray {

    class IShape : virtual public INode {
    public:
        virtual ~IShape() = default;

        virtual Maybe<Math::Point3D> hit(const ray::Ray& ray) = 0;
        virtual Math::Vector3D getNormale(const Math::Point3D& point, const ray::Ray& camRay) = 0;
    };

}

#endif /* !ISHAPE_HPP_ */
