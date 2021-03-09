
#include <xc.h>
#include "I2C.h"


//---------------[ I2C Routines ]-------------------
//--------------------------------------------------

void I2C_Master_Init()
{
    SSP1CON1bits.SSPEN = 1; //Synchronous Serial Port Enable bit
    //Synchronous Serial Port Mode Select bits
    SSP1CON1bits.SSPM3 = 1; //I2C Master mode, clock = FOSC / (4 * (SSPxADD+1))
    SSP1CON1bits.SSPM2 = 0;
    SSP1CON1bits.SSPM1 = 0;
    SSP1CON1bits.SSPM0 = 0;
    SSP1CON2 = 0x00;
    SSP1STAT = 0x00;
    SSP1ADD = 0x4F; //100 kHz @32MHz
    SCL_D = 1;
    SDA_D = 1; 
    ANSELBbits.ANSB5 = 0;
    
    
    SSPCLKPPS = 0b01101;
    SSPDATPPS = 0b01110;
    RB5PPSbits.RB5PPS = 0b10000;
    RB6PPSbits.RB6PPS = 0b10001;
    
    
}
 void I2C_Master_Wait()
{
    while ((SSP1STAT & 0x04) || (SSP1CON2 & 0x1F));
}

void I2C_Master_Start()
{
    I2C_Master_Wait();
    SEN = 1;
}

void I2C_Start(char add)
{
    I2C_Master_Wait();
    SEN = 1;
    I2C_Master_Write(add);
}

void I2C_Master_RepeatedStart()
{
    I2C_Master_Wait();
    RSEN = 1;
}

void I2C_Master_Stop()
{
    I2C_Master_Wait();
    PEN = 1;
}

void I2C_ACK(void)
{
	ACKDT = 0;			// 0 -> ACK
    ACKEN = 1;			// Send ACK
    while(ACKEN);
}

void I2C_NACK(void)
{
	ACKDT = 1;			// 1 -> NACK
	ACKEN = 1;			// Send NACK
    while(ACKEN);
}

unsigned char I2C_Master_Write(unsigned char data)
{
    I2C_Master_Wait();
    SSPBUF = data;
    while(!SSP1IF);  // Wait Until Completion
	SSP1IF = 0;
    return ACKSTAT;
}

unsigned char I2C_Read_Byte(void)
{
    //---[ Receive & Return A Byte ]---
    I2C_Master_Wait();
    RCEN = 1;		  // Enable & Start Reception
	while(!SSP1IF);	  // Wait Until Completion
	SSP1IF = 0;		  // Clear The Interrupt Flag Bit
    I2C_Master_Wait();
    return SSP1BUF;	  // Return The Received Byte
}

unsigned char I2C_Read(unsigned char ACK_NACK)
{  
    //---[ Receive & Return A Byte & Send ACK or NACK ]---
    unsigned char Data;
    RCEN = 1;              
    while(!BF);      
    Data = SSP1BUF;           
    if(ACK_NACK==0)
        I2C_ACK();            
    else
        I2C_NACK();     
    while(!SSP1IF);                 
    SSP1IF=0;   
    return Data;
}