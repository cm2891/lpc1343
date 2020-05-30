/**
 * 	@file       spp.h
 * 	@brief      Header file for LPC1343 SPI
 * 	@author     Christian Matar
 */

#ifndef INC_SPP_H_
#define INC_SPP_H_

#include "board.h"

/**
 *  @enum   SPP_WORD_SIZE
 *  @brief  The enums define the word size for the transfer.
 */
typedef enum
{
    SPP_WORD_SIZE_04_BIT = 0x3
,   SPP_WORD_SIZE_05_BIT = 0x4
,   SPP_WORD_SIZE_06_BIT = 0x5
,   SPP_WORD_SIZE_07_BIT = 0x6
,   SPP_WORD_SIZE_08_BIT = 0x7
,   SPP_WORD_SIZE_09_BIT = 0x8
,   SPP_WORD_SIZE_10_BIT = 0x9
,   SPP_WORD_SIZE_11_BIT = 0xA
,   SPP_WORD_SIZE_12_BIT = 0xB
,   SPP_WORD_SIZE_13_BIT = 0xC
,   SPP_WORD_SIZE_14_BIT = 0xD
,   SPP_WORD_SIZE_15_BIT = 0xE
,   SPP_WORD_SIZE_16_BIT = 0xF
} SPP_WORD_SIZE;

/** The SPP shall communicate using the SPI format. */
#define SPP_FORMAT_SPI              (0x0 << 4)
/** The SPP shall communicate using the TI format. */
#define SPP_FORMAT_TI               (0x1 << 4)
/** The SPP shall communicate using the MICRO format. */
#define SPP_FORMAT_MICRO            (0x2 << 4)
/** Defines the CLK polarity to be LOW. */
#define SPP_CLK_POL_LOW             (0 << 6)
/** Defines the CLK polarity to be HIGH. */
#define SPP_CLK_POL_HIGH            (1 << 6)
/** Power bit for SPP module in SYSAHBCLKCTRL */
#define SPP_SYSAHBCLKCTRL_POWER     (11U)
/** LSB of bitfield DSS in the control register. */
#define SPP_CR_DSS_LSB              (0U)
/** LSB of bitfield FRF in the control register. */
#define SPP_CR_FRF_LSB              (4U)
/** LSB of bitfield CPOL in the control register. */
#define SPP_CR_CPOL_LSB             (6U)
/** LSB of bitfield CPHA in the control register. */
#define SPP_CR_CPHA_LSB             (7U)
/** LSB of bitfield SCR in the control register. */
#define SPP_CR_SCR_LSB              (8U)
/** Bitmask for control register of SPP. The register has the following layout:
 *      [3:0]       DSS
 *      [5:4]       FRF
 *      [6:6]       CPOL
 *      [7:7]       CPHA
 *      [15:8]      SCR
 *      [31:16]     RESERVED
 */
#define SPP_CR_MASK                 ((uint32_t)0x0000FFFF)
/** Bitmask for CPSR. */
#define SPP_CPSR_MASK               ((uint32_t)0x000000FF)
/** Bitmask for DATA. */
#define SPP_DATA_MASK               ((uint32_t)0x0000FFFF)
/** Bitmask for DIV in SSP0CLKDIV. */
#define SPP_DIV_MASK                ((uint32_t)0x000000FF)

/**
 *  @struct SPP_STATUS
 *  @brief  Structure SPP_STATUS reflects the SSP0SSR register.
 */
typedef struct
{
    Bool TFE;       /**< 1: Transmit FIFO is empty, 0: else */
    Bool TNF;       /**< 1: Transmit FIFO is not full, 0: else */
    Bool RNE;       /**< 1: Receive FIFO is not empty, 0: else */
    Bool RFF;       /**< 1: Receive FIFO is full, 0: else */
    Bool BSY;       /**< 1: SPP is sending/receiving, 0: idle */
} SPP_STATUS;

/**
 *  @brief      Function SPP_init configures the LPC's SPP unit.
 *  @param[in]  frf Defines the frame format (SPI, TI, MICRO)
 *  @param[in]  cpol Defines the clock out polarity.
 *  @param[in]  cpha Defines the clock out phase.
 *  @param[in]  scr Defines the serial clock rate.
 *  @param[in]  prescale_val Defines the prescaler value of register CPSDVSR.
 *  @param[in]  clk_div Defines the clock divider value of register DIV.
 *  @return     void
 */
void SPP_init ( SPP_WORD_SIZE dss
              , uint8_t frf
              , Bool cpol
              , Bool cpha
              , uint8_t scr
              , uint8_t prescale_val
              , uint8_t clk_div
              );

/**
 *  @brief      Function SPP_write sends a 16-bit word to the SPP.
 *  @param[in]  data the data to be written. The high word will be masked.
 *  @return     void
 */
void SPP_write (uint32_t data);

/**
 *  @brief      Function SPP_read reads a 16-bit word from the SPP.
 *  @return     uint32_t
 *  @retval     The 16-bit word from the SPP.
 */
uint32_t SPP_read ();

/**
 *  @brief      Function SPP_get_status gets the status of the SPP from register
 *              <b>SSP0SR</b>.
 *  @param[in]  status a pointer to a structure <b>SPP_STATUS</b>, where the
 *              regiter's values will be stored to.
 *  @return     Bool
 *  @retval     FALSE Retrieving status failed.
 *  @retval     TRUE Retrieving status succeeded.
 */
Bool SPP_get_status (SPP_STATUS *status);

#endif /* INC_SPP_H_ */
