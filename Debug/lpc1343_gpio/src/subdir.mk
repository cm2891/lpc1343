################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lpc1343_gpio/src/gpio.c 

OBJS += \
./lpc1343_gpio/src/gpio.o 

C_DEPS += \
./lpc1343_gpio/src/gpio.d 


# Each subdirectory must supply rules for building sources it contributes
lpc1343_gpio/src/%.o: ../lpc1343_gpio/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__USE_LPCOPEN -D__LPC13XX__ -D__REDLIB__ -I"C:\Users\chris\Documents\MCUXpressoIDE_11.1.1_3241\workspace\lpc_board_nxp_lpcxpresso_1343\inc" -I"C:\Users\chris\Documents\MCUXpressoIDE_11.1.1_3241\workspace\lpc_chip_13xx\inc" -I"C:\Users\chris\Documents\MCUXpressoIDE_11.1.1_3241\workspace\lpc1343\lpc1343_timer\inc" -I"C:\Users\chris\Documents\MCUXpressoIDE_11.1.1_3241\workspace\lpc1343\lpc1343_gpio\inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m3 -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


