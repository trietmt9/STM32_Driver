/*
 * stm32f4xx_gpio_driver.c
 *
 *  Created on: Dec 21, 2023
 *      Author: trietmt9
 */

#include <stm32f4xx_gpio_driver.h>

/*
 * Peripheral clock control APIs
 *
 * 
 */
void DRV_GPIO_Pclkcontrol(GPIO_TypeDef_t* pGPIOx, EnOrDi_State EnOrDi)
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

/*
 * Peripheral clock control APIs
 *
 * 
 */
void DRV_GPIO_Init(GPIO_TypeDef_t* pGPIOx, GPIO_PinConfig_t* pGPIOPinCofig)
{
    uint32_t temp; 
    // 1. Configure mode 
    if(pGPIOPinCofig->PinMode <= GPIO_ANALOG)
    {
        temp = (pGPIOPinCofig->PinMode << (2*pGPIOPinCofig->PinNumber));
        pGPIOx->MODER &= ~(0x03 << pGPIOPinCofig->PinNumber); // clear bit 
        pGPIOx->MODER |= temp; // set bit 
    }
    else
    {
        /* interrupts */
    }
    temp = 0;

    // 2. Configure speed
    temp = (pGPIOPinCofig->PinSpeed << (2*pGPIOPinCofig->PinNumber));
    pGPIOx->OSPEEDER &= ~(0x03 << pGPIOPinCofig->PinNumber); // clear bit 
    pGPIOx->OSPEEDER |= temp; // set bit 
    temp = 0;

    // 3. Configure pull up pull down configuration
    temp = (pGPIOPinCofig->PinPUPDCtrl << (2*pGPIOPinCofig->PinNumber));
    pGPIOx->PUPDR &= ~(0x03 << pGPIOPinCofig->PinNumber); // clear bit 
    pGPIOx->PUPDR |= temp; //set bit 
    temp = 0;

    // 4. Configure output type 
    temp = (pGPIOPinCofig->PinOPType << pGPIOPinCofig->PinNumber);
    pGPIOx->OTYPER &= ~(0x01 << pGPIOPinCofig->PinNumber); // clear bit 
    pGPIOx->OTYPER |= temp; //set bit
    temp = 0;

    // 5. Configure alternative function
    if(pGPIOPinCofig->PinAltFunction == GPIO_ALTERNATE)
    {
        uint32_t temp1, temp2;
        temp1 = pGPIOPinCofig->PinNumber/8;
        temp2 = pGPIOPinCofig->PinNumber%8;
        pGPIOx->AFR[temp1] &= ~(0xFF << (4*temp2));
        pGPIOx->AFR[temp1] |= (pGPIOPinCofig->PinAltFunction << (4*temp2));
    }

}

/*
 * Peripheral clock control APIs
 *
 * 
 */
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

/*
 * Peripheral clock control APIs
 *
 * 
 */
uint8_t  DRV_GPIO_ReadPin(GPIO_TypeDef_t* pGPIOx, uint8_t PinNumber)
{
    uint8_t Value; 
    Value = (uint8_t) (pGPIOx->IDR >> PinNumber) & 0x01U;
    return Value;
}
uint16_t DRV_GPIO_ReadPort(GPIO_TypeDef_t* pGPIOx)
{
    uint16_t Value; 
    Value = (uint16_t) pGPIOx->IDR;
    return Value;
}
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
void DRV_GPIO_WritePort(GPIO_TypeDef_t* pGPIOx, Pin_State Value)
{
    pGPIOx->ODR = Value;
}
void DRV_GPIO_TogglePin(GPIO_TypeDef_t* pGPIOx, uint8_t PinNumber)
{
    pGPIOx->ODR ^= (1 << PinNumber);
}
