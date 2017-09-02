################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/adc.c \
../Src/crc.c \
../Src/gpio.c \
../Src/main.c \
../Src/stm32f1xx_hal_msp.c \
../Src/stm32f1xx_it.c \
../Src/syscalls.c \
../Src/system_stm32f1xx.c \
../Src/usart.c 

OBJS += \
./Src/adc.o \
./Src/crc.o \
./Src/gpio.o \
./Src/main.o \
./Src/stm32f1xx_hal_msp.o \
./Src/stm32f1xx_it.o \
./Src/syscalls.o \
./Src/system_stm32f1xx.o \
./Src/usart.o 

C_DEPS += \
./Src/adc.d \
./Src/crc.d \
./Src/gpio.d \
./Src/main.d \
./Src/stm32f1xx_hal_msp.d \
./Src/stm32f1xx_it.d \
./Src/syscalls.d \
./Src/system_stm32f1xx.d \
./Src/usart.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mlittle-endian -O3 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wno-unused  -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -I"/mnt/Data/Documents/workspace/blueProbe/Inc/blueProbe" -I"/mnt/Data/Documents/workspace/blueProbe/Inc/blueProbe/target" -I"/mnt/Data/Documents/workspace/blueProbe/Inc/blueProbe/platforms/common" -I"/mnt/Data/Documents/workspace/blueProbe/Inc/blueProbe/platforms/native" -I"/mnt/Data/Documents/workspace/blueProbe/Inc/blueProbe/platforms/stm32" -I"/mnt/Data/Documents/workspace/blueProbe/Inc/blueProbe/target/flashstub" -I"/mnt/Data/Documents/workspace/blueProbe/Inc/libnrf24l01" -I"/mnt/Data/Documents/workspace/blueProbe/Drivers/CMSIS/Include" -I"/mnt/Data/Documents/workspace/blueProbe/Drivers/CMSIS/Device/ST/STM32F1xx/Include" -I"/mnt/Data/Documents/workspace/blueProbe/Drivers/STM32F1xx_HAL_Driver/Inc" -I"/mnt/Data/Documents/workspace/blueProbe/Drivers/STM32F1xx_LL_Driver/Inc" -I"/mnt/Data/Documents/workspace/blueProbe/Inc" -I"/mnt/Data/Documents/workspace/blueProbe/Inc/blueProbe" -I"/mnt/Data/Documents/workspace/blueProbe/Inc/libnrf24l01" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


