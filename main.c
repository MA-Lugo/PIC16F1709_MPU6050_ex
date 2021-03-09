/* 
 * File:   main.c
 * Author: Mario
 * Brief:  MPU6050 example, read Ax & Ay and 
 *         send through UART port every 20ms.
 */

#include <stdint.h>
#include "ConfigBits.h"
#include "TMR0.h"
#include "UART.h"
#include "MPU6050.h"


#define _XTAL_FREQ 32000000

#define TMR0REG_VALUE       131         //1ms @ 32MHz 

#define ENABLE      1
#define DISABLE     0

int Ax,Ay;

uint16_t counter = 0;
uint8_t transmission = DISABLE;

uint8_t StartFrame = '$';
uint8_t EndFrame[]   = "\r\n";   


void DATA_ACQ (void);
void DATA_Transmission(void);

int main() 
{
  
    OSCCONbits.IRCF = 0b1110;   //8MHZ internal clock
    OSCCONbits.SPLLEN = 1;      //PLL Enable for 32MHz
    
    UART_setup(BRGH16_DISABLE,HIGH_SPEED,103);       //@ 19200 baud
    UART_InitPin_Tx(PORT_B,4);
      
    TMR0_setup(TMR0_CLK_FOSCDIV4, TMR0_EDGE_FALL,TMR0_PRESC_64);
    TMR0_EnableInterrupts();
    TMR0_INT_Handle(TMR0REG_VALUE);
    
    MPU6050_Init();
    
    while(1)
    {
        if(transmission == ENABLE)
        {
            MPU6050_Read();
            DATA_Transmission();
            transmission = DISABLE;
        }
    }
}


void __interrupt() my_interrupt(void)
{
    if (INTCONbits.TMR0IF)                  //TMR0 Interrupt Flag bit 
    {               
        TMR0_INT_Handle(TMR0REG_VALUE);
        counter++;
        if (counter == 20)
        {
            transmission = ENABLE;
            counter = 0;
        }
        
    } 
}



void DATA_Transmission(void)
{
 
    UART_WriteChar(StartFrame);
    UART_WriteChar((uint8_t)(Ax));
    UART_WriteChar((uint8_t)(Ax >> 8));
    UART_WriteChar((uint8_t)(Ay));
    UART_WriteChar((uint8_t)(Ay >> 8));
	
	UART_WriteChar(0x00);//Dummy value to complete 9 bytes in the frame
	UART_WriteChar(0x00);//Dummy value to complete 9 bytes in the frame
    UART_WriteString(&EndFrame);
}