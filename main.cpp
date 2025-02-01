#include <iostream>
#include <string>
#include <fstream>
#include <array>
#include <cstdio> // For popen, pclose

#ifdef _WIN32
#include <winsock2.h> // Required for Windows
#pragma comment(lib, "ws2_32.lib") // Link with Winsock library
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <unistd.h> // For close
#endif

std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    FILE* pipe = _popen(cmd, "r");
    if (!pipe) {
        return "popen failed!";
    }
    while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
        result += buffer.data();
    }
    _pclose(pipe);
    return result;
}

int main() {
#ifdef _WIN32
    // Initialize Winsock (Windows only)
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed" << std::endl;
        return 1;
    }
#endif
    std::string networkingCmd;
    std::cout << "Please enter a networking command: ";
    std::cin >> networkingCmd;

    std::string netstatOutput = exec(networkingCmd.c_str());
    //std::cout << netstatOutput << std::endl;

    //std::string myString = "Hello, world!";
    std::ofstream outputFile("output.txt");

    if (outputFile.is_open()) {
        outputFile << netstatOutput;
        outputFile.close();
        std::cout << "String written to file successfully!" << std::endl;
    }
    else {
        std::cerr << "Error opening file!" << std::endl;
    }

    return 0;


#ifdef _WIN32
    // Cleanup Winsock (Windows only)
    WSACleanup();
#endif

    return 0;
}