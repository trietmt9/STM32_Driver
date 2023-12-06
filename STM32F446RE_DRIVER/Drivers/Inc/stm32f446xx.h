#ifdef INC_STM32F446XX_H_
#define INC_STM32F446XX_H_
#include <stdint.h>

/* 
 *Define base Address of SRAM and FLASH memories
 */

/* <! Read in datasheet Memory map section to find SRAM base address>*/
#define SRAM1_BASE_ADDRESS              0x20000000UL 
#define SRAM2_BASE_ADDRESS              0x2001C000UL
/* <! Read in datasheet Embedded Flash memory interface section to find SRAM base address>*/   
#define FLASH_BASE_ADDRESS              0x08000000UL
#define ROM                             0x1FFF0000UL
#define SRAM                            SRAM1_BASE_ADDRESS /* Use this macro as main SRAM*/

/* 
 *Define base Address of AHBx and APBx Bus
 */

/* !<Read in datasheet STM32F446xx register boundary addresses section>*/ 
#define PERIPHERAL_BASE                 0x40000000UL
#define APB1_PERIPHERAL_BASE            PERIPHERAL_BASE
#define APB2_PERIPHERAL_BASE            0x40010000UL
#define AHB1_PERIPHERAL_BASE            0x40020000UL
#define AHB2_PERIPHERAL_BASE            0x50000000UL

/* 
 * Define base address peripherals connected to AHB1 bus  
 */

#define GPIOA_BASE_ADDRESS              (AHB1_PERIPHERAL_BASE + 0x0000UL)
#define GPIOB_BASE_ADDRESS              (AHB1_PERIPHERAL_BASE + 0x0400UL)
#define GPIOC_BASE_ADDRESS              (AHB1_PERIPHERAL_BASE + 0x0800UL)
#define GPIOD_BASE_ADDRESS              (AHB1_PERIPHERAL_BASE + 0x0C00UL)
#define GPIOE_BASE_ADDRESS              (AHB1_PERIPHERAL_BASE + 0x1000UL)
#define GPIOF_BASE_ADDRESS              (AHB1_PERIPHERAL_BASE + 0x1400UL)
#define GPIOG_BASE_ADDRESS              (AHB1_PERIPHERAL_BASE + 0x1800UL)
#define GPIOH_BASE_ADDRESS              (AHB1_PERIPHERAL_BASE + 0x1C00UL)

/* 
 * Define base address peripherals connected to APB1 bus  
 */

#define I2C1_BASE_ADDRESS               (APB1_PERIPHERAL_BASE + 0x5400UL)
#define I2C2_BASE_ADDRESS               (APB1_PERIPHERAL_BASE + 0x5800UL)
#define I2C3_BASE_ADDRESS               (APB1_PERIPHERAL_BASE + 0x5C00UL)
#define USART2_BASE_ADDRESS             (APB1_PERIPHERAL_BASE + 0x4400UL)
#define USART3_BASE_ADDRESS             (APB1_PERIPHERAL_BASE + 0x4800UL)
#define USART2_BASE_ADDRESS             (APB1_PERIPHERAL_BASE + 0x4400UL)
#define USART3_BASE_ADDRESS             (APB1_PERIPHERAL_BASE + 0x4800UL)
#define UART4_BASE_ADDRESS              (APB1_PERIPHERAL_BASE + 0x4C00UL)
#define UART5_BASE_ADDRESS              (APB1_PERIPHERAL_BASE + 0x5000UL)
#define SPI2_BASE_ADDRESS               (APB1_PERIPHERAL_BASE + 0x3800UL)
#define SPI3_BASE_ADDRESS               (APB1_PERIPHERAL_BASE + 0x3C00UL)

/* 
 * Define base address peripherals connected to APB2 bus  
 */

#define EXTI_BASE_ADDRESS               (APB2_PERIPHERAL_BASE + 0x3C00UL)
#define SPI1_BASE_ADDRESS               (APB2_PERIPHERAL_BASE + 0x3000UL)
#define USART1_BASE_ADDRESS             (APB2_PERIPHERAL_BASE + 0x1000UL)
#define USART6_BASE_ADDRESS             (APB2_PERIPHERAL_BASE + 0x1400UL)
#define SYSCFG_BASE_ADDRESS             (APB2_PERIPHERAL_BASE + 0x3800UL)


/* 
 * Define peripheral register structure for GPIO  
 */

typedef struct 
{
    volatile uint32_t MODER;                            /* Address offset: 0x00*/
    volatile uint32_t OTYPER;                           /* Address offset: 0x04*/
    volatile uint32_t OSPEEDR;                          /* Address offset: 0x08*/
    volatile uint32_t PUPDR;                            /* Address offset: 0x0C*/
    volatile uint32_t IDR;                              /* Address offset: 0x10*/
    volatile uint32_t ODR;                              /* Address offset: 0x14*/
    volatile uint32_t BSRRL;                            /* Address offset: 0x18*/
    volatile uint32_t BSRRH;                            /* Address offset: 0x1A*/
    volatile uint32_t LCKR;                             /* Address offset: 0x1C*/
    volatile uint32_t AFR[2];                           /* Address offset: 0x20-0X24*/

}GPIO_RegDef_t;

/* 
 * Peripheral definitions
 */

#define GPIOA                           ((GPIO_RegDef_t*)GPIOA_BASE_ADDRESS)
#define GPIOB                           ((GPIO_RegDef_t*)GPIOB_BASE_ADDRESS)
#define GPIOC                           ((GPIO_RegDef_t*)GPIOC_BASE_ADDRESS)
#define GPIOD                           ((GPIO_RegDef_t*)GPIOD_BASE_ADDRESS)
#define GPIOE                           ((GPIO_RegDef_t*)GPIOE_BASE_ADDRESS)
#define GPIOF                           ((GPIO_RegDef_t*)GPIOF_BASE_ADDRESS)
#define GPIOG                           ((GPIO_RegDef_t*)GPIOG_BASE_ADDRESS)
#define GPIOH                           ((GPIO_RegDef_t*)GPIOH_BASE_ADDRESS)


#endif