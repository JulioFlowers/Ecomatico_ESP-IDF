
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

static const char *TAG = "Ecometro.";

static esp_err_t init_wifi(void);
static esp_err_t init_esp_now(void);
void receiveCallback(const esp_now_recv_info_t *esp_now_info, const uint8_t *data, int data_len);
void sendCallback(const uint8_t *mac_addr, esp_now_send_status_t status);

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

void app_main(void)
{
    init_wifi();
    init_esp_now();
}

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