# Blue Pill Project using c++

A boilerplate for generating projects for stm32 blue pill board using cmake and makefile. The projects does not use any tools provided by ST Microelectronics.
Everything from development, flashing to debugging can be done in Visual Studio Code only. C and C++ both languages are supported along with OOP concepts.

![Build Passing](https://img.shields.io/badge/build-passing-brightgreen) [![GPLv3 License](https://img.shields.io/badge/License-GPL%20v3-yellow.svg)](https://opensource.org/licenses/)

## Dependencies

* cmake
    Cmake utility is required for configuring and building this project. You can install cmake on linux by running command:

    ```bash
    sudo apt install cmake
    ```

* make
    Make utility is required for configuring and building this project. You can install cmake on linux by running command:

    ```bash
    sudo apt-get install build-essential
    ```

* gcc-arm-none-eabi toolchain
    ARM cross-platform toolchain is required to build applications for arm mcus. Toolchain can be installed by running following command:

    ```bash
    sudo apt-get install gcc-arm-none-eabi
    ```

* openocd
    It is an Open On Circuit Debugging tool used to flash and debug arm micro controllers. You can install cmake on linux by running command:

   ```bash
   sudo apt install openocd -y
   ```

* Cortex Debug extension
    This extension is required to enable debugging for cortex m microcontrollers in vscode. Install all the recommendded extension for better experience.

## Project Structure

* `src` directory contains all source files for the project
* `include` directory contains all header files for the project

### Source file description

* `CMakeLists.txt` - Cmake configuration file for current project
* `gcc-arm-none-eabi.cmake` - Cmake configuration file for toolchain
* `STM32F103C8TX_FLASH.ld`  - linker script
* `STM32F103.svd` - The CMSIS System View Description format(CMSIS-SVD) formalizes the description of the system contained in Arm Cortex-M processor-based microcontrollers, in particular, the memory mapped registers of peripherals. This file re required to debug device.
* `src/main.c` - application code
* `src/startup_stm32f103c8tx.s` - assembly startup script for blue pill board
* `src/system_stm32f1xx.c` - clock configuration and system initialization functions

## Configuration

All the configuration required for building this project is given below.

1. Build output directory
    In `Makefile`, output directory can be configured using variable `BUILD_DIR`.

2. Build type
    In `Makefile`, build type can be configured using variable`BUILD_TYPE`. Possible values are `Debug` and `Release`.

3. Binary name
    In `CMakeLists.txt`, output binary name can be configured using `project(<binary-name>)` macro.
    ** update above info in `.vscode/launch.json` as well for debugging to work.

## Build

Run following command in terminal to generate flashable binaries for blue pill board. Build files will be written to **Build Output Directory** as configured.

```bash
make all
```

## Flash

1. Connect Stlink to PC and blue pill board using swd headers.
2. Put blue pill board in programming mode.
3. Run following to flash board with binary.

```bash
make flash
```

## Output

Onboard led connected to Pin C13 can be observed to be blinking after 500ms.

## Debug

Click in `Run and Debug` option in VsCode sidebar. Then launch `Cortex Debug` target.

Happy debugging....
