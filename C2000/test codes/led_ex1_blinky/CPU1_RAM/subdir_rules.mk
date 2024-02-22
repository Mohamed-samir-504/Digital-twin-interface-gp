################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1250/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --idiv_support=idiv0 --tmu_support=tmu0 -Ooff --include_path="D:/workc2000/led_ex1_blinky" --include_path="D:/C2000Ware_5_01_00_00" --include_path="C:/ti/ccs1250/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/include" --define=DEBUG --define=RAM --define=generic_ram_lnk --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" --include_path="D:/workc2000/led_ex1_blinky/CPU1_RAM/syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

build-1738275487: ../led_ex1_blinky.syscfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: SysConfig'
	"C:/ti/ccs1250/ccs/utils/sysconfig_1.18.0/sysconfig_cli.bat" -s "D:/C2000Ware_5_01_00_00/.metadata/sdk.json" --script "D:/workc2000/led_ex1_blinky/led_ex1_blinky.syscfg" -o "syscfg" --compiler ccs
	@echo 'Finished building: "$<"'
	@echo ' '

syscfg/board.c: build-1738275487 ../led_ex1_blinky.syscfg
syscfg/board.h: build-1738275487
syscfg/board.cmd.genlibs: build-1738275487
syscfg/board.opt: build-1738275487
syscfg/pinmux.csv: build-1738275487
syscfg/device.c: build-1738275487
syscfg/device.h: build-1738275487
syscfg/device_cmd.cmd: build-1738275487
syscfg/device_cmd.c: build-1738275487
syscfg/device_cmd.h: build-1738275487
syscfg/device_cmd.opt: build-1738275487
syscfg/device_cmd.cmd.genlibs: build-1738275487
syscfg/c2000ware_libraries.cmd.genlibs: build-1738275487
syscfg/c2000ware_libraries.opt: build-1738275487
syscfg/c2000ware_libraries.c: build-1738275487
syscfg/c2000ware_libraries.h: build-1738275487
syscfg/clocktree.h: build-1738275487
syscfg/: build-1738275487

syscfg/%.obj: ./syscfg/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1250/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --idiv_support=idiv0 --tmu_support=tmu0 -Ooff --include_path="D:/workc2000/led_ex1_blinky" --include_path="D:/C2000Ware_5_01_00_00" --include_path="C:/ti/ccs1250/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/include" --define=DEBUG --define=RAM --define=generic_ram_lnk --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --preproc_with_compile --preproc_dependency="syscfg/$(basename $(<F)).d_raw" --include_path="D:/workc2000/led_ex1_blinky/CPU1_RAM/syscfg" --obj_directory="syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

f28002x_codestartbranch.obj: D:/C2000Ware_5_01_00_00/device_support/f28002x/common/source/f28002x_codestartbranch.asm $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1250/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --idiv_support=idiv0 --tmu_support=tmu0 -Ooff --include_path="D:/workc2000/led_ex1_blinky" --include_path="D:/C2000Ware_5_01_00_00" --include_path="C:/ti/ccs1250/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/include" --define=DEBUG --define=RAM --define=generic_ram_lnk --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" --include_path="D:/workc2000/led_ex1_blinky/CPU1_RAM/syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


