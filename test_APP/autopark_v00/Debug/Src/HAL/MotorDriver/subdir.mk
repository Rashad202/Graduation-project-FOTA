################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/HAL/MotorDriver/MotorDriver_program.c 

OBJS += \
./Src/HAL/MotorDriver/MotorDriver_program.o 

C_DEPS += \
./Src/HAL/MotorDriver/MotorDriver_program.d 


# Each subdirectory must supply rules for building sources it contributes
Src/HAL/MotorDriver/%.o Src/HAL/MotorDriver/%.su Src/HAL/MotorDriver/%.cyclo: ../Src/HAL/MotorDriver/%.c Src/HAL/MotorDriver/subdir.mk
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F401RCTx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-HAL-2f-MotorDriver

clean-Src-2f-HAL-2f-MotorDriver:
	-$(RM) ./Src/HAL/MotorDriver/MotorDriver_program.cyclo ./Src/HAL/MotorDriver/MotorDriver_program.d ./Src/HAL/MotorDriver/MotorDriver_program.o ./Src/HAL/MotorDriver/MotorDriver_program.su

.PHONY: clean-Src-2f-HAL-2f-MotorDriver

