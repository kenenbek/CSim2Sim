//
// Created by ken on 23.05.16.
//
#include <simgrid/msg.h>
#include "messages.h"

void task_message_free(void *task){
    message_t message = MSG_task_get_data(task);
    xbt_free(message);
    MSG_task_destroy(task);
}

msg_task_t task_message_new(char *name, message_type type, const char *downloadfrom, double size){

    message_t message = xbt_new(s_message_t, 1);
    message->type = type;
    message->downloadfrom = downloadfrom;
    message->size_data = size;

    msg_task_t task = MSG_task_create(name, 0, MESSAGES_SIZE_INSTRUCTION, message);
    return task;
}

msg_task_t give_me_data(char *name, message_type type, double size){
    message_t message = xbt_new(s_message_t, 1);
    message->type = 


}




int task_message_size(message_type type){
    int size = 0;
    switch (type){
        case INSTRUCTION:
            size = MESSAGES_SIZE_INSTRUCTION;
            break;
        case GIVEMEDATA:
            size = MESSAGES_SIZE_GIVEMEDATA;
            break;
        case FINALIZE:
            size = MESSAGES_SIZE_FINALIZE;
    }
    return size;
}

