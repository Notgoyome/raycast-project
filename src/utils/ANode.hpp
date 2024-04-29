/*
** EPITECH PROJECT, 2024
** B-OOP-400-MPL-4-1-raytracer-robin.glaude
** File description:
** ANode
*/

#ifndef B_OOP_400_MPL_4_1_RAYTRACER_ROBIN_GLAUDE_ANODE_HPP
#define B_OOP_400_MPL_4_1_RAYTRACER_ROBIN_GLAUDE_ANODE_HPP

#include "INode.hpp"
#include <iostream>
#include <vector>

namespace ray {
    class ANode : virtual public INode {
    private:
        std::shared_ptr<ray::INode> _parent;
        ray::type type;
        std::vector<std::shared_ptr<ray::INode>> children;
        std::string _name;

    protected:
        explicit ANode(ray::type type) : type(type) {}

    public:
        virtual ~ANode() = default;

        // SETTERS
        void addChild(std::shared_ptr<INode> child) override;
        void removeChild(std::shared_ptr<INode> child) override;
        void setParent(std::shared_ptr<INode> parent) override;
        void setType(ray::type type) override;
        void setName(const std::string &name);

        [[nodiscard]] std::shared_ptr<INode> getShared() override;

        // GETTERS
        [[nodiscard]] std::shared_ptr<ray::INode> getChild(int index) const override;
        [[nodiscard]] std::shared_ptr<ray::INode> getParent() const override;
        [[nodiscard]] ray::type getType() const override;
        [[nodiscard]] std::string getName() const;
    };
}

#endif //B_OOP_400_MPL_4_1_RAYTRACER_ROBIN_GLAUDE_ANODE_HPP
