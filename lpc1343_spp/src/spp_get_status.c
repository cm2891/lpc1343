/*
 * spp_get_status.c
 *
 *  Created on: 28.05.2020
 *      Author: chris
 */


#include "spp.h"

Bool SPP_get_status (SPP_STATUS *status)
{
    if (status)
    {
        status->TFE = GET_BIT (LPC_SSP0->SR, 0);
        status->TNF = GET_BIT (LPC_SSP0->SR, 1);
        status->RNE = GET_BIT (LPC_SSP0->SR, 2);
        status->RFF = GET_BIT (LPC_SSP0->SR, 3);
        status->BSY = GET_BIT (LPC_SSP0->SR, 4);

        return TRUE;
    }

    return FALSE;
}
