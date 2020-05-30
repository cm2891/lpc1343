/**
 *  @file       i2c_slave_addr.h
 *  @brief      Header file for I2C
 *  @author     Christian Matar
 */


#ifndef INC_I2C_SLAVE_ADDR_H_
#define INC_I2C_SLAVE_ADDR_H_

#include "board.h"

/** Bitmask for the data registers. The LSB defines the General Call bit. */
#define I2C_ADDR_MASK       (0x000000FF)
/** Bitmask for the mask registers. */
#define I2C_MASK_REG_MASK   (I2C_ADDR_MASK)

/**
 *  @brief      Function I2C_set_slave_addr configures four slave addresses.
 *  @param[in]  addr, an array, which holds the four addresses.
 *  @return     Bool
 *  @retval     FALSE configuration failed.
 *  @retval     TRUE configuration succeeded.
 */
Bool I2C_set_slave_addr (uint32_t *addr);

/**
 *  @brief      Function I2C_set_mask configures four bit masks for comparison.
 *  @param[in]  mask, an array, which holds the four bit masks.
 *  @return     Bool
 *  @retval     FALSE configuration failed.
 *  @retval     TRUE configuration succeeded.
 */
Bool I2C_set_mask (uint32_t *mask);

#endif /* INC_I2C_SLAVE_ADDR_H_ */
