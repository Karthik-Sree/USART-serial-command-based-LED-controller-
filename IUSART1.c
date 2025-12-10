#include "stm32f4xx.h"
#include "IUSART1.h"
void IUSART1_Init(void)
{
	RCC->AHB1ENR |= ( 1 << 0 ); // AHB to enable GPIOA
	RCC->APB2ENR |= ( 1 << 4 ); //
	//PA9 as Tx
		GPIOA->MODER &= ~( 3 << ( 2 * 9 ) );
		GPIOA->MODER |=  ( 2 << ( 2 * 9 ) );
		// 0-7 = AFRL  8-15 = AFRH
		// Pin 9-8 = 1
		GPIOA->AFR[1] &= ~(15 << ( 4 * 1 ) );
		GPIOA->AFR[1] |=  ( 7 << ( 4 * 1 ) );
		//PA10 as Rx
		GPIOA->MODER &= ~( 3 << ( 2 * 10 ) );
		GPIOA->MODER |=  ( 2 << ( 2 * 10 ) );
		// 0-7 = AFRL  8-15 = AFRH
		// Pin 10-8 = 2
		GPIOA->AFR[1] &= ~( 15 << ( 4 * 2 ) );
		GPIOA->AFR[1] |=  ( 7 <<(4 * 2 ) );
		USART1->BRR = 0x8B;
		USART1->CR1 &= ~( 1 << 15 ); // over sampling by 16
		USART1->CR1 |= USART_CR1_UE; //enabling USART
		USART1->CR1 &= ~( 1 << 12 );// Word length 8N1
		USART1->CR1 &= ~( 1 << 10 ); //Parity is disabled
		USART1->CR1 |= USART_CR1_TE | USART_CR1_RE;// enabling Transmitter and receiver

		NVIC_EnableIRQ(USART1_IRQn );
		NVIC_SetPriority(USART1_IRQn,2);

       // NVIC_EnableIRQ(USART1_IRQn);
       // NVIC_SetPriority(USART1_IRQn,2);



}
