/* 
 * File:   TMR0.h
 * Author: Mario
 *
 */

#ifndef TMR0_H
#define	TMR0_H


#include <stdint.h>
#include <pic16f1709.h>


#define TMR0_CLK_FOSCDIV4   0
#define TMR0_CLK_TOCKIpin   1

#define TMR0_EDGE_RISE      0
#define TMR0_EDGE_FALL      1

#define TMR0_PRESC_2        0
#define TMR0_PRESC_4        1
#define TMR0_PRESC_8        2
#define TMR0_PRESC_16       3
#define TMR0_PRESC_32       4
#define TMR0_PRESC_64       5
#define TMR0_PRESC_128      6
#define TMR0_PRESC_256      7
#define TMR0_PRESC_DISABLE  8

/******************************************************************************
 * 						APIs supported by this driver
 *****************************************************************************/


void TMR0_setup (uint8_t TMR0_CLK, uint8_t TMR0_EDGE, uint8_t TMR0_PRESC);
void TMR0_INT_Handle(uint8_t TMR0REG_VALUE);
void TMR0_EnableInterrupts(void);

#endif	/* TMR0_H */

