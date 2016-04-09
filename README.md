# pgback
QEmu QSDK extension

# About
This is a library that when linked to the QEmu version listed here https://github.com/gabriel-cr/qemu/tree/stable-2.5-qsdk, can load devices and boards dynamically.
Right now it's focused on small-scale boards (e.g. Arduino Due).

A device repository can be found here: https://github.com/gabriel-cr/device-repo

# QEmu integration
In terms of features it overlaps with QEmu in a few areas like device management and the object property system. This aspect will probably be improved in the future.

# Run it
In order to run the projects you will have to compile QEmu, PGback and the device repository:

```
mkdir qsdk
cd qsdk
git clone https://github.com/gabriel-cr/device-repo.git
git clone https://github.com/gabriel-cr/pgback
git clone https://github.com/gabriel-cr/qemu.git

cd pgback; 
./make_prj.sh
./deploy_qsdk.sh # Installs an environment variable that points to QSDK - will work on it in order to avoid this setup

bash

cd ../device-repo
./make_prj.sh

cd ../qemu
git checkout -b stable-2.5-qsdk
./configure_qsdk.sh
make
ln -s ../device_repo/lib # Create a symlink to the device repository library

# Run -machine help to list the machines. The Arduino board should be listed as 'arduino_board'.
./arm-softmmu/qemu-system-arm -machine help

# Run QEmu with the demo found in device-repository. Make sure to point the -kernel argument to a binary file generated from Arduino
./arm-softmmu/qemu-system-arm -M arduino_board -nographic -kernel ~/arduino_due.bin
```
