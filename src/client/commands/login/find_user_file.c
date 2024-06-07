/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** find_user_file
*/

#include "client.h"

bool process_user_file(client_t *client, FILE *file,
    char *user_uuid, char *user_name)
{
    char file_user_name[55] = {0};

    while (fscanf(file, "user_name: %32s\n", file_user_name) == 1) {
        if (strcmp(file_user_name, user_name) == 0) {
            parse_file_content(file, &user_uuid);
            dprintf(client->socket, "/login/%s/%s/\n", user_name, user_uuid);
            fclose(file);
            client->status = 1;
            client->uuid_str = user_uuid;
            strncpy(client->name, user_name, MAX_NAME_LENGTH);
            uuid_parse(user_uuid, client->uuid);
            return true;
        }
    }
    fclose(file);
    return false;
}

bool find_user_file(client_t *client, DIR *dir,
    char *user_uuid, char *user_name)
{
    FILE *file = NULL;
    char filename[269] = {0};

    for (struct dirent *ent = readdir(dir); ent != NULL; ent = readdir(dir)) {
        if (strstr(ent->d_name, ".txt") == NULL) {
            continue;
        }
        snprintf(filename, sizeof(filename), "users_client/%s", ent->d_name);
        file = fopen(filename, "r");
        if (file == NULL) {
            continue;
        }
        if (process_user_file(client, file, user_uuid, user_name)) {
            return true;
        }
    }
    return false;
}
