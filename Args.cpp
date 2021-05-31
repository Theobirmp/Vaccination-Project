
#include <string>
#include <cstring>

#include "Args.h"
#include "helpers.h"

using namespace std;

Args::Args(int argc, char * argv[]) {
    //args=./vaccineMonitor -c citizenRecordsFile –b bloomSize
    //-c and -b can be given in any order
    string temp;
    filepath = argv[0];

    if (strcmp(argv[1], "-c") == 0) {
        c = argv[1];
        filename = argv[2];
        b = argv[3];
        temp = argv[4];
        bloom_size = args_string_to_int(temp);
    } else {
        c = argv[3];
        filename = argv[4];
        b = argv[1];
        temp = argv[2];
        bloom_size = args_string_to_int(temp);
    }

    levels = 30;//used for testing purposes at the early stages of the excercise. changed later 
}