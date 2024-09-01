#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "ISO7816/APDU.h"

int
main(int argc, char* argv[])
{
	APDU_t apdu;
	uint8_t temp[256];
	uint16_t length = 256;

	apdu_init(&apdu);

	while (true) {
		apdu.recvCmd();
		apdu.recvData();
		apdu.process();
		apdu.sendData(temp, length);
		apdu.sendSW(0x9000);
	}
	return (0);
}