/*
** EPITECH PROJECT, 2024
** B-OOP-400-MPL-4-1-raytracer-robin.glaude
** File description:
** Configuration
*/


#ifndef CONFIGURATION_HPP_
#define CONFIGURATION_HPP_

#include <vector>
#include <memory>
#include <string>

#include "INode.hpp"

namespace ray {

    class Configuration {
        public:
            Configuration(std::string filename);
            ~Configuration();

        private:
            std::vector<std::shared_ptr<ray::INode *>> _nodes;
    };
}

#endif /* !CONFIGURATION_HPP_ */
