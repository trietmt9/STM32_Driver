/*
 * stm32f4xx_gpio_driver.h
 *
 *  Created on: Dec 21, 2023
 *      Author: trietmt9
 */

#ifndef INC_STM32F4XX_GPIO_DRIVER_H_
#define INC_STM32F4XX_GPIO_DRIVER_H_
#include <stm32f4xx.h>

typedef struct 
{
    uint8_t PinNumber;          //* Pin Number
    uint8_t PinMode;            //* Pin Mode
    uint8_t PinSpeed;           //* Pin output speed
    uint8_t PinPUPDCtrl;        //* Pin Pull up/down configuration
    uint8_t PinOPType;          //* Pin output type
    uint8_t PinAltFunction;     //* Pin alternative function 
}GPIO_PinConfig_t;

// Definition enumerated of GPIO mode
typedef enum
{
    GPIO_INPUT = 0,
    GPIO_OUTPUT,
    GPIO_ALTERNATE,
    GPIO_ANALOG 

}GPIO_MODE;


// Definition enumerated of GPIO output type
typedef enum
{
    PushPull = 0,
    OpenDrain,   
}GPIO_OPTYPE;

// Definition enumerated of GPIO SPEED
typedef enum
{
    LOW = 0,
    MEDIUM,
    FAST,
    HIGH 

}GPIO_SPEED;

// Definition enumerated of GPIO mode
typedef enum
{
    NoPUPD = 0,
    PullUp,
    PullDown,
    Reversed 
    
}GPIO_PUPD;


/* Define GPIO pin number */

#define GPIO_PIN_0                          0
#define GPIO_PIN_1                          1 
#define GPIO_PIN_2                          2
#define GPIO_PIN_3                          3  
#define GPIO_PIN_4                          4
#define GPIO_PIN_5                          5                           
#define GPIO_PIN_6                          6
#define GPIO_PIN_7                          7  
#define GPIO_PIN_8                          8
#define GPIO_PIN_9                          9  
#define GPIO_PIN_10                         10
#define GPIO_PIN_11                         11  
#define GPIO_PIN_12                         12
#define GPIO_PIN_13                         13 
#define GPIO_PIN_14                         14
#define GPIO_PIN_15                         15


/*************************************************************************
 *                  APIs for controlling GPIO driver
 *           Check function definition for more information
**************************************************************************/

/*
 * Peripheral clock setup
 */
void DRV_GPIO_Init(GPIO_TypeDef_t* pGPIOx, GPIO_PinConfig_t* pGPIOPinCofig);
void DRV_GPIO_DeInit(GPIO_TypeDef_t* pGPIOx);
void DRV_GPIO_Pclkcontrol(GPIO_TypeDef_t* pGPIOx, EnOrDi_State EnOrDi);

/*
 * Read and Write Data
 */
uint8_t  DRV_GPIO_ReadPin(GPIO_TypeDef_t* pGPIOx, uint8_t PinNumber);
uint16_t DRV_GPIO_ReadPort(GPIO_TypeDef_t* pGPIOx);
void DRV_GPIO_WritePin(GPIO_TypeDef_t* pGPIOx, uint8_t PinNumber ,Pin_State Value);
void DRV_GPIO_WritePort(GPIO_TypeDef_t* pGPIOx, Pin_State Value);
void DRV_GPIO_TogglePin(GPIO_TypeDef_t* pGPIOx, uint8_t PinNumber );

/*
 * IRQ configure and ISR handling
 */
void DRV_GPIO_IRQConfig(uint8_t IRQNumber,uint8_t IRQPriority, EnOrDi_State EnOrDi);
void DRV_GPIO_IRQHandling(void);

#endif /* INC_STM32F4XX_GPIO_DRIVER_H_ */
