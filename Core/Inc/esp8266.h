#ifndef INC_ESP8266_H_
#define INC_ESP8266_H_

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "stm32c0xx_hal.h"

#define ESP8266_CMD_AT                  "AT\r\n"
#define ESP8266_CMD_EXPECTED_AT         "AT\n\nOK\n"

#define ESP8266_CMD_CWMODE              "AT+CWMODE=1\r\n"

#define ESP8266_CMD_CIFSR               "AT+CIFSR\r\n"

#define ESP8266_CMD_CWJAP_FMT           "AT+CWJAP=\"%s\",\"%s\"\r\n"

#define EPS8266_CMD_CIPMUX              "AT+CIPMUX=1\r\n"

#define ESP8266_CMD_CIPSERVER           "AT+CIPSERVER=1\r\n"

#define ESP9266_IPD_HEADER              "+IPD"

void esp8266_init(UART_HandleTypeDef *huart);
HAL_StatusTypeDef esp8266_connect_wifi(char *ssid, char *password);

#endif /* INC_ESP8266_H_ */