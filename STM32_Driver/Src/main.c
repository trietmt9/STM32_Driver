/*
 * main_SPI.c
 *
 *  Created on: Dec 28, 2023
 *      Author: pc
 */

#include <stm32f446xx.h>
#include <stm32f446xx_spi_driver.h>
#include <stm32f446xx_gpio_driver.h>
#include <string.h>

/*
 * Alternate function mode: 5
 * SPI1 pin configuration
 * PA4 ---> NSS  ---> A4
 * PA5 ---> SCK  ---> D13
 * PA6 ---> MISO ---> D12
 * PA7 ---> MOSI ---> D11
 */

void GPIO_INIT(void);
void SPI_INIT(void);
void delay(uint32_t timeout)
{
    for(uint32_t i = 0; i < (timeout*100000); i++);
}
int main(void)
{

	char buffer[]= "Hello Everyones!\n";
    GPIO_INIT();
    SPI_INIT();
    DRV_SPI_SSI(SPI1, ENABLE); // Pull NSS to high
    DRV_SPI_PeripheralEnable(SPI1, ENABLE);
    while(1)
    {
        DRV_SPI_Transmit(SPI1,(uint8_t*) buffer, strlen(buffer));
        delay(1000);
    }
	return 0;
}

/**
 * @brief Initializes the SPI1 peripheral with specific configuration.
 *
 * This function sets up SPI1 with the following configuration:
 * - Full-duplex communication
 * - Master mode
 * - Clock speed set to 8MHz (DIV_2)
 * - 8-bit data frame format
 * - Clock polarity low (CPOL_L)
 * - Clock phase low (CPHA_L)
 * - Software slave management enabled (SSM_EN)
 *
 * @param None
 * @return None
 */
void SPI_INIT(void)
{
	SPI_Handle_t hspi1                = {0};
    hspi1.pSPIx                       = SPI1;
    hspi1.SPIConfig.SPI_BusConfig     = FullDuplex;
    hspi1.SPIConfig.SPI_DeviceMode    = MASTER;
    hspi1.SPIConfig.SPI_SClkSpeed     = DIV_2; // generate 8MHz
    hspi1.SPIConfig.SPI_DFF           = DFF_8BITS;
    hspi1.SPIConfig.SPI_CPOL          = CPOL_L;
    hspi1.SPIConfig.SPI_CPHA          = CPHA_L;
    hspi1.SPIConfig.SPI_SSM           = SSM_EN; // SW management disable
    DRV_SPI_Init(&hspi1);
}

/**
 * @brief Initializes GPIO pins for SPI communication.
 *
 * This function configures the GPIO pins for SPI1 on GPIOA:
 * - PA4 as NSS (Chip Select)
 * - PA5 as SCK (Serial Clock)
 * - PA6 as MISO (Master In Slave Out)
 * - PA7 as MOSI (Master Out Slave In)
 *
 * The pins are set to alternate function mode with specific configurations.
 *
 * @param None
 * @return None
 */

void GPIO_INIT(void)
{
    GPIO_HandleTypeDef SpiGPIO             = {0};
    SpiGPIO.pGPIOx                         = GPIOA;
    SpiGPIO.GPIO_PinConfig.PinMode         = GPIO_ALTERNATE;
    SpiGPIO.GPIO_PinConfig.PinAltFunction  = 5;
    SpiGPIO.GPIO_PinConfig.PinOPType       = PushPull;
    SpiGPIO.GPIO_PinConfig.PinPUPDCtrl     = NoPUPD;
    SpiGPIO.GPIO_PinConfig.PinSpeed        = FAST;
    // NSS
    SpiGPIO.GPIO_PinConfig.PinNumber = GPIO_PIN_4;
    DRV_GPIO_Init(&SpiGPIO);

    // SCK
    SpiGPIO.GPIO_PinConfig.PinNumber = GPIO_PIN_5;
    DRV_GPIO_Init(&SpiGPIO);

    // MISO
    SpiGPIO.GPIO_PinConfig.PinNumber = GPIO_PIN_6;
    DRV_GPIO_Init(&SpiGPIO);

    // MOSI
    SpiGPIO.GPIO_PinConfig.PinNumber = GPIO_PIN_7;
    DRV_GPIO_Init(&SpiGPIO);

}

