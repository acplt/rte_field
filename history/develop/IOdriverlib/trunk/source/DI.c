
/******************************************************************************
*
*   FILE
*   ----
*   DI.c
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
 * Transport inputs to outputs.
 * Transport In if SimOn==0, else take SimIn.
 * Calculate TimeStamp for output: if PvSwitch==1 use Pv's TimeStamp, else generate it from execution time.
 *
 */

OV_DLLFNCEXPORT void IOdriverlib_DI_typemethod(
	OV_INSTPTR_fb_functionblock	pfb,
	OV_TIME						*pltc
) {
    /*    
    *   local variables
    */
    OV_TIME temptime;
	OV_INSTPTR_IOdriverlib_DI pinst = Ov_StaticPtrCast(IOdriverlib_DI, pfb);

	if(pinst->v_SimOn)	//Simulation-mode --> use SimIn(Pv)
	{
		if(pinst->v_PvSwitch)	//Use Pvs time Stamp
		{
			pinst->v_Pv = pinst->v_SimInPv.value;
			pinst->v_TimeStamp = pinst->v_SimInPv.time;
			pinst->v_PvPv = pinst->v_SimInPv;
		}
		else	//generate TimeStamp
		{
			ov_time_gettime(&temptime);
			pinst->v_Pv = pinst->v_SimIn;
			pinst->v_TimeStamp = temptime;
			pinst->v_PvPv.value = pinst->v_SimIn;
			pinst->v_PvPv.time = temptime;
		}
	}
	else	//field mode
	{
		if(pinst->v_PvSwitch)	//Use Pvs time Stamp
		{
			pinst->v_Pv = pinst->v_InPv.value;
			pinst->v_TimeStamp = pinst->v_InPv.time;
			pinst->v_PvPv = pinst->v_InPv;
		}
		else	//generate TimeStamp
		{
			ov_time_gettime(&temptime);
			pinst->v_Pv = pinst->v_In;
			pinst->v_TimeStamp = temptime;
			pinst->v_PvPv.value = pinst->v_In;
			pinst->v_PvPv.time = temptime;
		}
	}


    return;
}

/**
 * Initialize PVs.
 */

OV_DLLFNCEXPORT OV_RESULT IOdriverlib_DI_constructor(
	OV_INSTPTR_ov_object 	pobj
) {
    /*    
    *   local variables
    */
    OV_INSTPTR_IOdriverlib_DI pinst = Ov_StaticPtrCast(IOdriverlib_DI, pobj);
    OV_RESULT    result;

    /* do what the base class does first */
    result = IOdriverlib_input_constructor(pobj);
    if(Ov_Fail(result))
         return result;

    /* do what */

    pinst->v_InPv.time.secs = 0;
    pinst->v_InPv.time.usecs = 0;
    pinst->v_SimInPv.time.secs = 0;
    pinst->v_SimInPv.time.usecs = 0;
    pinst->v_PvPv.time.secs = 0;
    pinst->v_PvPv.time.usecs = 0;
    pinst->v_PvPv.state = KS_ST_NOTSUPPORTED;
    pinst->v_TimeStamp.secs = 0;
    pinst->v_TimeStamp.usecs = 0;

    return OV_ERR_OK;
}
