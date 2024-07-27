#include "userapp.h"

extern UART_HandleTypeDef huart2;

void userapp_init(void) {
    retarget_init(&huart2);
}

void userapp_loop(void) {
    HAL_StatusTypeDef status = HAL_OK;
    joystick_state_t state;

    status = joystick_init_periph();
    if (status != HAL_OK) {
        printf("Joystick init error: %d\n", status);
        return;
    }

    status = servo_init_periph();
    if (status != HAL_OK) {
        printf("Servo init error: %d\n", status);
        return;
    }

    //wait for ADC to stabilize
    HAL_Delay(100);

    printf("Entering endless loop\n");

    while(true){
        joystick_process(&state);

        // printf("X: %d, Y: %d\n", state.x, state.y);

        servo_set_angle(state.x, state.y);
    }
}