/*
** EPITECH PROJECT, 2024
** B-OOP-400-MPL-4-1-raytracer-robin.glaude
** File description:
** IShape
*/


#ifndef ISHAPE_HPP_
#define ISHAPE_HPP_

#include "INode.hpp"
#include "Ray.hpp"

namespace ray {

    class IShape : public INode {
        public:
            virtual bool hit(const Raytracer::Ray &ray) = 0;

            IShape();
            ~IShape();
    };
}

#endif /* !ISHAPE_HPP_ */
