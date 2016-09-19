/****************************************************
 * RFControlFirmware_iocShell.c
 * 
 * Define ioc shell commands
 *
 * Created by: Zheqiao Geng, gengzq@slac.stanford.edu
 * Created on: 2/13/2013
 * Description: Initial creation
 ****************************************************/
#include <epicsTypes.h>
#include <epicsExport.h>
#include <iocsh.h>

#include "RFControlFirmware_availableInterface_api.h"

#ifdef __cplusplus
extern "C" {
#endif

/*======================================
 * IOC shell Routines
 *======================================*/
/* RFCFW_API_createModule(const char *moduleName) */
static const iocshArg        RFCFW_createModule_Arg0    = {"moduleName",   iocshArgString};
static const iocshArg        RFCFW_createModule_Arg1    = {"firmwareType", iocshArgString};
static const iocshArg *const RFCFW_createModule_Args[2] = {&RFCFW_createModule_Arg0, &RFCFW_createModule_Arg1};
static const iocshFuncDef    RFCFW_createModule_FuncDef = {"RFCFW_createModule", 2, RFCFW_createModule_Args};
static void  RFCFW_createModule_CallFunc(const iocshArgBuf *args) {RFCFW_API_createModule(args[0].sval, args[1].sval);}

/* RFCFW_API_deleteModule(const char *moduleName) */
static const iocshArg        RFCFW_deleteModule_Arg0    = {"moduleName", iocshArgString};
static const iocshArg *const RFCFW_deleteModule_Args[1] = {&RFCFW_deleteModule_Arg0};
static const iocshFuncDef    RFCFW_deleteModule_FuncDef = {"RFCFW_deleteModule", 1, RFCFW_deleteModule_Args};
static void  RFCFW_deleteModule_CallFunc(const iocshArgBuf *args) {RFCFW_API_deleteModule(args[0].sval);}

/* RFCFW_API_setupModule(const char *moduleName, const char *cmd, const char *dataStr) */
static const iocshArg        RFCFW_setupModule_Arg0    = {"moduleName", iocshArgString};
static const iocshArg        RFCFW_setupModule_Arg1    = {"cmd",        iocshArgString};
static const iocshArg        RFCFW_setupModule_Arg2    = {"dataStr",    iocshArgString};
static const iocshArg *const RFCFW_setupModule_Args[3] = {&RFCFW_setupModule_Arg0, &RFCFW_setupModule_Arg1, &RFCFW_setupModule_Arg2};
static const iocshFuncDef    RFCFW_setupModule_FuncDef = {"RFCFW_setupModule", 3, RFCFW_setupModule_Args};
static void  RFCFW_setupModule_CallFunc(const iocshArgBuf *args) {RFCFW_API_setupModule(args[0].sval, args[1].sval, args[2].sval);}

void RFCFW_IOCShellRegister(void)
{
    iocshRegister(&RFCFW_createModule_FuncDef,  RFCFW_createModule_CallFunc);
    iocshRegister(&RFCFW_deleteModule_FuncDef,  RFCFW_deleteModule_CallFunc);
    iocshRegister(&RFCFW_setupModule_FuncDef,   RFCFW_setupModule_CallFunc);
}

epicsExportRegistrar(RFCFW_IOCShellRegister);

#ifdef __cplusplus
}
#endif

