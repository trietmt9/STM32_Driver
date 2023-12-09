/*
 * stm32f446xx.h
 *
 *  Created on: Dec 9, 2023
 *      Author: pc
 */

#ifndef INC_STM32F446XX_H_
#define INC_STM32F446XX_H_

#include <stdint.h>
/*
 * General macros
 */

#define ENABLE                          							1
#define DISABLE                         							0
#define SET																ENABLE
#define RESET                          								DISABLE
#define GPIO_PIN_SET                   						SET
#define GPIO_PIN_RESET                 					RESET
/*
 * Define base Address of SRAM and FLASH memories
 */

/* <! Read in datasheet Memory map section to find SRAM base address>*/
#define SRAM1_BASE_ADDRESS              			0x20000000UL
#define SRAM2_BASE_ADDRESS              			0x2001C000UL
/* <! Read in datasheet Embedded Flash memory interface section to find SRAM base address>*/
#define FLASH_BASE_ADDRESS              			0x08000000UL
#define ROM                             								0x1FFF0000UL
#define SRAM                            								SRAM1_BASE_ADDRESS /* Use this macro as main SRAM*/

/*
 * Define base Address of AHBx and APBx Bus
 */

/* !<Read in datasheet STM32F446xx register boundary addresses section>*/
#define PERIPHERAL_BASE                 				0x40000000UL
#define APB1_PERIPHERAL_BASE            		PERIPHERAL_BASE
#define APB2_PERIPHERAL_BASE            		0x40010000UL
#define AHB1_PERIPHERAL_BASE            		0x40020000UL
#define AHB2_PERIPHERAL_BASE           		0x50000000UL

/*
 * Define base address peripherals connected to AHB1 bus
 */

#define GPIOA_BASE_ADDRESS              			(AHB1_PERIPHERAL_BASE + 0x0000UL)
#define GPIOB_BASE_ADDRESS              			(AHB1_PERIPHERAL_BASE + 0x0400UL)
#define GPIOC_BASE_ADDRESS              			(AHB1_PERIPHERAL_BASE + 0x0800UL)
#define GPIOD_BASE_ADDRESS              			(AHB1_PERIPHERAL_BASE + 0x0C00UL)
#define GPIOE_BASE_ADDRESS              			(AHB1_PERIPHERAL_BASE + 0x1000UL)
#define GPIOF_BASE_ADDRESS              			(AHB1_PERIPHERAL_BASE + 0x1400UL)
#define GPIOG_BASE_ADDRESS              			(AHB1_PERIPHERAL_BASE + 0x1800UL)
#define GPIOH_BASE_ADDRESS              			(AHB1_PERIPHERAL_BASE + 0x1C00UL)
#define RCC_BASE_ADDRESS                				(AHB1_PERIPHERAL_BASE + 0x3800UL)
/*
 * Define base address peripherals connected to APB1 bus
 */

#define I2C1_BASE_ADDRESS               				(APB1_PERIPHERAL_BASE + 0x5400UL)
#define I2C2_BASE_ADDRESS               				(APB1_PERIPHERAL_BASE + 0x5800UL)
#define I2C3_BASE_ADDRESS               				(APB1_PERIPHERAL_BASE + 0x5C00UL)
#define USART2_BASE_ADDRESS             			(APB1_PERIPHERAL_BASE + 0x4400UL)
#define USART3_BASE_ADDRESS             			(APB1_PERIPHERAL_BASE + 0x4800UL)
#define UART4_BASE_ADDRESS              			(APB1_PERIPHERAL_BASE + 0x4C00UL)
#define UART5_BASE_ADDRESS              			(APB1_PERIPHERAL_BASE + 0x5000UL)
#define SPI2_BASE_ADDRESS              				(APB1_PERIPHERAL_BASE + 0x3800UL)
#define SPI3_BASE_ADDRESS               				(APB1_PERIPHERAL_BASE + 0x3C00UL)

/*
 * Define base address peripherals connected to APB2 bus
 */

#define EXTI_BASE_ADDRESS               				(APB2_PERIPHERAL_BASE + 0x3C00UL)
#define SPI1_BASE_ADDRESS               				(APB2_PERIPHERAL_BASE + 0x3000UL)
#define SPI4_BASE_ADDRESS               				(APB2_PERIPHERAL_BASE + 0x3400UL)
#define USART1_BASE_ADDRESS             			(APB2_PERIPHERAL_BASE + 0x1000UL)
#define USART6_BASE_ADDRESS            		 	(APB2_PERIPHERAL_BASE + 0x1400UL)
#define SYSCFG_BASE_ADDRESS             		(APB2_PERIPHERAL_BASE + 0x3800UL)


/*
 * Define peripheral register structure for GPIO
 * Read GPIO register map and reset values in the datasheet
 */

typedef struct
{
    volatile uint32_t MODER;                            	/* Address offset: 0x00*/
    volatile uint32_t OTYPER;                           	/* Address offset: 0x04*/
    volatile uint32_t OSPEEDR;                          	/* Address offset: 0x08*/
    volatile uint32_t PUPDR;                            		/* Address offset: 0x0C*/
    volatile uint32_t IDR;                              			/* Address offset: 0x10*/
    volatile uint32_t ODR;                              		/* Address offset: 0x14*/
    volatile uint32_t BSRRL;                            		/* Address offset: 0x18*/
    volatile uint32_t BSRRH;                            		/* Address offset: 0x1A*/
    volatile uint32_t LCKR;                             		/* Address offset: 0x1C*/
    volatile uint32_t AFR[2];                           		/* Address offset: 0x20-0X24*/

}GPIO_RegDef_t;

/*
 * Define peripheral register structure for RCC
 * Read RCC register map and reset values in the datasheet
 * This will sorted in order as Address Offset
 */
typedef struct
{
    volatile uint32_t CR;
    volatile uint32_t PLLCFGR;
    volatile uint32_t CIR;
    volatile uint32_t AHB1RSTR;
    volatile uint32_t AHB2RSTR;
    volatile uint32_t AHB3RSTR;
    uint32_t Reserved0;
    volatile uint32_t APB1RSTR;
    volatile uint32_t APB2RSTR;
    uint32_t Reserved1;
    uint32_t Reserved2;
    volatile uint32_t AHB1ENR;
    volatile uint32_t AHB2ENR;
    volatile uint32_t AHB3ENR;
    uint32_t Reserved3;
    volatile uint32_t APB1ENR;
    volatile uint32_t APB2ENR;
    uint32_t Reserved4;
    uint32_t Reserved5;
    volatile uint32_t AHB1LPENR;
    volatile uint32_t AHB2LPENR;
    volatile uint32_t AHB3LPENR;
    uint32_t Reserved6;
    volatile uint32_t APB1LPENR;
    volatile uint32_t APB2LPENR;
    uint32_t Reserved7;
    uint32_t Reserved8;
    volatile uint32_t BDCR;
    volatile uint32_t CSR;
    uint32_t Reserved9;
    uint32_t Reserved10;
    volatile uint32_t SSCGR;
    volatile uint32_t PLL2SCFGR;
    volatile uint32_t PLLSAICFGR;
    volatile uint32_t DCKCFGR;
    volatile uint32_t CKGATENR;
    volatile uint32_t DCKCFGR2;

}RCC_RegDef_t;

/*
 * Peripheral definitions
 */

#define GPIOA                           					((GPIO_RegDef_t*)GPIOA_BASE_ADDRESS)
#define GPIOB                           					((GPIO_RegDef_t*)GPIOB_BASE_ADDRESS)
#define GPIOC                           					((GPIO_RegDef_t*)GPIOC_BASE_ADDRESS)
#define GPIOD                           					((GPIO_RegDef_t*)GPIOD_BASE_ADDRESS)
#define GPIOE                           					((GPIO_RegDef_t*)GPIOE_BASE_ADDRESS)
#define GPIOF                           					((GPIO_RegDef_t*)GPIOF_BASE_ADDRESS)
#define GPIOG                           					((GPIO_RegDef_t*)GPIOG_BASE_ADDRESS)
#define GPIOH                           					((GPIO_RegDef_t*)GPIOH_BASE_ADDRESS)
#define RCC                             	 					((RCC_RegDef_t*)RCC_BASE_ADDRESS)

/*
 * CLock enable macros for GPIOx peripheral
 */

#define GPIOA_PCLK_EN()                 		(RCC->AHB1ENR |= (1<<0))
#define GPIOB_PCLK_EN()                 		(RCC->AHB1ENR |= (1<<1))
#define GPIOC_PCLK_EN()                 		(RCC->AHB1ENR |= (1<<2))
#define GPIOD_PCLK_EN()                 		(RCC->AHB1ENR |= (1<<3))
#define GPIOE_PCLK_EN()                 		(RCC->AHB1ENR |= (1<<4))
#define GPIOF_PCLK_EN()                 		(RCC->AHB1ENR |= (1<<5))
#define GPIOG_PCLK_EN()                 		(RCC->AHB1ENR |= (1<<6))
#define GPIOH_PCLK_EN()                 		(RCC->AHB1ENR |= (1<<7))

/*
 * CLock enable macros for I2Cx peripheral
 */

#define I2C1_PCLK_EN()                  			(RCC->APB1ENR |= (1<<21))
#define I2C2_PCLK_EN()                  			(RCC->APB1ENR |= (1<<22))
#define I2C3_PCLK_EN()                  			(RCC->APB1ENR |= (1<<23))

/*
 * CLock enable macros for SPIx peripheral
 */

#define SPI1_PCLK_EN()                  			(RCC->APB2ENR |= (1<<12))
#define SPI2_PCLK_EN()                  			(RCC->APB1ENR |= (1<<14))
#define SPI3_PCLK_EN()                  			(RCC->APB1ENR |= (1<<15))
#define SPI4_PCLK_EN()                  			(RCC->APB2ENR |= (1<<13))

/*
 * CLock enable macros for USARTx peripheral
 */

#define USART1_PCLK_EN()                	(RCC->APB2ENR |= (1<<4))
#define USART2_PCLK_EN()                	(RCC->APB1ENR |= (1<<17))
#define USART3_PCLK_EN()               		(RCC->APB1ENR |= (1<<18))
#define UART4_PCLK_EN()                 		(RCC->APB2ENR |= (1<<19))
#define UART5_PCLK_EN()                 		(RCC->APB1ENR |= (1<<20))
#define USART6_PCLK_EN()                	(RCC->APB2ENR |= (1<<5))

/*
 * CLock enable macros for SYSCFG peripheral
 */

#define SYSCFG_PCLK_EN()                	(RCC->APB2ENR|= (1<<14))


/*
 * CLock disable macros for GPIOx peripheral
 */
#define GPIOA_PCLK_DI()                	 	(RCC->AHB1ENR &=~ (1<<0))
#define GPIOB_PCLK_DI()                 		(RCC->AHB1ENR &=~ (1<<1))
#define GPIOC_PCLK_DI()                 		(RCC->AHB1ENR &=~ (1<<2))
#define GPIOD_PCLK_DI()                 		(RCC->AHB1ENR &=~ (1<<3))
#define GPIOE_PCLK_DI()                 		(RCC->AHB1ENR &=~ (1<<4))
#define GPIOF_PCLK_DI()                 		(RCC->AHB1ENR &=~ (1<<5))
#define GPIOG_PCLK_DI()                 		(RCC->AHB1ENR &=~ (1<<6))
#define GPIOH_PCLK_DI()                 		(RCC->AHB1ENR &=~ (1<<7))

/*
 * CLock disable macros for I2Cx peripheral
 */

#define I2C1_PCLK_DI()                  			(RCC->APB1ENR &=~ (1<<21))
#define I2C2_PCLK_DI()                  			(RCC->APB1ENR &=~ (1<<22))
#define I2C3_PCLK_DI()                  			(RCC->APB1ENR &=~ (1<<23))

/*
 * CLock disable macros for SPIx peripheral
 */

#define SPI1_PCLK_DI()                  			(RCC->APB2ENR &=~ (1<<12))
#define SPI2_PCLK_DI()                  			(RCC->APB1ENR &=~ (1<<14))
#define SPI3_PCLK_DI()                  			(RCC->APB1ENR &=~ (1<<15))
#define SPI4_PCLK_DI()                  			(RCC->APB2ENR &=~ (1<<13))

/*
 * CLock disable macros for USARTx peripheral
 */

#define USART1_PCLK_DI()                		(RCC->APB2ENR &=~ (1<<4))
#define USART2_PCLK_DI()                		(RCC->APB1ENR &=~ (1<<17))
#define USART3_PCLK_DI()                		(RCC->APB1ENR &=~ (1<<18))
#define UART4_PCLK_DI()                 		(RCC->APB2ENR &=~ (1<<19))
#define UART5_PCLK_DI()                 		(RCC->APB1ENR &=~ (1<<20))
#define USART6_PCLK_DI()               		(RCC->APB2ENR &=~ (1<<5))

/*
 * CLock disable macros for SYSCFG peripheral
 */

#define SYSCFG_PCLK_DI()                	(RCC->APB2ENR&=~ (1<<14))

#endif /* INC_STM32F446XX_H_ */