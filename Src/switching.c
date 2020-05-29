/*
CODE BY BG5CPU
*/

#include "main.h"

extern TIM_HandleTypeDef htim1;

/*
H-PWM;L-ON
For the L6390D
HVGx-PWM\LVGx-OFF: HINx-PWM\LINx-H: PWM mode1, LINx DISABLE, HINx PWM output ENABLE
HVGx-OFF\LVGx-ON: HINx-L\LINx-L: forced active, LINx ENABLE, HINx DISABLE
HVGx-OFF\LVGx-OFF: HINx-L\LINx-H: forced inactive, LINx ENABLE, HINx DISABLE
*/
void BLDC_Hall_Convert_Mode1(uint8_t Hall_Value)
{
	uint32_t tmp = 0U;
	//	TIM1->BDTR |= 1<<11;  //OSSR=1	
	switch (Hall_Value)
	{
		case 1:  // Step1, A+ B- Cx , HVGA-PWM;LVGA-OFF; HVGB-OFF;LVGB-ON; HVGC-OFF;LVGC-OFF;
		{					// HINA-PWM;LINA-H; HINB-L;LINB-L; HINC-L;LINC-H;
			// HINA-PWM;LINA-H;
			// PWM mode1 OC1M bits
			TIM1->CCMR1 &= 0x8F; TIM1->CCMR1 |= 6<<4;
			// Set or reset the CCxE Bit   ****Channel_1
			// LINA DISABLE
			tmp = TIM_CCER_CC1E << TIM_CHANNEL_1;
			htim1.Instance->CCER &= ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCx_DISABLE << TIM_CHANNEL_1); 
			// Set or reset the CCxNE Bit   ****Channel_1N
			// HINA PWM output ENABLE
			tmp = TIM_CCER_CC1NE << TIM_CHANNEL_1;
			htim1.Instance->CCER &=  ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCxN_ENABLE << TIM_CHANNEL_1);	
			
			//Phase B: HINB-L;LINB-L;
			// forced active OC2M bits     // here ??????????????????
			TIM1->CCMR1 &= 0x8FFF; TIM1->CCMR1 |= 5<<12; //TIM1->CCMR1 |= 1<<14; TIM1->CCMR1 |= 1<<12; 
			// LINB  ENABLE
			tmp = TIM_CCER_CC1E << TIM_CHANNEL_2;
			htim1.Instance->CCER &= ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCx_ENABLE << TIM_CHANNEL_2);
			// HINB  DISABLE
			tmp = TIM_CCER_CC1NE << TIM_CHANNEL_2;
			htim1.Instance->CCER &=  ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCxN_DISABLE << TIM_CHANNEL_2);		

			//Phase C: HINC-L;LINC-H;
			// Forced inactive  OC3M bits
			TIM1->CCMR2 &= 0x8F; TIM1->CCMR2 |= 4<<4; //TIM1->CCMR2 |= 1<<6;
			// LINC  ENABLE
			tmp = TIM_CCER_CC1E << TIM_CHANNEL_3;
			htim1.Instance->CCER &= ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCx_ENABLE << TIM_CHANNEL_3);
			// HINC  DISABLE
			tmp = TIM_CCER_CC1NE << TIM_CHANNEL_3;
			htim1.Instance->CCER &=  ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCxN_DISABLE << TIM_CHANNEL_3);			
			
		} break;
	
		case 2:  // Step2, A+ Bx C- , HVGA-PWM;LVGA-OFF; HVGB-OFF;LVGB-OFF; HVGC-OFF;LVGC-ON;
		{					// HINA-PWM;LINA-H; HINB-L;LINB-H; HINC-L;LINC-L;
			// Phase A: HINA-PWM;LINA-H;
			// PWM mode1 OC1M bits
			TIM1->CCMR1 &= 0x8F; TIM1->CCMR1 |= 6<<4;
			// Set or reset the CCxE Bit   ****Channel_1
			// LINA DISABLE
			tmp = TIM_CCER_CC1E << TIM_CHANNEL_1;
			htim1.Instance->CCER &= ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCx_DISABLE << TIM_CHANNEL_1); 
			// Set or reset the CCxNE Bit   ****Channel_1N
			// HINA PWM output ENABLE
			tmp = TIM_CCER_CC1NE << TIM_CHANNEL_1;
			htim1.Instance->CCER &=  ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCxN_ENABLE << TIM_CHANNEL_1);
			
			//Phase B: HINB-L;LINB-H;
			// Forced inactive OC2M bits
			TIM1->CCMR1 &= 0x8FFF; TIM1->CCMR1 |= 4<<12;
			// LINB  ENABLE
			tmp = TIM_CCER_CC1E << TIM_CHANNEL_2;
			htim1.Instance->CCER &= ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCx_ENABLE << TIM_CHANNEL_2);
			// HINB  DISABLE
			tmp = TIM_CCER_CC1NE << TIM_CHANNEL_2;
			htim1.Instance->CCER &=  ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCxN_DISABLE << TIM_CHANNEL_2);	

			//Phase C: HINC-L;LINC-L;
			// Forced active  OC3M bits
			TIM1->CCMR2 &= 0x8F; TIM1->CCMR2 |= 5<<4;
			// LINC  ENABLE
			tmp = TIM_CCER_CC1E << TIM_CHANNEL_3;
			htim1.Instance->CCER &= ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCx_ENABLE << TIM_CHANNEL_3);
			// HINC  DISABLE
			tmp = TIM_CCER_CC1NE << TIM_CHANNEL_3;
			htim1.Instance->CCER &=  ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCxN_DISABLE << TIM_CHANNEL_3); 				

		} break;
		
		case 3:  // Step3, Ax B+ C- , HVGA-OFF;LVGA-OFF; HVGB-PWM;LVGB-OFF; HVGC-OFF;LVGC-ON;
		{					// HINA-L;LINA-H; HINB-PWM;LINB-H; HINC-L;LINC-L;
			// Phase A: HINA-L;LINA-H;
			// forced inactive OC1M bits
			TIM1->CCMR1 &= 0x8F; TIM1->CCMR1 |= 4<<4;
			// Set or reset the CCxE Bit   ****Channel_1
			// LINA ENABLE
			tmp = TIM_CCER_CC1E << TIM_CHANNEL_1;
			htim1.Instance->CCER &= ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCx_ENABLE << TIM_CHANNEL_1); 
			// Set or reset the CCxNE Bit   ****Channel_1N
			// HINA DISABLE
			tmp = TIM_CCER_CC1NE << TIM_CHANNEL_1;
			htim1.Instance->CCER &=  ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCxN_DISABLE << TIM_CHANNEL_1);
			
			//Phase B: HINB-PWM;LINB-H;
			//  PWM mode1 OC2M bits
			TIM1->CCMR1 &= 0x8FFF; TIM1->CCMR1 |= 6<<12;
			// LINB  DISABLE
			tmp = TIM_CCER_CC1E << TIM_CHANNEL_2;
			htim1.Instance->CCER &= ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCx_DISABLE << TIM_CHANNEL_2);
			// HINB  ENABLE
			tmp = TIM_CCER_CC1NE << TIM_CHANNEL_2;
			htim1.Instance->CCER &=  ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCxN_ENABLE << TIM_CHANNEL_2);	

			//Phase C: HINC-L;LINC-L;
			// Forced active  OC3M bits
			TIM1->CCMR2 &= 0x8F; TIM1->CCMR2 |= 5<<4;
			// LINC  ENABLE
			tmp = TIM_CCER_CC1E << TIM_CHANNEL_3;
			htim1.Instance->CCER &= ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCx_ENABLE << TIM_CHANNEL_3);
			// HINC  DISABLE
			tmp = TIM_CCER_CC1NE << TIM_CHANNEL_3;
			htim1.Instance->CCER &=  ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCxN_DISABLE << TIM_CHANNEL_3);

		} break;		
		
		case 4:  // Step4, A- B+ Cx , HVGA-OFF;LVGA-ON; HVGB-PWM;LVGB-OFF; HVGC-OFF;LVGC-OFF;
		{					// HINA-L;LINA-L; HINB-PWM;LINB-H; HINC-L;LINC-H;
			// Phase A: HINA-L;LINA-L;
			// forced active OC1M bits
			TIM1->CCMR1 &= 0x8F; TIM1->CCMR1 |= 5<<4;
			// Set or reset the CCxE Bit   ****Channel_1
			// LINA ENABLE
			tmp = TIM_CCER_CC1E << TIM_CHANNEL_1;
			htim1.Instance->CCER &= ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCx_ENABLE << TIM_CHANNEL_1); 
			// Set or reset the CCxNE Bit   ****Channel_1N
			// HINA DISABLE
			tmp = TIM_CCER_CC1NE << TIM_CHANNEL_1;
			htim1.Instance->CCER &=  ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCxN_DISABLE << TIM_CHANNEL_1);
			
			//Phase B: HINB-PWM;LINB-H;
			//  PWM mode1 OC2M bits
			TIM1->CCMR1 &= 0x8FFF; TIM1->CCMR1 |= 6<<12;
			// LINB  DISABLE
			tmp = TIM_CCER_CC1E << TIM_CHANNEL_2;
			htim1.Instance->CCER &= ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCx_DISABLE << TIM_CHANNEL_2);
			// HINB  ENABLE
			tmp = TIM_CCER_CC1NE << TIM_CHANNEL_2;
			htim1.Instance->CCER &=  ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCxN_ENABLE << TIM_CHANNEL_2);	

			//Phase C: HINC-L;LINC-H;
			// Forced inactive  OC3M bits
			TIM1->CCMR2 &= 0x8F; TIM1->CCMR2 |= 4<<4;
			// LINC  ENABLE
			tmp = TIM_CCER_CC1E << TIM_CHANNEL_3;
			htim1.Instance->CCER &= ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCx_ENABLE << TIM_CHANNEL_3);
			// HINC  DISABLE
			tmp = TIM_CCER_CC1NE << TIM_CHANNEL_3;
			htim1.Instance->CCER &=  ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCxN_DISABLE << TIM_CHANNEL_3);

		} break;
		
		case 5:  // Step5, A- Bx C+ , HVGA-OFF;LVGA-ON; HVGB-OFF;LVGB-OFF; HVGC-PWM;LVGC-OFF;
		{					// HINA-L;LINA-L; HINB-L;LINB-H; HINC-PWM;LINC-H;
			// Phase A: HINA-L;LINA-L;
			// forced active OC1M bits
			TIM1->CCMR1 &= 0x8F; TIM1->CCMR1 |= 5<<4;
			// Set or reset the CCxE Bit   ****Channel_1
			// LINA ENABLE
			tmp = TIM_CCER_CC1E << TIM_CHANNEL_1;
			htim1.Instance->CCER &= ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCx_ENABLE << TIM_CHANNEL_1); 
			// Set or reset the CCxNE Bit   ****Channel_1N
			// HINA DISABLE
			tmp = TIM_CCER_CC1NE << TIM_CHANNEL_1;
			htim1.Instance->CCER &=  ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCxN_DISABLE << TIM_CHANNEL_1);
			
			//Phase B: HINB-L;LINB-H;
			// forced inactive OC2M bits
			TIM1->CCMR1 &= 0x8FFF; TIM1->CCMR1 |= 4<<12;
			// LINB  ENABLE
			tmp = TIM_CCER_CC1E << TIM_CHANNEL_2;
			htim1.Instance->CCER &= ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCx_ENABLE << TIM_CHANNEL_2);
			// HINB  DISABLE
			tmp = TIM_CCER_CC1NE << TIM_CHANNEL_2;
			htim1.Instance->CCER &=  ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCxN_DISABLE << TIM_CHANNEL_2);	

			//Phase C: HINC-PWM;LINC-H;
			// PWM mode1 OC3M bits
			TIM1->CCMR2 &= 0x8F; TIM1->CCMR2 |= 6<<4;
			// LINC  DISABLE
			tmp = TIM_CCER_CC1E << TIM_CHANNEL_3;
			htim1.Instance->CCER &= ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCx_DISABLE << TIM_CHANNEL_3);
			// HINC  ENABLE
			tmp = TIM_CCER_CC1NE << TIM_CHANNEL_3;
			htim1.Instance->CCER &=  ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCxN_ENABLE << TIM_CHANNEL_3);				

		} break;
		
		case 6:  // Step6, Ax B- C+ , HVGA-OFF;LVGA-OFF; HVGB-OFF;LVGB-ON; HVGC-PWM;LVGC-OFF;
		{					// HINA-L;LINA-H; HINB-L;LINB-L; HINC-PWM;LINC-H;
			// Phase A: HINA-L;LINA-H;
			// forced inactive OC1M bits
			TIM1->CCMR1 &= 0x8F; TIM1->CCMR1 |= 4<<4;
			// Set or reset the CCxE Bit   ****Channel_1
			// LINA ENABLE
			tmp = TIM_CCER_CC1E << TIM_CHANNEL_1;
			htim1.Instance->CCER &= ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCx_ENABLE << TIM_CHANNEL_1); 
			// Set or reset the CCxNE Bit   ****Channel_1N
			// HINA DISABLE
			tmp = TIM_CCER_CC1NE << TIM_CHANNEL_1;
			htim1.Instance->CCER &=  ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCxN_DISABLE << TIM_CHANNEL_1);
			
			//Phase B: HINB-L;LINB-L;
			// forced active OC2M bits
			TIM1->CCMR1 &= 0x8FFF; TIM1->CCMR1 |= 5<<12;
			// LINB  ENABLE
			tmp = TIM_CCER_CC1E << TIM_CHANNEL_2;
			htim1.Instance->CCER &= ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCx_ENABLE << TIM_CHANNEL_2);
			// HINB  DISABLE
			tmp = TIM_CCER_CC1NE << TIM_CHANNEL_2;
			htim1.Instance->CCER &=  ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCxN_DISABLE << TIM_CHANNEL_2);	

			//Phase C: HINC-PWM;LINC-H;
			// PWM mode1 OC3M bits
			TIM1->CCMR2 &= 0x8F; TIM1->CCMR2 |= 6<<4;
			// LINC  DISABLE
			tmp = TIM_CCER_CC1E << TIM_CHANNEL_3;
			htim1.Instance->CCER &= ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCx_DISABLE << TIM_CHANNEL_3);
			// HINC  ENABLE
			tmp = TIM_CCER_CC1NE << TIM_CHANNEL_3;
			htim1.Instance->CCER &=  ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCxN_ENABLE << TIM_CHANNEL_3);

		} break;

		case 7:  // DEBUG MODE
		{
			// HINA-PWM;LINA-H;
			// PWM mode1 OC1M bits
			TIM1->CCMR1 &= 0x8F; TIM1->CCMR1 |= 6<<4;
			// Set or reset the CCxE Bit   ****Channel_1
			// LINA DISABLE
			tmp = TIM_CCER_CC1E << TIM_CHANNEL_1;
			htim1.Instance->CCER &= ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCx_DISABLE << TIM_CHANNEL_1); 
			// Set or reset the CCxNE Bit   ****Channel_1N
			// HINA PWM output ENABLE
			tmp = TIM_CCER_CC1NE << TIM_CHANNEL_1;
			htim1.Instance->CCER &=  ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCxN_ENABLE << TIM_CHANNEL_1);	
			
			// HINB-L;LINB-L;
			// Forced active OC2M bits
			TIM1->CCMR1 &= 0x8FFF; TIM1->CCMR1 |= 5<<12;
			// LINB  ENABLE
			tmp = TIM_CCER_CC1E << TIM_CHANNEL_2;
			htim1.Instance->CCER &= ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCx_ENABLE << TIM_CHANNEL_2);
			// HINB  DISABLE
			tmp = TIM_CCER_CC1NE << TIM_CHANNEL_2;
			htim1.Instance->CCER &=  ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCxN_DISABLE << TIM_CHANNEL_2);		

			// HINC-L;LINC-H;
			// Forced inactive  OC3M bits
			TIM1->CCMR2 &= 0x8F; TIM1->CCMR2 |= 4<<4;			
			// LINC  ENABLE
			tmp = TIM_CCER_CC1E << TIM_CHANNEL_3;
			htim1.Instance->CCER &= ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCx_ENABLE << TIM_CHANNEL_3);
			// HINC  DISABLE
			tmp = TIM_CCER_CC1NE << TIM_CHANNEL_3;
			htim1.Instance->CCER &=  ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCxN_DISABLE << TIM_CHANNEL_3);					
		
		} break; 
		default : {} break;	
	}
	
	TIM1->CCMR2 &= 0x8FFF; 
	TIM1->CCMR2 |= 1<<12;
}


/*
H-PWM;L-PWM
For the L6390D
HVGx-PWM\LVGx-OFF: HINx-PWM\LINx-H: PWM mode1, LINx DISABLE, HINx PWM output ENABLE
HVGx-OFF\LVGx-PWM: HINx-L\LINx-PWM: PWM mode1, LINx PWM output ENABLE, HINx DISABLE
HVGx-OFF\LVGx-OFF: HINx-L\LINx-H: forced inactive, LINx ENABLE, HINx DISABLE
case  1	vAB
			2	vAC
			3	vBC
			4	vBA
			5	vCA
			6	vCB	
*/
void BLDC_Hall_Convert_Mode2(uint8_t Hall_Value)
{
	uint32_t tmp = 0U;

//	TIM1->BDTR |= 1<<11;  //OSSR=1
//	TIM1->CCMR2 |= 1<<12;
	
	switch (Hall_Value)
	{
		case 1:  // Step1, A+ B- Cx , HVGA-PWM;LVGA-OFF; HVGB-OFF;LVGB-PWM; HVGC-OFF;LVGC-OFF;
		{					// HINA-PWM;LINA-H; HINB-L;LINB-PWM; HINC-L;LINC-H;
			// HINA-PWM;LINA-H;
			// PWM mode1 OC1M bits
			TIM1->CCMR1 &= 0x8F; TIM1->CCMR1 |= 6<<4;
			// Set or reset the CCxE Bit   ****Channel_1
			// LINA DISABLE
			tmp = TIM_CCER_CC1E << TIM_CHANNEL_1;
			htim1.Instance->CCER &= ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCx_DISABLE << TIM_CHANNEL_1); 
			// Set or reset the CCxNE Bit   ****Channel_1N
			// HINA PWM output ENABLE
			tmp = TIM_CCER_CC1NE << TIM_CHANNEL_1;
			htim1.Instance->CCER &=  ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCxN_ENABLE << TIM_CHANNEL_1);	
			
			//Phase B: HINB-L;LINB-PWM;
			// PWM mode1 OC1M bits     
			TIM1->CCMR1 &= 0x8FFF; TIM1->CCMR1 |= 6<<12;  
			// LINB  ENABLE
			tmp = TIM_CCER_CC1E << TIM_CHANNEL_2;
			htim1.Instance->CCER &= ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCx_ENABLE << TIM_CHANNEL_2);
			// HINB  DISABLE
			tmp = TIM_CCER_CC1NE << TIM_CHANNEL_2;
			htim1.Instance->CCER &=  ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCxN_DISABLE << TIM_CHANNEL_2);		

			//Phase C: HINC-L;LINC-H;
			// Forced inactive  OC3M bits
			TIM1->CCMR2 &= 0x8F; TIM1->CCMR2 |= 4<<4; //TIM1->CCMR2 |= 1<<6;
			// LINC  ENABLE
			tmp = TIM_CCER_CC1E << TIM_CHANNEL_3;
			htim1.Instance->CCER &= ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCx_ENABLE << TIM_CHANNEL_3);
			// HINC  DISABLE
			tmp = TIM_CCER_CC1NE << TIM_CHANNEL_3;
			htim1.Instance->CCER &=  ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCxN_DISABLE << TIM_CHANNEL_3);			
			
		} break;
	
		case 2:  // Step2, A+ Bx C- , HVGA-PWM;LVGA-OFF; HVGB-OFF;LVGB-OFF; HVGC-OFF;LVGC-PWM;
		{					// HINA-PWM;LINA-H; HINB-L;LINB-H; HINC-L;LINC-PWM;
			// Phase A: HINA-PWM;LINA-H;
			// PWM mode1 OC1M bits
			TIM1->CCMR1 &= 0x8F; TIM1->CCMR1 |= 6<<4;
			// Set or reset the CCxE Bit   ****Channel_1
			// LINA DISABLE
			tmp = TIM_CCER_CC1E << TIM_CHANNEL_1;
			htim1.Instance->CCER &= ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCx_DISABLE << TIM_CHANNEL_1); 
			// Set or reset the CCxNE Bit   ****Channel_1N
			// HINA PWM output ENABLE
			tmp = TIM_CCER_CC1NE << TIM_CHANNEL_1;
			htim1.Instance->CCER &=  ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCxN_ENABLE << TIM_CHANNEL_1);
			
			//Phase B: HINB-L;LINB-H;
			// Forced inactive OC2M bits
			TIM1->CCMR1 &= 0x8FFF; TIM1->CCMR1 |= 4<<12;
			// LINB  ENABLE
			tmp = TIM_CCER_CC1E << TIM_CHANNEL_2;
			htim1.Instance->CCER &= ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCx_ENABLE << TIM_CHANNEL_2);
			// HINB  DISABLE
			tmp = TIM_CCER_CC1NE << TIM_CHANNEL_2;
			htim1.Instance->CCER &=  ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCxN_DISABLE << TIM_CHANNEL_2);	

			//Phase C: HINC-L;LINC-L;
			// PWM mode1  OC3M bits
			TIM1->CCMR2 &= 0x8F; TIM1->CCMR2 |= 6<<4;
			// LINC  ENABLE
			tmp = TIM_CCER_CC1E << TIM_CHANNEL_3;
			htim1.Instance->CCER &= ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCx_ENABLE << TIM_CHANNEL_3);
			// HINC  DISABLE
			tmp = TIM_CCER_CC1NE << TIM_CHANNEL_3;
			htim1.Instance->CCER &=  ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCxN_DISABLE << TIM_CHANNEL_3); 				

		} break;
		
		case 3:  // Step3, Ax B+ C- , HVGA-OFF;LVGA-OFF; HVGB-PWM;LVGB-OFF; HVGC-OFF;LVGC-PWM;
		{					// HINA-L;LINA-H; HINB-PWM;LINB-H; HINC-L;LINC-PWM;
			// Phase A: HINA-L;LINA-H;
			// forced inactive OC1M bits
			TIM1->CCMR1 &= 0x8F; TIM1->CCMR1 |= 4<<4;
			// Set or reset the CCxE Bit   ****Channel_1
			// LINA ENABLE
			tmp = TIM_CCER_CC1E << TIM_CHANNEL_1;
			htim1.Instance->CCER &= ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCx_ENABLE << TIM_CHANNEL_1); 
			// Set or reset the CCxNE Bit   ****Channel_1N
			// HINA DISABLE
			tmp = TIM_CCER_CC1NE << TIM_CHANNEL_1;
			htim1.Instance->CCER &=  ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCxN_DISABLE << TIM_CHANNEL_1);
			
			//Phase B: HINB-PWM;LINB-H;
			//  PWM mode1 OC2M bits
			TIM1->CCMR1 &= 0x8FFF; TIM1->CCMR1 |= 6<<12;
			// LINB  DISABLE
			tmp = TIM_CCER_CC1E << TIM_CHANNEL_2;
			htim1.Instance->CCER &= ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCx_DISABLE << TIM_CHANNEL_2);
			// HINB  ENABLE
			tmp = TIM_CCER_CC1NE << TIM_CHANNEL_2;
			htim1.Instance->CCER &=  ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCxN_ENABLE << TIM_CHANNEL_2);	

			//Phase C: HINC-L;LINC-L;
			// PWM mode1  OC3M bits
			TIM1->CCMR2 &= 0x8F; TIM1->CCMR2 |= 6<<4;
			// LINC  ENABLE
			tmp = TIM_CCER_CC1E << TIM_CHANNEL_3;
			htim1.Instance->CCER &= ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCx_ENABLE << TIM_CHANNEL_3);
			// HINC  DISABLE
			tmp = TIM_CCER_CC1NE << TIM_CHANNEL_3;
			htim1.Instance->CCER &=  ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCxN_DISABLE << TIM_CHANNEL_3);

		} break;		
		
		case 4:  // Step4, A- B+ Cx , HVGA-OFF;LVGA-PWM; HVGB-PWM;LVGB-OFF; HVGC-OFF;LVGC-OFF;
		{					// HINA-L;LINA-PWM; HINB-PWM;LINB-H; HINC-L;LINC-H;
			// Phase A: HINA-L;LINA-L;
			// PWM mode1 OC1M bits
			TIM1->CCMR1 &= 0x8F; TIM1->CCMR1 |= 6<<4;
			// Set or reset the CCxE Bit   ****Channel_1
			// LINA ENABLE
			tmp = TIM_CCER_CC1E << TIM_CHANNEL_1;
			htim1.Instance->CCER &= ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCx_ENABLE << TIM_CHANNEL_1); 
			// Set or reset the CCxNE Bit   ****Channel_1N
			// HINA DISABLE
			tmp = TIM_CCER_CC1NE << TIM_CHANNEL_1;
			htim1.Instance->CCER &=  ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCxN_DISABLE << TIM_CHANNEL_1);
			
			//Phase B: HINB-PWM;LINB-H;
			//  PWM mode1 OC2M bits
			TIM1->CCMR1 &= 0x8FFF; TIM1->CCMR1 |= 6<<12;
			// LINB  DISABLE
			tmp = TIM_CCER_CC1E << TIM_CHANNEL_2;
			htim1.Instance->CCER &= ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCx_DISABLE << TIM_CHANNEL_2);
			// HINB  ENABLE
			tmp = TIM_CCER_CC1NE << TIM_CHANNEL_2;
			htim1.Instance->CCER &=  ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCxN_ENABLE << TIM_CHANNEL_2);	

			//Phase C: HINC-L;LINC-H;
			// Forced inactive  OC3M bits
			TIM1->CCMR2 &= 0x8F; TIM1->CCMR2 |= 4<<4;
			// LINC  ENABLE
			tmp = TIM_CCER_CC1E << TIM_CHANNEL_3;
			htim1.Instance->CCER &= ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCx_ENABLE << TIM_CHANNEL_3);
			// HINC  DISABLE
			tmp = TIM_CCER_CC1NE << TIM_CHANNEL_3;
			htim1.Instance->CCER &=  ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCxN_DISABLE << TIM_CHANNEL_3);

		} break;
		
		case 5:  // Step5, A- Bx C+ , HVGA-OFF;LVGA-PWM; HVGB-OFF;LVGB-OFF; HVGC-PWM;LVGC-OFF;
		{					// HINA-L;LINA-PWM; HINB-L;LINB-H; HINC-PWM;LINC-H;
			// Phase A: HINA-L;LINA-L;
			// PWM mode1 OC1M bits
			TIM1->CCMR1 &= 0x8F; TIM1->CCMR1 |= 6<<4;
			// Set or reset the CCxE Bit   ****Channel_1
			// LINA ENABLE
			tmp = TIM_CCER_CC1E << TIM_CHANNEL_1;
			htim1.Instance->CCER &= ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCx_ENABLE << TIM_CHANNEL_1); 
			// Set or reset the CCxNE Bit   ****Channel_1N
			// HINA DISABLE
			tmp = TIM_CCER_CC1NE << TIM_CHANNEL_1;
			htim1.Instance->CCER &=  ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCxN_DISABLE << TIM_CHANNEL_1);
			
			//Phase B: HINB-L;LINB-H;
			// forced inactive OC2M bits
			TIM1->CCMR1 &= 0x8FFF; TIM1->CCMR1 |= 4<<12;
			// LINB  ENABLE
			tmp = TIM_CCER_CC1E << TIM_CHANNEL_2;
			htim1.Instance->CCER &= ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCx_ENABLE << TIM_CHANNEL_2);
			// HINB  DISABLE
			tmp = TIM_CCER_CC1NE << TIM_CHANNEL_2;
			htim1.Instance->CCER &=  ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCxN_DISABLE << TIM_CHANNEL_2);	

			//Phase C: HINC-PWM;LINC-H;
			// PWM mode1 OC3M bits
			TIM1->CCMR2 &= 0x8F; TIM1->CCMR2 |= 6<<4;
			// LINC  DISABLE
			tmp = TIM_CCER_CC1E << TIM_CHANNEL_3;
			htim1.Instance->CCER &= ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCx_DISABLE << TIM_CHANNEL_3);
			// HINC  ENABLE
			tmp = TIM_CCER_CC1NE << TIM_CHANNEL_3;
			htim1.Instance->CCER &=  ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCxN_ENABLE << TIM_CHANNEL_3);				

		} break;
		
		case 6:  // Step6, Ax B- C+ , HVGA-OFF;LVGA-OFF; HVGB-OFF;LVGB-PWM; HVGC-PWM;LVGC-OFF;
		{					// HINA-L;LINA-H; HINB-L;LINB-PWM; HINC-PWM;LINC-H;
			// Phase A: HINA-L;LINA-H;
			// forced inactive OC1M bits
			TIM1->CCMR1 &= 0x8F; TIM1->CCMR1 |= 4<<4;
			// Set or reset the CCxE Bit   ****Channel_1
			// LINA ENABLE
			tmp = TIM_CCER_CC1E << TIM_CHANNEL_1;
			htim1.Instance->CCER &= ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCx_ENABLE << TIM_CHANNEL_1); 
			// Set or reset the CCxNE Bit   ****Channel_1N
			// HINA DISABLE
			tmp = TIM_CCER_CC1NE << TIM_CHANNEL_1;
			htim1.Instance->CCER &=  ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCxN_DISABLE << TIM_CHANNEL_1);
			
			//Phase B: HINB-L;LINB-PWM;
			// PWM mode1 OC2M bits     
			TIM1->CCMR1 &= 0x8FFF; TIM1->CCMR1 |= 6<<12;  
			// LINB  ENABLE
			tmp = TIM_CCER_CC1E << TIM_CHANNEL_2;
			htim1.Instance->CCER &= ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCx_ENABLE << TIM_CHANNEL_2);
			// HINB  DISABLE
			tmp = TIM_CCER_CC1NE << TIM_CHANNEL_2;
			htim1.Instance->CCER &=  ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCxN_DISABLE << TIM_CHANNEL_2);

			//Phase C: HINC-PWM;LINC-H;
			// PWM mode1 OC3M bits
			TIM1->CCMR2 &= 0x8F; TIM1->CCMR2 |= 6<<4;
			// LINC  DISABLE
			tmp = TIM_CCER_CC1E << TIM_CHANNEL_3;
			htim1.Instance->CCER &= ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCx_DISABLE << TIM_CHANNEL_3);
			// HINC  ENABLE
			tmp = TIM_CCER_CC1NE << TIM_CHANNEL_3;
			htim1.Instance->CCER &=  ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCxN_ENABLE << TIM_CHANNEL_3);

		} break;	
		default : {} break;	
	}
	TIM1->CCMR2 &= 0x8FFF;
	TIM1->CCMR2 |= 7<<12;
}


/*
voltage vector
V100 -> V110 -> V010 -> V011 -> V001 -> V101
For the L6390D
HVGx-PWM\LVGx-OFF: HINx-PWM\LINx-H: PWM mode1, LINx DISABLE, HINx PWM output ENABLE
HVGx-OFF\LVGx-PWM: HINx-L\LINx-PWM: PWM mode1, LINx PWM output ENABLE, HINx DISABLE
case  1	V100
			2	V110
			3	V010
			4	V011
			5	V001
			6	V101
*/
void Voltage_Vector_Convert(uint8_t Hall_Value)
{
	uint32_t tmp = 0U;
	
	switch (Hall_Value)
	{
		case 1:  // Step1, V100, A+ B- C- , HVGA-PWM;LVGA-OFF; HVGB-OFF;LVGB-PWM; HVGC-OFF;LVGC-PWM;
		{					// 
			// HINA-PWM;LINA-H;
			// Set or reset the CCxE Bit   ****Channel_1
			// LINA DISABLE
			tmp = TIM_CCER_CC1E << TIM_CHANNEL_1;
			htim1.Instance->CCER &= ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCx_DISABLE << TIM_CHANNEL_1); 
			// Set or reset the CCxNE Bit   ****Channel_1N
			// HINA PWM output ENABLE
			tmp = TIM_CCER_CC1NE << TIM_CHANNEL_1;
			htim1.Instance->CCER &=  ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCxN_ENABLE << TIM_CHANNEL_1);	
			
			//Phase B: HINB-L;LINB-PWM;
			// LINB  ENABLE
			tmp = TIM_CCER_CC1E << TIM_CHANNEL_2;
			htim1.Instance->CCER &= ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCx_ENABLE << TIM_CHANNEL_2);
			// HINB  DISABLE
			tmp = TIM_CCER_CC1NE << TIM_CHANNEL_2;
			htim1.Instance->CCER &=  ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCxN_DISABLE << TIM_CHANNEL_2);		

			//Phase C: HINC-L;LINC-PWM;
			// LINC  ENABLE
			tmp = TIM_CCER_CC1E << TIM_CHANNEL_3;
			htim1.Instance->CCER &= ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCx_ENABLE << TIM_CHANNEL_3);
			// HINC  DISABLE
			tmp = TIM_CCER_CC1NE << TIM_CHANNEL_3;
			htim1.Instance->CCER &=  ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCxN_DISABLE << TIM_CHANNEL_3);			
			
		} break;
	
		case 2:  // Step2, V110, A+ B+ C- , HVGA-PWM;LVGA-OFF; HVGB-PWM;LVGB-OFF; HVGC-OFF;LVGC-PWM;
		{					// 
			// Phase A: HINA-PWM;LINA-H;
			// Set or reset the CCxE Bit   ****Channel_1
			// LINA DISABLE
			tmp = TIM_CCER_CC1E << TIM_CHANNEL_1;
			htim1.Instance->CCER &= ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCx_DISABLE << TIM_CHANNEL_1); 
			// Set or reset the CCxNE Bit   ****Channel_1N
			// HINA PWM output ENABLE
			tmp = TIM_CCER_CC1NE << TIM_CHANNEL_1;
			htim1.Instance->CCER &=  ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCxN_ENABLE << TIM_CHANNEL_1);
			
			//Phase B: HINB-PWM;LINB-H;
			// LINB  DISABLE
			tmp = TIM_CCER_CC1E << TIM_CHANNEL_2;
			htim1.Instance->CCER &= ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCx_DISABLE << TIM_CHANNEL_2);
			// HINB  ENABLE
			tmp = TIM_CCER_CC1NE << TIM_CHANNEL_2;
			htim1.Instance->CCER &=  ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCxN_ENABLE << TIM_CHANNEL_2);	

			//Phase C: HINC-L;LINC-PWM;
			// LINC  ENABLE
			tmp = TIM_CCER_CC1E << TIM_CHANNEL_3;
			htim1.Instance->CCER &= ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCx_ENABLE << TIM_CHANNEL_3);
			// HINC  DISABLE
			tmp = TIM_CCER_CC1NE << TIM_CHANNEL_3;
			htim1.Instance->CCER &=  ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCxN_DISABLE << TIM_CHANNEL_3); 				

		} break;
		
		case 3:  // Step3, V010, A- B+ C- , HVGA-OFF;LVGA-PWM; HVGB-PWM;LVGB-OFF; HVGC-OFF;LVGC-PWM;
		{					// 
			// Phase A: HINA-L;LINA-PWM;
			// Set or reset the CCxE Bit   ****Channel_1
			// LINA ENABLE
			tmp = TIM_CCER_CC1E << TIM_CHANNEL_1;
			htim1.Instance->CCER &= ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCx_ENABLE << TIM_CHANNEL_1); 
			// Set or reset the CCxNE Bit   ****Channel_1N
			// HINA DISABLE
			tmp = TIM_CCER_CC1NE << TIM_CHANNEL_1;
			htim1.Instance->CCER &=  ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCxN_DISABLE << TIM_CHANNEL_1);
			
			//Phase B: HINB-PWM;LINB-H;
			// LINB  DISABLE
			tmp = TIM_CCER_CC1E << TIM_CHANNEL_2;
			htim1.Instance->CCER &= ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCx_DISABLE << TIM_CHANNEL_2);
			// HINB  ENABLE
			tmp = TIM_CCER_CC1NE << TIM_CHANNEL_2;
			htim1.Instance->CCER &=  ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCxN_ENABLE << TIM_CHANNEL_2);	

			//Phase C: HINC-L;LINC-L;
			// LINC  ENABLE
			tmp = TIM_CCER_CC1E << TIM_CHANNEL_3;
			htim1.Instance->CCER &= ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCx_ENABLE << TIM_CHANNEL_3);
			// HINC  DISABLE
			tmp = TIM_CCER_CC1NE << TIM_CHANNEL_3;
			htim1.Instance->CCER &=  ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCxN_DISABLE << TIM_CHANNEL_3);

		} break;		
		
		case 4:  // Step4, V011, A- B+ C+ , HVGA-OFF;LVGA-PWM; HVGB-PWM;LVGB-OFF; HVGC-PWM;LVGC-OFF;
		{					// 
			// Phase A: HINA-L;LINA-PWM;
			// Set or reset the CCxE Bit   ****Channel_1
			// LINA ENABLE
			tmp = TIM_CCER_CC1E << TIM_CHANNEL_1;
			htim1.Instance->CCER &= ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCx_ENABLE << TIM_CHANNEL_1); 
			// Set or reset the CCxNE Bit   ****Channel_1N
			// HINA DISABLE
			tmp = TIM_CCER_CC1NE << TIM_CHANNEL_1;
			htim1.Instance->CCER &=  ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCxN_DISABLE << TIM_CHANNEL_1);
			
			//Phase B: HINB-PWM;LINB-H;
			// LINB  DISABLE
			tmp = TIM_CCER_CC1E << TIM_CHANNEL_2;
			htim1.Instance->CCER &= ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCx_DISABLE << TIM_CHANNEL_2);
			// HINB  ENABLE
			tmp = TIM_CCER_CC1NE << TIM_CHANNEL_2;
			htim1.Instance->CCER &=  ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCxN_ENABLE << TIM_CHANNEL_2);	

			//Phase C: HINC-PWM;LINC-H;
			// LINC  DISABLE
			tmp = TIM_CCER_CC1E << TIM_CHANNEL_3;
			htim1.Instance->CCER &= ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCx_DISABLE << TIM_CHANNEL_3);
			// HINC  ENABLE
			tmp = TIM_CCER_CC1NE << TIM_CHANNEL_3;
			htim1.Instance->CCER &=  ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCxN_ENABLE << TIM_CHANNEL_3);

		} break;
		
		case 5:  // Step5, V001, A- B- C+ , HVGA-OFF;LVGA-PWM; HVGB-OFF;LVGB-PWM; HVGC-PWM;LVGC-OFF;
		{					// 
			// Phase A: HINA-L;LINA-PWM;
			// Set or reset the CCxE Bit   ****Channel_1
			// LINA ENABLE
			tmp = TIM_CCER_CC1E << TIM_CHANNEL_1;
			htim1.Instance->CCER &= ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCx_ENABLE << TIM_CHANNEL_1); 
			// Set or reset the CCxNE Bit   ****Channel_1N
			// HINA DISABLE
			tmp = TIM_CCER_CC1NE << TIM_CHANNEL_1;
			htim1.Instance->CCER &=  ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCxN_DISABLE << TIM_CHANNEL_1);
			
			//Phase B: HINB-L;LINB-PWM;
			// LINB  ENABLE
			tmp = TIM_CCER_CC1E << TIM_CHANNEL_2;
			htim1.Instance->CCER &= ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCx_ENABLE << TIM_CHANNEL_2);
			// HINB  DISABLE
			tmp = TIM_CCER_CC1NE << TIM_CHANNEL_2;
			htim1.Instance->CCER &=  ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCxN_DISABLE << TIM_CHANNEL_2);	

			//Phase C: HINC-PWM;LINC-H;
			// LINC  DISABLE
			tmp = TIM_CCER_CC1E << TIM_CHANNEL_3;
			htim1.Instance->CCER &= ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCx_DISABLE << TIM_CHANNEL_3);
			// HINC  ENABLE
			tmp = TIM_CCER_CC1NE << TIM_CHANNEL_3;
			htim1.Instance->CCER &=  ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCxN_ENABLE << TIM_CHANNEL_3);				

		} break;
		
		case 6:  // Step6, V101, A+ B- C+ , HVGA-PWM;LVGA-OFF; HVGB-OFF;LVGB-PWM; HVGC-PWM;LVGC-OFF;
		{					// 
			// Phase A: HINA-PWM;LINA-H;
			// Set or reset the CCxE Bit   ****Channel_1
			// LINA DISABLE
			tmp = TIM_CCER_CC1E << TIM_CHANNEL_1;
			htim1.Instance->CCER &= ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCx_DISABLE << TIM_CHANNEL_1); 
			// Set or reset the CCxNE Bit   ****Channel_1N
			// HINA ENABLE
			tmp = TIM_CCER_CC1NE << TIM_CHANNEL_1;
			htim1.Instance->CCER &=  ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCxN_ENABLE << TIM_CHANNEL_1);
			
			//Phase B: HINB-L;LINB-L;
			// LINB  ENABLE
			tmp = TIM_CCER_CC1E << TIM_CHANNEL_2;
			htim1.Instance->CCER &= ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCx_ENABLE << TIM_CHANNEL_2);
			// HINB  DISABLE
			tmp = TIM_CCER_CC1NE << TIM_CHANNEL_2;
			htim1.Instance->CCER &=  ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCxN_DISABLE << TIM_CHANNEL_2);	

			//Phase C: HINC-PWM;LINC-H;
			// LINC  DISABLE
			tmp = TIM_CCER_CC1E << TIM_CHANNEL_3;
			htim1.Instance->CCER &= ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCx_DISABLE << TIM_CHANNEL_3);
			// HINC  ENABLE
			tmp = TIM_CCER_CC1NE << TIM_CHANNEL_3;
			htim1.Instance->CCER &=  ~tmp;
			htim1.Instance->CCER |=  (uint32_t)(TIM_CCxN_ENABLE << TIM_CHANNEL_3);

		} break;	
		default : {} break;	
	}
	TIM1->CCMR1 &= 0x8F; TIM1->CCMR1 |= 6<<4;
	TIM1->CCMR1 &= 0x8FFF; TIM1->CCMR1 |= 6<<12; 
	TIM1->CCMR2 &= 0x8F; TIM1->CCMR2 |= 6<<4;
	TIM1->CCMR2 &= 0x8FFF; TIM1->CCMR2 |= 7<<12;	
}



