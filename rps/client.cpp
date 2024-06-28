#include <iostream>
#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")

enum class Move { ROCK, PAPER, SCISSORS, INVALID };

Move getMoveFromString(const std::string& moveStr) {
    if (moveStr == "rock") return Move::ROCK;
    if (moveStr == "paper") return Move::PAPER;
    if (moveStr == "scissors") return Move::SCISSORS;
    return Move::INVALID;
}

void playGame(SOCKET clientSocket) {
    char buffer[1024] = { 0 };

    while (true) {
        std::string move;
        std::cout << "Enter your move (rock, paper, scissors): ";
        std::cin >> move;

        if (send(clientSocket, move.c_str(), move.length(), 0) == SOCKET_ERROR) {
            std::cerr << "Send failed: " << WSAGetLastError() << std::endl;
            break;
        }

        memset(buffer, 0, sizeof(buffer));
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived > 0) {
            std::cout << "Server reply: " << std::string(buffer, bytesReceived) << std::endl;
        }
        else if (bytesReceived == 0) {
            std::cout << "Connection closed." << std::endl;
            break;
        }
        else {
            std::cerr << "Recv failed: " << WSAGetLastError() << std::endl;
            break;
        }
    }

    closesocket(clientSocket);
}

int main() {
    std::string serverIP = "10.0.0.130"; // Replace with your server's IP address
    int port = 5000; // Replace with your server's port number

    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        std::cerr << "WSAStartup failed: " << iResult << std::endl;
        return 1;
    }

    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Socket creation failed: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 1;
    }

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    inet_pton(AF_INET, serverIP.c_str(), &serverAddress.sin_addr);

    if (connect(clientSocket, (sockaddr*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
        std::cerr << "Connection failed: " << WSAGetLastError() << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    std::cout << "Connected to server." << std::endl;

    playGame(clientSocket);

    WSACleanup();
    return 0;
}