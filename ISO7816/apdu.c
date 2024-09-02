#include <stdbool.h>
#include <stdint.h>
#include "apdu.h"
#include "StatusWords.h"
#include "ws_wraper.h"
#include "tags.h"

// Fast-forward declaration
static void receiveCmd(Interface iface);
static void receiveData(Interface iface);
static void sendData(Interface iface, uint8_t* data, uint32_t length);
static void sendSW(Interface iface, uint16_t sw);
static void process(void);

static APDU_t* apdu;

void
apdu_init(APDU_t* apdu)
{
	apdu->recvCmd	 = &receiveCmd;
	apdu->recvData	 = &receiveData;
	apdu->sendData	 = &sendData;
	apdu->sendSW	 = &sendSW;
	apdu->process	 = &process;
	apdu->sendLength = 0;
	apdu->iface		 = iface_websocket;
	apdu->SW		 = SW_NO_ERROR;
}

static void
receiveCmd(Interface iface)
{
	switch (iface) {
		case iface_websocket: ws_recvCmd(); break;
		default:
	}
}

void static
receiveData(Interface iface)
{
	switch (iface) {
		case iface_websocket: ws_recvData(); break;
		default:
	}
}

void static
sendData(Interface iface, uint8_t* data, uint32_t length)
{
	switch (iface) {
		case iface_websocket: ws_sendData(data, length); break;
		default:
	}
}

void static
sendSW(Interface iface, uint16_t sw)
{
	switch (iface) {
		case iface_websocket: ws_sendSW(sw); break;
		default:
	}
}

void static
process(void)
{
	uint8_t* data   = apdu->buffer;
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