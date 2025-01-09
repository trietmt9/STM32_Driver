/*
 * main.c
 *
 *  Created on: Dec 23, 2023
 *      Author: trietmt9
 */
#include "stm32f446xx.h"
#include "stm32f446xx_gpio_driver.h"

volatile uint8_t mode = 0; 

void delay(uint32_t timeout)
{
    for(uint32_t i = 0; i < (timeout*1000); i++);
}

void GPIO_Init(void);
void IRQ_INIT(void);
/**
 * @brief Main function
 * @details This function is the entry point of the application.
 * @retval int
 */
int main(void)
{
    GPIO_Init();
    IRQ_INIT();
    while (1)
    {
        switch (mode)
        {
        case 0:
            DRV_GPIO_WritePin(GPIOA, GPIO_PIN_5, SET);
            break;

        case 1:
            DRV_GPIO_WritePin(GPIOA, GPIO_PIN_5, RESET);
            break;

        case 2:
            DRV_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
            delay(500);
            break;

        default:
            mode = 0;
            break;
        }
    }
}

/**
 * @brief  Initializes the GPIO pins
 * @param  None
 * @retval None
 */
void GPIO_Init(void)
{
    GPIO_HandleTypeDef GPIO_Struct = {0};

    // LED PA5
    GPIO_Struct.pGPIOx                                      = GPIOA;
    GPIO_Struct.GPIO_PinConfig.PinNumber                    = GPIO_PIN_5;
    GPIO_Struct.GPIO_PinConfig.PinMode                      = GPIO_OUTPUT;
    GPIO_Struct.GPIO_PinConfig.PinSpeed                     = FAST;
    GPIO_Struct.GPIO_PinConfig.PinOPType                    = PushPull;
    GPIO_Struct.GPIO_PinConfig.PinPUPDCtrl                  = NoPUPD;
    DRV_GPIO_Init(&GPIO_Struct);
    // Button PC13
    GPIO_Struct.pGPIOx                                      = GPIOC;
    GPIO_Struct.GPIO_PinConfig.PinNumber                    = GPIO_PIN_13;
    GPIO_Struct.GPIO_PinConfig.PinMode                      = GPIO_IT_FALLING;
    GPIO_Struct.GPIO_PinConfig.PinPUPDCtrl                  = PullUp; 
    DRV_GPIO_Init(&GPIO_Struct);
}

/**
 * @brief Initialize the interrupt
 * @details This function initializes the interrupt used by the application.
 */
void IRQ_INIT(void)
{
    DRV_GPIO_IRQConfig(IRQ_NO_EXTI15_10, ENABLE);
    DRV_GPIO_IRQPriorityCFG(IRQ_NO_EXTI15_10, 15);
}

/**
 * @brief Interrupt service routine for EXTI15_10
 *
 * This function is the interrupt service routine for EXTI15_10. It is triggered
 * whenever the button connected to PC13 is pressed. The function increments the
 * mode variable, which is used to switch between different modes of operation.
 */
void EXTI15_10_IRQHandler(void)
{
    DRV_GPIO_IRQHandling(GPIO_PIN_13);
    mode++;
}
