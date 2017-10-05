################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/blueProbe/command.c \
../Src/blueProbe/crc32.c \
../Src/blueProbe/exception.c \
../Src/blueProbe/gdb_hostio.c \
../Src/blueProbe/gdb_main.c \
../Src/blueProbe/gdb_packet.c \
../Src/blueProbe/hex_utils.c \
../Src/blueProbe/morse.c 

OBJS += \
./Src/blueProbe/command.o \
./Src/blueProbe/crc32.o \
./Src/blueProbe/exception.o \
./Src/blueProbe/gdb_hostio.o \
./Src/blueProbe/gdb_main.o \
./Src/blueProbe/gdb_packet.o \
./Src/blueProbe/hex_utils.o \
./Src/blueProbe/morse.o 

C_DEPS += \
./Src/blueProbe/command.d \
./Src/blueProbe/crc32.d \
./Src/blueProbe/exception.d \
./Src/blueProbe/gdb_hostio.d \
./Src/blueProbe/gdb_main.d \
./Src/blueProbe/gdb_packet.d \
./Src/blueProbe/hex_utils.d \
./Src/blueProbe/morse.d 


# Each subdirectory must supply rules for building sources it contributes
Src/blueProbe/%.o: ../Src/blueProbe/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mlittle-endian -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O3 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wno-unused  -g -DUSE_FULL_LL_DRIVER -DUSE_HAL_DRIVER -DSTM32L432xx -I"/mnt/Data/Documents/workspace/blueProbe/Inc/blueProbe" -I"/mnt/Data/Documents/workspace/blueProbe/Inc/blueProbe/target" -I"/mnt/Data/Documents/workspace/blueProbe/Inc/blueProbe/platforms/common" -I"/mnt/Data/Documents/workspace/blueProbe/Inc/blueProbe/platforms/native" -I"/mnt/Data/Documents/workspace/blueProbe/Inc/blueProbe/platforms/stm32" -I"/mnt/Data/Documents/workspace/blueProbe/Inc/blueProbe/target/flashstub" -I"/mnt/Data/Documents/workspace/blueProbe/Inc/libnrf24l01" -I"/mnt/Data/Documents/workspace/blueProbe/Drivers/CMSIS/Include" -I"/mnt/Data/Documents/workspace/blueProbe/Drivers/CMSIS/Device/ST/STM32L4xx/Include" -I"/mnt/Data/Documents/workspace/blueProbe/Drivers/STM32L4xx_HAL_Driver/Inc" -I"/mnt/Data/Documents/workspace/blueProbe/Inc" -I"/mnt/Data/Documents/workspace/blueProbe/Inc/blueProbe" -I"/mnt/Data/Documents/workspace/blueProbe/Inc/libnrf24l01" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


