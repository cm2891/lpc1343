################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/cr_startup_lpc13xx.c \
../src/crp.c \
../src/main.c \
../src/sysinit.c 

OBJS += \
./src/cr_startup_lpc13xx.o \
./src/crp.o \
./src/main.o \
./src/sysinit.o 

C_DEPS += \
./src/cr_startup_lpc13xx.d \
./src/crp.d \
./src/main.d \
./src/sysinit.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__USE_LPCOPEN -D__LPC13XX__ -D__REDLIB__ -I"C:\Users\chris\Documents\MCUXpressoIDE_11.1.1_3241\workspace\lpc_board_nxp_lpcxpresso_1343\inc" -I"C:\Users\chris\Documents\MCUXpressoIDE_11.1.1_3241\workspace\lpc_chip_13xx\inc" -I"C:\Users\chris\Documents\MCUXpressoIDE_11.1.1_3241\workspace\lpc1343\lpc1343_timer\inc" -I"C:\Users\chris\Documents\MCUXpressoIDE_11.1.1_3241\workspace\lpc1343\lpc1343_gpio\inc" -I"C:\Users\chris\Documents\MCUXpressoIDE_11.1.1_3241\workspace\lpc1343\lpc1343_uart\inc" -I"C:\Users\chris\Documents\MCUXpressoIDE_11.1.1_3241\workspace\lpc1343\lpc1343_i2c\inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m3 -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


