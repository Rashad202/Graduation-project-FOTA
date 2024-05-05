################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/HAL/HMOTOR/HMOTOR.c 

OBJS += \
./Src/HAL/HMOTOR/HMOTOR.o 

C_DEPS += \
./Src/HAL/HMOTOR/HMOTOR.d 


# Each subdirectory must supply rules for building sources it contributes
Src/HAL/HMOTOR/%.o Src/HAL/HMOTOR/%.su Src/HAL/HMOTOR/%.cyclo: ../Src/HAL/HMOTOR/%.c Src/HAL/HMOTOR/subdir.mk
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F401RCTx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-HAL-2f-HMOTOR

clean-Src-2f-HAL-2f-HMOTOR:
	-$(RM) ./Src/HAL/HMOTOR/HMOTOR.cyclo ./Src/HAL/HMOTOR/HMOTOR.d ./Src/HAL/HMOTOR/HMOTOR.o ./Src/HAL/HMOTOR/HMOTOR.su

.PHONY: clean-Src-2f-HAL-2f-HMOTOR

