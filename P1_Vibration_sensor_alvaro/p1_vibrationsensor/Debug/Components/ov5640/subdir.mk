################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Components/ov5640/ov5640.c 

OBJS += \
./Components/ov5640/ov5640.o 

C_DEPS += \
./Components/ov5640/ov5640.d 


# Each subdirectory must supply rules for building sources it contributes
Components/ov5640/%.o Components/ov5640/%.su Components/ov5640/%.cyclo: ../Components/ov5640/%.c Components/ov5640/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/worbb/Desktop/Electronics/SEMP/SEMP_github/P1_Vibration_sensor_alvaro/p1_vibrationsensor/STM32F411E-Discovery" -I"C:/Users/worbb/Desktop/Electronics/SEMP/SEMP_github/P1_Vibration_sensor_alvaro/p1_vibrationsensor/Components" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Components-2f-ov5640

clean-Components-2f-ov5640:
	-$(RM) ./Components/ov5640/ov5640.cyclo ./Components/ov5640/ov5640.d ./Components/ov5640/ov5640.o ./Components/ov5640/ov5640.su

.PHONY: clean-Components-2f-ov5640

