/*
 * stm32f446xx_spi_driver.h
 *
 *  Created on: Dec 26, 2023
 *      Author: pc
 */

#ifndef INC_STM32F446XX_SPI_DRIVER_H_
#define INC_STM32F446XX_SPI_DRIVER_H_

#include <stm32f446xx.h>

// SPI Status macros
#define FLAG_RESET                          0
#define FLAG_SET                            1

// SPI status register macros
#define SPI_RXNE_FLAG                       (1 << 0)
#define SPI_TXE_FLAG                        (1 << 1)
#define SPI_BUSY_FLAG                       (1 << 7)

typedef struct 
{
    uint8_t SPI_DeviceMode;  // Choose master or slave mode for device
    uint8_t SPI_BusConfig;   // Configure half-duplex, full-duplex and simplex communications
    uint8_t SPI_SClkSpeed;   // Configure serial clock speed
    uint8_t SPI_DFF;         // Configure Data frame format      
    uint8_t SPI_CPOL;        // Configure Clock Polarity 
    uint8_t SPI_CPHA;        // Configure Clock Phase
    uint8_t SPI_SSM;         // Configure slave select management
}SPI_Config_t;


// SPI enumerated device mode
typedef enum
{
    SLAVE = 0,
    MASTER   
}Device_Mode;

// SPI enumerated bus configuration
typedef enum
{
    FullDuplex = 0,
    HalfDuplex,
    Simplex_Rx
}BusConfig;

// SPI enumerated Clock Speed
typedef enum
{
    DIV_2 = 0,
    DIV_4,
    DIV8,
    DIV_16,
    DIV_32,
    DIV_64,
    DIV_128,
    DIV_256
}ClockSpeed;

// SPI enumerated data frame format 
typedef enum 
{
    DFF_8BITS = 0,
    DFF_16BITS
}DFF;

// SPI enumerated Clock Polarity 
typedef enum 
{
    CPOL_L = 0,
    CPOL_H
}CPOL;

// SPI enumerated Clock Phase
typedef enum 
{   
    CPHA_L = 0,
    CPHA_H
}CPHA;

// SPI enumerated Slave Select Management
typedef enum 
{   
    SSM_DI = 0,
    SSM_EN
}SSM;   
/*************************************************************************
 *                  APIs for controlling SPI driver
 *           Check function definition for more information
**************************************************************************/

/*
 * Peripheral clock set up
 */
void DRV_SPI_Pclkcontrol(SPI_TypeDef_t* pSPIx, EnOrDi_State EnOrDi);

/*
 * Init, Deinit and Enable 
 */
void DRV_SPI_Init(SPI_TypeDef_t* pSPIx, SPI_Config_t* hspix);
void DRV_SPI_DeInit(SPI_TypeDef_t* pSPIx);
void DRV_SPI_PeripheralControl(SPI_TypeDef_t* pSPIx, EnOrDi_State EnOrDi);
void DRV_SPI_SSI(SPI_TypeDef_t* pSPIx, EnOrDi_State EnOrDi);
/*
 * Send and Receive 
 */
void DRV_SPI_Tx(SPI_TypeDef_t* hspix, uint8_t* pTx_Buffer, uint32_t Buffer_Size);
void DRV_SPI_Rx(SPI_TypeDef_t* hspix, uint8_t* pRx_Buffer, uint32_t Buffer_Size);
/*
 * IQR and ISR 
 */
void DRV_SPI_IRQConfig(uint8_t IRQNumber, EnOrDi_State EnOrDi);
void DRV_SPI_IRQPriorityCFG(uint8_t IRQNumber, uint8_t IRQPriority);
void DRV_SPI_IRQHandling(SPI_TypeDef_t* pSPI, SPI_Config_t* pSPICofig);

/*
 * SPI get flag status 
 */
uint8_t SPI_FlagStatus(SPI_TypeDef_t* pSPIx, uint32_t Flag);
#endif /* INC_STM32F446XX_SPI_DRIVER_H_ */
