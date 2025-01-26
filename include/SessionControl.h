#ifndef SESSION_CONTROL_H
#define SESSION_CONTROL_H
#pragma once
#include <iostream>
#include "Session.h"
#include "Logging.h"
#include "RadioTx.h"



inline void setControlMode(ControlMode mode){

    switch(mode){
        case ControlMode::MANUAL:
        {
            Session::control_mode.store(ControlMode::MANUAL, std::memory_order_acq_rel);
            Session::fixed_plane_heading.store(false, std::memory_order_acq_rel);
            Session::fixed_plane_altitude.store(false, std::memory_order_acq_rel);
            Session::fixed_plane_speed.store(false, std::memory_order_acq_rel);
            Logging::insertEventLog(EventType::CONTROL_MODE_CHANGE_MANUAL);

            Packet* event0_pkt = new EventPacket('e', EventType::CONTROL_MODE_CHANGE_MANUAL);
            sendToPlane(event0_pkt);
            std::cout << "Control mode set to MANUAL" << std::endl;
        }
            break;

        case ControlMode::ASSIST:
        {
            Session::control_mode.store(ControlMode::ASSIST, std::memory_order_acq_rel);
            Session::fixed_plane_heading.store(false, std::memory_order_acq_rel);
            Session::fixed_plane_altitude.store(false, std::memory_order_acq_rel);
            Session::fixed_plane_speed.store(false, std::memory_order_acq_rel);
            Logging::insertEventLog(EventType::CONTROL_MODE_CHANGE_ASSIST);

            Packet* event0_pkt = new EventPacket('e', EventType::CONTROL_MODE_CHANGE_ASSIST);
            sendToPlane(event0_pkt);
            std::cout << "Control mode set to ASSIST" << std::endl;
        }
            break;

        case ControlMode::TAXI:
        {
            if (!Session::isFlying.load(std::memory_order_relaxed)) {
                std::cout << "Cannot set TAXI mode while not flying" << std::endl;
                return;
            }
            Session::control_mode.store(ControlMode::TAXI, std::memory_order_acq_rel);
            Session::fixed_plane_heading.store(false, std::memory_order_acq_rel);
            Session::fixed_plane_altitude.store(false, std::memory_order_acq_rel);
            Session::fixed_plane_speed.store(false, std::memory_order_acq_rel);
            Logging::insertEventLog(EventType::CONTROL_MODE_CHANGE_TAXI);

            Packet* event0_pkt = new EventPacket('e', EventType::CONTROL_MODE_CHANGE_TAXI);
            sendToPlane(event0_pkt);
            std::cout << "Control mode set to TAXI" << std::endl;
        }
            break;

        case ControlMode::HOLDING:
        {
            //Session::control_mode.store(ControlMode::HOLDING, std::memory_order_release);

            if (Session::isFlying.load(std::memory_order_relaxed)) {
                Session::control_mode.store(ControlMode::HOLDING, std::memory_order_acq_rel);
            }
            Session::fixed_plane_heading.store(false, std::memory_order_acq_rel);
            Session::fixed_plane_altitude.store(true, std::memory_order_acq_rel);
            Session::fixed_plane_speed.store(true, std::memory_order_acq_rel);
            //Session::control_mode.store(ControlMode::HOLDING, std::memory_order_acq_rel);   // TODO: delete during production
            Logging::insertEventLog(EventType::CONTROL_MODE_CHANGE_HOLDING);
            
            // TODO: Implement waypoint to circle, ie 50 meters to left so plane just turns left and keeps going
            //Session::isCircleWaypoint.store(true, std::memory_order_acq_rel);
            Packet* event0_pkt = new EventPacket('e', EventType::CONTROL_MODE_CHANGE_HOLDING);
            sendToPlane(event0_pkt);
            Packet* event1_pkt = new EventData8Packet('e', EventType::FIXED_ALTITUDE_DATA_CHANGE, 40);  // 40 meters
            sendToPlane(event1_pkt);
            Packet* event2_pkt = new EventData8Packet('e', EventType::FIXED_SPEED_DATA_CHANGE, 30);     // 30 Km/h
            sendToPlane(event2_pkt);

            std::cout << "Control mode set to HOLDING" << std::endl;
        }
            break;

        case ControlMode::EMERGENCY:
            Session::control_mode.store(ControlMode::EMERGENCY, std::memory_order_release);
            break;

        case ControlMode::PAIRING:
            Session::control_mode.store(ControlMode::PAIRING, std::memory_order_release);
            break;

        case ControlMode::RECOVERY: 
            Session::control_mode.store(ControlMode::RECOVERY, std::memory_order_release);
            break;

        case ControlMode::AUTO: 
            Session::control_mode.store(ControlMode::AUTO, std::memory_order_release);
            break;
    }



}




#endif  // SESSION_CONTROL_H