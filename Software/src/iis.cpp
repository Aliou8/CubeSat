#include "iis.hpp"
#include <iostream>

using namespace std;

status_t magnetometer_init() {
    // Implement the initialization of the magnetometer
    cout << "Magnetometer initialized successfully..." << endl;
    return STATUS_OK;
}

status_t magnetometer_acquire_data(MagnetometerData *data){
    // Implement the acquisition of magnetometer data
    cout << "Acquiring magnetometer data..." << endl;
    // Generate random magnetic angle in degrees (0-360)
    data->magneticAngleNorth = rand_float(0.0 , 360.0);
    return STATUS_OK;
}

uint8_t magnetometer_serialize_data(const MagnetometerData *data, uint8_t *buffer)
{
    // Implement the serialization of magnetometer data into a byte buffer
    uint8_t *ptr = buffer;
    memcpy(ptr, &data->magneticAngleNorth, sizeof(data->magneticAngleNorth));
    
    return sizeof(data->magneticAngleNorth);
}