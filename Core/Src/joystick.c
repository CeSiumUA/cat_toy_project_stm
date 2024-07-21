#include "joystick.h"

extern TIM_HandleTypeDef htim3;
extern ADC_HandleTypeDef hadc1;

static bool half_cplt = false;
static bool full_cplt = false;
static uint16_t adc_data[4] = {0};

HAL_StatusTypeDef joystick_init_periph(void){
    HAL_StatusTypeDef status = HAL_OK;

    status = HAL_TIM_Base_Start(&htim3);
    if (status != HAL_OK) {
        printf("TIM3 start error: %d\n", status);
        return status;
    }

    status = HAL_ADC_Start_DMA(&hadc1, (uint32_t *)adc_data, (sizeof(adc_data) / sizeof(adc_data[0])));
    if (status != HAL_OK) {
        printf("ADC start error: %d\n", status);
        return status;
    }

    return status;
}

void joystick_get_state(joystick_state_t *state) {
    if(half_cplt){
        state->x = adc_data[0];
        state->y = adc_data[1];
        // BTN is not working right now
        state->btn = false;
    } else if(full_cplt){
        state->x = adc_data[2];
        state->y = adc_data[3];
        // BTN is not working right now
        state->btn = false;
    }
}

void joystick_adc_half_cplt(void) {
    half_cplt = true;
    full_cplt = false;
}

void joystick_adc_full_cplt(void) {
    full_cplt = true;
    half_cplt = false;
}