#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "apdu.h"

int
main(int argc, char* argv[])
{
	APDU* apdu = apdu_init(iface_udp);
	uint8_t* cmd = &apdu->buffer[OFF_CLA];
	// uint8_t* data = &apdu->buffer[OFF_DATA];
	
	while (true)
	{
		apdu_receiveCmd();
		switch (cmd[OFF_CLA]) {
			case 0x00:
			case 0x80:
			default: break;
		}
	}
	
	return (0);
}