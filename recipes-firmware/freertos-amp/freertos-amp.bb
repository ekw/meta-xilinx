DESCRIPTION = "FreeRTOS AMP Software"

LICENSE = "Proprietary"
LIC_FILES_CHKSUM = "file://${COREBASE}/meta/files/common-licenses/Proprietary;md5=0557f9d92cf58f2ccdd50f62f8ac0b28"

SRC_URI = "file://freertos"

do_configure() {
	:
}

do_compile() {
	:
}

do_install() {
	install -d ${D}${base_libdir}/firmware
	install -m 0755 ${WORKDIR}/freertos ${D}${base_libdir}/firmware/freertos
}

FILES_${PN} += "${base_libdir}/firmware/freertos"

