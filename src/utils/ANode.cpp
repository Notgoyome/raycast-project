//
// Created by Guillaume Tran on 27/04/2024.
//

#include "ANode.hpp"

void ray::ANode::addChild(std::shared_ptr<INode> child) {
    children.push_back(child);
}

void ray::ANode::removeChild(std::shared_ptr<INode> child) {
    if (child == nullptr)
        return;
    children.erase(std::remove(children.begin(), children.end(), child), children.end());
}

std::shared_ptr<ray::INode> ray::ANode::getChild(int index) {
    if (index < 0 || index >= children.size())
        return nullptr;
    return children[index];
}

const std::shared_ptr<ray::INode> ray::ANode::getParent() const {
    return _parent;
}

void ray::ANode::setParent(INode *parent) {
    _parent = std::shared_ptr<ANode>(dynamic_cast<ANode *>(parent));
}

ray::type ray::ANode::getType() {
    return type;
}

void ray::ANode::setType(ray::type type) {
    ANode::type = type;
}