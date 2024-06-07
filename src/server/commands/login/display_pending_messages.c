/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** login
*/

#include "server.h"

FILE *prepare_read_file(clients_t *client,
    char *filename, size_t filename_size)
{
    FILE *file = NULL;

    snprintf(filename, filename_size, "messages/%s.txt", client->uuid_str);
    file = fopen(filename, "r");
    return file;
}

FILE *prepare_temp_file(clients_t *client, char *tmp, size_t tmp_size)
{
    FILE *tmp_file = NULL;

    snprintf(tmp, tmp_size, "messages/%s_tmp.txt", client->uuid_str);
    tmp_file = fopen(tmp, "w");
    return tmp_file;
}

void display_pending_messages(clients_t *client)
{
    char filename[55] = {0};
    char tmp[55] = {0};
    FILE *file = NULL;
    FILE *tmp_file = NULL;

    file = prepare_read_file(client, filename, sizeof(filename));
    if (file == NULL) {
        return;
    }
    tmp_file = prepare_temp_file(client, tmp, sizeof(tmp));
    if (tmp_file == NULL) {
        fclose(file);
        return;
    }
    read_messages(client, file, tmp_file);
    fclose(file);
    fclose(tmp_file);
    remove(filename);
    rename(tmp, filename);
}
