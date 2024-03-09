/*
 * main_GPIO.c
 *
 *  Created on: Dec 23, 2023
 *      Author: trietmt9
 */
#include <stm32f446xx.h>
#include <stm32f446xx_gpio_driver.h>

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
    /**
     * @brief Initialize the GPIO
     * @details This function initializes the GPIO pins used by the application.
     */
    GPIO_Init();

    /**
     * @brief Initialize the interrupt
     * @details This function initializes the interrupt used by the application.
     */
    IRQ_INIT();

    /**
     * @brief Infinite loop
     * @details This loop runs forever, switching between different modes of operation.
     */
    while (1)
    {
        /**
         * @brief Switch between modes
         * @details This switch statement allows the user to switch between different modes of operation.
         */
        switch (mode)
        {
        case 0:
            /**
             * @brief Set the LED pin high
             * @details This function sets the LED pin to high.
             */
            DRV_GPIO_WritePin(GPIOA, GPIO_PIN_6, SET);
            break;

        case 1:
            /**
             * @brief Set the LED pin low
             * @details This function sets the LED pin to low.
             */
            DRV_GPIO_WritePin(GPIOA, GPIO_PIN_6, RESET);
            break;

        case 2:
            /**
             * @brief Toggle the LED pin
             * @details This function toggles the LED pin.
             */
            DRV_GPIO_TogglePin(GPIOA, 6);
            delay(500);
            break;

        default:
            /**
             * @brief Reset the mode to zero
             * @details This statement resets the mode variable to zero if it is greater than two.
             */
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
    GPIO_PinConfig_t GPIO_Struct = {0};

    // LED PA5
    GPIO_Struct.PinNumber   = GPIO_PIN_6;
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
