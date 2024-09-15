#include "isd.h"

/* Issuer Identification Number.
 * May be used to associate the card with a specific Card Management System.
 * See clasue 7.4.1.1 */
static uint8_t IIN[8];

/* Card Image Number.
 * May be used by Card Management System to identify a card within its card base.
 * See clause 7.4.1.2 */
static uint8_t CIN[8];

/* An information required by Card Management Systems before they can start to interact
 * with it.
 * See clause 7.4.1.3 and appendix 'H'. */
static uint8_t cardRecognitionData[8];

/* Optional data about cipher suites actually supported by the card.
 * See 7.4.1.4 and appendix 'H.4'. */
static uint8_t cardCapabilityInfo[8];