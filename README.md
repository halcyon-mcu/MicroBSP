# MicroBSP

Tiny implementation of a Board Support Package for the RM46x series of TI microcontrollers.

## Requirements

- arm-none-eabi-gcc toolchain

## Usage

Use `make example EXAMPLE=.` with one of the examples in the `examples/` folder to build an example project .bin file.

Then use a tool like `uniflash` to flash the `<EXAMPLE>.bin` file to the LAUNCHXL2-RM46 board.

Note you will need to enable `Run Target After Program Load/Flash Operation` if you want the program to immediately start running after flashing.
