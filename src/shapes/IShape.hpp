/*
** EPITECH PROJECT, 2024
** B-OOP-400-MPL-4-1-raytracer-robin.glaude
** File description:
** IShape
*/


#ifndef ISHAPE_HPP_
#define ISHAPE_HPP_

#include "INode.hpp"

namespace ray {

    class IShape : public INode {
        public:
            IShape();
            ~IShape();
    };
}

#endif /* !ISHAPE_HPP_ */
