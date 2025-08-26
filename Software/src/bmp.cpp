#include "bmp.hpp"
#include <iostream>

using namespace std;

status_t bmp_init(void) {
    // Initialize BMP sensor
    // Return success or failure based on initialization result
    cout << "BMP initialized successfully..." << endl;
    return STATUS_OK;
}

status_t bmp_acquire_data(bmp_values_t* values) {
    // Acquire BMP sensor data
    // Populate the values structure with the acquired data
    cout << "Acquiring BMP sensor data..." << endl;
    values->temperature = rand_float(-40.0, 85.0);
    values->pressure = rand_float(98000.0, 103000.0);
    values->humidity = rand_float(0.0, 100.0);
    values->verticalSpeed = rand_float(-50.0, 50.0);
    return STATUS_OK;
}

uint8_t bmp_serialize_data(const bmp_values_t* values, uint8_t* buffer) {
    uint8_t* ptr = buffer;
    memcpy(ptr, &values->temperature, sizeof(values->temperature));
    ptr += sizeof(values->temperature);
    memcpy(ptr, &values->pressure, sizeof(values->pressure));
    ptr += sizeof(values->pressure);
    memcpy(ptr, &values->humidity, sizeof(values->humidity));
    ptr += sizeof(values->humidity);
    memcpy(ptr, &values->verticalSpeed, sizeof(values->verticalSpeed));
    ptr += sizeof(values->verticalSpeed);

    return (uint8_t)(ptr - buffer);  // nb d’octets écrits
}
