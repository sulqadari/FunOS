#ifndef FUNOS_GP_COMMON_H
#define FUNOS_GP_COMMON_H

/* clause 5.1, "Card Life Cycle". See clause 11.1, "General Coding Rules"
 * for details about assigned values. */
typedef enum {
	lcs_ready			= 0x01,		/* <! Card life cycle: ready. */
	lcs_initialized		= 0x07,		/* <! Card life cycle: initialized. */
	lcs_secured			= 0x0F,		/* <! Card life cycle: secured. */
	lcs_locked			= 0x7F,		/* <! Card life cycle: locked. */
	lcs_terminated		= 0xFF		/* <! Card life cycle: terminated. */
} CardLcs_e;

/* clause 5.2, "Executable Load File/ Executable Module Life Cycle".
 * See clause 11.1, "General Coding Rules" for details about assigned values. */
typedef enum {
	lcs_loaded			= 0x01		/* <! Executable Load File Life Cycle: loaded. */
} ElfLcs_e;

/* clause 5.3.1, "Application Life Cycle States". See clause 11.1, "General Coding Rules"
 * for details about assigned values. */
typedef enum {
	lcs_installed		= 0x03,		/* <! Application Life Cycle: installed. */
	lcs_selectable		= 0x07,		/* <! Application Life Cycle: selectable. */
	lcs_personalized	= 0x0F,		/* <! Application Life Cycle: selectable. */
	lcs_locked			= 0x83,		/* <! Application Life Cycle: locked. */
} AppLcs_e;

/* clause 5.3.2, "Security Domain Life Cycle States". See clause 11.1, "General Coding
 * Rules" for details about assigned values. */
typedef enum {
	lcs_installed		= 0x03,		/* <! Application Life Cycle: installed. */
	lcs_selectable		= 0x07,		/* <! Application Life Cycle: selectable. */
	lcs_personalized	= 0x0F,		/* <! Application Life Cycle: selectable. */
	lcs_locked			= 0x83,		/* <! Application Life Cycle: locked. */
} SdLcs_e;

#endif /* FUNOS_GP_COMMON_H */