#ifndef INC_USERAPP_H_
#define INC_USERAPP_H_

#include "stm32c0xx_hal.h"
#include "retarget.h"
#include "main.h"

void userapp_init(void);
void userapp_loop(void);
void userapp_adc_half_cplt(void);
void userapp_adc_full_cplt(void);

#endif /* INC_USERAPP_H_ */