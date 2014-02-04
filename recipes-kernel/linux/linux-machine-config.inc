#
# This include file implements the MACHINE_DEVICETREE and MACHINE_KCONFIG
# variable handling for the Kernel.
#
# e.g. (set in the associated <machine>.conf)
# MACHINE_DEVICETREE := "zc702/zc702-zynq7.dts"
# MACHINE_KCONFIG := "common/rtc.cfg"
#
# This will expand out to:
# SRC_URI_append += "file://zc702/zc702-zynq7.dts file://common/rtc.cfg"
# OOT_KERNEL_DEVICETREE ?= "${WORKDIR}/devicetree/zc702-zynq7.dts"
#
# This include also adds all the 'conf/machine/boards' for all layers (that are
# available) to the FILESEXTRAPATHS.
#

inherit xilinx-utils

# If OOT_KERNEL_DEVICETREE is not set, default to the device tree's provided by
# MACHINE_DEVICETREE
OOT_KERNEL_DEVICETREE ?= "${@expand_dir_basepaths_by_extension("MACHINE_DEVICETREE", os.path.join(d.getVar("WORKDIR", True), 'devicetree'), '.dts', d)}"

# Appends the '<layer>/conf/machine/boards' path to FILESEXTRAPATHS for all
# layers (using the ${BBPATH})
FILESEXTRAPATHS_append := "${@get_additional_bbpath_filespath('conf/machine/boards', d)}"

# Using the MACHINE_DEVICETREE and MACHINE_KCONFIG vars, append them to SRC_URI
SRC_URI_append += " \
		${@paths_affix(d.getVar("MACHINE_DEVICETREE", True) or '', prefix = 'file://')} \
		${@paths_affix(d.getVar("MACHINE_KCONFIG", True) or '', prefix = 'file://')} \
		"

# Copy all device tree's into the same directory. This is due to compatibility
# with dtc and the use of DTSI (Device Tree Includes), the version of DTC in
# Yocto does not provide include path support.
do_install_prepend() {
	if test -n "${MACHINE_DEVICETREE}"; then
		mkdir -p ${WORKDIR}/devicetree
		for i in ${MACHINE_DEVICETREE}; do
			if test -e ${WORKDIR}/$i; then
				cp ${WORKDIR}/$i ${WORKDIR}/devicetree
			fi
		done
	fi
}

# returns all the elements from the src uri that are .cfg files
def find_config_fragments(d):
    sources=src_patches(d, True)
    sources_list=[]
    for s in sources:
        if s.endswith('.cfg'):
            sources_list.append(s)
    return sources_list

KERNEL_CONFIGS ?= "${@" ".join(find_config_fragments(d))}"

python do_kernel_configure_generate () {
    pass
}

do_kernel_configure_merge () {
	if [ ! -z "${KERNEL_CONFIGS}" ]; then
		# Merge the config files into a final .config file for the kernel, using
		# the merge_config.sh kernel script.
		${S}/scripts/kconfig/merge_config.sh -m ${KERNEL_CONFIGS}
	fi
}

addtask kernel_configure_generate after do_unpack before do_kernel_configure_merge
addtask kernel_configure_merge after do_kernel_configure_generate before do_configure
