#ifndef _MAGNETOMETER_HPP
#define _MAGNETOMETER_HPP

#include "system.hpp"

/**
 * @brief Structure to hold magnetometer sensor values
 * @details This structure contains fields for magnetic field strength along the X, Y, and Z axes.
 * Each field is of type float to accommodate decimal values.
 */
struct MagnetometerData {
    float magneticAngleNorth; // Angle relative to magnetic north in degrees
};
/**
 * @brief Initializes the magnetometer sensor
 * @details This function sets up the magnetometer sensor for data acquisition.
 * It should be called before any other magnetometer-related functions.
 * @return status_t Returns 0 on success, non-zero error code on failure.
 */
status_t magnetometer_init();
/**
 * @brief Acquires magnetometer sensor data
 * @details This function acquires magnetic field strength along the X, Y, and Z axes from the magnetometer sensor.
 * @param data Pointer to a MagnetometerData structure to store the acquired data.
 * @return status_t Returns 0 on success, non-zero error code on failure.
 */
status_t magnetometer_acquire_data(MagnetometerData *data);

/**
 * @brief Serialize the magnetometer data for transmission
 * @details This function serializes the magnetometer data in a format suitable for transmission over a network.
 * @param data Pointer to a MagnetometerData structure containing the acquired data.
 * @param buffer Pointer to a buffer where the serialized data will be stored.
 * @return size_t Returns the number of bytes written to the buffer.
 */
uint8_t magnetometer_serialize_data(const MagnetometerData *data, uint8_t *buffer);
#endif // _MAGNETOMETER_HPP