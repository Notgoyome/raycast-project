/*
** EPITECH PROJECT, 2024
** B-OOP-400-MPL-4-1-raytracer-robin.glaude
** File description:
** Configuration
*/

#include "Configuration.hpp"

ray::Configuration::Configuration(std::string filename)
{
    (void) filename;
}

ray::Configuration::~Configuration()
{
}

std::vector<std::shared_ptr<ray::INode *>> ray::Configuration::getNodes() const
{
    return _nodes;
}
