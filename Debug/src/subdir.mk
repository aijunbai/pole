################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/logger.cpp \
../src/main.cpp \
../src/monte-carlo.cpp \
../src/pole.cpp \
../src/qlearning.cpp \
../src/system.cpp 

OBJS += \
./src/logger.o \
./src/main.o \
./src/monte-carlo.o \
./src/pole.o \
./src/qlearning.o \
./src/system.o 

CPP_DEPS += \
./src/logger.d \
./src/main.d \
./src/monte-carlo.d \
./src/pole.d \
./src/qlearning.d \
./src/system.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -W -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


