#include"main.h"
#include "../libTT/delay.h"
#include "../libTT/PWM.h"
#include "port.h"


//ck (us)

void Tang_Giam_Duty(int (*duty2)) //P2_5 =0 duty +10% P2_6=0 duty giam 10%
	{
			if(P1_4 == 0)
			{
					(*duty2)+=10;
					while(P1_4 == 0);
			}
		if(P1_3 == 0)
			{
				  (*duty2)-=10;
				  while(P1_3 == 0);
			}

	}
void main()
{
	unsigned int duty = 0;
    int *p =  &duty;
    //	uartMode1();
	PWM_Init (1000); //T = 1000us = 1ms
	PWM_Set_Duty(0);
	PWM_Start();
	duty = 50;
	while(1)
	{
			Tang_Giam_Duty(p);//Bam nut thi %duty +- 10%
			PWM_Set_Duty(duty);//set muc duty
	}
}