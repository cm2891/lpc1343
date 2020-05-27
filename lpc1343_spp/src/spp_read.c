/**
 * 	@file       spp_read.c
 * 	@brief      Source file for LPC1343 SPP
 * 	@author     Christian Matar
 */

#include "spp.h"

uint16_t SPP_read ()
{
    return (uint16_t)(LPC_SSP0->DR & SPP_DATA_MASK);
}
