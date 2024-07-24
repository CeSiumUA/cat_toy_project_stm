#include "esp8266.h"

UART_HandleTypeDef *esp_uart;

void esp8266_init(UART_HandleTypeDef *huart) {
    esp_uart = huart;
}

void esp8266_connect_wifi(char *ssid, char *password) {
    int n;
    char cmd[80];
    n = sprintf(cmd, ESP8266_CMD_CWJAP_FMT, ssid, password);
}
