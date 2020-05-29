#ifndef SRC_SWITCHING_H_
#define SRC_SWITCHING_H_
#include "stm32f3xx_hal.h"

#define HALLOR_SWITCH 0
#define VECTOR_SWITCH 1

void BLDC_Hall_Convert_Mode1(uint8_t Hall_Value); //H-PWM;L-ON
void BLDC_Hall_Convert_Mode2(uint8_t Hall_Value); //H-PWM;L-PWM
void Voltage_Vector_Convert(uint8_t Hall_Value);

#endif
