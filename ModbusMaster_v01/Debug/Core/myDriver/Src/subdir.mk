################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/myDriver/Src/RingBuffer.c \
../Core/myDriver/Src/uart_ex.c \
../Core/myDriver/Src/uart_qrbcom.c 

OBJS += \
./Core/myDriver/Src/RingBuffer.o \
./Core/myDriver/Src/uart_ex.o \
./Core/myDriver/Src/uart_qrbcom.o 

C_DEPS += \
./Core/myDriver/Src/RingBuffer.d \
./Core/myDriver/Src/uart_ex.d \
./Core/myDriver/Src/uart_qrbcom.d 


# Each subdirectory must supply rules for building sources it contributes
Core/myDriver/Src/%.o Core/myDriver/Src/%.su Core/myDriver/Src/%.cyclo: ../Core/myDriver/Src/%.c Core/myDriver/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F439xx -c -I../Core/Inc -I"D:/workspace_udemy/ModbusMaster_v01/Core/myDriver/modbus_ex/Inc" -I"D:/workspace_udemy/ModbusMaster_v01/Core/myDriver/Timer_Ex/Inc" -I"D:/workspace_udemy/ModbusMaster_v01/Core/myDriver/Inc" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-myDriver-2f-Src

clean-Core-2f-myDriver-2f-Src:
	-$(RM) ./Core/myDriver/Src/RingBuffer.cyclo ./Core/myDriver/Src/RingBuffer.d ./Core/myDriver/Src/RingBuffer.o ./Core/myDriver/Src/RingBuffer.su ./Core/myDriver/Src/uart_ex.cyclo ./Core/myDriver/Src/uart_ex.d ./Core/myDriver/Src/uart_ex.o ./Core/myDriver/Src/uart_ex.su ./Core/myDriver/Src/uart_qrbcom.cyclo ./Core/myDriver/Src/uart_qrbcom.d ./Core/myDriver/Src/uart_qrbcom.o ./Core/myDriver/Src/uart_qrbcom.su

.PHONY: clean-Core-2f-myDriver-2f-Src

