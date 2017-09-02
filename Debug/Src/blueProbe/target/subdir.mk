################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/blueProbe/target/adiv5.c \
../Src/blueProbe/target/adiv5_jtagdp.c \
../Src/blueProbe/target/adiv5_swdp.c \
../Src/blueProbe/target/cortexa.c \
../Src/blueProbe/target/cortexm.c \
../Src/blueProbe/target/efm32.c \
../Src/blueProbe/target/jtag_scan.c \
../Src/blueProbe/target/jtagtap_generic.c \
../Src/blueProbe/target/kinetis.c \
../Src/blueProbe/target/lmi.c \
../Src/blueProbe/target/lpc11xx.c \
../Src/blueProbe/target/lpc15xx.c \
../Src/blueProbe/target/lpc43xx.c \
../Src/blueProbe/target/lpc_common.c \
../Src/blueProbe/target/nrf51.c \
../Src/blueProbe/target/sam3x.c \
../Src/blueProbe/target/sam4l.c \
../Src/blueProbe/target/samd.c \
../Src/blueProbe/target/stm32f1.c \
../Src/blueProbe/target/stm32f4.c \
../Src/blueProbe/target/stm32l0.c \
../Src/blueProbe/target/stm32l4.c \
../Src/blueProbe/target/swdptap_generic.c \
../Src/blueProbe/target/target.c 

OBJS += \
./Src/blueProbe/target/adiv5.o \
./Src/blueProbe/target/adiv5_jtagdp.o \
./Src/blueProbe/target/adiv5_swdp.o \
./Src/blueProbe/target/cortexa.o \
./Src/blueProbe/target/cortexm.o \
./Src/blueProbe/target/efm32.o \
./Src/blueProbe/target/jtag_scan.o \
./Src/blueProbe/target/jtagtap_generic.o \
./Src/blueProbe/target/kinetis.o \
./Src/blueProbe/target/lmi.o \
./Src/blueProbe/target/lpc11xx.o \
./Src/blueProbe/target/lpc15xx.o \
./Src/blueProbe/target/lpc43xx.o \
./Src/blueProbe/target/lpc_common.o \
./Src/blueProbe/target/nrf51.o \
./Src/blueProbe/target/sam3x.o \
./Src/blueProbe/target/sam4l.o \
./Src/blueProbe/target/samd.o \
./Src/blueProbe/target/stm32f1.o \
./Src/blueProbe/target/stm32f4.o \
./Src/blueProbe/target/stm32l0.o \
./Src/blueProbe/target/stm32l4.o \
./Src/blueProbe/target/swdptap_generic.o \
./Src/blueProbe/target/target.o 

C_DEPS += \
./Src/blueProbe/target/adiv5.d \
./Src/blueProbe/target/adiv5_jtagdp.d \
./Src/blueProbe/target/adiv5_swdp.d \
./Src/blueProbe/target/cortexa.d \
./Src/blueProbe/target/cortexm.d \
./Src/blueProbe/target/efm32.d \
./Src/blueProbe/target/jtag_scan.d \
./Src/blueProbe/target/jtagtap_generic.d \
./Src/blueProbe/target/kinetis.d \
./Src/blueProbe/target/lmi.d \
./Src/blueProbe/target/lpc11xx.d \
./Src/blueProbe/target/lpc15xx.d \
./Src/blueProbe/target/lpc43xx.d \
./Src/blueProbe/target/lpc_common.d \
./Src/blueProbe/target/nrf51.d \
./Src/blueProbe/target/sam3x.d \
./Src/blueProbe/target/sam4l.d \
./Src/blueProbe/target/samd.d \
./Src/blueProbe/target/stm32f1.d \
./Src/blueProbe/target/stm32f4.d \
./Src/blueProbe/target/stm32l0.d \
./Src/blueProbe/target/stm32l4.d \
./Src/blueProbe/target/swdptap_generic.d \
./Src/blueProbe/target/target.d 


# Each subdirectory must supply rules for building sources it contributes
Src/blueProbe/target/%.o: ../Src/blueProbe/target/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mlittle-endian -O3 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wno-unused  -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -I"/mnt/Data/Documents/workspace/blueProbe/Inc/blueProbe" -I"/mnt/Data/Documents/workspace/blueProbe/Inc/blueProbe/target" -I"/mnt/Data/Documents/workspace/blueProbe/Inc/blueProbe/platforms/common" -I"/mnt/Data/Documents/workspace/blueProbe/Inc/blueProbe/platforms/native" -I"/mnt/Data/Documents/workspace/blueProbe/Inc/blueProbe/platforms/stm32" -I"/mnt/Data/Documents/workspace/blueProbe/Inc/blueProbe/target/flashstub" -I"/mnt/Data/Documents/workspace/blueProbe/Inc/libnrf24l01" -I"/mnt/Data/Documents/workspace/blueProbe/Drivers/CMSIS/Include" -I"/mnt/Data/Documents/workspace/blueProbe/Drivers/CMSIS/Device/ST/STM32F1xx/Include" -I"/mnt/Data/Documents/workspace/blueProbe/Drivers/STM32F1xx_HAL_Driver/Inc" -I"/mnt/Data/Documents/workspace/blueProbe/Drivers/STM32F1xx_LL_Driver/Inc" -I"/mnt/Data/Documents/workspace/blueProbe/Inc" -I"/mnt/Data/Documents/workspace/blueProbe/Inc/blueProbe" -I"/mnt/Data/Documents/workspace/blueProbe/Inc/libnrf24l01" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


