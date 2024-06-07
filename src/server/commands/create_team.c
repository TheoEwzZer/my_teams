/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** users
*/

#include "server.h"

bool is_team_exists(server_t *server, const char *team_name)
{
    teams_t *current_team = NULL;

    LIST_FOREACH(current_team, &server->teams, pointers) {
        if (strcmp(current_team->name, team_name) == 0) {
            return true;
        }
    }
    return false;
}

void write_team_to_file(const char *team_name,
    const char *team_description, char *team_uuid_str)
{
    FILE *file = NULL;
    char filename[269] = {0};

    snprintf(filename, sizeof(filename), "teams/%s.txt", team_uuid_str);
    file = fopen(filename, "w");
    if (file == NULL) {
        return;
    }
    fprintf(file, "team_name: %s\n", team_name);
    fprintf(file, "team_description: %s\n", team_description);
    fprintf(file, "team_uuid: %s\n", team_uuid_str);
    fclose(file);
}

void add_team_in_struct(server_t *server, const char *team_name,
    const char *team_description, const char *team_uuid_str)
{
    teams_t *new_team = malloc(sizeof(teams_t));

    uuid_parse(team_uuid_str, new_team->uuid);
    strncpy(new_team->name, team_name, MAX_NAME_LENGTH);
    strncpy(new_team->description, team_description, MAX_DESCRIPTION_LENGTH);
    strncpy(new_team->uuid_str, team_uuid_str, UUID_LENGTH);
    LIST_INIT(&new_team->channels);
    LIST_INSERT_HEAD(&server->teams, new_team, pointers);
}

void create_new_team(server_t *server, const clients_t *client)
{
    char team_uuid_str[UUID_LENGTH] = {0};
    const char *team_name = client->arguments[0];
    const char *team_description = client->arguments[1];
    uuid_t team_uuid = {0};
    clients_t *current_client = NULL;

    uuid_generate(team_uuid);
    uuid_unparse(team_uuid, team_uuid_str);
    write_team_to_file(team_name, team_description, team_uuid_str);
    add_team_in_struct(server, team_name, team_description, team_uuid_str);
    server_event_team_created(team_uuid_str, team_name, client->uuid_str);
    LIST_FOREACH(current_client, &server->clients, pointers) {
        if ((current_client->socket != -1) && (current_client->status == 1)) {
            dprintf(current_client->socket,
                "client_event_team_created\n%s\n%s\n%s\n",
                team_uuid_str, team_name, team_description);
        }
    }
    dprintf(client->socket, "client_print_team_created\n%s\n%s\n%s\n",
        team_uuid_str, team_name, team_description);
}

void create_team(server_t *server, clients_t *client)
{
    DIR *dir = NULL;
    const char *team_name = client->arguments[0];

    if (strlen(team_name) > MAX_NAME_LENGTH) {
        return;
    }
    if (strlen(client->arguments[1]) > MAX_DESCRIPTION_LENGTH) {
        return;
    }
    create_directory_if_not_exists("teams");
    dir = opendir("teams");
    if (is_team_exists(server, team_name)) {
        dprintf(client->socket, "client_error_already_exist\n");
    } else {
        create_new_team(server, client);
    }
    closedir(dir);
}
