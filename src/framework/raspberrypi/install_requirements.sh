#!/bin/bash

BCM_VERSION=1.68
if [ "$EUID" -eq 0 ]
then
	echo "Please do not execute this script as root."
	exit 1
fi

echo "### PLEASE NOTE ###"
echo -e "The radar-bgt60 library requires access to the SPI peripheral.\nThe underlying BCM2835 library requires access to /dev/mem to access the SPI peripheral."
echo "This can EITHER be achieved by executing your binaries always as root or by installing libcap2 and libcap-dev and allowing your user to access the mem device."
read  -n 1 -p "Do you want to enable non-root access to SPI? This installs additional packets and changes udev rules and group membership of the current user (y/n). Cancel with CTRL-C." menuinput
echo -e "\n"

while [[ $menuinput != 'n' && $menuinput != 'N' && $menuinput != 'y' && $menuinput != 'Y' ]]
do
	read  -n 1 -p "Your selection $menuinput is not valid. Please press either y (yes) or n (no). Cancel with CTRL+C." menuinput
	echo -e "\n"
done

if [[ $menuinput == 'Y' || $menuinput == 'y' ]]
then
	CFLAGS='-DBCM2835_HAVE_LIBCAP'
	echo "Installing required packets..."
	sudo apt-get install libcap2 libcap-dev
	echo "Add current user to kmem group..."
	sudo adduser $USER kmem
	echo "Allow write access to /dev/mem by members of kmem group..."
	echo 'SUBSYSTEM=="mem", KERNEL=="mem", GROUP="kmem", MODE="0660"' | sudo tee /etc/udev/rules.d/98-mem.rules
else
	CFLAGS=''
fi

echo "Downloading source for BCM2835 library..."
wget http://www.airspayce.com/mikem/bcm2835/bcm2835-$BCM_VERSION.tar.gz

echo "Compiling BCM2835 library..."
tar zxvf bcm2835-$BCM_VERSION.tar.gz
cd bcm2835-$BCM_VERSION

./configure CFLAGS=$CFLAGS
make

echo "Installing BCM2835 library..."
sudo make check
sudo make install

echo "Cleaning up..."
cd ..
rm -f bcm2835-$BCM_VERSION.tar.gz
rm -rf bcm2835-$BCM_VERSION

if [[ $menuinput == 'Y' || $menuinput == 'y' ]]
then
	echo "--- PLEASE REBOOT YOUR SYSTEM ---"
fi