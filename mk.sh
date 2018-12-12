https://www.raspberrypi.org/documentation/linux/kernel/building.md


# build ko files 
make -C ~/linux/OUT M=$(pwd)  modules V=1

make -C /usr/src/linux-headers-`uname -r`/ M=$(pwd) modules V=1

#pi0
KERNEL=kernel make bcmrpi_defconfig

#pi3
KERNEL=kernel7 make bcm2709_defconfig O=OUT V=1

make -j3 zImage modules dtbs O=OUT V=1

make modules_install INSTALL_MOD_PATH=OUT V=1

cp arch/arm/boot/dts/*.dtb /boot/
cp arch/arm/boot/dts/overlays/*.dtb* /boot/overlays/
cp arch/arm/boot/dts/overlays/README /boot/overlays/
cp arch/arm/boot/zImage /boot/$KERNEL.img
