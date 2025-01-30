/*
 * stm32f446xx_spi_driver.c
 *
 *  Created on: Dec 26, 2023
 *      Author: pc
 */
#include <stm32f446xx_spi_driver.h>

static void spi_txe_int_handle(SPI_Handle_t *hspix);
static void spi_rxe_int_handle(SPI_Handle_t *hspix);
static void spi_ovr_err_int_handle(SPI_Handle_t *hspix);
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
void DRV_SPI_Init(SPI_Handle_t* hspix)
{
    // Configure CR1 register 
    uint32_t tempreg = 0;
    tempreg &= ~hspix->pSPIx->CR1;
    
    // Enable peripheral clock 
    DRV_SPI_Pclkcontrol(hspix->pSPIx, ENABLE);

    // 1. Configure device mode
    tempreg |= (hspix->SPIConfig.SPI_DeviceMode << 2);
    
    // 2. Bus configure 
    if(hspix->SPIConfig.SPI_BusConfig == FullDuplex)
    {
        // BIDI should be cleared
        tempreg &=~ (1<<15);
    }
    else if(hspix->SPIConfig.SPI_BusConfig == HalfDuplex)
    {
        // BIDI should be Set
        tempreg |= (1<<15);
    }
    
    else if(hspix->SPIConfig.SPI_BusConfig == Simplex_Rx)
    {
        // BIDI should be cleared and RXONLY bit must be set
        tempreg &=~ (1<<15);
        tempreg |=  (1<<10);
    }

    // 3. Configure SPI serial clock peripheral speed
    tempreg |= (hspix->SPIConfig.SPI_SClkSpeed << 3);

    // 4. Configure SPI Data frame format
    tempreg |= (hspix->SPIConfig.SPI_DFF << 11);

    // 5. Configure SPI polarity clock 
    tempreg |= (hspix->SPIConfig.SPI_CPOL << 1);

    // 6. Configure SPI phase clock 
    tempreg |= (hspix->SPIConfig.SPI_CPHA << 0);  

    // 7. Configure SPI phase clock
    tempreg |= (hspix->SPIConfig.SPI_SSM << 9);

    hspix->pSPIx->CR1 = tempreg;
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
void DRV_SPI_DeInit(SPI_Handle_t* hspix)
{
        if(hspix->pSPIx == SPI1) SPI1_REG_RESET();
        else if(hspix->pSPIx == SPI2) SPI2_REG_RESET();
        else if(hspix->pSPIx == SPI3) SPI3_REG_RESET();
        else if(hspix->pSPIx == SPI4) SPI4_REG_RESET();
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
void DRV_SPI_Transmit(SPI_TypeDef_t* hspix,uint8_t* pTx_Buffer, uint32_t Buffer_Size)
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
        //* 1. Wait TXE is set
        while(SPI_FlagStatus(hspix, SPI_RXNE_FLAG) == FLAG_RESET);

        //* 2. Check DFF bit in CR1 
        if(hspix->CR1 & (1 << 11))
        {
            //* 16 bits DFF 
            //* 1.1 Load data to Rx buffer address  
            *((uint16_t*) pRx_Buffer) = hspix->DR;
            Buffer_Size--;
            Buffer_Size--; 
            (uint16_t*) pRx_Buffer++;      
        }
        else 
        {
            //* 8 bits DFF
            //* 1.1 Load data to DR register 
            *(pRx_Buffer) = hspix->DR;
            Buffer_Size--;
            pRx_Buffer++;
        }
    }
}


/*******************************************************
 * @fn                     - DRV_SPI_IRQConfig
 * 
 * @brief                  - Configure interrupt mode
 * 
 * @param                  - IRQNumber: Interrupt number in the MCU
 * @param                  - EnOrDi: Enable or Disable interrupts
 * 
 * @return                 - void
********************************************************/
void DRV_SPI_IRQConfig(uint8_t IRQNumber, EnOrDi_State EnOrDi)
{
    if( EnOrDi == ENABLE)
    {
        if(IRQNumber <= 31)
        {
            // ISER0 register
            *NVIC_ISER_0 |= (1 << IRQNumber);
        }
        else if (IRQNumber > 31 && IRQNumber < 64)
        {
            // ISER1 register
            *NVIC_ISER_1 |= (1 << (IRQNumber % 32));
        }
        else if (IRQNumber >= 64 && IRQNumber <96)
        {
            *NVIC_ISER_2 |= (1 << (IRQNumber % 64));
        }
    }
    else 
    {
        if(IRQNumber <= 31)
        {
            *NVIC_ICER_0 |= (1 << IRQNumber);
        }
        else if (IRQNumber > 31 && IRQNumber < 64)
        {
            *NVIC_ICER_1 |= (1 << (IRQNumber % 32));
        }
        else if (IRQNumber >= 64 && IRQNumber <96)
        {
            *NVIC_ICER_2 |= (1 << (IRQNumber % 64));
        }
    }
}

/*******************************************************
 * @fn                     - DRV_GPIO_IRQPriorityCFG
 * 
 * @brief                  - Configure priority 
 * 
 * @param                  - IRQNumber: IRQ interrupt number
 * @param                  - IRQPriority: Priority of IRQ
 * 
 * @return                 - void
********************************************************/
void DRV_SPI_IRQPriorityCFG(uint8_t IRQNumber, uint8_t IRQPriority)
{
    //1. determine IPR register 
    uint8_t IPRx = IRQNumber/4; //IPR register
    uint8_t IPRxSec = IRQNumber%4; // IPR sections
    uint8_t shift_amount = (8 * IPRxSec) + (8 - NUM_PR_BITS_IMPLEMENTED);
    *(NVIC_PR_BASE + (IPRx*4)) |= (IRQPriority << shift_amount);
}

/*******************************************************
 * @fn                     - DRV_GPIO_IRQHandling
 * 
 * @brief                  - Handling IRQ APIs
 * 
 * @param                  - PinNumber: pin number
 * 
 * @return                 - void
********************************************************/
void DRV_SPI_IRQHandling(SPI_Handle_t* hspi)
{
    uint8_t temp1, temp2; 
    // Check for TXE 
    temp1 = hspi->pSPIx->SR & (1 << 1);
    temp2 = hspi->pSPIx->CR2 & (1 << 7);
    
    if (temp1 && temp2 )
    {
        // Handle TXE 
        spi_txe_int_handle(hspi);
    }

    // Check for RXNE
    temp1 = hspi->pSPIx->SR & (1 << 0);
    temp2 = hspi->pSPIx->CR2 & (1 << 6);

     if (temp1 && temp2 )
    {
        // Handle RXNE 
        spi_rxe_int_handle(hspi);
    }

    // Check for OVR flag 
    temp1 = hspi->pSPIx->SR & (1 << 6);
    temp2 = hspi->pSPIx->CR2 & (1 << 5);

    if (temp1 && temp2 )
    {
        // Handle RXNE 
        spi_ovr_err_int_handle(hspi);
    }
}

/*******************************************************
 * @brief   Transmit data using SPI in interrupt mode.
 *
 * @param   hspix       Pointer to the SPI handle structure.
 * @param   pTx_Buffer  Pointer to the transmit buffer.
 * @param   Buffer_Size Size of the transmit buffer.
 *
 * @return  void
 *
 * @note    This function is non-blocking and uses interrupts to transmit data.
 *          The user must ensure that the transmit buffer is not modified until
 *          the transmission is complete.
 *
 * @warning This function does not handle errors or timeouts.
********************************************************/
uint8_t DRV_SPI_Transmit_IT(SPI_Handle_t* hspix, uint8_t* pTx_Buffer, uint32_t Buffer_Size)
{
    uint8_t state = hspix->TxState;
    if(state != SPI_BUSY_IN_RX)
    {
        // 1. Save the Tx buffer address and length information in some global variables 
        hspix->pTxBuffer = pTx_Buffer;
        hspix->TxBufferLen = Buffer_Size;

        /* 2. Mark the SPI state as busy in transmission 
        so that no other code can take over same SPI peripheral until transmission is over*/ 
        hspix->TxState = SPI_BUSY_IN_TX;

        // 3. Enable the TXEIE control bit to get interrupt whenever TXE flag is set in SR 
        hspix->pSPIx->CR2 |= (1 << 7);
    }
    // 4. Data Transmission will be handled by ISR code 

    return state; 
}

/*******************************************************
 * @brief Receive data using SPI in interrupt mode.
 *
 * This function initiates the reception of data using SPI in interrupt mode.
 * It sets up the necessary parameters for interrupt-based reception and enables
 * the appropriate interrupts.
 *
 * @param hspix Pointer to the SPI handle structure containing SPI configuration
 * @param pRx_Buffer Pointer to the buffer where received data will be stored.
 * @param Buffer_Size Number of bytes to receive.
 *
 * @return void
 *
 * @note This function is non-blocking. The actual data reception is handled in
 *       the interrupt service routine.
*******************************************************/
uint8_t DRV_SPI_Receive_IT(SPI_Handle_t* hspix, uint8_t* pRx_Buffer, uint32_t Buffer_Size)
{
     uint8_t state = hspix->RxState;
    if(state != SPI_BUSY_IN_TX)
    {
        // 1. Save the Tx buffer address and length information in some global variables 
        hspix->pRxBuffer = pRx_Buffer;
        hspix->RxBufferLen = Buffer_Size;

        /* 2. Mark the SPI state as busy in transmission 
        so that no other code can take over same SPI peripheral until transmission is over*/ 
        hspix->RxState = SPI_BUSY_IN_RX;

        // 3. Enable the TXEIE control bit to get interrupt whenever TXE flag is set in SR 
        hspix->pSPIx->CR2 |= (1 << 6);
    }
    // 4. Data Transmission will be handled by ISR code 

    return state; 
}




// Help function 
static void spi_txe_int_handle(SPI_Handle_t *hspix)
{
    // 1. Check DFF bit in CR1 
        if(hspix->pSPIx->CR1 & (1 << 11))
        {
            // 16 bits DFF 
            // 1.1 Load data to DR register 
            hspix->pSPIx->DR = *((uint16_t*) hspix->pTxBuffer);
            (uint16_t*) hspix->pTxBuffer++;
            hspix->TxBufferLen--;
            hspix->TxBufferLen--; 
            hspix->pTxBuffer++;
        }
        else 
        {
            // 8 bits DFF
            // 1.1 Load data to DR register 
            hspix->pSPIx->DR = *hspix->pTxBuffer;
            hspix->TxBufferLen--;
            hspix->pTxBuffer++; 
            SPI_ApplicationEventCallBack(hspix, SPI_EVENT_TX_COMPLETE);
        }
}
static void spi_rxe_int_handle(SPI_Handle_t *hspix)
{
    //* 1. Check DFF bit in CR1 
        if(hspix->pSPIx->CR1 & (1 << 11))
        {
            //* 16 bits DFF 
            //* 1.1 Load data to Rx buffer address  
            *((uint16_t*) hspix->pRxBuffer) = hspix->pSPIx->DR;
            hspix->RxBufferLen--;
            hspix->RxBufferLen--;  
            (uint16_t*) hspix->pRxBuffer++;     
        }
        else 
        {
            //* 8 bits DFF
            //* 1.1 Load data to DR register 
            *(hspix->pRxBuffer) = hspix->pSPIx->DR;
            hspix->RxBufferLen--;
            hspix->pRxBuffer++;
        }

        if(!hspix->RxBufferLen)
        {
            // RxLen is zero, close the SPI transmission and inform the application that RX is over. 
            // This prevents any further interrupts from RXNIE
            SPI_CloseReception(hspix);
            SPI_ApplicationEventCallBack(hspix, SPI_EVENT_RX_COMPLETE);
        }
}
static void spi_ovr_err_int_handle(SPI_Handle_t *hspix)
{
    uint8_t temp; 
    // 1. Clear the OVR flag 
    if(hspix->TxState != SPI_BUSY_IN_TX)
    {
        SPI_ClearOVERFlag(hspix->pSPIx);
    }
    (void)temp; // Clear
    // 2. Inform the application about the error
    SPI_ApplicationEventCallBack(hspix, SPI_EVENT_OVR_ERR);
}

void SPI_CloseTransmission(SPI_Handle_t* hspix)
{
    hspix->pSPIx->CR2 &=~ (1 << 7);
    hspix->pTxBuffer = NULL;
    hspix->TxBufferLen = 0;
    hspix->TxState = SPI_RDY;
}
void SPI_CloseReception(SPI_Handle_t* hspix)
{
    hspix->pSPIx->CR2 &=~ (1 << 6);
    hspix->pRxBuffer = NULL;
    hspix->RxBufferLen = 0;
    hspix->RxState = SPI_RDY;
}

void SPI_ClearOVERFlag(SPI_TypeDef_t* pSPIx)
{
    uint8_t temp; 
    // 1. Clear the OVR flag 
    temp = pSPIx->DR;
    temp = pSPIx->SR;
    (void)temp;
}

__weak__ void SPI_ApplicationEventCallBack(SPI_Handle_t* hspix, uint8_t AppEv)
{

}