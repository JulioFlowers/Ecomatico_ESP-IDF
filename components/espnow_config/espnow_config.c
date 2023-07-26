#include "espnow_config.h"

static const char *TAGespnow = "ESP_NOW Service";
/*-----------------------------------------------------------*/
esp_err_t init_wifi(void)
{
    wifi_init_config_t wifi_cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_wifi_init(&wifi_cfg));
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_set_storage(WIFI_STORAGE_FLASH));
    ESP_ERROR_CHECK(esp_wifi_start());
    ESP_LOGI(TAGespnow, "WiFi inicializado.");
    return ESP_OK;
}
/*------------------------------1-----------------------------*/

/*-----------------------------------------------------------*/
 esp_err_t init_esp_now(void)
{
    ESP_ERROR_CHECK(esp_now_init());
    ESP_ERROR_CHECK(esp_now_register_recv_cb(receiveCallback));
    ESP_ERROR_CHECK(esp_now_register_send_cb(sendCallback));
    ESP_LOGI(TAGespnow, "ESP-NOW Inicializado.");
    return ESP_OK;
}
/*-----------------------------------------------------------*/


/*-----------------------------------------------------------*/
void receiveCallback(const esp_now_recv_info_t *esp_now_info, const uint8_t *data, int data_len)
{

    ESP_LOGI(TAGespnow, "Data received" MACSTR "%s", MAC2STR(esp_now_info->src_addr), data);
}
/*-----------------------------------------------------------*/

/*-----------------------------------------------------------*/
void sendCallback(const uint8_t *mac_addr, esp_now_send_status_t status)
{

    if (status == ESP_NOW_SEND_SUCCESS)
    {

        ESP_LOGI(TAGespnow, "ESP_NOW_SEND_SUCCESS");
    }

    else
    {

        ESP_LOGI(TAGespnow, "ESP_NOW_SEND_FAIL");
    }
}
/*-----------------------------------------------------------*/

/*-----------------------------------------------------------*/
esp_err_t register_peer(uint8_t *peer_adr)
{
    esp_now_peer_info_t peer_info = {};
    memcpy(peer_info.peer_addr, &peer_adr,ESP_NOW_ETH_ALEN);
    peer_info.channel = ESP_NOW_CHANNEL;
    peer_info.ifidx  = ESP_IF_WIFI_STA;
    ESP_ERROR_CHECK(esp_now_add_peer(&peer_info));
    return ESP_OK;
}

 esp_err_t enowSender(const uint8_t *peer_addr, const uint8_t *data, size_t len){
    esp_now_send(&peer_addr,&data,len);
    return ESP_OK;
}