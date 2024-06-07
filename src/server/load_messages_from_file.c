/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** load_clients
*/

#include "server.h"

FILE *open_message_file(clients_t *client,
    char *filename, size_t filename_size)
{
    FILE *file = NULL;

    snprintf(filename, filename_size, "messages/%s.txt", client->uuid_str);
    file = fopen(filename, "r");
    return file;
}

void process_and_load_message(clients_t *client, const char *line,
    message_t *message_info)
{
    char contact_uuid_str[UUID_LENGTH] = {0};
    int is_sender = 0;
    int is_seen = 0;
    char message_body[MAX_BODY_LENGTH] = {0};
    time_t timestamp = 0;

    sscanf(line, "%[^/]/%d/%d/%ld/%[^\n]", contact_uuid_str,
        &is_sender, &is_seen, &timestamp, message_body);
    uuid_parse(contact_uuid_str, message_info->contact_uuid);
    message_info->is_sender = is_sender;
    message_info->is_seen = is_seen;
    message_info->timestamp = timestamp;
    strncpy(message_info->message_body, message_body, MAX_BODY_LENGTH);
    strncpy(message_info->contact_uuid_str, contact_uuid_str, UUID_LENGTH);
    add_message_to_client(client, message_info);
}

void read_and_load_messages(clients_t *client, FILE *file)
{
    char *line = NULL;
    size_t len = 0;
    message_t *message_info = malloc(sizeof(message_t));

    while (getline(&line, &len, file) != -1) {
        process_and_load_message(client, line, message_info);
    }
    free(line);
    free(message_info);
}

void load_messages_from_file(clients_t *client)
{
    char filename[55] = {0};
    FILE *file = open_message_file(client, filename, sizeof(filename));

    if (file == NULL) {
        return;
    }
    read_and_load_messages(client, file);
    fclose(file);
}
