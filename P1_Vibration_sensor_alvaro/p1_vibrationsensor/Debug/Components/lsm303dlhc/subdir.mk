################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Components/lsm303dlhc/lsm303dlhc.c 

OBJS += \
./Components/lsm303dlhc/lsm303dlhc.o 

C_DEPS += \
./Components/lsm303dlhc/lsm303dlhc.d 


# Each subdirectory must supply rules for building sources it contributes
Components/lsm303dlhc/%.o Components/lsm303dlhc/%.su Components/lsm303dlhc/%.cyclo: ../Components/lsm303dlhc/%.c Components/lsm303dlhc/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/hontana_97/Downloads/SEMP_github-main (3)/SEMP_github-main/p1_vibrationsensor/STM32F411E-Discovery" -I"C:/Users/hontana_97/Downloads/SEMP_github-main (3)/SEMP_github-main/p1_vibrationsensor/Components" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Components-2f-lsm303dlhc

clean-Components-2f-lsm303dlhc:
	-$(RM) ./Components/lsm303dlhc/lsm303dlhc.cyclo ./Components/lsm303dlhc/lsm303dlhc.d ./Components/lsm303dlhc/lsm303dlhc.o ./Components/lsm303dlhc/lsm303dlhc.su

.PHONY: clean-Components-2f-lsm303dlhc

