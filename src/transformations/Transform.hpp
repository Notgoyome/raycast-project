//
// Created by Guillaume Tran on 28/04/2024.
//

#ifndef B_OOP_400_MPL_4_1_RAYTRACER_ROBIN_GLAUDE_TRANSFORM_HPP
#define B_OOP_400_MPL_4_1_RAYTRACER_ROBIN_GLAUDE_TRANSFORM_HPP

#include "../utils/ANode.hpp"
#include "../../include/math/Vector3D.hpp"
#include "../../include/math/Point3D.hpp"
#include "../../include/math/MatrixN.hpp"

namespace ray {
    class Transform : public ray::ANode {
    public:
        Transform(Math::Point3D position, Math::Vector3D rotation, Math::Vector3D scale);
        ~Transform() = default;

        Math::Point3D getPosition() { return _position; }

        Math::Vector3D getRotation() { return _rotation; }

        Math::Vector3D getScale() { return _scale; }

    private:
        Math::Point3D _position;
        Math::Vector3D _rotation;
        Math::Vector3D _scale;
        Math::Matrix<4, 4> _matrix;

    };
}


#endif //B_OOP_400_MPL_4_1_RAYTRACER_ROBIN_GLAUDE_TRANSFORM_HPP
