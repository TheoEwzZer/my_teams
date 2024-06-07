/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** create_channel
*/

#include "server.h"

void write_channel_to_file(clients_t *client, char *channel_uuid_str)
{
    FILE *file = NULL;
    char filename[269] = {0};
    const char *channel_name = client->arguments[0];
    const char *channel_description = client->arguments[1];
    const char *team_uuid = client->arguments[2];

    snprintf(filename, sizeof(filename), "channels/%s.txt", channel_uuid_str);
    file = fopen(filename, "w");
    if (file == NULL) {
        return;
    }
    fprintf(file, "team_uuid: %s\n", team_uuid);
    fprintf(file, "channel_name: %s\n", channel_name);
    fprintf(file, "channel_description: %s\n", channel_description);
    fprintf(file, "channel_uuid: %s\n", channel_uuid_str);
    fclose(file);
}

void add_channel_in_struct(teams_t *team, clients_t *client,
    const char *uuid_str)
{
    channel_t *new_channel = malloc(sizeof(teams_t));
    const char *name = client->arguments[0];
    const char *description = client->arguments[1];

    uuid_parse(uuid_str, new_channel->uuid);
    strncpy(new_channel->name, name, MAX_NAME_LENGTH);
    strncpy(new_channel->description, description, MAX_DESCRIPTION_LENGTH);
    strncpy(new_channel->uuid_str, uuid_str, UUID_LENGTH);
    LIST_INSERT_HEAD(&team->channels, new_channel, pointers);
}

void create_new_channel(teams_t *team, clients_t *client)
{
    char channel_uuid_str[UUID_LENGTH] = {0};
    const char *channel_name = client->arguments[0];
    const char *channel_description = client->arguments[1];
    const char *team_uuid = client->arguments[2];
    uuid_t channel_uuid = {0};
    clients_t *tmp = NULL;

    uuid_generate(channel_uuid);
    uuid_unparse(channel_uuid, channel_uuid_str);
    write_channel_to_file(client, channel_uuid_str);
    add_channel_in_struct(team, client, channel_uuid_str);
    server_event_channel_created(team_uuid, channel_name, client->uuid_str);
    LIST_FOREACH(tmp, &team->clients, pointers) {
        if ((tmp->socket != -1) && (tmp->status == 1)) {
            dprintf(tmp->socket, "client_event_channel_created\n%s\n%s\n%s\n",
                channel_uuid_str, channel_name, channel_description);
        }
    }
    dprintf(client->socket, "client_print_channel_created\n%s\n%s\n%s\n",
        channel_uuid_str, channel_name, channel_description);
}

void create_channel(server_t *server, clients_t *client)
{
    DIR *dir = NULL;
    const char *channel_name = client->arguments[0];
    const char *channel_description = client->arguments[1];
    const char *team_uuid = client->arguments[2];
    teams_t *team = get_team_by_uuid(server, team_uuid);

    if ((strlen(channel_name) > 32) || (strlen(channel_description) > 255)) {
        return;
    }
    create_directory_if_not_exists("channels");
    dir = opendir("channels");
    if (!is_team_exists_uuid(server, team_uuid)) {
        dprintf(client->socket, "client_error_unknown_team\n%s\n", team_uuid);
    } else if (is_channel_exists(team, channel_name) == true) {
        dprintf(client->socket, "client_error_already_exist\n");
    } else {
        create_new_channel(team, client);
    }
    closedir(dir);
}
