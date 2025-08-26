#ifndef _IMU_HPP
#define _IMU_HPP

#include "system.hpp"

/**
 * @brief Structure to hold IMU sensor values
 * @details This structure contains fields for acceleration, gyroscope, readings along the X, Y, and Z axes.
 * Each field is of type float to accommodate decimal values.
 */

 struct ImuData {
    float roll;  // Rotation around the X-axis in degrees
    float pitch; // Rotation around the Y-axis in degrees
    float yaw;   // Rotation around the Z-axis in degrees
};

/**
 * @brief Initializes the IMU sensor
 * @details This function sets up the IMU sensor for data acquisition.
 * It should be called before any other IMU-related functions.
 * @return status_t Returns 0 on success, non-zero error code on failure.
 */
status_t imu_init();

/**
 * @brief Acquires new IMU sensor data
 * @details This function retrieves the latest IMU sensor data.
 * It should be called after the IMU sensor has been initialized.
 * @param data Pointer to an ImuData structure to store the acquired data.
 * @return status_t Returns 0 on success, non-zero error code on failure.
 */
status_t imu_acquire_data(ImuData *data);

/**
 * @brief Serializes the IMU sensor for data transmission
 * @details This function serializes the IMU sensor data for transmission.
 * @param data Pointer to an ImuData structure containing the sensor data.
 * @param buffer Pointer to a buffer where the serialized data will be stored.
 * @return size_t Returns the number of bytes serialized, or 0 on failure.
 */
uint8_t imu_serialize_data(const ImuData *data, uint8_t *buffer);
#endif // _IMU_HPP