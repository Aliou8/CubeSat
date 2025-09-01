#include "system.hpp"
#include <iostream>
#include <random>
using namespace std;

std::mt19937 rng(std::random_device{}());
float rand_float(float min, float max) {
    std::uniform_real_distribution<float> dist(min, max);
    return dist(rng);
}

status_t init_socket(const char* server_ip, int server_port, SOCKET* sock){
    // Initialize socket connection with the given server IP and port
    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server_port);
    server_addr.sin_addr.s_addr = inet_addr(server_ip);

    if(connect(*sock, (sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR){
        cerr << "[CLIENT] Failed to connect to server: "<< server_ip << " Error: " << WSAGetLastError() << endl;
        closesocket(*sock);
        WSACleanup();
        return STATUS_ERROR;
    }
    cout << "[CLIENT] Connected to server successfully!" << endl;
    return STATUS_OK;
}

status_t send_data(SOCKET sock, const void* data, size_t size){
    // Send the given data over the socket
    int sent_bytes = send(sock, static_cast<const char*>(data), size, 0);
    if(sent_bytes == -1){
        cerr << "[CLIENT] Failed to send data: " << WSAGetLastError() << endl;
        closesocket(sock);
        WSACleanup();
        return STATUS_ERROR;
    }
    cout << "[CLIENT] Sent " << sent_bytes << " bytes." << endl;
    return STATUS_OK;
}

status_t deinit_socket(SOCKET* sock ){
    // Deinitialize the socket connection
    closesocket(*sock);
    WSACleanup();
    cout << "[CLIENT] Socket connection deinitialized successfully." << endl;
    return STATUS_OK;
}

