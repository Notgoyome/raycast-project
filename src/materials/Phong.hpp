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

namespace Phong {

    class Light {
        Math::Matrix<1, 3> _specularIntensity;
        Math::Matrix<1, 3> _diffuseIntensity;
        Math::Point3D _position;

    public:
        Light(Math::Matrix<1, 3> specularIntensity, Math::Matrix<1, 3> diffuseIntensity, Math::Point3D position)
            : _specularIntensity(specularIntensity), _diffuseIntensity(diffuseIntensity), _position(position) {}
        ~Light() = default;

        void setSpecularIntensity(Math::Matrix<1, 3> specularIntensity) { _specularIntensity = specularIntensity; }
        void setDiffuseIntensity(Math::Matrix<1, 3> diffuseIntensity) { _diffuseIntensity = diffuseIntensity; }
        void setPosition(Math::Point3D position) { _position = position; }

        [[nodiscard]] Math::Matrix<1, 3> getSpecularIntensity() const { return _specularIntensity; }
        [[nodiscard]] Math::Matrix<1, 3> getDiffuseIntensity() const { return _diffuseIntensity; }
        [[nodiscard]] Math::Point3D getPosition() const { return _position; }
    };

    class Model {
    private:
        std::vector<Light> _lights;
        double _ia;
        double _alpha;
        Math::Matrix<1, 3> _ka;
        Math::Matrix<1, 3> _kd;
        Math::Matrix<1, 3> _ks;
        Math::Point3D _pos;
        Math::Vector3D _normale;
        Math::Vector3D _view;

        [[nodiscard]] unsigned int getPhongForValues(int idx) const;

    public:
        // CONSTR DESTRUCT
        Model(
            std::vector<Light> lights,
            double ia,
            double alpha,
            Math::Matrix<1, 3> ka,
            Math::Matrix<1, 3> kd,
            Math::Matrix<1, 3> ks,
            Math::Point3D pos,
            Math::Vector3D normale,
            Math::Vector3D view)
            : _lights(std::move(lights)), _ia(ia), _alpha(alpha),
            _ka(ka), _kd(kd), _ks(ks), _pos(pos), _normale(normale),
            _view(view) {}
        ~Model() = default;

        // RUNTIME
        [[nodiscard]] RGB calculateColor();

        // SETTERS
        void setLights(std::vector<Light> lights) { _lights = lights; }
        void setIa(double ia) { _ia = ia; }
        void setAlpha(double alpha) { _alpha = alpha; }
        void setKa(Math::Matrix<1, 3> ka) { _ka = ka; }
        void setKd(Math::Matrix<1, 3> kd) { _kd = kd; }
        void setKs(Math::Matrix<1, 3> ks) { _ks = ks; }
        void setPos(Math::Point3D pos) { _pos = pos; }
        void setNormale(Math::Vector3D normale) { _normale = normale; }
        void setView(Math::Vector3D view) { _view = view; }

        // GETTERS
        [[nodiscard]] std::vector<Light> getLights() const { return _lights; }
        [[nodiscard]] double getIa() const { return _ia; }
        [[nodiscard]] double getAlpha() const { return _alpha; }
        [[nodiscard]] Math::Matrix<1, 3> getKa() const { return _ka; }
        [[nodiscard]] Math::Matrix<1, 3> getKd() const { return _kd; }
        [[nodiscard]] Math::Matrix<1, 3> getKs() const { return _ks; }
        [[nodiscard]] Math::Point3D getPos() const { return _pos; }
        [[nodiscard]] Math::Vector3D getNormale() const { return _normale; }
        [[nodiscard]] Math::Vector3D getView() const { return _view; }
    };

}


#endif //PHONGMODEL_HPP
