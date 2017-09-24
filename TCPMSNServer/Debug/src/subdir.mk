################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Broker.cpp \
../src/BrokerManager.cpp \
../src/Dispatcher.cpp \
../src/Server.cpp \
../src/TCPMSNServer.cpp 

OBJS += \
./src/Broker.o \
./src/BrokerManager.o \
./src/Dispatcher.o \
./src/Server.o \
./src/TCPMSNServer.o 

CPP_DEPS += \
./src/Broker.d \
./src/BrokerManager.d \
./src/Dispatcher.d \
./src/Server.d \
./src/TCPMSNServer.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/user/Desktop/lab10/SocketUtils/src" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


