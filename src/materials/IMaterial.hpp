/*
** EPITECH PROJECT, 2024
** B-OOP-400-MPL-4-1-raytracer-robin.glaude
** File description:
** IMaterial
*/


#ifndef IMATERIAL_HPP_
#define IMATERIAL_HPP_

#include "INode.hpp"
#include "RGB.hpp"
#include "math/Point3D.hpp"
#include "../scenes/IScene.hpp"

namespace ray {

    class IMaterial : virtual public INode {
    public:
        virtual ~IMaterial() = default;

        [[nodiscard]] virtual RGB getColor(int recursion, Math::Point3D collisionPoint,
            Math::Vector3D normale, Math::Point3D camPos,
            const std::shared_ptr<IScene>& scene) = 0;
    };

}

#endif /* !IMATERIAL_HPP_ */
