#ifndef FUNOS_APDU_H
#define FUNOS_APDU_H

#include <stdint.h>

#define APDU_COMMAD_LENGTH	5
#define APDU_DATA_LENGTH	256

#define APDU_OFFSET_CLA		0
#define APDU_OFFSET_INS		1
#define APDU_OFFSET_P1		2
#define APDU_OFFSET_P2		3
#define APDU_OFFSET_P3		4
#define APDU_OFFSET_DATA	5

typedef enum {
	iface_websocket
} Interface;

typedef struct {
	uint16_t sendLength;			/* The length of the data to be sent. */
	Interface iface;				/* Interface. */
	uint16_t SW;					/* Status Word. */
	uint8_t buffer[APDU_COMMAD_LENGTH + APDU_DATA_LENGTH];
} APDU_t;

extern APDU_t apdu;

void apdu_init(void);
void apdu_receiveCmd(void);
void apdu_receiveData(void);
void apdu_sendData(uint8_t* data, uint32_t length);
void apdu_sendSW(uint16_t sw);

#endif /* FUNOS_APDU_H */