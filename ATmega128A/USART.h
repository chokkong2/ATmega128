/*
 * USART.h
 *
 * Created: 2022-01-24 오후 3:57:24
 *  Author: RRLPC1
 */ 


#ifndef USART_H_
#define USART_H_

void USART0_init (void);
void USART1_init (void);
void Tx_MCUtoPC (unsigned char *InstrPacket);
void Tx_MCUtoPC_Char (unsigned char StatusPacket);
void Tx_PCtoDyn (unsigned char *InstrPacket);
void reset_arr(unsigned char *instr, int len);

#endif /* USART_H_ */