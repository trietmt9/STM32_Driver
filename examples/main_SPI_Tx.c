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
    for(uint32_t i = 0; i < (timeout*1000); i++);
}
int main(void)
{

	char buffer[]= "Hello CGU";
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
void SPI_INIT(void)
{
	SPI_Config_t hspi1      = {0};
    hspi1.SPI_BusConfig     = FullDuplex;
    hspi1.SPI_DeviceMode    = MASTER;
    hspi1.SPI_SClkSpeed     = DIV_2; // generate 8MHz
    hspi1.SPI_DFF           = DFF_8BITS;
    hspi1.SPI_CPOL          = CPOL_L;
    hspi1.SPI_CPHA          = CPHA_L;
    hspi1.SPI_SSM           = SSM_EN; // SW management disable
    DRV_SPI_Init(SPI1, &hspi1);
}

void GPIO_INIT(void)
{
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


