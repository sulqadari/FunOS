#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "apdu.h"
#include "ws_wraper.h"

APDU_t apdu;

int
main(int argc, char* argv[])
{
	apdu_init(&apdu);

#if defined(FUNOS_SIMULATOR)
	ws_init(&apdu);
#endif /* FUNOS_SIMULATOR */

	while (true) {
		apdu.recvCmd();
		apdu.recvData();
		apdu.process();
		apdu.sendData(apdu.buffer, apdu.sendLength);
		apdu.sendSW(apdu.SW);
	}
	return (0);
}