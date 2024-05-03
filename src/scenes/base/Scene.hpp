/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Scene.hpp
*/

#ifndef SCENE_HPP
#define SCENE_HPP

#include <map>

#include "../IScene.hpp"
#include "../../utils/ANode.hpp"
#include "../../transformations/ITransform.hpp"
#include "Maybe.hpp"
#include "../../materials/IMaterial.hpp"


namespace ray {

    class Scene : public ANode, public IScene {
    private:
        template<typename T>
        [[nodiscard]] std::vector<std::shared_ptr<T>> getNodesType(ray::type type) const;
        std::vector<std::shared_ptr<ray::ILight>> _lights;
        std::vector<std::shared_ptr<ray::IShape>> _shapes;
        std::vector<std::shared_ptr<ray::ICamera>> _cameras;
    public:
        // CONSTR DESTRUCT
        Scene();
        ~Scene() override = default;

        // RUNTIME
        Maybe<PosShapePair> hit(const ray::Ray &ray) override;

        // GETTERS
        [[nodiscard]] std::vector<std::shared_ptr<ray::ILight>> getLights() override;
        [[nodiscard]] std::vector<std::shared_ptr<ray::IShape>> getShapes() override;
        [[nodiscard]] std::vector<std::shared_ptr<ray::ICamera>> getCameras() override;

        // STATIC
        [[nodiscard]] static std::shared_ptr<ray::IMaterial> getMaterial(const std::shared_ptr<ray::IShape>& shape);
        [[nodiscard]] static std::shared_ptr<ray::IMaterial> getMaterial(const ray::IShape& shape);
        [[nodiscard]] static Math::Matrix<4, 4> getTransformationMatrix(const std::shared_ptr<ray::INode>& node);
        [[nodiscard]] static Math::Matrix<4, 4> getTransformationMatrix(const ray::INode& node);
        [[nodiscard]] static Math::Point3D getPosition(const std::shared_ptr<ray::INode>& node);
        [[nodiscard]] static Math::Point3D getPosition(const ray::INode& node);
    };

} // ray


#endif //SCENE_HPP
