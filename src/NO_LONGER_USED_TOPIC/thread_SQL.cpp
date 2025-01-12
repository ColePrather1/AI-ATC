#include "thread_SQL.hpp"
#include "Logging.h"



static bool sql_setup(){
    return logging_setup();
}

static void sql_loop(){
    logging_loop();
}


extern QuickThread sql_thread(sql_setup, sql_loop);

//extern QuickThread sql_thread(sql_setup, sql_loop);

