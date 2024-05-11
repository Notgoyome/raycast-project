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
#include <SFML/Graphics.hpp>

namespace ray {
    class AMaterial : public ray::IMaterial, public ray::ANode {
    protected:
        double _refractionIndex;
        bool _hasNormalMap = false;
        sf::Image _normalMap;

        explicit AMaterial(double refractionIndex);
        explicit AMaterial(double refractionIndex, std::string normalMap);

    public:
        virtual ~AMaterial() = default;

        [[nodiscard]] double getRefractionIndex() const override;
        [[nodiscard]] bool hasNormalMap() const override { return _hasNormalMap; }
        [[nodiscard]]Math::Vector3D normalFromMap(Math::Vector2D uv) const override;

        void setNormalMap(std::string normalMap) override;
    };
}


#endif //AMATERIAL_HPP
