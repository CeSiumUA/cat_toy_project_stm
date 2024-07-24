#ifndef INC_RETARGET_H_
#define INC_RETARGET_H_

#include <errno.h>
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "stm32c0xx_hal.h"

#define STDIN_FILENO           0
#define STDOUT_FILENO          1
#define STDERR_FILENO          2

void retarget_init(UART_HandleTypeDef *huart);

#endif /* INC_RETARGET_H_ */