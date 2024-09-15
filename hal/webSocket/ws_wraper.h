#ifndef FUNOS_WS_INTERFACE
#define FUNOS_WS_INTERFACE

#include "apdu.h"

void ws_init(void);
void ws_recvCmd(APDU* apdu);
void ws_recvData(void);
void ws_sendSW(APDU* apdu, uint16_t sw);
void ws_sendData(APDU* apdu, uint8_t* data, uint16_t length);

#endif /* FUNOS_WS_INTERFACE */