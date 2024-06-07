/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** main
*/

#include "client.h"

void print_client_usage(void)
{
    printf("USAGE: ./myteams_cli ip port\n");
    printf("\tip is the server ip address on which the server socket listens");
    printf("\n\tport is the port number on which the server socket listens\n");
}

int main(int argc, char **argv)
{
    char *endptr = NULL;
    long port_num = 0;

    if ((argc == 2) && (strcmp(argv[1], "-help") == 0)) {
        print_client_usage();
        return 0;
    }
    if (argc != 3) {
        printf("Invalid arguments. Use -help for usage instructions.\n");
        return 84;
    }
    port_num = strtol(argv[2], &endptr, 10);
    if ((*endptr != '\0') || (port_num < 1) || (port_num > MAX_PORT)) {
        printf("Invalid port given. It has to be a value from 1 to 65535.\n");
        return 84;
    }
    return client(argv[1], (uint16_t)port_num);
}
