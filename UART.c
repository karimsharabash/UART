/*
 * UART.c

 *
 *  Created on: Aug 11, 2016
 *      Author: ahmed
 */
#include <avr/io.h>

void Uart_init(long BaudRate)
	{
		unsigned short int BRvalue=0;
		UCSRB=(1<<RXEN)|(1<<TXEN); // enable reciever and transmitter
		UCSRC=(1<<URSEL)|(1<<UCSZ0)|(1<<UCSZ1); // select ucsrc and character size 8 bits
		BRvalue=(unsigned char)(((F_CPU)/(16*BaudRate))-1); // to calculate the value of the baud rate reg
		UBRRL=BRvalue; 			//low byte
	    UBRRH=(BRvalue>>8); 	//high byte
	}

void UART_send_byte( char byte)
 {
	while(!(UCSRA &(1<<UDRE))); // while shift register flag != 1 (not empty))
	UDR=byte;
 }

void UART_send_string( char *ptr)
 {
	unsigned char  i=0;

		while(ptr[i] != '\0')
		 {
			UART_send_byte(ptr[i]);
			i++;
		 }
	UART_send_byte(ptr[i]);
 }

 char  UART_recieve_byte(void)
 {
	while((UCSRA & (1<<RXC)) ==0); //check for the recieve flag . this flag cleared automatic after taking the byte from the buffer

		return UDR ;


 }
void  UART_recieve_string(char * ptr)
 {
  unsigned char i=0;
	do
	{

	ptr[i]=UART_recieve_byte();

	}while(ptr[i++]!='\0');


 }

