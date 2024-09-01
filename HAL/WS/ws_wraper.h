#ifndef FUNOS_WS_INTERFACE
#define FUNOS_WS_INTERFACE

#include "APDU.h"

void ws_init(APDU_t* instance);
void ws_recvCmd(void);
void ws_recvData(void);
void ws_sendSW(uint16_t sw);

#endif /* FUNOS_WS_INTERFACE */