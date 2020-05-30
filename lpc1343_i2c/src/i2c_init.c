/**
 *  @file       i2c.c
 *  @brief      Source file for I2C
 *  @author     Christian Matar
 */

#include "i2c.h"


Bool I2C_init (I2C_MODE mode)
{
    /* Power the I2C block. */
    LPC_SYSCTL->SYSAHBCLKCTRL |= 1 << SYSCTL_CLOCK_I2C;

    /* Reset the I2C block and release it immediately after. */
    LPC_SYSCTL->PRESETCTRL &= (1 << I2C_RESET_BIT);
    LPC_SYSCTL->PRESETCTRL |= (1 << I2C_RESET_BIT);

    switch (mode)
    {
        case I2C_STANDARD_MODE:
            LPC_I2C->SCLH = (I2C_SCLH_STANDARD & I2C_SCL_MASK);
            LPC_I2C->SCLL = (I2C_SCLL_STANDARD & I2C_SCL_MASK);
            break;

        case I2C_FAST_MODE:
            LPC_I2C->SCLH = (I2C_SCLH_FAST & I2C_SCL_MASK);
            LPC_I2C->SCLL = (I2C_SCLL_FAST & I2C_SCL_MASK);
            break;

        case I2C_FAST_MODE_PLUS:
            LPC_I2C->SCLH = (I2C_SCLH_FAST_PLUS & I2C_SCL_MASK);
            LPC_I2C->SCLL = (I2C_SCLL_FAST_PLUS & I2C_SCL_MASK);
            break;

        default:
            return FALSE;
    }


    return TRUE;
}
