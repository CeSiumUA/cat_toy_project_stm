#include "retarget.h"

static UART_HandleTypeDef *print_uart = NULL;

void retarget_init(UART_HandleTypeDef *huart) {
    print_uart = huart;
    setvbuf(stdout, NULL, _IONBF, 0);
}

int _write(int file, char *ptr, int len) {
    HAL_StatusTypeDef status = HAL_OK;
    if (print_uart == NULL) {
        return -1;
    }

    if (file == STDOUT_FILENO || file == STDERR_FILENO) {
        status = HAL_UART_Transmit(print_uart, (uint8_t *)ptr, len, HAL_MAX_DELAY);
        if (status != HAL_OK) {
            return EIO;
        }
    } else{
        errno = EBADF;
        return -1;
    }

    return len;
}

int _read(int file, char *ptr, int len){
    HAL_StatusTypeDef status = HAL_OK;

    if(file == STDIN_FILENO){
        status = HAL_UART_Receive(print_uart, (uint8_t *)ptr, 1, HAL_MAX_DELAY);
        if (status != HAL_OK) {
            return EIO;
        }
        return 1;
    } else {
        errno = EBADF;
        return -1;
    }
}