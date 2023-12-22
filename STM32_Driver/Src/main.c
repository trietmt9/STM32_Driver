/*
 * main.c
 *
 *  Created on: Dec 23, 2023
 *      Author: trietmt9
 */
#include <stm32f446xx.h>
#include <stm32f446xx_gpio_driver.h>
void GPIO_Init(void);

int main(void)
{
    GPIO_Init();
    DRV_GPIO_TogglePin(GPIOA, GPIO_PIN_5);

}

void GPIO_Init(void)
{
    GPIO_PinConfig_t GPIO_Struct = {0};
    GPIO_Struct.PinNumber   = GPIO_PIN_5;
    GPIO_Struct.PinMode     = GPIO_OUTPUT;
    GPIO_Struct.PinSpeed    = FAST;
    GPIO_Struct.PinOPType   = PushPull;
    GPIO_Struct.PinPUPDCtrl = NoPUPD;
    DRV_GPIO_Pclkcontrol(GPIOA, ENABLE);
    DRV_GPIO_Init(GPIOA, &GPIO_Struct);
}
