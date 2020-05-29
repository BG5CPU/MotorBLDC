/*
CODE BY BG5CPU
*/

#include "main.h"
#include "control.h"
#include "switching.h"

uint8_t cntl_level = INITIAL_POSITION;
uint8_t init_pos = INITIAL_P_VECTOR;
uint8_t filer_count = 0;

extern uint16_t adc_buf[4];

/*
HallValue to current ADC step
hallvalue 1 -> 4
hallvalue 2 -> 5
hallvalue 3 -> 0
hallvalue 4 -> 1
hallvalue 5 -> 2
hallvalue 6 -> 3
*/
uint8_t HallV_To_ADCstep(uint8_t Hall_Value)
{
	uint8_t ADCstep;
	if(Hall_Value > 2){ADCstep = Hall_Value-3;}
	else {ADCstep = Hall_Value+3;}
	return ADCstep;
}


/*
Clockwise rotation
When CCPC bit is set, it allows to update CCxE, CCxNE and OCxM bits
Preload next step setting
HallValue +=1;
*/
extern uint8_t HallValue;
void Clockwise_rotation()
{
	TIM1->EGR |= 1<<5; 
//	HallValue = motor_state+1;	
	HallValue +=1;
	if(HallValue > 6)	{HallValue = 1;}
}


/*
Start up process
*/
uint8_t StartTime[8] = {100, 70, 50, 40, 35, 30, 25, 20};
void StartUp_begin()
{
	uint8_t i;
	Clockwise_rotation();
	for(i=0;i<8;i++)
	{
		Clockwise_rotation();
		HAL_Delay(StartTime[i]);
	}
	HAL_Delay(1);
	Clockwise_rotation();
}


//uint16_t blank_time = 0;
/*
Compare V_phase and V_mid
When A+B- mid>C switch
When A+C- mid<B switch
When B+C- mid>A switch
When B+A- mid<C switch
When C+A- mid>B switch
When C+B- mid<A switch
*/
void switch_phase(void)
{
	uint16_t PH_A_EMF,PH_B_EMF,PH_C_EMF,PH_MID;
	uint8_t motor_state;

//	motor_state = HallV_To_ADCstep(HallValue)+1;	
	motor_state = HallValue;
	
	PH_A_EMF = adc_buf[0];
	PH_B_EMF = adc_buf[1];
	PH_C_EMF = adc_buf[2];
	PH_MID = (PH_A_EMF+ PH_B_EMF+ PH_C_EMF)/3;
	
	switch (motor_state)
	{
	case 1: // A+B- mid>C switch
	{
		if(PH_MID > PH_C_EMF)
		{
			if(filer_count == FILTER_COUNT)
			{
				Clockwise_rotation();
				filer_count = 0;
			}else {filer_count += 1;}		
		}else {filer_count = 0;}
		break;
	}	
	case 2: //A+C- mid<B switch
	{
		if(PH_MID < PH_B_EMF)
		{
			if(filer_count == FILTER_COUNT)
			{
				Clockwise_rotation();
				filer_count = 0;
			}else {filer_count += 1;}
		}else {filer_count = 0;}
		break;
	}
	case 3: //B+C- mid>A switch
	{
		if(PH_MID > PH_A_EMF)
		{
			if(filer_count == FILTER_COUNT)
			{
				Clockwise_rotation();
				filer_count = 0;
			}else {filer_count += 1;}
		}else {filer_count = 0;}
		break;
	}
	case 4: //B+A- mid<C switch
	{
		if(PH_MID < PH_C_EMF)
		{
			if(filer_count == FILTER_COUNT)
			{
				Clockwise_rotation();
				filer_count = 0;
			}else {filer_count += 1;}
		}else {filer_count = 0;}
		break;
	}
	case 5: //C+A- mid>B switch
	{
		if(PH_MID > PH_B_EMF)
		{
			if(filer_count == FILTER_COUNT)
			{
				Clockwise_rotation();
				filer_count = 0;
			}else {filer_count += 1;}
		}else {filer_count = 0;}
		break;
	}
	case 6: //C+B- mid<A switch
	{
		if(PH_MID < PH_A_EMF)
		{
			if(filer_count == FILTER_COUNT)
			{
				Clockwise_rotation();
				filer_count = 0;
			}else {filer_count += 1;}
		}else {filer_count = 0;}
		break;
	}	
	default:
		{filer_count = 0;}
		break;
	}
	
}



/*
Control loop

*/
uint8_t Max_V_Step;
uint8_t Max_H_Step;	

void controltask()
{
	
	switch_phase();

	/*
	if(blank_time)
	{
		blank_time--;
		return;
	}
	*/
	
}


// void switch_phase(void);
/*
void switch_phase(void)
{
	switch(motor_state)
	{
		case 0:	//vAB,measure C
			if(PH_C_EMF>PH_MID) 
			{
				motor_state = 1;
				Clockwise_rotation();
				blank_time = 20;
			}
			break;
		case 1:	//vAC, measure B
			if(PH_B_EMF<PH_MID)
			{
				motor_state = 2;
				Clockwise_rotation();
				blank_time = 20;
			}
			break;
		case 2: //vBC, measure A
			if(PH_A_EMF>PH_MID)
			{
				motor_state = 3;
				Clockwise_rotation();
				blank_time = 20;
			}
			break;
		case 3:	//vBA, measure C
			if(PH_C_EMF<PH_MID)
			{
				motor_state = 4;
				Clockwise_rotation();
				blank_time = 20;
			}
			break;
		case 4:	//vCA, measure B
			if(PH_B_EMF>PH_MID)
			{
				motor_state = 5;
				Clockwise_rotation();
				blank_time = 20;
			}
			break;
		case 5:	//vCB, measure A
			if(PH_A_EMF>PH_MID)
			{
				motor_state = 0;
				Clockwise_rotation();
				blank_time = 20;
			}
			break;
		default:
			motor_state = 0;
			break;
	}
}

*/

//	HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET);	

/*
Meaningless Caculation
Motor: 1360KV
Give the voltage: 600/3600*7.2=1.2V
Desire mechanical speed: 1360*1.2=1632rpm
Number of pole-pairs: 5
Desire electric speed: 1632*5=8160rpm=48960dec/s
Every step needs the time: 60/48960=1.225ms
*/
