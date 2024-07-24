#include "esp8266.h"

static UART_HandleTypeDef *esp_uart;

void esp8266_init(UART_HandleTypeDef *huart) {
    esp_uart = huart;
}

HAL_StatusTypeDef esp8266_connect_wifi(char *ssid, char *password) {
    char buf[80] = {0};
    HAL_StatusTypeDef status;

    status = HAL_UART_Transmit(esp_uart, (uint8_t *)ESP8266_CMD_AT, sizeof(ESP8266_CMD_AT) - 1, 1000);
    if (status != HAL_OK) {
        return status;
    }

    status = HAL_UART_Receive(esp_uart, (uint8_t *)buf, sizeof(ESP8266_CMD_EXPECTED_AT) - 1, 4000);
    if (status != HAL_OK) {
        return status;
    }

    while(strncmp(buf, ESP8266_CMD_EXPECTED_AT, sizeof(ESP8266_CMD_EXPECTED_AT)) != 0) {
        HAL_Delay(100);
    }

    return status;
}
