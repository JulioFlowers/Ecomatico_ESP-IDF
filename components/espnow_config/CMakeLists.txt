idf_component_register(SRCS "espnow_config.c"
                  INCLUDE_DIRS "include"
                  REQUIRES esp_wifi
                           esp_netif
                           esp_event
                           nvs_flash
                           esp_netif)

