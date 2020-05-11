#ifndef _SPH0645_H
#define _SPH0645_H

extern "C" {
#include "user_interface.h"
#include "i2s_reg.h"
#include "slc_register.h"
#include "esp8266_peri.h"
void rom_i2c_writeReg_Mask(int, int, int, int, int, int);
}


#endif //_SPH0645_H