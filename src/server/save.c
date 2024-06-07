/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** save
*/

#include "server.h"

void save_message_to_file(const char *client_uuid_str,
    message_t *message_info)
{
    FILE *file = NULL;
    char filename[55] = {0};

    snprintf(filename, sizeof(filename),
        "messages/%s.txt", client_uuid_str);
    file = fopen(filename, "a");
    if (file == NULL) {
        return;
    }
    fprintf(file, "%s/%d/%d", message_info->contact_uuid_str,
        message_info->is_sender, message_info->is_seen);
    fprintf(file, "/%ld/%s\n", message_info->timestamp,
        message_info->message_body);
    fclose(file);
}

void save_client_messages(clients_t *client)
{
    message_t *current = NULL;
    char filename[50] = {0};

    snprintf(filename, sizeof(filename), "messages/%s.txt", client->uuid_str);
    remove(filename);
    TAILQ_FOREACH_REVERSE(current, &client->messages, message_list, pointers) {
        save_message_to_file(client->uuid_str, current);
    }
}

void save(server_t *server)
{
    clients_t *current = NULL;
    FILE *file = NULL;
    char client_filename[55] = {0};

    create_directory_if_not_exists("users_server");
    create_directory_if_not_exists("messages");
    LIST_FOREACH(current, &server->clients, pointers) {
        snprintf(client_filename, sizeof(client_filename),
            "users_server/%s.txt", current->uuid_str);
        file = fopen(client_filename, "w+");
        if (file == NULL) {
            continue;
        }
        fprintf(file, "user_name: %s\nuser_uuid: %s\nuser_status: %d\n",
            current->name, current->uuid_str, current->status);
        fclose(file);
        save_client_messages(current);
    }
}
