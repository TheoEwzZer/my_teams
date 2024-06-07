/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** load_channels
*/

#include "server.h"

channel_t *create_new_channel2(char *name, char *description, char *uuid_str)
{
    channel_t *new_channel = malloc(sizeof(channel_t));

    uuid_parse(uuid_str, new_channel->uuid);
    strncpy(new_channel->name, name, MAX_NAME_LENGTH);
    strncpy(new_channel->description, description, MAX_DESCRIPTION_LENGTH);
    strncpy(new_channel->uuid_str, uuid_str, UUID_LENGTH);
    return new_channel;
}

void load_channel(server_t *server, const char *filename)
{
    FILE *file = fopen(filename, "r");
    teams_t *team = NULL;
    char team_uuid[UUID_LENGTH] = {0};
    char channel_uuid[UUID_LENGTH] = {0};
    char name[MAX_NAME_LENGTH] = {0};
    char description[MAX_DESCRIPTION_LENGTH] = {0};
    channel_t *new_channel = NULL;

    if (file != NULL) {
        fscanf(file, "team_uuid: %36s\nchannel_name: %32s\n"
        "channel_description: %255s\nchannel_uuid: %36s",
        team_uuid, name, description, channel_uuid);
        team = get_team_by_uuid(server, team_uuid);
        if (team != NULL) {
            new_channel = create_new_channel2(name, description, channel_uuid);
            LIST_INSERT_HEAD(&team->channels, new_channel, pointers);
        }
    }
    fclose(file);
}

void load_channels(server_t *server)
{
    DIR *dir = opendir("channels");
    char filename[270] = {0};

    if (dir == NULL) {
        return;
    }
    for (struct dirent *ent = readdir(dir); ent != NULL; ent = readdir(dir)) {
        if (strstr(ent->d_name, ".txt") == NULL) {
            continue;
        }
        snprintf(filename, sizeof(filename), "channels/%s", ent->d_name);
        load_channel(server, filename);
    }
    closedir(dir);
}
