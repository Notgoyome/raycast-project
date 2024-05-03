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
        unsigned int background_r;
        unsigned int background_g;
        unsigned int background_b;

        static std::shared_ptr<libconfig::Config> openFile(const std::string& filename);
        void parseNodes(const std::shared_ptr<libconfig::Config>& cfg);
        void buildTree(const libconfig::Setting& setting, const std::shared_ptr<INode>& parent);
        void parseHierarchy(const std::shared_ptr<libconfig::Config>& cfg);
        void parseBackgroundColor(const std::shared_ptr<libconfig::Config>& cfg);

    public:
        NodeBuilder(const std::string& filename);

        [[nodiscard]] const std::vector<std::shared_ptr<INode>>& getRootNodes() const { return rootNodes; }
        [[nodiscard]] RGB getBackgroundColor() const { return {background_r, background_g, background_b}; }
    };
}

#endif /* !NODEBUILDER_HPP_ */
