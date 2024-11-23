#include "statusWords.h"
#include "apdu.h"

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>

#define RED_COLOR		"\033[0;31m"
#define GREEN_COLOR		"\033[0;32m"
#define YELLOW_COLOR	"\033[0;33m"
#define BLUE_COLOR		"\033[0;34m"
#define PINK_COLOR		"\033[0;35m"
#define SKY_BLUE_COLOR	"\033[0;36m"
#define DEFAULT_COLOR	"\033[0m"
#define UDP_PORT		(8584)

typedef struct
{
	int32_t sock;
	struct sockaddr_in sAddr;
	struct sockaddr_in cAddr;
	socklen_t sockLen;
} UDP_handler;

typedef struct {
	uint8_t cla;
	uint8_t ins;
	uint8_t p1;
	const char* descr;
} command_t;

static UDP_handler udpHdlr;
static APDU* apdu;

static const command_t cmds[] = {
	{ 0x00, 0xa4, 0x04, "iso select" },
	{ 0x00, 0xca, 0x9f, "iso get data: CPLC" },
	{ 0x00, 0xca, 0x00, "iso get data: extra data" },

	{ 0x80, 0xec, 0x10, "perso: pre start" },
	{ 0x80, 0xec, 0x20, "perso: pre complete" },
	{ 0x80, 0xec, 0x30, "perso: end" },
};

static void
udp_printCommand(const uint8_t* buffer, uint16_t size)
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

static void
udp_printAnswer(const uint8_t* buffer, uint16_t size)
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

static void
udp_printAtr(const uint8_t* atr, uint16_t size)
{
	printf(GREEN_COLOR "\nATR: ");

	for (uint16_t i = 0; i < size; ++i)
		printf("%02X", (uint8_t)atr[i]);

	printf(DEFAULT_COLOR "\n");
	fflush(stdout);
}

void
udp_init(void* a)
{
	if ((udpHdlr.sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		perror("socket creation failed.");
		exit(1);
	}

	/* Reset endpoints */
	memset(&udpHdlr.sAddr, 0, sizeof(udpHdlr.sAddr));
	memset(&udpHdlr.cAddr, 0, sizeof(udpHdlr.cAddr));

	/* Fill in server info */
	udpHdlr.sAddr.sin_family = AF_INET;
	udpHdlr.sAddr.sin_addr.s_addr = INADDR_ANY;
	udpHdlr.sAddr.sin_port = htons(UDP_PORT);

	/* Bind the socket with the server address. */
	if (bind(udpHdlr.sock, (const struct sockaddr*)&udpHdlr.sAddr, sizeof(udpHdlr.sAddr)) < 0) {
		perror("Failed to bind the socket with the server address.");
		exit(1);
	}

	apdu = (APDU*)a;
	printf("listening to port #%d...\n", UDP_PORT);
}

void
udp_recvCmd(void)
{
	memset(apdu->buffer, 0, APDU_BUFF_LENGTH);

	uint16_t n = recvfrom(udpHdlr.sock,
					apdu->buffer,
					APDU_BUFF_LENGTH,
					MSG_WAITALL,
					(struct sockaddr*)&udpHdlr.cAddr,
					&udpHdlr.sockLen
				);
    
	apdu->recvLen = n;
	udp_printCommand(apdu->buffer, apdu->recvLen);

	apdu->sendLen = 0;
}

void
udp_recvData(void)
{
	/* Nothing to do for WebSocket, because in contrast to T0, the udp_recvCmd()
	 * function fetches both the command header and the data buffer at a time. */
}

void
udp_sendData(uint8_t* data, uint16_t length)
{
	memmove(apdu->buffer + apdu->sendLen, data, length);
	apdu->sendLen += length;
}

void
udp_sendSW(uint16_t sw)
{
	apdu->SW = sw;
	apdu->buffer[apdu->sendLen] = apdu->SW >> 8;
	apdu->buffer[apdu->sendLen + 1] = apdu->SW & 0xFF;
	apdu->sendLen += 2;

	sendto(udpHdlr.sock, (uint8_t*)apdu->buffer, apdu->sendLen,  
        MSG_CONFIRM, (const struct sockaddr *) &udpHdlr.cAddr, 
        udpHdlr.sockLen
	);

	udp_printAnswer((const void*)apdu->buffer, apdu->sendLen);

	memset(apdu->buffer, 0x00, APDU_COMMAD_LENGTH + APDU_DATA_LENGTH);
	apdu->sendLen = 0x00;
}