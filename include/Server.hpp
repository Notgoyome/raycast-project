/*
** EPITECH PROJECT, 2024
** B-OOP-400-MPL-4-1-raytracer-robin.glaude
** File description:
** Server
*/

#ifndef SERVER_HPP_
#define SERVER_HPP_

#include <iostream>
#include <string>
#include <cstring>
#include <exception>
#include <vector>
#include <deque>
#include <thread>
#include <mutex>
#include <map>
#include "Image.hpp"
#include "RGB.hpp"
#include "utils/mainMethods.hpp"
#include <libconfig.h++>

#ifdef _WIN32
    #include <winsock2.h>
    #pragma comment(lib, "ws2_32.lib")
#else
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <unistd.h>
#endif

namespace ray {
    class ServerException : public std::exception {
        public:
            ServerException(const std::string& message) : _message(message) {}
            const char* what() const noexcept override { return _message.c_str(); }
        private:
            std::string _message;
    };

    class Server {
        public:
            Server(int port, std::string cfgfile) : sockfd(-1), port(port), queue_size(30)
            {
                init_server();
                create_server_socket();
                bind_server_socket();
                start_server();
                cfg = openFile(cfgfile);
            }

            ~Server()
            {
                if (sockfd != -1) {
#ifdef _WIN32
                    closesocket(sockfd);
#else
                    close(sockfd);
#endif
                }

                for (int client_sockfd : client_sockets) {
#ifdef _WIN32
                    closesocket(client_sockfd);
#else
                    close(client_sockfd);
#endif
                }

                for (auto& pair : client_threads) {
                    if (pair.second.joinable()) {
                        pair.second.join();
                    }
                }
            }

            void accept_connections(int nb_clients)
            {
                for (int i = 0; i < nb_clients; ++i) {
                    struct sockaddr_in client_addr;
#ifdef _WIN32
                    int client_addr_len = sizeof(client_addr);
#else
                    socklen_t client_addr_len = sizeof(client_addr);
#endif
                    int client_sockfd = accept(sockfd, (struct sockaddr*)&client_addr, &client_addr_len);
                    if (client_sockfd < 0) {
                        throw ServerException("Failed to accept connection");
                    }
                    std::cout << "Client " << i << " connected" << std::endl;
                    client_sockets.push_back(client_sockfd);
                    client_threads[client_sockfd] = std::thread(&Server::monitor_client, this, client_sockfd);
                    send_data(client_sockfd, {"CFG", cfg});
                }
            }

            std::string openFile(const std::string& filename)
            {
                std::ifstream file(filename);
                if (!file.is_open()) {
                    throw ServerException("Failed to open file");
                }
                std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
                return content;
            }

            std::deque<std::pair<std::string, std::string>> get_client_data(int client_sockfd)
            {
                std::lock_guard<std::mutex> lock(data_mutex);
                return client_data[client_sockfd];
            }

            void close_client(int client_sockfd)
            {
                client_sockets.erase(std::remove(client_sockets.begin(), client_sockets.end(), client_sockfd), client_sockets.end());
#ifdef _WIN32
                closesocket(client_sockfd);
#else
                close(client_sockfd);
#endif
            }

            void send_data(int client_sockfd, const std::pair<std::string, std::string>& data)
            {
                std::string to_send = data.first + ":" + data.second + "\r\n";
                if (send(client_sockfd, to_send.c_str(), to_send.size(), 0) < 0) {
                    throw ServerException("Failed to send data");
                }
            }

            std::pair<std::string, std::string> receive_data(int client_sockfd)
            {
                char buffer[1024] = {0};
                std::string data;
                while (true) {
                    memset(buffer, 0, sizeof(buffer));
                    int n = recv(client_sockfd, buffer, sizeof(buffer) - 1, 0);
                    if (n < 0) {
                        throw ServerException("Failed to receive data");
                    }
                    data += buffer;
                    if (data.size() >= 2 && data.substr(data.size() - 2) == "\r\n") {
                        break;
                    }
                }
                data = data.substr(0, data.size() - 2);
                size_t pos = data.find(':');
                if (pos == std::string::npos) {
                    throw ServerException("Invalid data format");
                }
                return {data.substr(0, pos), data.substr(pos + 1)};
            }

            Image orchestrate_rendering(unsigned int width, unsigned int height,
                const std::shared_ptr<ray::IScene>& scene,
                const std::shared_ptr<ray::ICamera>& cam)
            {
                (void)scene;
                (void)cam;
                Image img;
                std::deque<std::pair<int, int>> bands;

                for (unsigned int i = 0; i < width; i++) {
                    for (unsigned int j = 0; j < height; j++) {
                        bands.push_back({i, j});
                    }
                }

                std::mutex bands_mutex;

                for (auto& pair : client_threads) {
                    pair.second = std::thread([&]() {
                        while (true) {
                            bands_mutex.lock();
                            if (bands.empty()) {
                                bands_mutex.unlock();
                                break;
                            }
                            std::pair<int, int> band = bands.front();
                            bands.pop_front();
                            bands_mutex.unlock();

                            send_data(pair.first, {"RENDER", std::to_string(band.first) + "," + std::to_string(band.second)});

                            std::pair<std::string, std::string> data = receive_data(pair.first);
                            if (data.first == "RENDERED") {
                                std::vector<std::string> xy = RayTracerUtils::renderTokenSpliter(data.second, ',');
                                int x = std::stoi(xy[0]);
                                int y = std::stoi(xy[1]);
                                RGB color;
                                color.R = std::stoi(xy[2]);
                                color.G = std::stoi(xy[3]);
                                color.B = std::stoi(xy[4]);
                                img.addPixel(Math::Vector2D{static_cast<double>(x), static_cast<double>(y)}, color);
                            }
                        }
                    });
                }

                for (auto& pair : client_threads) {
                    if (pair.second.joinable()) {
                        pair.second.join();
                    }
                }

                return img;
            }

        private:
            void init_server()
            {
                addr.sin_port = htons(port);
                addr.sin_family = AF_INET;
                addr.sin_addr.s_addr = INADDR_ANY;
            }

            void create_server_socket()
            {
#ifdef _WIN32
                WSADATA wsa;
                if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) {
                    throw ServerException("Failed to initialise winsock");
                }
#endif
                sockfd = socket(AF_INET, SOCK_STREAM, 0);
                if (sockfd == -1) {
                    throw ServerException("Socket creation failed");
                }
            }

            void bind_server_socket()
            {
                int e = bind(sockfd, (struct sockaddr *) &addr, sizeof(addr));
                if (e < 0) {
                    throw ServerException("Bind failed");
                }
            }

            void start_server()
            {
                if (listen(sockfd, queue_size) < 0) {
                    throw ServerException("Listen failed");
                }
            }

            void monitor_client(int client_sockfd)
            {
                while (true) {
                    char buffer[1];
                    int n;
#ifdef _WIN32
                    n = recv(client_sockfd, buffer, sizeof(buffer), 0);
#else
                    n = read(client_sockfd, buffer, sizeof(buffer));
#endif
                    if (n <= 0) {
                        close_client(client_sockfd);
                        return;
                    } else {
                        std::pair<std::string, std::string> data = receive_data(client_sockfd);
                        std::lock_guard<std::mutex> lock(data_mutex);
                        client_data[client_sockfd].push_back(data);
                    }
                }
            }

            int sockfd;
            int port;
            int queue_size;
            struct sockaddr_in addr;
            std::vector<int> client_sockets;
            std::map<int, std::deque<std::pair<std::string, std::string>>> client_data;
            std::map<int, std::thread> client_threads;
            std::mutex data_mutex;
            std::string cfg;
    };
}

#endif /* !SERVER_HPP_ */
