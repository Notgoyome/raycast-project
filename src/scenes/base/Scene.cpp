/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Scene.cpp
*/

#include "Scene.hpp"
#include "utils/getClosest.h"

namespace ray {

    bool isBehind(Math::Point3D pos, Math::Point3D lightPos, Math::Vector3D lightDir)
    {
        Math::Vector3D lightToPos = {pos.X - lightPos.X, pos.Y - lightPos.Y, pos.Z - lightPos.Z};
        double angle = lightToPos.dot(lightDir);

        return angle < 0;
    }

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

    void Scene::recursiveInitValues(std::shared_ptr<ray::INode> node)
    {
        std::shared_ptr<ray::INode> actual;
        node->initValues();

        for (int i = 0; (actual = node->getChild(i)) != nullptr; i++) {
            recursiveInitValues(actual);
        }
    }

    Maybe<PosShapePair> Scene::hit(const ray::Ray &ray) const
    {
        std::vector<std::shared_ptr<ray::IShape>> objects = getShapes();
        Math::Point3D point = {0, 0, 0};
        std::shared_ptr<ray::IShape> closestObj = nullptr;

        for (const std::shared_ptr<ray::IShape>& obj : objects) {
            Maybe<Math::Point3D> hit = obj->hit(ray);

            if (hit.has_value() &&
                isBehind(hit.value(), ray.origin, ray.direction) == false) {
                if (closestObj == nullptr) {
                    point = hit.value();
                    closestObj = obj;
                } else {
                    Math::Point3D closest = getClosest({point, hit.value()}, ray.origin);

                    if (closest == hit.value()) {
                        point = hit.value();
                        closestObj = obj;
                    }
                }
            }
        }
        if (closestObj == nullptr) {
            return Maybe<PosShapePair>{};
        }
        return Maybe{PosShapePair{point, closestObj}};
    }

    void Scene::initValues()
    {
        std::shared_ptr<ray::INode> actual;

        for (int i = 0; (actual = this->getChild(i)) != nullptr; i++) {
            recursiveInitValues(actual);
        }
        _cameras = getNodesType<ray::ICamera>(ray::type::CAMERA);
        _lights = getNodesType<ray::ILight>(ray::type::LIGHT);
        _shapes = getNodesType<ray::IShape>(ray::type::SHAPE);
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
        return _lights;
    }

    std::vector<std::shared_ptr<ray::IShape>> Scene::getShapes() const
    {
        return _shapes;
    }

    std::vector<std::shared_ptr<ray::ICamera>> Scene::getCameras() const
    {
        return _cameras;
    }

    std::shared_ptr<ray::IMaterial> Scene::getMaterial(
        const std::shared_ptr<ray::IShape>& shape)
    {
        std::shared_ptr<ray::INode> parent = shape->getParent();

        while (parent) {
            if (parent->getType() == ray::type::MATERIAL)
                return std::dynamic_pointer_cast<ray::IMaterial>(parent);
            parent = parent->getParent();
        }
        return nullptr;
    }

    std::shared_ptr<ray::IMaterial> Scene::getMaterial(const ray::IShape &shape)
    {
        std::shared_ptr<ray::INode> parent = shape.getParent();

        while (parent) {
            if (parent->getType() == ray::type::MATERIAL)
                return std::dynamic_pointer_cast<ray::IMaterial>(parent);
            parent = parent->getParent();
        }
        return nullptr;
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
        for (int i = 0; i < static_cast<int>(transformations.size()); i++) {
            finalMatrix = transformations[i] * finalMatrix;
        }
        return finalMatrix;
    }

    Math::Matrix<4, 4> Scene::getTransformationMatrix(const ray::INode &node)
    {

        std::shared_ptr<ray::INode> parent = node.getParent();
        std::vector<Math::Matrix<4, 4>> transformations;
        Math::Matrix<4, 4> finalMatrix = Math::Matrix<4, 4>::identity();

        while (parent) {
            if (parent->getType() == ray::type::TRANSFORM) {
                std::shared_ptr<ray::ITransform> transform = std::dynamic_pointer_cast<ray::ITransform>(parent);
                transformations.push_back(transform->getMatrix());
            }
            parent = parent->getParent();
        }
        for (int i = 0; i < static_cast<int>(transformations.size()); i++) {
            finalMatrix = transformations[i] * finalMatrix;
        }
        return finalMatrix;
    }

    Math::Point3D Scene::getPosition(const std::shared_ptr<ray::INode> &node)
    {
        Math::Matrix<4, 4> matrix = getTransformationMatrix(node);
        Math::Matrix<4, 1> pos = Math::Matrix<4, 1>{{{0}, {0}, {0}, {1}}};

        pos = matrix * pos;
        return {pos(0, 0), pos(1, 0), pos(2, 0)};
    }

    Math::Point3D Scene::getPosition(const ray::INode &node)
    {
        Math::Matrix<4, 4> matrix = getTransformationMatrix(node);
        Math::Matrix<4, 1> pos = Math::Matrix<4, 1>{{{0}, {0}, {0}, {1}}};

        pos = matrix * pos;
        return {pos(0, 0), pos(1, 0), pos(2, 0)};
    }
} // ray
