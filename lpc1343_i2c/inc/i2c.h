/**
 *  @file       i2c.h
 *  @brief      Header file for I2C
 *  @author     Christian Matar
 */

#ifndef INC_I2C_H_
#define INC_I2C_H_

#include "board.h"

/** @brief The frequency of the I2C bus is determined by the registers SCLH and SCLL.
 *  \f$I2C_bitfrequency = f_PCLK / (SCLH + SCLL)\f$.
 * */
/** Bit with which the I2C module an be reset. */
#define I2C_RESET_BIT           (1U)
/** Value for SCLH in I2C standard mode. */
#define I2C_SCLH_STANDARD       (60U)
/** Value for SCLL in I2C standard mode. */
#define I2C_SCLL_STANDARD       (I2C_SCLH_STANDARD)
/** Value for SCLH in I2C fast mode. */
#define I2C_SCLH_FAST           (15U)
/** Value for SCLL in I2C fast mode. */
#define I2C_SCLL_FAST           (I2C_SCLH_FAST)
/** Value for SCLH in I2C fast mode plus. */
#define I2C_SCLH_FAST_PLUS      (6U)
/** Value for SCLL in I2C fast mode plus. */
#define I2C_SCLL_FAST_PLUS      (I2C_SCLH_FAST_PLUS)
/** Bitmask for SCLL and SCLH register. */
#define I2C_SCL_MASK            (0x0000FFFF)

/** The available I2C modes of LPC1343. */
typedef enum
{
    I2C_STANDARD_MODE           /**<  100 kHz */
,   I2C_FAST_MODE               /**<  400 kHz */
,   I2C_FAST_MODE_PLUS          /**< 1000 kHz*/
} I2C_MODE;

/** @brief Function I2C_init initializes the I2C module.
 *  @param  mode The I2C mode to operate in.
 *  @return Bool
 *  @retval TRUE Initialization successful
 *  @retval FALSE Initialization failed
 */
Bool I2C_init (I2C_MODE mode);



#endif /* INC_I2C_H_ */
