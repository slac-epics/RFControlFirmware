/****************************************************
 * FWControl_sis8300_eicsys_iqfb.c
 * 
 * Realization of the virtual functions
 *
 * Created by: Zheqiao Geng, gengzq@slac.stanford.edu
 * Created on: 2011.07.07
 * Description: Initial creation
 *
 * Modified by: Zheqiao Geng
 * MOdified on: 2011.08.31
 * Description: Change the "wait interrupt" and "" to fit the user IRQ change for the firmware of LLRF_SIS8300-R0-1-5
 *
 * Modified by: Zheqiao Geng
 * Modified on: 2/5/2013
 * Description: Add the new functions implemented for firmware LLRF_SIS8300-R1-0-0
 *
 * Modified by: Zheqiao Geng
 * Modified on: 3/3/2013
 * Description: Fit to the firmware with EICSYS platform
 *
 * Modified by: Zheqiao Geng
 * Modified on: 3/26/2013
 * Description: Add the function to enable the DAQ trigger
 ****************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "FWControl_sis8300_eicsys_iqfb.h"
                  
/*======================================
 * Public Routines (virtual function implementation)
 *======================================*/
/**
 * Init the firmware data
 */
int FWC_sis8300_eicsys_iqfb_func_init(void *module)
{    
    FWC_sis8300_eicsys_iqfb_struc_data *arg = (FWC_sis8300_eicsys_iqfb_struc_data *)module;

    /* check input */
    if(!arg) return -1;

    /* Clean all data */
    memset(module, 0, sizeof(FWC_sis8300_eicsys_iqfb_struc_data));

    /* Init the local waveforms, there are no furthre calculation for the local waveforms */
    RFLIB_initRFWaveform(&arg -> rfData_refCh,         RFLIB_CONST_WF_SIZE);
    RFLIB_initRFWaveform(&arg -> rfData_fbkCh,         RFLIB_CONST_WF_SIZE);    
    
    RFLIB_initRFWaveform(&arg -> rfData_tracked,       RFLIB_CONST_WF_SIZE);
    RFLIB_initRFWaveform(&arg -> rfData_err,           RFLIB_CONST_WF_SIZE);
    
    RFLIB_initRFWaveform(&arg -> rfData_act,           RFLIB_CONST_WF_SIZE);
    RFLIB_initRFWaveform(&arg -> rfData_DACOut,        RFLIB_CONST_WF_SIZE);

    /* Init others */
    arg -> board_ADC_data[0] = arg -> board_ADC0_raw;
    arg -> board_ADC_data[1] = arg -> board_ADC1_raw;
    arg -> board_ADC_data[2] = arg -> board_ADC2_raw;
    arg -> board_ADC_data[3] = arg -> board_ADC3_raw;
    arg -> board_ADC_data[4] = arg -> board_ADC4_raw;
    arg -> board_ADC_data[5] = arg -> board_ADC5_raw;
    arg -> board_ADC_data[6] = arg -> board_ADC6_raw;
    arg -> board_ADC_data[7] = arg -> board_ADC7_raw;
    arg -> board_ADC_data[8] = arg -> board_ADC8_raw;
    arg -> board_ADC_data[9] = arg -> board_ADC9_raw;    

    return 0;       
}

/**
 * Get the board module handle for this firmware module
 */ 
int FWC_sis8300_eicsys_iqfb_func_getBoard(void *module, const char *boardModuleName)
{
    FWC_sis8300_eicsys_iqfb_struc_data *arg = (FWC_sis8300_eicsys_iqfb_struc_data *)module;

    if(!arg) return -1;

    arg -> board_handle = FWC_sis8300_eicsys_iqfb_func_getBoardHandle(boardModuleName);

    if(arg -> board_handle) return 0;
    else return -1;
}

/**
 * Trigger the DAQ data reading
 */
int FWC_sis8300_eicsys_iqfb_func_getDAQData(void *module)
{
    FWC_sis8300_eicsys_iqfb_struc_data *arg = (FWC_sis8300_eicsys_iqfb_struc_data *)module;

    unsigned int coefId;

    if(!arg) return -1;

    if(arg -> board_handle) {
        /* get the DRAM data */
        if(arg -> board_DAQShareSel == 0)
            FWC_sis8300_eicsys_iqfb_func_getAllDAQData(arg -> board_handle, (unsigned int)arg -> board_ADCSamplePno, (unsigned int)arg -> board_ADCSamplePno_old,
                                                       arg -> board_ADC0_raw,     arg -> board_ADC1_raw,
                                                       arg -> board_ADC2_raw,     arg -> board_ADC3_raw,
                                                       arg -> board_ADC4_raw,     arg -> board_ADC5_raw,
                                                       arg -> board_ADC6_raw,     arg -> board_ADC7_raw,
                                                       arg -> board_ADC8_raw,     arg -> board_ADC9_raw,
                                                       arg -> rfData_refCh.wfI,   arg -> rfData_refCh.wfQ,
                                                       arg -> rfData_fbkCh.wfI,   arg -> rfData_fbkCh.wfQ,
                                                       arg -> rfData_tracked.wfI, arg -> rfData_tracked.wfQ); 

        else
            FWC_sis8300_eicsys_iqfb_func_getAllDAQData(arg -> board_handle, (unsigned int)arg -> board_ADCSamplePno,  (unsigned int)arg -> board_ADCSamplePno_old,
                                                       arg -> board_ADC0_raw,     arg -> board_ADC1_raw,
                                                       arg -> board_ADC2_raw,     arg -> board_ADC3_raw,
                                                       arg -> board_ADC4_raw,     arg -> board_ADC5_raw,
                                                       arg -> board_ADC6_raw,     arg -> board_ADC7_raw,
                                                       arg -> board_ADC8_raw,     arg -> board_ADC9_raw,
                                                       arg -> rfData_err.wfI,     arg -> rfData_err.wfQ,
                                                       arg -> rfData_act.wfI,     arg -> rfData_act.wfQ,
                                                       arg -> rfData_DACOut.wfI,  arg -> rfData_DACOut.wfQ);

        /* remember the point number */
        arg -> board_ADCSamplePno_old = arg -> board_ADCSamplePno;

        /* get the current coefficient id for demod in CPU */
        FWC_sis8300_eicsys_iqfb_func_getNonIQCoefCur(arg -> board_handle, &coefId);
        arg -> board_coefIdCur = (long)coefId;
    }

/*
    int i;
    int var_cnt;

    var_cnt = 0;
    
    printf("-----------------------------------------------\n");
    for(i = 0; i < 128; i ++) {
        printf("%d  ", *(arg -> board_ADC0_raw + i));
        var_cnt ++;
        if(var_cnt >= 8) {
            var_cnt = 0;
            printf("\n");
        }
    }
*/
    return 0;
}

/**
 * Get ADC data (assume the ADC data is at channel 0-9 of the DAQ)
 */
int FWC_sis8300_eicsys_iqfb_func_getADCData(void *module, unsigned long channel, short *data, double *sampleFreq_MHz, double *sampleDelay_ns, long *pno, long *coefIdCur)
{
    FWC_sis8300_eicsys_iqfb_struc_data *arg = (FWC_sis8300_eicsys_iqfb_struc_data *)module;

    if(!arg || !data || channel > 9 || !sampleFreq_MHz || !sampleDelay_ns || !pno || !coefIdCur) return -1;

    /* get data */
    if(arg -> board_ADC_data[channel]) 
        memcpy((void *)data, (void *)arg -> board_ADC_data[channel], sizeof(short) * 1024);   /* temp value, this is the data used for Low level application */

    *sampleFreq_MHz = arg -> board_sampleFreq_MHz;
    *sampleDelay_ns = arg -> board_DAQTriggerDelay_ns;
    *pno            = 1024;
    *coefIdCur      = arg -> board_coefIdCur;

    return 0;
}

/**
 * Get the internal waveforms
 */
int FWC_sis8300_eicsys_iqfb_func_getIntData(void *module)
{
   /* the internal data has been get from the function of FWC_sis8300_eicsys_iqfb_func_getDAQData. EICSYS version does not need this function */

    return 0;
}

/**
 * Set the phase adjustment
 */
int FWC_sis8300_eicsys_iqfb_func_setPha_deg(void *module, double pha_deg)
{
    FWC_sis8300_eicsys_iqfb_struc_data *arg = (FWC_sis8300_eicsys_iqfb_struc_data *)module;

    /* check the input */
    if(!arg) return -1;

    /* Apply the adjustement to: 1). measurement chain rotation; 2). driving chain rotation */
    arg -> board_fbkRotationAngle_deg -= pha_deg;
    arg -> board_actRotationAngle_deg += pha_deg;
             
    /*arg -> board_fbkRotationGain = 1.0; */   /* these rotations are only used for fast phase rotation! */
    arg -> board_actRotationGain = 1.0;

    if(arg -> board_handle) {
        FWC_sis8300_eicsys_iqfb_func_setFbkVectorRotation(arg -> board_handle, arg -> board_fbkRotationGain, arg -> board_fbkRotationAngle_deg);
        FWC_sis8300_eicsys_iqfb_func_setActVectorRotation(arg -> board_handle, arg -> board_actRotationGain, arg -> board_actRotationAngle_deg);
    }

    return 0;
}

/**
 * Set amplitude (not supported now)
 */
int FWC_sis8300_eicsys_iqfb_func_setAmp(void *module, double amp)
{
    return 0;
}

/**
 * Wait for the interrupt
 */
int FWC_sis8300_eicsys_iqfb_func_waitIntr(void *module)
{
    unsigned int data;
    FWC_sis8300_eicsys_iqfb_struc_data *arg = (FWC_sis8300_eicsys_iqfb_struc_data *)module;

    /* check the input */
    if(!arg) return -1;   

    /* wait for interrupt */
    /*if(arg -> board_handle) 
        return FWC_sis8300_eicsys_iqfb_func_pullInterrupt(arg -> board_handle);        */

    /* enable the DAQ trigger by swapping the value of bit 9 of the switch control register */
    if(arg -> board_handle) {
        /* put the DAQ trigger enable bit to opsite and not touch other bits */
        /*FWC_sis8300_eicsys_iqfb_func_getBits(arg->board_handle, &data);        

		printf("Original data is 0x%4X\n", data);

        data ^= 0x200;
        FWC_sis8300_eicsys_iqfb_func_setBits(arg->board_handle, data); 

		FWC_sis8300_eicsys_iqfb_func_getBits(arg->board_handle, &data); 
		printf("New data is 0x%4X\n", data);
		*/
               

       
        /* wait for interrupt */
        return FWC_sis8300_eicsys_iqfb_func_pullInterrupt(arg -> board_handle);

    } else {
        return -1;
    }
}

/**
 * Measure the latency of the intrrupt, this is a temp implementation so we directly use the RFCB_API functions
 * Bit 6 of the switch control register is for enable/disable the IRQ delay measurement counter. 
 * The counter will be started by a trigger in FPGA if it is enabled and will be stopped when 0 is written to bit 6
 * of the switch control register
 */
int FWC_sis8300_eicsys_iqfb_func_meaIntrLatency(void *module, long *latencyCnt, long *pulseCnt)
{
    unsigned int data       = 0;
    unsigned int dataRead   = 0;
    unsigned int dataRead2  = 0;

    FWC_sis8300_eicsys_iqfb_struc_data *arg = (FWC_sis8300_eicsys_iqfb_struc_data *)module;

    /* check the input */
    if(!arg || !latencyCnt || !pulseCnt) return -1;
    
    if(arg -> board_handle) {
        /* stop the counter */
        FWC_sis8300_eicsys_iqfb_func_getBits(arg->board_handle, &data);        
        data &= 0xFFFFFFBF;
        FWC_sis8300_eicsys_iqfb_func_setBits(arg->board_handle, data);

        /* read the register */            
        RFCB_API_readRegister((RFCB_struc_moduleData *)arg->board_handle, CON_SIS8300_EICSYS_IQFB_REG_ADDR_IRQ_DELAY_CNT, &dataRead, RFCB_DEV_USR);
        RFCB_API_readRegister((RFCB_struc_moduleData *)arg->board_handle, CON_SIS8300_EICSYS_IQFB_REG_ADDR_PUL_CNT,       &dataRead2, RFCB_DEV_USR);

        *(latencyCnt) = (long)dataRead;
        *(pulseCnt)   = (long)dataRead2;

        /* enable the counter which will be started by the coming trigger */                    
        data |= 0x00000040;
        FWC_sis8300_eicsys_iqfb_func_setBits(arg->board_handle, data);  
    }

    return 0;
}












