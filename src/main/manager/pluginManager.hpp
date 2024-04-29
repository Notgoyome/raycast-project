/*
** EPITECH PROJECT, 2024
** B-OOP-400-MPL-4-1-raytracer-robin.glaude
** File description:
** pluginManager
*/

#include "DLClass.hpp"
#include <memory>
#include <string>

#ifndef PLUGINMANAGER_HPP_
#define PLUGINMANAGER_HPP_

namespace ray {
    template<typename T>
    class PluginManager {
        public:
            PluginManager();
            ~PluginManager();

            std::shared_ptr<T> loadPlugin(const std::string &pluginPath);
        private:
            DynamicPlugin _plugin;
    };

    template<typename T>
    PluginManager<T>::PluginManager()
    {
    }

    template<typename T>
    PluginManager<T>::~PluginManager()
    {
        _plugin.close();
    }

    template<typename T>
    std::shared_ptr<T> PluginManager<T>::loadPlugin(const std::string& path)
    {
        _plugin.open(path);
        auto allocator = _plugin.getSymbol<std::shared_ptr<T>(*)()>("allocator");
        if (!allocator) {
            _plugin.close();
            throw PluginManagerException("Failed to find allocator function");
        }
        auto destructor = _plugin.getSymbol<void(*)()>("destructor");
        if (!destructor) {
            _plugin.close();
            throw PluginManagerException("Failed to find destructor function");
        }
        std::shared_ptr<T> plugin = allocator();
        destructor();
        return plugin;
    }
}

#endif /* !PLUGINMANAGER_HPP_ */
