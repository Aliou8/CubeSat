#include "waveshare_rgb_lcd_port.h"
#include "protocol_examples_common.h"
#include "ui.h"
#include "tcp_server.h"
#include "freertos/queue.h"


// Queue globale pour passer les messages du TCP -> UI
QueueHandle_t ui_queue = NULL ;

// UI Task
void ui_task(void *pvParameters);

void app_main(void)
{
    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    // Initialize the LCD display
    waveshare_esp32_s3_rgb_lcd_init(); // Initialize the Waveshare ESP32-S3 RGB LCD 
    wavesahre_rgb_lcd_bl_off(); //Turn off the screen backlight
    vTaskDelay(pdMS_TO_TICKS(100)); //Delay for 100ms
    wavesahre_rgb_lcd_bl_on();  //Turn on the screen backlight  
    if (lvgl_port_lock(-1)) {
        ui_init();
        lvgl_port_unlock();
    }

    /* This helper function configures Wi-Fi or Ethernet, as selected in menuconfig.
     * Read "Establishing Wi-Fi or Ethernet Connection" section in
     * examples/protocols/README.md for more information about this function.
     */
    ESP_ERROR_CHECK(example_connect());
    // Create the queue to handle messages
    ui_queue = xQueueCreate(10, sizeof(ui_message_t));
    if (ui_queue == NULL) {
        ESP_LOGE(TAG, "Failed to create UI queue");
        abort();
    }
    // Create the UI task
    xTaskCreate(ui_task, "ui_task", 4096, NULL, 5, NULL);

#ifdef CONFIG_EXAMPLE_IPV4
    xTaskCreate(tcp_server_task, "tcp_server", 4096, (void*)AF_INET, 5, NULL);
#endif
#ifdef CONFIG_EXAMPLE_IPV6
    xTaskCreate(tcp_server_task, "tcp_server", 4096, (void*)AF_INET6, 5, NULL);
#endif
}


// UI Task implementation
void ui_task(void *pvParameters)
{
    ui_message_t msg;
    while (1) {
        // Wait for a message from the TCP server task
        if (xQueueReceive(ui_queue, &msg, portMAX_DELAY) == pdPASS) {
            // Lock the LVGL mutex
                // Update the UI with the received message
                update_ui(msg.data, msg.type); // Assuming the first byte indicates the message type
                // Unlock the LVGL mutex
            vTaskDelay(pdMS_TO_TICKS(5));
        }
    }
}