#ifndef _GPS_HPP
#define _GPS_HPP

#include "system.hpp"
#include <string>

using std::string;
/**
 * @brief Structure to hold GPS data
 * @details This structure contains fields for latitude, longitude, altitude, and timestamp.
 * Each field is of type float to accommodate decimal values, except for timestamp which is a string.
 */
typedef struct GPSData {
    float latitude;
    float longitude;
    float altitude;
    float speed;
    float precision;
    char timestamp[20];

} GPSData_t;

/**
 * @brief Initializes the GPS module
 * @details This function sets up the GPS module for data acquisition.
 * It should be called before any other GPS-related functions.
 * @return status_t Returns 0 on success, non-zero error code on failure.
 */
status_t gps_init();

/**
 * @brief Acquires and processes GPS data
 * @details This function acquires GPS data from the module and processes it.
 * It should be called periodically to get the latest GPS data.
 * @param data Pointer to a GPSData structure to store the acquired data.
 * @return status_t Returns 0 on success, non-zero error code on failure.
 */
status_t gps_acquire_data(GPSData_t *data);

/**
 * @brief Serializes the GPS module for data acquisition
 * @details This function serializes the data for transmission, converting it to a format suitable for transmission over a serial link..
 * @param data Pointer to a GPSData structure containing the acquired data.
 * @param buffer Pointer to a character buffer to store the serialized data.
 * @return size_t Returns the number of bytes written to the buffer.
 */
uint8_t gps_serialize_data(const GPSData_t* data, uint8_t* buffer);

#endif // _GPS_HPP