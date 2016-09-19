/****************************************************
 * RFControlFirmware_availableInterface_api.h
 * 
 * Header file for the available interface for RFControlFirmware module (API), which can be used by other modules / iocShells
 *
 * Created by: Zheqiao Geng, gengzq@slac.stanford.edu
 * Created on: 2/12/2013
 * Description: Initial creation
 ****************************************************/
#ifndef RF_CONTROL_FIRMWARE_AVAILABLE_INTERFACE_API_H
#define RF_CONTROL_FIRMWARE_AVAILABLE_INTERFACE_API_H

#include "RFControlFirmware_main.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * APIs that will be used by other moduels/iocShells
 */
/* Management of the modules (NOT REAL-TIME) */
int RFCFW_API_createModule(const char *moduleName, const char *firmwareType);            
int RFCFW_API_deleteModule(const char *moduleName);
int RFCFW_API_setupModule(const char *moduleName, const char *cmd, const char *dataStr);

RFCFW_struc_moduleData *RFCFW_API_getModule(const char *moduleName);

/* wrappers for the virtual functions */
#define RFCFW_API_getDAQData      RFCFW_func_getDAQData
#define RFCFW_API_getADCData      RFCFW_func_getADCData
#define RFCFW_API_getIntData      RFCFW_func_getIntData

#define RFCFW_API_setPha_deg      RFCFW_func_setPha_deg
#define RFCFW_API_setAmp          RFCFW_func_setAmp

#define RFCFW_API_waitIntr        RFCFW_func_waitIntr
#define RFCFW_API_meaIntrLatency  RFCFW_func_meaIntrLatency

#ifdef __cplusplus
}
#endif

#endif

