#include <stdbool.h>
#include <stdint.h>
#include "apdu.h"
#include "statusWords.h"
#include "ws_wraper.h"

static APDU apdu;

void
apdu_receiveCmd(void)
{
	switch (apdu.iface) {
		case iface_websocket: ws_recvCmd(&apdu); break;
		default:
	}
}

void
apdu_receiveData(void)
{
	switch (apdu.iface) {
		case iface_websocket: ws_recvData(); break;
		default:
	}
}

void
apdu_sendData(uint8_t* data, uint32_t length)
{
	switch (apdu.iface) {
		case iface_websocket: ws_sendData(&apdu, data, length); break;
		default:
	}
}

void
apdu_sendSW(uint16_t sw)
{
	switch (apdu.iface) {
		case iface_websocket: ws_sendSW(&apdu, sw); break;
		default:
	}
}

void
apdu_init(void)
{
	apdu.sendLength	= 0;
	apdu.iface		= iface_websocket;
	apdu.SW		 	= SW_SUCCESS;
}

APDU*
apdu_getReference(void)
{
	return &apdu;
}