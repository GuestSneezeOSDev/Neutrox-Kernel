##########################
#       BUILD.SH         #
##########################
cd ~/
wget https://busybox.net/downloads/busybox-1.36.1.tar.bz2
tar xjf busybox-1.36.1.tar.bz2
cd busybox-1.36.1
mkdir -p ~/rootfs/{bin,sbin,etc,proc,sys}
cp ~/busybox ~/rootfs/bin/
cd rootfs/bin && ln -s busybox sh && ln -s busybox init
cd ..
find . | cpio -o --format=newc | gzip > ../initramfs.cpio.gz
cd ~/neutrox
make -j $(nproc)
