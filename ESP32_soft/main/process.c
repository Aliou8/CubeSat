#include "process.h"

static const char *TAG = "process"; // Tag for logging

// Function to update the UI with the latest data from the sensor and actuators
esp_err_t update_ui(uint8_t *data , messageType_t msg_type )
{
    if (data == NULL) {
        ESP_LOGE(TAG, "Data pointer is NULL");
        return ESP_ERR_INVALID_ARG; // Return error if data pointer is NULL
    }
        ESP_LOGI(TAG, "UI label updated with: %s", data);
        switch (msg_type) {
            case MSG_IIS:
                ui_update_iis_data(data); // Update IIS data on the UI
                break;
            case MSG_GPS:
                ui_update_gps_data(data); // Update GPS data on the UI
                break;
            case MSG_IMU:
                ui_update_imu_data(data); // Update IMU data on the UI
                break;
            case MSG_BMP:
                ui_update_bmp_data(data); // Update BMP data on the UI
                break;
            case MSG_MOD:
                ui_update_mod_data(data); // Update Modem data on the UI
                break;
            case MSG_STA:
                ui_update_sta_data(data); // Update Station data on the UI
                break;
            case MSG_NBM:
                ui_update_nbm_data(data); // Update NBM data on the UI
                break;
            default:
                ESP_LOGW(TAG, "Unknown message type: %d", msg_type); // Log warning for unknown message type
                break;
        }
    return ESP_OK; // Return success
}

// Function to update the UI for iis data
esp_err_t ui_update_iis_data(uint8_t *data)
{
    if (data == NULL) {
        ESP_LOGE(TAG, "Data pointer is NULL");
        return ESP_ERR_INVALID_ARG; // Return error if data pointer is NULL
    }

    // Assuming data contains the necessary information to update the UI
    float magneticAngleNorth;
    memcpy(&magneticAngleNorth, data, sizeof(float));
    char buffer[16];
    snprintf(buffer, sizeof(buffer), "%.2f °", magneticAngleNorth);
    lv_label_set_text(ui_LabelAngMag, buffer); 
    lv_img_set_angle(ui_ImageMAG, (int16_t)(magneticAngleNorth * 10)); // Update the angle of the image
    return ESP_OK; // Return success
}
// Function to update the UI for gps data
esp_err_t ui_update_gps_data(uint8_t *data)
{
    if (data == NULL) {
        ESP_LOGE(TAG, "Data pointer is NULL");
        return ESP_ERR_INVALID_ARG; // Return error if data pointer is NULL
    }

    // Variables de destination
    float latitude, longitude, altitude, speed, precision;
    char timestamp[20];   // "dd-mm-YYYY-HH-MM-SS" + '\0'
    char date[11];        // "dd-mm-YYYY" + '\0'
    char time[9];         // "HH:MM:SS" + '\0'

    // Désérialisation
    char buffer[17];
    uint8_t *ptr = data;

    memcpy(&latitude, ptr, sizeof(latitude));
    lv_snprintf(buffer, sizeof(buffer), "%.3f", latitude);
    ESP_LOGI(TAG, "Latitude: %s", buffer);
    lv_label_set_text(ui_LatVal, buffer);
    ptr += sizeof(latitude);

    memcpy(&longitude, ptr, sizeof(longitude));
    lv_snprintf(buffer, sizeof(buffer), "%.3f", longitude);
    ESP_LOGI(TAG, "Longitude: %s", buffer);
    lv_label_set_text(ui_LongVal, buffer);
    ptr += sizeof(longitude);

    memcpy(&altitude, ptr, sizeof(altitude));
    snprintf(buffer, sizeof(buffer), "%.3f m", altitude);
    ESP_LOGI(TAG, "Altitude: %s", buffer);
    lv_label_set_text(ui_AltVal, buffer);
    ptr += sizeof(altitude);

    memcpy(&speed, ptr, sizeof(speed));
    lv_snprintf(buffer, sizeof(buffer), "%.1f Km/s", speed);
    ESP_LOGI(TAG, "Speed: %s", buffer);
    lv_label_set_text(ui_SpeedVal, buffer);
    ptr += sizeof(speed);

    memcpy(&precision, ptr, sizeof(precision));
    ptr += sizeof(precision);

    memcpy(timestamp, ptr, sizeof(timestamp)); 
    ptr += sizeof(timestamp);

    // Séparer date et time à partir de timestamp
    int day, month, year, hour, min, sec;
    if (sscanf(timestamp, "%d-%d-%d-%d-%d-%d",
               &day, &month, &year, &hour, &min, &sec) == 6)
    {
        snprintf(date, sizeof(date), "%02d-%02d-%04d", day, month, year);
        snprintf(time, sizeof(time), "%02d:%02d:%02d", hour, min, sec);
    }
    
    else {
        ESP_LOGE(TAG, "Failed to parse timestamp: %s", timestamp);
        return ESP_FAIL;
    }

    // Ici tu peux mettre à jour ton UI avec les nouvelles valeurs
        lv_label_set_text(ui_TimeVal, time);
        lv_label_set_text(ui_DateVal, date);

    ESP_LOGI(TAG, "GPS data updated: lat=%.6f, lon=%.6f, alt=%.2f, speed=%.2f, precision=%.2f, date=%s, time=%s",
             latitude, longitude, altitude, speed, precision, date, time);

    return ESP_OK; // Return success
}
// Function to update the UI for imu data
esp_err_t ui_update_imu_data(uint8_t *data)
{
    if (data == NULL) {
        ESP_LOGE(TAG, "Data pointer is NULL");
        return ESP_ERR_INVALID_ARG; // Return error if data pointer is NULL
    }

    // Assuming data contains the necessary information to update the UI
    float roll;
    memcpy(&roll, data, sizeof(float));
    //memcpy(&pitch, data + sizeof(float), sizeof(float));
    //memcpy(&yaw, data + 2 * sizeof(float), sizeof(float));
    char buffer[16];
    snprintf(buffer, sizeof(buffer), "%.1f °", roll);
    lv_label_set_text(ui_LabelAngIMU, buffer); 
    lv_img_set_angle(ui_ImageIMU, (int16_t)(roll * 10)); // Update the angle of the image

    return ESP_OK; // Return success
}

// Function to update the UI for bmp data
esp_err_t ui_update_bmp_data(uint8_t *data)
{
    if (data == NULL) {
        ESP_LOGE(TAG, "Data pointer is NULL");
        return ESP_ERR_INVALID_ARG; // Return error if data pointer is NULL
    }

    // Assuming data contains the necessary information to update the UI
    float temperature, pressure , himidity , verticalSpeed;
    memcpy(&temperature, data, sizeof(float));
    memcpy(&pressure, data + sizeof(float), sizeof(float));
    memcpy(&himidity, data + 2 * sizeof(float), sizeof(float));
    memcpy(&verticalSpeed, data + 3 * sizeof(float), sizeof(float));

    char buffer[16];
    snprintf(buffer, sizeof(buffer), "%.2f °C", temperature);
    lv_label_set_text(ui_TempVal, buffer); 

    snprintf(buffer, sizeof(buffer), "%.2f hPa", pressure);
    lv_label_set_text(ui_PresVal, buffer); 

    snprintf(buffer, sizeof(buffer), "%.2f m/s", verticalSpeed);
    lv_label_set_text(ui_VSpeedVal, buffer);

    return ESP_OK; // Return success
}
// Function to update the UI for modem data
esp_err_t ui_update_mod_data(uint8_t *data)
{
    if (data == NULL) {
        ESP_LOGE(TAG, "Data pointer is NULL");
        return ESP_ERR_INVALID_ARG; // Return error if data pointer is NULL
    }

    // Assuming data contains the necessary information to update the UI
    uint8_t mode ;
    memcpy(&mode, data, sizeof(uint8_t));
    char mode_str[15];
    switch(mode) {
        case 0:
            snprintf(mode_str, sizeof(mode_str), "NORMAL");
            break;
        case 1:
            snprintf(mode_str, sizeof(mode_str), "CALIBRATION");
            break;
        case 2:
            snprintf(mode_str, sizeof(mode_str), "STABILIZATION");
            break;
        default:
            snprintf(mode_str, sizeof(mode_str), "MISSION");
            break;
    }
    lv_label_set_text(ui_LabelModeValue, mode_str);

    return ESP_OK; // Return success
}
// Function to update the UI for status data
esp_err_t ui_update_sta_data(uint8_t *data)
{
    if (data == NULL) {
        ESP_LOGE(TAG, "Data pointer is NULL");
        return ESP_ERR_INVALID_ARG; // Return error if data pointer is NULL
    }

    // Assuming data contains the necessary information to update the UI
    uint8_t status ;
    memcpy(&status, data, sizeof(uint8_t));
    char status_str[10];
   switch(status) {
        case 0:
            snprintf(status_str, sizeof(status_str), "ARMED");
            lv_obj_clear_state(ui_ButtonStatus, LV_STATE_USER_1 | LV_STATE_USER_2 | LV_STATE_USER_3 | LV_STATE_USER_4);
            lv_obj_add_state(ui_ButtonStatus, LV_STATE_USER_3);
            break;

        case 1:
            snprintf(status_str, sizeof(status_str), "DISARMED");
            lv_obj_clear_state(ui_ButtonStatus, LV_STATE_USER_1 | LV_STATE_USER_2 | LV_STATE_USER_3 | LV_STATE_USER_4);
            lv_obj_add_state(ui_ButtonStatus, LV_STATE_USER_4);
            break;

        case 2:
            snprintf(status_str, sizeof(status_str), "STANDBY");
            lv_obj_clear_state(ui_ButtonStatus, LV_STATE_USER_1 | LV_STATE_USER_2 | LV_STATE_USER_3 | LV_STATE_USER_4);
            lv_obj_add_state(ui_ButtonStatus, LV_STATE_USER_2);
            break;

        default:
            snprintf(status_str, sizeof(status_str), "FLYING");
            lv_obj_clear_state(ui_ButtonStatus, LV_STATE_USER_1 | LV_STATE_USER_2 | LV_STATE_USER_3 | LV_STATE_USER_4);
            lv_obj_add_state(ui_ButtonStatus, LV_STATE_USER_1);
            break;
    }

    lv_label_set_text(ui_LabelStatusValue, status_str);

    return ESP_OK; // Return success
}
// Function to update the UI for nbm data
esp_err_t ui_update_nbm_data(uint8_t *data)
{
    if (data == NULL) {
        ESP_LOGE(TAG, "Data pointer is NULL");
        return ESP_ERR_INVALID_ARG; // Return error if data pointer is NULL
    }

    // Assuming data contains the necessary information to update the UI
    uint8_t nbm ;
    memcpy(&nbm, data, sizeof(uint8_t));
    char buffer[5];
    snprintf(buffer, sizeof(buffer), "%u", (unsigned)nbm);
    lv_label_set_text(ui_LabelNBMValue, buffer);

    return ESP_OK; // Return success
}

