#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "apdu.h"
#include "udp/udp.h"

int
main(int argc, char* argv[])
{
	APDU* apdu;
	apdu_init();
	apdu = apdu_getReference();

#if defined(FUNOS_SIMULATOR)
	udp_init();
#endif /* FUNOS_SIMULATOR */

	while (true) {
		apdu_receiveCmd();
		apdu_receiveData();
		apdu_sendData(apdu->buffer, apdu->sendLength);
		apdu_sendSW(apdu->SW);
	}
	return (0);
}