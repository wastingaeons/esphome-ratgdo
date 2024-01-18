/************************************
 * Rage
 * Against
 * The
 * Garage
 * Door
 * Opener
 *
 * Copyright (C) 2022  Paul Wieland
 *
 * GNU GENERAL PUBLIC LICENSE
 ************************************/

#pragma once
#include "macros.h"
#include <cstdint>

namespace esphome {
namespace ratgdo {

    ENUM(DoorState, uint8_t,
        (UNKNOWN, 0),
        (OPEN, 1),
        (CLOSED, 2),
        (STOPPED, 3),
        (OPENING, 4),
        (CLOSING, 5))

    /// Enum for all states a the light can be in.
    ENUM(LightState, uint8_t,
        (OFF, 0),
        (ON, 1),
        (UNKNOWN, 2))
    LightState light_state_toggle(LightState state);

    /// Enum for all states a the lock can be in.
    ENUM(LockState, uint8_t,
        (UNLOCKED, 0),
        (LOCKED, 1),
        (UNKNOWN, 2))
    LockState lock_state_toggle(LockState state);

    /// MotionState for all states a the motion can be in.
    ENUM(MotionState, uint8_t,
        (CLEAR, 0),
        (DETECTED, 1),
        (UNKNOWN, 2))

    /// Enum for all states a the obstruction can be in.
    ENUM(ObstructionState, uint8_t,
        (OBSTRUCTED, 0),
        (CLEAR, 1),
        (UNKNOWN, 2))

    /// Enum for all states a the motor can be in.
    ENUM(MotorState, uint8_t,
        (OFF, 0),
        (ON, 1),
        (UNKNOWN, 2))

    /// Enum for all states the button can be in.
    ENUM(ButtonState, uint8_t,
        (PRESSED, 0),
        (RELEASED, 1),
        (UNKNOWN, 2))


    // actions
    ENUM(LightAction, uint8_t,
        (OFF, 0),
        (ON, 1),
        (TOGGLE, 2),
        (UNKNOWN, 3))

    ENUM(LockAction, uint8_t,
        (UNLOCK, 0),
        (LOCK, 1),
        (TOGGLE, 2),
        (UNKNOWN, 3))

    ENUM(DoorAction, uint8_t,
        (CLOSE, 0),
        (OPEN, 1),
        (TOGGLE, 2),
        (STOP, 3),
        (UNKNOWN, 4))

    struct Openings {
        uint16_t count;
        uint8_t flag;
    };

    struct TimeToClose {
        uint16_t seconds;
    };

} // namespace ratgdo
} // namespace esphome
