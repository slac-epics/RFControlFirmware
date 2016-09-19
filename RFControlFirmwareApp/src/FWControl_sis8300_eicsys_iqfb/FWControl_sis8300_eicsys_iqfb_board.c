/****************************************************
 * FWControl_sis8300_eicsys_iqfb_board.c
 * 
 * This is the interface with the the RFControlBoard module
 *
 * Created by: Zheqiao Geng, gengzq@slac.stanford.edu
 * Created on: 2011.07.07
 * Description: Initial creation
 * 
 * Modified by: Zheqiao Geng
 * Modified on: 2/6/2013
 * Description: Implement the new functions for firmware LLRF_SIS8300-R1-0-0
 *
 * Modified by: Zheqiao Geng
 * Modified on: 3/6/2013
 * Description: Modify the implementation to fit the EICSYS firmware
 ****************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "FWControl_sis8300_eicsys_iqfb_board.h"

/*-------------------------------------------------------------
 * COMMON FUNCTION
 *-------------------------------------------------------------*/
/**
 * Get the handle of the RFControlBoard (a pointer of the data structure of the module)
 * Input:
 *   boardModuleName    : Name of the RFControlBoard module
 * Return:
 *   Address with the type of void of the data structure of the module
 */
void *FWC_sis8300_eicsys_iqfb_func_getBoardHandle(const char *boardModuleName)
{
    return (void *)RFCB_API_getModule(boardModuleName);
}

/**
 * Get the information of the board, the device name in the folder of "/dev" and if it is correctly opened
 */
void FWC_sis8300_eicsys_iqfb_func_getBoardInfo(void *boardHandle, char *deviceName, int *deviceOpened)
{
    RFCB_struc_moduleData *board = (RFCB_struc_moduleData *)boardHandle;

    RFCB_API_getModuleStatus(board, deviceName, deviceOpened, RFCB_DEV_USR);
}

/*-------------------------------------------------------------
 * PLATFORM FIRMWARE SETTINGS/READINGS
 *-------------------------------------------------------------*/
/**
 * Setup the AD9510, ADC chip and DAC chip. 
 * This function is provided to set all above to default values, which are enough for 
 *   the LLRF operation. Later if necessay, we will provide the possiblity to set them
 *   based on user's requirements
 * 
 * AD9510 channel configuration:
 * - chip 1:
 *      -- Out 0-3  not used
 *      -- Out 4    (FPGA DIV-CLK05)            : LVDS 3.5 mA
 *      -- Out 5    (ADC3-CLK, ch4/5)           : LVDS 3.5 mA
 *      -- Out 6    (ADC2-CLK, ch3/4)           : LVDS 3.5 mA
 *      -- Out 7    (ADC1-CLK, ch1/2)           : LVDS 3.5 mA
 * - chip 2:	
 *      -- Out 0-3  not used
 *      -- Out 4    (FPGA DIV-CLK69)            : LVDS 3.5 mA
 *      -- Out 5    (ADC5-CLK, ch8/9)           : LVDS 3.5 mA
 *      -- Out 6    (ADC4-CLK, ch6/7)           : LVDS 3.5 mA
 *      -- Out 7    (Frontpanel Clk, Harlink)   : LVDS 3.5 mA
 */
void FWC_sis8300_eicsys_iqfb_func_setSPI(void *boardHandle, unsigned int clkDiv2)
{
    RFCB_struc_moduleData *board = (RFCB_struc_moduleData *)boardHandle;
    
	/* to be implemented later, use the tools provided by EICSYS for testing */
}

/**
 * Set the selection of the ADC clock source
 * Input value (src):
 *      0:      RTM CLK2
 *      1:      Backplane CLK1
 *      2:      Backplane CLK2
 *      3:      EXTCLKA (Front Panel SMA clock)
 *      4:      EXTCLKB (Harlink)
 *      5:      Oscillator (250MHz)
 */
void FWC_sis8300_eicsys_iqfb_func_setADCClockSource(void *boardHandle, unsigned int src)
{
    RFCB_struc_moduleData *board = (RFCB_struc_moduleData *)boardHandle;

	/* to be implemented later, use the tools provided by EICSYS for testing */
}

/**
 * Get the platform firmware info (id and serial number)
 */
void FWC_sis8300_eicsys_iqfb_func_getPlatformInfo(void *boardHandle,
                                                  unsigned int *id, 
                                                  char *FPGAType,
                                                  char *compileTime,
                                                  double *clkMainFreq_MHz,
                                                  double *clkExt0Freq_MHz,
                                                  double *clkExt1Freq_MHz,
                                                  double *clkDDR00Freq_MHz,
                                                  double *clkDDR90Freq_MHz,
                                                  double *clkDDRDvFreq_MHz,
                                                  double *clkIDelayFreq_MHz,
                                                  double *clkSPIFreq_MHz)
{
    RFCB_struc_moduleData *board = (RFCB_struc_moduleData *)boardHandle;

    /* to be implemented later, use the tools provided by EICSYS for testing */
}

/*-------------------------------------------------------------
 * RF CONTROLLER FIRMWARE SETTINGS
 *-------------------------------------------------------------*/
/**
 * Set bits register in the FPGA
 */
void  FWC_sis8300_eicsys_iqfb_func_setBits(void *boardHandle, unsigned int data)
{
    RFCB_API_writeRegister((RFCB_struc_moduleData *)boardHandle, CON_SIS8300_EICSYS_IQFB_REG_ADDR_SWITCH_CTRL, data, RFCB_DEV_USR);   /* Write to the register */
}

void  FWC_sis8300_eicsys_iqfb_func_getBits(void *boardHandle, unsigned int *data)
{
    RFCB_API_readRegister((RFCB_struc_moduleData *)boardHandle, CON_SIS8300_EICSYS_IQFB_REG_ADDR_SWITCH_CTRL, data, RFCB_DEV_USR);
}

/**
 * Setup the DAQ module in FPGA. The offset is the memory starting address for data saving, pno is the point numer (16-bit data for 16 channels) that will be saved
 */
void  FWC_sis8300_eicsys_iqfb_func_setDAQ(void *boardHandle, unsigned int offset, unsigned int pno)
{
    RFCB_API_writeRegister((RFCB_struc_moduleData *)boardHandle, CON_SIS8300_EICSYS_IQFB_REG_ADDR_DAQ_ADDR, offset, RFCB_DEV_USR);
    RFCB_API_writeRegister((RFCB_struc_moduleData *)boardHandle, CON_SIS8300_EICSYS_IQFB_REG_ADDR_DAQ_SIZE, pno,    RFCB_DEV_USR);
}

/**
 * Set the external trigger (ACC/STDBY/SPARE) delay
 * Input:
 *   boardHandle        : Address of the data structure of the board moudle
 *   value_ns           : Delay value in ns
 *   freq_MHz           : Sampling frequency in MHz
 */
void  FWC_sis8300_eicsys_iqfb_func_setExtTrigDelayAcc(void *boardHandle, double value_ns, double freq_MHz)
{
    unsigned int data = (unsigned int)(value_ns * freq_MHz / 1000.0);
    RFCB_API_writeRegister((RFCB_struc_moduleData *)boardHandle, CON_SIS8300_EICSYS_IQFB_REG_ADDR_DELAY_ACC, data, RFCB_DEV_USR);    
}

void  FWC_sis8300_eicsys_iqfb_func_setExtTrigDelayStdby(void *boardHandle, double value_ns, double freq_MHz)
{
    unsigned int data = (unsigned int)(value_ns * freq_MHz / 1000.0);
    RFCB_API_writeRegister((RFCB_struc_moduleData *)boardHandle, CON_SIS8300_EICSYS_IQFB_REG_ADDR_DELAY_STDBY, data, RFCB_DEV_USR);    
}

void  FWC_sis8300_eicsys_iqfb_func_setExtTrigDelaySpare(void *boardHandle, double value_ns, double freq_MHz)
{
    unsigned int data = (unsigned int)(value_ns * freq_MHz / 1000.0);
    RFCB_API_writeRegister((RFCB_struc_moduleData *)boardHandle, CON_SIS8300_EICSYS_IQFB_REG_ADDR_DELAY_SPARE, data, RFCB_DEV_USR);    
}

/**
 * Set the internal trigger period
 * Input:
 *   boardHandle        : Address of the data structure of the board moudle
 *   value_ms           : Trigger period value in ms
 *   freq_MHz           : Sampling frequency in MHz
 */
void  FWC_sis8300_eicsys_iqfb_func_setIntTrigPeriod(void *boardHandle, double value_ms, double freq_MHz)
{
    unsigned int data = (unsigned int)(value_ms * freq_MHz * 1000.0);
    RFCB_API_writeRegister((RFCB_struc_moduleData *)boardHandle, CON_SIS8300_EICSYS_IQFB_REG_ADDR_TRIG_INT_PERIOD, data, RFCB_DEV_USR);        
}

/**
 * Set the RF pulse length
 * Input:
 *   boardHandle        : Address of the data structure of the board moudle
 *   value_ns           : Pulse length value in ns
 *   freq_MHz           : Sampling frequency in MHz
 */
void  FWC_sis8300_eicsys_iqfb_func_setRFPulseLength(void *boardHandle, double value_ns, double freq_MHz)
{
    unsigned int data = (unsigned int)(value_ns * freq_MHz / 1000.0);
    RFCB_API_writeRegister((RFCB_struc_moduleData *)boardHandle, CON_SIS8300_EICSYS_IQFB_REG_ADDR_RF_PULSE_LENGTH, data, RFCB_DEV_USR);     
}

/**
 * Set the DAQ trigger delay
 * Input:
 *   boardHandle        : Address of the data structure of the board moudle
 *   value_ns           : DAQ trigger delay value in ns
 *   freq_MHz           : Sampling frequency in MHz
 */
void  FWC_sis8300_eicsys_iqfb_func_setDAQTrigDelay(void *boardHandle, double value_ns, double freq_MHz)
{
    unsigned int data = (unsigned int)(value_ns * freq_MHz / 1000.0);
    RFCB_API_writeRegister((RFCB_struc_moduleData *)boardHandle, CON_SIS8300_EICSYS_IQFB_REG_ADDR_DAQ_TRIG_DELAY, data, RFCB_DEV_USR);     
}

/**
 * Select the reference and feedback channel. The higher 16 bits for reference channel and the lower 16 bits for feedback channel
 * Input:
 *   boardHandle        : Address of the data structure of the board moudle
 *   refCh              : The channel ID of the reference signal
 *   fbkCh              : The channel ID of the feedback signal
 */ 
void  FWC_sis8300_eicsys_iqfb_func_selectRefFbkChannel(void *boardHandle, unsigned int refCh, unsigned int fbkCh)
{
    unsigned int data = (refCh << 16) + (fbkCh & 0x0000FFFF);       
    RFCB_API_writeRegister((RFCB_struc_moduleData *)boardHandle, CON_SIS8300_EICSYS_IQFB_REG_ADDR_REF_FBK_SEL, data, RFCB_DEV_USR);    
}

/**
 * Set the trigger mode (combination of ACC/STDBY/SPARE triggers)
 */
void  FWC_sis8300_eicsys_iqfb_func_selectTrigMode(void *boardHandle, unsigned int trigMode)
{
    RFCB_API_writeRegister((RFCB_struc_moduleData *)boardHandle, CON_SIS8300_EICSYS_IQFB_REG_ADDR_TRIG_MODE_SEL, trigMode, RFCB_DEV_USR);    
}

/**
 * Set the usage status. The code will be defined by the applications 
 */
void  FWC_sis8300_eicsys_iqfb_func_setUsageStatus(void *boardHandle, unsigned int useStatus)
{
    RFCB_API_writeRegister((RFCB_struc_moduleData *)boardHandle, CON_SIS8300_EICSYS_IQFB_REG_ADDR_USE_STATUS, useStatus, RFCB_DEV_USR);    
}

/**
 * Set the trigger rate division ratio. This will apply to the final RF trigger 
 */
void  FWC_sis8300_eicsys_iqfb_func_setTrigRateDiv(void *boardHandle, unsigned int trigRateDiv)
{
    RFCB_API_writeRegister((RFCB_struc_moduleData *)boardHandle, CON_SIS8300_EICSYS_IQFB_REG_ADDR_DIV_RATIO, trigRateDiv, RFCB_DEV_USR);    
}

/**
 * Set the reference phase set point for reference tracking. The input is in degree and will be converted into radian and
 * coded by a 16-bit data with 13 bit of fraction
 */
void  FWC_sis8300_eicsys_iqfb_func_setRefPhaSP(void *boardHandle, double phaSP_deg)
{
    unsigned int pha = (unsigned int)(RFLIB_degToRad(phaSP_deg) * pow(2, FWC_SIS8300_EICSYS_IQFB_CONST_PHS_FRACTION));
    RFCB_API_writeRegister((RFCB_struc_moduleData *)boardHandle, CON_SIS8300_EICSYS_IQFB_REG_ADDR_REF_PHAS_SP, pha, RFCB_DEV_USR);      
}

/**
 * Set the rotation coefficients for the feedback signal. The higher 16 bits is for cos and the lower 16 bits for sin. They all
 *   have 14 bits of fraction
 * Input:
 *   boardHandle        : Address of the data structure of the board moudle
 *   scale              : Scale factor of the feedback signal (should be in the range of [0, 2))
 *   rotAngle_deg       : Rotation angle (radian) of the feedback siganl
 */
void  FWC_sis8300_eicsys_iqfb_func_setFbkVectorRotation(void *boardHandle, double scale, double rotAngle_deg)
{
    unsigned int cs   = (unsigned int)(scale * cos(RFLIB_degToRad(rotAngle_deg)) * pow(2, FWC_SIS8300_EICSYS_IQFB_CONST_ROT_COEF_FRACTION));
    unsigned int sn   = (unsigned int)(scale * sin(RFLIB_degToRad(rotAngle_deg)) * pow(2, FWC_SIS8300_EICSYS_IQFB_CONST_ROT_COEF_FRACTION));    
    unsigned int data = (cs << 16) + (sn & 0x0000FFFF);
    RFCB_API_writeRegister((RFCB_struc_moduleData *)boardHandle, CON_SIS8300_EICSYS_IQFB_REG_ADDR_ROT_COEF_FBK, data, RFCB_DEV_USR);      
}

/**
 * Set the rotation coefficients for the actuation signal. The higher 16 bits is for cos and the lower 16 bits for sin. They all
 *   have 14 bits of fraction
 * Input:
 *   boardHandle        : Address of the data structure of the board moudle
 *   scale              : Scale factor of the actuation signal (should be in the range of [0, 2))
 *   rotAngle_deg       : Rotation angle (radian) of the actuation siganl
 */
void  FWC_sis8300_eicsys_iqfb_func_setActVectorRotation(void *boardHandle, double scale, double rotAngle_deg)
{
    unsigned int cs   = (unsigned int)(scale * cos(RFLIB_degToRad(rotAngle_deg)) * pow(2, FWC_SIS8300_EICSYS_IQFB_CONST_ROT_COEF_FRACTION));
    unsigned int sn   = (unsigned int)(scale * sin(RFLIB_degToRad(rotAngle_deg)) * pow(2, FWC_SIS8300_EICSYS_IQFB_CONST_ROT_COEF_FRACTION));    
    unsigned int data = (cs << 16) + (sn & 0x0000FFFF);
    RFCB_API_writeRegister((RFCB_struc_moduleData *)boardHandle, CON_SIS8300_EICSYS_IQFB_REG_ADDR_ROT_COEF_ACT, data, RFCB_DEV_USR);     
}

/**
 * Set the feed forward values
 * Input:
 *   boardHandle        : Address of the data structure of the board moudle
 *   value_MV           : Feed forward vlues in MV
 *   factor             : Factor to scale the physical unit to FPGA data 
 */
void  FWC_sis8300_eicsys_iqfb_func_setFeedforward_I(void *boardHandle, double value_MV, double factor)
{
    unsigned int data = (unsigned int)(value_MV * factor);
    RFCB_API_writeRegister((RFCB_struc_moduleData *)boardHandle, CON_SIS8300_EICSYS_IQFB_REG_ADDR_FEEDFORWARD_I, data, RFCB_DEV_USR);     
}

void  FWC_sis8300_eicsys_iqfb_func_setFeedforward_Q(void *boardHandle, double value_MV, double factor)
{
    unsigned int data = (unsigned int)(value_MV * factor);
    RFCB_API_writeRegister((RFCB_struc_moduleData *)boardHandle, CON_SIS8300_EICSYS_IQFB_REG_ADDR_FEEDFORWARD_Q, data, RFCB_DEV_USR);     
}

/**
 * Set the gain for the feedback
 * Input:
 *   boardHandle        : Address of the data structure of the board moudle
 *   value              : Gain value
 */
void  FWC_sis8300_eicsys_iqfb_func_setGain_I(void *boardHandle, double value)
{
    unsigned int data = (unsigned int)(value * pow(2, FWC_SIS8300_EICSYS_IQFB_CONST_GAIN_FRACTION));
    RFCB_API_writeRegister((RFCB_struc_moduleData *)boardHandle, CON_SIS8300_EICSYS_IQFB_REG_ADDR_GAIN_I, data, RFCB_DEV_USR);
}

void  FWC_sis8300_eicsys_iqfb_func_setGain_Q(void *boardHandle, double value)
{
    unsigned int data = (unsigned int)(value * pow(2, FWC_SIS8300_EICSYS_IQFB_CONST_GAIN_FRACTION));
    RFCB_API_writeRegister((RFCB_struc_moduleData *)boardHandle, CON_SIS8300_EICSYS_IQFB_REG_ADDR_GAIN_Q, data, RFCB_DEV_USR);
}

/**
 * Set the feedback correction limits
 */
void  FWC_sis8300_eicsys_iqfb_func_setFeedbackCorrLimits(void *boardHandle, unsigned int limit_i, unsigned int limit_q)
{
    RFCB_API_writeRegister((RFCB_struc_moduleData *)boardHandle, CON_SIS8300_EICSYS_IQFB_REG_ADDR_CORR_LIMIT_I, limit_i, RFCB_DEV_USR);
    RFCB_API_writeRegister((RFCB_struc_moduleData *)boardHandle, CON_SIS8300_EICSYS_IQFB_REG_ADDR_CORR_LIMIT_Q, limit_q, RFCB_DEV_USR);
}

/**
 * Set the time window for the integration
 * Input:
 *   boardHandle        : Address of the data structure of the board moudle
 *   value_ns           : Time value in ns
 *   freq_MHz           : Sampling frequency in MHz
 */
void  FWC_sis8300_eicsys_iqfb_func_setIntgStart(void *boardHandle, double value_ns, double freq_MHz)
{
    unsigned int data = (unsigned int)(value_ns * freq_MHz / 1000.0);
    RFCB_API_writeRegister((RFCB_struc_moduleData *)boardHandle, CON_SIS8300_EICSYS_IQFB_REG_ADDR_INTG_START, data, RFCB_DEV_USR);       
}

void  FWC_sis8300_eicsys_iqfb_func_setIntgEnd(void *boardHandle, double value_ns, double freq_MHz)
{
    unsigned int data = (unsigned int)(value_ns * freq_MHz / 1000.0);
    RFCB_API_writeRegister((RFCB_struc_moduleData *)boardHandle, CON_SIS8300_EICSYS_IQFB_REG_ADDR_INTG_END, data, RFCB_DEV_USR);       
}            

/**
 * Set the time window for applying correction
 * Input:
 *   boardHandle        : Address of the data structure of the board moudle
 *   value_ns           : Time value in ns
 *   freq_MHz           : Sampling frequency in MHz
 */
void  FWC_sis8300_eicsys_iqfb_func_setApplStart(void *boardHandle, double value_ns, double freq_MHz)
{
    unsigned int data = (unsigned int)(value_ns * freq_MHz / 1000.0);
    RFCB_API_writeRegister((RFCB_struc_moduleData *)boardHandle, CON_SIS8300_EICSYS_IQFB_REG_ADDR_APPL_START, data, RFCB_DEV_USR);       
}    

void  FWC_sis8300_eicsys_iqfb_func_setApplEnd(void *boardHandle, double value_ns, double freq_MHz)
{
    unsigned int data = (unsigned int)(value_ns * freq_MHz / 1000.0);
    RFCB_API_writeRegister((RFCB_struc_moduleData *)boardHandle, CON_SIS8300_EICSYS_IQFB_REG_ADDR_APPL_END, data, RFCB_DEV_USR);         
}

/**
 * Set the offset of the DAC
 * Input:
 *   boardHandle        : Address of the data structure of the board moudle
 *   offset             : Offset in digits
 */
void  FWC_sis8300_eicsys_iqfb_func_setDACOffset_I(void *boardHandle, unsigned int offset)
{
    RFCB_API_writeRegister((RFCB_struc_moduleData *)boardHandle, CON_SIS8300_EICSYS_IQFB_REG_ADDR_OFFSET_I, offset, RFCB_DEV_USR);
}

void  FWC_sis8300_eicsys_iqfb_func_setDACOffset_Q(void *boardHandle, unsigned int offset)
{
    RFCB_API_writeRegister((RFCB_struc_moduleData *)boardHandle, CON_SIS8300_EICSYS_IQFB_REG_ADDR_OFFSET_Q, offset, RFCB_DEV_USR);
}

/**
 * Set the limits for DAC output signal
 *   boardHandle        : Address of the data structure of the board moudle
 *   limit              : Limit value in digits
 */
void  FWC_sis8300_eicsys_iqfb_func_setAmpLimitHi(void *boardHandle, unsigned int limit)
{
    RFCB_API_writeRegister((RFCB_struc_moduleData *)boardHandle, CON_SIS8300_EICSYS_IQFB_REG_ADDR_AMP_LIMIT_HI , limit, RFCB_DEV_USR);
}

void  FWC_sis8300_eicsys_iqfb_func_setAmpLimitLo(void *boardHandle, unsigned int limit)
{
    RFCB_API_writeRegister((RFCB_struc_moduleData *)boardHandle, CON_SIS8300_EICSYS_IQFB_REG_ADDR_AMP_LIMIT_LO , limit, RFCB_DEV_USR);
}

/**
 * Set the I/Q set point table. The higher 16 bits is for I and the lower 16 bits for Q.
 * Input:
 *   boardHandle        : Address of the data structure of the board moudle
 *   pno                : Number of the points
 *   ISPTable           : set point table for I
 *   QSPTable           : set point table for Q
 */
void  FWC_sis8300_eicsys_iqfb_func_setIQSPTable(void *boardHandle, unsigned int pno, double *ISPTable, double *QSPTable)
{
    unsigned int i;
    unsigned int Idata;
    unsigned int Qdata;
    unsigned int data;
      
    for(i = 0; i < pno; i ++) {
        /* Make up the data */
        Idata = (unsigned int)(*(ISPTable + i));
        Qdata = (unsigned int)(*(QSPTable + i)); 
        data = (Idata << 16) + (Qdata & 0x0000FFFF);

        /* Write to the firmware via two registers */
        RFCB_API_writeRegister((RFCB_struc_moduleData *)boardHandle, CON_SIS8300_EICSYS_IQFB_REG_ADDR_BUF_WR_ADDR, CON_SIS8300_EICSYS_IQFB_IQ_SP_TABLE_OFFSET + i, RFCB_DEV_USR);         /* address */
        RFCB_API_writeRegister((RFCB_struc_moduleData *)boardHandle, CON_SIS8300_EICSYS_IQFB_REG_ADDR_BUF_WR_DATA, data, RFCB_DEV_USR);                                                   /* data */        
    }
    
    RFCB_API_writeRegister((RFCB_struc_moduleData *)boardHandle, CON_SIS8300_EICSYS_IQFB_REG_ADDR_BUF_WR_ADDR, 0, RFCB_DEV_USR);      /* disable the writing */    
}

/**
 * Set the driving chain rotoation table. The higher 16 bits is for cos and the lower 16 bits for sin. They all
 *   have 14 bits of fraction
 * Input:
 *   boardHandle        : Address of the data structure of the board moudle
 *   pno                : Number of the points
 *   scaleTable         : Table of the scales (should be [0, 1])
 *   rotAngleTable_deg  : Table of the rotation angle in radian
 */
void  FWC_sis8300_eicsys_iqfb_func_setDrvRotationTable(void *boardHandle, unsigned int pno, double *scaleTable, double *rotAngleTable_deg)
{
    unsigned int i;
    unsigned int cs;
    unsigned int sn;
    unsigned int data;
  
    for(i = 0; i < pno; i ++) {
        /* Make up the data */
        cs   = (unsigned int)(*(scaleTable + i) * cos(RFLIB_degToRad(*(rotAngleTable_deg + i))) * pow(2, FWC_SIS8300_EICSYS_IQFB_CONST_ROT_COEF_FRACTION));
        sn   = (unsigned int)(*(scaleTable + i) * sin(RFLIB_degToRad(*(rotAngleTable_deg + i))) * pow(2, FWC_SIS8300_EICSYS_IQFB_CONST_ROT_COEF_FRACTION)); 
        data = (cs << 16) + (sn & 0x0000FFFF);

        /* Write to the firmware via two registers */
        RFCB_API_writeRegister((RFCB_struc_moduleData *)boardHandle, CON_SIS8300_EICSYS_IQFB_REG_ADDR_BUF_WR_ADDR, CON_SIS8300_EICSYS_IQFB_DRV_ROT_TABLE_OFFSET + i, RFCB_DEV_USR);       /* address */
        RFCB_API_writeRegister((RFCB_struc_moduleData *)boardHandle, CON_SIS8300_EICSYS_IQFB_REG_ADDR_BUF_WR_DATA, data, RFCB_DEV_USR);                                                   /* data */        
    }
    
    RFCB_API_writeRegister((RFCB_struc_moduleData *)boardHandle, CON_SIS8300_EICSYS_IQFB_REG_ADDR_BUF_WR_ADDR, 0, RFCB_DEV_USR);      /* disable the writing */    
}

/** 
 * Set the non-IQ coefficient index offset value (will be valid only you press the apply button)
 */
void  FWC_sis8300_eicsys_iqfb_func_setNonIQCoefOffset(void *boardHandle, unsigned int offset)
{
    RFCB_API_writeRegister((RFCB_struc_moduleData *)boardHandle, CON_SIS8300_EICSYS_IQFB_REG_ADDR_COEF_ID_OFF, offset, RFCB_DEV_USR);
}

/**
 * set the imbalance correction matrix of the vector modulator. 
 * Please note that the element abs values should be smaller than 1
 */
void  FWC_sis8300_eicsys_iqfb_func_setImbalanceCorrMatrix(void *boardHandle, double a11, double a12, double a21, double a22)
{
    unsigned int hw1x, hw2x;            /* high 16bit words */
    unsigned int lw1x, lw2x;            /* low 16bit words */

    unsigned int a1x = 0;               /* combine of a11 and a12 for one register */
    unsigned int a2x = 0;               /* combine of a21 and a22 for one register */

    hw1x  = (unsigned int)(a11 * pow(2, FWC_SIS8300_EICSYS_IQFB_CONST_COR_COEF_FRACTION));
    lw1x  = (unsigned int)(a12 * pow(2, FWC_SIS8300_EICSYS_IQFB_CONST_COR_COEF_FRACTION));
    hw2x  = (unsigned int)(a21 * pow(2, FWC_SIS8300_EICSYS_IQFB_CONST_COR_COEF_FRACTION));
    lw2x  = (unsigned int)(a22 * pow(2, FWC_SIS8300_EICSYS_IQFB_CONST_COR_COEF_FRACTION));
    
    a1x   = (hw1x << 16) + (lw1x & 0x0000FFFF);
    a2x   = (hw2x << 16) + (lw2x & 0x0000FFFF);

    RFCB_API_writeRegister((RFCB_struc_moduleData *)boardHandle, CON_SIS8300_EICSYS_IQFB_REG_ADDR_IMBALANCE_MATRIX_A1X, a1x, RFCB_DEV_USR);
    RFCB_API_writeRegister((RFCB_struc_moduleData *)boardHandle, CON_SIS8300_EICSYS_IQFB_REG_ADDR_IMBALANCE_MATRIX_A2X, a2x, RFCB_DEV_USR);
}

/*-------------------------------------------------------------
 * RF CONTROLLER FIRMWARE READINGS
 *-------------------------------------------------------------*/
/**
 * Get the board information. Including the firmware name (4 char string), major and minor version number and the build number
 */
void FWC_sis8300_eicsys_iqfb_func_getAppFwInfo(void *boardHandle, unsigned int *firmwareName, unsigned int *majorVer, unsigned int *minorVer, unsigned int *buildNum)
{
    unsigned int var_version;
    
    /* read the registers */    
    RFCB_API_readRegister((RFCB_struc_moduleData *)boardHandle, CON_SIS8300_EICSYS_IQFB_REG_ADDR_FRIMWARE_NAME,     firmwareName, RFCB_DEV_USR);
    RFCB_API_readRegister((RFCB_struc_moduleData *)boardHandle, CON_SIS8300_EICSYS_IQFB_REG_ADDR_FIRMWARE_VERSION,  &var_version, RFCB_DEV_USR);    

    /* build up the data */   
    *majorVer   = (var_version >> 24) & 0xFF;
    *minorVer   = (var_version >> 16) & 0xFF;
    *buildNum   = var_version & 0xFFFF;
}

/**
 * Get the usage status 
 */
void  FWC_sis8300_eicsys_iqfb_func_getUsageStatus(void *boardHandle, unsigned int *useStatus)
{
    RFCB_API_readRegister((RFCB_struc_moduleData *)boardHandle, CON_SIS8300_EICSYS_IQFB_REG_ADDR_USE_STATUS, useStatus, RFCB_DEV_USR);
}

/**
 * Get the race condition flags of ACC/STDBY/SPARE triggers 
 */
void  FWC_sis8300_eicsys_iqfb_func_getRaceConditionFlags(void *boardHandle, unsigned int *accFlags, unsigned int *stdbyFlags, unsigned int *spareFlags)
{
    RFCB_API_readRegister((RFCB_struc_moduleData *)boardHandle, CON_SIS8300_EICSYS_IQFB_REG_ADDR_RCFLAGS_ACC,   accFlags, RFCB_DEV_USR);
    RFCB_API_readRegister((RFCB_struc_moduleData *)boardHandle, CON_SIS8300_EICSYS_IQFB_REG_ADDR_RCFLAGS_STDBY, stdbyFlags, RFCB_DEV_USR);
    RFCB_API_readRegister((RFCB_struc_moduleData *)boardHandle, CON_SIS8300_EICSYS_IQFB_REG_ADDR_RCFLAGS_SPARE, spareFlags, RFCB_DEV_USR);
}

/**
 * Get the pulse counter
 */
void FWC_sis8300_eicsys_iqfb_func_getPulseCounter(void *boardHandle, unsigned int *pulseCnt)
{
    RFCB_API_readRegister((RFCB_struc_moduleData *)boardHandle, CON_SIS8300_EICSYS_IQFB_REG_ADDR_PUL_CNT, pulseCnt, RFCB_DEV_USR);
}

/**
 * Get the measured trigger period
 */
void  FWC_sis8300_eicsys_iqfb_func_getMeaTrigPeriod(void *boardHandle, double *value_ms, double freq_MHz)
{
    unsigned int data;
    RFCB_API_readRegister((RFCB_struc_moduleData *)boardHandle, CON_SIS8300_EICSYS_IQFB_REG_ADDR_DIAG_TRIG_PERIOD, &data, RFCB_DEV_USR);
    *value_ms = (double)data / freq_MHz / 1000.0;
}

/**
 * Get the non-IQ coefficient index of the first point for the ADC DAQ data
 */
void  FWC_sis8300_eicsys_iqfb_func_getNonIQCoefCur(void *boardHandle, unsigned int *cur)
{
    RFCB_API_readRegister((RFCB_struc_moduleData *)boardHandle, CON_SIS8300_EICSYS_IQFB_REG_ADDR_COEF_ID_TRIG, cur, RFCB_DEV_USR);
}

/**
 * Get the watch dog counter, this counter is a count of the ADC clock, so it can be used to diagnostic the ADC clock is OK or not
 */
void  FWC_sis8300_eicsys_iqfb_func_getWatchDogCnt(void *boardHandle, unsigned int *cnt)
{
    RFCB_API_readRegister((RFCB_struc_moduleData *)boardHandle, CON_SIS8300_EICSYS_IQFB_REG_ADDR_WD_CNT, cnt, RFCB_DEV_USR);
}

/**
 * Get the status of the platform firmware and the RF control firmware
 */
void  FWC_sis8300_eicsys_iqfb_func_getFwStatus(void *boardHandle, unsigned int *platformStatus, unsigned int *RFCtrlStatus)
{
    RFCB_API_readRegister((RFCB_struc_moduleData *)boardHandle, CON_SIS8300_EICSYS_IQFB_REG_ADDR_PLATFORM_STATUS, platformStatus, RFCB_DEV_USR);
    RFCB_API_readRegister((RFCB_struc_moduleData *)boardHandle, CON_SIS8300_EICSYS_IQFB_REG_ADDR_RFCTRL_STATUS,   RFCtrlStatus, RFCB_DEV_USR);
}

/**
 * Get all DAQ data from the FPGA
 * Input:
 *   boardHandle        : Address of the data structure of the board moudle
 *   pno                : Point number to be read (may be updated by CA put)
 *   pno_old            : Old point number match to the DMA transfer size and memery map size
 *   *data*             : Buffer to store the data, not the buffer should be large enough to store all data
 */
void  FWC_sis8300_eicsys_iqfb_func_getAllDAQData(void *boardHandle, unsigned int pno, unsigned int pno_old,                            
                                                            short *ADC0Data, short *ADC1Data,                               /* fixed for Ch0 and Ch1 */            
                                                            short *ADC2Data, short *ADC3Data,                               /* fixed for Ch2 and Ch3 */  
                                                            short *ADC4Data, short *ADC5Data,                               /* fixed for Ch4 and Ch5 */  
                                                            short *ADC6Data, short *ADC7Data,                               /* fixed for Ch6 and Ch7 */  
                                                            short *ADC8Data, short *ADC9Data,                               /* fixed for Ch8 and Ch9 */  
                                                            short *dataCh10, short *dataCh11,                               /* Ch10 - ref_i or err_i; Ch11 - ref_q or err_q */
                                                            short *dataCh12, short *dataCh13,                               /* Ch12 - fbk_i or act_i; Ch13 - fbk_q or act_q */
                                                            short *dataCh14, short *dataCh15)                               /* Ch14 - tracked_i or dac_i; Ch11 - tracked_q or dac_q */
{
    int i;
    unsigned int bufSize, loc_pno;
    short *bufDAQ = NULL;
	
    /* check the input */
    if(!boardHandle ||
       !ADC0Data || !ADC1Data || !ADC2Data || !ADC3Data || !ADC4Data || !ADC5Data || !ADC6Data || !ADC7Data || !ADC8Data || !ADC9Data ||
       !dataCh10 || !dataCh11 || !dataCh12 || !dataCh13 || !dataCh14 || !dataCh15) return;

    /* get the board handle */
    RFCB_struc_moduleData *board = (RFCB_struc_moduleData *)boardHandle;

    /* get the DMA pool address and current transfer size */
    bufDAQ = (short *)RFCB_API_getDMADataPoolPtr(board, &bufSize);

    /* handle the point number (each point has 16 2-byte data) */
	if(pno_old > bufSize / 32) 
       loc_pno = (unsigned int)(bufSize / 32);
    else
       loc_pno = pno_old;

    /* get the data */
    if(bufDAQ && loc_pno > 0) {
    	for(i = 0; i < loc_pno; i ++) {
            *(ADC0Data + i) = *(bufDAQ + 16 * i + 8);
            *(ADC1Data + i) = *(bufDAQ + 16 * i + 9);
            *(ADC2Data + i) = *(bufDAQ + 16 * i + 10);
            *(ADC3Data + i) = *(bufDAQ + 16 * i + 11);
            *(ADC4Data + i) = *(bufDAQ + 16 * i + 12);
            *(ADC5Data + i) = *(bufDAQ + 16 * i + 13);
            *(ADC6Data + i) = *(bufDAQ + 16 * i + 14);
            *(ADC7Data + i) = *(bufDAQ + 16 * i + 15);
            *(ADC8Data + i) = *(bufDAQ + 16 * i + 0);
            *(ADC9Data + i) = *(bufDAQ + 16 * i + 1);
            *(dataCh10 + i) = *(bufDAQ + 16 * i + 2);
            *(dataCh11 + i) = *(bufDAQ + 16 * i + 3);
            *(dataCh12 + i) = *(bufDAQ + 16 * i + 4);
            *(dataCh13 + i) = *(bufDAQ + 16 * i + 5);
            *(dataCh14 + i) = *(bufDAQ + 16 * i + 6);
            *(dataCh15 + i) = *(bufDAQ + 16 * i + 7);
        }
    } 

    /* set up the DMA for next pulse if the new pno is different than the old pno */
    if(pno != pno_old) {
        /* reuse the variable of loc_pno, limit the size to the maximum size of DMA pool (4MBytes) */
    	if(pno > RFCB_EICSYS_CONST_DMA_POOL_SIZE / 32) 
            loc_pno = (unsigned int)(RFCB_EICSYS_CONST_DMA_POOL_SIZE / 32);
        else
            loc_pno = pno;
   
        /* setup DMA, set the transfer size and remap the memory */
        if(RFCB_API_setupDMA(board, 0, loc_pno * 32) != 0) return;
    }
}








