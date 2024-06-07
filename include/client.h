/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** client
*/

#pragma once

#include "logging_client.h"
#include "logging_server.h"
#include <arpa/inet.h>
#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <netinet/in.h>
#include <regex.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <unistd.h>
#include <uuid/uuid.h>

#define MAX_PORT 65535
#define MAX_NAME_LENGTH 32
#define MAX_DESCRIPTION_LENGTH 255
#define MAX_BODY_LENGTH 512
#define MAX_COMMAND_LENGTH 800
#define UUID_LENGTH 37
#define MAX_ARGS 3

typedef struct client {
    char *arguments[MAX_ARGS];
    char *context[MAX_ARGS];
    char *uuid_str;
    char command[MAX_COMMAND_LENGTH];
    char command_buffer[MAX_COMMAND_LENGTH];
    char server_response[MAX_COMMAND_LENGTH];
    char name[MAX_NAME_LENGTH];
    int max_fd;
    int socket;
    int status;
    uuid_t uuid;
} client_t;

typedef void (*command_handler_t)(client_t *client);
typedef void (*api_handler_t)(client_t *client, const regmatch_t *matches);

typedef struct command {
    const char *command_regex;
    command_handler_t handler;
} command_t;

typedef struct api {
    const char *api_regex;
    api_handler_t handler;
} api_t;

bool find_user_file(client_t *client, DIR *dir,
    char *user_uuid, char *user_name);
bool process_user_file(client_t *client, FILE *file,
    char *user_uuid, char *user_name);
int client(const char *ip, uint16_t port);
int connect_to_server(const char *ip_address, long port_num);
size_t count_contexts(const client_t *client);
void create(client_t *client);
void create_directory_if_not_exists(const char *dir_name);
void create_new_user(client_t *client, char *user_uuid, char *user_name);
void free_arg(client_t *client);
void free_client(client_t *client) __attribute__((noreturn));
void handle_already_exist(client_t *client, const regmatch_t *matches);
void handle_client_command(client_t *client);
void handle_command_match(client_t *client,
    const regmatch_t *matches, command_t command);
void handle_event_channel_created(client_t *client, const regmatch_t *matches);
void handle_event_team_created(client_t *client, const regmatch_t *matches);
void handle_input(client_t *client);
void handle_io(client_t *client, int client_socket);
void handle_logged_in(client_t *client, const regmatch_t *matches);
void handle_logged_out(client_t *client, const regmatch_t *matches);
void handle_message_received(client_t *client, const regmatch_t *matches);
void handle_print_channel(client_t *client, const regmatch_t *matches);
void handle_print_channel_created(client_t *client, const regmatch_t *matches);
void handle_print_subscribed(client_t *client, const regmatch_t *matches);
void handle_print_team(client_t *client, const regmatch_t *matches);
void handle_print_team_created(client_t *client, const regmatch_t *matches);
void handle_print_teams(client_t *client, const regmatch_t *matches);
void handle_print_unsubscribed(client_t *client, const regmatch_t *matches);
void handle_print_user(client_t *client, const regmatch_t *matches);
void handle_print_users(client_t *client, const regmatch_t *matches);
void handle_private_message_print(client_t *client, const regmatch_t *matches);
void handle_server_response(client_t *client);
void handle_team_print_channels(client_t *client, const regmatch_t *matches);
void handle_unknown_channel(client_t *client, const regmatch_t *matches);
void handle_unknown_team(client_t *client, const regmatch_t *matches);
void handle_unknown_user(client_t *client, const regmatch_t *matches);
void help(client_t *client);
void help_create(void);
void help_info(void);
void help_list(void);
void info(client_t *client);
void list(client_t *client);
void login(client_t *client);
void logout(client_t *client);
void messages(client_t *client);
void parse_file_content(FILE *file, char **user_uuid);
void print_client_usage(void);
void send_message(client_t *client);
void sigint_handler(int signum);
void subscribe(client_t *client);
void unsubscribe(client_t *client);
void use_channel(client_t *client);
void use_default(client_t *client);
void use_team(client_t *client);
void use_thread(client_t *client);
void user(client_t *client);
void users(client_t *client);
