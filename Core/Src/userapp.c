#include "userapp.h"

extern UART_HandleTypeDef huart2;
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim3;
extern ADC_HandleTypeDef hadc1;

static uint16_t adc_data[4] = {0};

void userapp_init(void) {
    retarget_init(&huart2);
}

void userapp_loop(void) {
    HAL_StatusTypeDef status = HAL_OK;

    status = HAL_TIM_Base_Start(&htim3);
    if (status != HAL_OK) {
        printf("TIM3 start error: %d\n", status);
        return;
    }

    status = HAL_ADC_Start_DMA(&hadc1, (uint32_t *)adc_data, (sizeof(adc_data) / sizeof(adc_data[0])));
    if (status != HAL_OK) {
        printf("ADC start error: %d\n", status);
        return;
    }

    while(true){
        printf("ADC data: %d %d %d %d\n", adc_data[0], adc_data[1], adc_data[2], adc_data[3]);
        HAL_Delay(5000);
    }
}

void userapp_adc_half_cplt(void) {
    // printf("ADC half complete\n");
}

void userapp_adc_full_cplt(void) {
    // printf("ADC full complete\n");
}