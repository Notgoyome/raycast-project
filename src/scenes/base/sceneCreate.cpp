/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** sceneCreate.cpp
*/

#include "Scene.hpp"

extern "C" ray::INode *create(__attribute__((unused))const std::map<std::string, std::string> &attributes)
{
    return new ray::Scene();
}
