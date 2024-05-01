/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** AMaterial.hpp
*/

#ifndef AMATERIAL_HPP
#define AMATERIAL_HPP

#include "IMaterial.hpp"
#include "../utils/ANode.hpp"

namespace ray {
    class AMaterial : public ray::IMaterial, public ray::ANode {
    protected:
        AMaterial();
    public:
        virtual ~AMaterial() = default;
    };
}


#endif //AMATERIAL_HPP
