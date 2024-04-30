/*
** EPITECH PROJECT, 2024
** B-OOP-400-MPL-4-1-raytracer-robin.glaude
** File description:
** pluginManager
*/

#ifndef NODEFACTORY_HPP_
#define NODEFACTORY_HPP_

#include "DLClass.hpp"
#include "INode.hpp"
#include <map>

namespace ray {
    class NodeFactoryException : public std::exception {
    public:
        NodeFactoryException(const std::string& message) : _message(message) {}
        const char* what() const noexcept override { return _message.c_str(); }
    private:
        std::string _message;
    };

    template<typename T>
    class NodeFactory {
    public:
        static std::shared_ptr<T> create(const std::string& type, const std::map<std::string, std::string>& properties) {
            ray::DynamicPlugin plugin;
            try {
                plugin.open(type);
                auto create_fun = plugin.getSymbol<T*(*)(const std::map<std::string, std::string>&)>("create");
                T* instance = create_fun(properties);
                return std::shared_ptr<T>(instance, [&plugin](T* p) { delete p; plugin.close(); });
            } catch (const ray::NodeFactoryException& e) {
                std::cerr << "Factory error: " << e.what() << std::endl;
                return nullptr;
            }
        }
    };
}

#endif /* !NODEFACTORY_HPP_ */
