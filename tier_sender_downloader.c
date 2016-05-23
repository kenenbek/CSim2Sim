//
// Created by ken on 23.05.16.
//
#include <simgrid/msg.h>
#include "messages.h"

XBT_LOG_NEW_DEFAULT_CATEGORY(sender_downloader, "messsages specific for sending and downloading");

int tier_sender_downloader(int argc, char *argv[]){

    char mailbox[80];
    msg_task_t task = NULL;

    int num = xbt_str_parse_int(argv[1], "Invalid argument %s");
    int id = xbt_str_parse_int(argv[2], "Invalid argument %s");

    sprintf(mailbox, "tier1_%i_%i", num, id);

    while (1){

        if(!strcmp(MSG_task_get_name(task), "finalize")){
            MSG_task_destroy(task);
            break;
        }

        int res = MSG_task_receive(&(task), mailbox);
        xbt_assert(res == MSG_OK, "MSG_get_task failed");

        message_t message = MSG_task_get_data(task);

        msg_task_t d_task = MSG_task_create(MSG_task_get_name(task), message->flops_amount, message->size_data, NULL);
        MSG_task_send(d_task, MSG_host_get_name(MSG_task_get_source(task)));
        MSG_task_destroy(task);
        task = NULL;
    }
}
