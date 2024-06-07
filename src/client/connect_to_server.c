/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** connect_to_server
*/

#include "client.h"

int connect_to_server(const char *ip_address, long port_num)
{
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_address = {0};

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons((uint16_t)port_num);
    if (inet_pton(AF_INET, ip_address, &server_address.sin_addr) <= 0) {
        close(client_socket);
        printf("Invalid address/Address not supported\n");
        return -1;
    }
    if (connect(client_socket, (struct sockaddr *)&server_address,
        sizeof(server_address)) == -1) {
        close(client_socket);
        printf("Connection failed\n");
        return -1;
    }
    return client_socket;
}
