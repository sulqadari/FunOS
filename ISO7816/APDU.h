#ifndef FUNOS_APDU_H
#define FUNOS_APDU_H

#include <stdint.h>

#define APDU_COMMAD_LENGTH	5
#define APDU_DATA_LENGTH	256

typedef struct APDU_t
{
	void (*recvCmd)(void);
	void (*recvData)(void);
	void (*sendData)(uint8_t*, uint32_t);
	void (*sendSW)(uint16_t);
	void (*process)(void);
	uint16_t SW;
	uint8_t buffer[APDU_COMMAD_LENGTH + APDU_DATA_LENGTH];
} APDU_t;

void apdu_init(APDU_t* apdu);

#endif /* FUNOS_APDU_H */