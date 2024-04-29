//
// Created by Guillaume Tran on 28/04/2024.
//

#include "Transform.hpp"

ray::Transform::Transform(Math::Point3D position, Math::Vector3D rotation, Math::Vector3D scale) :
    ANode(ray::type::TRANSFORM)
{
    // Implémentation ici, par exemple:
    this->_position = position;
    this->_rotation = rotation;
    this->_scale = scale;
}