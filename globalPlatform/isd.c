#include <stdlib.h>
#include <string.h>
#include "statuses.h"
#include "isd.h"

#if (0)
/* Issuer Identification Number.
 * May be used to associate the card with a specific Card Management System.
 * See clasue 7.4.1.1 */
static uint8_t IIN[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

/* Card Image Number.
 * May be used by Card Management System to identify a card within its card base.
 * See clause 7.4.1.2 */
static uint8_t CIN[] = {0x00, 0x00, 0x01};

/* An information required by Card Management Systems before they can start to interact
 * with it.
 * See clause 7.4.1.3 and appendix 'H'. */
static uint8_t* cardRecognitionData;

/* Optional data about cipher suites actually supported by the card.
 * See 7.4.1.4 and appendix 'H.4'. */
static uint8_t* cardCapabilityInfo;
#endif

/* ISD AID.
 * See Appendix 'H'.*/
static const uint8_t isdAID[] = { 0xA0, 0x00, 0x00, 0x01, 0x51, 0x00, 0x00, 0x00 };

static ISD isd = {
	.lcState = cardReady,
	.privilege = privSD | privReset | privFinalApp,
	.key = NULL
};

cardLcs
isd_getLifeCycleState(void)
{
	return isd.lcState;
}

gpStatus
isd_setLifeCycleState(cardLcs lcs)
{
	if (isd.lcState == cardTerminated)
		return gpErrCardTerm;
	
	isd.lcState = lcs;
	return gpSuccess;
}

const uint8_t*
isd_getAID(void)
{
	if (isd.lcState >= cardLocked)
		return NULL;
	
	return &isdAID[0];
}

gpPrivilege
isd_getPrivilege(void)
{
	if (isd.lcState >= cardLocked)
		return privRFU;
	
	return isd.privilege;
}

gpStatus
isd_setPrivilege(gpPrivilege privilege)
{
	if (isd.lcState >= cardLocked)
		return gpErrCardTerm;
	
	isd.privilege |= privilege;
	return gpSuccess;
}

gpStatus
isd_resetPrivilege(gpPrivilege privilege)
{
	if (isd.lcState >= cardLocked)
		return gpErrCardTerm;

	isd.privilege &= ~privilege;
	return gpSuccess;
}

ISDKey*
isd_getKey(uint8_t _kvn, uint8_t _kid)
{
	if (isd.lcState >= cardLocked)
		return NULL;
	
	return isd.key;
}

gpStatus
isd_setKey(ISDKey* _key)
{
	if (isd.lcState >= cardLocked)
		return gpErrCardTerm;
	
	memcpy(isd.key, _key, sizeof(ISDKey));
	return gpSuccess;
}