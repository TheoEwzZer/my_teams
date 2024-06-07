/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** utils
*/

#include "server.h"

bool is_file_exists(const char *filename)
{
    FILE *file = fopen(filename, "r");

    if (file != NULL) {
        fclose(file);
        return true;
    }
    return false;
}

void create_directory_if_not_exists(const char *dir_name)
{
    DIR *dir = opendir(dir_name);

    if (dir == NULL) {
        if (mkdir(dir_name, 0700) == -1) {
            return;
        }
    } else {
        closedir(dir);
    }
}

bool is_team_exists_uuid(server_t *server, const char *team_uuid)
{
    teams_t *current_team = NULL;

    LIST_FOREACH(current_team, &server->teams, pointers) {
        if (strcmp(current_team->uuid_str, team_uuid) == 0) {
            return true;
        }
    }
    return false;
}

bool is_channel_exists(teams_t *team, const char *channel_name)
{
    channel_t *current_channel = NULL;

    LIST_FOREACH(current_channel, &team->channels, pointers) {
        if (strcmp(current_channel->name, channel_name) == 0) {
            return true;
        }
    }
    return false;
}
