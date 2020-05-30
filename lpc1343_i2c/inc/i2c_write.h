/**
 *  @file       i2c_write.h
 *  @brief      Header file for I2C
 *  @author     Christian Matar
 */

#ifndef INC_I2C_WRITE_H_
#define INC_I2C_WRITE_H_

#include "board.h"

/**
 *  @brief      Function I2C_write sends one byte over the I2C bus. The I2C
 *              module must be configured beforehand. Although the LPC register
 *              I2C0DAT is 32-bit wide, only one byte can be written. The
 *              function takes care to mask the data accordingly.
 *  @param[in]  data the byte to be sent.
 *              It will be masked with <b>I2C_DATA_MASK</b>.
 *  @return     void
 */
void I2C_write (uint32_t data);

#endif /* INC_I2C_WRITE_H_ */
