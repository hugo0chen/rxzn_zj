################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CC1101.cpp \
../flash.cpp \
../main.cpp \
../net_intf_transceive.cpp \
../process.cpp \
../rf_receive.cpp \
../spi.cpp \
../timer_a.cpp 

CMD_SRCS += \
../lnk_msp430f2272.cmd 

CPP_DEPS += \
./CC1101.pp \
./flash.pp \
./main.pp \
./net_intf_transceive.pp \
./process.pp \
./rf_receive.pp \
./spi.pp \
./timer_a.pp 

OBJS += \
./CC1101.obj \
./flash.obj \
./main.obj \
./net_intf_transceive.obj \
./process.obj \
./rf_receive.obj \
./spi.obj \
./timer_a.obj 

OBJS__QTD += \
".\CC1101.obj" \
".\flash.obj" \
".\main.obj" \
".\net_intf_transceive.obj" \
".\process.obj" \
".\rf_receive.obj" \
".\spi.obj" \
".\timer_a.obj" 

CPP_DEPS__QTD += \
".\CC1101.pp" \
".\flash.pp" \
".\main.pp" \
".\net_intf_transceive.pp" \
".\process.pp" \
".\rf_receive.pp" \
".\spi.pp" \
".\timer_a.pp" 

CPP_SRCS_QUOTED += \
"../CC1101.cpp" \
"../flash.cpp" \
"../main.cpp" \
"../net_intf_transceive.cpp" \
"../process.cpp" \
"../rf_receive.cpp" \
"../spi.cpp" \
"../timer_a.cpp" 


# Each subdirectory must supply rules for building sources it contributes
CC1101.obj: ../CC1101.cpp $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/ccsv4/tools/compiler/msp430/bin/cl430" -vmsp -g --define=__MSP430F2272__ --include_path="D:/ccsv4/msp430/include" --include_path="D:/ccsv4/tools/compiler/msp430/include" --include_path="../../shared/include" --diag_warning=225 --printf_support=minimal --preproc_with_compile --preproc_dependency="CC1101.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

flash.obj: ../flash.cpp $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/ccsv4/tools/compiler/msp430/bin/cl430" -vmsp -g --define=__MSP430F2272__ --include_path="D:/ccsv4/msp430/include" --include_path="D:/ccsv4/tools/compiler/msp430/include" --include_path="../../shared/include" --diag_warning=225 --printf_support=minimal --preproc_with_compile --preproc_dependency="flash.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

main.obj: ../main.cpp $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/ccsv4/tools/compiler/msp430/bin/cl430" -vmsp -g --define=__MSP430F2272__ --include_path="D:/ccsv4/msp430/include" --include_path="D:/ccsv4/tools/compiler/msp430/include" --include_path="../../shared/include" --diag_warning=225 --printf_support=minimal --preproc_with_compile --preproc_dependency="main.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

net_intf_transceive.obj: ../net_intf_transceive.cpp $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/ccsv4/tools/compiler/msp430/bin/cl430" -vmsp -g --define=__MSP430F2272__ --include_path="D:/ccsv4/msp430/include" --include_path="D:/ccsv4/tools/compiler/msp430/include" --include_path="../../shared/include" --diag_warning=225 --printf_support=minimal --preproc_with_compile --preproc_dependency="net_intf_transceive.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

process.obj: ../process.cpp $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/ccsv4/tools/compiler/msp430/bin/cl430" -vmsp -g --define=__MSP430F2272__ --include_path="D:/ccsv4/msp430/include" --include_path="D:/ccsv4/tools/compiler/msp430/include" --include_path="../../shared/include" --diag_warning=225 --printf_support=minimal --preproc_with_compile --preproc_dependency="process.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

rf_receive.obj: ../rf_receive.cpp $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/ccsv4/tools/compiler/msp430/bin/cl430" -vmsp -g --define=__MSP430F2272__ --include_path="D:/ccsv4/msp430/include" --include_path="D:/ccsv4/tools/compiler/msp430/include" --include_path="../../shared/include" --diag_warning=225 --printf_support=minimal --preproc_with_compile --preproc_dependency="rf_receive.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

spi.obj: ../spi.cpp $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/ccsv4/tools/compiler/msp430/bin/cl430" -vmsp -g --define=__MSP430F2272__ --include_path="D:/ccsv4/msp430/include" --include_path="D:/ccsv4/tools/compiler/msp430/include" --include_path="../../shared/include" --diag_warning=225 --printf_support=minimal --preproc_with_compile --preproc_dependency="spi.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

timer_a.obj: ../timer_a.cpp $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/ccsv4/tools/compiler/msp430/bin/cl430" -vmsp -g --define=__MSP430F2272__ --include_path="D:/ccsv4/msp430/include" --include_path="D:/ccsv4/tools/compiler/msp430/include" --include_path="../../shared/include" --diag_warning=225 --printf_support=minimal --preproc_with_compile --preproc_dependency="timer_a.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '


