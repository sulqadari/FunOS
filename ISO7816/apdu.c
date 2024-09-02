#include <stdbool.h>
#include <stdint.h>
#include "apdu.h"
#include "StatusWords.h"
#include "ws_wraper.h"
#include "tags.h"

static APDU_t* apdu;

static void
receiveCmd(void)
{
	switch (apdu->iface) {
		case iface_websocket: ws_recvCmd(); break;
		default:
	}
}

void static
receiveData(void)
{
	switch (apdu->iface) {
		case iface_websocket: ws_recvData(); break;
		default:
	}
}

void static
sendData(uint8_t* data, uint32_t length)
{
	switch (apdu->iface) {
		case iface_websocket: ws_sendData(data, length); break;
		default:
	}
}

void static
sendSW(uint16_t sw)
{
	switch (apdu->iface) {
		case iface_websocket: ws_sendSW(sw); break;
		default:
	}
}

void static
process(void)
{
	uint8_t* data   = &apdu->buffer[APDU_OFFSET_DATA];
	uint8_t claByte = data[APDU_OFFSET_CLA];
	uint8_t insByte = data[APDU_OFFSET_INS];
	uint8_t p1Byte  = data[APDU_OFFSET_P1];
	uint8_t p2Byte  = data[APDU_OFFSET_P2];


	switch (claByte) {
		case GP_CLA_ELM:
		case GP_CLA_WAFER:
		case GP_CLA_PREPERSO:
		case GP_CLA_PERSO:
		case GP_CLA_BLOCKED:	
			apdu->SW = SW_NO_ERROR;
		break;
		default: apdu->SW = SW_UNKNOW;
	}
}

void
apdu_init(APDU_t* inst)
{
	inst->recvCmd	 = &receiveCmd;
	inst->recvData	 = &receiveData;
	inst->sendData	 = &sendData;
	inst->sendSW	 = &sendSW;
	inst->process	 = &process;
	inst->sendLength = 0;
	inst->iface		 = iface_websocket;
	inst->SW		 = SW_NO_ERROR;
	apdu = inst;
}