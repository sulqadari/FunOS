#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "APDU.h"
#include "WS/ws_wraper.h"

int
main(int argc, char* argv[])
{
	APDU_t apdu;
	uint8_t temp[256];
	uint16_t length = 256;

	apdu_init(&apdu);

#if defined(FUNOS_SIMULATOR)
	ws_init(&apdu);
#endif /* FUNOS_SIMULATOR */

	while (true) {
		apdu.recvCmd(apdu.iface);
		apdu.recvData(apdu.iface);
		apdu.process();
		apdu.sendData(temp, length);
		apdu.sendSW(0x9000);
	}
	return (0);
}