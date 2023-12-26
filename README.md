# STM32F4_Driver
- This repo contains is peripheral driver for the stm32f4 series based on CMSIS standard
## The Diagram below shown a full driver layer of the STM32F446xx series that I had built <br/>
### STM32F446xx 
![HAL](Images/HAL.png)
- This driver contain STM32F446xx series for controlling other drivers peripheral.
- It also contain peripheral base address, control macros,...
### GPIO driver 
![GPIO](Images/GPIO.png)
- GPIO driver is use for controlling GPIO peripheral in the STM32F4 series 
- It contain APIs like: GPIO_Write_Pin, GPIO_Read_Pin, GPIO_Write_Port, GPIO_Read_Port, GPIO_IQR <br/>

