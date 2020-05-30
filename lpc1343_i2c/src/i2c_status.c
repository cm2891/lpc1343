/**
 *  @file       i2c_status.c
 *  @brief      Source file for I2C
 *  @author     Christian Matar
 */

#include "i2c_status.h"

uint32_t I2C_get_status ()
{
    return (LPC_I2C->STAT & I2C_STATUS_MASK);
}
