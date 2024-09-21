#include "isd.h"
#include "statuses.h"

/* Issuer Identification Number.
 * May be used to associate the card with a specific Card Management System.
 * See clasue 7.4.1.1 */
static uint8_t* IIN;

/* Card Image Number.
 * May be used by Card Management System to identify a card within its card base.
 * See clause 7.4.1.2 */
static uint8_t* CIN;

/* An information required by Card Management Systems before they can start to interact
 * with it.
 * See clause 7.4.1.3 and appendix 'H'. */
static uint8_t* cardRecognitionData;

/* Optional data about cipher suites actually supported by the card.
 * See 7.4.1.4 and appendix 'H.4'. */
static uint8_t* cardCapabilityInfo;

/* ISD AID.
 * See Appendix 'H'.*/
static uint8_t isdAID[] = { 0xA0, 0x00, 0x00, 0x01, 0x51, 0x00, 0x00, 0x00 };

Status
isd_getAID(uint8_t** aidPtr)
{
	*aidPtr = &isdAID[0];
	return gpSuccess;
}