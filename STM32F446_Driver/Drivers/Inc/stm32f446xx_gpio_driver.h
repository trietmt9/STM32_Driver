/*
 * stm32f446x_gpio_driver.h
 *
 *  Created on: Dec 9, 2023
 *      Author: pc
 */

#ifndef INC_STM32F446XX_GPIO_DRIVER_H_
#define INC_STM32F446XX_GPIO_DRIVER_H_
#include <stm32f446xx.h>

/*
 * Driver general Macros
 */

/*
 * @GPIO_MODE
 * GPIO modes
 */
#define GPIO_MODE_INPUT                     			0U
#define GPIO_MODE_OUTPUT                    		1U
#define GPIO_MODE_ALT                       				2U
#define GPIO_MODE_ANALOG                    		3U
#define GPIO_MODE_IT_FT                     			4U
#define GPIO_MODE_IT_RT                     			5U
#define GPIO_MODE_IT_RFT                    			6U

/*
 * @GPIO_OUTPUT_TYPE
 * GPIO output types
 */
#define GPIO_OUTPUT_TYPE_PP                 		0U
#define GPIO_OUTPUT_TYPE_OD                 	1U

/*
 * @GPIO_OUTPUT_SPEED
 * GPIO output speed
 */
#define GPIO_SPEED_LOW                      			0U
#define GPIO_SPEED_MEDIUM                   		1U
#define GPIO_SPEED_FAST                     				2U
#define GPIO_SPEED_HIGH                     			3U

/*
 * @GPIO_PUPD_CFG
 * GPIO pull up, pull down configuration
 */

#define GPIO_NO_PUPD                        				0U
#define GPIO_PULL_UP                        				1U
#define GPIO_PULL_DOWN                      			2U


/*
 * Handle structure of a GPIO pin
 */
typedef struct
{
    uint8_t GPIO_PinNumber;
    uint8_t GPIO_PinMode;  						/*!< Value from @GPIO_MODE >*/
    uint8_t GPIO_PinSpeed; 						/*!< Value from @GPIO_OUTPUT_SPEED >*/
    uint8_t GPIO_PuPd;     							/*!< Value from @GPIO_PUPD_CFG >*/
    uint8_t GPIO_PinOPType;						/*!< Value from @GPIO_OUTPUT_TYPE >*/
    uint8_t GPIO_PinAlt;   							/*!< Value from @GPIO_MODE >*/


}GPIO_PinConfig_t ;


/*
 * Handle structure of a GPIO pin
 */
typedef struct
{
    // pointer hold base address of the GPIO peripheral

    GPIO_RegDef_t *pGPIOx; 							/*!< This pointer hold the bas address of the GPIO port to which pin belong >*/
    GPIO_PinConfig_t  GPIO_PinCFG; 			/*!< This variable hold the pin configuration setting>*/

}GPIO_Handle_t;


/******************************************************************************************
 *                                  API supports by this driver
 *                             Check API in the function definitions
 ******************************************************************************************/

/*
 * GPIO Init and Deinit functions
 */
void GPIO_Init(GPIO_Handle_t* pGPIOHandle);
void GPIO_DeInit(GPIO_RegDef_t* pGPIOx);

/*
 * GPIO peripheral clock setup function
 */
void GPIO_PCLK_CTRL(GPIO_RegDef_t* pGPIOx, uint8_t EnOrDi);

/*
 * GPIO input and output control functions
 */
uint8_t GPIO_ReadPin(GPIO_RegDef_t* pGPIOx, uint8_t PinNumber);
uint16_t GPIO_ReadPort(GPIO_RegDef_t* pGPIOx);
void GPIO_WritePin(GPIO_RegDef_t* pGPIOx, uint8_t PinNumber, uint8_t Value);
void GPIO_WritePort(GPIO_RegDef_t* pGPIOx, uint16_t Value);
void GPIO_TogglePin(GPIO_RegDef_t* pGPIOx, uint8_t PinNumber);

/*
 * GPIO interrupt control functions
 */
void GPIO_IRQ_Config(uint8_t IRQNumber, uint8_t IRQPriority, uint8_t EnOrDi);
void GPIO_IRQ_Handling(uint8_t PinNumber);


#endif /* INC_STM32F446XX_GPIO_DRIVER_H_ */
