################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/MCAL/MTIMER/MTIMER_program.c 

OBJS += \
./Src/MCAL/MTIMER/MTIMER_program.o 

C_DEPS += \
./Src/MCAL/MTIMER/MTIMER_program.d 


# Each subdirectory must supply rules for building sources it contributes
Src/MCAL/MTIMER/%.o Src/MCAL/MTIMER/%.su Src/MCAL/MTIMER/%.cyclo: ../Src/MCAL/MTIMER/%.c Src/MCAL/MTIMER/subdir.mk
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F401RCTx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-MCAL-2f-MTIMER

clean-Src-2f-MCAL-2f-MTIMER:
	-$(RM) ./Src/MCAL/MTIMER/MTIMER_program.cyclo ./Src/MCAL/MTIMER/MTIMER_program.d ./Src/MCAL/MTIMER/MTIMER_program.o ./Src/MCAL/MTIMER/MTIMER_program.su

.PHONY: clean-Src-2f-MCAL-2f-MTIMER

