
/******************************************************************************
*
*   FILE
*   ----
*   input.c
*
*   History
*   -------
*   2012-10-02   File created
*
*******************************************************************************
*
*   This file is generated by the 'acplt_builder' command
*
******************************************************************************/


#ifndef OV_COMPILE_LIBRARY_IOdriverlib
#define OV_COMPILE_LIBRARY_IOdriverlib
#endif


#include "IOdriverlib.h"
#include "libov/ov_macros.h"


/**
 * This one is empty. This class not implement functionality.
 */
OV_DLLFNCEXPORT void IOdriverlib_input_typemethod(
	OV_INSTPTR_fb_functionblock	pfb,
	OV_TIME						*pltc
) {
    /*    
    *   local variables
    */

    return;
}

/**
 * Initialize TimeStamp with 0.
 */
OV_DLLFNCEXPORT OV_RESULT IOdriverlib_input_constructor(
	OV_INSTPTR_ov_object 	pobj
) {
    /*    
    *   local variables
    */
    OV_INSTPTR_IOdriverlib_input pinst = Ov_StaticPtrCast(IOdriverlib_input, pobj);
    OV_RESULT    result;

    /* do what the base class does first */
    result = fb_functionblock_constructor(pobj);
    if(Ov_Fail(result))
         return result;

    /* do what */

    pinst->v_TimeStamp.secs = 0;
    pinst->v_TimeStamp.usecs = 0;

    return OV_ERR_OK;
}

