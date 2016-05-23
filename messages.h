//
// Created by ken on 23.05.16.
//

#ifndef CSIM2SIM_MESSAGES_H
#define CSIM2SIM_MESSAGES_H

#include <simgrid/msg.h>

#define MESSAGES_SIZE_INSTRUCTION 1
#define MESSAGES_SIZE_GIVEMEDATA 1
#define MESSAGES_SIZE_FINALIZE 1

typedef enum {
    INSTRUCTION,
    GIVEMEDATA,
    FINALIZE,
    DOWNLOADED
} message_type;

typedef struct s_message{
    message_type type;
    const char *downloadfrom;
    double size_data;
    double flops_amount;
} s_message_t, *message_t;

msg_task_t task_message_new(char *name, message_type type, const char *downloadfrom, double size);
msg_task_t give_me_data(char *name, message_type type, double flops_amount, double size);

void task_message_free(void *);
int task_message_size(message_type type);

#endif //CSIM2SIM_MESSAGES_H
