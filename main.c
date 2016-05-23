//
// Created by ken on 23.05.16.
//

#include <simgrid/msg.h>
int scheduler(int argc, char *argv[]);
int tier1(int argc, char *argv[]);

XBT_LOG_NEW_DEFAULT_CATEGORY(msg_app_masterworker, "Messages specific for this msg example");


int scheduler(int argc, char *argv[]){

}

int tier1(int argc, char *argv[]){
    msg_task_t task = NULL;
    char mailbox[80];

    int num = xbt_str_parse_int(argv[1], "Invalid argument %s");
    int id = xbt_str_parse_int(argv[2], "Invalid argument %s");

    sprintf(mailbox, "tier1_%i_%i", num, id);

    while(1){
        int res = MSG_task_receive(&task, mailbox);
        xbt_assert(res == MSG_OK, "MSG_task_get failes");

        if(!strcmp(MSG_task_get_name(task), "finalize")){
            MSG_task_destroy(task);
            break;
        }
        if(!strcmp(MSG_task_get_name(task)))
    }

 }

int main(int argc, char *argv[]){
    MSG_init(&argc, argv);

    MSG_create_environment(argv[1]);

    MSG_function_register("scheduler", scheduler);
    MSG_function_register("tier1", tier1);
    MSG_launch_application(argv[2]);

    msg_error_t res = MSG_main();

    XBT_INFO("Simulation time %g", MSG_get_clock());

    return res != MSG_OK;
}