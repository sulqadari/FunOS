#ifndef FUNOS_FLASH_H
#define FUNOS_FLASH_H

#include <stdint.h>

typedef enum {
	mmOk = 0xC00D,
	mmInitialized = 0xBABE,
	mmNotFound = 0xFADE,
	mmNotEmoughMemory = 0xDEAF,
	mmError = 0xDEAD,
} mmStatus;

mmStatus flashInit(uint32_t lowerBound, uint32_t upperBound, uint32_t pageSize);

#endif /* FUNOS_FLASH_H */