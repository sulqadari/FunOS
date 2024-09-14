#ifndef FUNOS_ISD_H
#define FUNOS_ISD_H

#include <stdint.h>
#include "commonInfo.h"

/**
 * GPCS, clause 6.6.1, "Privilege Definition".
 * The following enumeration defines Security Domain and Application privileges.
 * See clause 11.1.2, "Privileges Coding" for details about the values beind assigned. */
typedef enum {
	privSD			= 0x00000000,	/* <! The application is the Security Domain. */
	privDAPVerify	= 0x000000C0,	/* <! Verify a DAP (clause 9.2.1). */
	privDelMgmt		= 0x000000A0,	/* <! Delegated Card Content Mgmt (9.1.3.3). Note: 'privSD' is required. */
	privCardLock	= 0x00000010,	/* <! Card locking privilege (9.6.3). */
	privTerminate	= 0x00000008,	/* <! Card terminating privilege (9.6.4). */
	privReset		= 0x00000004,	/* <! Modify ATR's historical bytes (6.6.2). */
	privCVMMgmt		= 0x00000002,	/* <! Shared CardHolder Verification Method (8.2.1). */
	privDAPVerifyM	= 0x000000C1,	/* <! An App requires the verification of a DAP (9.2.1). Note: 'privSD' and 'privDAP' are required. */
	privTrustPath	= 0x00008000,	/* <! An App is a Trusted Path for interapplication communication (6.7). */
	privAuthMgmt	= 0x00004000,	/* <! Card Content Management capable application (9.1.3.2). Note: 'privSD' is required.*/
	privTknMgmt		= 0x00002000,	/* <! An App is capable of verifying a token for 'privDelMgmt' (9.1.3.1 and 9.2.3). */
	privGlblDelete	= 0x00001000,	/* <! An App might delete any Card Content (9.1.3.4 and 9.5). */
	privGlblLock	= 0x00000800,	/* <! An App might lock or unlock any Application (9.1.3.5 and 9.6.2). */
	privGlblRegtry	= 0x00000400,	/* <! An App might access any entry in the GP Registry (aka GPRegistry_t) (9.6.5). */
	privFinalApp	= 0x00000200,	/* <! The only App selectable in the CLCS 'lcs_locked' and 'lcs_locked. and 'lcs_terminated' (9.6.4). */
	privGlblService	= 0x00000100,	/* <! An App provides services to other applications on the Card (8.1.1). */
	privReceiptGen	= 0x00800000,	/* <! An App is capable of generating a receipt for 'privDelMgmt' (9.1.3.6). */
	privLoadFileEnc	= 0x00400000,	/* <! The SD requires that the Load File being associated to it is to be loaded ciphered (9.1.3.7). */
	privCLActivate	= 0x00200000,	/* <! An App is capable of [de]activating on the contactless interface (Amd C, clause 7.1). */
	privCLSelfActiv	= 0x00010000,	/* <! An App is capable of activating itself on the contactless interface without a prior request to the Application with the Contactless Activation privilege (Amd C, clause 7.2). */
} SdPrivl_e;

/*
 * GPCS, clause 7, "Security Domains"
 */
typedef struct Sd_t {
	SdLcs_e		lcState;
	SdPrivl_e	privilege;
	uint32_t	currApp;
	Sd_t*		parent;
} Sd_t;

#endif /* FUNOS_ISD_H */