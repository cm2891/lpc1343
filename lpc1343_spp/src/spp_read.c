/**
 * 	@file       spp_read.c
 * 	@brief      Source file for LPC1343 SPP
 * 	@author     Christian Matar
 */

#include "spp.h"

uint32_t SPP_read ()
{
    return (LPC_SSP0->DR & SPP_DATA_MASK);
}
