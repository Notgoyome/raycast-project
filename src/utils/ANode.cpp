//
// Created by Guillaume Tran on 27/04/2024.
//

#include "ANode.hpp"

void ray::ANode::addChild(std::shared_ptr<INode> child)
{
    children.push_back(child);
}

void ray::ANode::removeChild(std::shared_ptr<INode> child)
{
    if (child == nullptr)
        return;
    children.erase(std::remove(children.begin(), children.end(), child), children.end());
}

void ray::ANode::setParent(std::shared_ptr<INode> parent)
{
    _parent = std::shared_ptr(std::dynamic_pointer_cast<ANode>(parent));
}

void ray::ANode::setType(ray::type type)
{
    ANode::type = type;
}

std::shared_ptr<ray::INode> ray::ANode::getChild(int index) const
{
    if (index < 0 || index >= static_cast<int>(children.size()))
        return nullptr;
    return children[index];
}

std::shared_ptr<ray::INode> ray::ANode::getParent() const
{
    return _parent;
}

ray::type ray::ANode::getType() const
{
    return type;
}
