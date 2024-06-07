/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** load_teams
*/

#include "server.h"

teams_t *parse_team_data(const char *team_name,
    const char *team_description, const char *team_uuid_str)
{
    teams_t *new_team = malloc(sizeof(teams_t));

    uuid_parse(team_uuid_str, new_team->uuid);
    strncpy(new_team->name, team_name, MAX_NAME_LENGTH);
    strncpy(new_team->description, team_description, MAX_DESCRIPTION_LENGTH);
    strncpy(new_team->uuid_str, team_uuid_str, UUID_LENGTH);
    return new_team;
}

teams_t *load_team(const char *filename)
{
    FILE *file = NULL;
    char team_uuid_str[UUID_LENGTH] = {0};
    char team_name[MAX_NAME_LENGTH] = {0};
    char team_description[MAX_DESCRIPTION_LENGTH] = {0};
    teams_t *new_team = NULL;

    file = fopen(filename, "r");
    if (file == NULL) {
        return NULL;
    }
    while (fscanf(file,
        "team_name: %32s\nteam_description: %255s\nteam_uuid: %36s\n",
        team_name, team_description, team_uuid_str) == 3) {
        new_team = parse_team_data(team_name, team_description, team_uuid_str);
        if (new_team == NULL) {
            break;
        }
    }
    fclose(file);
    return new_team;
}

DIR *open_teams_directory(void)
{
    DIR *dir = opendir("teams");

    if (dir == NULL) {
        mkdir("teams", 0700);
        return NULL;
    }
    return dir;
}

void read_and_load_teams(server_t *server, DIR *dir)
{
    char filename[270] = {0};
    teams_t *new_team = NULL;

    for (struct dirent *ent = readdir(dir); ent != NULL; ent = readdir(dir)) {
        if (strstr(ent->d_name, ".txt") == NULL) {
            continue;
        }
        snprintf(filename, sizeof(filename), "teams/%s", ent->d_name);
        new_team = load_team(filename);
        if (new_team != NULL) {
            LIST_INIT(&new_team->channels);
            LIST_INSERT_HEAD(&server->teams, new_team, pointers);
        }
    }
    closedir(dir);
}

void load_teams(server_t *server)
{
    DIR *dir = open_teams_directory();

    if (dir == NULL) {
        return;
    }
    read_and_load_teams(server, dir);
}
