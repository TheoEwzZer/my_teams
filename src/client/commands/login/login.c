/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** login
*/

#include "client.h"

void create_directory_if_not_exists(const char *dir_name)
{
    DIR *dir = opendir(dir_name);

    if (dir == NULL) {
        if (mkdir(dir_name, 0700) == -1) {
            return;
        }
    } else {
        closedir(dir);
    }
}

void parse_file_content(FILE *file, char **user_uuid)
{
    char *line = NULL;
    char uuid[UUID_LENGTH] = {0};
    size_t len = 0;

    rewind(file);
    while ((getline(&line, &len, file)) != -1) {
        if (sscanf(line, "user_uuid: %36s", uuid) == 1) {
            free(*user_uuid);
            *user_uuid = strdup(uuid);
        }
    }
    free(line);
}

void create_new_user(client_t *client, char *user_uuid, char *user_name)
{
    FILE *file = NULL;
    uuid_t uuid = {0};
    char filename[269] = {0};

    user_uuid = calloc(UUID_LENGTH, sizeof(char));
    uuid_generate(uuid);
    uuid_unparse(uuid, user_uuid);
    snprintf(filename, sizeof(filename), "users_client/%s.txt", user_uuid);
    file = fopen(filename, "a+");
    if (file == NULL) {
        free(user_uuid);
        return;
    }
    fprintf(file, "user_name: %s\nuser_uuid: %s\n", user_name, user_uuid);
    dprintf(client->socket, "/login/%s/%s/\n", user_name, user_uuid);
    fclose(file);
    client->status = 1;
    client->uuid_str = user_uuid;
    strncpy(client->name, user_name, MAX_NAME_LENGTH);
    uuid_parse(user_uuid, client->uuid);
}

void login(client_t *client)
{
    DIR *dir = NULL;
    char *user_uuid = NULL;
    char *user_name = client->arguments[0];
    bool user_exists = false;

    if (strlen(user_name) > MAX_NAME_LENGTH) {
        return;
    }
    create_directory_if_not_exists("users_client");
    dir = opendir("users_client");
    user_exists = find_user_file(client, dir, user_uuid, user_name);
    if (user_exists == false) {
        create_new_user(client, user_uuid, user_name);
    }
    closedir(dir);
}
