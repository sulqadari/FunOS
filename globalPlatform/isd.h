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

typedef struct {
	appLcs		lcState;
	gpPrivilege	privilege;
} Application;

/* GPCS, clause 7, "Security Domains".
 * The first application installed on a card and inherits the card life cycle state. */
typedef struct {
	cardLcs*	 lcState;	/* <! The ISD inherits the Card's Life Cycle State. */
	gpPrivilege	 privilege;
	Application* apps;
	ISDKey*		 keys;
} ISD;

cardLcs isd_getCardLifeCycleState(void);
appLcs isd_getAppLifeCycleState(uint8_t* _aid);

gpStatus isd_updatePrivege(gpPrivilege privilege);
gpPrivilege isd_getPrivilege(void);

uint8_t* isd_getAID(void);
gpStatus isd_getKey(ISDKey** _key, uint8_t _kvn, uint8_t _kid);
gpStatus isd_setKey(ISDKey* _key);

#endif /* FUNOS_ISD_H */