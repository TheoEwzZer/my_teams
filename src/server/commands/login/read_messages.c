/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** login
*/

#include "server.h"

void update_messages(clients_t *client, const message_t *message_ref,
    int is_seen, int is_sender)
{
    message_t *message = NULL;

    TAILQ_FOREACH(message, &client->messages, pointers) {
        if (strcmp(message->contact_uuid_str,
            message_ref->contact_uuid_str) != 0) {
            continue;
        }
        if (strcmp(message->message_body, message_ref->message_body) != 0) {
            continue;
        }
        if (message->timestamp != message_ref->timestamp) {
            continue;
        }
        if ((is_seen == 1) || (is_sender == 1)) {
            continue;
        }
        message->is_seen = 1;
    }
}

void process_line(clients_t *client, const char *line,
    FILE *tmp_file, message_t *message_ref)
{
    char contact_uuid_str[UUID_LENGTH] = {0};
    char message_body[MAX_BODY_LENGTH] = {0};
    int is_seen = 0;
    int is_sender = 0;
    time_t timestamp = 0;

    sscanf(line, "%[^/]/%d/%d/%ld/%[^\n]", contact_uuid_str,
        &is_sender, &is_seen, &timestamp, message_body);
    if (is_seen == 0) {
        dprintf(client->socket,
            "client_event_private_message_received\n%s\n%s\n",
            contact_uuid_str, message_body);
    }
    fprintf(tmp_file, "%s/%d/%d/%ld/%s\n", contact_uuid_str,
        is_sender, 1, timestamp, message_body);
    strcpy(message_ref->contact_uuid_str, contact_uuid_str);
    strcpy(message_ref->message_body, message_body);
    message_ref->timestamp = timestamp;
    update_messages(client, message_ref, is_seen, is_sender);
}

void read_messages(clients_t *client, FILE *file, FILE *tmp_file)
{
    char *line = NULL;
    size_t len = 0;
    message_t *message_ref = malloc(sizeof(message_t));

    while (getline(&line, &len, file) != -1) {
        process_line(client, line, tmp_file, message_ref);
    }
    free(line);
    free(message_ref);
}
