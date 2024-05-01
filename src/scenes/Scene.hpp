/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Scene.hpp
*/

#ifndef SCENE_HPP
#define SCENE_HPP

#include "IScene.hpp"
#include "../utils/ANode.hpp"
#include "../transformations/ITransform.hpp"

namespace ray {

    class Scene : public ANode, public IScene {
    public:
        // CONSTR DESTRUCT
        Scene();
        ~Scene() override = default;

        // RUNTIME
        Maybe<PosShapePair> hit(const Raytracer::Ray &ray) override;

        // GETTERS
        template<typename T>
        [[nodiscard]] std::vector<std::shared_ptr<T>> getNodesType(ray::type type) const;
        [[nodiscard]] std::vector<std::shared_ptr<ray::ILight>> getLights() const override;
        [[nodiscard]] std::vector<std::shared_ptr<ray::IShape>> getShapes() const override;

        // STATIC
        [[nodiscard]] static std::shared_ptr<ray::IMaterial> getMaterial(std::shared_ptr<ray::IShape> shape);
        [[nodiscard]] static Math::Matrix<4, 4> getTransformationMatrix(const std::shared_ptr<ray::INode>& node);
    };

} // ray

#endif //SCENE_HPP
