#include <stdbool.h>
#include <stdint.h>
#include "statusWords.h"
#include "apdu.h"
#include "udp/udp_handler.h"

static APDU apdu;

void
apdu_receiveCmd(void)
{
	udp_recvCmd();
}

void
apdu_receiveData(void)
{
	udp_recvData();
}

void
apdu_sendData(uint8_t* data, uint32_t length)
{
	udp_sendData(data, length);
}

void
apdu_sendSW(uint16_t sw)
{
	udp_sendSW(sw);
}

APDU*
apdu_init(void)
{
	apdu.recvLen	= 0;
	apdu.sendLen	= 0;
	apdu.SW		 	= SW_SUCCESS;

	udp_init(&apdu);
	
	return &apdu;
}