#ifndef FUNOS_GPAPI_H
#define FUNOS_GPAPI_H

void gpapi_cardHolderVerification(void);
void gpapi_cardHolderPersonalization(void);
void gpapi_securityService(void);
void gpapi_lockCard(void);

/**
 * Updates the card's life cycle.
 */
void gpapi_clcUpdate(void);

#endif /* FUNOS_GPAPI_H */