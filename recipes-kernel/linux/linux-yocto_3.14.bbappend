
#require linux-machine-common.inc

COMPATIBLE_MACHINE_zynq = "zynq"
KMACHINE_zynq ?= "zynq"

COMPATIBLE_MACHINE_microblaze = "microblaze"

FILESEXTRAPATHS_prepend := "${THISDIR}/config:"

SRC_URI_append += " \
		file://zynq-standard.scc \
		"