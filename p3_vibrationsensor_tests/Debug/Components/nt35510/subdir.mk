################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Components/nt35510/nt35510.c 

OBJS += \
./Components/nt35510/nt35510.o 

C_DEPS += \
./Components/nt35510/nt35510.d 


# Each subdirectory must supply rules for building sources it contributes
Components/nt35510/%.o Components/nt35510/%.su Components/nt35510/%.cyclo: ../Components/nt35510/%.c Components/nt35510/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../USB_HOST/App -I../USB_HOST/Target -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/worbb/Desktop/Electronics/SEMP/sempspace/p3_vibrationsensor_tests/Components" -I"C:/Users/worbb/Desktop/Electronics/SEMP/sempspace/p3_vibrationsensor_tests/STM32F411E-Discovery" -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Middlewares/ST/ARM/DSP/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Components-2f-nt35510

clean-Components-2f-nt35510:
	-$(RM) ./Components/nt35510/nt35510.cyclo ./Components/nt35510/nt35510.d ./Components/nt35510/nt35510.o ./Components/nt35510/nt35510.su

.PHONY: clean-Components-2f-nt35510

