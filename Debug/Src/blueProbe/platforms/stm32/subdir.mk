################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/blueProbe/platforms/stm32/gdb_if.c \
../Src/blueProbe/platforms/stm32/jtagtap.c \
../Src/blueProbe/platforms/stm32/serialno.c \
../Src/blueProbe/platforms/stm32/timing_stm32.c \
../Src/blueProbe/platforms/stm32/traceswo.c 

OBJS += \
./Src/blueProbe/platforms/stm32/gdb_if.o \
./Src/blueProbe/platforms/stm32/jtagtap.o \
./Src/blueProbe/platforms/stm32/serialno.o \
./Src/blueProbe/platforms/stm32/timing_stm32.o \
./Src/blueProbe/platforms/stm32/traceswo.o 

C_DEPS += \
./Src/blueProbe/platforms/stm32/gdb_if.d \
./Src/blueProbe/platforms/stm32/jtagtap.d \
./Src/blueProbe/platforms/stm32/serialno.d \
./Src/blueProbe/platforms/stm32/timing_stm32.d \
./Src/blueProbe/platforms/stm32/traceswo.d 


# Each subdirectory must supply rules for building sources it contributes
Src/blueProbe/platforms/stm32/%.o: ../Src/blueProbe/platforms/stm32/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mlittle-endian -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O3 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wno-unused  -g -DUSE_FULL_LL_DRIVER -DUSE_HAL_DRIVER -DSTM32L432xx -I"/mnt/Data/Documents/workspace/blueProbe/Inc/blueProbe" -I"/mnt/Data/Documents/workspace/blueProbe/Inc/blueProbe/target" -I"/mnt/Data/Documents/workspace/blueProbe/Inc/blueProbe/platforms/common" -I"/mnt/Data/Documents/workspace/blueProbe/Inc/blueProbe/platforms/native" -I"/mnt/Data/Documents/workspace/blueProbe/Inc/blueProbe/platforms/stm32" -I"/mnt/Data/Documents/workspace/blueProbe/Inc/blueProbe/target/flashstub" -I"/mnt/Data/Documents/workspace/blueProbe/Inc/libnrf24l01" -I"/mnt/Data/Documents/workspace/blueProbe/Drivers/CMSIS/Include" -I"/mnt/Data/Documents/workspace/blueProbe/Drivers/CMSIS/Device/ST/STM32L4xx/Include" -I"/mnt/Data/Documents/workspace/blueProbe/Drivers/STM32L4xx_HAL_Driver/Inc" -I"/mnt/Data/Documents/workspace/blueProbe/Inc" -I"/mnt/Data/Documents/workspace/blueProbe/Inc/blueProbe" -I"/mnt/Data/Documents/workspace/blueProbe/Inc/libnrf24l01" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


