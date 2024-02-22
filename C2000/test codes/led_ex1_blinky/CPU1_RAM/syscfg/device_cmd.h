#ifndef DEVICE_CMD_H
#define DEVICE_CMD_H

#include <cpy_tbl.h>


#ifdef generic_ram_lnk
void generic_ram_lnk_init();
#endif
#ifdef generic_flash_lnk
void generic_flash_lnk_init();
#endif

void CMD_init();

#endif
