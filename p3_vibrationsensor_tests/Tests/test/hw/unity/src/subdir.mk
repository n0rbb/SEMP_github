################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../test/hw/unity/src/unity.c 

OBJS += \
./test/hw/unity/src/unity.o 

C_DEPS += \
./test/hw/unity/src/unity.d 


# Each subdirectory must supply rules for building sources it contributes
test/hw/unity/src/%.o test/hw/unity/src/%.su test/hw/unity/src/%.cyclo: ../test/hw/unity/src/%.c test/hw/unity/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../USB_HOST/App -I../USB_HOST/Target -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/worbb/Desktop/Electronics/SEMP/sempspace/p3_vibrationsensor_tests/test/hw/unity/src" -I"C:/Users/worbb/Desktop/Electronics/SEMP/sempspace/p3_vibrationsensor_tests/Components" -I"C:/Users/worbb/Desktop/Electronics/SEMP/sempspace/p3_vibrationsensor_tests/STM32F411E-Discovery" -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Middlewares/ST/ARM/DSP/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-test-2f-hw-2f-unity-2f-src

clean-test-2f-hw-2f-unity-2f-src:
	-$(RM) ./test/hw/unity/src/unity.cyclo ./test/hw/unity/src/unity.d ./test/hw/unity/src/unity.o ./test/hw/unity/src/unity.su

.PHONY: clean-test-2f-hw-2f-unity-2f-src

