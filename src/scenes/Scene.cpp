/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Scene.cpp
*/

#include "Scene.hpp"

namespace ray {

    template<typename T>
    std::vector<std::shared_ptr<T>> recursiveGetType(const std::shared_ptr<ray::INode> node, ray::type type)
    {
        std::vector<std::shared_ptr<T>> res;
        std::shared_ptr<ray::INode> child;

        if (node == nullptr)
            return res;
        for (int i = 0; (child = node->getChild(i)) != nullptr; i++) {
            if (child->getType() == type)
                res.push_back(std::dynamic_pointer_cast<T>(child));
            else {
                auto funcRes = recursiveGetType<T>(child, type);
                res.insert(res.end(), funcRes.begin(), funcRes.end());
            }
        }
        return res;
    }

    Scene::Scene() : ANode(ray::type::SCENE)
    {
    }

    Maybe<PosShapePair> Scene::hit(const Raytracer::Ray &ray)
    {
        return Maybe<PosShapePair>{};
        //TODO
    }

    template<typename T>
    std::vector<std::shared_ptr<T>> ray::Scene::getNodesType(ray::type type) const
    {
        std::vector<std::shared_ptr<T>> res;
        std::shared_ptr<ray::INode> child;

        for (int i = 0; (child = getChild(i)) != nullptr; i++) {
            if (child->getType() == type)
                res.push_back(std::dynamic_pointer_cast<T>(child));
            else {
                auto funcRes = recursiveGetType<T>(child, type);
                res.insert(res.end(), funcRes.begin(), funcRes.end());
            }
        }
        return res;
    }

    std::vector<std::shared_ptr<ray::ILight>> Scene::getLights() const
    {
        return getNodesType<ray::ILight>(ray::type::LIGHT);
    }

    std::vector<std::shared_ptr<ray::IShape>> Scene::getShapes() const
    {
        return getNodesType<ray::IShape>(ray::type::SHAPE);
    }

    std::shared_ptr<ray::IMaterial> Scene::getMaterial(
        std::shared_ptr<ray::IShape> shape)
    {
        return nullptr;
        //TODO
    }

    Math::Matrix<4, 4> Scene::getTransformationMatrix(
        const std::shared_ptr<ray::INode>& node)
    {
        std::shared_ptr<ray::INode> parent = node->getParent();
        std::vector<Math::Matrix<4, 4>> transformations;
        Math::Matrix<4, 4> finalMatrix = Math::Matrix<4, 4>::identity();

        while (parent) {
            if (parent->getType() == ray::type::TRANSFORM) {
                std::shared_ptr<ray::ITransform> transform = std::dynamic_pointer_cast<ray::ITransform>(parent);
                transformations.push_back(transform->getMatrix());
            }
            parent = parent->getParent();
        }
        for (int i = static_cast<int>(transformations.size()) - 1; i >= 0; i--) {
            finalMatrix = transformations[i] * finalMatrix;
        }
        return finalMatrix;
    }
} // ray
