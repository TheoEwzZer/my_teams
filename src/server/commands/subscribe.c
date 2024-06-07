/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** subscribe
*/

#include "server.h"

bool is_user_in_team(teams_t *team, const clients_t *client)
{
    clients_t *current_client = NULL;

    LIST_FOREACH(current_client, &team->clients, pointers) {
        if (strcmp(current_client->uuid_str, client->uuid_str) == 0) {
            return true;
        }
    }
    return false;
}

void subscribe(server_t *server, clients_t *client)
{
    const char *team_uuid = client->arguments[0];
    teams_t *team = get_team_by_uuid(server, team_uuid);

    if (team == NULL) {
        dprintf(client->socket, "client_error_unknown_team\n%s\n", team_uuid);
        return;
    }
    if (is_user_in_team(team, client)) {
        return;
    }
    LIST_INSERT_HEAD(&team->clients, client, pointers);
    dprintf(client->socket, "client_print_subscribed\n%s\n%s\n",
        client->uuid_str, team_uuid);
    server_event_user_subscribed(team->uuid_str, client->uuid_str);
}
