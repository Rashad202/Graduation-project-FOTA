################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/APP/HexParser/HexParser_program.c 

OBJS += \
./Src/APP/HexParser/HexParser_program.o 

C_DEPS += \
./Src/APP/HexParser/HexParser_program.d 


# Each subdirectory must supply rules for building sources it contributes
Src/APP/HexParser/%.o Src/APP/HexParser/%.su Src/APP/HexParser/%.cyclo: ../Src/APP/HexParser/%.c Src/APP/HexParser/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F401RCTx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-APP-2f-HexParser

clean-Src-2f-APP-2f-HexParser:
	-$(RM) ./Src/APP/HexParser/HexParser_program.cyclo ./Src/APP/HexParser/HexParser_program.d ./Src/APP/HexParser/HexParser_program.o ./Src/APP/HexParser/HexParser_program.su

.PHONY: clean-Src-2f-APP-2f-HexParser

