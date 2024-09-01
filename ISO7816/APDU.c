#include <stdbool.h>
#include "APDU.h"

// Fast-forward declaration
static void receiveCmd(void);
static void receiveData(void);
static void sendData(uint8_t*, uint32_t);
static void sendSW(uint16_t);
static void process(void);

static uint8_t ifaceType = 0;
void
apdu_init(APDU_t* apdu)
{
	apdu->recvCmd	= &receiveCmd;
	apdu->recvData	= &receiveData;
	apdu->sendData	= &sendData;
	apdu->sendSW	= &sendSW;
	apdu->process	= &process;
}

static void
receiveCmd(void)
{
	udp_recvCmd();
}

void static
receiveData(void)
{

}

void static
sendData(uint8_t*, uint32_t)
{

}

void static
sendSW(uint16_t)
{

}

void static
process(void)
{

}