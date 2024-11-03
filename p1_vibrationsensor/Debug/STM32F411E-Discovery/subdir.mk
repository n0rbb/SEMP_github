################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../STM32F411E-Discovery/stm32f411e_discovery.c \
../STM32F411E-Discovery/stm32f411e_discovery_accelerometer.c \
../STM32F411E-Discovery/stm32f411e_discovery_gyroscope.c 

OBJS += \
./STM32F411E-Discovery/stm32f411e_discovery.o \
./STM32F411E-Discovery/stm32f411e_discovery_accelerometer.o \
./STM32F411E-Discovery/stm32f411e_discovery_gyroscope.o 

C_DEPS += \
./STM32F411E-Discovery/stm32f411e_discovery.d \
./STM32F411E-Discovery/stm32f411e_discovery_accelerometer.d \
./STM32F411E-Discovery/stm32f411e_discovery_gyroscope.d 


# Each subdirectory must supply rules for building sources it contributes
STM32F411E-Discovery/%.o STM32F411E-Discovery/%.su STM32F411E-Discovery/%.cyclo: ../STM32F411E-Discovery/%.c STM32F411E-Discovery/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/worbb/Desktop/Electronics/SEMP/sempspace/p1_vibrationsensor/STM32F411E-Discovery" -I"C:/Users/worbb/Desktop/Electronics/SEMP/sempspace/p1_vibrationsensor/Components" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-STM32F411E-2d-Discovery

clean-STM32F411E-2d-Discovery:
	-$(RM) ./STM32F411E-Discovery/stm32f411e_discovery.cyclo ./STM32F411E-Discovery/stm32f411e_discovery.d ./STM32F411E-Discovery/stm32f411e_discovery.o ./STM32F411E-Discovery/stm32f411e_discovery.su ./STM32F411E-Discovery/stm32f411e_discovery_accelerometer.cyclo ./STM32F411E-Discovery/stm32f411e_discovery_accelerometer.d ./STM32F411E-Discovery/stm32f411e_discovery_accelerometer.o ./STM32F411E-Discovery/stm32f411e_discovery_accelerometer.su ./STM32F411E-Discovery/stm32f411e_discovery_gyroscope.cyclo ./STM32F411E-Discovery/stm32f411e_discovery_gyroscope.d ./STM32F411E-Discovery/stm32f411e_discovery_gyroscope.o ./STM32F411E-Discovery/stm32f411e_discovery_gyroscope.su

.PHONY: clean-STM32F411E-2d-Discovery

