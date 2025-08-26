#include <iostream>
#include <winsock2.h>
#include <thread>
#include <chrono>
#include <semaphore.h>

//-----------------------------------------------------------
// Les includes pour les peripheriques
//-----------------------------------------------------------
#include "bmp.hpp"
#include "imu.hpp"
#include "iis.hpp"
#include "gps.hpp"
#include "system.hpp"

// Le buffer pour les données des peripheriques
#define BUFFER_SIZE 40
uint8_t rxBuffer[BUFFER_SIZE];
using namespace std;

int main(int argc, char const *argv[])
{
    if (argc!= 3) 
    {
        cerr << "Usage: you must give <server_ip> <server_port>" << endl;
        return 1;
    }
    
    // Les structures pour les données des peripheriques
    bmp_values_t bmpData;
    ImuData imuData;
    MagnetometerData magnetometerData;
    GPSData_t gpsData;
    // Initialise la bibliothèque Winsock et le socket pour le serveur
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    const char* SERVER_IP = argv[1];
    int SERVER_PORT = stoi(argv[2]);
    if (init_socket(SERVER_IP, SERVER_PORT, &sock)!= STATUS_OK) {
        cerr << "[CLIENT] Erreur lors de l'initialisation du socket" << endl;
        return 1;
    }

    // Initialise les peripheriques
    status_t status = bmp_init();
    if (status!= STATUS_OK) {
        cerr << "[CLIENT] Erreur lors de l'initialisation du BMP" << endl;
        return 1;
    }
    status = imu_init();
    if (status!= STATUS_OK) {
        cerr << "[CLIENT] Erreur lors de l'initialisation de l'IMU" << endl;
        return 1;
    }
    status = magnetometer_init();
    if (status!= STATUS_OK) {
        cerr << "[CLIENT] Erreur lors de l'initialisation de l'IIS" << endl;
        return 1;
    }
    status = gps_init();
    if (status!= STATUS_OK) {
        cerr << "[CLIENT] Erreur lors de l'initialisation du GPS" << endl;
        return 1;
    }
    // Boucle de communication avec le serveur
    while (true) {
        // Acquiert les données des peripheriques
        bmp_acquire_data(&bmpData);
        imu_acquire_data(&imuData);
        magnetometer_acquire_data(&magnetometerData);
        gps_acquire_data(&gpsData);
        this_thread::sleep_for(chrono::milliseconds(500));
        // Sérialise et envoie les données BMP
        uint8_t bmpSize = bmp_serialize_data(&bmpData, rxBuffer);
        hex_header_t bmpHeader = {MessageType::MSG_BMP, bmpSize};
        send_data(sock, &bmpHeader, sizeof(bmpHeader));
        send_data(sock, rxBuffer, bmpSize);
       /* this_thread::sleep_for(chrono::seconds(1));
        // Sérialise et envoie les données IMU
        uint8_t imuSize = imu_serialize_data(&imuData, rxBuffer);
        hex_header_t imuHeader = {MessageType::MSG_IMU, imuSize};
        send_data(sock, &imuHeader, sizeof(imuHeader));
        send_data(sock, rxBuffer, imuSize);
        this_thread::sleep_for(chrono::seconds(1));
        // Sérialise et envoie les données IIS
        uint8_t iisSize = magnetometer_serialize_data(&magnetometerData, rxBuffer);
        hex_header_t iisHeader = {MessageType::MSG_IIS, iisSize};
        send_data(sock, &iisHeader, sizeof(iisHeader));
        send_data(sock, rxBuffer, iisSize);
        this_thread::sleep_for(chrono::seconds(1));
        // Sérialise et envoie les données GPS
        uint8_t gpsSize = gps_serialize_data(&gpsData, rxBuffer);
        hex_header_t gpsHeader = {MessageType::MSG_GPS, gpsSize};
        send_data(sock, &gpsHeader, sizeof(gpsHeader));
        send_data(sock, rxBuffer, gpsSize);
        this_thread::sleep_for(chrono::seconds(1));
        // Evoie le mode du systeme
        int modeValue = rand() % 5; // Exemple de mode actuel
        system_mode_t currentMode = static_cast<system_mode_t>(modeValue);
        hex_header_t modeHeader = {MessageType::MSG_MOD, sizeof(currentMode)};
        send_data(sock, &modeHeader, sizeof(modeHeader));
        send_data(sock, &currentMode, sizeof(currentMode));
        this_thread::sleep_for(chrono::seconds(1));
        // Evoie le status du systeme
        int statusValue = rand() % 5; // Exemple de status actuel
        system_status_t currentStatus = static_cast<system_status_t>(statusValue); // Exemple de status actuel
        hex_header_t statusHeader = {MessageType::MSG_STA, sizeof(currentStatus)};
        send_data(sock, &statusHeader, sizeof(statusHeader));
        send_data(sock, &currentStatus, sizeof(currentStatus));
        this_thread::sleep_for(chrono::seconds(1));
        // Envoie un nmbreur aléatoire de satellites détectés
        uint8_t nbSatellites = rand() % 51; // Nombre aléatoire entre 0 et 50
        hex_header_t nbSatHeader = {MessageType::MSG_NBM, sizeof(nbSatellites)};
        send_data(sock, &nbSatHeader, sizeof(nbSatHeader));
        send_data(sock, &nbSatellites, sizeof(nbSatellites));
        // Attendre 1 seconde avant la prochaine acquisition
        this_thread::sleep_for(chrono::seconds(1));*/
    }
    // Deinitialise le socket pour le serveur
    if (deinit_socket(&sock)!= STATUS_OK) {
        cerr << "[CLIENT] Erreur lors de la déinitialisation du socket" << endl;
        return 1;
    }

    return 0;
}