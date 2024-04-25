/*
** EPITECH PROJECT, 2024
** B-OOP-400-MPL-4-1-raytracer-robin.glaude
** File description:
** IMaterial
*/


#ifndef IMATERIAL_HPP_
#define IMATERIAL_HPP_

#include "INode.hpp"

namespace ray {

    class IMaterial : public INode {
        public:
            IMaterial();
            ~IMaterial();
    };
}

#endif /* !IMATERIAL_HPP_ */
