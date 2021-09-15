#!/bin/bash

BCM_VERSION=1.68
if [ "$EUID" -eq 0 ]
then
	echo "Please do not execute this script as root."
	exit 1
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

echo "Installing wiringPi..."
sudo apt-get update -y
sudo apt-get install wiringpi -y