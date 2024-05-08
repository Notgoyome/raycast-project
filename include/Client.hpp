/*
** EPITECH PROJECT, 2024
** B-OOP-400-MPL-4-1-raytracer-robin.glaude
** File description:
** Client
*/

#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#include <iostream>
#include <string>
#include <exception>
#include <deque>
#include <thread>
#include <mutex>
#include <cstring>
#include "utils/mainMethods.hpp"

#ifdef _WIN32
    #include <winsock2.h>
    #pragma comment(lib, "ws2_32.lib")
#else
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <unistd.h>
    #include <arpa/inet.h>
#endif

namespace ray {
    class ClientException : public std::exception {
        public:
            ClientException(const std::string& message) : _message(message) {}
            const char* what() const noexcept override { return _message.c_str(); }
        private:
            std::string _message;
    };

    class Client {
        public:
            Client(const std::string& ip, int port) : sockfd(-1), port(port), ip(ip)
            {
                init_client();
                create_client_socket();
                connect_to_server();
            }

            ~Client()
            {
                if (sockfd != -1) {
#ifdef _WIN32
                    closesocket(sockfd);
#else
                    close(sockfd);
#endif
                }
            }

            std::pair<std::string, std::string> get_next_data()
            {
                std::lock_guard<std::mutex> lock(data_mutex);
                if (data_queue.empty()) {
                    return {"", ""};
                }
                std::pair<std::string, std::string> data = data_queue.front();
                data_queue.pop_front();
                return data;
            }

            void send_data(const std::pair<std::string, std::string>& data)
            {
                std::string to_send = data.first + ":" + data.second + "\r\n";
                if (send(sockfd, to_send.c_str(), to_send.size(), 0) < 0) {
                    throw ClientException("Failed to send data");
                }
            }

            std::pair<std::string, std::string> receive_data()
            {
                char buffer[1024] = {0};
                std::string data;
                while (true) {
                    memset(buffer, 0, sizeof(buffer));
                    int n = recv(sockfd, buffer, sizeof(buffer) - 1, 0);
                    if (n <= 0) {
#ifdef _WIN32
                        closesocket(sockfd);
#else
                        close(sockfd);
#endif
                        throw ClientException("Failed to receive data");
                    }
                    data += buffer;
                    if (data.size() >= 2 && data.substr(data.size() - 2) == "\r\n") {
                        break;
                    }
                    std::cout << "Received partial data" << std::endl;
                }
                size_t pos = data.find(':');
                if (pos == std::string::npos) {
                    throw ClientException("Invalid data format");
                }
                std::cout << "Received " << data << std::endl;
                return {data.substr(0, pos), data.substr(pos + 1, data.size() - pos - 3)};
            }

            void render(std::pair<std::string, std::string> data)
            {
                std::cout << "New command : \"" << data.first << "\" \""<< data.second << "\"" << std::endl;
                if (data.first == "RENDER") {
                    std::cout << "Rendering" << std::endl;
                    std::string coordinates = data.second;
                    std::string response = "";
                    std::vector<std::string> coords = RayTracerUtils::renderTokenSpliter(coordinates, ';');
                    for (const std::string& coord : coords) {
                        std::vector<std::string> xy = RayTracerUtils::renderTokenSpliter(coord, ',');
                        int x = std::stoi(xy[0]);
                        int y = std::stoi(xy[1]);
                        RGB color = RayTracerUtils::renderPixel(scene, camera, x, y, backgroundColor);
                        response += std::to_string(x) + "," + std::to_string(y) + ":" + std::to_string(color.R) + "," + std::to_string(color.G) + "," + std::to_string(color.B) + ";";
                    }
                    send_data({"RENDERED", response});
                    std::cout << "Sent RENDERED:" << response << std::endl;
                }
            }

            void monitor()
            {
                while (true) {
                    fd_set read_fds;
                    FD_ZERO(&read_fds);
                    FD_SET(sockfd, &read_fds);

                    int activity = select(sockfd + 1, &read_fds, NULL, NULL, NULL);

                    if (activity < 0) {
                        throw ClientException("Error in select");
                    }

                    if (FD_ISSET(sockfd, &read_fds)) {
                        std::cout << "Data received" << std::endl;
                        std::pair<std::string, std::string> data = receive_data();
                        render(data);
                    }
                }
            }

        private:
            void init_client()
            {
                addr.sin_port = htons(port);
                addr.sin_family = AF_INET;
#ifdef _WIN32
                struct sockaddr_in sa;
                INT sa_len = sizeof(sa);
                std::wstring wip(ip.begin(), ip.end());
                if (WSAStringToAddress((LPWSTR)wip.c_str(), AF_INET, NULL, (struct sockaddr*)&sa, &sa_len) == SOCKET_ERROR) {
                    throw ClientException("Invalid IP address");
                }
                addr.sin_addr = sa.sin_addr;
#else
                if (inet_pton(AF_INET, ip.c_str(), &(addr.sin_addr)) <= 0) {
                    throw ClientException("Invalid IP address");
                }
#endif
            }

            void create_client_socket()
            {
#ifdef _WIN32
                WSADATA wsa;
                if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) {
                    throw ClientException("Failed to initialise winsock");
                }
#endif
                sockfd = socket(AF_INET, SOCK_STREAM, 0);
                if (sockfd == -1) {
                    throw ClientException("Socket creation failed");
                }
            }

            void connect_to_server()
            {
                if (connect(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
                    throw ClientException("Connection to server failed");
                }
                std::pair<std::string, std::string> data = receive_data();
                if (data.first == "CFG") {
                    NodeBuilder builder(data.second, true);
                    rootNodes = builder.getRootNodes();
                    imageData = builder.getImageData();
                    scene = std::dynamic_pointer_cast<IScene>(RayTracerUtils::getScene(rootNodes));
                    scene->initValues();
                    camera = RayTracerUtils::getCamera(scene);
                    
                }
            }

            int sockfd;
            int port;
            std::string ip;
            struct sockaddr_in addr;
            std::deque<std::pair<std::string, std::string>> data_queue;
            std::mutex data_mutex;
            std::thread monitor_thread;
            image_data_t imageData;
            RGB backgroundColor;
            std::vector<std::shared_ptr<INode>> rootNodes;
            std::shared_ptr<IScene> scene;
            std::shared_ptr<ICamera> camera;
    };
}

#endif /* !CLIENT_HPP_ */
