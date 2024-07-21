#include "userapp.h"

extern UART_HandleTypeDef huart2;
extern TIM_HandleTypeDef htim1;

void userapp_init(void) {
    retarget_init(&huart2);
}

void userapp_loop(void) {
    HAL_StatusTypeDef status = HAL_OK;

    status = joystick_init_periph();
    if (status != HAL_OK) {
        printf("Joystick init error: %d\n", status);
        return;
    }

    while(true){
        
    }
}