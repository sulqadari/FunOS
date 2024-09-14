#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "apdu.h"
#include "ws_wraper.h"

static APDU_t* apdu;

int
main(int argc, char* argv[])
{
	apdu_init();
	apdu = apdu_get();
#if defined(FUNOS_SIMULATOR)
	ws_init(apdu);
#endif /* FUNOS_SIMULATOR */

	while (true) {
		apdu_receiveCmd();
		apdu_receiveData();
		apdu_sendData(apdu->buffer, apdu->sendLength);
		apdu_sendSW(apdu->SW);
	}
	return (0);
}