/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** PerlinMaterial.cpp
*/

#include "PerlinMaterial.hpp"

#include <random>

namespace ray {

    double interpolate(double a0, double a1, float w) {
        /* // You may want clamping by inserting:
         * if (0.0 > w) return a0;
         * if (1.0 < w) return a1;
         */
        return (a1 - a0) * w + a0;
        /* // Use this cubic interpolation [[Smoothstep]] instead, for a smooth appearance:
         * return (a1 - a0) * (3.0 - w * 2.0) * w * w + a0;
         *
         * // Use [[Smootherstep]] for an even smoother result with a second derivative equal to zero on boundaries:
         * return (a1 - a0) * ((w * (w * 6.0 - 15.0) + 10.0) * w * w * w) + a0;
         */
    }

    Math::Vector2D randomGradient(int ix, int iy) {
        // No precomputed gradients mean this works for any number of grid coordinates
        const unsigned w = 8 * sizeof(unsigned);
        const unsigned s = w / 2; // rotation width
        unsigned a = ix, b = iy;
        a *= 3284157443; b ^= a << s | a >> (w-s);
        b *= 1911520717; a ^= b << s | b >> (w-s);
        a *= 2048419325;
        double random = a * (3.14159265 / ~(~0u >> 1)); // in [0, 2*Pi]
        Math::Vector2D v{0, 0};
        v.first = std::cos(random); v.second = std::sin(random);
        return v;
    }

    double dotGridGradient(int ix, int iy, double x, double y) {
        // Get gradient from integer coordinates
        Math::Vector2D gradient = randomGradient(ix, iy);

        // Compute the distance vector
        double dx = x - ix;
        double dy = y - iy;

        // Compute the dot-product
        return (dx*gradient.first + dy*gradient.second);
    }

    double perlin(double x, double y) {
        // Determine grid cell coordinates
        int x0 = static_cast<int>(std::floor(x));
        int x1 = x0 + 1;
        int y0 = static_cast<int>(std::floor(y));
        int y1 = y0 + 1;

        // Determine interpolation weights
        // Could also use higher order polynomial/s-curve here
        double sx = x - x0;
        double sy = y - y0;

        // Interpolate between grid point gradients
        double n0, n1, ix0, ix1, value;

        n0 = dotGridGradient(x0, y0, x, y);
        n1 = dotGridGradient(x1, y0, x, y);
        ix0 = interpolate(n0, n1, sx);

        n0 = dotGridGradient(x0, y1, x, y);
        n1 = dotGridGradient(x1, y1, x, y);
        ix1 = interpolate(n0, n1, sx);

        value = interpolate(ix0, ix1, sy);
        return value * 0.5 + 0.5; // Will return in range -1 to 1. To make it in range 0 to 1, multiply by 0.5 and add 0.5
    }

    double perlinOctaves(double x, double y, int octaves, double persistence) {
        double total = 0;
        double frequency = 1;
        double amplitude = 1;
        double maxValue = 0;  // Used for normalizing result to 0.0 - 1.0

        for(int i=0; i < octaves; i++) {
            total += perlin(x * frequency, y * frequency) * amplitude;

            maxValue += amplitude;

            amplitude *= persistence;
            frequency *= 2;
        }

        return total / maxValue;
    }

    Math::Vector2D getRandomCoordinates()
    {
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_real_distribution<double> dist(0, 1);
        return {dist(rng), dist(rng)};
    }

    PerlinMaterial::PerlinMaterial(RGB color,
        double shadowQuality,
        double ambiantOccQuality,
        double roughness,
        int octaves,
        double persistence,
        double minPerlin,
        double maxPerlin) : _color(color), _octaves(octaves), _persistence(persistence), _minPerlin(minPerlin), _maxPerlin(maxPerlin),
        _phong({},
            0.05,
            50,
            shadowQuality,
            ambiantOccQuality,
            Math::Matrix<1, 3>({{1, 1, 1}}),
            Math::Matrix<1, 3>{{{0, 0, 0}}},
            Math::Matrix<1, 3>{{{roughness, roughness, roughness}}})
    {
        _phong.setKd(Math::Matrix<1, 3>({{color.R / 255.f, color.G / 255.f, color.B / 255.f}}));
    }

    RGB PerlinMaterial::getColor(int recursion, Math::Point3D collisionPoint,
                                 Math::Vector3D normale, Math::Point3D camPos,
                                 const std::shared_ptr<ray::IShape>& shape,
                                 const std::shared_ptr<ray::IScene> &scene) const
    {
        Math::Vector2D uv = shape->getUVMapping(collisionPoint);
        Math::Vector3D view = {camPos.X - collisionPoint.X, camPos.Y - collisionPoint.Y, camPos.Z - collisionPoint.Z};
        RGB color;
        double perlinValue;

        view /= view.length();

        if (recursion > REFLECTION_RECURSION_LIMIT)
            color = _color;
        else
            color = _phong.calculateColor(scene, view, collisionPoint, normale, recursion);
        if (uv == Math::Vector2D{-1, -1})
            uv = getRandomCoordinates();
        perlinValue = perlinOctaves(uv.first, uv.second, _octaves, _persistence) * (_maxPerlin - _minPerlin) + _minPerlin;
        return {
            static_cast<unsigned int>(color.R * perlinValue),
            static_cast<unsigned int>(color.G * perlinValue),
            static_cast<unsigned int>(color.B * perlinValue)
        };
    }
} // ray


extern "C" ray::INode *create(const std::map<std::string, std::string> &attributes)
{
    if (attributes.find("color") == attributes.end())
        throw ray::NodeError("IMaterial: missing color attribute", "PerlinMaterial.cpp");
    if (attributes.find("shadow_quality") == attributes.end())
        throw ray::NodeError("IMaterial: missing shadow_quality attribute (number between 0 and 100 for render time)", "PerlinMaterial.cpp");
    if (attributes.find("ambiant_occlusion") == attributes.end())
        throw ray::NodeError("IMaterial: missing ambiant_occlusion attribute (number between 0 and 100 for render time)", "PerlinMaterial.cpp");
    if (attributes.find("roughness") == attributes.end())
        throw ray::NodeError("IMaterial: missing roughness attribute (number between 0 and 1 for material roughness)", "PerlinMaterial.cpp");
    if (attributes.find("octaves") == attributes.end())
        throw ray::NodeError("IMaterial: missing octaves attribute (number between 0 and +inf for Perlin Noise)", "PerlinMaterial.cpp");
    if (attributes.find("persistence") == attributes.end())
        throw ray::NodeError("IMaterial: missing persistence attribute (number between 0 and +inf for Perlin Noise)", "PerlinMaterial.cpp");
    if (attributes.find("min_perlin") == attributes.end())
        throw ray::NodeError("IMaterial: missing min_perlin attribute (number between 0 and 1 for Perlin Noise)", "PerlinMaterial.cpp");
    if (attributes.find("max_perlin") == attributes.end())
        throw ray::NodeError("IMaterial: missing max_perlin attribute (number between 0 and 1 for Perlin Noise)", "PerlinMaterial.cpp");

    Maybe<RGB> color = RGB::fromStr(attributes.at("color"));
    double shadowQuality = std::stod(attributes.at("shadow_quality"));
    double ambiantOcclusion = std::stod(attributes.at("ambiant_occlusion"));
    double roughness = std::stod(attributes.at("roughness"));
    int octaves = std::stoi(attributes.at("octaves"));
    double persistence = std::stod(attributes.at("persistence"));
    double minPerlin = std::stod(attributes.at("min_perlin"));
    double maxPerlin = std::stod(attributes.at("max_perlin"));

    if (!color.has_value())
        throw ray::NodeError("IMaterial: invalid color attribute", "PerlinMaterial.cpp");
    if (shadowQuality < 1 || shadowQuality > 100)
        throw ray::NodeError("IMaterial: shadow_quality must be a number between 1 and 100", "PerlinMaterial.cpp");
    if (ambiantOcclusion < 0 || ambiantOcclusion > 100)
        throw ray::NodeError("IMaterial: ambiant_occlusion must be a number between 0 and 100", "PerlinMaterial.cpp");
    if (roughness < 0 || roughness > 1)
        throw ray::NodeError("IMaterial: roughness must be a number between 0 and 1", "PerlinMaterial.cpp");
    if (octaves < 0)
        throw ray::NodeError("IMaterial: octaves must be a number between 0 and 1", "PerlinMaterial.cpp");
    if (persistence < 0)
        throw ray::NodeError("IMaterial: persistence must be a number between 0 and 1", "PerlinMaterial.cpp");
    if (minPerlin < 0 || minPerlin > 1)
        throw ray::NodeError("IMaterial: min_perlin must be a number between 0 and 1", "PerlinMaterial.cpp");
    if (maxPerlin < 0 || maxPerlin > 1)
        throw ray::NodeError("IMaterial: max_perlin must be a number between 0 and 1", "PerlinMaterial.cpp");

    return new ray::PerlinMaterial(color.value(), shadowQuality, ambiantOcclusion, roughness, octaves, persistence, minPerlin, maxPerlin);
}
