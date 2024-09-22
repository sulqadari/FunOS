#ifndef FUNOS_GPREGISTRY_H
#define FUNOS_GPREGISTRY_H

#include <stdint.h>
#include "commonTypes.h"

#define AID_LENGTH 16

typedef struct {
	execLoadLcs lcState;
	uint8_t AID[AID_LENGTH];
	uint8_t aidLength;
} ExecLoad;

typedef struct {
	execLoadLcs lcState;
	uint8_t AID[AID_LENGTH];
	uint8_t aidLength;
} ExecModule;

typedef struct {
	appLcs lcState;
	gpPrivilege privilege;
	uint8_t AID[AID_LENGTH];
	uint8_t aidLength;
} Application;

typedef struct {

} GpRegistry;

#endif /* FUNOS_GPREGISTRY_H*/