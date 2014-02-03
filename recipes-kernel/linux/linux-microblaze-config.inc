#
# This include file implements the MicroBlaze auto-generated CPU flag kconfig
# options for the Kernel.
#

def get_mb_configs(d):
	cfgs = []

	cfgs.append("CONFIG_XILINX_MICROBLAZE0_HW_VER=\"%s\"" % d.getVar("MBCPUVERSION", True))

	cfgs.append("CONFIG_XILINX_MICROBLAZE0_USE_DIV=%s" %
			bb.utils.contains("TUNE_FEATURES", "divide-hard", "1", "0", d))
	cfgs.append("CONFIG_XILINX_MICROBLAZE0_USE_FPU=%s" %
			bb.utils.contains("TUNE_FEATURES", "fpu-hard", "1", "0", d))
	cfgs.append("CONFIG_XILINX_MICROBLAZE0_USE_HW_MUL=%s" %
			bb.utils.contains("TUNE_FEATURES", "multiply-high", "2",
				bb.utils.contains("TUNE_FEATURES", "multiply-low", "1", "0", d), d))
	cfgs.append("CONFIG_XILINX_MICROBLAZE0_USE_BARREL=%s" %
			bb.utils.contains("TUNE_FEATURES", "barrel-shift", "1", "0", d))
	cfgs.append("CONFIG_XILINX_MICROBLAZE0_USE_PCMP_INSTR=%s" %
			bb.utils.contains("TUNE_FEATURES", "pattern-compare", "1", "0", d))

	cfgs.append("CONFIG_XILINX_MICROBLAZE0_USE_MSR_INSTR=%s" %
			bb.utils.contains("TUNE_FEATURES", "msr", "1", "0", d))

	return "\\n".join(cfgs) + "\\n"

KERNEL_CONFIGS_append_microblaze += "${WORKDIR}/microblaze.machine.config"

kernel_do_configure_prepend_microblaze () {
	printf "${@get_mb_configs(d)}" > ${WORKDIR}/microblaze.machine.config
}
