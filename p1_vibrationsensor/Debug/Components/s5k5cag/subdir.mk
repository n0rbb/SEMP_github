################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Components/s5k5cag/s5k5cag.c 

OBJS += \
./Components/s5k5cag/s5k5cag.o 

C_DEPS += \
./Components/s5k5cag/s5k5cag.d 


# Each subdirectory must supply rules for building sources it contributes
Components/s5k5cag/%.o Components/s5k5cag/%.su Components/s5k5cag/%.cyclo: ../Components/s5k5cag/%.c Components/s5k5cag/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/worbb/Desktop/Electronics/SEMP/sempspace/p1_vibrationsensor/STM32F411E-Discovery" -I"C:/Users/worbb/Desktop/Electronics/SEMP/sempspace/p1_vibrationsensor/Components" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Components-2f-s5k5cag

clean-Components-2f-s5k5cag:
	-$(RM) ./Components/s5k5cag/s5k5cag.cyclo ./Components/s5k5cag/s5k5cag.d ./Components/s5k5cag/s5k5cag.o ./Components/s5k5cag/s5k5cag.su

.PHONY: clean-Components-2f-s5k5cag

