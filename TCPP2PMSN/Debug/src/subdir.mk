################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/CLI.cpp \
../src/Handler.cpp \
../src/P2PClient.cpp \
../src/P2PServer.cpp \
../src/TCPP2PMSN.cpp 

OBJS += \
./src/CLI.o \
./src/Handler.o \
./src/P2PClient.o \
./src/P2PServer.o \
./src/TCPP2PMSN.o 

CPP_DEPS += \
./src/CLI.d \
./src/Handler.d \
./src/P2PClient.d \
./src/P2PServer.d \
./src/TCPP2PMSN.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/eontorch/NPLgit/SocketUtils/src" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


