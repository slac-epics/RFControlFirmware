/****************************************************
 * FWControl_sis8300_eicsys_iqfb_board.h
 * 
 * This is the interface with the the RFControlBoard module
 *
 * Created by: Zheqiao Geng, gengzq@slac.stanford.edu
 * Created on: 2011.07.07
 * Description: Initial creation
 *
 * Modified by: Zheqiao Geng
 * Modified on: 2011.08.03
 * Description: Add the access for the firmware of LLRF-SIS8300-R-0-0-1
 * 
 * Modified by: Zheqiao Geng
 * Modified on: 11/09/2012
 * Description: Change the rotation coefficient fraction to 14 bit, this allow (-2, 2) range of the coefficients in firmware
 * 
 * Modified by: Zheqiao Geng
 * Modified on: 2/6/2013
 * Description: Implement the new functions for firmware LLRF_SIS8300-R1-0-0
 *
 * Modified by: Zheqiao Geng
 * Modified on: 3/6/2013
 * Description: Modify the implementation to fit the EICSYS firmware
 ****************************************************/
#ifndef FW_CONTROL_SIS8300_EICSYS_IQFB_BOARD_H
#define FW_CONTROL_SIS8300_EICSYS_IQFB_BOARD_H

#include "RFControlBoard_availableInterface.h"                                          /* only point to interact with the RFControlBoard module */                     
#include "addrMap_sis8300_eicsys_iqfb.h"                                                /* use the address map here */
#include "RFLib_signalProcess.h"

/**
 * Constants for board access 
 */
#define FWC_SIS8300_EICSYS_IQFB_CONST_ROT_COEF_FRACTION 14                                                  /* fraction bits number of the rotation coefficients */
#define FWC_SIS8300_EICSYS_IQFB_CONST_COR_COEF_FRACTION 14                                                  /* fraction bits number of the coefficients for I/Q modulator imbalance correction */
#define FWC_SIS8300_EICSYS_IQFB_CONST_GAIN_FRACTION     15                                                  /* fraction bits number of the feedback gain */
#define FWC_SIS8300_EICSYS_IQFB_CONST_PHS_FRACTION      13                                                  /* fraction bits number of the phase in radian */

#define FWC_SIS8300_EICSYS_IQFB_CONST_SP_TAB_BUF_DEPTH  CON_SIS8300_EICSYS_IQFB_IQ_SP_TAB_DEPTH             /* buffer length for writing to FPGA (for I/Q set point tables) */
#define FWC_SIS8300_EICSYS_IQFB_CONST_DRV_TAB_BUF_DEPTH CON_SIS8300_EICSYS_IQFB_DRV_ROT_TAB_DEPTH           /* buffer length for writing to FPGA (for driving chain rotation) */

#define FWC_SIS8300_EICSYS_IQFB_CONST_ADC_SAMPLE_MAX    65536                                               /* 64k points (65536) */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Interface functions
 */
/*--------------------------
 * common 
 *-------------------------- */
void *FWC_sis8300_eicsys_iqfb_func_getBoardHandle(const char *boardModuleName);                                             /* get the handle of the RF Control Board module */
void FWC_sis8300_eicsys_iqfb_func_getBoardInfo(void *boardHandle, char *deviceName, int *deviceOpened);                     /* get the information of the RF Control Board module */

#define FWC_sis8300_eicsys_iqfb_func_pullInterrupt(boardHandle) RFCB_API_pullInterrupt((RFCB_struc_moduleData *)(boardHandle), RFCB_DEV_DMA)      /* pull the interrupt at DMA device for EICSYS firmware */

/*--------------------------
 * platform firmware 
 *-------------------------- */                    
void FWC_sis8300_eicsys_iqfb_func_setSPI(void *boardHandle, unsigned int clkDiv2);                                          /* set the clock divider, ADC chips and DAC chips (with fixed value,later can make it changable) */
void FWC_sis8300_eicsys_iqfb_func_setADCClockSource(void *boardHandle, unsigned int src);
void FWC_sis8300_eicsys_iqfb_func_getPlatformInfo(void *boardHandle,                                                        /* get the board/platform firmware basic info, including the clock frequencies */
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
                                                  double *clkSPIFreq_MHz);

/*--------------------------
 * LLRF Controller firmware 
 *-------------------------- */
/* Fimrware settings */
__inline__ void  FWC_sis8300_eicsys_iqfb_func_setBits(void *boardHandle, unsigned int data);                                /* set the register for bits (switch control in the firmware) */
__inline__ void  FWC_sis8300_eicsys_iqfb_func_getBits(void *boardHandle, unsigned int *data); 

__inline__ void  FWC_sis8300_eicsys_iqfb_func_setDAQ(void *boardHandle, unsigned int offset, unsigned int pno);             /* set the DAQ offset and point number (for 256 bits) in FPGA */

__inline__ void  FWC_sis8300_eicsys_iqfb_func_setExtTrigDelayAcc(void *boardHandle,    double value_ns, double freq_MHz);   /* set the external trigger delay */
__inline__ void  FWC_sis8300_eicsys_iqfb_func_setExtTrigDelayStdby(void *boardHandle,  double value_ns, double freq_MHz);
__inline__ void  FWC_sis8300_eicsys_iqfb_func_setExtTrigDelaySpare(void *boardHandle,  double value_ns, double freq_MHz);
__inline__ void  FWC_sis8300_eicsys_iqfb_func_setIntTrigPeriod(void *boardHandle, double value_ms, double freq_MHz);        /* set the internal trigger period */
__inline__ void  FWC_sis8300_eicsys_iqfb_func_setRFPulseLength(void *boardHandle, double value_ns, double freq_MHz);        /* set the RF pulse length */
__inline__ void  FWC_sis8300_eicsys_iqfb_func_setDAQTrigDelay(void *boardHandle,  double value_ns, double freq_MHz);        /* set the DAQ trigger delay (relative to the global trigger) */

__inline__ void  FWC_sis8300_eicsys_iqfb_func_selectRefFbkChannel(void *boardHandle, unsigned int refCh, unsigned int fbkCh);  /* select the reference and feedback channel */
__inline__ void  FWC_sis8300_eicsys_iqfb_func_selectTrigMode(void *boardHandle, unsigned int trigMode);                     /* select the trigger mode */

__inline__ void  FWC_sis8300_eicsys_iqfb_func_setUsageStatus(void *boardHandle, unsigned int useStatus);                    /* set the usage staus of the board */

__inline__ void  FWC_sis8300_eicsys_iqfb_func_setTrigRateDiv(void *boardHandle, unsigned int trigRateDiv);                  /* set the RF trigger division ratio */

__inline__ void  FWC_sis8300_eicsys_iqfb_func_setRefPhaSP(void *boardHandle, double phaSP_deg);                             /* set the reference phase set point */

__inline__ void  FWC_sis8300_eicsys_iqfb_func_setFbkVectorRotation(void *boardHandle, double scale, double rotAngle_deg);   /* scale and rotate the feedback signal */
__inline__ void  FWC_sis8300_eicsys_iqfb_func_setActVectorRotation(void *boardHandle, double scale, double rotAngle_deg);   /* scale and rotate the actuation signal */

__inline__ void  FWC_sis8300_eicsys_iqfb_func_setFeedforward_I(void *boardHandle, double value_MV, double factor);          /* set the feedforward value for I component */
__inline__ void  FWC_sis8300_eicsys_iqfb_func_setFeedforward_Q(void *boardHandle, double value_MV, double factor);          /* set the feedforward value for Q component */

__inline__ void  FWC_sis8300_eicsys_iqfb_func_setGain_I(void *boardHandle, double value);                                   /* set the gain value for I component */
__inline__ void  FWC_sis8300_eicsys_iqfb_func_setGain_Q(void *boardHandle, double value);                                   /* set the gain value for Q component */

__inline__ void  FWC_sis8300_eicsys_iqfb_func_setFeedbackCorrLimits(void *boardHandle, unsigned int limit_i, unsigned int limit_q); /* set the feedback correction limits */

__inline__ void  FWC_sis8300_eicsys_iqfb_func_setIntgStart(void *boardHandle, double value_ns, double freq_MHz);            /* start time for integration, relative to the trigger */
__inline__ void  FWC_sis8300_eicsys_iqfb_func_setIntgEnd(void *boardHandle,   double value_ns, double freq_MHz);             

__inline__ void  FWC_sis8300_eicsys_iqfb_func_setApplStart(void *boardHandle, double value_ns, double freq_MHz);            /* start time for applying the correction, relative to the trigger */
__inline__ void  FWC_sis8300_eicsys_iqfb_func_setApplEnd(void *boardHandle,   double value_ns, double freq_MHz);             

__inline__ void  FWC_sis8300_eicsys_iqfb_func_setDACOffset_I(void *boardHandle, unsigned int offset);                       /* set the DAC offset */
__inline__ void  FWC_sis8300_eicsys_iqfb_func_setDACOffset_Q(void *boardHandle, unsigned int offset);

__inline__ void  FWC_sis8300_eicsys_iqfb_func_setAmpLimitHi(void *boardHandle,  unsigned int limit);                        /* set the output limits */
__inline__ void  FWC_sis8300_eicsys_iqfb_func_setAmpLimitLo(void *boardHandle,  unsigned int limit);

__inline__ void  FWC_sis8300_eicsys_iqfb_func_setIQSPTable(void *boardHandle, unsigned int pno, double *ISPTable, double *QSPTable);                        /* set the set point table */
__inline__ void  FWC_sis8300_eicsys_iqfb_func_setDrvRotationTable(void *boardHandle, unsigned int pno, double *scaleTable, double *rotAngleTable_deg);      /* set the driving chain rotation table */

__inline__ void  FWC_sis8300_eicsys_iqfb_func_setNonIQCoefOffset(void *boardHandle, unsigned int offset);                                                   /* set the offset for non-IQ demodulation coefficients */

__inline__ void  FWC_sis8300_eicsys_iqfb_func_setImbalanceCorrMatrix(void *boardHandle, double a11, double a12, double a21, double a22);                    /* set the imbalance correction matrix */

/* Fimrware readings */
void FWC_sis8300_eicsys_iqfb_func_getAppFwInfo(void *boardHandle, unsigned int *firmwareName, unsigned int *majorVer, unsigned int *minorVer, unsigned int *buildNum);

__inline__ void  FWC_sis8300_eicsys_iqfb_func_getUsageStatus(void *boardHandle, unsigned int *useStatus);

__inline__ void  FWC_sis8300_eicsys_iqfb_func_getRaceConditionFlags(void *boardHandle, unsigned int *accFlags, unsigned int *stdbyFlags, unsigned int *spareFlags);

__inline__ void  FWC_sis8300_eicsys_iqfb_func_getPulseCounter(void *boardHandle, unsigned int *pulseCnt);
__inline__ void  FWC_sis8300_eicsys_iqfb_func_getMeaTrigPeriod(void *boardHandle, double *value_ms, double freq_MHz);       /* get the measurement trigger period */

__inline__ void  FWC_sis8300_eicsys_iqfb_func_getNonIQCoefCur(void *boardHandle, unsigned int *cur);

__inline__ void  FWC_sis8300_eicsys_iqfb_func_getWatchDogCnt(void *boardHandle, unsigned int *cnt);
__inline__ void  FWC_sis8300_eicsys_iqfb_func_getFwStatus(void *boardHandle, unsigned int *platformStatus, unsigned int *RFCtrlStatus);

__inline__ void  FWC_sis8300_eicsys_iqfb_func_getAllDAQData(void *boardHandle, unsigned int pno, unsigned int pno_old,      /* data from DRAM */
                                                            short *ADC0Data, short *ADC1Data,                               /* fixed for Ch0 and Ch1 */            
                                                            short *ADC2Data, short *ADC3Data,                               /* fixed for Ch2 and Ch3 */  
                                                            short *ADC4Data, short *ADC5Data,                               /* fixed for Ch4 and Ch5 */  
                                                            short *ADC6Data, short *ADC7Data,                               /* fixed for Ch6 and Ch7 */  
                                                            short *ADC8Data, short *ADC9Data,                               /* fixed for Ch8 and Ch9 */  
                                                            short *dataCh10, short *dataCh11,                               /* Ch10 - ref_i or err_i; Ch11 - ref_q or err_q */
                                                            short *dataCh12, short *dataCh13,                               /* Ch12 - fbk_i or act_i; Ch13 - fbk_q or act_q */
                                                            short *dataCh14, short *dataCh15);                              /* Ch14 - tracked_i or dac_i; Ch11 - tracked_q or dac_q */

#ifdef __cplusplus
}
#endif

#endif


