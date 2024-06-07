/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** main
*/

#include "server.h"

void print_server_usage(void)
{
    printf("USAGE: ./myteams_server port\n");
    printf("\tport is the port number on which the server socket listens.\n");
}

void exit_error(const char *str)
{
    dprintf(1, "%s: %s\n", str, strerror(errno));
    exit(84);
}

int main(int argc, char **argv)
{
    char *endptr = NULL;
    long port_num = 0;

    if ((argc == 2) && (strcmp(argv[1], "-help") == 0)) {
        print_server_usage();
        return 0;
    }
    if (argc != 2) {
        printf("Invalid arguments. Use -help for usage instructions.\n");
        return 84;
    }
    port_num = strtol(argv[1], &endptr, 10);
    if ((*endptr != '\0') || (port_num < 1) || (port_num > MAX_PORT)) {
        printf("Invalid port given. It has to be a value from 1 to 65535.\n");
        return 84;
    }
    return server((uint16_t)port_num);
}
