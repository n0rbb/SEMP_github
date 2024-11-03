################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Components/ili9341/ili9341.c 

OBJS += \
./Components/ili9341/ili9341.o 

C_DEPS += \
./Components/ili9341/ili9341.d 


# Each subdirectory must supply rules for building sources it contributes
Components/ili9341/%.o Components/ili9341/%.su Components/ili9341/%.cyclo: ../Components/ili9341/%.c Components/ili9341/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/worbb/Desktop/Electronics/SEMP/sempspace/p1_vibrationsensor/STM32F411E-Discovery" -I"C:/Users/worbb/Desktop/Electronics/SEMP/sempspace/p1_vibrationsensor/Components" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Components-2f-ili9341

clean-Components-2f-ili9341:
	-$(RM) ./Components/ili9341/ili9341.cyclo ./Components/ili9341/ili9341.d ./Components/ili9341/ili9341.o ./Components/ili9341/ili9341.su

.PHONY: clean-Components-2f-ili9341

