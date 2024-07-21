#ifndef INC_JOYSTICK_H_
#define INC_JOYSTICK_H_

#include "stm32c0xx_hal.h"
#include "main.h"
#include <stdint.h>

typedef struct {
    uint16_t x;
    uint16_t y;
    bool btn;
} joystick_state_t;

HAL_StatusTypeDef joystick_init_periph(void);
void joystick_adc_half_cplt(void);
void joystick_adc_full_cplt(void);
void joystick_get_state(joystick_state_t *state);

#endif /* INC_JOYSTICK_H_ */