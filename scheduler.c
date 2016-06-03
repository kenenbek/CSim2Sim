//
// Created by ken on 24.05.16.
//

#include <simgrid/msg.h>
#include <csvparser.h>

xbt_dynar_t task_names;
xbt_dynar_t flops_sizes;
xbt_dynar_t data_sizes;
xbt_dynar_t types;
xbt_dynar_t data_location;

XBT_LOG_NEW_DEFAULT_CATEGORY(scheduler, "messsages specific for scheduler");

int comparator(void *a, void *b){
    msg_host_t hostA = *(msg_host_t*) a;
    msg_host_t hostB = *(msg_host_t*) b;
    return MSG_host_get_speed(hostA) < MSG_host_get_speed(hostB);
}

int 


int scheduler(int argc, char* argv[]){

    task_names = xbt_dynar_new(sizeof(char[20]), NULL);
    flops_sizes = xbt_dynar_new(sizeof(double), NULL);
    data_sizes = xbt_dynar_new(sizeof(double), NULL);
    types = xbt_dynar_new(sizeof(char[20]), NULL);
    data_location = xbt_dynar_new(sizeof(xbt_dynar_t), NULL);

    CsvParser *csvparser = CsvParser_new("data.csv", ",", 1);
    CsvRow *header;
    CsvRow *row;

    while ((row = CsvParser_getRow(csvparser))){
        const char **rowFields = CsvParser_getFields(row);

        xbt_dynar_push(task_names, rowFields[0]);
        xbt_dynar_push(flops_sizes, rowFields[1]);
        xbt_dynar_push(data_sizes, rowFields[2]);
        xbt_dynar_push(types, rowFields[3]);

        int number_fields = CsvParser_getNumFields(row);

        xbt_dynar_t locations = xbt_dynar_new(sizeof(char[20]), NULL);

        switch (number_fields){
            case 5:
                xbt_dynar_push(locations, rowFields[4]);
                break;
            case 6:
                xbt_dynar_push(locations, rowFields[4]);
                xbt_dynar_push(locations, rowFields[5]);
                break;
            case 7:
                xbt_dynar_push(locations, rowFields[4]);
                xbt_dynar_push(locations, rowFields[5]);
                xbt_dynar_push(locations, rowFields[6]);
                break;
        }
        xbt_dynar_push(data_location, &locations);
        CsvParser_destroy_row(row);
    }
    CsvParser_destroy(csvparser);


    char mailbox[30];
    msg_task_t task;
    int id = xbt_str_parse_int(argv[1], "Invalid argument %s");
    sprintf(mailbox, "scheduler");

    while (1){
        XBT_INFO("Scheduler received");
        int res = MSG_task_receive(&task, mailbox);
        XBT_INFO("Scheduler received");

        if(!strcmp(MSG_task_get_name(task), "finalize")){
            MSG_task_destroy(task);
            break;
        }

        xbt_dynar_t dynar = MSG_task_get_data(task);
        xbt_dynar_sort(dynar, comparator);


        MSG_task_destroy(task);
        task = NULL;
    }

    return 0;

}