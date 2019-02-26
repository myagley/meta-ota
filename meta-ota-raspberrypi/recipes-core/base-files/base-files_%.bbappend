do_install_append () {
    cat >> ${D}${sysconfdir}/fstab <<EOF
/dev/mmcblk0p1       /uboot          vfat       defaults,sync  0  0
EOF
}
