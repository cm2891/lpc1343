/**
 *  @file       i2c_monitor.h
 *  @brief      Header file for I2C
 *  @author     Christian Matar
 */

#ifndef INC_I2C_MONITOR_H_
#define INC_I2C_MONITOR_H_

#include "board.h"

/** @struct I2C_MONITOR_REG
 *  @brief Structure I2C_MONITOR_REG reflects the register I2C0MMCTRL. */
typedef struct
{
    Bool MM_ENA;        /**< Enables the monitor mode. */
    Bool ENA_SCL;       /**< Enables the SCL output. */
    Bool MATCH_ALL;     /**< Select interrupt register match. */
} I2C_MONITOR_REG;

/** @brief      Function I2C_set_monitor configures the <b>I2C0MMCTRL</b>
 *              register.
 *  @param[in]  reg pointer to a structure holding the configuration values.
 *  @return     Bool
 *  @retval     FALSE configuration failed
 *  @retval     TRUE configuration succeeded
 */
Bool I2C_set_monitor (I2C_MONITOR_REG *reg);

/** @brief      Function I2C_get_monitor gets the values of <b>I2C0MMCTRL</b>
 *              register.
 *  @param[out] reg pointer to a structure where the configuration values will
 *              be writen to.
 *  @return     Bool
 *  @retval     FALSE configuration failed
 *  @retval     TRUE configuration succeeded
 */
Bool I2C_get_monitor (I2C_MONITOR_REG *reg);


#endif /* INC_I2C_MONITOR_H_ */
