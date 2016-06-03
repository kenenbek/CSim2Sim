//
// Created by ken on 23.05.16.
//
#include <simgrid/msg.h>
#include "messages.h"

XBT_LOG_NEW_DEFAULT_CATEGORY(dispatcher, "messsages specific for dispatching");


static int from_scheduler_to_tier(int argc, char *argv[]){

    msg_task_t task;
    char mailbox[80];
    xbt_dict_t map;
    xbt_dict_cursor_t cursor = NULL;

    int id = xbt_str_parse_int(argv[1], "Invalid argument %s");
    int number_tiers = xbt_str_parse_int(argv[2], "Invalid argument %s");

    sprintf(mailbox, "dispatcher1_%i_ST", id);

    while (1){
        int res = MSG_task_receive(&(task), mailbox);

        if(!strcmp(MSG_task_get_name(task), "finalize")){
            MSG_task_destroy(task);
            break;
        }
        map = MSG_task_get_data(task);

        msg_host_t host;
        msg_task_t task_t;

        xbt_dict_foreach(map, cursor, host, task_t){
            MSG_task_send(task_t, MSG_host_get_name(host));
        }
        xbt_dict_free(&map);
    }
    return 0;
}

static int from_tier_to_scheduler(int argc, char **argv){

    char mailbox[80];
    msg_task_t task;
    msg_task_t m_pilot;

    int id = xbt_str_parse_int(argv[1], "Invalid argument %s");

    xbt_dynar_t dynar = xbt_dynar_new(sizeof(msg_host_t), NULL);

    sprintf(mailbox, "dispatcher1_%i_TS", id);

    while (1){
        int res = MSG_task_receive(&task, mailbox);
        XBT_INFO("Received");

        if(!strcmp(MSG_task_get_name(task), "finalize")){
            MSG_task_destroy(task);
            break;
        }

        xbt_dynar_push_as(dynar, msg_host_t, MSG_task_get_source(task));

        if (xbt_dynar_length(dynar) > 0){
            XBT_INFO("1");
            m_pilot = MSG_task_create("mega_pilot", 0, MESSAGES_SIZE, dynar);
            MSG_task_send(m_pilot, "scheduler");
        }
        MSG_task_destroy(task);
        task = NULL;

    }

    return 0;
}

int dispatcher(int argc, char *argv[]){

    int num = xbt_str_parse_int(argv[1], "Invalid argument %s");
    int number_tiers = xbt_str_parse_int(argv[2], "Invalid argument %s");

    char** newargv = xbt_new(char*, 3);
    newargv[0] = xbt_strdup("TS");
    newargv[1] = xbt_strdup(argv[1]);
    newargv[2] = xbt_strdup(argv[2]);
    MSG_process_create_with_arguments("TS", from_tier_to_scheduler, NULL, MSG_host_self(), 3, newargv);

    return 0;
}

