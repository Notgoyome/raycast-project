/*
** EPITECH PROJECT, 2024
** B-OOP-400-MPL-4-1-raytracer-robin.glaude
** File description:
** Configuration
*/


#ifndef CONFIGURATION_HPP_
#define CONFIGURATION_HPP_

#include <iostream>
#include <exception>
#include <vector>
#include <memory>
#include <string>

#include "INode.hpp"
#include "RGB.hpp"

namespace ray {
    class ConfigurationException : public std::exception {
        public:
            ConfigurationException(const std::string &message) : _message(message) {}
            const char *what() const noexcept override { return _message.c_str(); }
        private:
            std::string _message;
    };

    class Configuration {
        public:
            Configuration(std::string filename);
            ~Configuration();

            std::vector<std::shared_ptr<ray::INode *>>getNodes() const;
        private:
            std::vector<std::shared_ptr<ray::INode *>> _nodes;
            RGB _background;
    };
}

#endif /* !CONFIGURATION_HPP_ */
