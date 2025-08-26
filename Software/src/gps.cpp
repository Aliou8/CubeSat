#include "gps.hpp"
#include <iostream>

using namespace std;

status_t gps_init()
{
    // Initialize GPS module
    cout << "GPS module initialized successfully..." << endl;
    return STATUS_OK;
}

status_t gps_acquire_data(GPSData_t *data)
{
    // Acquire GPS data and store it in the provided structure
    cout << "GPS data acquired successfully." << endl;
    data->latitude = rand_float(-90.0, 90.0);
    data->longitude = rand_float(-180.0, 180.0);
    data->altitude = rand_float(0.0, 1000.0);
    data->speed = rand_float(0.0, 300.0);
    data->precision = rand_float(0.0, 100.0);
    // Set the timestamp to the current time
    time_t now = time(nullptr);
    tm *info = localtime(&now);
    strftime(data->timestamp, sizeof(data->timestamp), "%d-%m-%Y-%H-%M-%S", info);
    return STATUS_OK;
}

uint8_t gps_serialize_data(const GPSData_t* data, uint8_t* buffer)
{
    // Serialize GPS data into a byte buffer
    uint8_t* ptr = buffer;
    memcpy(ptr, &data->latitude, sizeof(data->latitude));
    ptr += sizeof(data->latitude);
    memcpy(ptr, &data->longitude, sizeof(data->longitude));
    ptr += sizeof(data->longitude);
    memcpy(ptr, &data->altitude, sizeof(data->altitude));
    ptr += sizeof(data->altitude);
    memcpy(ptr, &data->speed, sizeof(data->speed));
    ptr += sizeof(data->speed);
    memcpy(ptr, &data->precision, sizeof(data->precision));
    ptr += sizeof(data->precision);
    memcpy(ptr, &data->timestamp, sizeof(data->timestamp));
    ptr += sizeof(data->timestamp);
    
    return (uint8_t)(ptr - buffer);  // nb d’octets écrits
}
