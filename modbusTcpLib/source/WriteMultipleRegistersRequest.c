
/******************************************************************************
 *
 *   FILE
 *   ----
 *   WriteMultipleRegistersRequest.c
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
#include "ov_macros.h"
#include "ov_memstack.h"
#include "ksbase_helper.h"


OV_DLLFNCEXPORT OV_RESULT modbusTcpLib_WriteMultipleRegistersRequest_handleResponse(
		OV_INSTPTR_modbusTcpLib_Request	thisReq,
		OV_UINT		dataLength,
		OV_BYTE*	dataToHandle
) {
	OV_BYTE	operationCode;
	OV_BYTE	errorCode;
	OV_TIME timestamp;
	OV_INSTPTR_modbusTcpLib_IOChannel	pIOCHannel = NULL;
	OV_INSTPTR_modbusTcpLib_Slave		pSlave	=	NULL;

	ov_time_gettime(&timestamp);

	/*	request	*/
	operationCode = *dataToHandle;
	dataToHandle++;
	if((operationCode & 0x7F) == (thisReq->v_requestType)){
		pIOCHannel = Ov_GetChild(modbusTcpLib_requestToChannel, thisReq);
		if(!pIOCHannel){
			return OV_ERR_GENERIC;
		}
		pSlave = Ov_DynamicPtrCast(modbusTcpLib_Slave, Ov_GetParent(ov_containment, thisReq)->v_pouterobject);
		if(pSlave){
			pSlave->v_error = ((thisReq->v_requestType & 0xFF) & 0x80)?TRUE:FALSE;
		}
		errorCode = *dataToHandle;
		dataToHandle++;
		do{
			pIOCHannel->v_error = ((thisReq->v_requestType & 0xFF) & 0x80)?TRUE:FALSE;
			pIOCHannel->v_errorCode = errorCode;
			modbusTcpLib_IOChannel_setErrorText(pIOCHannel);
			Ov_LinkPlaced(modbusTcpLib_errorChannels, pSlave, pIOCHannel, OV_PMH_END);
			pIOCHannel = Ov_GetNextChild(modbusTcpLib_toNextChannel, pIOCHannel);
		}while(pIOCHannel);
	} else {
		/*	weird things....	*/
		pIOCHannel = Ov_GetChild(modbusTcpLib_requestToChannel, thisReq);
		if(!pIOCHannel){
			return OV_ERR_GENERIC;
		}
		pSlave = Ov_DynamicPtrCast(modbusTcpLib_Slave, Ov_GetParent(ov_containment, thisReq)->v_pouterobject);
		if(pSlave){
			pSlave->v_error = TRUE;
		}
		errorCode = 0xFF;
		do{
			pIOCHannel->v_error = TRUE;
			pIOCHannel->v_errorCode = errorCode;
			modbusTcpLib_IOChannel_setErrorText(pIOCHannel);
			Ov_LinkPlaced(modbusTcpLib_errorChannels, pSlave, pIOCHannel, OV_PMH_END);
			pIOCHannel = Ov_GetNextChild(modbusTcpLib_toNextChannel, pIOCHannel);
		}while(pIOCHannel);
	}
	return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_RESULT modbusTcpLib_WriteMultipleRegistersRequest_constructor(
		OV_INSTPTR_ov_object 	pobj
) {
	/*
	 *   local variables
	 */
	OV_INSTPTR_modbusTcpLib_WriteMultipleRegistersRequest pinst = Ov_StaticPtrCast(modbusTcpLib_WriteMultipleRegistersRequest, pobj);
	OV_RESULT    result;

	/* do what the base class does first */
	result = ov_object_constructor(pobj);
	if(Ov_Fail(result))
		return result;

	/* do what */
	pinst->v_requestID = modbusTcpLib_ModbusTcpManager_getReqId();
	pinst->v_requestType = 16;

	return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_RESULT modbusTcpLib_WriteMultipleRegistersRequest_sendRequest(
		OV_INSTPTR_modbusTcpLib_Request thisReq
) {
	KS_DATAPACKET request;
	OV_INSTPTR_TCPbind_TCPChannel	pChannel = NULL;
	OV_VTBLPTR_TCPbind_TCPChannel	pVtblChannel	=	NULL;
	OV_INSTPTR_ov_domain			pDomain	=	NULL;
	OV_INSTPTR_modbusTcpLib_Slave	pSlave	=	NULL;
	OV_RESULT result;
	OV_INSTPTR_modbusTcpLib_IOChannel	pIOChannel = NULL;
	OV_UINT	iterator;

	pSlave = Ov_DynamicPtrCast(modbusTcpLib_Slave, pDomain->v_pouterobject);
	ov_memstack_lock();
	request.length = 7 + 6 + 2 * thisReq->v_requestedItems;
	request.data = ov_memstack_alloc(request.length);
	if(!request.data){
		return OV_ERR_HEAPOUTOFMEMORY;
	}
	for(iterator = 0; iterator < request.length; iterator++){
		request.data[iterator] = 0;
	}
	request.readPT = request.data;
	request.writePT = request.data;
	/*	MBAP header	*/
	modbusTcpLib_Request_writeWord(thisReq->v_requestID, request.writePT);
	request.writePT += 2;
	modbusTcpLib_Request_writeWord(0, request.writePT);	//	protocol identification; has to be 0
	request.writePT += 2;
	modbusTcpLib_Request_writeWord(request.length - 6, request.writePT);	// number of bytes following
	request.writePT += 2;
	*request.writePT = (OV_BYTE)(thisReq->v_unitIdentifier & 0xFF);
	request.writePT += 1;
	/*	request	*/
	*request.writePT = (OV_BYTE)(thisReq->v_requestType & 0xFF);
	request.writePT += 1;
	modbusTcpLib_Request_writeWord(thisReq->v_requestStartAddr, request.writePT);
	request.writePT += 2;
	modbusTcpLib_Request_writeWord(thisReq->v_requestedItems, request.writePT);
	request.writePT += 2;
	*request.writePT = (OV_BYTE)((thisReq->v_requestedItems * 2) & 0xFF);
	request.writePT += 1;

	pIOChannel = Ov_GetChild(modbusTcpLib_requestToChannel, thisReq);
	if(!pIOChannel){
		return OV_ERR_GENERIC;
	}
	do{
		if(((pIOChannel->v_address - thisReq->v_requestStartAddr)) <= thisReq->v_requestedItems){
			if(Ov_CanCastTo(modbusTcpLib_AoRO, pIOChannel)){
				if(Ov_StaticPtrCast(modbusTcpLib_AoRO, pIOChannel)->v_rawSwitch){
					modbusTcpLib_Request_writeWord(Ov_StaticPtrCast(modbusTcpLib_AoRO, pIOChannel)->v_FV, &(request.writePT[pIOChannel->v_address - thisReq->v_requestStartAddr]));
				} else {
					modbusTcpLib_Request_writeWord((OV_INT)(Ov_StaticPtrCast(modbusTcpLib_AoRI, pIOChannel)->v_PV
							* (Ov_StaticPtrCast(modbusTcpLib_AoRI, pIOChannel)->v_RawHi - Ov_StaticPtrCast(modbusTcpLib_AoRI, pIOChannel)->v_RawLo)),
							&(request.writePT[pIOChannel->v_address - thisReq->v_requestStartAddr]));
				}
			}
		} else {
			pIOChannel->v_error = TRUE;
			pIOChannel->v_errorCode = 0xFF;
			modbusTcpLib_IOChannel_setErrorText(pIOChannel);
			Ov_LinkPlaced(modbusTcpLib_errorChannels, pSlave, pIOChannel, OV_PMH_END);
		}
		pIOChannel = Ov_GetFirstChild(modbusTcpLib_toNextChannel, pIOChannel);
	}while(pIOChannel);
	/*	get channel	*/
	pDomain = Ov_GetParent(ov_containment, thisReq);
	if(!pDomain){
		ov_memstack_unlock();
		return OV_ERR_BADPLACEMENT;
	}

	pChannel = &pSlave->p_channel;
	Ov_GetVTablePtr(TCPbind_TCPChannel, pVtblChannel, pChannel);
	if(!pVtblChannel){
		ov_memstack_unlock();
		return OV_ERR_GENERIC;
	}
	/*	copy data and send	*/
	result = ksbase_KSDATAPACKET_append(&(pChannel->v_outData), request.data, request.length);
	ov_memstack_unlock();
	if(Ov_OK(result)){
		pVtblChannel->m_SendData(Ov_PtrUpCast(ksbase_Channel, pChannel));
	}
	ov_time_gettime(&thisReq->v_validTill);
	thisReq->v_validTill.secs += pSlave->v_timeout;
	return result;
}

