#include "servo.h"

extern TIM_HandleTypeDef htim1;

HAL_StatusTypeDef  servo_init_periph(void){
    HAL_StatusTypeDef status = HAL_OK;

    status = HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
    if (status != HAL_OK) {
        printf("TIM1 start error: %d\n", status);
        return status;
    }

    status = HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
    if (status != HAL_OK) {
        printf("TIM1 start error: %d\n", status);
        return status;
    }

    return status;
}

void servo_set_angle(uint16_t angle_x, uint16_t angle_y){

    float pulse_x = (1000.0f) + (((float)angle_x / 4095.0f) * 1000.0f);
    float pulse_y = (1000.0f) + (((float)angle_y / 4095.0f) * 1000.0f);

    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, (uint16_t)pulse_x);
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, (uint16_t)pulse_y);
}