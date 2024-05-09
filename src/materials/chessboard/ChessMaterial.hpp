/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** ChessMaterial.hpp
*/

#ifndef CHESSBOARD_HPP
#define CHESSBOARD_HPP

#include <map>

#include "../AMaterial.hpp"
#include "../Phong.hpp"

namespace ray {

    class ChessMaterial : public AMaterial {
        RGB _color;
        double _chessSize;
        double _minChess;
        double _maxChess;
        Phong::Model _phong;

    public:
        // CONSTR DESTRUCT
        ChessMaterial(RGB color,
            double refractionIndex,
            double shadowQuality,
            double ambiantOccQuality,
            double roughness,
            double chessSize,
            double minChess,
            double maxChess);
        ~ChessMaterial() override = default;

        // RUNTIME
        [[nodiscard]] RGB getColor(
            int recursion,
            Math::Point3D collisionPoint,
            Math::Vector3D normale,
            Math::Point3D camPos,
            const std::shared_ptr<ray::IShape>& shape,
            const std::shared_ptr<ray::IScene> &scene) const override;
    };

} // ray

extern "C" ray::INode *create(const std::map<std::string, std::string> &attributes);

#endif //CHESSBOARD_HPP
