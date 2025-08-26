#ifndef __PROCESS_H__
#define __PROCESS_H__
#include "esp_err.h"
#include "ui.h"
#include "lvgl_port.h"
#include "esp_log.h"
#include "lvgl.h"

/**
 * @brief enum to represent the type of sensor or actuator
*/
typedef enum MessageType {
    MSG_IIS = 1,
    MSG_GPS = 2,
    MSG_IMU = 3,
    MSG_BMP = 4,
    MSG_MOD = 5,
    MSG_STA = 6,
    MSG_NBM = 7

} messageType_t;

/**
 * @brief Function to update the UI with the latest data from the sensor and actuators
 * @param[in] data: Pointer to the data structure containing the latest sensor and actuator data
 * @return ESP_OK on success, error code otherwise
 */
esp_err_t update_ui(uint8_t *data , messageType_t msg_type);

esp_err_t ui_update_iis_data(uint8_t *data);
esp_err_t ui_update_gps_data(uint8_t *data);
esp_err_t ui_update_imu_data(uint8_t *data);
esp_err_t ui_update_bmp_data(uint8_t *data);
esp_err_t ui_update_mod_data(uint8_t *data);
esp_err_t ui_update_sta_data(uint8_t *data);
esp_err_t ui_update_nbm_data(uint8_t *data);
#endif // __PROCESS_H__