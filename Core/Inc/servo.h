#ifndef INC_SERVO_H_
#define INC_SERVO_H_

#include "stm32c0xx_hal.h"
#include "main.h"

HAL_StatusTypeDef  servo_init_periph(void);
void servo_set_angle(uint16_t angle_x, uint16_t angle_y);

#endif /* INC_SERVO_H_ */