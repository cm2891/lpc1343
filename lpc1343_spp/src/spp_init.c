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
              )
{
    /* Power the SPP module. */
    LPC_SYSCTL->SYSAHBCLKCTRL |= 1 << SPP_SYSAHBCLKCTRL_POWER;

    LPC_SSP0->CR0 |= (((dss     << SPP_CR_DSS_LSB)      |
                       (frf     << SPP_CR_FRF_LSB)      |
                       (cpol    << SPP_CR_CPOL_LSB)     |
                       (cpha    << SPP_CR_CPHA_LSB)     |
                       (scr     << SPP_CR_SCR_LSB))
                        & SPP_CR_MASK);

    LPC_SSP0->CPSR = (prescale_val & SPP_CPSR_MASK);

}
