cmake_minimum_required(VERSION 3.13)

# MP3 board: RP2354A (2 MB in-package flash), 12 MHz oscillator on XIN.
# The generic pico2 board config matches the chip, crystal and flash size.
set(PICO_PLATFORM rp2350-arm-s)
set(PICO_BOARD pico2)

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(blinky C CXX ASM)
set(CMAKE_C_STANDARD 11)

pico_sdk_init()

add_executable(blinky main.c)
target_link_libraries(blinky pico_stdlib)

# Serial output over the board's USB-C port.
pico_enable_stdio_usb(blinky 1)
pico_enable_stdio_uart(blinky 0)

pico_add_extra_outputs(blinky)
