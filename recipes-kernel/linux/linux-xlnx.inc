DESCRIPTION = "Xilinx Kernel"
SECTION = "kernel"
LICENSE = "GPLv2"

LIC_FILES_CHKSUM = "file://COPYING;md5=d7810fab7487fb0aad327b76f1be7cd7"

# This version extension should match CONFIG_LOCALVERSION in defconfig
LINUX_VERSION_EXTENSION ?= "-xilinx"
PV = "${LINUX_VERSION}${LINUX_VERSION_EXTENSION}+git${SRCREV}"

# Sources
KBRANCH ?= "master"
SRC_URI = "git://github.com/Xilinx/linux-xlnx;protocol=git;branch=${KBRANCH}"
FILESEXTRAPATHS_prepend := "${THISDIR}/files:"
FILESEXTRAPATHS_prepend := "${THISDIR}/linux-xlnx:"

# Source Directory
S = "${WORKDIR}/git"

# Inherit/include base functionality
inherit kernel
require linux-machine-common.inc

# Override COMPATIBLE_MACHINE to include your machine in a bbappend file.
COMPATIBLE_MACHINE = "qemumicroblaze|qemuzynq|microblaze|zynq"

# Common kernel configuration parts
# Arch specific kernel configuration parts
MACHINE_KCONFIG_append_zynq += "common/zynq_defconfig_${LINUX_VERSION}.cfg"
MACHINE_KCONFIG_append_microblaze += "common/microblaze_defconfig_${LINUX_VERSION}.cfg"

# returns all the elements from the src uri that are .cfg files
def find_config_fragments(d):
    sources=src_patches(d, True)
    sources_list=[]
    for s in sources:
        if s.endswith('.cfg'):
            sources_list.append(s)
    return sources_list

KERNEL_CONFIGS ?= "${@" ".join(find_config_fragments(d))}"

kernel_do_configure_prepend() {
	if [ ! -z "${KERNEL_CONFIGS}" ]; then
		# Merge the config files into a final .config file for the kernel, using
		# the merge_config.sh kernel script.
		${S}/scripts/kconfig/merge_config.sh -O ${B} ${KERNEL_CONFIGS}
	fi
}
