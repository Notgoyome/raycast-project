/*
** EPITECH PROJECT, 2024
** B-OOP-400-MPL-4-1-raytracer-robin.glaude
** File description:
** IShape
*/


#ifndef ISHAPE_HPP_
#define ISHAPE_HPP_

#include <math/Vector2D.hpp>

#include "INode.hpp"
#include "Ray.hpp"
#include "Maybe.hpp"
#include "../materials/IMaterial.hpp"

namespace ray {

    class IShape : virtual public INode {
    public:
        virtual ~IShape() = default;

        [[nodiscard]] virtual Maybe<Math::Point3D> hit(const ray::Ray& ray) const = 0;
        [[nodiscard]] virtual Math::Vector3D getNormale(const Math::Point3D& point, const ray::Ray& camRay) const = 0;
        [[nodiscard]] virtual std::shared_ptr<ray::IMaterial> getMaterial() const = 0;

        [[nodiscard]] virtual Math::Vector2D getUVMapping(Math::Vector3D coords) const = 0;
    };

}

#endif /* !ISHAPE_HPP_ */
