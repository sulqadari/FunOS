#ifndef FUNOS_ISD_H
#define FUNOS_ISD_H

#include <stdint.h>
#include "commonTypes.h"

typedef struct {
	uint8_t  kvn;		/* <! Key Version Number. */
	uint8_t  kid;		/* <! Key Identifier. */
	uint8_t  type;		/* <! Cryptographic algorithm's identifier. */
	uint16_t length;	/* <! The length of the key. */
	uint8_t* key;		/* <! The key. */
} ISDKey;

/* GPCS, clause 7, "Security Domains".
 * The first application installed on a card. */
typedef struct {
	cardLcs		lcState;	/* <! The ISD inherits the Card's Life Cycle State. */
	gpPrivilege	privilege;
	ISDKey*		key;
} ISD;

cardLcs isd_getLifeCycleState(void);
gpStatus isd_setLifeCycleState(cardLcs lcs);

const uint8_t* isd_getAID(void);

gpPrivilege isd_getPrivilege(void);
gpStatus isd_setPrivilege(gpPrivilege privilege);
gpStatus isd_resetPrivilege(gpPrivilege privilege);

ISDKey* isd_getKey(uint8_t _kvn, uint8_t _kid);
gpStatus isd_setKey(ISDKey* _key);

#endif /* FUNOS_ISD_H */