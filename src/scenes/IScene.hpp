/*
** EPITECH PROJECT, 2024
** B-OOP-400-MPL-4-1-raytracer-robin.glaude
** File description:
** IScene
*/


#ifndef ISCENE_HPP_
#define ISCENE_HPP_

#include "INode.hpp"

namespace ray {

    class IScene : public INode {
        public:
            IScene();
            ~IScene();
    };
}

#endif /* !ISCENE_HPP_ */
