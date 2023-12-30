################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/Src/stm32f446xx_gpio_driver.c \
../Drivers/Src/stm32f446xx_spi_driver.c 

OBJS += \
./Drivers/Src/stm32f446xx_gpio_driver.o \
./Drivers/Src/stm32f446xx_spi_driver.o 

C_DEPS += \
./Drivers/Src/stm32f446xx_gpio_driver.d \
./Drivers/Src/stm32f446xx_spi_driver.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/Src/%.o Drivers/Src/%.su Drivers/Src/%.cyclo: ../Drivers/Src/%.c Drivers/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F446RETx -DNUCLEO_F446RE -c -I../Inc -I"C:/Users/pc/Documents/STM32_Driver/STM32_Driver/Drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-Src

clean-Drivers-2f-Src:
	-$(RM) ./Drivers/Src/stm32f446xx_gpio_driver.cyclo ./Drivers/Src/stm32f446xx_gpio_driver.d ./Drivers/Src/stm32f446xx_gpio_driver.o ./Drivers/Src/stm32f446xx_gpio_driver.su ./Drivers/Src/stm32f446xx_spi_driver.cyclo ./Drivers/Src/stm32f446xx_spi_driver.d ./Drivers/Src/stm32f446xx_spi_driver.o ./Drivers/Src/stm32f446xx_spi_driver.su

.PHONY: clean-Drivers-2f-Src

