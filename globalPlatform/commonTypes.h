#ifndef FUNOS_GP_COMMON_H
#define FUNOS_GP_COMMON_H

/* clause 5.1, "Card Life Cycle". See clause 11.1, "General Coding Rules"
 * for details about assigned values. */
typedef enum {
	cardReady		= 0x01,		/* <! Card life cycle: ISD is ready to accept APDUs. */
	cardInitialized	= 0x07,		/* <! Card life cycle: initialized. */
	cardSecured		= 0x0F,		/* <! Card life cycle: secured. */
	cardLocked		= 0x7F,		/* <! Card life cycle: locked. */
	cardTerminated	= 0xFF		/* <! Card life cycle: terminated. */
} cardLcs;

/* clause 5.2, "Executable Load File/ Executable Module Life Cycle".
 * See clause 11.1, "General Coding Rules" for details about assigned values. */
typedef enum {
	lcs_loaded			= 0x01		/* <! Executable Load File Life Cycle: loaded. */
} elfLcs;

/* clause 5.3.1, "Application Life Cycle States". See clause 11.1, "General Coding Rules"
 * for details about assigned values. */
typedef enum {
	appInstalled	= 0x03,		/* <! Application Life Cycle: installed. */
	appSelectable	= 0x07,		/* <! Application Life Cycle: selectable. */
	appPersonalized	= 0x0F,		/* <! Application Life Cycle: personalized. */
	appLocked		= 0x83,		/* <! Application Life Cycle: locked. */
} appLcs;

/* NOTE: Current version doesn't feature the multi-SD implementation. And because the ISD
 * inherits a life cycle of the Card, the structure below can be commented out. */
#if (0)
/* clause 5.3.2, "Security Domain Life Cycle States". See clause 11.1, "General Coding
 * Rules" for details about assigned values. */
typedef enum {
	sdInstalled		= 0x03,		/* <! ISD Life Cycle: installed. */
	sdSelectable	= 0x07,		/* <! ISD Life Cycle: selectable. */
	sdPersonalized	= 0x0F,		/* <! ISD Life Cycle: personalized. */
	sdLocked		= 0x83,		/* <! ISD Life Cycle: locked. */
} sdLcs;
#endif

/**
 * GPCS, clause 6.6.1, "Privilege Definition".
 * The following enumeration defines Security Domain and Application privileges.
 * See clause 11.1.2, "Privileges Coding" for values details. */
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
	privRFU			= 0xFFFFFFFF	/* <! RFU. */
} gpPrivilege;

#endif /* FUNOS_GP_COMMON_H */