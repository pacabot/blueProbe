################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/libnrf24l01/nrf24l01.c \
../Src/libnrf24l01/nrf24l01_hw_stm32.c \
../Src/libnrf24l01/nrf24l01_regs.c 

OBJS += \
./Src/libnrf24l01/nrf24l01.o \
./Src/libnrf24l01/nrf24l01_hw_stm32.o \
./Src/libnrf24l01/nrf24l01_regs.o 

C_DEPS += \
./Src/libnrf24l01/nrf24l01.d \
./Src/libnrf24l01/nrf24l01_hw_stm32.d \
./Src/libnrf24l01/nrf24l01_regs.d 


# Each subdirectory must supply rules for building sources it contributes
Src/libnrf24l01/%.o: ../Src/libnrf24l01/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mlittle-endian -O3 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wno-unused  -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -I"/mnt/Data/Documents/workspace/blueProbe/Inc/blueProbe" -I"/mnt/Data/Documents/workspace/blueProbe/Inc/blueProbe/target" -I"/mnt/Data/Documents/workspace/blueProbe/Inc/blueProbe/platforms/common" -I"/mnt/Data/Documents/workspace/blueProbe/Inc/blueProbe/platforms/native" -I"/mnt/Data/Documents/workspace/blueProbe/Inc/blueProbe/platforms/stm32" -I"/mnt/Data/Documents/workspace/blueProbe/Inc/blueProbe/target/flashstub" -I"/mnt/Data/Documents/workspace/blueProbe/Inc/libnrf24l01" -I"/mnt/Data/Documents/workspace/blueProbe/Drivers/CMSIS/Include" -I"/mnt/Data/Documents/workspace/blueProbe/Drivers/CMSIS/Device/ST/STM32F1xx/Include" -I"/mnt/Data/Documents/workspace/blueProbe/Drivers/STM32F1xx_HAL_Driver/Inc" -I"/mnt/Data/Documents/workspace/blueProbe/Drivers/STM32F1xx_LL_Driver/Inc" -I"/mnt/Data/Documents/workspace/blueProbe/Inc" -I"/mnt/Data/Documents/workspace/blueProbe/Inc/blueProbe" -I"/mnt/Data/Documents/workspace/blueProbe/Inc/libnrf24l01" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


