/*
** EPITECH PROJECT, 2024
** B-OOP-400-MPL-4-1-raytracer-robin.glaude
** File description:
** ATransform
*/

#include "include/math/MatrixN.hpp"
#include "../utils/ANode.hpp"
#include "include/math/Point3D.hpp"
#include "include/math/Vector3D.hpp"

#ifndef ATRANSFORM_HPP_
#define ATRANSFORM_HPP_

namespace ray {

    class ATransform : public ANode {
        public:

        protected:
            Math::Point3D _position;
            Math::Vector3D _rotation;
            Math::Vector3D _scale;
        private:
    };
}

#endif /* !ATRANSFORM_HPP_ */
