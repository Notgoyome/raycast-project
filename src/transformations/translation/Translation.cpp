/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Translation.cpp
*/

#include "Translation.hpp"

ray::Translation::Translation(Math::Vector3D translation)
{
    Math::Matrix<4, 4> translationMatrix = getIdentityMatrix();

    translationMatrix(0, 3) = translation.X;
    translationMatrix(1, 3) = translation.Y;
    translationMatrix(2, 3) = translation.Z;

    _matrix = translationMatrix * _matrix;
}
