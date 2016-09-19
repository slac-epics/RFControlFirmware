/******************************************************
 * addrMap_sis8300_eicsys_iqfb.h
 * 
 * Automatically generated from pakg_RFController_config.vhd
 * Do not modify ... 
 * Sat Jul 09 21:55:53 2011
 *
 * Modified by: Zheqiao Geng
 * Modified on: 2011.07.10
 * Description: Change the macro name to avoid duplication
 * 
 * Modified by: Zheqiao Geng
 * Modified on: 2011.08.03
 * Description: Add the definitions for the firmware of LLRF-SIS8300-R-0-0-1
 *
 * Modified by: Zheqiao Geng
 * Modified on: 2/5/2013
 * Description: Add the new registers implemented for firmware LLRF_SIS8300-R1-0-0
 *
 * Modified by: Zheqiao Geng
 * Modified on: 3/3/2013
 * Description: Fit to the firmware with EICSYS platform
 ******************************************************/
#ifndef ADDRMAP_SIS8300_EICSYS_IQFB_H
#define ADDRMAP_SIS8300_EICSYS_IQFB_H

#include "sis8300_reg.h"                                                 /* platform firmware map */

/*-------------------------------- */
/* constant definitions            */
/*-------------------------------- */
/* Firmware info */

/* Configuration for the platform modules and global settings */
/* ADC and DAC */
#define CON_SIS8300_EICSYS_IQFB_ADC_DATA_SIZE       ( 16)                /* bits number of the ADC    */
#define CON_SIS8300_EICSYS_IQFB_DAC_DATA_SIZE       ( 16)                /* bits number of the DAC */
#define CON_SIS8300_EICSYS_IQFB_ADC_CHANNEL_NUM     ( 10)                /* channel number of the ADC */
#define CON_SIS8300_EICSYS_IQFB_DAC_CHANNEL_NUM     ( 2)                 /* channel number of the DAC */

/* register access     */
#define CON_SIS8300_EICSYS_IQFB_REG_ADDR_SIZE       ( 32)                /* 32 bits register address bus */
#define CON_SIS8300_EICSYS_IQFB_REG_DATA_SIZE       ( 32)                /* 32 bits register data bus */

/* buffer access */
#define CON_SIS8300_EICSYS_IQFB_BUF_ADDR_SIZE       ( 32)
#define CON_SIS8300_EICSYS_IQFB_BUF_DATA_SIZE       ( 32)

/* DSP data size */
#define CON_SIS8300_EICSYS_IQFB_DSP_DATA_SIZE      ( 18)                 /* compatible with the DSP core in the FPGA, for main stream data */
#define CON_SIS8300_EICSYS_IQFB_DSP_COEF_SIZE      ( 18)                 /* compatible with the DSP core in the FPGA, for coefficients */

/* configuration for the RF controller core modules */
/* RFControlDAQ */
#define CON_SIS8300_EICSYS_IQFB_DAQ_DATA_SIZE      ( 16)                 /* 16 bits buffer */

/* RFSignalDetection */
#define CON_SIS8300_EICSYS_IQFB_ENA_NONIQ          ( 1)                  /* 1 to enable the non-IQ demodulation (119MHz for 25.5MHz, 14 points for 3 cycles) */

/* RFSignalControl     */
#define CON_SIS8300_EICSYS_IQFB_IQ_SP_TAB_DEPTH    ( 1024)               /* for iq set point table) */

/* KBVBasedFeedback */
#define CON_SIS8300_EICSYS_IQFB_KBV_SP_TAB_DEPTH   ( 1024)               /* for klyston beam voltage */

/* Rotation table length */
#define CON_SIS8300_EICSYS_IQFB_DRV_ROT_TAB_DEPTH  ( 2048)               /* rotation table for the RF signal actuation */

/* RF system simulator */
#define CON_SIS8300_EICSYS_IQFB_ENA_SIM            ( 1)                  /* 1 to enable the simulator */

/*-------------------------------- */
/* type definitions */
/*-------------------------------- */

/*-------------------------------- */
/* register addresses */
/* all registers are defined in the RFController_top module */
/* a). each module has 32 addresses reserved so that later they can be extended without redefining the address  */
/*     of other modules */
/*--------------------------------     */
#define CON_SIS8300_EICSYS_IQFB_REG_ADDR_START             ( 0x0)                                     /* start address of the internal registers */

/* global */
#define CON_SIS8300_EICSYS_IQFB_REG_ADDR_OFFSET_GLOBAL     ( CON_SIS8300_EICSYS_IQFB_REG_ADDR_START + 0)       

#define CON_SIS8300_EICSYS_IQFB_REG_ADDR_FRIMWARE_NAME     ( CON_SIS8300_EICSYS_IQFB_REG_ADDR_OFFSET_GLOBAL + 0 * 4)        /* R */
#define CON_SIS8300_EICSYS_IQFB_REG_ADDR_FIRMWARE_VERSION  ( CON_SIS8300_EICSYS_IQFB_REG_ADDR_OFFSET_GLOBAL + 1 * 4)        /* R */
#define CON_SIS8300_EICSYS_IQFB_REG_ADDR_SWITCH_CTRL       ( CON_SIS8300_EICSYS_IQFB_REG_ADDR_OFFSET_GLOBAL + 2 * 4)        /* W */
#define CON_SIS8300_EICSYS_IQFB_REG_ADDR_BUF_WR_ADDR       ( CON_SIS8300_EICSYS_IQFB_REG_ADDR_OFFSET_GLOBAL + 3 * 4)        /* W */
#define CON_SIS8300_EICSYS_IQFB_REG_ADDR_BUF_WR_DATA       ( CON_SIS8300_EICSYS_IQFB_REG_ADDR_OFFSET_GLOBAL + 4 * 4)        /* W */
#define CON_SIS8300_EICSYS_IQFB_REG_ADDR_WD_CNT            ( CON_SIS8300_EICSYS_IQFB_REG_ADDR_OFFSET_GLOBAL + 5 * 4)        /* R */
#define CON_SIS8300_EICSYS_IQFB_REG_ADDR_PLATFORM_STATUS   ( CON_SIS8300_EICSYS_IQFB_REG_ADDR_OFFSET_GLOBAL + 6 * 4)        /* R */
#define CON_SIS8300_EICSYS_IQFB_REG_ADDR_USE_STATUS        ( CON_SIS8300_EICSYS_IQFB_REG_ADDR_OFFSET_GLOBAL + 7 * 4)        /* RW */

/* triggerHandling (including race condtion detection and RF Timing) */
#define CON_SIS8300_EICSYS_IQFB_REG_ADDR_OFFSET_TRIGH      ( CON_SIS8300_EICSYS_IQFB_REG_ADDR_START + 64)    

#define CON_SIS8300_EICSYS_IQFB_REG_ADDR_RCFLAGS_ACC       ( CON_SIS8300_EICSYS_IQFB_REG_ADDR_OFFSET_TRIGH + 0 * 4)         /* R */
#define CON_SIS8300_EICSYS_IQFB_REG_ADDR_RCFLAGS_STDBY     ( CON_SIS8300_EICSYS_IQFB_REG_ADDR_OFFSET_TRIGH + 1 * 4)         /* R */
#define CON_SIS8300_EICSYS_IQFB_REG_ADDR_RCFLAGS_SPARE     ( CON_SIS8300_EICSYS_IQFB_REG_ADDR_OFFSET_TRIGH + 2 * 4)         /* R */

#define CON_SIS8300_EICSYS_IQFB_REG_ADDR_TRIG_MODE_SEL     ( CON_SIS8300_EICSYS_IQFB_REG_ADDR_OFFSET_TRIGH + 3 * 4)         /* W */
#define CON_SIS8300_EICSYS_IQFB_REG_ADDR_DELAY_ACC         ( CON_SIS8300_EICSYS_IQFB_REG_ADDR_OFFSET_TRIGH + 4 * 4)         /* W */
#define CON_SIS8300_EICSYS_IQFB_REG_ADDR_DELAY_STDBY       ( CON_SIS8300_EICSYS_IQFB_REG_ADDR_OFFSET_TRIGH + 5 * 4)         /* W */
#define CON_SIS8300_EICSYS_IQFB_REG_ADDR_DELAY_SPARE       ( CON_SIS8300_EICSYS_IQFB_REG_ADDR_OFFSET_TRIGH + 6 * 4)         /* W */
#define CON_SIS8300_EICSYS_IQFB_REG_ADDR_DIV_RATIO         ( CON_SIS8300_EICSYS_IQFB_REG_ADDR_OFFSET_TRIGH + 7 * 4)         /* W */

#define CON_SIS8300_EICSYS_IQFB_REG_ADDR_TRIG_INT_PERIOD   ( CON_SIS8300_EICSYS_IQFB_REG_ADDR_OFFSET_TRIGH + 8 * 4)         /* W */
#define CON_SIS8300_EICSYS_IQFB_REG_ADDR_RF_PULSE_LENGTH   ( CON_SIS8300_EICSYS_IQFB_REG_ADDR_OFFSET_TRIGH + 9 * 4)         /* W */
#define CON_SIS8300_EICSYS_IQFB_REG_ADDR_DIAG_TRIG_PERIOD  ( CON_SIS8300_EICSYS_IQFB_REG_ADDR_OFFSET_TRIGH + 10 * 4)        /* R */
#define CON_SIS8300_EICSYS_IQFB_REG_ADDR_PUL_CNT           ( CON_SIS8300_EICSYS_IQFB_REG_ADDR_OFFSET_TRIGH + 11 * 4)        /* R */

/* RFControlDAQ */
#define CON_SIS8300_EICSYS_IQFB_REG_ADDR_OFFSET_RFCDAQ     ( CON_SIS8300_EICSYS_IQFB_REG_ADDR_START + 128)    
    
#define CON_SIS8300_EICSYS_IQFB_REG_ADDR_DAQ_TRIG_DELAY    ( CON_SIS8300_EICSYS_IQFB_REG_ADDR_OFFSET_RFCDAQ + 0 * 4)        /* W */
#define CON_SIS8300_EICSYS_IQFB_REG_ADDR_IRQ_DELAY_CNT     ( CON_SIS8300_EICSYS_IQFB_REG_ADDR_OFFSET_RFCDAQ + 1 * 4)        /* R */
#define CON_SIS8300_EICSYS_IQFB_REG_ADDR_COEF_ID_TRIG      ( CON_SIS8300_EICSYS_IQFB_REG_ADDR_OFFSET_RFCDAQ + 2 * 4)        /* R */

#define CON_SIS8300_EICSYS_IQFB_REG_ADDR_DAQ_SIZE          ( CON_SIS8300_EICSYS_IQFB_REG_ADDR_OFFSET_RFCDAQ + 3 * 4)        /* W */
#define CON_SIS8300_EICSYS_IQFB_REG_ADDR_DAQ_ADDR          ( CON_SIS8300_EICSYS_IQFB_REG_ADDR_OFFSET_RFCDAQ + 4 * 4)        /* W */

/* RFController_main */
#define CON_SIS8300_EICSYS_IQFB_REG_ADDR_OFFSET_RFCM       ( CON_SIS8300_EICSYS_IQFB_REG_ADDR_START + 192)

#define CON_SIS8300_EICSYS_IQFB_REG_ADDR_REF_FBK_SEL       ( CON_SIS8300_EICSYS_IQFB_REG_ADDR_OFFSET_RFCM + 0 * 4)         /* W */

#define CON_SIS8300_EICSYS_IQFB_REG_ADDR_REF_PHAS_SP       ( CON_SIS8300_EICSYS_IQFB_REG_ADDR_OFFSET_RFCM + 1 * 4)         /* W */
#define CON_SIS8300_EICSYS_IQFB_REG_ADDR_ROT_COEF_FBK      ( CON_SIS8300_EICSYS_IQFB_REG_ADDR_OFFSET_RFCM + 2 * 4)         /* W */

#define CON_SIS8300_EICSYS_IQFB_REG_ADDR_FEEDFORWARD_I     ( CON_SIS8300_EICSYS_IQFB_REG_ADDR_OFFSET_RFCM + 3 * 4)         /* W */
#define CON_SIS8300_EICSYS_IQFB_REG_ADDR_FEEDFORWARD_Q     ( CON_SIS8300_EICSYS_IQFB_REG_ADDR_OFFSET_RFCM + 4 * 4)         /* W */

#define CON_SIS8300_EICSYS_IQFB_REG_ADDR_GAIN_I            ( CON_SIS8300_EICSYS_IQFB_REG_ADDR_OFFSET_RFCM + 5 * 4)         /* W */
#define CON_SIS8300_EICSYS_IQFB_REG_ADDR_GAIN_Q            ( CON_SIS8300_EICSYS_IQFB_REG_ADDR_OFFSET_RFCM + 6 * 4)         /* W */

#define CON_SIS8300_EICSYS_IQFB_REG_ADDR_INTG_START        ( CON_SIS8300_EICSYS_IQFB_REG_ADDR_OFFSET_RFCM + 7 * 4)         /* W */
#define CON_SIS8300_EICSYS_IQFB_REG_ADDR_INTG_END          ( CON_SIS8300_EICSYS_IQFB_REG_ADDR_OFFSET_RFCM + 8 * 4)         /* W */

#define CON_SIS8300_EICSYS_IQFB_REG_ADDR_APPL_START        ( CON_SIS8300_EICSYS_IQFB_REG_ADDR_OFFSET_RFCM + 9 * 4)         /* W */
#define CON_SIS8300_EICSYS_IQFB_REG_ADDR_APPL_END          ( CON_SIS8300_EICSYS_IQFB_REG_ADDR_OFFSET_RFCM + 10 * 4)        /* W */

#define CON_SIS8300_EICSYS_IQFB_REG_ADDR_ROT_COEF_ACT      ( CON_SIS8300_EICSYS_IQFB_REG_ADDR_OFFSET_RFCM + 11 * 4)        /* W */

#define CON_SIS8300_EICSYS_IQFB_REG_ADDR_OFFSET_I          ( CON_SIS8300_EICSYS_IQFB_REG_ADDR_OFFSET_RFCM + 12 * 4)        /* W */
#define CON_SIS8300_EICSYS_IQFB_REG_ADDR_OFFSET_Q          ( CON_SIS8300_EICSYS_IQFB_REG_ADDR_OFFSET_RFCM + 13 * 4)        /* W */

#define CON_SIS8300_EICSYS_IQFB_REG_ADDR_AMP_LIMIT_HI      ( CON_SIS8300_EICSYS_IQFB_REG_ADDR_OFFSET_RFCM + 14 * 4)        /* W */
#define CON_SIS8300_EICSYS_IQFB_REG_ADDR_AMP_LIMIT_LO      ( CON_SIS8300_EICSYS_IQFB_REG_ADDR_OFFSET_RFCM + 15 * 4)        /* W */

#define CON_SIS8300_EICSYS_IQFB_REG_ADDR_KLY_COEF_INP_SCALE ( CON_SIS8300_EICSYS_IQFB_REG_ADDR_OFFSET_RFCM + 16 * 4)       /* W */
#define CON_SIS8300_EICSYS_IQFB_REG_ADDR_KLY_COEF_TRANS_M11 ( CON_SIS8300_EICSYS_IQFB_REG_ADDR_OFFSET_RFCM + 17 * 4)       /* W */
#define CON_SIS8300_EICSYS_IQFB_REG_ADDR_KLY_COEF_TRANS_M12 ( CON_SIS8300_EICSYS_IQFB_REG_ADDR_OFFSET_RFCM + 18 * 4)       /* W */
#define CON_SIS8300_EICSYS_IQFB_REG_ADDR_KLY_COEF_TRANS_M21 ( CON_SIS8300_EICSYS_IQFB_REG_ADDR_OFFSET_RFCM + 19 * 4)       /* W */
#define CON_SIS8300_EICSYS_IQFB_REG_ADDR_KLY_COEF_TRANS_M22 ( CON_SIS8300_EICSYS_IQFB_REG_ADDR_OFFSET_RFCM + 20 * 4)       /* W */

#define CON_SIS8300_EICSYS_IQFB_REG_ADDR_SLED_COEF_INP_SCALE ( CON_SIS8300_EICSYS_IQFB_REG_ADDR_OFFSET_RFCM + 21 * 4)      /* W */
#define CON_SIS8300_EICSYS_IQFB_REG_ADDR_SLED_COEF_TRANS_M11 ( CON_SIS8300_EICSYS_IQFB_REG_ADDR_OFFSET_RFCM + 22 * 4)      /* W */
#define CON_SIS8300_EICSYS_IQFB_REG_ADDR_SLED_COEF_TRANS_M12 ( CON_SIS8300_EICSYS_IQFB_REG_ADDR_OFFSET_RFCM + 23 * 4)      /* W */
#define CON_SIS8300_EICSYS_IQFB_REG_ADDR_SLED_COEF_TRANS_M21 ( CON_SIS8300_EICSYS_IQFB_REG_ADDR_OFFSET_RFCM + 24 * 4)      /* W */
#define CON_SIS8300_EICSYS_IQFB_REG_ADDR_SLED_COEF_TRANS_M22 ( CON_SIS8300_EICSYS_IQFB_REG_ADDR_OFFSET_RFCM + 25 * 4)      /* W */

#define CON_SIS8300_EICSYS_IQFB_REG_ADDR_COEF_ID_OFF        ( CON_SIS8300_EICSYS_IQFB_REG_ADDR_OFFSET_RFCM + 26 * 4)       /* W */

#define CON_SIS8300_EICSYS_IQFB_REG_ADDR_CORR_LIMIT_I       ( CON_SIS8300_EICSYS_IQFB_REG_ADDR_OFFSET_RFCM + 27 * 4)       /* W */
#define CON_SIS8300_EICSYS_IQFB_REG_ADDR_CORR_LIMIT_Q       ( CON_SIS8300_EICSYS_IQFB_REG_ADDR_OFFSET_RFCM + 28 * 4)       /* W */

#define CON_SIS8300_EICSYS_IQFB_REG_ADDR_RFCTRL_STATUS      ( CON_SIS8300_EICSYS_IQFB_REG_ADDR_OFFSET_RFCM + 29 * 4)       /* R */

#define CON_SIS8300_EICSYS_IQFB_REG_ADDR_IMBALANCE_MATRIX_A1X   ( CON_SIS8300_EICSYS_IQFB_REG_ADDR_OFFSET_RFCM + 30 * 4)   /* W */
#define CON_SIS8300_EICSYS_IQFB_REG_ADDR_IMBALANCE_MATRIX_A2X   ( CON_SIS8300_EICSYS_IQFB_REG_ADDR_OFFSET_RFCM + 31 * 4)   /* W */

/**
 * Constant for DAQ buffers
 */
#define CON_SIS8300_EICSYS_IQFB_IQ_SP_TABLE_OFFSET      0x00010000
#define CON_SIS8300_EICSYS_IQFB_DRV_ROT_TABLE_OFFSET    0x00020000

#endif




