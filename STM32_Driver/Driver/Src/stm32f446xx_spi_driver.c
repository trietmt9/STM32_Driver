/*
 * stm32f446xx_spi_driver.c
 *
 *  Created on: Dec 26, 2023
 *      Author: pc
 */
#include <stm32f446xx_spi_driver.h>


/*******************************************************
 * @fn                     - DRV_SPI_Pclkcontrol
 * 
 * @brief                  - Enable or Disable peripheral clock 
 * 
 * @param                  - pSPIx: SPI peripheral of  the MCU
 * @param                  - EnOrDi: Enable or Disable 
 * 
 * @return                 - void
********************************************************/
void DRV_SPI_Pclkcontrol(SPI_TypeDef_t* pSPIx, EnOrDi_State EnOrDi)
{
    if (EnOrDi == ENABLE)
    {
        if(pSPIx == SPI1)       SPI1_PCLK_EN();
        else if(pSPIx == SPI2)  SPI2_PCLK_EN();
        else if(pSPIx == SPI3)  SPI3_PCLK_EN();
        else if(pSPIx == SPI4)  SPI4_PCLK_EN();
    }
    else
    {
        if(pSPIx == SPI1)       SPI1_PCLK_DI();
        else if(pSPIx == SPI2)  SPI2_PCLK_DI();
        else if(pSPIx == SPI3)  SPI3_PCLK_DI();
        else if(pSPIx == SPI4)  SPI4_PCLK_DI();
    }
    
}

/*******************************************************
 * @fn                     - DRV_SPI_Init
 * 
 * @brief                  - Initialize SPI
 * 
 * @param                  - pSPIx: SPI peripheral of  the MCU
 * @param                  - pGPIOConfig: Pin configuration variable
 * 
 * @return                 - void
********************************************************/
void DRV_SPI_Init(SPI_TypeDef_t* pSPIx, SPI_Config_t* hspix)
{
    // Configure CR1 register 
    uint32_t tempreg = 0;
    tempreg &= ~pSPIx->CR1;
    
    // Enable peripheral clock 
    DRV_SPI_Pclkcontrol(pSPIx, ENABLE);

    // 1. Configure device mode
    tempreg |= (hspix->SPI_DeviceMode << 2);
    
    // 2. Bus configure 
    if(hspix->SPI_BusConfig == FullDuplex)
    {
        // BIDI should be cleared
        tempreg &=~ (1<<15);
    }
    else if(hspix->SPI_BusConfig == HalfDuplex)
    {
        // BIDI should be Set
        tempreg |= (1<<15);
    }
    
    else if(hspix->SPI_BusConfig == Simplex_Rx)
    {
        // BIDI should be cleared and RXONLY bit must be set
        tempreg &=~ (1<<15);
        tempreg |=  (1<<10);
    }

    // 3. Configure SPI serial clock peripheral speed
    tempreg |= (hspix->SPI_SClkSpeed << 3);

    // 4. Configure SPI Data frame format
    tempreg |= (hspix->SPI_DFF << 11);

    // 5. Configure SPI polarity clock 
    tempreg |= (hspix->SPI_CPOL << 1);

    // 6. Configure SPI phase clock 
    tempreg |= (hspix->SPI_CPHA << 0);  

    // 7. Configure SPI phase clock
    tempreg |= (hspix->SPI_SSM << 9);

    pSPIx->CR1 = tempreg;
}

void DRV_SPI_PeripheralEnable(SPI_TypeDef_t* pSPIx, EnOrDi_State EnOrDi)
{
    if(EnOrDi == ENABLE)
    {
        pSPIx->CR1 |= (1 << 6);
    }
    else 
    {
        pSPIx->CR1 &=~ (1 << 6);
    }
}

/*******************************************************
 * @fn                     - DRV_SPI_SSI
 * 
 * @brief                  - Enable or Disable SSI register
 * 
 * @param                  - pSPIx: SPI peripheral of the MCU
 * @param                  - EnOrDi: Enable or Disable
 * 
 * @return                 - void
********************************************************/
void DRV_SPI_SSI(SPI_TypeDef_t* pSPIx, EnOrDi_State EnOrDi)
{
    if(EnOrDi == ENABLE)
    {
        pSPIx->CR1 |= (1 << 8);
    }
    else 
    {
        pSPIx->CR1 &=~ (1 << 8);
    }
}

/*******************************************************
 * @fn                     - DRV_SPI_SSOE
 * 
 * @brief                  - Enable or Disable SSOE register
 * 
 * @param                  - pSPIx: SPI peripheral of the MCU
 * @param                  - EnOrDi: Enable or Disable
 * 
 * @return                 - void
********************************************************/
void DRV_SPI_SSOE(SPI_TypeDef_t* pSPIx, EnOrDi_State EnOrDi)
{
    if(EnOrDi == ENABLE)
    {
        pSPIx->CR2 |= (1 << 2);
    }
    else 
    {
        pSPIx->CR2 &=~ (1 << 2);
    }
}

/*******************************************************
 * @fn                     - DRV_SPI_DeInit
 * 
 * @brief                  - Reset SPI register 
 * 
 * @param                  - pSPIx: SPI peripheral of the MCU
 * 
 * @return                 - void
********************************************************/
void DRV_SPI_DeInit(SPI_TypeDef_t* pSPIx)
{
        if(pSPIx == SPI1) SPI1_REG_RESET();
        else if(pSPIx == SPI2) SPI2_REG_RESET();
        else if(pSPIx == SPI3) SPI3_REG_RESET();
        else if(pSPIx == SPI4) SPI4_REG_RESET();
}

/*******************************************************
 * @fn                     - SPI_FlagStatus
 * 
 * @brief                  - Check TXE register status 
 * 
 * @param                  - pSPIx: SPI peripheral of the MCU
 * @param                  - FLag: Flag name
 * 
 * @return                 - void
********************************************************/
uint8_t SPI_FlagStatus(SPI_TypeDef_t* hspix, uint32_t Flag)
{
    if(hspix->SR & Flag)
    {
        return FLAG_SET;
    }
    return FLAG_RESET;
}

/*******************************************************
 * @fn                     - DRV_SPI_Transmit
 * 
 * @brief                  - SPI transmit data  
 * 
 * @param                  - pSPIx: SPI peripheral of the MCU
 * @param                  - pTx_Buffer: Transmitted buffer
 * @param                  - Buffer_size: Size of buffer
 * 
 * @return                 - void
 * @note                   - This function is in blocking mode
********************************************************/
void DRV_SPI_Transmit(SPI_TypeDef_t* hspix, uint8_t* pTx_Buffer, uint32_t Buffer_Size)
{
    while(Buffer_Size > 0)
    {
        // 1. Wait TXE is set
        while(SPI_FlagStatus(hspix, SPI_TXE_FLAG) == FLAG_RESET);

        // 2. Check DFF bit in CR1 
        if(hspix->CR1 & (1 << 11))
        {
            // 16 bits DFF 
            // 1.1 Load data to DR register 
            hspix->DR = *((uint16_t*) pTx_Buffer);
            (uint16_t*) pTx_Buffer++;
            Buffer_Size--;
            Buffer_Size--;       
        }
        else 
        {
            // 8 bits DFF
            // 1.1 Load data to DR register 
            hspix->DR = *pTx_Buffer;
            Buffer_Size--;
            pTx_Buffer++;
        }
    }
}

/*******************************************************
 * @fn                     - DRV_SPI_Receive
 * 
 * @brief                  - SPI receive data  
 * 
 * @param                  - pSPIx: SPI peripheral of the MCU
 * @param                  - pTx_Buffer: Received buffer
 * @param                  - Buffer_size: Size of buffer
 * 
 * @return                 - void
 * @note                   - This function is in blocking mode
********************************************************/
void DRV_SPI_Receive(SPI_TypeDef_t* hspix, uint8_t* pRx_Buffer, uint32_t Buffer_Size)
{
    while(Buffer_Size > 0)
    {
        // 1. Wait TXE is set
        while(SPI_FlagStatus(hspix, SPI_RXNE_FLAG) == FLAG_RESET);

        // 2. Check DFF bit in CR1 
        if(hspix->CR1 & (1 << 11))
        {
            // 16 bits DFF 
            // 1.1 Load data to Rx buffer address  
            *((uint16_t*) pRx_Buffer) = hspix->DR;
            (uint16_t*) pRx_Buffer++;
            Buffer_Size--;
            Buffer_Size--;       
        }
        else 
        {
            // 8 bits DFF
            // 1.1 Load data to DR register 
            *(pRx_Buffer) = hspix->DR;
            Buffer_Size--;
            pRx_Buffer++;
        }
    }
}