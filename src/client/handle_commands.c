/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** handle_commands
*/

#include "client.h"

static const command_t commands[16] = {
    {"/login\\s+\"([^/\n]+)\"", &login},
    {"/create\\s+\"([^/\n]+)\"\\s+\"([^/\n]+)\"", &create},
    {"/help", &help},
    {"/info", &info},
    {"/list", &list},
    {"/logout", &logout},
    {"/messages\\s+\"([^/\n]+)\"", &messages},
    {"/send\\s+\"([^/\n]+)\"\\s+\"([^/\n]+)\"", &send_message},
    {"/users", &users},
    {"/use\\s+\"([^/\n]+)\"\\s+\"([^/\n]+)\"\\s+\"([^/\n]+)\"", &use_thread},
    {"/use\\s+\"([^/\n]+)\"\\s+\"([^/\n]+)\"", &use_channel},
    {"/use\\s+\"([^/\n]+)\"", &use_team},
    {"/use", &use_default},
    {"/user\\s+\"([^/\n]+)\"", &user},
    {"/subscribe\\s+\"([^/\n]+)\"", &subscribe},
    {"/unsubscribe\\s+\"([^/\n]+)\"", &unsubscribe},
};

size_t count_contexts(const client_t *client)
{
    size_t count = 0;

    for (size_t i = 0; i < MAX_ARGS; i++) {
        if ((client->context[i] != NULL)
        && (strcmp(client->context[i], "") != 0)) {
            count++;
        }
    }
    return count;
}

void handle_command_match(client_t *client,
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
    command.handler(client);
}

void handle_client_command(client_t *client)
{
    regex_t regex = {0};
    regmatch_t matches[4] = {0};

    for (size_t i = 0; i < (sizeof(commands) / sizeof(command_t)); i++) {
        if ((i > 0) && (client->status == 0)) {
            client_error_unauthorized();
            return;
        }
        if (regcomp(&regex, commands[i].command_regex, REG_EXTENDED) != 0) {
            continue;
        }
        if (regexec(&regex, client->command, 4, matches, 0) == 0) {
            handle_command_match(client, matches, commands[i]);
            free_arg(client);
            regfree(&regex);
            return;
        }
        regfree(&regex);
    }
}
