/* Example code for a multi-tasking system with four tasks */

#include "cmsis.h"

#define LED1 (1UL<<13)
#define LED2 (1UL<<14)
#define COUNT_TIMES (0x1000000)

void LED_initialize(void); // Initialize LED
// -------------------------------------------------------------
// Start of main program
int main(void)
{
	volatile long int count = 0;
	LED_initialize();
	for(;;){
		for(count = 0; count < COUNT_TIMES; count++);
		GPIOG->BSRR = LED1;
		GPIOG->BSRR = (LED2 << 16);
		for(count = 0; count < COUNT_TIMES; count++);
		GPIOG->BSRR = (LED1 << 16);
		GPIOG->BSRR = LED2;
	}

}


// ------------------------------------------------------------
void LED_initialize(void)
{
	// Configure LED outputs
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOGEN; // Enable Port D clock
	// Set pin 13, 14 as general purpose output mode (pull-push)
	GPIOG->MODER |= (GPIO_MODER_MODER13_0 |GPIO_MODER_MODER14_0);
	GPIOG->OTYPER |= 0; // No need to change - use pull-push output
	GPIOG->OSPEEDR |= ( GPIO_OSPEEDER_OSPEEDR13 | GPIO_OSPEEDER_OSPEEDR14);// 100MHz operations
	GPIOG->PUPDR = 0; // No pull up , no pull down
	return;
}
// ------------------------------------------------------------
