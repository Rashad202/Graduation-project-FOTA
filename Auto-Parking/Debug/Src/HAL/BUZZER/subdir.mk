################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/HAL/BUZZER/BUZZER_program.c 

OBJS += \
./Src/HAL/BUZZER/BUZZER_program.o 

C_DEPS += \
./Src/HAL/BUZZER/BUZZER_program.d 


# Each subdirectory must supply rules for building sources it contributes
Src/HAL/BUZZER/%.o Src/HAL/BUZZER/%.su Src/HAL/BUZZER/%.cyclo: ../Src/HAL/BUZZER/%.c Src/HAL/BUZZER/subdir.mk
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F401RCTx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-HAL-2f-BUZZER

clean-Src-2f-HAL-2f-BUZZER:
	-$(RM) ./Src/HAL/BUZZER/BUZZER_program.cyclo ./Src/HAL/BUZZER/BUZZER_program.d ./Src/HAL/BUZZER/BUZZER_program.o ./Src/HAL/BUZZER/BUZZER_program.su

.PHONY: clean-Src-2f-HAL-2f-BUZZER

