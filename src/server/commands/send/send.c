/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** logout
*/

#include "server.h"

void add_message_to_client(clients_t *client, message_t *message_info)
{
    message_t *new_message = malloc(sizeof(message_t));

    if (new_message == NULL) {
        return;
    }
    uuid_parse(message_info->contact_uuid_str, new_message->contact_uuid);
    new_message->is_sender = message_info->is_sender;
    new_message->is_seen = message_info->is_seen;
    new_message->timestamp = message_info->timestamp;
    strncpy(new_message->message_body,
        message_info->message_body, MAX_BODY_LENGTH);
    strncpy(new_message->contact_uuid_str,
        message_info->contact_uuid_str, UUID_LENGTH);
    TAILQ_INSERT_HEAD(&client->messages, new_message, pointers);
}

message_t *prepare_message(clients_t *client)
{
    const char *sender_uuid_str = client->arguments[0];
    const char *receiver_uuid_str = client->arguments[1];
    const char *message_body = client->arguments[2];
    uuid_t sender_uuid = {0};
    uuid_t receiver_uuid = {0};
    time_t timestamp = time(NULL);
    message_t *message_info = malloc(sizeof(message_t));

    if (message_info == NULL) {
        return NULL;
    }
    strncpy(message_info->contact_uuid_str, receiver_uuid_str,
        sizeof(message_info->contact_uuid_str));
    strncpy(message_info->message_body,
        message_body, sizeof(message_info->message_body));
    message_info->is_sender = 1;
    message_info->timestamp = timestamp;
    uuid_parse(sender_uuid_str, sender_uuid);
    uuid_parse(receiver_uuid_str, receiver_uuid);
    return message_info;
}

clients_t *find_sender(server_t *server, clients_t *client)
{
    const char *sender_uuid_str = client->arguments[0];
    uuid_t sender_uuid = {0};
    clients_t *sender = NULL;

    uuid_parse(sender_uuid_str, sender_uuid);
    sender = find_client_by_uuid(server, sender_uuid);
    return sender;
}

clients_t *find_receiver(server_t *server, clients_t *client)
{
    const char *receiver_uuid_str = client->arguments[1];
    uuid_t receiver_uuid = {0};
    clients_t *receiver = NULL;

    uuid_parse(receiver_uuid_str, receiver_uuid);
    receiver = find_client_by_uuid(server, receiver_uuid);
    return receiver;
}

void send_message(server_t *server, clients_t *client)
{
    message_t *message_info = prepare_message(client);
    clients_t *sender = NULL;
    clients_t *receiver = NULL;
    const char *sender_uuid_str = client->arguments[0];
    const char *receiver_uuid_str = client->arguments[1];

    if (message_info == NULL) {
        return;
    }
    sender = find_sender(server, client);
    receiver = find_receiver(server, client);
    if ((sender != NULL) && (receiver == NULL)) {
        dprintf(sender->socket,
            "client_error_unknown_user\n%s\n", receiver_uuid_str);
    } else if (sender != NULL) {
        handle_message_sending(sender, receiver, message_info);
        save_messages_to_file(sender_uuid_str,
            receiver_uuid_str, message_info);
    }
    free(message_info);
}
