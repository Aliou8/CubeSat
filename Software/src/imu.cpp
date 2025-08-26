#include "imu.hpp"
#include <iostream>

using namespace std;

status_t imu_init() {
    // Initialize IMU hardware and return success status
    cout << "IMU initialized successfully..." << endl;

    return STATUS_OK;
}

status_t imu_acquire_data(ImuData *data) {
    // Acquire IMU data and store it in the provided data structure
    cout << "Acquiring IMU data..." << endl;
    data->pitch = rand_float(-90.0f, 90.0f);
    data->roll  = rand_float(-180.0f, 180.0f);
    data->yaw   = rand_float(-180.0f, 180.0f);

    return STATUS_OK;
}

uint8_t imu_serialize_data(const ImuData *data, uint8_t *buffer)
{
    // Serialize IMU data into the provided buffer
    uint8_t *ptr = buffer;
    memcpy(ptr, &data->roll, sizeof(data->roll));
    printf("roll: %.2f\n", data->roll);
    ptr += sizeof(data->roll);
    memcpy(ptr, &data->pitch, sizeof(data->pitch));
    ptr += sizeof(data->pitch);
    memcpy(ptr, &data->yaw, sizeof(data->yaw));
    ptr += sizeof(data->yaw);

    return ptr - buffer;
}