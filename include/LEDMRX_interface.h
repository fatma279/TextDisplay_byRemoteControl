/***************************************************/
/* Author  : fatma                                 */
/* Date    : 20 Sep 2021                          */
/* version : V03                                  */
/***************************************************/

 #ifndef LEDMRX_interface_H
 #define LEDMRX_interface_H
 
 
 
void HLEDMRX_voidInit(void);
void HLEDMRX_voidStartAnimating(u8 *Copy_u8Data);
void HLEDMRX_voidPauseAnimating(void);
void HLEDMRX_voidResumeAnimating(void);
void HLEDMRX_voidSpeedDown(void);
void HLEDMRX_voidSpeedUp(void);
 
 
 #endif
