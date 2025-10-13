#ifndef INC_CLI_H_
#define INC_CLI_H_

#include <stdint.h>
#include "interface_comm.h"

// structure to hold command info
typedef struct
{
    const char *name;
    void (*execute)(void);
    const char *help;
}command_t;

void cli_setup(Comm_Interface_t *comm, command_t *table, uint32_t Len);
void cli_update(void);
void cli_dispatch(char *buffer);

void cli_help(void);

#endif /* INC_CLI_H_ */