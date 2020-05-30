/**
 *  @file       i2c_slave_addr.c
 *  @brief      Source file for I2C
 *  @author     Christian Matar
 */

#include "i2c_slave_addr.h"

Bool I2C_set_slave_addr (uint32_t *addr)
{
    if (!addr)
        return FALSE;

    LPC_I2C->ADR0 = (addr[0U] & I2C_ADDR_MASK);
    LPC_I2C->ADR1 = (addr[1U] & I2C_ADDR_MASK);
    LPC_I2C->ADR2 = (addr[2U] & I2C_ADDR_MASK);
    LPC_I2C->ADR3 = (addr[3U] & I2C_ADDR_MASK);

    return TRUE;
}

Bool I2C_set_mask (uint32_t *mask)
{
    if (!mask)
        return FALSE;

    uint8_t i;

    for (i = 0; i < 4U; i++)
        LPC_I2C->MASK[i] = (mask[i] & I2C_MASK_REG_MASK);

    return TRUE;
}
