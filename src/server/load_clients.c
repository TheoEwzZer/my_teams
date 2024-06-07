/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** load_clients
*/

#include "server.h"

clients_t *parse_client_data(const char *uuid_str,
    const char *name, const int status)
{
    clients_t *new_client = malloc(sizeof(clients_t));

    uuid_parse(uuid_str, new_client->uuid);
    strncpy(new_client->name, name, MAX_NAME_LENGTH);
    new_client->status = status;
    new_client->socket = -1;
    new_client->uuid_str = strdup(uuid_str);
    server_event_user_loaded(uuid_str, name);
    return new_client;
}

clients_t *load_client(const char *filename)
{
    FILE *file = NULL;
    char uuid_str[UUID_LENGTH] = {0};
    char name[MAX_NAME_LENGTH] = {0};
    int status = 0;
    clients_t *new_client = NULL;

    file = fopen(filename, "r");
    if (file == NULL) {
        return NULL;
    }
    while (fscanf(file, "user_name: %32s\nuser_uuid: %36s\nuser_status: %d\n",
        name, uuid_str, &status) == 3) {
        new_client = parse_client_data(uuid_str, name, status);
        if (new_client == NULL) {
            break;
        }
    }
    fclose(file);
    return new_client;
}

DIR *open_clients_directory(void)
{
    DIR *dir = opendir("users_server");

    if (dir == NULL) {
        mkdir("users_server", 0700);
        return NULL;
    }
    return dir;
}

void read_and_load_clients(server_t *server, DIR *dir)
{
    char filename[270] = {0};
    clients_t *new_client = NULL;

    for (struct dirent *ent = readdir(dir); ent != NULL; ent = readdir(dir)) {
        if (strstr(ent->d_name, ".txt") == NULL) {
            continue;
        }
        snprintf(filename, sizeof(filename), "users_server/%s", ent->d_name);
        new_client = load_client(filename);
        if (new_client != NULL) {
            LIST_INSERT_HEAD(&server->clients, new_client, pointers);
            TAILQ_INIT(&new_client->messages);
            load_messages_from_file(new_client);
        }
    }
    closedir(dir);
}

void load_clients(server_t *server)
{
    DIR *dir = open_clients_directory();

    if (dir == NULL) {
        return;
    }
    read_and_load_clients(server, dir);
}
