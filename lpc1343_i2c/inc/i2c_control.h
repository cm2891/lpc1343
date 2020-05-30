/**
 *  @file       i2c_control.h
 *  @brief      Header file for I2C
 *  @author     Christian Matar
 */

#ifndef INC_I2C_CONTROL_H_
#define INC_I2C_CONTROL_H_

#include "board.h"

/** Positions of bits in register I2C0CONSET. */
typedef enum
{
    I2C_ASSERT_ACK_BIT  = 2U
,   I2C_SI_BIT
,   I2C_STO_BIT
,   I2C_STA_BIT
,   I2C_I2EN_BIT
} I2C_CONSET_BITS;

/** Positions of bits in register I2C0CONCLR. */
typedef enum
{
    I2C_ASSERT_ACKC_BIT = 2U
,   I2C_SIC_BIT
,   I2C_STAC_BIT        = 5U
,   I2C_I2ENC_BIT
} I2C_CONCLR_BITS;

/** @struct I2C_CTRL_SET_REG
 *  @brief Structure I2C_CTRL_SET_REG implements register I2C0CONSET.
 */
typedef struct
{
    Bool assert_ack;
    Bool irq;
    Bool stop;
    Bool start;
    Bool enable;
} I2C_CTRL_SET_REG;

/** @brief Structure I2C_CTRL_CLR_REG implements register I2C0CONCLR. */
typedef I2C_CTRL_SET_REG I2C_CTRL_CLR_REG;

/** Bitmask for data register. */
#define I2C_DATA_MASK       (0x000000FF)

/**
 * @brief   Function I2C_start sets bit <b>I2EN</b> in register
 *          <b>I2C0CONSET</b> to start the I2C communication.
 * @return  void
 */
void I2C_start ();

/**
 * @brief   Function I2C_stop sets bit <b>I2EN</b> in register <b>I2C0CONCLR</b>
 *          to stop the I2C communication.
 * @return  void
 */
void I2C_stop ();

/**
 * @brief       Function I2C_write_ctrl_set_reg configures the <b>I2C0CONSET</b>
 *              register.
 * @param[in]   set a pointer to structure <b>I2C_CTRL_SET_REG</b>, which holds
 *              the values for each bit of <b>I2C0CONSET</b>.
 * @param[in]   clr a pointer to structure <b>I2C_CTRL_CLR_REG</b>, which holds
 *              the values for each bit of <b>I2C0CONCLR</b>.
 * @return      Bool
 * @retval      FALSE configuration failed
 * @retval      TRUE configuration was successful
 */
Bool I2C_write_ctrl_regs (I2C_CTRL_SET_REG *set, I2C_CTRL_CLR_REG *clr);

/**
 * @brief       Function I2C_read_ctrl_set_reg reads the <b>I2C0CONSET</b>
 *              register.
 * @param[out]  set a pointer to structure <b>I2C_CTRL_SET_REG</b>, where the
 *              values for each bit of <b>I2C0CONSET</b> will be stored to.
 * @param[out]  clr a pointer to structure <b>I2C_CTRL_CLR_REG</b>, where the
 *              values for each bit of <b>I2C0CONCLR</b> will be stored to.
 * @return      Bool
 * @retval      FALSE reading failed
 * @retval      TRUE reading was successful
 */
Bool I2C_read_ctrl_regs (I2C_CTRL_SET_REG *set, I2C_CTRL_CLR_REG *clr);



#endif /* INC_I2C_CONTROL_H_ */
