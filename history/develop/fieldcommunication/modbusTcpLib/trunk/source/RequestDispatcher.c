
/******************************************************************************
 *
 *   FILE
 *   ----
 *   RequestDispatcher.c
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
#include "libov/ov_memstack.h"
#include "libov/ov_result.h"
#include "ksbase_helper.h"

OV_DLLFNCEXPORT void modbusTcpLib_RequestDispatcher_typemethod (
	OV_INSTPTR_ksbase_ComTask	this
) {
    this->v_actimode = 0;
    Ov_Unlink(ksbase_AssocComTaskList, Ov_GetParent(ksbase_AssocComTaskList, this), this);
	return;
}


OV_DLLFNCEXPORT OV_RESULT modbusTcpLib_RequestDispatcher_HandleData(
		OV_INSTPTR_ksbase_DataHandler this,
		OV_INSTPTR_ksbase_Channel pChannel,
		KS_DATAPACKET* dataReceived,
		KS_DATAPACKET* answer
) {
	OV_INT requestId;
	OV_INT protocolID;
	OV_INT lengthAfterHeader;
	OV_BYTE unitIdentifier;
	OV_UINT offset = 0;
	OV_UINT packetLength;
	OV_INSTPTR_modbusTcpLib_Request pRequest = NULL;
	OV_VTBLPTR_modbusTcpLib_Request pVtblRequest = NULL;
	OV_INSTPTR_modbusTcpLib_IOChannel	pIOChannel	=	NULL;
	OV_INSTPTR_modbusTcpLib_IOChannel	pNextIOChannel	=	NULL;
	OV_RESULT result;

	if(!this->v_pouterobject || !Ov_CanCastTo(modbusTcpLib_Slave, this->v_pouterobject)){
		ov_logfile_error("%s: RequestDispatchers only work as parts of modbusTcpLib/Slaves", this->v_identifier);
		ksbase_free_KSDATAPACKET(dataReceived);
	}
	do{
		packetLength = (dataReceived->data + dataReceived->length) - dataReceived->readPT;
		if(packetLength < 9){
			/*	incomplete	*/
			return OV_ERR_OK;
		}
		/*	MBAP header	*/
		requestId = modbusTcpLib_Request_readWord(dataReceived->readPT);
		offset = 2;
		protocolID = modbusTcpLib_Request_readWord(dataReceived->readPT + offset);
		offset += 2;
		lengthAfterHeader = modbusTcpLib_Request_readWord(dataReceived->readPT + offset);
		offset += 2;
		if(packetLength < lengthAfterHeader + offset ){
			/*	incomplete	*/
			return OV_ERR_OK;
		}
		/*	from here on we can assume that at least one complete request was received
		 * 	process it...	*/
		dataReceived->readPT += offset;
		unitIdentifier = *(dataReceived->readPT);
		dataReceived->readPT++;
		lengthAfterHeader--;	//	The byte read last also belongs to the header
		Ov_ForEachChildEx(ov_containment, &(Ov_StaticPtrCast(modbusTcpLib_Slave, this->v_pouterobject)->p_requests), pRequest, modbusTcpLib_Request){
			if(pRequest->v_requestID == requestId){
				/*	found the right request	*/
				Ov_GetVTablePtr(modbusTcpLib_Request, pVtblRequest, pRequest);
				if(!pVtblRequest){
					ov_logfile_error("%s: could not get Vtable of Request", this->v_identifier);
					break;
				}
				if((protocolID != 0) || (unitIdentifier != pRequest->v_unitIdentifier)){
					ov_logfile_error("%s: mismatch of protocolID and/or unitIdentifier", this->v_identifier);
					break;
				}
				result = pVtblRequest->m_handleResponse(pRequest, lengthAfterHeader, dataReceived->readPT);	//
				if(Ov_Fail(result)){
					ov_memstack_lock();
					ov_logfile_error("%s: handle Response failed with error %s", pRequest->v_identifier, ov_result_getresulttext(result));
					ov_memstack_unlock();
				}
				pIOChannel = Ov_GetChild(modbusTcpLib_requestToChannel, pRequest);
				pNextIOChannel = Ov_GetChild(modbusTcpLib_toNextChannel, pIOChannel);
				while(pNextIOChannel){
					Ov_Unlink(modbusTcpLib_toNextChannel, pIOChannel, pNextIOChannel);
					pIOChannel = pNextIOChannel;
					pNextIOChannel = Ov_GetChild(modbusTcpLib_toNextChannel, pIOChannel);
				}
				Ov_DeleteObject(pRequest);
				break;
			}
		}
		if(!pRequest){
			ov_logfile_error("%s: no fitting request object found", this->v_identifier);
		}
		dataReceived->readPT += lengthAfterHeader+1;
		if(dataReceived->readPT >= dataReceived->data + dataReceived->length){
			/*	everything done	*/
			ksbase_free_KSDATAPACKET(dataReceived);
			break;
		}
	}while(1);
	return OV_ERR_OK;
}

