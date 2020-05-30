/**
 * 	@file       spp_write.c
 * 	@brief      Source file for LPC1343 SPP
 * 	@author     Christian Matar
 */

#include "spp.h"

void SPP_write (uint32_t data)
{
    LPC_SSP0->DR = (data & SPP_DATA_MASK);
}
