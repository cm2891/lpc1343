/**
 *  @file       i2c_mode.h
 *  @brief      Header file for I2C
 *  @author     Christian Matar
 */

#ifndef INC_I2C_MODE_H_
#define INC_I2C_MODE_H_

#include "board.h"

/**
 *  @enum   I2C_MODE
 *  @brief  Defines the I2C mode, the LPC shall operate in.
 */
typedef enum
{
    I2C_MASTER      /**< LPC is the MASTER. */
,   I2C_SLAVE       /**< LPC is a SLAVE. */
} I2C_MODE;

/**
 *  @brief      Function I2C_set_mode sets the mode the LPC shall operate
 *              the I2C bus in.
 *  @param[in]  mode The I2C mode. Valid values are defined by <b>I2C_MODE</b>.
 *  @return     Bool
 *  @retval     FALSE mode was not set.
 *  @retval     TRUE mode was set.
 */
Bool I2C_set_mode (I2C_MODE mode);


#endif /* INC_I2C_MODE_H_ */
