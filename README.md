# MicroBSP

Tiny implementation of a Board Support Package for the RM46x series of TI microcontrollers.

## Requirements

1. Download the [arm-none-eabi toolchain](https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads)
2. Install uniflash from [TI's website](https://www.ti.com/tool/UNIFLASH#downloads) which will provide drivers for USB interface and allow you to flash the board
3. Optionally get HalCoGen,CCS, and OpenOCD for debugging.

## Usage

Use `make example EXAMPLE=.` with one of the examples in the `examples/` folder (for example, `make example EXAMPLE=blink`). This will build to `./build/<EXAMPLE>.bin`.

Then use a tool like [`uniflash`](https://www.ti.com/tool/UNIFLASH) to flash the `<EXAMPLE>.bin` file to the LAUNCHXL2-RM46 board. Alternatively this should work with [CCStudio](https://www.ti.com/tool/CCSTUDIO)

**NOTE**: You will need to enable `Run Target After Program Load/Flash Operation` if you want the program to immediately start running after flashing.


## Debugging

### CCS

If you are using Code Composer Studio likely its debug mechanisms will work just fine.

### OpenOCD + UniFlash

There is a configuration file for the RM46x series provided in ./openocd.cfg.

1. Flash the program (ensure 'Remain connected after flashing the program' is checked OFF in uniflash)
2. Run `openocd`, it should use the openocd.cfg.
3. Connect to the gdb server it hosts with `arm-none-eabi-gdb`
4. Run `target remote localhost:3333` in gdb
5. Load the ELF file with `file ./build/<EXAMPLE>.elf`
6. You may want to `load` the program again in gdb if it doesn't initially behave
    - You need to do this when building with optimizations disabled.
