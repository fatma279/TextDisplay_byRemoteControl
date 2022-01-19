/***************************************************/
/* Author  : fatma                                 */
/* Date    : 20 Sep 2021                         */
/* version : V03                                   */
/***************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "STK_interface.h"

#include "LEDMRX_interface.h"
#include "LEDMRX_private.h"
#include "LEDMRX_config.h"

#include "Delay.h"

volatile u8 Stop_Animating 	= 0;
volatile u8 Speed			= 50;
volatile u8 flag			= 0;


 void HLEDMRX_voidInit(void)
 {
		for(int iteration =0; iteration<8; iteration++)
		{
			/* Set Row direction */
			MGPIO_voidSetPinDirection(LEDMRX_ROW_PIN[iteration][0],LEDMRX_ROW_PIN[iteration][1], OUTPUT_SPEED_2MHZ_PP);
		     /* Set Column direction */
			MGPIO_voidSetPinDirection(LEDMRX_COL_PIN[iteration][0],LEDMRX_COL_PIN[iteration][1], OUTPUT_SPEED_2MHZ_PP);
		}
 }
	 

static void DisableAllCols(void)
{
	/* Disable all columns */
	for(u8 iteration=0; iteration<8; iteration++)
	{
		MGPIO_voidSetPinValue(LEDMRX_COL_PIN[iteration][0],LEDMRX_COL_PIN[iteration][1], HIGH);
	}
}


static void SetRowValue(u8 Copy_u8Value)
{
	u8 Local_u8BIT;

	for(int iteration=0; iteration<8; iteration++)
	{
		/* Get bit value in desire Row */
		Local_u8BIT = GET_BIT(Copy_u8Value,iteration);

		/*Set value in desire LEDMRX row */
		MGPIO_voidSetPinValue(LEDMRX_ROW_PIN[iteration][0],LEDMRX_ROW_PIN[iteration][1], Local_u8BIT);
	}

}



void HLEDMRX_voidStartAnimating(u8 *Copy_u8Data)
{
	/* 40 for the size of data array , flag to prevent it working until i push start(HLEDMRX_voidResumeAnimating)*/
			for (u8 i = 0; i < 40; i=i+flag)
			{
				while(Stop_Animating);

				//speed
				for(u8 j = 0; j < Speed; j++)
				{
					 /*  show the 8 column together*/
					for(u8 iteration =0; iteration < 8; iteration++){

					    /* Disable all columns */
						DisableAllCols();

						 /* (j+iteration) to show the next 8 column together in the array, starting from j*/
						SetRowValue(Copy_u8Data[iteration+i]);

						/* Enable the desire column */
						MGPIO_voidSetPinValue(LEDMRX_COL_PIN [iteration][0], LEDMRX_COL_PIN[iteration][1], LOW);

						delay_ms(2);
					}
				}
			}

	}


void HLEDMRX_voidPauseAnimating(void)
{
	Stop_Animating = 1;
	flag=0;
}

void HLEDMRX_voidResumeAnimating(void)
{
	Stop_Animating = 0;
	flag=1;
}

void HLEDMRX_voidSpeedDown(void)
{
	Speed += 10;
}

void HLEDMRX_voidSpeedUp(void)
{
	Speed -= 10;
}
