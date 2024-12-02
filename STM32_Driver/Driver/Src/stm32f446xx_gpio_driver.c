/*
 * stm32f4xx_gpio_driver.c
 *
 *  Created on: Dec 21, 2023
 *      Author: trietmt9
 */

#include <stm32f446xx_gpio_driver.h>

/*******************************************************
 * @fn                     - DRV_GPIO_Pclkcontrol
 * 
 * @brief                  - Enable or Disable peripheral clock 
 * 
 * @param                  - pGPIOx: Port of  the MCU
 * @param                  - EnOrDi: Enable or Disable 
 * 
 * @return                 - void
********************************************************/
void DRV_GPIO_Pclkcontrol(GPIO_TypeDef_t* pGPIOx,  EnOrDi_State EnOrDi)
{
    if (EnOrDi == ENABLE)
    {
        if(pGPIOx == GPIOA) GPIOA_PCLK_EN();
        else if(pGPIOx == GPIOB) GPIOB_PCLK_EN();
        else if(pGPIOx == GPIOC) GPIOC_PCLK_EN();
        else if(pGPIOx == GPIOD) GPIOD_PCLK_EN();
        else if(pGPIOx == GPIOE) GPIOE_PCLK_EN();
        else if(pGPIOx == GPIOF) GPIOF_PCLK_EN();
        else if(pGPIOx == GPIOG) GPIOG_PCLK_EN();
        else if(pGPIOx == GPIOH) GPIOH_PCLK_EN();
    }
    else
    {
        if(pGPIOx == GPIOA) GPIOA_PCLK_DI();
        else if(pGPIOx == GPIOB) GPIOB_PCLK_DI();
        else if(pGPIOx == GPIOC) GPIOC_PCLK_DI();
        else if(pGPIOx == GPIOD) GPIOD_PCLK_DI();
        else if(pGPIOx == GPIOE) GPIOE_PCLK_DI();
        else if(pGPIOx == GPIOF) GPIOF_PCLK_DI();
        else if(pGPIOx == GPIOG) GPIOG_PCLK_DI();
        else if(pGPIOx == GPIOH) GPIOH_PCLK_DI();
    }
    
}

/*******************************************************
 * @fn                     - DRV_GPIO_Init
 * 
 * @brief                  - Initialize GPIO 
 * 
 * @param                  - pGPIOx: Port of  the MCU
 * @param                  - pGPIOConfig: Pin configuration variable
 * 
 * @return                 - void
********************************************************/
void DRV_GPIO_Init(GPIO_HandleTypeDef* pGPIO_Handle)
{
    uint32_t temp; 

    // Enable peripheral clock 
    DRV_GPIO_Pclkcontrol(pGPIO_Handle->pGPIOx, ENABLE);
    // 1. Configure mode 
    if(pGPIO_Handle->GPIO_PinConfig.PinMode <= GPIO_ANALOG)
    {
        temp = (pGPIO_Handle->GPIO_PinConfig.PinMode << (2*pGPIO_Handle->GPIO_PinConfig.PinNumber));
        pGPIO_Handle->pGPIOx->MODER &= ~(0x03 << pGPIO_Handle->GPIO_PinConfig.PinNumber); // clear bit
        pGPIO_Handle->pGPIOx->MODER |= temp; // set bit
    }
    else
    {
        /* interrupts */
        if(pGPIO_Handle->GPIO_PinConfig.PinMode == GPIO_IT_FALLING)
        {
            /* 1. Configure FTSR ( Falling Trigger Select Register) */
            EXTI->FTSR |= (1<< pGPIO_Handle->GPIO_PinConfig.PinNumber);// set FTSR bit
            EXTI->RTSR &= ~(1<< pGPIO_Handle->GPIO_PinConfig.PinNumber);// clear RTSR bit
        }
        else if(pGPIO_Handle->GPIO_PinConfig.PinMode == GPIO_IT_RISING)
        {
            /* 1. Configure RTSR ( Falling Trigger Select Register) */
            EXTI->RTSR |= (1<< pGPIO_Handle->GPIO_PinConfig.PinNumber); // set RTSR bit
            EXTI->FTSR &= ~(1<< pGPIO_Handle->GPIO_PinConfig.PinNumber);// clear FTSR bit
        }
        else if (pGPIO_Handle->GPIO_PinConfig.PinMode == GPIO_IT_FALLING_RISING)
        {
            /* 1. Configure both register */
            EXTI->RTSR |= (1<< pGPIO_Handle->GPIO_PinConfig.PinNumber);// set RTSR bit
            EXTI->FTSR |= (1<< pGPIO_Handle->GPIO_PinConfig.PinNumber);// set FTSR bit            
        }

        // 2. Configure the GPIO port selection in SYSCFG_EXTIR
        uint8_t temp1 = pGPIO_Handle->GPIO_PinConfig.PinNumber/4;
        uint8_t temp2 = pGPIO_Handle->GPIO_PinConfig.PinNumber%4;
        uint8_t portcode = GPIO_BASE_TO_CODE(pGPIO_Handle->pGPIOx);
        SYSCFG_PCLK_EN();
        SYSCFG->EXTICR[temp1] = portcode << (4*temp2);
        // 3. Enable EXTI deliver using IMR
        EXTI->IMR |= (1<< pGPIO_Handle->GPIO_PinConfig.PinNumber);
        

    }
    temp = 0;

    // 2. Configure speed
    temp = (pGPIO_Handle->GPIO_PinConfig.PinSpeed << (2*pGPIO_Handle->GPIO_PinConfig.PinNumber));
    pGPIO_Handle->pGPIOx->OSPEEDER &= ~(0x03 << pGPIO_Handle->GPIO_PinConfig.PinNumber); // clear bit 
    pGPIO_Handle->pGPIOx->OSPEEDER |= temp; // set bit 
    temp = 0;

    // 3. Configure pull up pull down configuration
    temp = (pGPIO_Handle->GPIO_PinConfig.PinPUPDCtrl << (2*pGPIO_Handle->GPIO_PinConfig.PinNumber));
    pGPIO_Handle->pGPIOx->PUPDR &= ~(0x03 << pGPIO_Handle->GPIO_PinConfig.PinNumber); // clear bit 
    pGPIO_Handle->pGPIOx->PUPDR |= temp; //set bit 
    temp = 0;

    // 4. Configure output type 
    temp = (pGPIO_Handle->GPIO_PinConfig.PinOPType << pGPIO_Handle->GPIO_PinConfig.PinNumber);
    pGPIO_Handle->pGPIOx->OTYPER &= ~(0x01 << pGPIO_Handle->GPIO_PinConfig.PinNumber); // clear bit 
    pGPIO_Handle->pGPIOx->OTYPER |= temp; //set bit
    temp = 0;

    // 5. Configure alternative function
    if(pGPIO_Handle->GPIO_PinConfig.PinMode == GPIO_ALTERNATE)
    {
        uint32_t temp1, temp2;
        temp1 = pGPIO_Handle->GPIO_PinConfig.PinNumber/8;
        temp2 = pGPIO_Handle->GPIO_PinConfig.PinNumber%8;
        pGPIO_Handle->pGPIOx->AFR[temp1] &= ~(0xFF << (4*temp2));
        pGPIO_Handle->pGPIOx->AFR[temp1] |= (pGPIO_Handle->GPIO_PinConfig.PinAltFunction << (4*temp2));
    }

}

/*******************************************************
 * @fn                     - DRV_GPIO_DeInit
 * 
 * @brief                  - Reset GPIO register 
 * 
 * @param                  - pGPIOx: Port of  the MCU
 * 
 * @return                 - void
********************************************************/
void DRV_GPIO_DeInit(GPIO_TypeDef_t* pGPIOx)
{
        if(pGPIOx == GPIOA) GPIOA_REG_RESET();
        else if(pGPIOx == GPIOB) GPIOB_REG_RESET();
        else if(pGPIOx == GPIOC) GPIOC_REG_RESET();
        else if(pGPIOx == GPIOD) GPIOD_REG_RESET();
        else if(pGPIOx == GPIOE) GPIOE_REG_RESET();
        else if(pGPIOx == GPIOF) GPIOF_REG_RESET();
        else if(pGPIOx == GPIOG) GPIOG_REG_RESET();
        else if(pGPIOx == GPIOH) GPIOH_REG_RESET();
}

/*******************************************************
 * @fn                     - DRV_GPIO_ReadPin
 * 
 * @brief                  - Read data from pin 
 * 
 * @param                  - pGPIOx: Port of  the MCU
 * @param                  - PinNumber: Pin Number  
 * 
 * @return                 - 8 bits unsigned integer 
********************************************************/
uint8_t  DRV_GPIO_ReadPin(GPIO_TypeDef_t* pGPIOx, uint8_t PinNumber)
{
    uint8_t Value; 
    Value = (uint8_t) (pGPIOx->IDR >> PinNumber) & 0x01U;
    return Value;
}

/*******************************************************
 * @fn                     - DRV_GPIO_ReadPort
 * 
 * @brief                  - Read data from port
 * 
 * @param                  - pGPIOx: Port of  the MCU 
 * 
 * @return                 - 16 bits unsigned integer 
********************************************************/
uint16_t DRV_GPIO_ReadPort(GPIO_TypeDef_t* pGPIOx)
{
    uint16_t Value; 
    Value = (uint16_t) pGPIOx->IDR;
    return Value;
}

/*******************************************************
 * @fn                     - DRV_GPIO_WritePin
 * 
 * @brief                  - Write data to attached pin 
 * 
 * @param                  - pGPIOx: Port of  the MCU
 * @param                  - PinNumber: Pin Number
 * @param                  - Value: SET or RESET level to attached pin
 * 
 * @return                 - void
********************************************************/
void DRV_GPIO_WritePin(GPIO_TypeDef_t* pGPIOx, uint8_t PinNumber ,Pin_State Value)
{
    if(Value == SET_PIN || Value == SET)
    {
        pGPIOx->ODR |= (1<<PinNumber);
    }
    else
    {
        pGPIOx->ODR &= ~(1<<PinNumber);
    }
}

/*******************************************************
 * @fn                     - DRV_GPIO_WritePort
 * 
 * @brief                  - Write data to attched port
 * 
 * @param                  - pGPIOx: Port of  the MCU
 * @param                  - Value: SET or RESET level to attached port
 * 
 * @return                 - void
********************************************************/
void DRV_GPIO_WritePort(GPIO_TypeDef_t* pGPIOx, Pin_State Value)
{
    pGPIOx->ODR = Value;
}

/*******************************************************
 * @fn                     - DRV_GPIO_WritePort
 * 
 * @brief                  - Write data to attched port
 * 
 * @param                  - pGPIOx: Port of  the MCU
 * @param                  - PinNumber: Pin number of the MCU
 * 
 * @return                 - void
********************************************************/
void DRV_GPIO_TogglePin(GPIO_TypeDef_t* pGPIOx, uint8_t PinNumber)
{
    pGPIOx->ODR ^= (1 << PinNumber);
}

/*******************************************************
 * @fn                     - DRV_GPIO_IRQConfig
 * 
 * @brief                  - Configure interrupt mode
 * 
 * @param                  - IRQNumber: Interrupt number in the MCU
 * @param                  - EnOrDi: Enable or Disable interrupts
 * 
 * @return                 - void
********************************************************/
void DRV_GPIO_IRQConfig(uint8_t IRQNumber, EnOrDi_State EnOrDi)
{
    if( EnOrDi == ENABLE)
    {
        if(IRQNumber <= 31)
        {
            // ISER0 register
            *NVIC_ISER_0 |= (1 << IRQNumber);
        }
        else if (IRQNumber > 31 && IRQNumber < 64)
        {
            // ISER1 register
            *NVIC_ISER_1 |= (1 << (IRQNumber % 32));
        }
        else if (IRQNumber >= 64 && IRQNumber <96)
        {
            *NVIC_ISER_2 |= (1 << (IRQNumber % 64));
        }
    }
    else 
    {
        if(IRQNumber <= 31)
        {
            *NVIC_ICER_0 |= (1 << IRQNumber);
        }
        else if (IRQNumber > 31 && IRQNumber < 64)
        {
            *NVIC_ICER_1 |= (1 << (IRQNumber % 32));
        }
        else if (IRQNumber >= 64 && IRQNumber <96)
        {
            *NVIC_ICER_2 |= (1 << (IRQNumber % 64));
        }
    }
}

/*******************************************************
 * @fn                     - DRV_GPIO_IRQPriorityCFG
 * 
 * @brief                  - Configure priority 
 * 
 * @param                  - IRQNumber: IRQ interrupt number
 * @param                  - IRQPriority: Priority of IRQ
 * 
 * @return                 - void
********************************************************/
void DRV_GPIO_IRQPriorityCFG(uint8_t IRQNumber, uint8_t IRQPriority)
{
    //1. determine IPR register 
    uint8_t IPRx = IRQNumber/4; //IPR register
    uint8_t IPRxSec = IRQNumber%4; // IPR sections
    uint8_t shift_amount = (8 * IPRxSec) + (8 - NUM_PR_BITS_IMPLEMENTED);
    *(NVIC_PR_BASE + (IPRx*4)) |= (IRQPriority << shift_amount);
}

/*******************************************************
 * @fn                     - DRV_GPIO_IRQHandling
 * 
 * @brief                  - Handling IRQ APIs
 * 
 * @param                  - PinNumber: pin number
 * 
 * @return                 - void
********************************************************/
void DRV_GPIO_IRQHandling(uint8_t PinNumber)
{
    // Clear the EXTI PR register corresponding to pin number 
    if(EXTI->PR & (1 << PinNumber))
    {
        // clear 
        EXTI->PR |= (1<<PinNumber);
    }
}
