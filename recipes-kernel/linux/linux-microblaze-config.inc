#
# This include file implements the MicroBlaze auto-generated CPU flag kconfig
# options for the Kernel.
#

KERNEL_CONFIGS_MICROBLAZE_GENERATED = "${WORKDIR}/microblaze.machine.config"
KERNEL_CONFIGS_append_microblaze += "${KERNEL_CONFIGS_MICROBLAZE_GENERATED}"

def tune_features_index(d, *args):
    value = 0
    tunes = (d.getVar("TUNE_FEATURES", True) or "").split()
    for count, i in enumerate(args):
        enumvalue = len(args) - count
        if i in tunes and enumvalue > value:
            value = enumvalue
    return "%d" % value

python do_kernel_configure_generate_append_microblaze () {
    cfgs = {}

    cfgs["CONFIG_XILINX_MICROBLAZE0_HW_VER"] = "\"%s\"" % d.getVar("MBCPUVERSION", True)
    cfgs["CONFIG_XILINX_MICROBLAZE0_USE_DIV"] = tune_features_index(d, "divide-hard")
    cfgs["CONFIG_XILINX_MICROBLAZE0_USE_FPU"] = tune_features_index(d, "fpu-hard")
    cfgs["CONFIG_XILINX_MICROBLAZE0_USE_HW_MUL"] = tune_features_index(d, "multiply-high", "multiply-low")
    cfgs["CONFIG_XILINX_MICROBLAZE0_USE_BARREL"] = tune_features_index(d, "barrel-shift")
    cfgs["CONFIG_XILINX_MICROBLAZE0_USE_PCMP_INSTR"] = tune_features_index(d, "pattern-compare")
    cfgs["CONFIG_XILINX_MICROBLAZE0_USE_MSR_INSTR"] = tune_features_index(d, "msr")

    generatepath = d.getVar("KERNEL_CONFIGS_MICROBLAZE_GENERATED", True)
    if generatepath:
        with open(generatepath, "w") as cfgfile:
            cfgfile.write("\n")
            for i in cfgs.iteritems():
                cfgfile.write("%s=%s\n" % (i[0], i[1]))
            cfgfile.write("\n")
}

