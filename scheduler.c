//
// Created by ken on 24.05.16.
//

#include <simgrid/msg.h>
#include <csvparser.h>


int scheduler(int argc, char* argv[]){

    xbt_dynar_t task_names = xbt_dynar_new(sizeof(char[20]), NULL);
    xbt_dynar_t flops_sizes = xbt_dynar_new(sizeof(double), NULL);
    xbt_dynar_t data_sizes = xbt_dynar_new(sizeof(double), NULL);
    xbt_dynar_t types = xbt_dynar_new(sizeof(char[20]), NULL);
    xbt_dynar_t data_location = xbt_dynar_new(sizeof(xbt_dynar_t), NULL);

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



    
    return 0;

}