/**
 *  @file       i2c_status.h
 *  @brief      Header file for I2C
 *  @author     Christian Matar
 */


#ifndef INC_I2C_STATUS_H_
#define INC_I2C_STATUS_H_

#include "board.h"

/** Bitmask for register I2C0STAT. */
#define I2C_STATUS_MASK         (0x000000F8)

/**
 *  @brief  Function I2C_get_status retrieves the register I2C0STAT.
 *  @return uint32_t
 *  @retval The register's content.
 */
uint32_t I2C_get_status ();

#endif /* INC_I2C_STATUS_H_ */
