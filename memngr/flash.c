#include "flash.h"

static uint32_t mmStart;		/*!< The lower bound of the memory. */
static uint32_t mmBound;		/*!< The upper bound of the memory. */
static uint32_t mmPageSize;		/*!< typical size is 512 bytes. */
static uint32_t mmPagesTotal;	/*!< derived from memory size divided by page size. */
static uint32_t mmBlkSize;		/*!< payload: the whole page except 'MemHdr_t' service data. */
static mmStatus mmIsInitialzied;

typedef struct {
	uint32_t len;
	uint32_t usrid;
} MemHdr_t;

mmStatus
flashInit(uint32_t lowerBound, uint32_t upperBound, uint32_t pSize)
{
	mmStart      = lowerBound;
	mmBound      = upperBound;
	mmPageSize   = pSize;
	mmPagesTotal = ((upperBound - lowerBound) / pSize);
	mmBlkSize    = mmPageSize - sizeof(MemHdr_t);

	mmIsInitialzied = mmInitialized;

	return mmOk;
}

mmStatus
flashAlloc(uint32_t blkId, uint32_t offset, uint32_t len, uint8_t fill)
{
	for (uint32_t i = offset; i < len;) {
		
	}

	return mmOk;
}