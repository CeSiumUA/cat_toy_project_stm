#ifndef INC_USERAPP_H_
#define INC_USERAPP_H_

#include "stm32c0xx_hal.h"
#include "retarget.h"
#include "main.h"
#include "joystick.h"
#include "servo.h"
#include "esp8266.h"
#include "secrets.h"

void userapp_init(void);
void userapp_loop(void);

#endif /* INC_USERAPP_H_ */