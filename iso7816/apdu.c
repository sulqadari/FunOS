#include <stdbool.h>
#include <stdint.h>
#include "apdu.h"
#include "statusWords.h"
#include "udp/udp_handler.h"

static APDU apdu;

void
apdu_receiveCmd(void)
{
	switch (apdu.iface) {
		case iface_udp: udp_recvCmd(); break;
		default: break;
	}
}

void
apdu_receiveData(void)
{
	switch (apdu.iface) {
		case iface_udp: udp_recvData(); break;
		default: break;
	}
}

void
apdu_sendData(uint8_t* data, uint32_t length)
{
	switch (apdu.iface) {
		case iface_udp: udp_sendData(data, length); break;
		default: break;
	}
}

void
apdu_sendSW(uint16_t sw)
{
	switch (apdu.iface) {
		case iface_udp: udp_sendSW(sw); break;
		default: break;
	}
}

APDU*
apdu_init(const Interface iface)
{
	apdu.recvLen	= 0;
	apdu.sendLen	= 0;
	apdu.iface		= iface;
	apdu.SW		 	= SW_SUCCESS;

	if (iface == iface_udp)
		udp_init(&apdu);
	
	return &apdu;
}