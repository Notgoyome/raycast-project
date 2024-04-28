/*
** EPITECH PROJECT, 2024
** B-OOP-400-MPL-4-1-raytracer-robin.glaude
** File description:
** ATransform
*/

#ifndef ATRANSFORM_HPP_
#define ATRANSFORM_HPP_

namespace ray {

    class ATransform : public ANode {
        public:
            ATransform();
            ~ATransform();

        protected:
            Math::Point3D _position;
            Math::Vector3D _rotation;
            Math::Vector3D _scale;
        private:
    };
}

#endif /* !ATRANSFORM_HPP_ */
