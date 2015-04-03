################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
drivers/adxl345.obj: ../drivers/adxl345.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"c:/ti/ccsv6/tools/compiler/arm_5.1.9/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me --include_path="c:/ti/ccsv6/tools/compiler/arm_5.1.9/include" --include_path="F:/Google Drive/Workspaces/ccs/quadGloveRemote" --include_path="C:/TI/TivaWare" -g --display_error_number --verbose_diagnostics --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="drivers/adxl345.pp" --obj_directory="drivers" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

drivers/hmc5883l.obj: ../drivers/hmc5883l.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"c:/ti/ccsv6/tools/compiler/arm_5.1.9/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me --include_path="c:/ti/ccsv6/tools/compiler/arm_5.1.9/include" --include_path="F:/Google Drive/Workspaces/ccs/quadGloveRemote" --include_path="C:/TI/TivaWare" -g --display_error_number --verbose_diagnostics --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="drivers/hmc5883l.pp" --obj_directory="drivers" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

drivers/i2c.obj: ../drivers/i2c.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"c:/ti/ccsv6/tools/compiler/arm_5.1.9/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me --include_path="c:/ti/ccsv6/tools/compiler/arm_5.1.9/include" --include_path="F:/Google Drive/Workspaces/ccs/quadGloveRemote" --include_path="C:/TI/TivaWare" -g --display_error_number --verbose_diagnostics --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="drivers/i2c.pp" --obj_directory="drivers" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

drivers/itg3200.obj: ../drivers/itg3200.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"c:/ti/ccsv6/tools/compiler/arm_5.1.9/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me --include_path="c:/ti/ccsv6/tools/compiler/arm_5.1.9/include" --include_path="F:/Google Drive/Workspaces/ccs/quadGloveRemote" --include_path="C:/TI/TivaWare" -g --display_error_number --verbose_diagnostics --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="drivers/itg3200.pp" --obj_directory="drivers" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

drivers/lcd.obj: ../drivers/lcd.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"c:/ti/ccsv6/tools/compiler/arm_5.1.9/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me --include_path="c:/ti/ccsv6/tools/compiler/arm_5.1.9/include" --include_path="F:/Google Drive/Workspaces/ccs/quadGloveRemote" --include_path="C:/TI/TivaWare" -g --display_error_number --verbose_diagnostics --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="drivers/lcd.pp" --obj_directory="drivers" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


