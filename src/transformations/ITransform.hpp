/*
** EPITECH PROJECT, 2024
** B-OOP-400-MPL-4-1-raytracer-robin.glaude
** File description:
** ITransform
*/


#ifndef ITRANSFORM_HPP_
#define ITRANSFORM_HPP_

#include "INode.hpp"

namespace ray {

    class ITransform : public INode {
        public:
            ITransform();
            ~ITransform();
    };
}

#endif /* !ITRANSFORM_HPP_ */
