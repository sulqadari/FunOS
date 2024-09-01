#include <stdbool.h>
#include <stdint.h>
#include "APDU.h"
#include "StatusWords.h"
#include "WS/ws_wraper.h"

// Fast-forward declaration
static void receiveCmd(Interface iface);
static void receiveData(Interface iface);
static void sendData(Interface iface, uint8_t* data, uint32_t length);
static void sendSW(uint16_t sw);
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
	apdu->sendOffset = 0;
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
sendSW(uint16_t)
{

}

void static
process(void)
{

}