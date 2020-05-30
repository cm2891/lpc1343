/**
 *  @file       i2c_read.h
 *  @brief      Header file for I2C
 *  @author     Christian Matar
 */

#ifndef INC_I2C_READ_H_
#define INC_I2C_READ_H_

#include "board.h"

/**
 *  @brief      Function I2C_read reads one byte from the I2C bus. The I2C
 *              module must be configured beforehand. Although the LPC register
 *              <b>I2C0DAT</b> is 32-bit wide, only one byte can be read. The
 *              function takes care to mask the data accordingly.
 *  @return     uint32_t
 *  @retval     The read byte.
 */
uint32_t I2C_read ();

/**
 *  @brief      Function I2C_get_data_buffer reads one byte from register
 *              <b>I2C0DATA_BUFFER</b>. The I2C module must be configured
 *              beforehand. Although the register is 32-bit wide, only one byte
 *              can be read. The function takes care to mask the data
 *              accordingly.
 *  @return     uint32_t
 *  @retval     The read byte from the data buffer.
 */
uint32_t I2C_get_data_buffer ();

#endif /* INC_I2C_READ_H_ */
