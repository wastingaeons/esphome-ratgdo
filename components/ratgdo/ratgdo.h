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

#include "esphome/core/component.h"
#include "esphome/core/hal.h"
#include "esphome/core/preferences.h"

#include "observable.h"
#include "callbacks.h"
#include "macros.h"
#include "ratgdo_state.h"
#include "protocol.h"

namespace esphome {
    class InternalGPIOPin;
namespace ratgdo {

    class RATGDOComponent;
    typedef Parented<RATGDOComponent> RATGDOClient;

    const float DOOR_POSITION_UNKNOWN = -1.0;
    const float DOOR_DELTA_UNKNOWN = -2.0;

    struct RATGDOStore {
        int obstruction_low_count = 0; // count obstruction low pulses

        static void IRAM_ATTR HOT isr_obstruction(RATGDOStore* arg)
        {
            arg->obstruction_low_count++;
        }
    };

    using protocol::Args;
    using protocol::Result;
    
    class RATGDOComponent : public Component {
    public:

        void setup() override;
        void loop() override;
        void dump_config() override;

        void init_protocol();

        void obstruction_loop();

        float start_opening { -1 };
        observable<float> opening_duration { 0 };
        float start_closing { -1 };
        observable<float> closing_duration { 0 };

        observable<uint16_t> openings { 0 }; // number of times the door has been opened

        observable<DoorState> door_state { DoorState::UNKNOWN };
        observable<float> door_position { DOOR_POSITION_UNKNOWN };

        unsigned long door_start_moving { 0 };
        float door_start_position { DOOR_POSITION_UNKNOWN };
        float door_move_delta { DOOR_DELTA_UNKNOWN };

        observable<LightState> light_state { LightState::UNKNOWN };
        observable<LockState> lock_state { LockState::UNKNOWN };
        observable<ObstructionState> obstruction_state { ObstructionState::UNKNOWN };
        observable<MotorState> motor_state { MotorState::UNKNOWN };
        observable<ButtonState> button_state { ButtonState::UNKNOWN };
        observable<MotionState> motion_state { MotionState::UNKNOWN };

        OnceCallbacks<void(DoorState)> door_state_received;

        observable<bool> sync_failed { false };

        void set_output_gdo_pin(InternalGPIOPin* pin) { this->output_gdo_pin_ = pin; }
        void set_input_gdo_pin(InternalGPIOPin* pin) { this->input_gdo_pin_ = pin; }
        void set_input_obst_pin(InternalGPIOPin* pin) { this->input_obst_pin_ = pin; }
        
        Result call_protocol(Args args);

        void received(const DoorState door_state);
        void received(const LightState light_state);
        void received(const LockState lock_state);
        void received(const ObstructionState obstruction_state);
        void received(const LightAction light_action);
        void received(const MotorState motor_state);
        void received(const ButtonState button_state);
        void received(const MotionState motion_state);
        void received(const Openings openings);
        void received(const TimeToClose ttc);

        // door
        void door_toggle();
        void door_open();
        void door_close();
        void door_stop();

        void door_action(DoorAction action);
        void ensure_door_action(DoorAction action, uint32_t delay = 1500);
        void door_move_to_position(float position);
        void set_door_position(float door_position) { this->door_position = door_position; }
        void set_opening_duration(float duration);
        void set_closing_duration(float duration);
        void schedule_door_position_sync(float update_period = 500);
        void door_position_update();
        void cancel_position_sync_callbacks();


        // light
        void light_toggle();
        void light_on();
        void light_off();
        LightState get_light_state() const;

        // lock
        void lock_toggle();
        void lock();
        void unlock();

        // button functionality
        void query_status();
        void query_openings();
        void sync();

        // children subscriptions
        void subscribe_rolling_code_counter(std::function<void(uint32_t)>&& f);
        void subscribe_opening_duration(std::function<void(float)>&& f);
        void subscribe_closing_duration(std::function<void(float)>&& f);
        void subscribe_openings(std::function<void(uint16_t)>&& f);
        void subscribe_door_state(std::function<void(DoorState, float)>&& f);
        void subscribe_light_state(std::function<void(LightState)>&& f);
        void subscribe_lock_state(std::function<void(LockState)>&& f);
        void subscribe_obstruction_state(std::function<void(ObstructionState)>&& f);
        void subscribe_motor_state(std::function<void(MotorState)>&& f);
        void subscribe_button_state(std::function<void(ButtonState)>&& f);
        void subscribe_motion_state(std::function<void(MotionState)>&& f);
        void subscribe_sync_failed(std::function<void(bool)>&& f);

    protected:

        RATGDOStore isr_store_ {};
        Protocol* protocol_;
        bool obstruction_from_status_ { false };

        InternalGPIOPin* output_gdo_pin_;
        InternalGPIOPin* input_gdo_pin_;
        InternalGPIOPin* input_obst_pin_;
    }; // RATGDOComponent

} // namespace ratgdo
} // namespace esphome
