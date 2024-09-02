#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "apdu.h"
#include "ws_wraper.h"

int
main(int argc, char* argv[])
{
	APDU_t apdu;

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