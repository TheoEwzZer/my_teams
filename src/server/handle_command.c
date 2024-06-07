/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** handle_command
*/

#include "server.h"

static const command_t commands[14] = {
    {"/login/([^/\n]+)/([^/\n]+)", &login},
    {"/logout/([^/\n]+)/([^/\n]+)", &logout},
    {"/send/([^/\n]+)/([^/\n]+)/([^/\n]+)", &send_message},
    {"/user/([^/\n]+)", &user},
    {"/users", &users},
    {"/messages/([^/\n]+)/([^/\n]+)", &messages},
    {"/create_team/([^/\n]+)/([^/\n]+)", &create_team},
    {"/display_team/([^/\n]+)", &display_team},
    {"/list_teams", &list_teams},
    {"/create_channel/([^/\n]+)/([^/\n]+)/([^/\n]+)", &create_channel},
    {"/subscribe/([^/\n]+)", &subscribe},
    {"/unsubscribe/([^/\n]+)", &unsubscribe},
    {"/display_channel/([^/\n]+)/([^/\n]+)", &display_channel},
    {"/list_channels/([^/\n]+)", &list_channels},
};

void handle_command_match(server_t *server, clients_t *client,
    const regmatch_t *matches, command_t command)
{
    size_t match_length = 0;
    const char *src = NULL;
    regmatch_t match = {0};

    for (size_t i = 0; i < MAX_ARGS; i++) {
        match = matches[i + 1];
        match_length = (size_t)match.rm_eo - (size_t)match.rm_so;
        client->arguments[i] = calloc(match_length + 1, sizeof(char));
        src = client->command + match.rm_so;
        strncpy(client->arguments[i], src, match_length);
    }
    command.handler(server, client);
}

void handle_command(server_t *server, clients_t *client)
{
    regex_t regex = {0};
    regmatch_t matches[MAX_ARGS + 1] = {0};

    for (size_t i = 0; i < (sizeof(commands) / sizeof(command_t)); i++) {
        if (regcomp(&regex, commands[i].command_regex, REG_EXTENDED) != 0) {
            continue;
        }
        if (regexec(&regex, client->command, 4, matches, 0) == 0) {
            handle_command_match(server, client, matches, commands[i]);
            regfree(&regex);
            return;
        }
    }
    regfree(&regex);
}
