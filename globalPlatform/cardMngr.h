/* 
 * Clause 3.8 "Card Manager".
 * The Card Manager as the central administrator of the card, assumes multiple
 * responsibilities. It can be viewed as three entities:
 * - The GlobalPlatform Environment (OPEN) (clause 3.5);
 * - The ISD (clause 7.1.1);
 * - CardHolder Verification Method Services. */

#ifndef FUNOS_GP_CARD_MNGR_H
#define FUNOS_GP_CARD_MNGR_H

#include "commonInfo.h"
#include "securityDomain.h"

/* Clause 6.5, "GlobalPlatform Registry".
 * The GlobalPlatform Registry is used to:
 * - store card management info;
 * - store relevant application management info (e.g., AID, associated SD and privileges);
 * - support card resource management data (c. 6.5.1.3);
 * - store application LCS info;
 * - track any counters associated with logs;
 * 
 * The contents of the Registry may be updated in response to:
 *  - an internal OPEN invoked action;
 *  - an authorized application invoked action. 
 * All applications including all SDs and ELFs shall have an entry in the Registry. */
typedef struct {
	CardLcs_e	cardLcs;
	Sd_t*		isd;
} GpRegistry_t;

typedef struct {

} GpCtx_t;

#endif /* FUNOS_GP_CARD_MNGR_H */