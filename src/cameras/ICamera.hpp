/*
** EPITECH PROJECT, 2024
** B-OOP-400-MPL-4-1-raytracer-robin.glaude
** File description:
** ICamera
*/


#ifndef ICAMERA_HPP_
#define ICAMERA_HPP_

#include "INode.hpp"

namespace ray {

    class ICamera : public INode {
        public:
            ICamera();
            ~ICamera();
    };
}

#endif /* !ICAMERA_HPP_ */
