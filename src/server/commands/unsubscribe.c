/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** subscribe
*/

#include "server.h"

void unsubscribe(server_t *server, clients_t *client)
{
    const char *team_uuid = client->arguments[0];
    teams_t *team = get_team_by_uuid(server, team_uuid);

    if (team == NULL) {
        dprintf(client->socket, "client_error_unknown_team\n%s\n", team_uuid);
        return;
    }
    LIST_FOREACH(client, &team->clients, pointers) {
        if (strcmp(client->uuid_str, client->uuid_str) == 0) {
            LIST_REMOVE(client, pointers);
            dprintf(client->socket, "client_print_unsubscribed\n%s\n%s\n",
                client->uuid_str, team_uuid);
            server_event_user_unsubscribed(team->uuid_str, client->uuid_str);
            return;
        }
    }
}
