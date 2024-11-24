#ifndef FUNOS_UDP_HANDLER_H
#define FUNOS_UDP_HANDLER_H

#include <stdint.h>

void udp_init(void* a);
void udp_recvCmd(void);
void udp_recvData(void);
void udp_sendData(uint8_t* data, uint16_t length);
void udp_sendSW(uint16_t sw);

#endif // !FUNOS_UDP_HANDLER_H