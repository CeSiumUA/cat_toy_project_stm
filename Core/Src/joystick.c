#include "joystick.h"

extern TIM_HandleTypeDef htim3;
extern ADC_HandleTypeDef hadc1;

static bool half_cplt = false;
static bool full_cplt = false;
static bool use_random_sequence = false;
static uint16_t adc_data[4] = {0};
uint32_t last_debounce_time = 0;
joystick_random_sequence random_sequence = WAIT_FOR_UP1;
joystick_direction last_dir = JOYSTICK_CENTER;
float target_x = 0;
float target_y = 0;
uint32_t random_gen_steps = 0;
float random_x = 0;
float random_y = 0;

static void joystick_generate_targets(void){
    target_x = (float)(rand() % (JOYSTICK_VALUE_MAX - JOYSTICK_VALUE_MIN + 1) + JOYSTICK_VALUE_MIN);
    target_y = (float)(rand() % (JOYSTICK_VALUE_MAX - JOYSTICK_VALUE_MIN + 1) + JOYSTICK_VALUE_MIN);
}

static float joystick_lerp(float a, float b, float t){
    return a + t * (b - a);
}

static void joystick_generate_random_states(joystick_state_t *state){
    // BTN is not working right now
    state->btn = false;

    if(random_gen_steps >= JOYSTICK_INTERPOLATION_STEPS){
        joystick_generate_targets();
        random_gen_steps = 0;
    }

    float multiplier = (float)random_gen_steps / (float)JOYSTICK_INTERPOLATION_STEPS;
    random_x = joystick_lerp(random_x, target_x, multiplier);
    random_y = joystick_lerp(random_y, target_y, multiplier);

    state->x = (uint16_t)random_x;
    state->y = (uint16_t)random_y;

    random_gen_steps++;
}

static void joystick_get_state(joystick_state_t *state) {
    uint8_t offs = 0;
    if(half_cplt){
        offs = 0;
    } else if(full_cplt){
        offs = 2;
    }
    
    state->x = adc_data[offs];
    state->y = adc_data[offs + 1];
    // BTN is not working right now
    state->btn = false;
}

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

    srand(HAL_GetTick() + __TIME__[7]);

    return status;
}

void joystick_process(joystick_state_t *state) {
    joystick_direction dir = JOYSTICK_CENTER;
    uint32_t current_tick = HAL_GetTick();

    joystick_get_state(state);

    if (state->x >= JOYSTICK_RIGHT_THRESHOLD_LOW && state->x <= JOYSTICK_RIGHT_THRESHOLD_HIGH) {
        dir = JOYSTICK_RIGHT;
    } else if (state->x >= JOYSTICK_LEFT_THRESHOLD_LOW && state->x <= JOYSTICK_LEFT_THRESHOLD_HIGH) {
        dir = JOYSTICK_LEFT;
    } else if (state->y >= JOYSTICK_UP_THRESHOLD_LOW && state->y <= JOYSTICK_UP_THRESHOLD_HIGH) {
        dir = JOYSTICK_UP;
    } else if (state->y >= JOYSTICK_DOWN_THRESHOLD_LOW && state->y <= JOYSTICK_DOWN_THRESHOLD_HIGH) {
        dir = JOYSTICK_DOWN;
    }

    if(use_random_sequence){
        joystick_generate_random_states(state);
    }

    if((current_tick - last_debounce_time) <= JOYSTICK_DEBOUNCE_TIME_MS){
        return;
    }

    if(dir == last_dir){
        return;
    }

    last_dir = dir;

    if((current_tick - last_debounce_time) >= JOYSTICK_SEQUENCE_EXPIRE_MS){
        random_sequence = WAIT_FOR_UP1;
    }

    switch(random_sequence){
        case WAIT_FOR_UP1:
            if(dir == JOYSTICK_UP){
                printf("up\n");
                random_sequence = WAIT_FOR_UP2;
                last_debounce_time = current_tick;
            } else{
                random_sequence = WAIT_FOR_UP1;
            }
            break;
        case WAIT_FOR_UP2:
            if(dir == JOYSTICK_UP){
                printf("up2\n");
                random_sequence = WAIT_FOR_DOWN1;
                last_debounce_time = current_tick;
            } else{
                random_sequence = WAIT_FOR_UP1;
            }
            break;
        case WAIT_FOR_DOWN1:
            if(dir == JOYSTICK_DOWN){
                printf("down\n");
                random_sequence = WAIT_FOR_DOWN2;
                last_debounce_time = current_tick;
            } else{
                random_sequence = WAIT_FOR_UP1;
            }
            break;
        case WAIT_FOR_DOWN2:
            if(dir == JOYSTICK_DOWN){
                printf("down2\n");
                random_sequence = SEQUENCE_DETECTED;
                last_debounce_time = current_tick;
            } else{
                random_sequence = WAIT_FOR_UP1;
            }
            break;
        case SEQUENCE_DETECTED:
            printf("sequence detected\n");
            break;
    }

    if(random_sequence == SEQUENCE_DETECTED){
        //TODO: remove print after debug
        printf("Sequence detected\n");
        use_random_sequence = !use_random_sequence;
        random_sequence = WAIT_FOR_UP1;
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