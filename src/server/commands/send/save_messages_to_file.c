/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** logout
*/

#include "server.h"

void save_new_message_to_file(const char *client_uuid_str,
    message_t *message_info)
{
    FILE *file = NULL;
    char filename[55] = {0};
    int is_seen = message_info->is_sender;

    snprintf(filename, sizeof(filename),
        "messages/%s.txt", client_uuid_str);
    file = fopen(filename, "a");
    if (file == NULL) {
        return;
    }
    fprintf(file, "%s/%d/%d", message_info->contact_uuid_str,
        message_info->is_sender, is_seen);
    fprintf(file, "/%ld/%s\n", message_info->timestamp,
        message_info->message_body);
    fclose(file);
}

void save_messages_to_file(const char *sender_uuid_str,
    const char *receiver_uuid_str, message_t *message_info)
{
    create_directory_if_not_exists("messages");
    message_info->is_sender = 1;
    save_new_message_to_file(sender_uuid_str, message_info);
    strncpy(message_info->contact_uuid_str,
        sender_uuid_str, sizeof(message_info->contact_uuid_str));
    message_info->is_sender = 0;
    save_new_message_to_file(receiver_uuid_str, message_info);
}

void handle_message_sending(clients_t *sender, clients_t *receiver,
    message_t *message_info)
{
    server_event_private_message_sended(
        sender->uuid_str, receiver->uuid_str, message_info->message_body
    );
    message_info->is_seen = 1;
    add_message_to_client(sender, message_info);
    message_info->is_sender = 0;
    message_info->is_seen = 0;
    add_message_to_client(receiver, message_info);
}
