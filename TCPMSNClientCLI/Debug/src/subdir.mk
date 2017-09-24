################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/CLIHandler.cpp \
../src/TCPMSNClientCLI.cpp 

OBJS += \
./src/CLIHandler.o \
./src/TCPMSNClientCLI.o 

CPP_DEPS += \
./src/CLIHandler.d \
./src/TCPMSNClientCLI.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/user/Desktop/lab10/TCPMSNClient/src" -I"/home/user/Desktop/lab10/SocketUtils/src" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


