/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** loadObjMaterials.cpp
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include "math/MatrixN.hpp"
#include "loadObjMaterials.h"

#include "../../materials/basic/BasicMaterial.hpp"

// struct Material {
//     std::string name;
//     Math::Matrix<1, 3> Ka; // Ambient color
//     Math::Matrix<1, 3> Kd; // Diffuse color
//     Math::Matrix<1, 3> Ks; // Specular color
//     float Ns = 0.0f; // Specular exponent
//     float d = 1.0f;  // Dissolve or transparency
//     int illum = 0;   // Illumination model
//     float Ni = 1.0f; // Optical density
// };

std::shared_ptr<ray::IMaterial> materialToRayMaterial(Material mtl)
{
    RGB color = RGB(mtl.Kd(0,0) * 255,
        mtl.Kd(0,1) * 255,
        mtl.Kd(0,2) * 255);
    double ksMean = (mtl.Ks(0,0) + mtl.Ks(0,1) + mtl.Ks(0,2)) / 3;

    return std::make_shared<ray::BasicMaterial>(color, 1, 0, ksMean);
}

std::map<std::string, std::shared_ptr<ray::IMaterial>> loadObjMaterials(const std::string& filename)
{
    std::ifstream file(filename);
    std::string line;
    std::map<std::string, std::shared_ptr<ray::IMaterial>> materials;
    Material currentMaterial;

    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return materials;
    }

    while (getline(file, line)) {
        std::istringstream iss(line);
        std::string key;
        iss >> key;

        if (key == "newmtl") {
            if (!currentMaterial.name.empty()) {
                materials[currentMaterial.name] = materialToRayMaterial(currentMaterial);
                currentMaterial = Material();
            }
            iss >> currentMaterial.name;
        } else if (key == "Ka" || key == "Kd" || key == "Ks") {
            Math::Matrix<1, 3> color;
            iss >> color(0,0) >> color(0,1) >> color(0,2);
            if (key == "Ka") {
                currentMaterial.Ka = color;
            } else if (key == "Kd") {
                currentMaterial.Kd = color;
            } else if (key == "Ks") {
                currentMaterial.Ks = color;
            }
        } else if (key == "Ns") {
            iss >> currentMaterial.Ns;
        } else if (key == "d") {
            iss >> currentMaterial.d;
        } else if (key == "illum") {
            iss >> currentMaterial.illum;
        } else if (key == "Ni") {
            iss >> currentMaterial.Ni;
        }
    }

    if (!currentMaterial.name.empty()) {
        materials[currentMaterial.name] = materialToRayMaterial(currentMaterial);
    }

    file.close();
    return materials;
}
