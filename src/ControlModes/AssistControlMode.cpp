#include "ControlModes/AssistControlMode.h"
#include "packets/Assist.h"
#include "GameController.h"
#include "RadioTx.h"
#include "CommonTools.h"

#include <cstdint>

/*
TODO: Test Right X-Y Methods with wings attached
*/


void AssistControlMode::assistMode(uint32_t mask) {

    // Sticks & Triggers
    assist_send_features();

    // Buttons 
    assist_send_btns(mask);

    // System checks to act on buttons

}


void AssistControlMode::assist_send_features() {}
void AssistControlMode::assist_send_btns(uint32_t mask) {}

