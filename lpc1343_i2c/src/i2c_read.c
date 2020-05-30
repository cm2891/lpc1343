/**
 *  @file       i2c_read.c
 *  @brief      Source file for I2C
 *  @author     Christian Matar
 */

#include "i2c_read.h"
#include "i2c_control.h"

uint32_t I2C_read ()
{
    return (LPC_I2C->DAT & I2C_DATA_MASK);
}
