/**
 *  @file       i2c_control.c
 *  @brief      Source file for I2C
 *  @author     Christian Matar
 */

#include "i2c_control.h"

void I2C_start ()
{
    LPC_I2C->CONSET |= (1 << I2C_I2EN_BIT);
}

void I2C_stop ()
{
    LPC_I2C->CONCLR |= (1 << I2C_I2ENC_BIT);
}

Bool I2C_write_ctrl_regs (I2C_CTRL_SET_REG *set, I2C_CTRL_CLR_REG *clr)
{
    if (!set || !clr)
        return FALSE;

    LPC_I2C->CONSET |= ( (set->assert_ack   << I2C_ASSERT_ACK_BIT)  |
                         (set->irq          << I2C_SI_BIT)          |
                         (set->stop         << I2C_STO_BIT)         |
                         (set->start        << I2C_STA_BIT)         |
                         (set->enable       << I2C_I2EN_BIT)
                       );

    LPC_I2C->CONCLR |= ( (clr->assert_ack   << I2C_ASSERT_ACKC_BIT) |
                         (clr->irq          << I2C_SIC_BIT)         |
                         (clr->start        << I2C_STAC_BIT)        |
                         (clr->enable       << I2C_I2ENC_BIT)
                       );

    return TRUE;
}

Bool I2C_read_ctrl_regs (I2C_CTRL_SET_REG *set, I2C_CTRL_CLR_REG *clr)
{
    if (!set || !clr)
        return FALSE;

    set->assert_ack = GET_BIT (LPC_I2C->CONSET, I2C_ASSERT_ACK_BIT);
    set->irq        = GET_BIT (LPC_I2C->CONSET, I2C_SI_BIT);
    set->stop       = GET_BIT (LPC_I2C->CONSET, I2C_STO_BIT);
    set->start      = GET_BIT (LPC_I2C->CONSET, I2C_STA_BIT);
    set->enable     = GET_BIT (LPC_I2C->CONSET, I2C_I2EN_BIT);

    clr->assert_ack = GET_BIT (LPC_I2C->CONCLR, I2C_ASSERT_ACKC_BIT);
    clr->irq        = GET_BIT (LPC_I2C->CONCLR, I2C_SIC_BIT);
    clr->start      = GET_BIT (LPC_I2C->CONCLR, I2C_STAC_BIT);
    clr->enable     = GET_BIT (LPC_I2C->CONCLR, I2C_I2ENC_BIT);

    return TRUE;
}
