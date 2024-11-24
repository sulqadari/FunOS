#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "apdu.h"
#include "flash.h"

#define PAGE_SIZE   512
#define PAGES_TOTAL 1
#define FLASH_SIZE  ((PAGE_SIZE * PAGES_TOTAL) / sizeof(uint32_t))

static uint32_t flash[FLASH_SIZE];

int
main(int argc, char* argv[])
{
	APDU* apdu = apdu_init();
	uint8_t* cmd = &apdu->buffer[OFF_CLA];
	flashInit((uint32_t)flash, (uint32_t)(flash + FLASH_SIZE), PAGE_SIZE);

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