// https://www.silabs.com/community/mcu/8-bit/knowledge-base.entry.html/2016/01/13/locking_flash_using-RdLy

#include <si_toolchain.h>
#include "app.h"

const uint8_t code lockbyte = 0x00;

//#ifdef U2F_USING_BOOTLOADER
//const uint8_t code BOOTSIGNB = 0xA5; //bootloader_signature_byte
//#else
//const uint8_t code BOOTSIGNB = 0x00; //bootloader_signature_byte
//#endif

