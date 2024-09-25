#ifndef FUNOS_WS_INTERFACE
#define FUNOS_WS_INTERFACE

#include "apdu.h"

void udp_init(void);
void udp_recvCmd(APDU* apdu);
void udp_recvData(void);
void udp_sendSW(APDU* apdu, uint16_t sw);
void udp_sendData(APDU* apdu, uint8_t* data, uint16_t length);

#endif /* FUNOS_WS_INTERFACE */