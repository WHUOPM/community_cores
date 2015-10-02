################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/CoeurCommunaute.cpp \
../src/Digraph.cpp \
../src/Edge.cpp \
../src/EdgeWeight.cpp \
../src/nodeDeg.cpp \
../src/Triangles.cpp \
../src/CoeurCommunaute-Old.cpp 

OBJS += \
./src/CoeurCommunaute.o \
./src/Digraph.o \
./src/Edge.o \
./src/EdgeWeight.o \
./src/nodeDeg.o 

OBJS_T += \
./src/Triangles.o \
./src/Digraph.o \
./src/Edge.o \
./src/EdgeWeight.o \
./src/nodeDeg.o

OBJS_O += \
./src/CoeurCommunaute-Old.o \
./src/Digraph.o \
./src/Edge.o \
./src/EdgeWeight.o \
./src/nodeDeg.o

CPP_DEPS += \
./src/CoeurCommunaute.d \
./src/Digraph.d \
./src/Edge.d \
./src/EdgeWeight.d \
./src/nodeDeg.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -std=c++0x -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


