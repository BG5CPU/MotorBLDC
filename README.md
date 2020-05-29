Keywords: Brushless DC motor; Sensorless; Zero-Crossing Back EMF

Hardware: STM32F303RETx(MCU); L6390D(Gate Driver)

STM32 --> Interfacing with Hall sensors, please see ...\Src\switching.c
Compare V_phase and V_mid to decide how to switch phase, please see ...\Src\control.c
STM32 --> TIM1_CHANNEL_4 --> ADC synchronization(DMA) --> ADC after the current is stable

Thanks the help from BG2CSF


