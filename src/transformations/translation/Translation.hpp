/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Translation.hpp
*/

#ifndef TRANSLATION_HPP
#define TRANSLATION_HPP

#include "../ATransform.hpp"
#include "math/Vector3D.hpp"
#include <cmath>
#include <map>

namespace ray {

    class Translation : public ATransform {
    public:
        explicit Translation(Math::Vector3D translation);
    };

}

extern "C" ray::ITransform* create(const std::map<std::string, std::string>& attributes);

#endif //TRANSLATION_HPP