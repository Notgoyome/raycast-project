/*
** EPITECH PROJECT, 2024
** B-OOP-400-MPL-4-1-raytracer-robin.glaude
** File description:
** ILight
*/


#ifndef ILIGHT_HPP_
#define ILIGHT_HPP_

#include "INode.hpp"

namespace ray {

    class ILight : public INode {
        public:
            ILight();
            ~ILight();
    };
}

#endif /* !ILIGHT_HPP_ */
