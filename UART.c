/* 
 * File:   UART.c
 * Author: Mario
 *
 */

#include "UART.h"


/******************************************************************************
 * @fn				- UART_setup
 * @brief			- This function initialize the UART Port as asynchronous 
 *                    mode and 8 bit transmition
 *
 * @param[in]		- ENABLE or DISABLE macros
 * @param[in]		- HIGH_SPEED or LOW_SPEED macros
 * @param[in]		- SPBRG value
 *
 * @return			- none
 *
 * @note			- none
 *****************************************************************************/
void UART_setup(uint8_t BRGH16_EnOrDis,uint8_t HighOrLow_Speed, uint16_t SPBRG_value)
{
    TX1STA = 0;
    TX1STAbits.TXEN = 1;                    //Transmit Enable bit
    TX1STAbits.BRGH = HighOrLow_Speed;      //High Baud Rate Select bit
    TX1STAbits.TRMT = 1;
    
    
    RC1STA = 0;
    RC1STAbits.SPEN = 1;                    //SPEN: Serial Port Enable bit
    RC1STAbits.CREN = 1;                    //CREN: Continuous Receive Enable bit 
    
    BAUDCON1bits.BRG16 = BRGH16_EnOrDis;
    
    SPBRGL = (uint8_t)SPBRG_value;
    SPBRGH = (SPBRG_value >> 8);
    
}




/******************************************************************************
 * @fn				- UART_InitPin_Tx
 * @brief			- This function initialize the Tx Pin
 *
 * @param[in]		- PORT_A, PORT_B OR PORT_C macros
 * @param[in]		- Pin Number
 *
 * @return			- none
 *
 * @note			- none
 *****************************************************************************/
void UART_InitPin_Tx(uint8_t PORT_x, uint8_t PinNumber)
{
    if (PORT_x == PORT_A)
    {
        ANSELA &= ~(1 << PinNumber);
        WPUA   &= ~(1 << PinNumber);
        TRISA  &= ~(1 << PinNumber);
        
        if (PinNumber == 0)
        {
            RA0PPS = 0x14;
        }
        else if (PinNumber == 1)
        {
            RA1PPS = 0x14;
        }
        else if (PinNumber == 2)
        {
            RA2PPS = 0x14;
        }
        else if (PinNumber == 4)
        {
            RA4PPS = 0x14;
        }
        else if (PinNumber == 5)
        {
            RA5PPS = 0x14;
        }
        
    }
    
    else if (PORT_x == PORT_B)
    {
        ANSELB &= ~(1 << PinNumber);
        WPUB   &= ~(1 << PinNumber);
        TRISB  &= ~(1 << PinNumber);
        
        if (PinNumber == 4)
        {
            RB4PPS = 0x14;
        }
        else if (PinNumber == 5)
        {
            RB5PPS = 0x14;
        }
        else if (PinNumber == 6)
        {
            RB6PPS = 0x14;
        }
        else if (PinNumber == 7)
        {
            RB7PPS = 0x14;
        }
        
    }
    else if (PORT_x == PORT_C)
    {
        ANSELC &= ~(1 << PinNumber);
        WPUC   &= ~(1 << PinNumber);
        TRISC  &= ~(1 << PinNumber);
        
        if (PinNumber == 0)
        {
            RC0PPS = 0x14;
        }
        else if (PinNumber == 1)
        {
            RC1PPS = 0x14;
        }
        else if (PinNumber == 2)
        {
            RC2PPS = 0x14;
        }
        else if (PinNumber == 3)
        {
            RC3PPS = 0x14;
        }
        else if (PinNumber == 4)
        {
            RC4PPS = 0x14;
        }
        else if (PinNumber == 5)
        {
            RC5PPS = 0x14;
        }
        else if (PinNumber == 6)
        {
            RC6PPS = 0x14;
        }
        else if (PinNumber == 7)
        {
            RC7PPS = 0x14;
        }
    }
    
}

/******************************************************************************
 * @fn				- UART_InitPin_Rx
 * @brief			- This function initialize the Rx Pin
 *
 * @param[in]		- PORT_A, PORT_B OR PORT_C macros
 * @param[in]		- Pin Number
 *
 * @return			- none
 *
 * @note			- none
 *****************************************************************************/

void UART_InitPin_Rx(uint8_t PORT_x, uint8_t PinNumber)
{
    if (PORT_x == PORT_A)
    {
        ANSELA &= ~(1 << PinNumber);
        WPUA   &= ~(1 << PinNumber);
        TRISA  |=  (1 << PinNumber);
        
        if (PinNumber == 0)
        {
            RXPPS = 0x00;
        }
        else if (PinNumber == 1)
        {
            RXPPS = 0x01;
        }
        else if (PinNumber == 2)
        {
            RXPPS = 0x02;
        }
        else if (PinNumber == 3)
        {
            RXPPS = 0x03;
        }
        else if (PinNumber == 4)
        {
            RXPPS = 0x04;
        }
        else if (PinNumber == 5)
        {
            RXPPS = 0x05;
        }
    }
    else if (PORT_x == PORT_B)
    {
        ANSELB &= ~(1 << PinNumber);
        WPUB   &= ~(1 << PinNumber);
        TRISB  |=  (1 << PinNumber);   
        
        if (PinNumber == 4)
        {
            RXPPS = 0b01100;
        }
        else if (PinNumber == 5)
        {
            RXPPS = 0b01101;
        }
        else if (PinNumber == 6)
        {
            RXPPS = 0b01110;
        }
        else if (PinNumber == 7)
        {
            RXPPS = 0b01111;
        }
        
        
    }
    
    else if (PORT_x == PORT_C)
    {
        ANSELC &= ~(1 << PinNumber);
        WPUC   &= ~(1 << PinNumber);
        TRISC  |=  (1 << PinNumber);
        
        if (PinNumber == 0)
        {
            RXPPS = 0b10000;
        }
        else if (PinNumber == 1)
        {
            RXPPS = 0b10001;
        }
        else if (PinNumber == 2)
        {
            RXPPS = 0b10010;
        }
        else if (PinNumber == 3)
        {
            RXPPS = 0b10011;
        }
        else if (PinNumber == 4)
        {
            RXPPS = 0b10100;
        }
        else if (PinNumber == 5)
        {
            RXPPS = 0b10101;
        }
        else if (PinNumber == 6)
        {
            RXPPS = 0b10110;
        }
        else if (PinNumber == 7)
        {
            RXPPS = 0b10111;
        }
    }
    
}

/******************************************************************************
 * @fn				- UART_WriteChar
 * @brief			- This function send a byte or one byte of data
 *
 * @param[in]		- character or data
 *
 * @return			- none
 *
 * @note			- none
 *****************************************************************************/

void UART_WriteChar(uint8_t data)
{
    while(!TX1STAbits.TRMT); //Transmit Shift Register Status bit 1:EMPTY
    TXREG = data;     
   
}

/******************************************************************************
 * @fn				- UART_WriteString
 * @brief			- This function send a string
 *
 * @param[in]		- pointer of one string
 *
 * @return			- none
 *
 * @note			- none
 *****************************************************************************/
void UART_WriteString(uint8_t *pText)
{
    for(uint8_t i=0 ; pText[i]!='\0' ; i++)
    {
        UART_WriteChar(pText[i]);
    }
    
}

/******************************************************************************
 * @fn				- UART_Read
 * @brief			- This function read the UART port
 *
 *
 * @return			- a byte or char
 *
 * @note			- none
 *****************************************************************************/

uint8_t UART_Read(void)
{
    while(!RCIF); // Wait Untill a Data Frame is Received
    return RCREG;
}


/******************************************************************************
 * @fn				- UART_EnableInterrupts
 * @brief			- This function enables the given interrupt type
 *
 * @param[in]		- Interrupt type : RX or TX
 *
 * @return			- none
 *
 * @note			- none
 *****************************************************************************/

void UART_EnableInterrupts(uint8_t RxOrTx)
{
    INTCONbits.GIE = 1;     
    INTCONbits.PEIE = 1;    
    
    if (RxOrTx == RX)
    {
        PIE1bits.RCIE = 1;
    }
    else if (RxOrTx == TX)
    {
        PIE1bits.TXIE = 1;
    }

}


