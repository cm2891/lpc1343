/**
 *  @file       i2c_mode.c
 *  @brief      Source file for I2C
 *  @author     Christian Matar
 */

#include "i2c_mode.h"
#include "i2c_control.h"

Bool I2C_set_mode (I2C_MODE mode)
{
    I2C_CTRL_SET_REG set;
    I2C_CTRL_CLR_REG clr;

    switch (mode)
    {
        case I2C_MASTER:
            set.assert_ack = FALSE;
            set.irq        = FALSE;
            set.start      = FALSE;
            set.stop       = FALSE;
            set.enable     = TRUE;

            clr.assert_ack = ~set.assert_ack;
            clr.irq        = ~set.irq;
            clr.start      = ~set.start;
            clr.enable     = ~set.enable;

            return I2C_write_ctrl_regs (&set, &clr);

        case I2C_SLAVE:
            set.assert_ack = TRUE;
            set.irq        = FALSE;
            set.start      = FALSE;
            set.stop       = FALSE;
            set.enable     = TRUE;

            clr.assert_ack = ~set.assert_ack;
            clr.irq        = ~set.irq;
            clr.start      = ~set.start;
            clr.enable     = ~set.enable;

            return I2C_write_ctrl_regs (&set, &clr);

        default:
            /* Invalid mode */
            return FALSE;
    }
}

