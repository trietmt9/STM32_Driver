#include <stm32f446xx_gpio_driver.h>

/******************************************************************************************
*                                  API supports by this driver
*                             Check API in the function definitions
******************************************************************************************/

/*****************************************************************
* @fn          - GPIO_Init
* @brief       - This function will set the GPIO peripheral
* @param[in]   - Base address of each GPIO peripheral
*
* @return      - None
*
* @note        - None
*****************************************************************/
void GPIO_Init(GPIO_Handle_t* pGPIOHandle)
{
    uint8_t temp;
    /* 1. Configure the mode of the pin */
    if(pGPIOHandle->GPIO_PinCFG.GPIO_PinMode <= GPIO_MODE_ANALOG)
    {
        temp = (pGPIOHandle->GPIO_PinCFG.GPIO_PinMode << (2 * pGPIOHandle->GPIO_PinCFG.GPIO_PinNumber));
        pGPIOHandle->pGPIOx->MODER &=~ (0x3 << pGPIOHandle->GPIO_PinCFG.GPIO_PinNumber );
        pGPIOHandle->pGPIOx->MODER |= temp; 
        temp = 0;
    }
    /* 2. Configure the speed output of the pin*/
    temp = (pGPIOHandle->GPIO_PinCFG.GPIO_PinSpeed << (2 * pGPIOHandle->GPIO_PinCFG.GPIO_PinNumber));
    pGPIOHandle->pGPIOx->OSPEEDR &=~ (0x3 << pGPIOHandle->GPIO_PinCFG.GPIO_PinNumber );
    pGPIOHandle->pGPIOx->OSPEEDR |= temp; 
    temp = 0;
    /* 3. Configure the Pull Up and Pull Down setting*/
    temp = (pGPIOHandle->GPIO_PinCFG.GPIO_PuPd << (2 * pGPIOHandle->GPIO_PinCFG.GPIO_PinNumber));
    pGPIOHandle->pGPIOx->PUPDR &=~ (0x3 << pGPIOHandle->GPIO_PinCFG.GPIO_PinNumber );
    pGPIOHandle->pGPIOx->PUPDR |= temp; 
    temp = 0;
    /* 4. Configure the output type of the pin */
    temp = (pGPIOHandle->GPIO_PinCFG.GPIO_PinOPType << pGPIOHandle->GPIO_PinCFG.GPIO_PinNumber);
    pGPIOHandle->pGPIOx->OTYPER &=~ (0x1 << pGPIOHandle->GPIO_PinCFG.GPIO_PinNumber );
    pGPIOHandle->pGPIOx->OTYPER |= temp; 
    temp = 0;
    /* 5 Configure alternate function */
    if((pGPIOHandle->GPIO_PinCFG.GPIO_PinMode == GPIO_MODE_ALT))
    {
        uint8_t temp1, temp2;
        temp1 = pGPIOHandle->GPIO_PinCFG.GPIO_PinNumber / 8;
        temp2 = pGPIOHandle->GPIO_PinCFG.GPIO_PinNumber % 8;
        pGPIOHandle->pGPIOx->AFR[temp1] &=~ (0xFF << (4*temp2));
        pGPIOHandle->pGPIOx->AFR[temp1] |= (pGPIOHandle->GPIO_PinCFG.GPIO_PinAlt << (4*temp2)); 
    }

}

/*****************************************************************
* @fn          - GPIO_DeInit
* @brief       - This function will reset the given GPIO port
* @param[in]   - Base address of each GPIO peripheral
*
* @return      - None
*
* @note        - None
*****************************************************************/
void GPIO_DeInit(GPIO_TypeDef* pGPIOx)
{
    if(pGPIOx == GPIOA)         RCC_AHB1RSTR_GPIOARST;
    else if(pGPIOx == GPIOB) 	RCC_AHB1RSTR_GPIOBRST;
    else if(pGPIOx == GPIOC) 	RCC_AHB1RSTR_GPIOCRST;
    else if(pGPIOx == GPIOD) 	RCC_AHB1RSTR_GPIODRST;
    else if(pGPIOx == GPIOE) 	RCC_AHB1RSTR_GPIOERST;
    else if(pGPIOx == GPIOF) 	RCC_AHB1RSTR_GPIOFRST;
    else if(pGPIOx == GPIOG) 	RCC_AHB1RSTR_GPIOGRST;
    else if(pGPIOx == GPIOH) 	RCC_AHB1RSTR_GPIOHRST;
}

/*****************************************************************
* @fn          - GPIO_PCLK_CTRL
* @brief       - This function will enable or disable peripheral clock for the given GPIO port
* @param[in]   - Base address of each GPIO peripheral
* @param[in]   - Enable or Disable macros
*
* @return      - None
*
* @note        - None
*****************************************************************/
void GPIO_PCLK_CTRL(GPIO_TypeDef* pGPIOx)
{
    if(pGPIOx == GPIOA)         RCC_AHB1ENR_GPIOAEN;
    else if(pGPIOx == GPIOB) 	RCC_AHB1ENR_GPIOBEN;
    else if(pGPIOx == GPIOC) 	RCC_AHB1ENR_GPIOCEN;
    else if(pGPIOx == GPIOD) 	RCC_AHB1ENR_GPIODEN;
    else if(pGPIOx == GPIOE) 	RCC_AHB1ENR_GPIOEEN;
    else if(pGPIOx == GPIOF) 	RCC_AHB1ENR_GPIOFEN;
    else if(pGPIOx == GPIOG) 	RCC_AHB1ENR_GPIOGEN;
    else if(pGPIOx == GPIOH) 	RCC_AHB1ENR_GPIOHEN;
}
/*****************************************************************
* @fn          - GPIO_ReadPin
* @brief       - This function will read digital input of the given GPIO pin and GPIO Port
* @param[in]   - Base address of each GPIO peripheral
* @param[in]   - Pin number in  GPIO
* @param[in]   -
*
* @return      - unsigned 8 bit integer
*
* @note        - None
*****************************************************************/
uint8_t GPIO_ReadPin(GPIO_TypeDef* pGPIOx, uint8_t PinNumber)
{
    uint8_t Value; 
    Value = (uint8_t)(pGPIOx->IDR >> PinNumber) & 0x01;
    return Value;
}

/*****************************************************************
* @fn          - GPIO_ReadPort
* @brief       - This function will read digital input of the the given GPIO port
* @param[in]   - Base address of each GPIO peripheral
*
* @return      - unsigned 16 bit integer
*
* @note        - None
*****************************************************************/
uint16_t GPIO_ReadPort(GPIO_TypeDef* pGPIOx)
{
    uint16_t Value;
    Value = (uint16_t)(pGPIOx->IDR);
    return Value;
}

/*****************************************************************
* @fn          - GPIO_WritePin
* @brief       - This function write a digital signal output of the given GPIO pin and GPIO port
* @param[in]   - Base address of each GPIO peripheral
* @param[in]   - Pin number
* @param[in]   - SET or RESET macros
*
* @return      - None
*
* @note        - None
*****************************************************************/
void GPIO_WritePin(GPIO_TypeDef* pGPIOx, uint8_t PinNumber, uint8_t Value)
{
    if(pGPIOx->ODR == GPIO_PIN_SET)
    {
        pGPIOx->ODR |= (1 << PinNumber);
    }
    else
    {
        pGPIOx->ODR &=~(1 << PinNumber);
    }
}

/*****************************************************************
* @fn          - GPIO_WritePort
* @brief       - This function write a digital signal output of the given GPIO port
* @param[in]   - Base address of each GPIO peripheral
* @param[in]   - Enable or Disable macros
* @param[in]   -
*
* @return      - None
*
* @note        - None
*****************************************************************/
void GPIO_WritePort(GPIO_TypeDef* pGPIOx, uint16_t Value)
{
    pGPIOx->ODR = Value; 
}

/*****************************************************************
* @fn          - GPIO_TogglePin
* @brief       - This function will toggle the given output GPIO pin and GPIO port
* @param[in]   - Base address of each GPIO peripheral
* @param[in]   - Pin number
*
* @return      - None
*
* @note        - None
*****************************************************************/
void GPIO_TogglePin(GPIO_TypeDef* pGPIOx, uint8_t PinNumber)
{
    pGPIOx->ODR ^= (1<<PinNumber);
}

/*****************************************************************
* @fn          - GPIO_IRQ_Config
* @brief       - This function will configure the interrupt request
* @param[in]   - Base address of each GPIO peripheral
* @param[in]   - IRQ Priority
* @param[in]   - Enable or Disable macros
*
* @return      - None
*
* @note        - None
*****************************************************************/
void GPIO_IRQ_Config(uint8_t IRQNumber, uint8_t IRQPriority, uint8_t EnOrDi)
{

}

/*****************************************************************
* @fn          - GPIO_ReadPin
* @brief       - This function will handle the IRQ
* @param[in]   - Pin number
*
* @return      - None
*
* @note        - None
*****************************************************************/
void GPIO_IRQ_Handling(uint8_t PinNumber)
{

}/*
* stm32f446xx_gpio_driver.c
*
*  Created on: Dec 9, 2023
*      Author: pc
*/


