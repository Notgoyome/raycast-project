/*
** EPITECH PROJECT, 2024
** B-OOP-400-MPL-4-1-raytracer-robin.glaude
** File description:
** INode
*/

#ifndef INODE_HPP_
#define INODE_HPP_

namespace ray {

    enum type {
        UNDEFINED = 0,
        SCENE = 1,
        SHAPE = 2,
        LIGHT = 3,
        CAMERA = 4,
        MATERIAL = 5,
        TRANSFORM = 6,
    };

    class INode {
        public:
            virtual ~INode() = default;

            virtual void addChild(INode *node) = 0;
            virtual void removeChild(INode *node) = 0;
            virtual INode *getChild(int index) = 0;

            virtual void setParent(INode *node) = 0;
            virtual INode *getParent() = 0;
    };
}

#endif /* !INODE_HPP_ */
