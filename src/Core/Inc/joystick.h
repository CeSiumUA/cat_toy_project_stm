#ifndef INC_JOYSTICK_H_
#define INC_JOYSTICK_H_

#include "stm32c0xx_hal.h"
#include "main.h"
#include <stdint.h>
#include <stdlib.h>

#define JOYSTICK_VALUE_MAX                                      4095
#define JOYSTICK_VALUE_MIN                                      0

#define JOYSTICK_UP_THRESHOLD_HIGH                              JOYSTICK_VALUE_MAX
#define JOYSTICK_UP_THRESHOLD_LOW                               4000

#define JOYSTICK_DOWN_THRESHOLD_HIGH                            200
#define JOYSTICK_DOWN_THRESHOLD_LOW                             JOYSTICK_VALUE_MIN

#define JOYSTICK_RIGHT_THRESHOLD_HIGH                           JOYSTICK_VALUE_MAX
#define JOYSTICK_RIGHT_THRESHOLD_LOW                            4000

#define JOYSTICK_LEFT_THRESHOLD_HIGH                            200
#define JOYSTICK_LEFT_THRESHOLD_LOW                             JOYSTICK_VALUE_MIN

#define JOYSTICK_DEBOUNCE_TIME_MS                               50
#define JOYSTICK_SEQUENCE_EXPIRE_MS                             3000

#define JOYSTICK_INTERPOLATION_STEPS                            200

typedef struct {
    uint16_t x;
    uint16_t y;
    bool btn;
} joystick_state_t;

typedef enum {
    JOYSTICK_UP,
    JOYSTICK_DOWN,
    JOYSTICK_LEFT,
    JOYSTICK_RIGHT,
    JOYSTICK_CENTER
} joystick_direction;

typedef enum {
    WAIT_FOR_UP1,
    WAIT_FOR_UP2,
    WAIT_FOR_DOWN1,
    WAIT_FOR_DOWN2,
    SEQUENCE_DETECTED
} joystick_random_sequence;

HAL_StatusTypeDef joystick_init_periph(void);
void joystick_adc_half_cplt(void);
void joystick_adc_full_cplt(void);
void joystick_process(joystick_state_t *state);

#endif /* INC_JOYSTICK_H_ */