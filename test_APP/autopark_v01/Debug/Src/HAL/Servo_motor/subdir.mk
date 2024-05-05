################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/HAL/Servo_motor/Servo_motor_program.c 

OBJS += \
./Src/HAL/Servo_motor/Servo_motor_program.o 

C_DEPS += \
./Src/HAL/Servo_motor/Servo_motor_program.d 


# Each subdirectory must supply rules for building sources it contributes
Src/HAL/Servo_motor/%.o Src/HAL/Servo_motor/%.su Src/HAL/Servo_motor/%.cyclo: ../Src/HAL/Servo_motor/%.c Src/HAL/Servo_motor/subdir.mk
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F401RCTx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-HAL-2f-Servo_motor

clean-Src-2f-HAL-2f-Servo_motor:
	-$(RM) ./Src/HAL/Servo_motor/Servo_motor_program.cyclo ./Src/HAL/Servo_motor/Servo_motor_program.d ./Src/HAL/Servo_motor/Servo_motor_program.o ./Src/HAL/Servo_motor/Servo_motor_program.su

.PHONY: clean-Src-2f-HAL-2f-Servo_motor

