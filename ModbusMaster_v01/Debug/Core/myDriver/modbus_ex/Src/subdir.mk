################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/myDriver/modbus_ex/Src/modbus_crc16.c \
../Core/myDriver/modbus_ex/Src/modbus_ex.c 

OBJS += \
./Core/myDriver/modbus_ex/Src/modbus_crc16.o \
./Core/myDriver/modbus_ex/Src/modbus_ex.o 

C_DEPS += \
./Core/myDriver/modbus_ex/Src/modbus_crc16.d \
./Core/myDriver/modbus_ex/Src/modbus_ex.d 


# Each subdirectory must supply rules for building sources it contributes
Core/myDriver/modbus_ex/Src/%.o Core/myDriver/modbus_ex/Src/%.su Core/myDriver/modbus_ex/Src/%.cyclo: ../Core/myDriver/modbus_ex/Src/%.c Core/myDriver/modbus_ex/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F439xx -c -I../Core/Inc -I"D:/workspace_udemy/ModbusMaster_v01/Core/myDriver/modbus_ex/Inc" -I"D:/workspace_udemy/ModbusMaster_v01/Core/myDriver/Timer_Ex/Inc" -I"D:/workspace_udemy/ModbusMaster_v01/Core/myDriver/Inc" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-myDriver-2f-modbus_ex-2f-Src

clean-Core-2f-myDriver-2f-modbus_ex-2f-Src:
	-$(RM) ./Core/myDriver/modbus_ex/Src/modbus_crc16.cyclo ./Core/myDriver/modbus_ex/Src/modbus_crc16.d ./Core/myDriver/modbus_ex/Src/modbus_crc16.o ./Core/myDriver/modbus_ex/Src/modbus_crc16.su ./Core/myDriver/modbus_ex/Src/modbus_ex.cyclo ./Core/myDriver/modbus_ex/Src/modbus_ex.d ./Core/myDriver/modbus_ex/Src/modbus_ex.o ./Core/myDriver/modbus_ex/Src/modbus_ex.su

.PHONY: clean-Core-2f-myDriver-2f-modbus_ex-2f-Src

