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
} message_type;

typedef struct s_message{
    message_type type;
    const char *downloadfrom;
    double size_data;
} s_message_t, *message_t;


int task_message_size(message_type type);
void task_message_free(void *);

#endif //CSIM2SIM_MESSAGES_H
