################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/HAL/PushB/PushB_program.c 

OBJS += \
./Src/HAL/PushB/PushB_program.o 

C_DEPS += \
./Src/HAL/PushB/PushB_program.d 


# Each subdirectory must supply rules for building sources it contributes
Src/HAL/PushB/%.o Src/HAL/PushB/%.su Src/HAL/PushB/%.cyclo: ../Src/HAL/PushB/%.c Src/HAL/PushB/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F401RCTx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-HAL-2f-PushB

clean-Src-2f-HAL-2f-PushB:
	-$(RM) ./Src/HAL/PushB/PushB_program.cyclo ./Src/HAL/PushB/PushB_program.d ./Src/HAL/PushB/PushB_program.o ./Src/HAL/PushB/PushB_program.su

.PHONY: clean-Src-2f-HAL-2f-PushB

