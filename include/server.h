/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** server
*/

#pragma once

#include "logging_client.h"
#include "logging_server.h"
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
#include <string.h>
#include <sys/queue.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <unistd.h>
#include <uuid/uuid.h>

#define MAX_PORT 65535
#define MAX_NAME_LENGTH 32
#define MAX_DESCRIPTION_LENGTH 255
#define MAX_BODY_LENGTH 512
#define MAX_COMMAND_LENGTH 255
#define UUID_LENGTH 37
#define MAX_ARGS 4

typedef struct channel {
    char name[MAX_NAME_LENGTH];
    char description[MAX_DESCRIPTION_LENGTH];
    char uuid_str[UUID_LENGTH];
    uuid_t uuid;
    LIST_ENTRY(channel) pointers;
} channel_t;

typedef struct teams {
    char name[MAX_NAME_LENGTH];
    char description[MAX_DESCRIPTION_LENGTH];
    char uuid_str[UUID_LENGTH];
    uuid_t uuid;
    LIST_ENTRY(teams) pointers;
    LIST_HEAD(channel_list, channel) channels;
    LIST_HEAD(team_client_list, clients) clients;
} teams_t;

typedef struct message {
    uuid_t contact_uuid;
    int is_sender;
    int is_seen;
    char message_body[MAX_BODY_LENGTH];
    char contact_uuid_str[UUID_LENGTH];
    time_t timestamp;
    TAILQ_ENTRY(message) pointers;
} message_t;

typedef struct clients {
    bool need_exit;
    char *arguments[MAX_ARGS];
    TAILQ_HEAD(message_list, message) messages;
    char command[MAX_COMMAND_LENGTH];
    char name[MAX_NAME_LENGTH];
    int socket;
    int status;
    uuid_t uuid;
    char *uuid_str;
    LIST_ENTRY(clients) pointers;
} clients_t;

typedef struct server {
    LIST_HEAD(client_list, clients) clients;
    LIST_HEAD(team_list, teams) teams;
    fd_set read_fds;
    int max_fd;
    int server_socket;
    socklen_t server_addr_len;
    struct sockaddr_in server_addr;
    uint16_t port;
} server_t;

typedef void (*command_handler_t)(server_t *server, clients_t *client);

typedef struct command {
    const char *command_regex;
    command_handler_t handler;
} command_t;

bool is_file_exists(const char *filename);
clients_t *find_client_by_uuid(server_t *server, const uuid_t uuid);
clients_t *load_client(const char *filename);
clients_t *parse_client_data(const char *uuid_str,
    const char *name, const int status);
int handle_read(clients_t *client);
int server(uint16_t port) __attribute__((noreturn));
void add_new_client(server_t *server, int client_socket);
void assign_client_values(server_t *server, clients_t *client,
    char *user_uuid, const char *user_name);
void bind_and_listen(const server_t *server);
void check_clients(server_t *server);
void create_directory_if_not_exists(const char *dir_name);
void disconnect_client(server_t *server, clients_t *client);
void exit_error(const char *str) __attribute__((noreturn));
void handle_client(server_t *server, clients_t **client_ptr);
void handle_command(server_t *server, clients_t *current_client);
void handle_command_match(server_t *server, clients_t *client,
    const regmatch_t *matches, command_t command);
void handle_disconnection(server_t *server);
void init_fds(server_t *server);
void init_server(server_t *server, uint16_t port);
void load_clients(server_t *server);
void login(server_t *server, clients_t *client);
void logout(server_t *server, clients_t *client);
void loop_server(server_t *server) __attribute__((noreturn));
void modify_file(const char *filename);
void modify_file_logout(const char *filename);
void print_server_usage(void);
void remove_existing_client(server_t *server, const char *user_uuid);
void save(server_t *server);
void select_accept(server_t *server);
void send_message(server_t *server, clients_t *client);
void sigint_handler(int signum);
void user(server_t *server, clients_t *client);
void users(server_t *server, clients_t *client);
void save_new_message_to_file(const char *client_uuid_str,
    message_t *message_info);
void save_messages_to_file(const char *sender_uuid_str,
    const char *receiver_uuid_str, message_t *message_info);
void add_message_to_client(clients_t *client, message_t *message_info);
void handle_message_sending(clients_t *sender, clients_t *receiver,
    message_t *message_info);
void display_pending_messages(clients_t *client);
void read_messages(clients_t *client, FILE *file, FILE *tmp_file);
void load_messages_from_file(clients_t *client);
FILE *open_message_file(clients_t *client,
    char *filename, size_t filename_size);
void read_and_load_messages(clients_t *client, FILE *file);
FILE *prepare_read_file(clients_t *client,
    char *filename, size_t filename_size);
FILE *prepare_temp_file(clients_t *client, char *tmp, size_t tmp_size);
message_t *prepare_message(clients_t *client);
clients_t *find_sender(server_t *server, clients_t *client);
clients_t *find_receiver(server_t *server, clients_t *client);
DIR *open_clients_directory(void);
void read_and_load_clients(server_t *server, DIR *dir);
void update_messages(clients_t *client, const message_t *message_ref,
    int is_seen, int is_sender);
void process_line(clients_t *client, const char *line,
    FILE *tmp_file, message_t *message_ref);
void process_and_load_message(clients_t *client, const char *line,
    message_t *message_info);
void messages(server_t *server, clients_t *client);
void save_message_to_file(const char *client_uuid_str,
    message_t *message_info);
void save_client_messages(clients_t *client);
void free_messages(struct message_list *head);
void free_clients(struct client_list *head);
void free_server(server_t *server);
void print_messages(clients_t *client, const char *contact_uuid,
    const char *user_uuid);
void create_team(server_t *server, clients_t *client);
bool is_team_exists(server_t *server, const char *team_name);
void create_new_team(server_t *server, const clients_t *client);
void write_team_to_file(const char *team_name,
    const char *team_description, char *team_uuid_str);
teams_t *parse_team_data(const char *team_name,
    const char *team_description, const char *team_uuid_str);
teams_t *load_team(const char *filename);
DIR *open_teams_directory(void);
void read_and_load_teams(server_t *server, DIR *dir);
void load_teams(server_t *server);
void add_team_in_struct(server_t *server, const char *team_name,
    const char *team_description, const char *team_uuid_str);
void free_teams(struct team_list *head);
void display_team(server_t *server, clients_t *client);
void list_teams(server_t *server, clients_t *client);
void create_channel(server_t *server, clients_t *client);
bool is_team_exists_uuid(server_t *server, const char *team_uuid);
teams_t *get_team_by_uuid(server_t *server, const char *team_uuid);
bool is_channel_exists(teams_t *team, const char *channel_name);
void write_channel_to_file(clients_t *client, char *channel_uuid_str);
void add_channel_in_struct(teams_t *team, clients_t *client,
    const char *uuid_str);
void create_new_channel(teams_t *team, clients_t *client);
channel_t *create_new_channel2(char *name, char *description, char *uuid_str);
void load_channels(server_t *server);
void load_channel(server_t *server, const char *filename);
void free_channels(struct channel_list *head);
void subscribe(server_t *server, clients_t *client);
bool is_user_in_team(teams_t *team, const clients_t *client);
void unsubscribe(server_t *server, clients_t *client);
void display_channel(server_t *server, clients_t *client);
channel_t *get_channel_by_uuid(teams_t *team, const char *channel_uuid);
void list_channels(server_t *server, clients_t *client);
