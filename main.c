main.c
/*
this is the main.c file for execution 
*/
#include "stm32f4xx.h"
#include "IUSART1.h"
void USART1_echo(char *input);
void delay(volatile uint32_t t)
{
    while(t--);
}
volatile uint8_t e=0;
volatile uint8_t c ;
uint8_t rx_buf[32];
uint8_t rx_index=0;

void USART1_echo(char *input )
{
	char *p;
	char expected_response[]="L1 en";
	char valid_response[]="Received\r\n";
	char invalid_response[]="Cannot identify command\r\n";
	if (  (strcmp(input,expected_response))==0 )
	{
		p= valid_response;
		e=10;
		while(e--)
		{
		GPIOA->BSRR = ( 1 << 2)
		delay(300000);
		GPIOA->BSRR = (1 <<( 16 + 2 ) );
				delay(300000);
		}
	}
	else{
		p = invalid_response;
	}
	while(*p)
	{
		while( !(USART1->SR & USART_SR_TXE) );
			USART1->DR = *p++;
	}
}
void USART1_IRQHandler(void)
{
	if(USART1->SR & USART_SR_RXNE)
	{
		c= USART1->DR;
	if (c =='\n')
		return;
	if ( c !='\r')
	{
		rx_buf[rx_index++]= c;
		return;
	}
	     rx_buf[rx_index] = '\0';

		USART1_echo(rx_buf);
		rx_index=0;
	}
}
void main(void)
{
	IUSART1_Init();
   RCC->AHB1ENR |= ( 1 << 0 ); // Enable AHB clock for GPIOA
   GPIOA->PUPDR &= ~(3  << ( 2 * 2 ); // no Push up or Pull down
   GPIOA->MODER &= ~( 3 << (2  * 2)); // PA2 as LED
   GPIOA->MODER |= ( 1 << ( 2 * 2)); // mode is configured as output
   USART1->CR1 |= USART_CR1_RXNEIE; // enable Receive interrupt for USART1
	while(1)
	{
			}
}
