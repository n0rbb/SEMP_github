################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Components/mfxstm32l152/mfxstm32l152.c 

OBJS += \
./Components/mfxstm32l152/mfxstm32l152.o 

C_DEPS += \
./Components/mfxstm32l152/mfxstm32l152.d 


# Each subdirectory must supply rules for building sources it contributes
Components/mfxstm32l152/%.o Components/mfxstm32l152/%.su Components/mfxstm32l152/%.cyclo: ../Components/mfxstm32l152/%.c Components/mfxstm32l152/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/hontana_97/Downloads/SEMP_github-main (3)/SEMP_github-main/p1_vibrationsensor/STM32F411E-Discovery" -I"C:/Users/hontana_97/Downloads/SEMP_github-main (3)/SEMP_github-main/p1_vibrationsensor/Components" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Components-2f-mfxstm32l152

clean-Components-2f-mfxstm32l152:
	-$(RM) ./Components/mfxstm32l152/mfxstm32l152.cyclo ./Components/mfxstm32l152/mfxstm32l152.d ./Components/mfxstm32l152/mfxstm32l152.o ./Components/mfxstm32l152/mfxstm32l152.su

.PHONY: clean-Components-2f-mfxstm32l152

