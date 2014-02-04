# This include file implements the MicroBlaze auto-generated CPU flag kconfig
# options for the Kernel.

def tune_features_index(d, *args):
    value = 0
    tunes = (d.getVar("TUNE_FEATURES", True) or "").split()
    for count, i in enumerate(args):
        enumvalue = len(args) - count
        if i in tunes and enumvalue > value:
            value = enumvalue
    return "%d" % value

MACHINE_KCONFIG_XILINX_MICROBLAZE0_HW_VER_microblaze = "${MBCPUVERSION}"
MACHINE_KCONFIG_XILINX_MICROBLAZE0_USE_DIV_microblaze = "${@tune_features_index(d, 'divide-hard')}"
MACHINE_KCONFIG_XILINX_MICROBLAZE0_USE_FPU_microblaze = "${@tune_features_index(d, 'fpu-hard')}"
MACHINE_KCONFIG_XILINX_MICROBLAZE0_USE_HW_MUL_microblaze = "${@tune_features_index(d, 'multiply-high', 'multiply-low')}"
MACHINE_KCONFIG_XILINX_MICROBLAZE0_USE_BARREL_microblaze = "${@tune_features_index(d, 'barrel-shift')}"
MACHINE_KCONFIG_XILINX_MICROBLAZE0_USE_PCMP_INSTR_microblaze = "${@tune_features_index(d, 'pattern-compare')}"
MACHINE_KCONFIG_XILINX_MICROBLAZE0_USE_MSR_INSTR_microblaze = "${@tune_features_index(d, 'msr')}"
