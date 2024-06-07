/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** login
*/

#include "server.h"

void remove_existing_client(server_t *server, const char *user_uuid)
{
    clients_t *current = LIST_FIRST(&server->clients);
    clients_t *next = NULL;

    while (current != NULL) {
        next = LIST_NEXT(current, pointers);
        if ((current->socket == -1) && (current->uuid_str != NULL)
        && (strcmp(current->uuid_str, user_uuid) == 0)) {
            LIST_REMOVE(current, pointers);
            free(current);
            return;
        }
        current = next;
    }
}

void assign_client_values(server_t *server, clients_t *client,
    char *user_uuid, const char *user_name)
{
    clients_t *current_client = NULL;

    client->uuid_str = user_uuid;
    uuid_parse(user_uuid, client->uuid);
    strncpy(client->name, user_name, MAX_NAME_LENGTH);
    client->status = 1;
    server_event_user_logged_in(client->uuid_str);
    LIST_FOREACH(current_client, &server->clients, pointers) {
        if ((current_client->socket != -1) && (current_client->status == 1)) {
            dprintf(current_client->socket, "client_event_logged_in\n%s\n%s\n",
                user_uuid, user_name);
        }
    }
    load_messages_from_file(client);
    remove_existing_client(server, user_uuid);
}

void modify_file(const char *filename)
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
            snprintf(line, len, "user_status: 1\n");
        }
        strcat(new_content, line);
    }
    free(line);
    fseek(file, 0, SEEK_SET);
    fprintf(file, "%s", new_content);
    fclose(file);
}

void login(server_t *server, clients_t *client)
{
    char *user_name = client->arguments[0];
    char *user_uuid = client->arguments[1];
    char filename[55] = {0};
    FILE *file = NULL;

    snprintf(filename, sizeof(filename), "users_server/%s.txt", user_uuid);
    if (is_file_exists(filename) == false) {
        server_event_user_created(user_uuid, user_name);
        file = fopen(filename, "a+");
        if (file == NULL) {
            return;
        }
        fprintf(file, "user_name: %s\nuser_uuid: %s\n", user_name, user_uuid);
        fprintf(file, "user_status: 1\n");
        fclose(file);
    } else {
        modify_file(filename);
    }
    assign_client_values(server, client, user_uuid, user_name);
}
