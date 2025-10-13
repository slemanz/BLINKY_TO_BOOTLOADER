#include "core/cli.h"
#include "interface_comm.h"
#include <stdio.h>
#include <string.h>

#define CLI_BUFFER_SIZE         64

static Comm_Interface_t *_comm = NULL;
static command_t *_table = NULL;
static uint32_t _table_len = 0;

static char cli_buffer[CLI_BUFFER_SIZE];
static uint32_t cli_idx = 0;

void cli_setup(Comm_Interface_t *comm, command_t *table, uint32_t Len)
{
    if(table != NULL)
    {
        _comm = comm;
        _table = table;
        _table_len = Len;
    }
}

void cli_update(void)
{
    if(_comm == NULL) return;

    while(_comm->data_available())
    {
        uint8_t ch;
        _comm->receive(&ch, 1);
        _comm->send(&ch, 1);

        if(ch == '\r')
        {
            // nothing todo
        }else if(ch == '\n')
        {
             // command end
             cli_buffer[cli_idx] = '\0';
             // dispatch
             cli_dispatch(cli_buffer);
        }else if(cli_idx < CLI_BUFFER_SIZE)
        {
            cli_buffer[cli_idx++] = (char)ch;
        }
    }
}

void cli_dispatch(char *buffer)
{
    for (int i = 0; i < _table_len; i++) // Match command
    {
        if (strcmp(cli_buffer, _table[i].name) == 0)
        {
            _table[i].execute();
            break;
        }
    }
}

void cli_help(void)
{

}