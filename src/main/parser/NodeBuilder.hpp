/*
** EPITECH PROJECT, 2024
** B-OOP-400-MPL-4-1-raytracer-robin.glaude
** File description:
** NodeBuilder
*/

#include "NodeFactory.hpp"

#ifndef NODEBUILDER_HPP_
#define NODEBUILDER_HPP_

#include <libconfig.h++>
#include <map>
#include <vector>
#include <memory>
#include "RGB.hpp"

namespace ray {
    class NodeBuilderException : public std::exception {
        public:
            NodeBuilderException(const std::string& message) : _message(message) {}

            const char* what() const noexcept override { return _message.c_str(); }

        private:
            std::string _message;
    };

    class NodeBuilder {
        private:
            std::map<int, std::shared_ptr<INode>> nodeMap;
            std::vector<std::shared_ptr<INode>> rootNodes;
            int background_r;
            int background_g;
            int background_b;

        public:
            NodeBuilder(const std::string& filename)
            {
                libconfig::Config cfg;
                try {
                    cfg.readFile(filename.c_str());
                } catch (const libconfig::ParseException &pex) {
                    std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine()
                              << " - " << pex.getError() << std::endl;
                }

                const libconfig::Setting& nodes = cfg.lookup("nodes");
                for (int i = 0; i < nodes.getLength(); ++i) {
                    const libconfig::Setting& node = nodes[i];
                    int id;
                    std::string typePath;
                    node.lookupValue("id", id);
                    node.lookupValue("type", typePath);

                    // propriétés
                    std::map<std::string, std::string> properties;
                    try {
                        const libconfig::Setting& props = node["properties"];
                        for (int j = 0; j < props.getLength(); ++j) {
                            const std::string propName = props[j].getName();
                            properties[propName] = props[j].c_str();
                        }
                    } catch (const libconfig::SettingNotFoundException &nfex) {
                        std::cerr << "Setting not found: " << nfex.getPath() << std::endl;
                    } catch (const libconfig::SettingTypeException &tex) {
                        std::cerr << "Type error in setting: " << tex.getPath() << std::endl;
                    } catch (const std::exception &ex) {
                        std::cerr << "General exception: " << ex.what() << std::endl;
                    }

                    auto createdNode = NodeFactory<INode>::create("plugins/" + typePath, properties);
                    if (!createdNode) {
                        throw NodeBuilderException("Failed to create node for ID " + std::to_string(id));
                    }
                    nodeMap[id] = createdNode;
                }

                // hiérarchie
                const libconfig::Setting& configs = cfg.lookup("config");
                for (int i = 0; i < configs.getLength(); ++i) {
                    const libconfig::Setting& config = configs[i];
                    int id;
                    config.lookupValue("id", id);

                    if (nodeMap.find(id) != nodeMap.end()) {
                        auto parentNode = nodeMap[id];
                        if (config.exists("children")) {
                            const libconfig::Setting& children = config["children"];
                            for (int j = 0; j < children.getLength(); ++j) {
                                int childId;
                                children[j].lookupValue("id", childId);
                                if (nodeMap.find(childId) != nodeMap.end()) {
                                    parentNode->addChild(nodeMap[childId]);
                                }
                            }
                        }
                        if (!config.exists("parent")) {
                            rootNodes.push_back(parentNode);
                        }
                    }
                }

                // background color
                try {
                    const libconfig::Setting& settings = cfg.lookup("settings");
                    for (int i = 0; i < settings.getLength(); ++i) {
                        const libconfig::Setting& setting = settings[i];
                        if (setting.exists("background_color")) {
                            const libconfig::Setting& color = setting["background_color"];
                            int r, g, b;
                            color.lookupValue("r", r);
                            color.lookupValue("g", g);
                            color.lookupValue("b", b);
                            background_r = r;
                            background_g = g;
                            background_b = b;
                        }
                    }
                } catch (const libconfig::SettingNotFoundException &nfex) {
                    throw NodeBuilderException("Missing 'settings' in configuration file.");
                }
            }

            const std::vector<std::shared_ptr<INode>>& getRootNodes() const { return rootNodes; }
    };
}

#endif /* !NODEBUILDER_HPP_ */
