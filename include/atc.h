#ifndef ATC_H
#define ATC_H

#pragma once


namespace ATC {
    
    bool pair_pilot();
    bool atc_startup();
    bool atc_shutdown();        // returns 1 if successful


    // Control Modes
    /*
    bool setAutoControlMode();
    bool setManualControlMode();
    bool setAssistControlMode();
    bool setEmergencyControlMode();
    bool setHoldingPatternControlMode();
    bool setTaxiOnlyControlMode();
    */

    // Flight Status

}

#endif // ATC_H