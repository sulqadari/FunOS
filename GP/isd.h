#ifndef FUNOS_ISD_H
#define FUNOS_ISD_H

#include <stdint.h>
#include "isd.h"
#include "open.h"

typedef enum {
	privSD	= 0,		/* <! The application is SD. */
	privDAP,			/* <! Verify a DAP (clause 9.2.1). */
	privDelMgmt,		/* <! Delegated Card Content Mgmt (9.1.3.3). Note: 'privSD' is required. */
	privCardLock,		/* <! Card locking privilege (9.6.3). */
	privTerminate,		/* <! Card terminating privilege (9.6.4). */
	privReset,			/* <! Modify ATR's historical bytes (6.6.2). */
	privCVMmgmt,		/* <! Shared CardHolder Verification Method (8.2.1). */
	privDAPMandate,		/* <! An App requires the verification of a DAP (9.2.1). Note: 'privSD' and 'privDAP' are required. */
	privTrustPath,		/* <! An App is a Trusted Path for interapplication communication (6.7). */
	privAuthMgmt,		/* <! Card Content Management capable application (9.1.3.2). Note: 'privSD' is required.*/
	privTknVrfn,		/* <! An App is capable of verifying a token for 'privDelMgmt' (9.1.3.1 and 9.2.3). */
	privGlblDelete,		/* <! An App might delete any Card Content (9.1.3.4 and 9.5). */
	privGlblLock,		/* <! An App might lock or unlock any Application (9.1.3.5 and 9.6.2). */
	privGlblRegtry,		/* <! An App might access any entry in the GP Registry (aka GPRegistry_t) (9.6.5). */
	privFinalApp,		/* <! The only App selectable in the CLCS 'lcs_locked' and 'lcs_locked. and 'lcs_terminated' (9.6.4). */
	privGlblService,	/* <! An App provides services to other applications on the Card (8.1.1). */
	privReceiptGen,		/* <! An App is capable of generating a receipt for 'privDelMgmt' (9.1.3.6). */
	privLoadFileEnc,	/* <! The SD requires that the Load File being associated to it is to be loaded ciphered (9.1.3.7). */
	privCLActivate,		/* <! An App is capable of [de]activating on the contactless interface (Amd C, clause 7.1). */
	privCLSelfActivate,	/* <! An App is capable of activating itself on the contactless interface without a prior request to
						 * the Application with the Contactless Activation privilege (Amd C, clause 7.2). */
} SDPrivilege_e;

typedef struct SecurityDomain { 
	CardLCS_e cardLcStart;
	uint32_t currApp;
} SD_t;

#endif /* FUNOS_ISD_H */