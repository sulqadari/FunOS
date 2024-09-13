#ifndef FUNOS_GP_CONTEXT_H
#define FUNOS_GP_CONTEXT_H

/**
 * Spans over every kind of application, including a Security Domains.
 */
typedef enum {
	lcs_loaded			= 0x01,		/* <! Executable Load File Life Cycle: loaded. */
	lcs_installed		= 0x03,		/* <! Application Life Cycle: installed. */
	lcs_selectable		= 0x07,		/* <! Application Life Cycle: selectable. */
	lcs_personalized	= 0x0F,		/* <! Application Life Cycle: personalized. */
	lcs_locked			= 0x83,		/* <! Application Life Cycle: locked. */
} AppLCS_e;

typedef enum {
	lcs_ready			= 0x01,		/* <! Card life cycle: ready. */
	lcs_initialized		= 0x07,		/* <! Card life cycle: initialized. */
	lcs_secured			= 0x0F,		/* <! Card life cycle: secured. */
	lcs_locked			= 0x7F,		/* <! Card life cycle: locked. */
	lcs_terminated		= 0xFF		/* <! Card life cycle: terminated. */
} CardLCS_e;

/**
 * Clause 3.5 "GlobalPlatform Environment".
 * The OPEN owns and uses an internal GlobalPlatform Registry as an
 * information resource for Card Content management, which contains information
 * for managing the below mentioned entities:
 * - Card;
 * - Executable Load Files;
 * - Applications;
 * - SD associations;
 * - privileges.
 */
typedef struct {
	/* data */
} GPRegistry_t;

typedef struct {

} GPCtx_t;

void open_loadApplication(void);
void open_installApplication(void);
void open_manageCardContent(void);
void open_manageMemory(void);
void open_forceSecurityPolicy(void);
void open_dispatchAPDU(void);
void open_selectApplication(void);

#endif /* FUNOS_GP_CONTEXT_H */