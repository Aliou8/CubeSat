#ifndef __TCP_SERVER_H__
#define __TCP_SERVER_H__

#include <string.h>
#include <sys/param.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "esp_netif.h"


#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include <lwip/netdb.h>

#include "process.h"

#define PORT                        CONFIG_EXAMPLE_PORT
#define KEEPALIVE_IDLE              CONFIG_EXAMPLE_KEEPALIVE_IDLE
#define KEEPALIVE_INTERVAL          CONFIG_EXAMPLE_KEEPALIVE_INTERVAL
#define KEEPALIVE_COUNT             CONFIG_EXAMPLE_KEEPALIVE_COUNT

static const char *TAG_TCP = "tcp_server"; 

typedef struct {
    uint8_t data[128];   // les données du message (payload GPS, texte, etc.)
    uint8_t length;      // longueur réelle des données
    uint8_t type;     // numéro de séquence du message
} ui_message_t;

extern QueueHandle_t ui_queue; // la file d'attente des messages pour le UI
/**
 * @brief TCP server task to  transmit data to connected clients
 * @param sock: socket descriptor
 * @return None
 */
void do_retransmit(const int sock) ;

/**
 * @brief Function to start the TCP server task
 * @param pvParameters: Pointer to the parameters passed to the task (address family)
 * @return None
 */
void tcp_server_task(void *pvParameters);

/**
 * @brief Function to handle incoming TCP client data and update the UI
 * @param data: Pointer to the received data
 * @return ESP_OK on success, error code otherwise
 */
void handle_tcp_client_data(const int sock);

#endif // __TCP_SERVER_H__