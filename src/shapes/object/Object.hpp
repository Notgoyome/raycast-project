//
// Created by Guillaume Tran on 08/05/2024.
//

#ifndef RAYTRACER_OBJECT_HPP
#define RAYTRACER_OBJECT_HPP

#include <cmath>
#include "Ray.hpp"
#include "../../../include/Maybe.hpp"
#include "../../scenes/base/Scene.hpp"
#include "../../../src/shapes/AShape.hpp"
#include "../../../include/math/Vector3D.hpp"
#include "../triangle/Triangle.hpp"
#include <vector>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

namespace ray {
    class Object : public ray::AShape {
    public:
        void initValues() override;
        void parse(std::string objPath);
        Maybe<Math::Point3D> hit(const ray::Ray &ray) const override;
        Math::Vector3D getNormale(const Math::Point3D& point, const ray::Ray& camRay) const override;
        void applyCurrentTriangleIndex(int index) { _currentTriangleIndex = index; }
        void setPath(std::string path) { _objPath = path; }
    private:
        std::vector<Math::Point3D> _points;
        std::vector<Triangle> _triangles;
        std::vector<Math::Vector3D> _normals;
        mutable int _currentTriangleIndex;
        std::string _objPath;
    };

}

extern "C" ray::INode *create(std::map<std::string, std::string>& properties);

#endif //RAYTRACER_OBJECT_HPP
