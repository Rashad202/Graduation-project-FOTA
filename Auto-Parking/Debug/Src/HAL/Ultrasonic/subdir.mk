################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/HAL/Ultrasonic/Ultrasonic_program.c 

OBJS += \
./Src/HAL/Ultrasonic/Ultrasonic_program.o 

C_DEPS += \
./Src/HAL/Ultrasonic/Ultrasonic_program.d 


# Each subdirectory must supply rules for building sources it contributes
Src/HAL/Ultrasonic/%.o Src/HAL/Ultrasonic/%.su Src/HAL/Ultrasonic/%.cyclo: ../Src/HAL/Ultrasonic/%.c Src/HAL/Ultrasonic/subdir.mk
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F401RCTx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-HAL-2f-Ultrasonic

clean-Src-2f-HAL-2f-Ultrasonic:
	-$(RM) ./Src/HAL/Ultrasonic/Ultrasonic_program.cyclo ./Src/HAL/Ultrasonic/Ultrasonic_program.d ./Src/HAL/Ultrasonic/Ultrasonic_program.o ./Src/HAL/Ultrasonic/Ultrasonic_program.su

.PHONY: clean-Src-2f-HAL-2f-Ultrasonic
