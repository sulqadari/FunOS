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

typedef struct APDU {
	uint16_t sendLength;			/* The length of the data to be sent. */
	uint16_t recvLength;
	Interface iface;				/* Interface. */
	uint16_t SW;					/* Status Word. */
	uint8_t buffer[APDU_COMMAD_LENGTH + APDU_DATA_LENGTH];
} APDU;

/* Visa (Sampo Estonia, 2010) */
static const uint8_t ATR[] = { 
	0x3B, 0xEF, 0x00, 0x00, 0x81, 0x31, 0xFE, 0x45,
	/* Historical bytes */
	0x43, 0x4D, 0x42, 0x5F, 0x43, 0x6F, 0x6D, 0x53,
	0x44, 0x41, 0x30, 0x30, 0x35, 0x31, 0x00, 0xE4
};

void apdu_init(void);
void apdu_receiveCmd(void);
void apdu_receiveData(void);
void apdu_sendData(uint8_t* data, uint32_t length);
void apdu_sendSW(uint16_t sw);
APDU* apdu_getReference(void);

#endif /* FUNOS_APDU_H */