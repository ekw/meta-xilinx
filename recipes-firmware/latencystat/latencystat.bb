DESCRIPTION = "latencystat"

LICENSE = "Proprietary"
LIC_FILES_CHKSUM = "file://${COREBASE}/meta/files/common-licenses/Proprietary;md5=0557f9d92cf58f2ccdd50f62f8ac0b28"

SRC_URI = " \
	file://latencydemo.h \
	file://latencygraph.c \
	file://latencygraph.h \
	file://latencyrpmsg.c \
	file://latencyrpmsg.h \
	file://latencystat.c \
	"

S = "${WORKDIR}"

do_configure() {
	:
}

do_compile() {
	${CC} ${CFLAGS} ${LDFLAGS} -o ${S}/latencystat -I${S} ${S}/latencystat.c ${S}/latencygraph.c ${S}/latencyrpmsg.c
}

do_install() {
	install -d ${D}${bindir}
	install -m 0755 ${S}/latencystat ${D}${bindir}/latencystat
}

FILES_${PN} += "${bindir}/latencystat"
