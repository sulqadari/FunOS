#include <stdbool.h>
#include <stdint.h>
#include "apdu.h"
#include "statusWords.h"
#include "ws_wraper.h"

static APDU_t apdu;

void
apdu_receiveCmd(void)
{
	switch (apdu.iface) {
		case iface_websocket: ws_recvCmd(); break;
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
		case iface_websocket: ws_sendData(data, length); break;
		default:
	}
}

void
apdu_sendSW(uint16_t sw)
{
	switch (apdu.iface) {
		case iface_websocket: ws_sendSW(sw); break;
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

APDU_t*
apdu_get(void)
{
	return &apdu;
}