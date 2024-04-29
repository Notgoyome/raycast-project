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
#include "../utils/ANode.hpp"
#include "../../include/math/MatrixN.hpp"
#include "../transformations/Transform.hpp"

namespace ray {

class AShape : public ray::ANode {
        public:
            AShape();
            ~AShape();
            virtual Maybe<Math::Point3D> hit(const Raytracer::Ray ray) = 0;
            virtual Math::Vector3D getNormale(const Math::Point3D point) = 0;
            Math::Point3D getPosition() const;
            Math::Vector3D getScale() const;
            Math::Matrix<3,3> getRotation() const;
            void applyMatrix();
            std::vector<Math::Vector3D> getTransformations() const;
    private:
        Math::Matrix<4, 4> _transformMatrix;
    };
}

#endif /* !ASHAPE_HPP_ */
