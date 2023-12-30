/*
 * main_GPIO.c
 *
 *  Created on: Dec 23, 2023
 *      Author: trietmt9
 */
#include <stm32f446xx.h>
#include <stm32f446xx_gpio_driver.h>
void GPIO_Init(void);
void IRQ_INIT(void);
int main(void)
{
    GPIO_Init();
    IRQ_INIT();
    

}

void GPIO_Init(void)
{
    GPIO_PinConfig_t GPIO_Struct = {0};
    // LED PA5
    GPIO_Struct.PinNumber   = GPIO_PIN_5;
    GPIO_Struct.PinMode     = GPIO_OUTPUT;
    GPIO_Struct.PinSpeed    = FAST;
    GPIO_Struct.PinOPType   = PushPull;
    GPIO_Struct.PinPUPDCtrl = NoPUPD;
    DRV_GPIO_Pclkcontrol(GPIOA, ENABLE);
    DRV_GPIO_Init(GPIOA, &GPIO_Struct);

    // Button PC13
    GPIO_Struct.PinNumber   = GPIO_PIN_13;
    GPIO_Struct.PinMode     = GPIO_IT_FALLING;
    GPIO_Struct.PinPUPDCtrl = PullUp; 
    DRV_GPIO_Pclkcontrol(GPIOC, ENABLE);
    DRV_GPIO_Init(GPIOC, &GPIO_Struct);
}

void IRQ_INIT(void)
{
    DRV_GPIO_IRQConfig(IRQ_NO_EXTI15_10, ENABLE);
    DRV_GPIO_IRQPriorityCFG(IRQ_NO_EXTI15_10, 15);
}

void EXTI15_10_IRQHandler(void)
{
    DRV_GPIO_IRQHandling(GPIO_PIN_13);
    DRV_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
}