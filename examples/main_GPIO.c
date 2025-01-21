/*
 * main_SPI.c
 *
 *  Created on: Dec 28, 2023
 *      Author: pc
 */

#include <stm32f446xx.h>
#include <stm32f446xx_spi_driver.h>
#include <stm32f446xx_gpio_driver.h>
#include <string.h>

void GPIO_INIT(void);
void SPI_INIT(void);
void delay(uint32_t timeout)
{
    for(volatile uint32_t i = 0; i < (timeout*1000); i++);
}
int main(void)
{

    GPIO_INIT();
    while(1)
    {    
        DRV_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
        delay(500);
    }
	return 0;
}
void GPIO_INIT(void)
{
    GPIO_HandleTypeDef                    LEDPin;
    LEDPin.pGPIOx                         = GPIOA;
    LEDPin.GPIO_PinConfig.PinNumber       = 5;
    LEDPin.GPIO_PinConfig.PinMode         = GPIO_OUTPUT;
    LEDPin.GPIO_PinConfig.PinOPType       = PushPull;
    LEDPin.GPIO_PinConfig.PinPUPDCtrl     = NoPUPD;
    LEDPin.GPIO_PinConfig.PinSpeed        = FAST;

    DRV_GPIO_Pclkcontrol(LEDPin.pGPIOx, ENABLE);
}


