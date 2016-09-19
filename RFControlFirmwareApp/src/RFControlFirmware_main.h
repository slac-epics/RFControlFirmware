/****************************************************
 * RFControlFirmware_main.h
 * 
 * Header file for the RFControlFirmware module
 * This module is mainly designed to perform the firmware specific control.
 *
 * Created by: Zheqiao Geng, gengzq@slac.stanforde.edu
 * Created on: 2/12/2013
 * Description: Initial creation
 ****************************************************/
#ifndef RF_CONTROL_FIRMWARE_MAIN_H
#define RF_CONTROL_FIRMWARE_MAIN_H

#include "RFLib_signalProcess.h"                            /* use the library data definitions and routines */
#include "MathLib_dataProcess.h"
#include "EPICSLib_wrapper.h"

#include "RFControlFirmware_requiredInterface_fwCtrlVirtual.h"

#ifdef __cplusplus
extern "C" {
#endif

/*======================================
 * Data structure for the RF Control Firmware module
 *======================================*/
typedef struct {

    EPICSLIB_type_linkedListNode node;                      /* to fit this structure to linked list */

    char moduleName[EPICSLIB_CONST_NAME_LEN];               /* name of the module instance */
    char boardModuleName[EPICSLIB_CONST_NAME_LEN];          /* name of the module of the RFControlBoard */

    void *fwModule;                                         /* data structure of the firmware control, there maybe multitypes of the fw module, so use void pointer */    
    RFCFW_struc_fwAccessFunc fwFunc;                        /* virtual functions for firmware access */                    

} RFCFW_struc_moduleData;

/*======================================
 * Routines for the RF Control Firmware module
 *======================================*/  
/*--- functions to do module management (called locally) ---*/   
int RFCFW_func_createModule(RFCFW_struc_moduleData *arg, const char *moduleName);              /* create an instance of this module,INIT ALL PARAMETERS! */      
int RFCFW_func_destroyModule(RFCFW_struc_moduleData *arg);                                     /* destroy the instance */
int RFCFW_func_associateBoardModule(RFCFW_struc_moduleData *arg, const char *boardModuleName); /* associate this module with a RFControlBoard module */

int RFCFW_func_initModule(RFCFW_struc_moduleData *arg);
int RFCFW_func_createEpicsData(RFCFW_struc_moduleData *arg);
int RFCFW_func_deleteEpicsData(RFCFW_struc_moduleData *arg);

/*--- functions to serve the external client (called by higher level module) ---*/ 
int RFCFW_func_getDAQData(RFCFW_struc_moduleData *arg);
int RFCFW_func_getADCData(RFCFW_struc_moduleData *arg, unsigned long channel, short *data, double *sampleFreq_MHz, double *sampleDelay_ns, long *pno, long *coefIdCur);
int RFCFW_func_getIntData(RFCFW_struc_moduleData *arg);

int RFCFW_func_setPha_deg(RFCFW_struc_moduleData *arg, double pha_deg);
int RFCFW_func_setAmp(RFCFW_struc_moduleData *arg, double amp);

int RFCFW_func_waitIntr(RFCFW_struc_moduleData *arg);
int RFCFW_func_meaIntrLatency(RFCFW_struc_moduleData *arg, long *latencyCnt, long *pulseCnt);

#ifdef __cplusplus
}
#endif

#endif


