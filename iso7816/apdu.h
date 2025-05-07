#ifndef FUNOS_APDU_H
#define FUNOS_APDU_H

#include <stdint.h>

#if(0)
#define APDU_COMMAD_LENGTH	5
#define APDU_DATA_LENGTH	256
#define APDU_BUFF_LENGTH	(APDU_DATA_LENGTH + APDU_COMMAD_LENGTH)
#define OFF_CLA		0
#define OFF_INS		1
#define OFF_P1		2
#define OFF_P2		3
#define OFF_P3		4
#define OFF_DATA	5

typedef struct {
	uint16_t recvLen;		/* Number of received length. */
	uint16_t sendLen;		/* The length of the data to be sent. */
	uint16_t SW;			/* Status Word. */
	uint8_t buffer[APDU_COMMAD_LENGTH + APDU_DATA_LENGTH];
} APDU;

/* Visa (Sampo Estonia, 2010) */
static const uint8_t ATR[] = { 
	0x3B, 0xEF, 0x00, 0x00, 0x81, 0x31, 0xFE, 0x45,
	/* Historical bytes */
	0x43, 0x4D, 0x42, 0x5F, 0x43, 0x6F, 0x6D, 0x53,
	0x44, 0x41, 0x30, 0x30, 0x35, 0x31, 0x00, 0xE4
};

APDU* apdu_init(void);
void apdu_receiveCmd(void);
void apdu_receiveData(void);
void apdu_sendData(uint8_t* data, uint32_t length);
void apdu_sendSW(uint16_t sw);
#endif

/* ISO 7816-4, c 5.2. */
#define APDU_BUFF_LEN 256

/* ISO 7816-4, 5.4 */
#define CLA_SM_PROPRIETARY      0x04
#define CLA_SM_ISO7816          0x0C
#define CLA_COMMAND_CHAIN       0x10    /* When asserted, the 'Le' field must be absent; INS, P1 and P2 are immutable. */
#define CLA_ISO7816_STANDART    0x00
#define CLA_ISO7816_PROPRIETARY 0x80
#define CLA_ISO7816_INVALID     0xFF

/* ISO 7816-4, 5.5 */
#define INS_INVALID_60          0x60
#define INS_INVALID_90          0x90
#define INS_ISO7816_ODD         0x01    /* When asserted, the payload (if any) must be encoded in BER-TLV. */

#define INS_SELECT              0xA4
#define INS_GET_RESPONSE        0xC0
#define INS_GET_DATA            0xCA
#define INS_PUT_DATA            0xDA

typedef struct {
    uint8_t cla;
    uint8_t ins;
    uint8_t p1;
    uint8_t p2;
    uint8_t p3;     /* in range 01-FF */
    uint8_t data[APDU_BUFF_LEN];
    uint8_t le;     /* in range 00-FF */
} CAPDU_t;

typedef struct {
    uint8_t data[APDU_BUFF_LEN];
    uint8_t sw1;
    uint8_t sw2;
} RAPDU_t;

void apdu_init(void);
void apdu_receive_header(void);
void apdu_receive_data(void);
void apdu_send_data(void);
void apdu_send_sw(void);


#endif /* FUNOS_APDU_H */