/****************************************************
 * RFControlFirmware_main.c
 * 
 * Implementation of the RFControlFirmware module
 *
 * Created by: Zheqiao Geng, gengzq@slac.stanforde.edu
 * Created on: 2/12/2013
 * Description: Initial creation
 ****************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "RFControlFirmware_main.h"

/**
 * Create the module. The data structure has been created in other places and here only initialize it
 */
int RFCFW_func_createModule(RFCFW_struc_moduleData *arg, const char *moduleName)
{
    /* Check the input */
    if(!arg || !moduleName || !moduleName[0]) return -1;

    /* Init the data structure */
    strcpy(arg -> moduleName, moduleName);

    return 0;
}

/**
 * Destroy the module. Destroy the newly created objects
 */
int RFCFW_func_destroyModule(RFCFW_struc_moduleData *arg)
{
    /* Check the input */
    if(!arg) return -1;

    /* Delete the data structure for firmware */
    if(arg -> fwModule) free(arg -> fwModule);

    return 0;
}

/**
 * Associate an RF Control Board module with the firmware. Call the virtual function.
 */
int RFCFW_func_associateBoardModule(RFCFW_struc_moduleData *arg, const char *boardModuleName)
{
    /* Check the input */
    if(!arg || !boardModuleName ||!boardModuleName[0]) return -1;
    
    /* Save the module name and get its address */
    strcpy(arg -> boardModuleName, boardModuleName);   
    
    if(arg -> fwFunc.FWC_func_getBoardHandle) {
        return arg -> fwFunc.FWC_func_getBoardHandle(arg -> fwModule, boardModuleName);
    }

    return -1;
}

/**
 * Init the module. Call the virtual function.
 */
int RFCFW_func_initModule(RFCFW_struc_moduleData *arg)
{
    if(arg && arg -> fwFunc.FWC_func_init) {
        return arg -> fwFunc.FWC_func_init(arg -> fwModule);
    }

    return -1;
}

/**
 * Create EPICS data. Call virtual function.
 */
int RFCFW_func_createEpicsData(RFCFW_struc_moduleData *arg)
{
    if(arg && arg -> fwFunc.FWC_func_createEpicsData) {
        return arg -> fwFunc.FWC_func_createEpicsData(arg -> fwModule, arg -> moduleName);
    }

    return -1;
}

/**
 * Delete EPICS data. Call virtual function.
 */
int RFCFW_func_deleteEpicsData(RFCFW_struc_moduleData *arg)
{
    if(arg && arg -> fwFunc.FWC_func_deleteEpicsData) {
        return arg -> fwFunc.FWC_func_deleteEpicsData(arg -> fwModule, arg -> moduleName);
    }

    return -1;
}

/**
 * Get the DAQ data. Call the virtual function.
 */
int RFCFW_func_getDAQData(RFCFW_struc_moduleData *arg)
{
    if(arg && arg -> fwFunc.FWC_func_getDAQData) {
        return arg -> fwFunc.FWC_func_getDAQData(arg -> fwModule);
    }

    return -1;
}

/**
 * Get ADC data. Call the virtual function.
 */
int RFCFW_func_getADCData(RFCFW_struc_moduleData *arg, unsigned long channel, short *data, double *sampleFreq_MHz, double *sampleDelay_ns, long *pno, long *coefIdCur)
{
    if(arg && arg -> fwFunc.FWC_func_getADCData) {
        return arg -> fwFunc.FWC_func_getADCData(arg -> fwModule, channel, data, sampleFreq_MHz, sampleDelay_ns, pno, coefIdCur);
    }

    return -1;
}

/**
 * Get the internal DAQ data. Call the virtual function.
 */
int RFCFW_func_getIntData(RFCFW_struc_moduleData *arg)
{
    if(arg && arg -> fwFunc.FWC_func_getIntData) {
       return arg -> fwFunc.FWC_func_getIntData(arg -> fwModule);
    }

    return -1;
}

/**
 * Set the phase set point value. Call the virtual function
 */
int RFCFW_func_setPha_deg(RFCFW_struc_moduleData *arg, double pha_deg)
{
    if(arg && arg -> fwFunc.FWC_func_setPha_deg) {
       return arg -> fwFunc.FWC_func_setPha_deg(arg -> fwModule, pha_deg);
    }

    return -1;
}

/**
 * Set the amplitude set point value. Call the virtual function.
 */
int RFCFW_func_setAmp(RFCFW_struc_moduleData *arg, double amp)
{
    if(arg && arg -> fwFunc.FWC_func_setAmp) {
       return arg -> fwFunc.FWC_func_setAmp(arg -> fwModule, amp);
    }

    return -1;
}

/**
 * Wait for the interrupt (suspend the thread of caller). Call the virtual function.
 */
int RFCFW_func_waitIntr(RFCFW_struc_moduleData *arg)
{
    if(arg && arg -> fwFunc.FWC_func_waitIntr) {
       return arg -> fwFunc.FWC_func_waitIntr(arg -> fwModule);
    }

    return -1;
}

/**
 * Get the interrupt latency. Call the virtual function.
 */
int RFCFW_func_meaIntrLatency(RFCFW_struc_moduleData *arg, long *latencyCnt, long *pulseCnt)
{
    if(arg && arg -> fwFunc.FWC_func_meaIntrLatency) {
       return arg -> fwFunc.FWC_func_meaIntrLatency(arg -> fwModule, latencyCnt, pulseCnt);
    }

    return -1;
}











