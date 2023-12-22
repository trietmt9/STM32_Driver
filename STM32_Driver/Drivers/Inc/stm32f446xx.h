/*
 * stm32f4xx.h
 *
 *  Created on: Dec 21, 2023
 *      Author: trietmt
 */

#ifndef INC_STM32F446XX_H_
#define INC_STM32F446XX_H_
#include <stdint.h>

//define volatile type for each peripheral register 

#define __IO                                volatile  // read/write type
/*
 * Macros for Base address of SRAM and FLASH memories of MCU
 * User can check Table 3. Memory mapping vs. Boot mode/physical in Reference Manual 
 */


#define FLASH_BASEADDR                      0x08000000U
#define SRAM_BASEADDR                       0x20000000U
#define SRAM2_BASEADDR                      0x2001C000U
#define ROM_BASEADDR                        0x1FFF0000U

/*
 * Macros for peripheral base address 
 * User can check Memory map and register boundary addresses section in Reference Manual 
 */

#define PERIPHERAL_BASEADDR                 0x40000000U
#define APB1_PERIPHERAL_BASEADDR            PERIPHERAL_BASEADDR
#define APB2_PERIPHERAL_BASEADDR            0x40010000U
#define AHB1_PERIPHERAL_BASEADDR            0x40020000U
#define AHB2_PERIPHERAL_BASEADDR            0x50000000U
#define AHB3_PERIPHERAL_BASEADDR            0xA0001000U

/*
 * Macros for peripheral connect to AHB1 bus  
 */

// *< Macros for GPIO base address > 
#define GPIOA_BASE                          (AHB1_PERIPHERAL_BASEADDR + 0x0000U)
#define GPIOB_BASE                          (AHB1_PERIPHERAL_BASEADDR + 0x0400U)
#define GPIOC_BASE                          (AHB1_PERIPHERAL_BASEADDR + 0x0800U)
#define GPIOD_BASE                          (AHB1_PERIPHERAL_BASEADDR + 0x0C00U)
#define GPIOE_BASE                          (AHB1_PERIPHERAL_BASEADDR + 0x1000U)
#define GPIOF_BASE                          (AHB1_PERIPHERAL_BASEADDR + 0x1400U)
#define GPIOG_BASE                          (AHB1_PERIPHERAL_BASEADDR + 0x1800U)
#define GPIOH_BASE                          (AHB1_PERIPHERAL_BASEADDR + 0x1C00U)
#define RCC_BASE                            (AHB1_PERIPHERAL_BASEADDR + 0x3800U)   
/*
 * Macros for peripheral connect to APB1 bus 
 */
// *< Macros for I2Cx base address >
#define I2C1_BASE                           (APB1_PERIPHERAL_BASEADDR + 0x5400U)
#define I2C2_BASE                           (APB1_PERIPHERAL_BASEADDR + 0x5800U)
#define I2C3_BASE                           (APB1_PERIPHERAL_BASEADDR + 0x5C00U)

// *< Macros for UARTx/USARTx base address >
#define USART2_BASE                         (APB1_PERIPHERAL_BASEADDR + 0x4400U)
#define USART3_BASE                         (APB1_PERIPHERAL_BASEADDR + 0x4800U)
#define UART4_BASE                          (APB1_PERIPHERAL_BASEADDR + 0x4C00U)
#define UART5_BASE                          (APB1_PERIPHERAL_BASEADDR + 0x5000U)

// *< Macros for SPIx base address >
#define SPI2_BASE                           (APB1_PERIPHERAL_BASEADDR + 0x3800U)
#define SPI3_BASE                           (APB1_PERIPHERAL_BASEADDR + 0x3C00U)

/*
 * Macros for peripheral connect to APB2 bus 
 */

// *< Macros for USARTx base address >
#define USART6_BASE                         (APB2_PERIPHERAL_BASEADDR + 0x1400U)
#define USART1_BASE                         (APB2_PERIPHERAL_BASEADDR + 0x1000U)

// *< Macros for SPIx base address >
#define SPI4_BASE                           (APB2_PERIPHERAL_BASEADDR + 0x3400U)
#define SPI1_BASE                           (APB2_PERIPHERAL_BASEADDR + 0x3000U)

// *< Macros for EXTI and SYSCFG base address >
#define EXTI_BASE                           (APB2_PERIPHERAL_BASEADDR + 0x3C00U)
#define SYSCFG_BASE                         (APB2_PERIPHERAL_BASEADDR + 0x3800U)
/************************** Peripheral Register definition structure **************************/
/*
 * Check device's reference manual and define a struct in order 
 */

/**GPIO configuration definition structure**/
typedef struct
{
    __IO uint32_t MODER;            //* Mode register                                offset: 0x00
    __IO uint32_t OTYPER;           //* Output type register                         offset: 0x04
    __IO uint32_t OSPEEDER;         //* Output speed register                        offset: 0x08
    __IO uint32_t PUPDR;            //* Pull up/down configuration register          offset: 0x0C   
    __IO uint32_t IDR;              //* Input data register                          offset: 0x10
    __IO uint32_t ODR;              //* Output data register                         offset: 0x14
    __IO uint32_t BSRR;             //* Bit set/reset register                       offset: 0x18
    __IO uint32_t LCKR;             //* Lock configuration register                  offset: 0x1C
    __IO uint32_t AFR[2];           //* Alternative function register                offset: 0x20 - 0x24

}GPIO_TypeDef_t;

/**RCC configuration definition structure**/
typedef struct 
{
    __IO uint32_t CR;              //* Control register                             offset: 0x00
    __IO uint32_t PLLCFG;          //* PLL configuration register                   offset: 0x04
    __IO uint32_t CFGR;            //* Clock configure register                     offset: 0x08
    __IO uint32_t CIR;             //* Clock interrupts register                    offset: 0x0C
    __IO uint32_t AHB1RSTR;        //* AHB1 bus reset register                      offset: 0x10
    __IO uint32_t AHB2RSTR;        //* AHB2 bus reset register                      offset: 0x14
    __IO uint32_t AHB3RSTR;        //* AHB3 bus reset register                      offset: 0x18
    uint32_t Reserved0;             //* Reserved bit                                 offset: 0x1C
    __IO uint32_t APB1RSTR;        //* APB1 bus reset register                      offset: 0x20
    __IO uint32_t APB2RSTR;        //* APB2 bus reset register                      offset: 0x24
    uint32_t Reserved1[2];          //* Reserved bit                                 offset: 0x28 - 0x2C
    __IO uint32_t AHB1ENR;         //* AHB1 bus enable register                     offset: 0x30
    __IO uint32_t AHB2ENR;         //* AHB2 bus enable register                     offset: 0x34
    __IO uint32_t AHB3ENR;         //* AHB3 bus enable register                     offset: 0x38
    uint32_t Reserved2;             //* Reserved bit                                 offset: 0x3C
    __IO uint32_t APB1ENR;         //* APB1 bus enable register                     offset: 0x40
    __IO uint32_t APB2ENR;         //* APB2 bus enable register                     offset: 0x44
    uint32_t Reserved3[2];          //* Reserved bit                                 offset: 0x48 - 0x4C
    __IO uint32_t AHB1LPENR;       //* AHB1 bus low power mode register             offset: 0x50
    __IO uint32_t AHB2LPENR;       //* AHB2 bus low power mode register             offset: 0x54
    __IO uint32_t AHB3LPENR;       //* AHB3 bus low power mode register             offset: 0x58
    uint32_t Reserved4;             //* Reserved bit                                 offset: 0x5C
    __IO uint32_t APB1LPENR;       //* APB1 bus low power mode register             offset: 0x60
    __IO uint32_t APB2LPENR;       //* APB2 bus low power mode register             offset: 0x64
    uint32_t Reserved5[2];          //* Reserved bit                                 offset: 0x68 - 0x6C
    __IO uint32_t BDCR;            //* Backup domain control register               offset: 0x70
    __IO uint32_t CSR;             //* Clock control and status register            offset: 0x74
    uint32_t Reserved6[2];          //* Reserved bit                                 offset: 0x78 - 0x7C
    __IO uint32_t SSCGR;           //* Spread spectrum clock generation register    offset: 0x80
    __IO uint32_t PLLI2SCFGR;      //* PLLI2S configuration register                offset: 0x84
    __IO uint32_t PLLSAICFGR;      //* PLL configuration register                   offset: 0x88
    __IO uint32_t DCKCFGR;         //* Dedicated clock configuration register       offset: 0x8C
    __IO uint32_t CKGATENR;        //* Clocks gated enable register                 offset: 0x90
    __IO uint32_t DCKCFGR2;        //* Dedicated clock configuration register 2     offset: 0x94
}RCC_TypeDef_t;

typedef enum 
{
    DISABLE = 0, 
    ENABLE
}EnOrDi_State;

typedef enum
{
    RESET_PIN = 0, RESET = RESET_PIN,
    SET_PIN, SET = SET_PIN
}Pin_State;
/*
 * Peripheral definitions 
 */

#define GPIOA                               ((GPIO_TypeDef_t*)GPIOA_BASE)
#define GPIOB                               ((GPIO_TypeDef_t*)GPIOB_BASE)
#define GPIOC                               ((GPIO_TypeDef_t*)GPIOC_BASE)
#define GPIOD                               ((GPIO_TypeDef_t*)GPIOD_BASE)
#define GPIOE                               ((GPIO_TypeDef_t*)GPIOE_BASE)
#define GPIOF                               ((GPIO_TypeDef_t*)GPIOF_BASE)
#define GPIOG                               ((GPIO_TypeDef_t*)GPIOG_BASE)
#define GPIOH                               ((GPIO_TypeDef_t*)GPIOH_BASE)
#define RCC                                 ((RCC_TypeDef_t*)RCC_BASE)


/*
 * Enable GPIOx peripherals clock macros 
 */
#define GPIOA_PCLK_EN()                     (RCC->AHB1ENR |= (1<<0))
#define GPIOB_PCLK_EN()                     (RCC->AHB1ENR |= (1<<1))
#define GPIOC_PCLK_EN()                     (RCC->AHB1ENR |= (1<<2))
#define GPIOD_PCLK_EN()                     (RCC->AHB1ENR |= (1<<3))
#define GPIOE_PCLK_EN()                     (RCC->AHB1ENR |= (1<<4))
#define GPIOF_PCLK_EN()                     (RCC->AHB1ENR |= (1<<5))
#define GPIOG_PCLK_EN()                     (RCC->AHB1ENR |= (1<<6))
#define GPIOH_PCLK_EN()                     (RCC->AHB1ENR |= (1<<7))

/*
 * Enable I2Cx peripherals clock macros 
 */
#define I2C1_PCLK_EN()                      (RCC->APB1ENR |= (1<<21))
#define I2C2_PCLK_EN()                      (RCC->APB1ENR |= (1<<22))
#define I2C3_PCLK_EN()                      (RCC->APB1ENR |= (1<<23))

/*
 * Enable SPIx peripherals clock macros 
 */
#define SPI1_PCLK_EN()                      (RCC->APB2ENR |= (1<<12))
#define SPI2_PCLK_EN()                      (RCC->APB1ENR |= (1<<14))
#define SPI3_PCLK_EN()                      (RCC->APB1ENR |= (1<<15))
#define SPI4_PCLK_EN()                      (RCC->APB2ENR |= (1<<13))

/*
 * Enable UARTx/USARTx peripherals clock macros 
 */
#define USART1_PCLK_EN()                    (RCC->APB2ENR |= (1<<4))
#define USART2_PCLK_EN()                    (RCC->APB1ENR |= (1<<17))
#define USART3_PCLK_EN()                    (RCC->APB1ENR |= (1<<18))
#define UART4_PCLK_EN()                     (RCC->APB1ENR |= (1<<19))
#define UART5_PCLK_EN()                     (RCC->APB1ENR |= (1<<20))
#define USART6_PCLK_EN()                    (RCC->APB2ENR |= (1<<5))   


/*
 * Disable GPIOx peripherals clock macros 
 */
#define GPIOA_PCLK_DI()                     (RCC->AHB1ENR &=~ (1<<0))
#define GPIOB_PCLK_DI()                     (RCC->AHB1ENR &=~ (1<<1))
#define GPIOC_PCLK_DI()                     (RCC->AHB1ENR &=~ (1<<2))
#define GPIOD_PCLK_DI()                     (RCC->AHB1ENR &=~ (1<<3))
#define GPIOE_PCLK_DI()                     (RCC->AHB1ENR &=~ (1<<4))
#define GPIOF_PCLK_DI()                     (RCC->AHB1ENR &=~ (1<<5))
#define GPIOG_PCLK_DI()                     (RCC->AHB1ENR &=~ (1<<6))
#define GPIOH_PCLK_DI()                     (RCC->AHB1ENR &=~ (1<<7))

/*
 * Reset register GPIOx peripherals clock macros 
 */
#define GPIOA_REG_RESET()                     do{ (RCC->AHB1RSTR |=(1<<0)); (RCC->AHB1RSTR &= ~(1<<0)); }while(0)
#define GPIOB_REG_RESET()                     do{ (RCC->AHB1RSTR |=(1<<1)); (RCC->AHB1RSTR &= ~(1<<1)); }while(0)
#define GPIOC_REG_RESET()                     do{ (RCC->AHB1RSTR |=(1<<2)); (RCC->AHB1RSTR &= ~(1<<2)); }while(0)
#define GPIOD_REG_RESET()                     do{ (RCC->AHB1RSTR |=(1<<3)); (RCC->AHB1RSTR &= ~(1<<3)); }while(0)
#define GPIOE_REG_RESET()                     do{ (RCC->AHB1RSTR |=(1<<4)); (RCC->AHB1RSTR &= ~(1<<4)); }while(0)
#define GPIOF_REG_RESET()                     do{ (RCC->AHB1RSTR |=(1<<5)); (RCC->AHB1RSTR &= ~(1<<5)); }while(0)
#define GPIOG_REG_RESET()                     do{ (RCC->AHB1RSTR |=(1<<6)); (RCC->AHB1RSTR &= ~(1<<6)); }while(0)
#define GPIOH_REG_RESET()                     do{ (RCC->AHB1RSTR |=(1<<7)); (RCC->AHB1RSTR &= ~(1<<7)); }while(0)

#endif /* INC_STM32F4XX_H_ */
