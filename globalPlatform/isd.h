#ifndef FUNOS_ISD_H
#define FUNOS_ISD_H

#include <stdint.h>
#include "commonTypes.h"

typedef struct {
	AppLcs state;
} Application;

/* GPCS, clause 7, "Security Domains".
 * The first application installed on a card and inherits the card life cycle state. */
typedef struct {
	CardLcs*	lcState;	/* <! The ISD inherits the Card's Life Cycle State. */
	Privilege	privilege;
} ISD;

Status isd_getAID(uint8_t** aidPtr);

#endif /* FUNOS_ISD_H */