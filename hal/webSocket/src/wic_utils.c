#include <stdint.h>
#include "wic_utils.h"
#include "statusWords.h"
#include "apdu.h"

typedef struct {
	uint8_t cla;
	uint8_t ins;
	uint8_t p1;
	const char* descr;
} command_t;

static const command_t cmds[] = {
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
	int j, cmdArrayLen = sizeof(cmds) / sizeof(command_t);
	
	/* Iterate through the list of known commands and display (if any). */
	for (j = 0; j < cmdArrayLen; j++) {

		uint8_t cla = buffer[APDU_OFFSET_CLA];
		uint8_t ins = buffer[APDU_OFFSET_INS];
		uint8_t p1 = buffer[APDU_OFFSET_P1];
		
		if ((cmds[j].cla == cla) && (cmds[j].ins == ins) && (cmds[j].p1 == p1)) {
			printf("%s\n", cmds[j].descr);
			break;
		}
	}

	if (j >= cmdArrayLen)
		printf(RED_COLOR "unknown command\n");

	printf(DEFAULT_COLOR "<< ");

	/* print CLA INS P1 P2. */
	for (int i = 0; i < 4; ++i)
		printf(SKY_BLUE_COLOR "%02X", (uint8_t)buffer[i]);
	
	/* Print Lc */
	if (size >= APDU_COMMAD_LENGTH) {
		printf(PINK_COLOR " %02X ", buffer[APDU_OFFSET_P3]);
	}

	if (size > APDU_COMMAD_LENGTH) {
		/* Print CDATA */
		for (int i = 0; i < buffer[APDU_OFFSET_P3]; ++i) {
			printf(YELLOW_COLOR "%02X", (uint8_t)buffer[i]);
		}

		if (size - APDU_COMMAD_LENGTH != buffer[APDU_OFFSET_P3]) {
			printf(" ");
			for (int i = APDU_COMMAD_LENGTH + buffer[APDU_OFFSET_P3]; i < size; ++i) {
				printf(SKY_BLUE_COLOR "%02X", (uint8_t)buffer[i - 5]);
			}
		}
	}

	printf(DEFAULT_COLOR "\n");
	fflush(stdout);
}

void
wic_printAnswer(const uint8_t* buffer, uint16_t size)
{
	printf(">> ");

	if (size > 2) {
		/* Print response data. */
		for (uint16_t i = 0; i < size - 2; ++i)
			printf(YELLOW_COLOR "%02X", (uint8_t)buffer[i]);

		printf(" ");
	}

	uint16_t sw = ((uint16_t)buffer[size - 2] << 8) | (buffer[size - 1]);

	/* Print SW. */
	if (sw == SW_SUCCESS || (sw & 0xFF00) == SW_BYTES_REMAIN)
		printf(GREEN_COLOR "%04X\n", sw);
	else
		printf(RED_COLOR "%04X\n", sw);

	printf(DEFAULT_COLOR);
	fflush(stdout);
}

void
wic_printAtr(const uint8_t* atr, uint16_t size)
{
	printf(GREEN_COLOR "\nATR: ");

	for (uint16_t i = 0; i < size; ++i)
		printf("%02X", (uint8_t)atr[i]);

	printf(DEFAULT_COLOR "\n");
	fflush(stdout);
}
