################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Src/libnrf24l01/subdir.mk
-include Src/blueProbe/target/subdir.mk
-include Src/blueProbe/platforms/stm32/subdir.mk
-include Src/blueProbe/platforms/native/subdir.mk
-include Src/blueProbe/platforms/common/subdir.mk
-include Src/blueProbe/subdir.mk
-include Src/subdir.mk
-include Drivers/STM32F1xx_LL_Driver/Src/subdir.mk
-include Drivers/STM32F1xx_HAL_Driver/Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
blueProbe.bin \

SECONDARY_SIZE += \
blueProbe.siz \


# All Target
all: blueProbe.elf secondary-outputs

# Tool invocations
blueProbe.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross ARM C Linker'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mlittle-endian -O3 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wno-unused  -g3 -T "/mnt/Data/Documents/workspace/blueProbe/STM32F103RBTx_FLASH.ld" -Xlinker --gc-sections -Wl,-Map,"blueProbe.map" -o "blueProbe.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

blueProbe.bin: blueProbe.elf
	@echo 'Invoking: Cross ARM GNU Create Flash Image'
	arm-none-eabi-objcopy -O binary "blueProbe.elf"  "blueProbe.bin"
	@echo 'Finished building: $@'
	@echo ' '

blueProbe.siz: blueProbe.elf
	@echo 'Invoking: Cross ARM GNU Print Size'
	arm-none-eabi-size --format=berkeley "blueProbe.elf"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(SECONDARY_FLASH)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_DEPS)$(S_UPPER_DEPS)$(C_DEPS) blueProbe.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets
