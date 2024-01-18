/*
 * main_SPI_ESP32.c
 *
 *  Created on: Jan 15, 2024
 *      Author: trietmt9
 */

#include <stm32f446xx_gpio_driver.h>
#include <stm32f446xx_spi_driver.h>
#include <stdint.h>
void GPIO_INIT(void);
void SPI_INIT(void);

int main(void)
{
    char buffer[]= "Hello World !";
    // Initialize GPIO and SPI peripherals 
    GPIO_INIT();
    SPI_INIT();

    // Enable SPI SSOE register 
    DRV_SPI_SSOE(SPI1, ENABLE);

    while(1)
    {    
        while(!(DRV_GPIO_ReadPin(GPIOC, GPIO_PIN_13)));
        // Enable SPI peripheral
        DRV_SPI_PeripheralEnable(SPI1, ENABLE);

        // Send data length 
        uint8_t dataLength = strlen(buffer);
        DRV_SPI_Transmit(SPI1,&dataLength, 1);
        
        // Send data 
        DRV_SPI_Transmit(SPI1,(uint8_t*) buffer, strlen(buffer));

        // check SPI is busy or not
        while(SPI_FlagStatus(SPI1, SPI_BUSY_FLAG)); 
        DRV_SPI_PeripheralEnable(SPI1, DISABLE);
    }
	return 0;
}

void SPI_INIT(void)
{ 
	SPI_Config_t hspi1      = {0};
    hspi1.SPI_BusConfig     = FullDuplex;
    hspi1.SPI_DeviceMode    = MASTER;
    hspi1.SPI_SClkSpeed     = DIV_8; // generate 8MHz
    hspi1.SPI_DFF           = DFF_8BITS;
    hspi1.SPI_CPOL          = CPOL_L;
    hspi1.SPI_CPHA          = CPHA_L;
    hspi1.SPI_SSM           = SSM_DI; // SW management disable
    DRV_SPI_Init(SPI1, &hspi1);
}


void GPIO_INIT(void)
{
    // Button PC13
    GPIO_PinConfig_t GPIO_Struct = {0};
    GPIO_Struct.PinNumber   = GPIO_PIN_13;
    GPIO_Struct.PinMode     = GPIO_IT_FALLING;
    GPIO_Struct.PinPUPDCtrl = PullUp; 
    DRV_GPIO_Init(GPIOC, &GPIO_Struct);

    GPIO_PinConfig_t SpiGPIO ;
    SpiGPIO.PinMode         = GPIO_ALTERNATE;
    SpiGPIO.PinAltFunction  = 5;
    SpiGPIO.PinOPType       = PushPull;
    SpiGPIO.PinPUPDCtrl     = NoPUPD;
    SpiGPIO.PinSpeed        = FAST;
    // NSS
    SpiGPIO.PinNumber = GPIO_PIN_4;
    DRV_GPIO_Init(GPIOA, &SpiGPIO);

    // SCK
    SpiGPIO.PinNumber = GPIO_PIN_5;
    DRV_GPIO_Init(GPIOA, &SpiGPIO);

    // MISO
    SpiGPIO.PinNumber = GPIO_PIN_6;
    DRV_GPIO_Init(GPIOA, &SpiGPIO);  

    // MOSI
    SpiGPIO.PinNumber = GPIO_PIN_7;
    DRV_GPIO_Init(GPIOA, &SpiGPIO);

}