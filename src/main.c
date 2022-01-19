/***************************************************/
/* Author  : fatma                                 */
/* Date    : 22 Sep 2021                          */
/* version : V01                                   */
/***************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_interface.h"
#include "DIO_interface.h"
#include "EXTI_interface.h"
#include "NVIC_interface.h"
#include "STK_interface.h"
#include "IR_interface.h"
#include "LEDMRX_interface.h"


u8 Data[40]={0, 0, 126, 18, 18, 2, 0, 0,                    //f
		    0, 124, 18, 18, 18, 124, 0, 0,                  //a
			0, 4, 126, 68, 0, 0, 0, 0,                      //t
			60, 2, 2, 60, 2, 2, 60, 0,                      //m
		    0, 124, 18, 18, 18, 124, 0, 0                   //a
};


void voidDetermineKey(u8 Copy_u8Key)
{
		switch(Copy_u8Key)
		{
		    case ON			:	HLEDMRX_voidResumeAnimating();              break;
		    case STOP	    :	HLEDMRX_voidPauseAnimating();	            break;
            case VOL_UP		:	HLEDMRX_voidSpeedUp();		                break;
			case VOL_DOWN   :	HLEDMRX_voidSpeedDown();	                break;
		}
}
void main (void)
{
	/* RCC Initialize */
	MRCC_voidInitSysClock();
	MRCC_voidEnableClock(APB2, IOPA); /* GPIOA Enable Clock */
	MRCC_voidEnableClock(APB2, IOPB); /* GPIOB Enable Clock */

	MGPIO_voidSetPinDirection(GPIOA,PIN0,INPUT_FLOATING); /* A0 Input Floating        */

	/* EXTI Initializtion */
	MEXTI_voidSetCallBack(HIR_voidGetFrame, LINE0);
	MEXTI_voidInit(); /* A0 EXTI0 Enabled / Falling Edge */

	/* Enable EXTI0 from NVIC */
	MNVIC_voidInit();
	MNVIC_voidEnableInterrupt(6); /* EXTI0 */

	/* SysTick Init */
	MSTK_voidInit();

	/*Init LedMatrix pins*/
	HLEDMRX_voidInit();


while(1)
{
	HIR_voidSetCallBack(voidDetermineKey);
	/*Start animating the name*/
       HLEDMRX_voidStartAnimating(Data);

}

}
