#ifndef _SYSTEM_HPP
#define _SYSTEM_HPP

#include <winsock2.h>
#include <stdint.h>

typedef enum STATUS {
    STATUS_OK = 0,
    STATUS_ERROR = -1
} status_t;

typedef enum SYSTEM_MODE:uint8_t {
    MODE_NORMAL = 0,
    MODE_CALIBRATION = 1,
    MODE_STABILIZATION = 2,
    MODE_MISSION = 3

} system_mode_t;

typedef enum SYSTEM_STATUS:uint8_t {
    SYSTEM_ARMED = 0,
    SYSTEM_DISARMED = 1,
    SYSTEM_STANDBY = 2,
    SYSTEM_FLYING = 3
} system_status_t;

enum class MessageType : uint8_t {
    MSG_IIS = 1,
    MSG_GPS = 2,
    MSG_IMU = 3,
    MSG_BMP = 4,
    MSG_MOD = 5,
    MSG_STA = 6,
    MSG_NBM = 7

};
typedef struct Header{
    MessageType mode;
    uint8_t size;
} hex_header_t;

/**
 * @brief function to intialise socket 
 * @param server_ip address
 * @param server_port port number
 * @param sock socket descriptor
 * @return status_t
 * STATUS_OK if successful, STATUS_ERROR otherwise
 */
status_t init_socket(const char* server_ip, int server_port, SOCKET* sock);

/**
 * @brief function to send data over socket
 * @param sock socket descriptor
 * @param data data to send
 * @param size size of data to send
 * @return status_t
 * STATUS_OK if successful, STATUS_ERROR otherwise
 */
status_t send_data(SOCKET sock, const void* data, size_t size);

/**
 * @brief Function to give a random float value within a given range.
 * @param min Minimum value of the random float.
 * @param max Maximum value of the random float.
 * @return Random float value within the given range.
*/ 
float rand_float(float min, float max) ;

/**
 * @brief Function to deinitialise socket
 * @param sock socket descriptor
 * @return status_t
 */
 status_t deinit_socket(SOCKET* sock);
#endif // _SYSTEM_HPP


