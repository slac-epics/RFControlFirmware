/****************************************************
 * RFControlFirmware_availableInterface_api.c
 * 
 * Source file for the available interface for RFControlFirmware module (API), which can be used by other modules / iocShells
 *
 * Created by: Zheqiao Geng, gengzq@slac.stanford.edu
 * Created on: 2/12/2013
 * Description: Initial creation
 ****************************************************/
#include <stdlib.h>             
#include <string.h>
#include <errlog.h>

#include "RFControlFirmware_availableInterface_api.h"

/*======================================
 * Global data for module management
 *======================================*/
/* A global list of the module instances */
static EPICSLIB_type_linkedList RFCFW_gvar_moduleInstanceList;
static int RFCFW_gvar_moduleInstanceListInitalized = 0;

/* A mutex is required for this list (to be done later) */

/*======================================
 * Common API Routines for module management
 *======================================*/
/**
 * Create an instance of the module
 * Input: 
 *     moduleName : An unique name of the module instance
 *     firmwareType : one of the pre-defined firmware type supported by the software
 * Return:
 *     0          : Successful
 *    -1          : Failed
 */
int RFCFW_API_createModule(const char *moduleName, const char *firmwareType)
{
    RFCFW_struc_moduleData              *ptr_dataInstance    = NULL;
    FWC_sis8300_struck_iqfb_struc_data  *ptr_fwDataInstance  = NULL;                         /* firmware specific data: sis8300 board, struck platform fw, i/q feedback app fw */
    FWC_sis8300_eicsys_iqfb_struc_data  *ptr_fwDataInstance2 = NULL;                         /* firmware specific data: sis8300 board, eicsys platform fw, i/q feedback app fw */

    /* Check the input parameters */
    if(!moduleName || !moduleName[0]) {
        EPICSLIB_func_errlogPrintf("RFCFW_API_createModule: Illegal module name\n");
        return -1;
    }

    /* Check if the list initialized */
    if(!RFCFW_gvar_moduleInstanceListInitalized) {
        EPICSLIB_func_LinkedListInit(RFCFW_gvar_moduleInstanceList);
        RFCFW_gvar_moduleInstanceListInitalized = 1;
    }

    /* Create a new instance of the data structure */
    ptr_dataInstance = (RFCFW_struc_moduleData *)calloc(1, sizeof(RFCFW_struc_moduleData));

    if(ptr_dataInstance == NULL) {
        EPICSLIB_func_errlogPrintf("RFCFW_API_createModule: Failed to create the data structure for the module of %s\n", moduleName);
        return -1;
    }

    /* Call the routine for the construction of the module */
    if(RFCFW_func_createModule(ptr_dataInstance, moduleName) != 0) {
        EPICSLIB_func_errlogPrintf("RFCFW_API_createModule: Failed to construct the module of %s\n", moduleName);
        free(ptr_dataInstance);                            /* clean the garbage */
        return -1;
    }

    /* --- initalize the firmware specific things --- */
    if(strcmp("SIS8300:STRUCK:IQFB", firmwareType) == 0) {
            
        /* 1. connect the virtual functions */
        ptr_dataInstance -> fwFunc.FWC_func_init            = FWC_sis8300_struck_iqfb_func_init;

        ptr_dataInstance -> fwFunc.FWC_func_createEpicsData = FWC_sis8300_struck_iqfb_func_createEpicsData;
        ptr_dataInstance -> fwFunc.FWC_func_deleteEpicsData = FWC_sis8300_struck_iqfb_func_deleteEpicsData;

        ptr_dataInstance -> fwFunc.FWC_func_getBoardHandle  = FWC_sis8300_struck_iqfb_func_getBoard;

        ptr_dataInstance -> fwFunc.FWC_func_getDAQData      = FWC_sis8300_struck_iqfb_func_getDAQData;
        ptr_dataInstance -> fwFunc.FWC_func_getADCData      = FWC_sis8300_struck_iqfb_func_getADCData;
        ptr_dataInstance -> fwFunc.FWC_func_getIntData      = FWC_sis8300_struck_iqfb_func_getIntData;

        ptr_dataInstance -> fwFunc.FWC_func_setPha_deg      = FWC_sis8300_struck_iqfb_func_setPha_deg;
        ptr_dataInstance -> fwFunc.FWC_func_setAmp          = FWC_sis8300_struck_iqfb_func_setAmp;
            
        ptr_dataInstance -> fwFunc.FWC_func_waitIntr        = FWC_sis8300_struck_iqfb_func_waitIntr;
        ptr_dataInstance -> fwFunc.FWC_func_meaIntrLatency  = FWC_sis8300_struck_iqfb_func_meaIntrLatency;

        /* 2. create data instance for the firmware */
        ptr_fwDataInstance = (FWC_sis8300_struck_iqfb_struc_data *)calloc(1, sizeof(FWC_sis8300_struck_iqfb_struc_data));

        if(ptr_fwDataInstance == NULL) {
            EPICSLIB_func_errlogPrintf("RFCFW_API_createModule: Failed to create the data structure for the firmware SIS8300:STRUCK:IQFB for %s\n", moduleName);
            return -1;
        } else {
            ptr_dataInstance -> fwModule = (void *)ptr_fwDataInstance;
        }
   
    } else if(strcmp("SIS8300:EICSYS:IQFB", firmwareType) == 0) {
            
        /* 1. connect the virtual functions */
        ptr_dataInstance -> fwFunc.FWC_func_init            = FWC_sis8300_eicsys_iqfb_func_init;

        ptr_dataInstance -> fwFunc.FWC_func_createEpicsData = FWC_sis8300_eicsys_iqfb_func_createEpicsData;
        ptr_dataInstance -> fwFunc.FWC_func_deleteEpicsData = FWC_sis8300_eicsys_iqfb_func_deleteEpicsData;

        ptr_dataInstance -> fwFunc.FWC_func_getBoardHandle  = FWC_sis8300_eicsys_iqfb_func_getBoard;

        ptr_dataInstance -> fwFunc.FWC_func_getDAQData      = FWC_sis8300_eicsys_iqfb_func_getDAQData;
        ptr_dataInstance -> fwFunc.FWC_func_getADCData      = FWC_sis8300_eicsys_iqfb_func_getADCData;
        ptr_dataInstance -> fwFunc.FWC_func_getIntData      = FWC_sis8300_eicsys_iqfb_func_getIntData;

        ptr_dataInstance -> fwFunc.FWC_func_setPha_deg      = FWC_sis8300_eicsys_iqfb_func_setPha_deg;
        ptr_dataInstance -> fwFunc.FWC_func_setAmp          = FWC_sis8300_eicsys_iqfb_func_setAmp;
            
        ptr_dataInstance -> fwFunc.FWC_func_waitIntr        = FWC_sis8300_eicsys_iqfb_func_waitIntr;
        ptr_dataInstance -> fwFunc.FWC_func_meaIntrLatency  = FWC_sis8300_eicsys_iqfb_func_meaIntrLatency;

        /* 2. create data instance for the firmware */
        ptr_fwDataInstance2 = (FWC_sis8300_eicsys_iqfb_struc_data *)calloc(1, sizeof(FWC_sis8300_eicsys_iqfb_struc_data));

        if(ptr_fwDataInstance2 == NULL) {
            EPICSLIB_func_errlogPrintf("RFCFW_API_createModule: Failed to create the data structure for the firmware SIS8300:EICSYS:IQFB for %s\n", moduleName);
            return -1;
        } else {
            ptr_dataInstance -> fwModule = (void *)ptr_fwDataInstance2;
        }
   
    }

    /* init the system */
    if(RFCFW_func_initModule(ptr_dataInstance) != 0) {
        EPICSLIB_func_errlogPrintf("RFCFW_API_createModule: Failed to init the module of %s\n", moduleName);
        return -1;
    }

    /* create EPICS records */
    if(RFCFW_func_createEpicsData(ptr_dataInstance) != 0) {                                                                          
        EPICSLIB_func_errlogPrintf("RFCFW_API_createModule: There are errors to create records for the module of %s\n", moduleName);
        return -1;
    }

    /* Add the successful module instance into the list */
    EPICSLIB_func_LinkedListInsert(RFCFW_gvar_moduleInstanceList, ptr_dataInstance -> node);

    return 0;
}

/**
 * Delete the module instance
 * Input: 
 *     moduleName : Name of the module instance to be deleted
 * Return:
 *     0          : Successful
 *    -1          : Failed
 */
int RFCFW_API_deleteModule(const char *moduleName) 
{
    RFCFW_struc_moduleData *ptr_dataInstance = NULL;

    /* Check the input parameters */
    if(!moduleName || !moduleName[0]) {
        EPICSLIB_func_errlogPrintf("RFCFW_API_deleteModule: Illegal module name\n");
        return -1;
    }

    /* Find the module from the list */
    ptr_dataInstance = RFCFW_API_getModule(moduleName);

    if(ptr_dataInstance == NULL) {
        EPICSLIB_func_errlogPrintf("RFCFW_API_deleteModule: Failed to find the module of %s\n", moduleName);
        return -1;
    }

    /* Here we need to disable or delete the internal data associated to the module that to be deleted. If we do not do this,
     * the EPICS PVs will try to talk to an non-exists address which will cause the program crashes. This feature is useful when
     * the EPICS base supports dynamic record loading/deleting, but not supported now! Here I put the function as a place holder.
     */
    if(RFCFW_func_deleteEpicsData(ptr_dataInstance) != 0) {
        EPICSLIB_func_errlogPrintf("RFCFW_API_deleteModule: Failed to delete the internal data connected to the module of %s\n", moduleName);
        return -1;
    }

    /* Call the distruction routine of the module */
    if(RFCFW_func_destroyModule(ptr_dataInstance) != 0) {
        EPICSLIB_func_errlogPrintf("RFCFW_API_deleteModule: Failed to delete the module of %s\n", moduleName);
        return -1;
    }

    /* Delete it */
    EPICSLIB_func_LinkedListDelete(RFCFW_gvar_moduleInstanceList, ptr_dataInstance -> node);
    free(ptr_dataInstance);

    return 0;
}

/**
 * Set up the parameters of the module instance, the command will include:
 *   - RFCB_NAME  : Set the RFControlBoard module name that this module instance will be connected to
 * Input: 
 *     moduleName : Name of the module instance
 *     cmd        : Command listed above
 *     dataStr    : Data for the specified command
 * Return:
 *     0          : Successful
 *    -1          : Failed
 */
int RFCFW_API_setupModule(const char *moduleName, const char *cmd, const char *dataStr)
{
    RFCFW_struc_moduleData                *ptr_dataInstance    = NULL;

    /* Check the input parameters */
    if(!moduleName || !moduleName[0]) {
        EPICSLIB_func_errlogPrintf("RFCFW_API_setupModule: Illegal module name\n");
        return -1;
    }

    /* Find the module instance */
    ptr_dataInstance = RFCFW_API_getModule(moduleName);

    if(ptr_dataInstance == NULL) {
        EPICSLIB_func_errlogPrintf("RFCFW_API_setupModule: Failed to find the module of %s\n", moduleName);
        return -1;
    }

    /* Response to each command */
    if(strcmp("RFCB_NAME", cmd) == 0) {

        /* --- set RFControlBoardName --- */
        if(RFCFW_func_associateBoardModule(ptr_dataInstance, dataStr) != 0) {
            EPICSLIB_func_errlogPrintf("RFCFW_API_setupModule: Failed to set board name\n");
            return -1;
        }

    } else {
        
        /* --- invalid command --- */
        EPICSLIB_func_errlogPrintf("RFCFW_API_setupModule: Invalid command\n");
        return -1;
        
    }

    return 0;
}

/**
 * Find the module from the list
 * Input: 
 *     moduleName  : Name of the module instance
 * Return:
 *     NULL        : If the module instance is not found
 *     module addr : Successful
 */
RFCFW_struc_moduleData *RFCFW_API_getModule(const char *moduleName)
{
    int var_moduleFound = 0;
    RFCFW_struc_moduleData *ptr_moduleData  = NULL;

    /* Check the input parameters */
    if(!moduleName || !moduleName[0]) {
        EPICSLIB_func_errlogPrintf("RFCFW_API_getModule: Illegal module name\n");
        return NULL;
    }    

    /* Look up the list */
    for(ptr_moduleData = (RFCFW_struc_moduleData *)EPICSLIB_func_LinkedListFindFirst(RFCFW_gvar_moduleInstanceList);
        ptr_moduleData;
        ptr_moduleData = (RFCFW_struc_moduleData *)EPICSLIB_func_LinkedListFindNext(ptr_moduleData -> node)) {
        if(strcmp(ptr_moduleData -> moduleName, moduleName) == 0) {
            var_moduleFound = 1;
            break;
        }
    }

    if(var_moduleFound) return ptr_moduleData;
    else return NULL;
}



