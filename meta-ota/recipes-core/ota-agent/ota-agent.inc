DEPENDS += "openssl10"
RDEPENDS_${PN} += "u-boot-fw-utils"
INSANE_SKIP_${PN} += "dev-deps"

inherit systemd

SYSTEMD_PACKAGES = "${@bb.utils.contains('DISTRO_FEATURES', 'systemd', '${PN}', '', d)}"
SYSTEMD_SERVICE_${PN} = "${@bb.utils.contains('DISTRO_FEATURES', 'systemd', 'ota.service', '', d)}"
SYSTEMD_AUTO_ENABLE_${PN} = "enable"

do_install () {
    # Binaries
    install -d  "${D}${bindir}"
    install -m 755 "${WORKDIR}/git/target/${CARGO_TARGET_SUBDIR}/ota" ${D}${bindir}/ota

    if ${@bb.utils.contains('DISTRO_FEATURES', 'systemd', 'true', 'false', d)}; then
        install -d ${D}${systemd_unitdir}/system
        install -m 644 ${WORKDIR}/git/contrib/systemd/ota.service ${D}${systemd_unitdir}/system
    fi
}

FILES_${PN} += " \
    ${systemd_unitdir}/system/* \
    "
