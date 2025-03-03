/*
 * stm32f446xx_spi_driver.h
 *
 *  Created on: Dec 26, 2023
 *      Author: pc
 */

#ifndef INC_STM32F446XX_SPI_DRIVER_H_
#define INC_STM32F446XX_SPI_DRIVER_H_

#include <stm32f446xx.h>
#include <stdint.h>
#include <stddef.h>
// SPI Status macros
#define FLAG_RESET                          0
#define FLAG_SET                            1

// SPI status register macros
#define SPI_RXNE_FLAG                       (1 << 0)
#define SPI_TXE_FLAG                        (1 << 1)
#define SPI_BUSY_FLAG                       (1 << 7)

#define SPI_RDY                              0
#define SPI_BUSY_IN_RX                       1
#define SPI_BUSY_IN_TX                       2 

#define SPI_EVENT_TX_COMPLETE                1
#define SPI_EVENT_RX_COMPLETE                2
#define SPI_EVENT_OVR_ERR                    3
#define SPI_EVENT_CRC_ERR                    4


// SPI Configuration struct 
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

// SPI handler struct 
typedef struct 
{
    SPI_TypeDef_t* pSPIx;    // Hold SPI register base address
    SPI_Config_t SPIConfig;  // SPI configuration handle
    uint8_t *pTxBuffer;      //* To store the app, Tx buffer address 
    uint8_t *pRxBuffer;      //* To store the app, Rx buffer address
    uint32_t TxBufferLen;    //* Length of Tx buffer
    uint32_t RxBufferLen;    //* Length of Rx buffer
    uint8_t TxState;         //* To store Tx state
    uint8_t RxState;         //* To store Rx state
}SPI_HandleTypeDef;

// SPI enumerated device mode
enum
{
    SLAVE = 0,
    MASTER   
};

// SPI enumerated bus configuration
enum
{
    FullDuplex = 0,
    HalfDuplex    ,
    Simplex_Rx
};

// SPI enumerated Clock Speed
enum
{
    DIV_2 = 0,
    DIV_4    ,
    DIV8     ,
    DIV_16   ,
    DIV_32   ,
    DIV_64   ,
    DIV_128  ,
    DIV_256
};

// SPI enumerated data frame format 
enum 
{
    DFF_8BITS = 0,
    DFF_16BITS
};

// SPI enumerated Clock Polarity 
enum 
{
    CPOL_L = 0,
    CPOL_H
};

// SPI enumerated Clock Phase
enum 
{   
    CPHA_L = 0,
    CPHA_H
};

// SPI enumerated Slave Select Management
enum 
{   
    SSM_DI = 0,
    SSM_EN
};   
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
void DRV_SPI_Init(SPI_HandleTypeDef* hspix);
void DRV_SPI_DeInit(SPI_HandleTypeDef* hspix);
void DRV_SPI_PeripheralEnable(SPI_TypeDef_t* pSPIx, EnOrDi_State EnOrDi);
void DRV_SPI_SSI(SPI_TypeDef_t* pSPIx, EnOrDi_State EnOrDi);
void DRV_SPI_SSOE(SPI_TypeDef_t* pSPIx, EnOrDi_State EnOrDi);

/*
 * Send and Receive 
 */
void DRV_SPI_Transmit(SPI_TypeDef_t* hspix, uint8_t* pTx_Buffer, uint32_t Buffer_Size);
void DRV_SPI_Receive(SPI_TypeDef_t* hspix, uint8_t* pRx_Buffer, uint32_t Buffer_Size);

/*
 * Send and Receive INT
 */
uint8_t DRV_SPI_Transmit_IT(SPI_HandleTypeDef* hspix, uint8_t* pTx_Buffer, uint32_t Buffer_Size);
uint8_t DRV_SPI_Receive_IT(SPI_HandleTypeDef* hspix, uint8_t* pRx_Buffer, uint32_t Buffer_Size);

/*
 * IQR and ISR 
 */
void DRV_SPI_IRQConfig(uint8_t IRQNumber, EnOrDi_State EnOrDi);
void DRV_SPI_IRQPriorityCFG(uint8_t IRQNumber, uint8_t IRQPriority);
void DRV_SPI_IRQHandling(SPI_HandleTypeDef* hspi);

/*
 * SPI get flag status 
 */
uint8_t SPI_FlagStatus(SPI_TypeDef_t* pSPIx, uint32_t Flag);
void SPI_ClearOVERFlag(SPI_TypeDef_t* pSPIx);
void SPI_CloseTransmission(SPI_HandleTypeDef* hspix);
void SPI_CloseReception(SPI_HandleTypeDef* hspix);


/* APPLICATION CALLBACK */
void SPI_ApplicationEventCallBack(SPI_HandleTypeDef* hspix, uint8_t AppEv);
#endif /* INC_STM32F446XX_SPI_DRIVER_H_ */
