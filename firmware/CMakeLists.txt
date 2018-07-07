cmake_minimum_required(VERSION 3.10)
project(u2f C)

#set(CMAKE_C_STANDARD 11)

SET(CMAKE_SYSTEM_NAME Generic)
SET(CMAKE_SYSTEM_PROCESSOR arm)
#set(CMAKE_C_COMPILER "arm-none-eabi-gcc")
set(CMAKE_C_COMPILER "sdcc")
#set(CMAKE_CXX_COMPILER "arm-none-eabi-g++")
#set(CMAKE_EXE_LINKER_FLAGS "--specs=nosys.specs" CACHE INTERNAL "")
SET(CMAKE_CROSSCOMPILING 1)

include_directories(inc)
include_directories(inc/config)
include_directories(lib/efm8_assert)
include_directories(lib/efm8_usb/inc)
include_directories(lib/efm8ub1/peripheralDrivers/inc)
include_directories(tests)

# Requires a full SDK dir copy from Simplicity Studio v3
include_directories(../sdks/si8051/v3/Device/shared/si8051Base)
include_directories(../sdks/si8051/v3/Device/EFM8UB1/inc)

# Set any flag, just to make it build (for now)
add_definitions(-D__GNUC__ -D__ARM_ARCH=7 -D__ARMEL__)

add_executable(firmware
        inc/config/efm8_config.h
        inc/config/usbconfig.h
        inc/app.h
        inc/atecc508a.h
        inc/bsp.h
        inc/custom.h
        inc/descriptors.h
        inc/eeprom.h
        inc/i2c.h
        inc/InitDevice.h
        inc/u2f.h
        inc/u2f_hid.h
        lib/efm8_assert/assert.c
        lib/efm8_assert/assert.h
        lib/efm8_usb/inc/efm8_usb.h
        lib/efm8_usb/src/efm8_usbd.c
        lib/efm8_usb/src/efm8_usbdch9.c
        lib/efm8_usb/src/efm8_usbdep.c
        lib/efm8_usb/src/efm8_usbdint.c
        lib/efm8ub1/peripheralDrivers/inc/usb_0.h
        lib/efm8ub1/peripheralDrivers/src/usb_0.c
        src/atecc508a.c
        src/bsp.c
        src/callback.c
        src/cert.c
        src/custom.c
        src/descriptors.c
        src/eeprom.c
        src/i2c.c
        src/InitDevice.c
        src/Interrupts.c
        src/main.c
        src/u2f.c
        src/u2f_atecc.c
        src/u2f_hid.c
#        tests/tests.c
#        tests/tests.h
        )
