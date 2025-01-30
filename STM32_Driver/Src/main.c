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

#define SLAVE_MODE
// #define MASTER_MODE


/*
 * Alternate function mode: 5
 * SPI1 pin configuration
 * PA4 ---> NSS  ---> A4
 * PA5 ---> SCK  ---> D13
 * PA6 ---> MISO ---> D12
 * PA7 ---> MOSI ---> D11
 */
uint8_t rx_buffer = 0;
uint8_t tx_buffer = 0;

void GPIO_INIT(void);
void SPI_INIT(void);
void IRQ_INIT(void);
void delay(uint32_t timeout)
{
    for(volatile uint32_t i = 0; i < (timeout*1000); i++);
}
int main(void)
{ 


    #ifdef MASTER_MODE
    IRQ_INIT();
    #endif
    GPIO_INIT();
    SPI_INIT();
    DRV_SPI_SSI(SPI1, ENABLE);
    DRV_SPI_PeripheralEnable(SPI1, ENABLE);
    #ifdef MASTER_MODE
    DRV_GPIO_WritePin(GPIOA,GPIO_PIN_4, SET);
    #endif
    while(1)
    {
        // DRV_SPI_Receive(SPI1, (uint8_t*) &rx_buffer, 1);
        #ifdef SLAVE_MODE
        DRV_SPI_Receive(SPI1, (uint8_t*) &rx_buffer, 1);
        if(rx_buffer == 0x07)
        {
            DRV_GPIO_TogglePin(GPIOA, GPIO_PIN_8);
            tx_buffer = 0x01;
            DRV_SPI_Transmit(SPI1,(uint8_t*) &tx_buffer, sizeof(tx_buffer));
        }
        #endif
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
    #ifdef MASTER_MODE
    SPI_Handle_t hspi1                = {0};
    hspi1.pSPIx                       = SPI1;
    hspi1.SPIConfig.SPI_BusConfig     = FullDuplex;
    hspi1.SPIConfig.SPI_DeviceMode    = MASTER;
    hspi1.SPIConfig.SPI_SClkSpeed     = DIV_2; // generate 8MHz
    hspi1.SPIConfig.SPI_DFF           = DFF_8BITS;
    hspi1.SPIConfig.SPI_CPOL          = CPOL_L;
    hspi1.SPIConfig.SPI_CPHA          = CPHA_L;
    hspi1.SPIConfig.SPI_SSM           = SSM_EN; // SW management enable
    #endif
    #ifdef SLAVE_MODE
    SPI_Handle_t hspi1                = {0};
    hspi1.pSPIx                       = SPI1;
    hspi1.SPIConfig.SPI_BusConfig     = FullDuplex;
    hspi1.SPIConfig.SPI_DeviceMode    = SLAVE;
    hspi1.SPIConfig.SPI_SClkSpeed     = DIV_2; // generate 8MHz
    hspi1.SPIConfig.SPI_DFF           = DFF_8BITS;
    hspi1.SPIConfig.SPI_CPOL          = CPOL_L;
    hspi1.SPIConfig.SPI_CPHA          = CPHA_L;
    hspi1.SPIConfig.SPI_SSM           = SSM_DI; // SW management disable
    #endif
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

    #ifdef SLAVE_MODE
    // NSS
    SpiGPIO.GPIO_PinConfig.PinNumber = GPIO_PIN_4;
    DRV_GPIO_Init(&SpiGPIO);
    #endif

    // SCK
    SpiGPIO.GPIO_PinConfig.PinNumber = GPIO_PIN_5;
    DRV_GPIO_Init(&SpiGPIO);

    // MISO
    SpiGPIO.GPIO_PinConfig.PinNumber = GPIO_PIN_6;
    DRV_GPIO_Init(&SpiGPIO);

    // MOSI
    SpiGPIO.GPIO_PinConfig.PinNumber = GPIO_PIN_7;
    DRV_GPIO_Init(&SpiGPIO);

#ifdef MASTER_MODE
    // GPIO Button init
    GPIO_HandleTypeDef Button = {0};
    Button.pGPIOx                                      = GPIOC;
    Button.GPIO_PinConfig.PinNumber                    = GPIO_PIN_13;
    Button.GPIO_PinConfig.PinMode                      = GPIO_IT_FALLING;
    Button.GPIO_PinConfig.PinPUPDCtrl                  = PullUp; 
    DRV_GPIO_Init(&Button);

    // GPIO LED init
    GPIO_HandleTypeDef LED                          = {0};
    LED.pGPIOx                                      = GPIOA;
    LED.GPIO_PinConfig.PinNumber                    = GPIO_PIN_8;
    LED.GPIO_PinConfig.PinMode                      = GPIO_OUTPUT;
    LED.GPIO_PinConfig.PinSpeed                     = FAST;
    LED.GPIO_PinConfig.PinOPType                    = PushPull;
    LED.GPIO_PinConfig.PinPUPDCtrl                  = NoPUPD;
    DRV_GPIO_Init(&LED);
    // NSS
    LED.GPIO_PinConfig.PinNumber = GPIO_PIN_4;
    DRV_GPIO_Init(&LED);
#endif

#ifdef SLAVE_MODE
    // GPIO LED init
    GPIO_HandleTypeDef LED              = {0};
    LED.pGPIOx                          = GPIOA;
    LED.GPIO_PinConfig.PinMode          = GPIO_OUTPUT;
    LED.GPIO_PinConfig.PinOPType        = PushPull;
    LED.GPIO_PinConfig.PinPUPDCtrl      = NoPUPD;
    LED.GPIO_PinConfig.PinSpeed         = FAST;
    LED.GPIO_PinConfig.PinNumber        = GPIO_PIN_8;
    DRV_GPIO_Init(&LED);
#endif
}
#ifdef MASTER_MODE
/**
 * @brief Initialize the interrupt
 * @details This function initializes the interrupt used by the application.
 */
void IRQ_INIT(void)
{
    DRV_GPIO_IRQConfig(IRQ_NO_EXTI15_10, ENABLE);
    DRV_GPIO_IRQPriorityCFG(IRQ_NO_EXTI15_10, 15);
}

/**
 * @brief Interrupt service routine for EXTI15_10
 *
 * This function is the interrupt service routine for EXTI15_10. It is triggered
 * whenever the button connected to PC13 is pressed. The function increments the
 * mode variable, which is used to switch between different modes of operation.
 */
void EXTI15_10_IRQHandler(void)
{
    DRV_GPIO_IRQHandling(GPIO_PIN_13);
    tx_buffer = 0x01;
    DRV_GPIO_WritePin(GPIOA,GPIO_PIN_4, RESET);
    DRV_SPI_Transmit(SPI1,(uint8_t*) &tx_buffer, sizeof(tx_buffer));  
    DRV_GPIO_WritePin(GPIOA,GPIO_PIN_4, SET);
    DRV_GPIO_TogglePin(GPIOA, GPIO_PIN_8);
}
#endif

