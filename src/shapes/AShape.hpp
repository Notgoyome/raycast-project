/*
** EPITECH PROJECT, 2024
** B-OOP-400-MPL-4-1-raytracer-robin.glaude
** File description:
** AShape
*/

#ifndef ASHAPE_HPP_
#define ASHAPE_HPP_

#include "Ray.hpp"
#include "../../include/Maybe.hpp"

namespace ray {

    class AShape {
        public:
            AShape();
            ~AShape();
            virtual Maybe<Math::Point3D> hit(const Raytracer::Ray &ray) = 0;
            virtual Math::Vector3D getNormal(const Math::Vector3D &point) = 0;
    private:
    };
}

#endif /* !ASHAPE_HPP_ */
