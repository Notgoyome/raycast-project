/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** NodeBuilder.cpp
*/

#include "NodeBuilder.hpp"

namespace ray {

    std::shared_ptr<libconfig::Config> NodeBuilder::openFile(const std::string& filename)
    {
        std::shared_ptr<libconfig::Config> cfg = std::make_shared<libconfig::Config>();
        try {
            cfg->readFile(filename.c_str());
        } catch (const libconfig::ParseException &pex) {
            std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine()
                      << " - " << pex.getError() << std::endl;
        }
        return cfg;
    }

    void NodeBuilder::parseNodes(const std::shared_ptr<libconfig::Config>& cfg)
    {
        const libconfig::Setting& nodes = cfg->lookup("nodes");
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
    }

    void NodeBuilder::buildTree(const libconfig::Setting &setting,
        const std::shared_ptr<INode>& parent)
    {
        int id = -1;
        setting.lookupValue("id", id);
        auto node = nodeMap[id];

        if (parent != nullptr) {
            parent->addChild(node);
        } else {
            rootNodes.push_back(node);
        }

        if (setting.exists("children")) {
            int count = setting["children"].getLength();
            for (int i = 0; i < count; ++i) {
                buildTree(setting["children"][i], node);
            }
        }
    }

    void NodeBuilder::parseHierarchy(const std::shared_ptr<libconfig::Config>& cfg)
    {
        const libconfig::Setting& configs = cfg->lookup("config");
        for (int i = 0; i < configs.getLength(); i++)
            buildTree(configs[i], nullptr);
    }

    void NodeBuilder::parseBackgroundColor(const std::shared_ptr<libconfig::Config>& cfg)
    {
        try {
            if (!cfg->exists("background"))
                throw NodeBuilderException("Background block is missing in the configuration file.");

            const libconfig::Setting& background = cfg->lookup("background");

            background.lookupValue("r", background_r);
            background.lookupValue("g", background_g);
            background.lookupValue("b", background_b);

        } catch (const libconfig::SettingNotFoundException &nfex) {
            std::cerr << "Setting not found: " << nfex.getPath() << std::endl;
            throw NodeBuilderException("Missing 'background' in configuration file.");
        }
    }

    NodeBuilder::NodeBuilder(const std::string &filename) : background_r(0), background_g(0), background_b(0)
    {
        std::shared_ptr<libconfig::Config> cfg = openFile(filename);

        parseNodes(cfg);
        parseHierarchy(cfg);
        parseBackgroundColor(cfg);
    }

}