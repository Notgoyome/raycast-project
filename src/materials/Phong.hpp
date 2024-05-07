/*
** EPITECH PROJECT, 2024
** raytracer_bootstrap
** File description:
** PhongModel.hpp
*/

#ifndef PHONGMODEL_HPP
#define PHONGMODEL_HPP

#include <utility>
#include <vector>
#include "RGB.hpp"
#include "math/MatrixN.hpp"
#include "math/Point3D.hpp"
#include "../lights/ILight.hpp"
#include "../scenes/IScene.hpp"
#include "../shapes/IShape.hpp"

using ListLight = std::vector<std::shared_ptr<ray::ILight>>;

namespace Phong {

    class Model {
    private:
        ListLight _lights;
        double _ia;
        double _alpha;
        double _shadowQuality;
        double _ambOccQuality;
        Math::Matrix<1, 3> _ka;
        Math::Matrix<1, 3> _kd;
        Math::Matrix<1, 3> _ks;

        [[nodiscard]] Math::Matrix<1, 3> getReflectionContribution(
            const std::shared_ptr<ray::IScene>& scene,
            Math::Point3D pos, Math::Vector3D normale,
            Math::Vector3D view, int recursive) const;

        [[nodiscard]] Math::Matrix<1, 3> getLightsContribution(
            Math::Vector3D normale,
            Math::Point3D pos,
            Math::Vector3D view,
            const std::shared_ptr<ray::IScene>& scene) const;

    public:
        // CONSTR DESTRUCT
        Model(
            ListLight lights,
            double ia,
            double alpha,
            double shadowQuality,
            double ambOccQuality,
            Math::Matrix<1, 3> ka,
            Math::Matrix<1, 3> kd,
            Math::Matrix<1, 3> ks)
            : _lights(std::move(lights)), _ia(ia), _alpha(alpha), _shadowQuality(shadowQuality), _ambOccQuality(ambOccQuality),
            _ka(ka), _kd(kd), _ks(ks) {}
        ~Model() = default;

        // RUNTIME
        [[nodiscard]] RGB calculateColor(
            const std::shared_ptr<ray::IScene>& scene,
            Math::Vector3D view,
            Math::Point3D pos,
            Math::Vector3D normale,
            int recursion) const;

        // SETTERS
        void setLights(ListLight lights) { _lights = lights; }
        void setIa(double ia) { _ia = ia; }
        void setAlpha(double alpha) { _alpha = alpha; }
        void setKa(Math::Matrix<1, 3> ka) { _ka = ka; }
        void setKd(Math::Matrix<1, 3> kd) { _kd = kd; }
        void setKs(Math::Matrix<1, 3> ks) { _ks = ks; }

        // GETTERS
        [[nodiscard]] ListLight getLights() const { return _lights; }
        [[nodiscard]] double getIa() const { return _ia; }
        [[nodiscard]] double getAlpha() const { return _alpha; }
        [[nodiscard]] Math::Matrix<1, 3> getKa() const { return _ka; }
        [[nodiscard]] Math::Matrix<1, 3> getKd() const { return _kd; }
        [[nodiscard]] Math::Matrix<1, 3> getKs() const { return _ks; }
    };

}


#endif //PHONGMODEL_HPP
