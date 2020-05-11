#ifndef _SPH0645_H
#define _SPH0645_H

extern "C" {
#include "user_interface.h"
#include "i2s_reg.h"
#include "slc_register.h"
#include "esp8266_peri.h"
void rom_i2c_writeReg_Mask(int, int, int, int, int, int);
}

//#define DEBUG

#define I2S_CLK_FREQ      160000000  // Hz
#define I2S_24BIT         3     // I2S 24 bit half data
#define I2S_LEFT          2     // I2S RX Left channel

#define I2SI_DATA         12    // I2S data on GPIO12
#define I2SI_BCK          13    // I2S clk on GPIO13
#define I2SI_WS           14    // I2S select on GPIO14

#define SLC_BUF_CNT       8     // Number of buffers in the I2S circular buffer
#define SLC_BUF_LEN       64    // Length of one buffer, in 32-bit words.

/**
 * Convert I2S data.
 * Data is 18 bit signed, MSBit first, two's complement.
 * Note: We can only send 31 cycles from ESP8266 so we only
 * shift by 13 instead of 14.
 * The 240200 is a magic calibration number I haven't figured
 * out yet.
 */
#define convert(sample) (((int32_t)(sample) >> 13) - 240200)

typedef struct {
  uint32_t blocksize      : 12;
  uint32_t datalen        : 12;
  uint32_t unused         : 5;
  uint32_t sub_sof        : 1;
  uint32_t eof            : 1;
  volatile uint32_t owner : 1;

  uint32_t *buf_ptr;
  uint32_t *next_link_ptr;
} sdio_queue_t;

static sdio_queue_t i2s_slc_items[SLC_BUF_CNT];  // I2S DMA buffer descriptors
static uint32_t *i2s_slc_buf_pntr[SLC_BUF_CNT];  // Pointer to the I2S DMA buffer data
static volatile uint32_t rx_buf_cnt = 0;
static volatile uint32_t rx_buf_idx = 0;
static volatile bool rx_buf_flag = false;

void i2s_init();
void slc_init();
void i2s_set_rate(uint32_t rate);
void slc_isr(void *para);


/**
 * Initialise I2S as a RX master.
 */
void i2s_init()
{
  // Config RX pin function
  PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTDI_U, FUNC_I2SI_DATA);
  PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTCK_U, FUNC_I2SI_BCK);
  PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTMS_U, FUNC_I2SI_WS);

  // Enable a 160MHz clock
  I2S_CLK_ENABLE();

  // Reset I2S
  I2SC &= ~(I2SRST);
  I2SC |= I2SRST;
  I2SC &= ~(I2SRST);

  // Reset DMA
  I2SFC &= ~(I2SDE | (I2SRXFMM << I2SRXFM));

  // Enable DMA
  I2SFC |= I2SDE | (I2S_24BIT << I2SRXFM);

  // Set RX single channel (left)
  I2SCC &= ~((I2STXCMM << I2STXCM) | (I2SRXCMM << I2SRXCM));
  I2SCC |= (I2S_LEFT << I2SRXCM);
  i2s_set_rate(16667);

  // Set RX data to be received
  I2SRXEN = SLC_BUF_LEN;

  // Bits mode
  I2SC |= (15 << I2SBM);

  // Start receiver
  I2SC |= I2SRXS;
}

#endif //_SPH0645_H