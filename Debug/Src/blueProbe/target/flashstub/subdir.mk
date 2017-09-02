################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/blueProbe/target/flashstub/efm32.c \
../Src/blueProbe/target/flashstub/nrf51.c \
../Src/blueProbe/target/flashstub/stm32f1.c \
../Src/blueProbe/target/flashstub/stm32f4_x32.c \
../Src/blueProbe/target/flashstub/stm32f4_x8.c \
../Src/blueProbe/target/flashstub/stm32l4.c 

OBJS += \
./Src/blueProbe/target/flashstub/efm32.o \
./Src/blueProbe/target/flashstub/nrf51.o \
./Src/blueProbe/target/flashstub/stm32f1.o \
./Src/blueProbe/target/flashstub/stm32f4_x32.o \
./Src/blueProbe/target/flashstub/stm32f4_x8.o \
./Src/blueProbe/target/flashstub/stm32l4.o 

C_DEPS += \
./Src/blueProbe/target/flashstub/efm32.d \
./Src/blueProbe/target/flashstub/nrf51.d \
./Src/blueProbe/target/flashstub/stm32f1.d \
./Src/blueProbe/target/flashstub/stm32f4_x32.d \
./Src/blueProbe/target/flashstub/stm32f4_x8.d \
./Src/blueProbe/target/flashstub/stm32l4.d 


# Each subdirectory must supply rules for building sources it contributes
Src/blueProbe/target/flashstub/%.o: ../Src/blueProbe/target/flashstub/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mlittle-endian -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wno-unused  -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -I"/mnt/Data/Documents/workspace/blueProbe/Inc/blueProbe" -I"/mnt/Data/Documents/workspace/blueProbe/Inc/blueProbe/target" -I"/mnt/Data/Documents/workspace/blueProbe/Inc/blueProbe/platforms/common" -I"/mnt/Data/Documents/workspace/blueProbe/Inc/blueProbe/platforms/native" -I"/mnt/Data/Documents/workspace/blueProbe/Inc/blueProbe/platforms/stm32" -I"/mnt/Data/Documents/workspace/blueProbe/Inc/blueProbe/target/flashstub" -I"/mnt/Data/Documents/workspace/blueProbe/Inc/libnrf24l01" -I"/mnt/Data/Documents/workspace/blueProbe/Drivers/CMSIS/Include" -I"/mnt/Data/Documents/workspace/blueProbe/Drivers/CMSIS/Device/ST/STM32F1xx/Include" -I"/mnt/Data/Documents/workspace/blueProbe/Drivers/STM32F1xx_HAL_Driver/Inc" -I"/mnt/Data/Documents/workspace/blueProbe/Drivers/STM32F1xx_LL_Driver/Inc" -I"/mnt/Data/Documents/workspace/blueProbe/Inc" -I"/mnt/Data/Documents/workspace/blueProbe/Inc/blueProbe" -I"/mnt/Data/Documents/workspace/blueProbe/Inc/libnrf24l01" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


