#ifndef SRC_CONTROL_H_
#define SRC_CONTROL_H_
#include "stm32f3xx_hal.h"

#define INITIAL_POSITION 0  // find the initial position of rotor
#define SPEED_ACCELERATE 1  // speed up, accelerate the speed of rotor
#define SELF_SYNCHRONOUS 2  // 

#define INITIAL_P_VECTOR 0  // use the VECTOR switch method
#define INITIAL_P_HALLOR 1  // 
#define INITIAL_P_HNULLL 3  //

#define FILTER_COUNT 1

void StartUp_begin(void);
void controltask(void);

#endif

