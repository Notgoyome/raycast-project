/*
** EPITECH PROJECT, 2024
** B-OOP-400-MPL-4-1-raytracer-robin.glaude
** File description:
** Renderer
*/

#ifndef RENDERER_HPP_
#define RENDERER_HPP_

#include <iostream>
#include <exception>

namespace ray {
    class RendererException : public std::exception {
        public:
            RendererException(const std::string &message) : _message(message) {}
            const char *what() const noexcept override { return _message.c_str(); }
        private:
            std::string _message;
    };

    class Renderer {
        public:
            Renderer();
            ~Renderer();

        private:
    };
}

#endif /* !RENDERER_HPP_ */
