//
// Created by ken on 30.05.16.
//

#include <simgrid/msg.h>
#include "messages.h"

XBT_LOG_NEW_DEFAULT_CATEGORY(node, "messages specific for nodes");

int tier1(int argc, char *argv[]){
    XBT_INFO("I'am ready to work");
    msg_task_t task = NULL;
    msg_task_t data = NULL;
    char mailbox[80];
    char dispatcher_mail[80];

    int num = xbt_str_parse_int(argv[1], "Invalid argument %s");
    int id = xbt_str_parse_int(argv[2], "Invalid argument %s");

    sprintf(mailbox, "Tier1_%i_%i", num, id);

    //At first moment nodes go to dispatcher
    sprintf(dispatcher_mail, "dispatcher1_%i_TS", num);
    msg_task_t first_task = MSG_task_create("Firstrequest", 0, MESSAGES_SIZE, NULL);
    XBT_INFO("Send a pilot message to dispatcher");
    MSG_task_send(first_task, dispatcher_mail);

    while(1){

        int res = MSG_task_receive(&task, mailbox);
        xbt_assert(res == MSG_OK, "MSG_task_get fails");

        if(!strcmp(MSG_task_get_name(task), "finalize")){
            MSG_task_destroy(task);
            break;
        }

        message_t message = MSG_task_get_data(task);
        switch (message->type){
            case MONTE_CARLO:

                XBT_INFO("Receive %s", MSG_task_get_name(task));
                XBT_INFO("Start to execute Monte-Carlo %s", MSG_task_get_name(task));
                message_t sms_from_task = MSG_task_get_data(task);
                msg_task_t mc_task = MSG_task_create("", sms_from_task->flops_amount, 0, NULL);
                MSG_task_execute(mc_task);
                XBT_INFO("Finished execute Monte-Carlo %s", MSG_task_get_name(task));

                MSG_task_destroy(mc_task);
                MSG_task_destroy(task);
                task = NULL;
                XBT_INFO("Send a pilot message to dispatcherxx");
                MSG_task_send(MSG_task_create("Request", 0, MESSAGES_SIZE, NULL), dispatcher_mail);

                break;
            case INSTRUCTION:

                XBT_INFO("Receive %s", MSG_task_get_name(task));
                if (!strcmp(message->downloadfrom, MSG_host_get_name(MSG_host_self()))){
                    XBT_INFO("Start to execute %s.I have all data", MSG_task_get_name(task));
                    MSG_task_execute(task);
                    XBT_INFO("Finished to execute %s", MSG_task_get_name(task));

                    MSG_task_destroy(task);
                    task = NULL;
                    XBT_INFO("Send a pilot message to dispatcher");
                    MSG_task_send(MSG_task_create("Request", 0, MESSAGES_SIZE, NULL), dispatcher_mail);

                } else{
                    msg_task_t gtask = give_me_data(MSG_task_get_name(task), message->flops_amount, message->size_data);
                    XBT_INFO("Hey %s, give me data for %s", message->downloadfrom, MSG_task_get_name(task));
                    MSG_task_send(gtask, message->downloadfrom);
                    XBT_INFO("yyyyyyyyyy");

                    MSG_task_destroy(task);
                    task = NULL;
                }
                break;

            case DOWNLOADED:

                XBT_INFO("Download data of %s from %s", MSG_task_get_name(task), sg_host_get_name(MSG_task_get_source(task)));
                XBT_INFO("Start to execute %s", MSG_task_get_name(task));
                MSG_task_execute(task);
                XBT_INFO("Finished to execute %s", MSG_task_get_name(task));

                MSG_task_destroy(task);
                task = NULL;
                XBT_INFO("Send a pilot message to dispatcher");
                MSG_task_send(MSG_task_create("Request", 0, MESSAGES_SIZE, NULL), dispatcher_mail);
                break;
        }
    }

 }
