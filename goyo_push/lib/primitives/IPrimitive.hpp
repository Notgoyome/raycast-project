//
// Created by Guillaume Tran on 25/04/2024.
//

#ifndef B_OOP_400_MPL_4_1_RAYTRACER_ROBIN_GLAUDE_IPRIMITIVE_HPP
#define B_OOP_400_MPL_4_1_RAYTRACER_ROBIN_GLAUDE_IPRIMITIVE_HPP

#include "../../include/Ray.hpp"

class IPrimitive {
public:
    virtual bool hit(const Raytracer::Ray &ray) = 0;

};


#endif //B_OOP_400_MPL_4_1_RAYTRACER_ROBIN_GLAUDE_IPRIMITIVE_HPP
