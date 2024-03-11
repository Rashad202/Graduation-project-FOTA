################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/APP/BootLoader/BootLoader_program.c 

OBJS += \
./Src/APP/BootLoader/BootLoader_program.o 

C_DEPS += \
./Src/APP/BootLoader/BootLoader_program.d 


# Each subdirectory must supply rules for building sources it contributes
Src/APP/BootLoader/%.o Src/APP/BootLoader/%.su Src/APP/BootLoader/%.cyclo: ../Src/APP/BootLoader/%.c Src/APP/BootLoader/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F401RCTx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-APP-2f-BootLoader

clean-Src-2f-APP-2f-BootLoader:
	-$(RM) ./Src/APP/BootLoader/BootLoader_program.cyclo ./Src/APP/BootLoader/BootLoader_program.d ./Src/APP/BootLoader/BootLoader_program.o ./Src/APP/BootLoader/BootLoader_program.su

.PHONY: clean-Src-2f-APP-2f-BootLoader

