//
// Created by ken on 23.05.16.
//
#include <simgrid/msg.h>
#include "messages.h"

XBT_LOG_NEW_DEFAULT_CATEGORY(sender_downloader, "messsages specific for sending and downloading");

int dispatcher(int argc, char *argv[]){

    int num = xbt_str_parse_int(argv[1], "Invalid argument %s");
    int number_tiers = xbt_str_parse_int(argv[2], "Invalid argument %s");

    return 0;
}

int from_scheduler_to_tier(int argc, char *argv[]){
    msg_task_t task;
    char mailbox[80];

    int id = xbt_str_parse_int(argv[1], "Invalid argument %s");
    int number_tiers = xbt_str_parse_int(argv[2], "Invalid argument %s");

    sprintf(mailbox, "dispatcher1_%i_ST", id);

    while (1){
        task = MSG_task_receive(task, mailbox);
    }


    return 0;
}

int from_tier_to_scheduler(int argc, char *argv[]){
    int id = xbt_str_parse_int(argv[1], "Invalid argument %s");
    int number_of_tiers = xbt_str_parse_int(argv[1], "Invalid argument %s");
    char mailbox[80];
    msg_task_t task;
    xbt_dynar_t dynar = xbt_dynar_new(sizeof(msg_host_t), NULL);

    sprintf(mailbox, "dispatcher1_%i_TS", id);

    while (1){
        int res = MSG_task_receive(&(task), mailbox);

        if(!strcmp(MSG_task_get_name(task), "finalize")){
            MSG_task_destroy(task);
            break;
        }
        xbt_dynar_push_as(dynar, msg_host_t, MSG_task_get_source(task));

        if ()
    }


    return 0;
}

