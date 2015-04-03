################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
button.obj: ../button.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"c:/ti/ccsv6/tools/compiler/arm_5.1.9/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me --include_path="c:/ti/ccsv6/tools/compiler/arm_5.1.9/include" --include_path="F:/Google Drive/Workspaces/ccs/quadGloveRemote" --include_path="C:/TI/TivaWare" -g --display_error_number --verbose_diagnostics --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="button.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

console.obj: ../console.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"c:/ti/ccsv6/tools/compiler/arm_5.1.9/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me --include_path="c:/ti/ccsv6/tools/compiler/arm_5.1.9/include" --include_path="F:/Google Drive/Workspaces/ccs/quadGloveRemote" --include_path="C:/TI/TivaWare" -g --display_error_number --verbose_diagnostics --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="console.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

gesture.obj: ../gesture.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"c:/ti/ccsv6/tools/compiler/arm_5.1.9/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me --include_path="c:/ti/ccsv6/tools/compiler/arm_5.1.9/include" --include_path="F:/Google Drive/Workspaces/ccs/quadGloveRemote" --include_path="C:/TI/TivaWare" -g --display_error_number --verbose_diagnostics --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="gesture.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

imufilter.obj: ../imufilter.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"c:/ti/ccsv6/tools/compiler/arm_5.1.9/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me --include_path="c:/ti/ccsv6/tools/compiler/arm_5.1.9/include" --include_path="F:/Google Drive/Workspaces/ccs/quadGloveRemote" --include_path="C:/TI/TivaWare" -g --display_error_number --verbose_diagnostics --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="imufilter.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

launchpad.obj: ../launchpad.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"c:/ti/ccsv6/tools/compiler/arm_5.1.9/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me --include_path="c:/ti/ccsv6/tools/compiler/arm_5.1.9/include" --include_path="F:/Google Drive/Workspaces/ccs/quadGloveRemote" --include_path="C:/TI/TivaWare" -g --display_error_number --verbose_diagnostics --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="launchpad.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

link.obj: ../link.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"c:/ti/ccsv6/tools/compiler/arm_5.1.9/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me --include_path="c:/ti/ccsv6/tools/compiler/arm_5.1.9/include" --include_path="F:/Google Drive/Workspaces/ccs/quadGloveRemote" --include_path="C:/TI/TivaWare" -g --display_error_number --verbose_diagnostics --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="link.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

lm4f120h5qr_startup_ccs.obj: ../lm4f120h5qr_startup_ccs.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"c:/ti/ccsv6/tools/compiler/arm_5.1.9/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me --include_path="c:/ti/ccsv6/tools/compiler/arm_5.1.9/include" --include_path="F:/Google Drive/Workspaces/ccs/quadGloveRemote" --include_path="C:/TI/TivaWare" -g --display_error_number --verbose_diagnostics --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="lm4f120h5qr_startup_ccs.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

main.obj: ../main.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"c:/ti/ccsv6/tools/compiler/arm_5.1.9/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me --include_path="c:/ti/ccsv6/tools/compiler/arm_5.1.9/include" --include_path="F:/Google Drive/Workspaces/ccs/quadGloveRemote" --include_path="C:/TI/TivaWare" -g --display_error_number --verbose_diagnostics --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="main.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


