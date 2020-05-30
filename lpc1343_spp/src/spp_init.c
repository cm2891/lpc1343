/**
 * 	@file       spp_init.c
 * 	@brief      Source file for LPC1343 SPP
 * 	@author     Christian Matar
 */

#include "spp.h"

void SPP_init ( SPP_WORD_SIZE dss
              , uint8_t frf
              , Bool cpol
              , Bool cpha
              , uint8_t scr
              , uint8_t prescale_val
              , uint8_t clk_div
              )
{
    /* Power the SPP module. */
    LPC_SYSCTL->SYSAHBCLKCTRL |= 1 << SPP_SYSAHBCLKCTRL_POWER;
    /* Set the clock divider. */
    LPC_SYSCTL->SSP0CLKDIV = ((uint32_t)clk_div & SPP_DIV_MASK);

    /* Configure the control register. */
    LPC_SSP0->CR0 |= (((dss     << SPP_CR_DSS_LSB)      |
                       (frf     << SPP_CR_FRF_LSB)      |
                       (cpol    << SPP_CR_CPOL_LSB)     |
                       (cpha    << SPP_CR_CPHA_LSB)     |
                       (scr     << SPP_CR_SCR_LSB))
                        & SPP_CR_MASK);

    /* Set the prescaler. */
    LPC_SSP0->CPSR = ((uint32_t)prescale_val & SPP_CPSR_MASK);
}
