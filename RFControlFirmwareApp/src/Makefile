##########################################################
# Makefile
# 
# Makefile for the RF Control Firmware module
# 
# Created by: Zheqiao Geng, gengzq@slac.stanford.edu
# Created on: 2/12/2013
# Description: Initial creation 
##########################################################
TOP=../..

include $(TOP)/configure/CONFIG

#------------------------------------------------
# build the library for RFControl
#------------------------------------------------
# ---- library name ----
LIBRARY_IOC = RFControlFirmware

# ---- sub directory ----
FWC_SIS8300_STRUCK_IQFB = $(TOP)/RFControlFirmwareApp/src/FWControl_sis8300_struck_iqfb
FWC_SIS8300_EICSYS_IQFB = $(TOP)/RFControlFirmwareApp/src/FWControl_sis8300_eicsys_iqfb

SRC_DIRS += $(FWC_SIS8300_STRUCK_IQFB)
SRC_DIRS += $(FWC_SIS8300_EICSYS_IQFB)

USR_DBDFLAGS += -I $(FWC_SIS8300_STRUCK_IQFB)
USR_DBDFLAGS += -I $(FWC_SIS8300_EICSYS_IQFB)

# ---- ported include files ----
INC += RFControlFirmware_main.h
INC += RFControlFirmware_availableInterface_api.h
INC += RFControlFirmware_requiredInterface_fwCtrlVirtual.h
INC += FWControl_sis8300_struck_iqfb.h
INC += FWControl_sis8300_struck_iqfb_board.h
INC += FWControl_sis8300_struck_iqfb_upLink.h
INC += addrMap_sis8300_struck_iqfb.h
INC += FWControl_sis8300_eicsys_iqfb.h
INC += FWControl_sis8300_eicsys_iqfb_board.h
INC += FWControl_sis8300_eicsys_iqfb_upLink.h
INC += addrMap_sis8300_eicsys_iqfb.h

# ---- library database definition files (including record type definitions and all registerations) ----
DBD += RFControlFirmware.dbd
RFControlFirmware_DBD += RFControlFirmware_iocShell.dbd

# ---- private source files ----
RFControlFirmware_SRCS += RFControlFirmware_main.c
RFControlFirmware_SRCS += RFControlFirmware_availableInterface_api.c
RFControlFirmware_SRCS += RFControlFirmware_iocShell.c
RFControlFirmware_SRCS += FWControl_sis8300_struck_iqfb.c
RFControlFirmware_SRCS += FWControl_sis8300_struck_iqfb_board.c
RFControlFirmware_SRCS += FWControl_sis8300_struck_iqfb_upLink.c
RFControlFirmware_SRCS += FWControl_sis8300_eicsys_iqfb.c
RFControlFirmware_SRCS += FWControl_sis8300_eicsys_iqfb_board.c
RFControlFirmware_SRCS += FWControl_sis8300_eicsys_iqfb_upLink.c

# ---- finally link to the EPICS Base libraries ----
RFControlFirmware_LIBS += $(EPICS_BASE_IOC_LIBS)

include $(TOP)/configure/RULES

