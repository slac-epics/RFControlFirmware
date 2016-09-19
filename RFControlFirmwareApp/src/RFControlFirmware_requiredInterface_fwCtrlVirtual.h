/****************************************************
 * RFControlFirmware_requiredInterface_fwCtrlVirtual.h
 * 
 * Virtual function definition for the firmware control. The motivation to make this is because we will have different 
 *   version of firmware/board to be supported by this module. The virtual functions will allow us to reuse the low level
 *   application layer (pulse-pulse phase control) and adapt to different firmware. This is a common interface definition.
 *   And because we are using C instead of C++, function pointers will be used to replace the virtual functions in C++.
 *
 * Created by: Zheqiao Geng, gengzq@slac.stanford.edu
 * Created on: 2011.07.07
 * Description: Initial creation
 *
 * Modified by: Zheqiao Geng
 * Modified on: 2/12/2013
 * Description: Move the file to the RFControlFirmware module
 * 
 * Modified by: Zheqiao Geng
 * Modified on: 3/9/2013
 * Description: Add the part for EICSYS driver support
 ****************************************************/
#ifndef RF_CONTROL_FIRMWARE_REQUIRED_INTERFACE_FW_CTRL_VIRTUAL_H
#define RF_CONTROL_FIRMWARE_REQUIRED_INTERFACE_FW_CTRL_VIRTUAL_H

#include "FWControl_sis8300_struck_iqfb.h"                                                  /* support codes for the sis8300 board, struck platform firmware, iq feedback application firmware (SIS8300:STRUCK:IQFB) */
#include "FWControl_sis8300_struck_iqfb_upLink.h"
#include "FWControl_sis8300_eicsys_iqfb.h"                                                  /* support codes for the sis8300 board, eicsys platform firmware, iq feedback application firmware (SIS8300:EICSYS:IQFB) */
#include "FWControl_sis8300_eicsys_iqfb_upLink.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Function pointer definitions 
 */
typedef int (*RFCFW_FUNCPTR_INIT)(void*);                                                    /* init the firmware control module */

typedef int (*RFCFW_FUNCPTR_CREATE_EPICS_DATA)(void*, const char*);                          /* create the internal data nodes for the firmware control */
typedef int (*RFCFW_FUNCPTR_DELETE_EPICS_DATA)(void*, const char*);                          /* delete */

typedef int (*RFCFW_FUNCPTR_GET_BOARD_HANDLE)(void *, const char*);                          /* get the board handle */

typedef int (*RFCFW_FUNCPTR_GET_DAQ_DATA)(void*);                                                         /* get all DAQ data (saved in the firmware control module, because different firmware needs different buffer size) */
typedef int (*RFCFW_FUNCPTR_GET_ADC_DATA)(void*, unsigned long, short*, double*, double*, long*, long*);  /* get the ADC channel raw data (channel number, buffer, sample frequency (MHz), sample delay(ns), point number) */
typedef int (*RFCFW_FUNCPTR_GET_INT_DATA)(void*);                                                         /* get the internal data of the firmware module, we make this because it might not be at the same rate with get DAQ data */

typedef int (*RFCFW_FUNCPTR_SET_PHA_DEG)(void*, double);                                     /* set the phase in degree */
typedef int (*RFCFW_FUNCPTR_SET_AMP)(void*, double);                                         /* set the amplitude */

typedef int (*RFCFW_FUNCPTR_WAIT_INTR)(void*);                                               /* wait interrupt */

typedef int (*RFCFW_FUNCPTR_MEA_INTR_LATENCY)(void*, long*, long*);                          /* measure the interrupt latency */

/**
 * Structure of the virtual functions
 */
typedef struct {

    RFCFW_FUNCPTR_INIT                FWC_func_init;

    RFCFW_FUNCPTR_CREATE_EPICS_DATA   FWC_func_createEpicsData;
    RFCFW_FUNCPTR_DELETE_EPICS_DATA   FWC_func_deleteEpicsData;

    RFCFW_FUNCPTR_GET_BOARD_HANDLE    FWC_func_getBoardHandle;

    RFCFW_FUNCPTR_GET_DAQ_DATA        FWC_func_getDAQData;
    RFCFW_FUNCPTR_GET_ADC_DATA        FWC_func_getADCData;
    RFCFW_FUNCPTR_GET_INT_DATA        FWC_func_getIntData;

    RFCFW_FUNCPTR_SET_PHA_DEG         FWC_func_setPha_deg;
    RFCFW_FUNCPTR_SET_AMP             FWC_func_setAmp;

    RFCFW_FUNCPTR_WAIT_INTR           FWC_func_waitIntr;
    RFCFW_FUNCPTR_MEA_INTR_LATENCY    FWC_func_meaIntrLatency;

} RFCFW_struc_fwAccessFunc;

#ifdef __cplusplus
}
#endif

#endif


