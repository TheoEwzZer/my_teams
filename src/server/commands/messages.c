/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** logout
*/

#include "server.h"

void print_messages(clients_t *client, const char *contact_uuid,
    const char *user_uuid)
{
    char sender_uuid[UUID_LENGTH] = {0};
    message_t *message = NULL;
    struct timespec ts = {.tv_sec = 0, .tv_nsec = 100000000L};

    TAILQ_FOREACH_REVERSE(message, &client->messages, message_list, pointers) {
        if (strcmp(message->contact_uuid_str, contact_uuid) != 0) {
            continue;
        }
        if (message->is_sender == 1) {
            strcpy(sender_uuid, user_uuid);
        } else {
            strcpy(sender_uuid, contact_uuid);
        }
        dprintf(client->socket, "client_private_message_print\n%s\n%ld\n%s\n",
            sender_uuid, message->timestamp, message->message_body);
        nanosleep(&ts, NULL);
    }
}

void messages(server_t *server, clients_t *client)
{
    const char *contact_uuid = client->arguments[1];
    const char *user_uuid = client->arguments[0];
    uuid_t uuid = {0};

    (void)server;
    uuid_parse(contact_uuid, uuid);
    if (find_client_by_uuid(server, uuid) == NULL) {
        dprintf(client->socket,
            "client_error_unknown_user\n%s\n", contact_uuid);
        return;
    }
    print_messages(client, contact_uuid, user_uuid);
}
