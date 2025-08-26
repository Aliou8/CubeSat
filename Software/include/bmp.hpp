#ifndef _BMP_HPP
#define _BMP_HPP

#include "system.hpp"
/**
 * @brief Structure to hold BMP sensor values
 * @details This structure contains fields for temperature, pressure, humidity, and vertical speed.
 * Each field is of type float to accommodate decimal values.
 */
typedef struct BMP_VALUES {
    float temperature;
    float pressure;
    float humidity;
    float verticalSpeed;
} bmp_values_t;

/**
 * @brief Initializes the BMP sensor
 * @details This function sets up the BMP sensor for data acquisition.
 * It should be called before any other BMP-related functions.
 * @return status_t Returns 0 on success, non-zero error code on failure.
 */
status_t bmp_init(void);

/**
 * @brief Acquires BMP sensor data
 * @details This function acquires temperature, pressure, altitude, humidity, and vertical speed from the BMP sensor.
 * @param values Pointer to a BMP_VALUES structure to store the acquired data.
 * @return status_t Returns 0 on success, non-zero error code on failure.
 */
status_t bmp_acquire_data(bmp_values_t *values);

/**
 * @brief Serializes BMP sensor data for transmission
 * @details This function serializes the BMP sensor data for transmission, 
 * converting it to a format suitable for transmission over a serial link.
 * @param values Pointer to a BMP_VALUES structure containing the acquired data.
 * @param buffer Pointer to a buffer to store the serialized data.
 * @return size_t Returns the number of bytes written to the buffer.
 */
uint8_t bmp_serialize_data(const bmp_values_t* values, uint8_t* buffer);

#endif // _BMP_HPP