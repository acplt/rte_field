
/******************************************************************************
*
*   FILE
*   ----
*   AoRI.c
*
*   History
*   -------
*   2015-04-29   File created
*
*******************************************************************************
*
*   This file is generated by the 'acplt_builder' command
*
******************************************************************************/


#ifndef OV_COMPILE_LIBRARY_modbusTcpLib
#define OV_COMPILE_LIBRARY_modbusTcpLib
#endif


#include "modbusTcpLib.h"
#include "libov/ov_macros.h"

OV_DLLFNCEXPORT OV_RESULT modbusTcpLib_AoRI_RawHi_set(
    OV_INSTPTR_modbusTcpLib_AoRI          pobj,
    const OV_UINT  value
) {
    if(value > 0xFFFF){
    	return OV_ERR_BADVALUE;
    }
	pobj->v_RawHi = value;
    return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_RESULT modbusTcpLib_AoRI_RawLo_set(
    OV_INSTPTR_modbusTcpLib_AoRI          pobj,
    const OV_UINT  value
) {
	if(value > 0xFFFF){
		return OV_ERR_BADVALUE;
	}
    pobj->v_RawLo = value;
    return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_RESULT modbusTcpLib_AoRI_constructor(
	OV_INSTPTR_ov_object 	pobj
) {
    /*    
    *   local variables
    */
    OV_INSTPTR_modbusTcpLib_AoRI pinst = Ov_StaticPtrCast(modbusTcpLib_AoRI, pobj);
    OV_RESULT    result;

    /* do what the base class does first */
    result = modbusTcpLib_IOChannel_constructor(pobj);
    if(Ov_Fail(result))
         return result;

    /* do what */
    pinst->v_functionCode = 04;

    return OV_ERR_OK;
}
