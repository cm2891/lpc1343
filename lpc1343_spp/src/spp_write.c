/**
 * 	@file       spp_write.c
 * 	@brief      Source file for LPC1343 SPP
 * 	@author     Christian Matar
 */

#include "spp.h"

void SPP_write (uint16_t data)
{
    LPC_SSP0->DR = (uint16_t)(data & SPP_DATA_MASK);
}
