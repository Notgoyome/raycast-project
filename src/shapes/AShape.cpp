/*
** EPITECH PROJECT, 2024
** B-OOP-400-MPL-4-1-raytracer-robin.glaude
** File description:
** AShape
*/

#include "AShape.hpp"

ray::AShape::AShape() : ANode(ray::type::SHAPE)
{
}

ray::AShape::~AShape()
{
}

Math::Matrix<4,4> applyRotationX(Math::Matrix<4,4> matrix, double angle)
{
    Math::Matrix<4,4> rotationMatrix;
    rotationMatrix(0,0) = 1;
    rotationMatrix(1,1) = cos(angle);
    rotationMatrix(1,2) = -sin(angle);
    rotationMatrix(2,1) = sin(angle);
    rotationMatrix(2,2) = cos(angle);
    rotationMatrix(3,3) = 1;
    return matrix * rotationMatrix;
}

Math::Matrix<4,4> applyRotationY(Math::Matrix<4,4> matrix, double angle)
{
    Math::Matrix<4,4> rotationMatrix;
    rotationMatrix(0,0) = cos(angle);
    rotationMatrix(0,2) = sin(angle);
    rotationMatrix(1,1) = 1;
    rotationMatrix(2,0) = -sin(angle);
    rotationMatrix(2,2) = cos(angle);
    rotationMatrix(3,3) = 1;
    return matrix * rotationMatrix;
}

Math::Matrix<4,4> applyRotationZ(Math::Matrix<4,4> matrix, double angle)
{
    Math::Matrix<4,4> rotationMatrix;
    rotationMatrix(0,0) = cos(angle);
    rotationMatrix(0,1) = -sin(angle);
    rotationMatrix(1,0) = sin(angle);
    rotationMatrix(1,1) = cos(angle);
    rotationMatrix(2,2) = 1;
    rotationMatrix(3,3) = 1;
    return matrix * rotationMatrix;
}

Math::Matrix<4,4> applyRotation(Math::Matrix<4,4> matrix, Math::Vector3D rotation)
{
    matrix = applyRotationX(matrix, rotation.X);
    matrix = applyRotationY(matrix, rotation.Y);
    return applyRotationZ(matrix, rotation.Z);
}

Math::Matrix<4,4> applyScale(Math::Matrix<4,4> matrix, Math::Vector3D scale)
{
    Math::Matrix<4, 4> scaleMatrix;
    scaleMatrix(0, 0) = scale.X;
    scaleMatrix(1, 1) = scale.Y;
    scaleMatrix(2, 2) = scale.Z;
    return matrix * scaleMatrix;
}

Math::Matrix<4,4> applyTranslation(Math::Matrix<4,4> matrix, Math::Point3D position)
{
    Math::Matrix<4,4> translationMatrix;
    Math::Matrix<4,4> resultMatrix;
    translationMatrix(0,3) = position.X;
    translationMatrix(1,3) = position.Y;
    translationMatrix(2,3) = position.Z;
    std::cout << "position: " << position.X << " " << position.Y << " " << position.Z << std::endl;
    resultMatrix = matrix * translationMatrix;
    std::cout << resultMatrix << std::endl;
    return resultMatrix;
}

Math::Matrix<4,4> setTranslation(Math::Matrix<4,4> matrix, Math::Point3D position)
{
    Math::Matrix<4,4> translationMatrix;
    translationMatrix(0,3) = position.X;
    translationMatrix(1,3) = position.Y;
    translationMatrix(2,3) = position.Z;
    return translationMatrix;
}

void ray::AShape::applyMatrix()
{
    Math::Matrix<4,4> newMatrix;
    Math::Vector3D rotation = {0, 0, 0};
    Math::Vector3D scale = {1, 1, 1};
    Math::Point3D position = {0, 0, 0};

    for (int i = 0; i < 3; i++) {
            newMatrix(i, i) = 1;
    }
    std::shared_ptr<INode> parent = getParent();
    while (parent != nullptr) {
        if (parent->getType() == ray::type::TRANSFORM) {
            std::shared_ptr<ray::Transform> transform = std::dynamic_pointer_cast<ray::Transform>(parent);
            Math::Vector3D transform_rotation = transform->getRotation();
            Math::Vector3D transform_scale = transform->getScale();
            Math::Point3D transform_position = transform->getPosition();
            newMatrix = applyRotation(newMatrix, transform_rotation);
            newMatrix = applyScale(newMatrix, transform_scale);
            newMatrix = applyTranslation(newMatrix, transform_position);
        }
        parent = parent->getParent();
    }
    std::cout << "position_end: " << position.X << " " << position.Y << " " << position.Z << std::endl;
    _transformMatrix = newMatrix;
}

Math::Point3D ray::AShape::getPosition() const
{
    Math::Point3D position = { _transformMatrix(0, 3),
                 _transformMatrix(1, 3),
                 _transformMatrix(2, 3) };
    return position;
}

Math::Vector3D ray::AShape::getScale() const
{
    Math::Vector3D scale = { _transformMatrix(0, 0),
                 _transformMatrix(1, 1),
                 _transformMatrix(2, 2) };
    return scale;
}

Math::Matrix<3,3> ray::AShape::getRotation() const
{
    Math::Matrix<3,3> rotation;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++)
            rotation(i, j) = _transformMatrix(i, j);

    }
    return rotation;
}