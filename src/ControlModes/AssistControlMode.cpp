#include "ControlModes/AssistControlMode.h"
#include "packets/Assist.h"
#include "GameController.h"
#include "RadioTx.h"
#include "CommonTools.h"

/*
TODO: Test Right X-Y Methods with wings attached
*/


void AssistControlMode::assistMode() {

    // Sticks & Triggers
    assist_send_features();

    // Buttons 
    assist_send_btns();

    // System checks to act on buttons

}


void AssistControlMode::assist_send_features() {}
void AssistControlMode::assist_send_btns() {}

