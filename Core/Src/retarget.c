#include "retarget.h"

static UART_HandleTypeDef *print_uart = NULL;

void retarget_init(UART_HandleTypeDef *huart)
{
    print_uart = huart;
}

int _write(int file, char *ptr, int len)
{
    if (print_uart == NULL) {
        return -1;
    }
    HAL_UART_Transmit(print_uart, (uint8_t *)ptr, len, 0xFFFF);
    return len;
}