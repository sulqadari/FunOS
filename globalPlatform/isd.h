#ifndef FUNOS_ISD_H
#define FUNOS_ISD_H

#include <stdint.h>
#include "commonTypes.h"

/* GPCS, clause 7, "Security Domains".
 * The first application installed on a card and inherits the card life cycle state. */
typedef struct {
	CardLcs*	lcState;	/* <! The ISD inherits the Card's Life Cycle State. */
	Privilege	privilege;
} ISD;

#endif /* FUNOS_ISD_H */