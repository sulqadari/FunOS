#include <stdint.h>
#include "wic_utils.h"
#include "StatusWords.h"

typedef struct {
	//uint8_t cmd[3];
	uint8_t cla;
	uint8_t ins;
	uint8_t p1;
	const char* descr;
} commandKt2_t;

static const commandKt2_t cmds[] = {
	{ 0x00, 0xa4, 0x04, "iso select" },
	{ 0x00, 0xca, 0x9f, "iso get data: CPLC" },
	{ 0x00, 0xca, 0x00, "iso get data: extra data" },

	{ 0x80, 0xec, 0x10, "perso: pre start" },
	{ 0x80, 0xec, 0x20, "perso: pre complete" },
	{ 0x80, 0xec, 0x30, "perso: end" },
};

void
wic_printCommand(const uint8_t* buffer, uint16_t size)
{
	uint8_t* cdata = (uint8_t*)&buffer[5];

	int j;
	for (j = 0; j < sizeof(cmds) / sizeof(commandKt2_t); j++) {
		uint8_t cla = buffer[0];
		uint8_t ins = buffer[1];
		uint8_t p1 = buffer[2] & ~0x01;
		if (cmds[j].cla == cla && cmds[j].ins == ins && cmds[j].p1 == p1) {
			if ((buffer[2] & 0x01) != 0) {
				printf("%s (secure channel)\n", cmds[j].descr);
			} else {
				printf("%s\n", cmds[j].descr);
			}
			break;
		}
	}
	if (j >= sizeof(cmds) / sizeof(commandKt2_t)) {
		printf(RED_COLOR);
		printf("unknown command\n");
		printf(DEFAULT_COLOR);
	}

	printf(">> ");
	printf(SKY_BLUE_COLOR);

	/* print CLA INS P1 P2. */
	for (int i = 0; i < 4; ++i) {
		printf("%02X", (uint8_t)buffer[i]);
	}
	
	/* Print Lc */
	if (size >= 5) {
		printf(" %02X ", buffer[4]);
	}

	if (size > 5) {
		/* Print CDATA */
		printf(YELLOW_COLOR);
		for (int i = 0; i < buffer[4]; ++i) {
			printf("%02X", (uint8_t)cdata[i]);
		}
		if (size - 5 != buffer[4]) {
			printf(" ");
			printf(SKY_BLUE_COLOR);
			for (int i = 5 + buffer[4]; i < size; ++i) {
				printf("%02X", (uint8_t)cdata[i - 5]);
			}
		}
	}

	printf(DEFAULT_COLOR);
	printf("\n");
	fflush(stdout);
}

void
wic_printAnswer(const uint8_t* buffer, uint16_t size)
{
	printf(">> ");

	uint16_t sw = (uint16_t)(((uint16_t)buffer[size - 2] << 8) |
				  ((uint16_t)buffer[size - 1]));

	printf((sw == SW_NO_ERROR || (sw & 0xFF00) == SW_BYTES_REMAIN) ? GREEN_COLOR : RED_COLOR);

	/* Print SW. */
	printf("%04X\t\t", sw);

	printf(YELLOW_COLOR);

	if (size > 2) {
		/* Print response data. */
		for (uint16_t i = 0; i < size - 2; ++i) {
//			if ((i != 0) && ((i % 16) == 0))
//				printf("\n   ");

			printf("%02X", (uint8_t)buffer[i]);
		}
		printf(" ");
//		printf("\n   ");
	}



	printf(DEFAULT_COLOR);
	printf("\n");
	fflush(stdout);
}

void
wic_printAtr(const uint8_t* atr, uint16_t size)
{
	printf(GREEN_COLOR);
	printf("ATR: ");

	for (uint16_t i = 0; i < size; ++i)
		printf("%02X", (uint8_t)atr[i]);
	
	printf(DEFAULT_COLOR);
	printf("\n");
	fflush(stdout);
}
