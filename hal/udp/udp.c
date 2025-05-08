#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>
#include <stdlib.h>
#include <signal.h>

#include "apdu.h"
#include "cmdParser.h"

#define UDP_PORT (8584)
static struct sockaddr_in serverAddress = {0};
static struct sockaddr_in clientAddress = {0};
static socklen_t socketLength = sizeof(clientAddress);

static int socketFd;

void
udp_recvCmd(APDU* apdu)
{
	memset(apdu->buffer, 0, APDU_COMMAD_LENGTH + APDU_DATA_LENGTH);
	uint16_t n = recvfrom(socketFd, apdu->buffer,
					APDU_COMMAD_LENGTH + APDU_DATA_LENGTH, MSG_WAITALL,
					(struct sockaddr*)&clientAddress, &socketLength
				);
    
	apdu->recvLength = n;
	apdu->sendLength = 0;
	utils_printCommand(apdu->buffer, apdu->recvLength);
}

void
udp_recvData(void)
{
	/* Nothing to do for WebSocket, because in contrast to T0, the udp_recvCmd()
	 * function fetches both the command header and the data buffer at a time. */
}

void
udp_sendData(APDU* apdu, uint8_t* data, uint16_t length)
{
	memmove(apdu->buffer + apdu->sendLength, data, length);
	apdu->sendLength += length;
}

void
udp_sendSW(APDU* apdu, uint16_t sw)
{
	apdu->SW = sw;
	apdu->buffer[apdu->sendLength] = apdu->SW >> 8;
	apdu->buffer[apdu->sendLength + 1] = apdu->SW & 0xFF;
	apdu->sendLength += 2;

	sendto(socketFd, (uint8_t*)apdu->buffer, apdu->sendLength, MSG_CONFIRM,
					(const struct sockaddr *) &clientAddress, socketLength);

	utils_printAnswer((const void*)apdu->buffer, apdu->sendLength);

	memset(apdu->buffer, 0x00, APDU_COMMAD_LENGTH + APDU_DATA_LENGTH);
	apdu->sendLength = 0x00;
}

void
udp_init(void)
{
	if ((socketFd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		perror("socket creation failed.");
		exit(1);
	}

	/* Reset endpoints */
	memset(&serverAddress, 0, sizeof(serverAddress));
	memset(&clientAddress, 0, sizeof(clientAddress));

	/* Fill in server info */
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = INADDR_ANY;
	serverAddress.sin_port = htons(UDP_PORT);

	/* Bind the socket with the server address. */
	if (bind(socketFd, (const struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
		perror("Failed to bind the socket with the server address.");
		exit(1);
	}
	
	printf("listening to port #%d...\n", UDP_PORT);
}