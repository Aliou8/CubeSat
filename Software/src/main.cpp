#include <iostream>
#include <winsock2.h>
#include <thread>
#include <chrono>
#include <semaphore.h>


// Sémaphore global pour protéger std::cout
sem_t semaphore;

// =======================
// Fonction du serveur
// =======================
void runServer() {
    // Initialiser Winsock pour le serveur
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(8080);

    bind(serverSocket, (sockaddr *)&serverAddress, sizeof(serverAddress));
    listen(serverSocket, SOMAXCONN);

    sem_wait(&semaphore);
    std::cout << "[SERVEUR] En attente d'une connexion..." << std::endl;
    sem_post(&semaphore);

    SOCKET clientSocket = accept(serverSocket, nullptr, nullptr);

    sem_wait(&semaphore);
    std::cout << "[SERVEUR] Client connecté !" << std::endl;
    sem_post(&semaphore);

    char buffer[1024];
    int bytesReceived;
    while (true) {
        ZeroMemory(buffer, 1024);
        bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);

        if (bytesReceived > 0) {
            sem_wait(&semaphore);
            std::cout << "[SERVEUR] Reçu : " << std::string(buffer, 0, bytesReceived) << std::endl;
            sem_post(&semaphore);
        } else {
            break;
        }
    }

    closesocket(clientSocket);
    closesocket(serverSocket);
    WSACleanup();

    sem_wait(&semaphore);
    std::cout << "[SERVEUR] Arrêt." << std::endl;
    sem_post(&semaphore);
}

// =======================
// Fonction du client
// =======================
void runClient() {
    // Petite pause pour laisser le serveur démarrer
    std::this_thread::sleep_for(std::chrono::seconds(1));

    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in server{};
    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(sock, (sockaddr *)&server, sizeof(server)) == SOCKET_ERROR) {
        sem_wait(&semaphore);
        std::cerr << "[CLIENT] Impossible de se connecter au serveur." << std::endl;
        sem_post(&semaphore);
        closesocket(sock);
        WSACleanup();
        return;
    }

    sem_wait(&semaphore);
    std::cout << "[CLIENT] Connecté au serveur !" << std::endl;
    sem_post(&semaphore);

    for (int i = 0; i < 5; i++) {
        std::string message = "Message " + std::to_string(i);
        send(sock, message.c_str(), message.size(), 0);

        sem_wait(&semaphore);
        std::cout << "[CLIENT] Envoyé : " << message << std::endl;
        sem_post(&semaphore);

    }

    closesocket(sock);
    WSACleanup();

    sem_wait(&semaphore);
    std::cout << "[CLIENT] Déconnexion." << std::endl;
    sem_post(&semaphore);
}

// =======================
// Programme principal
// =======================
int main() {
    // Forcer le console à utiliser UTF-8
    SetConsoleOutputCP(CP_UTF8);
    // Init du sémaphore (compteur = 1, donc exclusif)
    sem_init(&semaphore, 0, 1);

    // Lancer serveur + client dans des threads séparés
    std::thread serverThread(runServer);
    std::thread clientThread(runClient);

    serverThread.join();
    clientThread.join();

    sem_destroy(&semaphore);

    sem_wait(&semaphore);
    std::cout << "[MAIN] Programme terminé." << std::endl;
    sem_post(&semaphore);

    return 0;
}
