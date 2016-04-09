# pgback
QEmu QSDK extension

# About
This project consists of a library that links to a thin client added in QEmu, enabling it to load devices and boards dynamically.

The goal behind this project is to simplify the development of QEmu boards by adding modularity through loadable libraries and to define a friendlier API for writing new devices in other languages than C.

### Why?
This project was branched off a start-up idea which didn't take off and since then I've always wanted to open source some of it. 

### What can it do now?
- loads so and pyc files dynamically
- works and tested with Python and Rust devices (see https://github.com/gabriel-cr/device-repo for what modules are in the repo)
- the device repository contains a very simple arduino due board that can print messages through the serial port

### Doesn't it overlap with parts of QEmu?
It does. QEmu already has some mechanisms for defining loadable devices and setting object properties, but as development continues, I would like to integrate it nicely into QEmu.

### Why are you trying to redefine the API?
The project is not redefining the API for device development, but it attempts to add value to higher level development (e.g. SoCs).

# Run
For details on how to compile and run, read the README.md file here: https://github.com/gabriel-cr/qemu/blob/stable-2.5-qsdk
