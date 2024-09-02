#ifndef FUNOS_WS_INTERFACE
#define FUNOS_WS_INTERFACE

#include "apdu.h"

void ws_init(APDU_t* instance);
void ws_recvCmd(void);
void ws_recvData(void);
void ws_sendSW(uint16_t sw);
void ws_sendData(uint8_t* data, uint16_t length);

#endif /* FUNOS_WS_INTERFACE */