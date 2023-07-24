
#include "stdio.h"

#include "string.h"
#include "esp_log.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_wifi.h"
#include "esp_netif.h"
#include "esp_event.h"
#include "nvs_flash.h"

#include "esp_now.h"
#include "esp_netif.h"
#include "esp_mac.h"

#define ESP_NOW_CHANNEL 1

static const char *TAG = "Ecometro.";
static uint8_t peer_mac[ESP_NOW_ETH_ALEN] = {0x58, 0xcf, 0xec, 0x62, 0x60, 0x83, 0x4b, 0xbc};

static esp_err_t init_wifi(void);
static esp_err_t init_esp_now(void);
static esp_err_t register_peer(uint8_t *peer_adr);

void receiveCallback(const esp_now_recv_info_t *esp_now_info, const uint8_t *data, int data_len);
void sendCallback(const uint8_t *mac_addr, esp_now_send_status_t status);
static esp_err_t enowSender(const uint8_t *peer_addr, const uint8_t *data, size_t len);

/*-----------------------------------------------------------*/
static esp_err_t init_wifi(void)
{
    wifi_init_config_t wifi_cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_wifi_init(&wifi_cfg));
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_set_storage(WIFI_STORAGE_FLASH));
    ESP_ERROR_CHECK(esp_wifi_start());
    ESP_LOGI(TAG, "WiFi inicializado.");
    return ESP_OK;
}
/*------------------------------1-----------------------------*/

/*-----------------------------------------------------------*/
static esp_err_t init_esp_now(void)
{
    ESP_ERROR_CHECK(esp_now_init());
    ESP_ERROR_CHECK(esp_now_register_recv_cb(receiveCallback));
    ESP_ERROR_CHECK(esp_now_register_send_cb(sendCallback));
    ESP_LOGI(TAG, "ESP-NOW Inicializado.");
    return ESP_OK;
}
/*-----------------------------------------------------------*/

/*-----------------------------------------------------------*/
void app_main(void)
{
    init_wifi();
    init_esp_now();
    ESP_ERROR_CHECK(register_peer(peer_mac));
}
/*-----------------------------------------------------------*/

/*-----------------------------------------------------------*/
void receiveCallback(const esp_now_recv_info_t *esp_now_info, const uint8_t *data, int data_len)
{

    ESP_LOGI(TAG, "Data received" MACSTR "%s", MAC2STR(esp_now_info->src_addr), data);
}
/*-----------------------------------------------------------*/

/*-----------------------------------------------------------*/
void sendCallback(const uint8_t *mac_addr, esp_now_send_status_t status)
{

    if (status == ESP_NOW_SEND_SUCCESS)
    {

        ESP_LOGI(TAG, "ESP_NOW_SEND_SUCCESS");
    }

    else
    {

        ESP_LOGI(TAG, "ESP_NOW_SEND_FAIL");
    }
}
/*-----------------------------------------------------------*/

/*-----------------------------------------------------------*/
static esp_err_t register_peer(uint8_t *peer_adr)
{
    esp_now_peer_info_t peer_info = {};
    memcpy(peer_info.peer_addr, peer_mac,ESP_NOW_ETH_ALEN);
    peer_info.channel = ESP_NOW_CHANNEL;
    peer_info.ifidx  = ESP_IF_WIFI_STA;
    ESP_ERROR_CHECK(esp_now_add_peer(&peer_info));
    return ESP_OK;
}

static esp_err_t enowSender(const uint8_t *peer_addr, const uint8_t *data, size_t len){
    esp_now_send(&peer_addr,&data,len);
    return ESP_OK;
}