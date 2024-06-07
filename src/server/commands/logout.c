/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** logout
*/

#include "server.h"

void modify_file_logout(const char *filename)
{
    FILE *file = NULL;
    char *line = NULL;
    size_t len = 0;
    char new_content[128] = {0};

    file = fopen(filename, "r+");
    if (file == NULL) {
        return;
    }
    while (getline(&line, &len, file) != -1) {
        if (strstr(line, "user_status:") != NULL) {
            snprintf(line, len, "user_status: 0\n");
        }
        strcat(new_content, line);
    }
    free(line);
    fseek(file, 0, SEEK_SET);
    fprintf(file, "%s", new_content);
    fclose(file);
}

void logout(server_t *server, clients_t *client)
{
    char filename[55] = {0};
    clients_t *current_client = NULL;

    (void)server;
    snprintf(filename, sizeof(filename),
        "users_server/%s.txt", client->uuid_str);
    modify_file_logout(filename);
    LIST_FOREACH(current_client, &server->clients, pointers) {
        if ((current_client->socket != -1) && (current_client->status == 1)) {
            dprintf(
                current_client->socket,
                "client_event_logged_out\n%s\n%s\n",
                client->uuid_str, client->name
            );
        }
    }
}
