/****************************************************
 * FWControl_sis8300_eicsys_iqfb_upLink.h
 * 
 * EPICS records definition for the firmware control module
 *
 * Created by: Zheqiao Geng, gengzq@slac.stanford.edu
 * Created on: 2011.07.07
 * Description: Initial creation
 *
 * Modified by: Zheqiao Geng
 * Modified on: 3/6/2013
 * Description: Modify the implementation to fit the EICSYS firmware
 ****************************************************/
#ifndef FW_CONTROL_SIS8300_eicsys_IQFB_UPLINK_H
#define FW_CONTROL_SIS8300_eicsys_IQFB_UPLINK_H

#include "FWControl_sis8300_eicsys_iqfb.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Routines to associate the module data with the EPICS record (virtual function implementation)
 */
int FWC_sis8300_eicsys_iqfb_func_createEpicsData(void *module, const char *moduleName);
int FWC_sis8300_eicsys_iqfb_func_deleteEpicsData(void *module, const char *moduleName);

#ifdef __cplusplus
}
#endif

#endif

