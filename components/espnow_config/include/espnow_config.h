#pragma once


#include "stdio.h"

#include "string.h"
#include "esp_log.h"

#include "esp_wifi.h"
#include "esp_netif.h"
#include "esp_event.h"
#include "nvs_flash.h"

#include "esp_now.h"
#include "esp_netif.h"
#include "esp_mac.h"

#define ESP_NOW_CHANNEL 1

esp_err_t init_wifi(void);
esp_err_t init_esp_now(void);
esp_err_t register_peer(uint8_t *peer_adr);

void receiveCallback(const esp_now_recv_info_t *esp_now_info, const uint8_t *data, int data_len);
void sendCallback(const uint8_t *mac_addr, esp_now_send_status_t status);
esp_err_t enowSender(const uint8_t *peer_addr, const uint8_t *data, size_t len);