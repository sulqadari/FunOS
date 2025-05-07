#ifndef FUNOS_ISO7816_SW_H
#define FUNOS_ISO7816_SW_H

/* See GlobalPlatform, clause 11.1.3 "General Error Conditions". */
#define SW_SUCCESS							0x9000
#define SW_BYTES_REMAIN						0x6100
#define SW_LOGICAL_CHANNEL_NOT_SUPPORTED	0x6881
#define SW_SECURITY_STATUS_NOT_SATISFIED	0x6982
#define SW_CONDITIONS_OF_USE_NOT_SATISFIED	0x6985
#define SW_INCORRECT_P1P2					0x6A86
#define SW_INVALID_INSTRUCTION_BYTE			0x6D00
#define SW_INVALID_CLASS_BYTE				0x6E00
#define SW_UNKNOW							0x6F00

/* ISO 7816-4, clause 5.3.3 */
#define SW_CHAIN_LAST_CMD_EXPECTED          0x6883
#define SW_CHAIN_NOT_SUPPORTED              0x6884

/* ISO 7816-4, 5.6 */
#define SW_MEMORY_FAILURE                   0x6581
#define SW_WORNG_CAPDU_FORMAT               0x6701
#define SW_WRONG_LC                         0x6702
#define SW_SM_NOT_SUPPORTED                 0x6882
#define SW_CMD_NOT_ALLOWED                  0x6986
#define SW_WRONG_DATA                       0x6A80
#define SW_CDATA_INCONSISTENT_WITH_P1P2     0x6A87
#define SW_REFERENCED_DATA_NOT_FOUND        0x6A88

#endif /* FUNOS_ISO7816_SW_H */