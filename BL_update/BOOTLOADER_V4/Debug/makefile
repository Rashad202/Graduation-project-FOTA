################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Src/MCAL/MUSART/subdir.mk
-include Src/MCAL/MSTK/subdir.mk
-include Src/MCAL/MRCC/subdir.mk
-include Src/MCAL/MNVIC/subdir.mk
-include Src/MCAL/MGPIO/subdir.mk
-include Src/MCAL/MFMI/subdir.mk
-include Src/MCAL/MEXTI/subdir.mk
-include Src/HAL/PushB/subdir.mk
-include Src/HAL/LED/subdir.mk
-include Src/APP/HexParser/subdir.mk
-include Src/APP/BootLoader/subdir.mk
-include Src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
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

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := BOOTLOADER_V4
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
BOOTLOADER_V4.elf \

MAP_FILES += \
BOOTLOADER_V4.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
BOOTLOADER_V4.list \

OBJCOPY_HEX += \
BOOTLOADER_V4.hex \


# All Target
all: main-build

# Main-build Target
main-build: BOOTLOADER_V4.elf secondary-outputs

# Tool invocations
BOOTLOADER_V4.elf BOOTLOADER_V4.map: $(OBJS) $(USER_OBJS) D:\GP\black\ pill\projects\test_0\BOOTLOADER_V4\STM32F401RCTX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "BOOTLOADER_V4.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"D:\GP\black pill\projects\test_0\BOOTLOADER_V4\STM32F401RCTX_FLASH.ld" --specs=nosys.specs -Wl,-Map="BOOTLOADER_V4.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

BOOTLOADER_V4.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "BOOTLOADER_V4.list"
	@echo 'Finished building: $@'
	@echo ' '

BOOTLOADER_V4.hex: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "BOOTLOADER_V4.hex"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) BOOTLOADER_V4.elf BOOTLOADER_V4.hex BOOTLOADER_V4.list BOOTLOADER_V4.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_HEX)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
