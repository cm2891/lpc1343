/**
 *  @file       i2c_write.c
 *  @brief      Source file for I2C
 *  @author     Christian Matar
 */

#include "i2c_write.h"
#include "i2c_control.h"

void I2C_write (uint32_t data)
{
    LPC_I2C->DAT |= (data & I2C_DATA_MASK);
}

