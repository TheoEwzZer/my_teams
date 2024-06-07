/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** help
*/

#include "client.h"

void help(client_t *client)
{
    (void)client;
    printf("/login [\"user_name\"]\n");
    printf("/logout\n");
    printf("/users\n");
    printf("/user [\"user_uuid\"]\n");
    printf("/send [\"user_uuid\"] [\"message_body\"]\n");
    printf("/messages [\"user_uuid\"]\n");
    printf("/subscribe [\"team_uuid\"]\n");
    printf("/subscribed ?[\"team_uuid\"]\n");
    printf("/unsubscribe [\"team_uuid\"]\n");
    printf("/use ?[\"team_uuid\"] ?[\"channel_uuid\"] ?[\"thread_uuid\"]\n");
    printf("/create : create the sub resource (see below)\n");
    printf("/list : list all the sub resources (see below)\n");
    printf("/info : display details of the current resource (see below)\n");
    help_create();
}

void help_create(void)
{
    printf("\n/CREATE\n");
    printf("When the context is not defined (/use):\n");
    printf("/create [\"team_name\"] [\"team_description\"] ");
    printf(": create a new team\n");
    printf("When team_uuid is defined (/use \"team_uuid\"):\n");
    printf("/create [\"channel_name\"] [\"channel_description\"] ");
    printf(": create a new channel\n");
    printf("When team_uuid and channel_uuid are defined ");
    printf("(/use \"team_uuid\" \"channel_uuid\"):\n");
    printf("/create [\"thread_title\"] [\"thread_message\"] ");
    printf("create a new thread\n");
    printf("When team_uuid, channel_uuid and thread_uuid are defined ");
    printf("(/use \"team_uuid\" \"channel_uuid\" \"thread_uuid\"):\n");
    printf("/create [\"comment_body\"] : create a new reply\n");
    help_list();
}

void help_list(void)
{
    printf("\n/LIST\n");
    printf("When the context is not defined (/use):\n");
    printf("/list : list all existing teams\n");
    printf("When team_uuid is defined (/use \"team_uuid\"):\n");
    printf("/list : list all existing channels\n");
    printf("When team_uuid and channel_uuid are defined ");
    printf("(/use \"team_uuid\" \"channel_uuid\"):\n");
    printf("/list : list all existing threads\n");
    printf("When team_uuid, channel_uuid and thread_uuid are defined ");
    printf("(/use \"team_uuid\" \"channel_uuid\" \"thread_uuid\"):\n");
    printf("/list : list all existing replies\n");
    help_info();
}

void help_info(void)
{
    printf("\n/INFO\n");
    printf("When the context is not defined (/use):\n");
    printf("/info : display currently logged-in user details\n");
    printf("When team_uuid is defined (/use \"team_uuid\"):\n");
    printf("/info : display currently selected team details\n");
    printf("When team_uuid and channel_uuid are ");
    printf("defined (/use \"team_uuid\" \"channel_uuid\"):\n");
    printf("/info : display currently selected channel details\n");
    printf("When team_uuid, channel_uuid and thread_uuid are defined ");
    printf("(/use \"team_uuid\" \"channel_uuid\" \"thread_uuid\"):\n");
    printf("/info : display currently selected thread details\n");
}
