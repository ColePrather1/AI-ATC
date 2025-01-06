#ifndef THREAD_SQL_H
#define THREAD_SQL_H

#pragma once
#include "Logging.h"
#include "QuickThread.h"
//#include "FlightDatabase.h"
//#include "SQL.h"


static bool sql_setup(){
    return logging_setup();
}

static void sql_loop(){
    logging_loop();
}

extern QuickThread sql_thread(sql_setup, sql_loop);

#endif // THREAD_SQL_H