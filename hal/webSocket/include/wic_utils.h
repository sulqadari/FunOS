#ifndef WIC_UTILS_H
#define WIC_UTILS_H

#include <stdio.h>
#include <stdint.h>

#define RED_COLOR		"\033[0;31m"
#define GREEN_COLOR		"\033[0;32m"
#define YELLOW_COLOR	"\033[0;33m"
#define BLUE_COLOR		"\033[0;34m"
#define PINK_COLOR		"\033[0;35m"
#define SKY_BLUE_COLOR	"\033[0;36m"
#define DEFAULT_COLOR	"\033[0m"

void wic_printCommand(const uint8_t* buffer, uint16_t size);
void wic_printAnswer(const uint8_t* buffer, uint16_t size);
void wic_printAtr(const uint8_t* buffer, uint16_t size);

#endif // !WIC_UTILS_H