//
// Created by Guillaume Tran on 27/04/2024.
//

#ifndef B_OOP_400_MPL_4_1_RAYTRACER_ROBIN_GLAUDE_ANODE_HPP
#define B_OOP_400_MPL_4_1_RAYTRACER_ROBIN_GLAUDE_ANODE_HPP

#include "../../../include/INode.hpp"
#include <iostream>

namespace ray {
    class ANode : public INode {

    public:
        void addChild(std::shared_ptr<INode> child);
        void removeChild(std::shared_ptr<INode> child);
        std::shared_ptr<ray::INode>getChild(int index) override;
        const std::shared_ptr<ray::INode>getParent() const override;
        void setParent(INode *parent) override;
        ray::type getType() override;
        void setType(ray::type type);

    private:
        std::shared_ptr<ray::INode> _parent;
        ray::type type;
        std::vector<std::shared_ptr<ray::INode>> children;
    };
}


#endif //B_OOP_400_MPL_4_1_RAYTRACER_ROBIN_GLAUDE_ANODE_HPP
