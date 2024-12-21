################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Components/i3g4250d/i3g4250d.c 

OBJS += \
./Components/i3g4250d/i3g4250d.o 

C_DEPS += \
./Components/i3g4250d/i3g4250d.d 


# Each subdirectory must supply rules for building sources it contributes
Components/i3g4250d/%.o Components/i3g4250d/%.su Components/i3g4250d/%.cyclo: ../Components/i3g4250d/%.c Components/i3g4250d/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../USB_HOST/App -I../USB_HOST/Target -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/worbb/Desktop/Electronics/SEMP/sempspace/p3_vibrationsensor_tests/test/hw/unity/src" -I"C:/Users/worbb/Desktop/Electronics/SEMP/sempspace/p3_vibrationsensor_tests/Components" -I"C:/Users/worbb/Desktop/Electronics/SEMP/sempspace/p3_vibrationsensor_tests/STM32F411E-Discovery" -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Middlewares/ST/ARM/DSP/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Components-2f-i3g4250d

clean-Components-2f-i3g4250d:
	-$(RM) ./Components/i3g4250d/i3g4250d.cyclo ./Components/i3g4250d/i3g4250d.d ./Components/i3g4250d/i3g4250d.o ./Components/i3g4250d/i3g4250d.su

.PHONY: clean-Components-2f-i3g4250d

