/*
 * buim_telemetry_frame_regulators.h
 *
 *  Created on: Dec 6, 2018
 *      Author: demid
 */

#ifndef BUIM_TELEMETRY_FRAME_REGULATORS_H_
#define BUIM_TELEMETRY_FRAME_REGULATORS_H_

#include "telemetry_frame_base.h"

static const char* regulators_frame_name = "regulators_frame";
static const int regulators_frame_max_params_count = 30;
static const pt_logs::ID_PACKET regulators_frame_id = pt_logs::ID_PACKET::Buim_regulators;

const telemetry::Param_description motor_q_current_d = {
  .name = "motor_q_current",
  .description = "q component of motor current",
  .measure_unit = "norm",
  .min_val = -10000,
  .max_val = 10000
};

const telemetry::Param_description torq_target_d = {
  .name = "torque_target",
  .description = "Desire torque value",
  .measure_unit = "norm",
  .min_val = -10000,
  .max_val = 10000
};

const telemetry::Param_description torq_reg_in_d = {
  .name = "torque_reg_in",
  .description = "Torque regulator input",
  .measure_unit = "norm",
  .min_val = -10000,
  .max_val = 10000
};

const telemetry::Param_description torq_reg_id_out_d = {
  .name = "torque_reg_id_out",
  .description = "Current Id regulator output",
  .measure_unit = "norm",
  .min_val = -1.,
  .max_val = 1.
};

const telemetry::Param_description torq_reg_iq_out_d = {
  .name = "torque_reg_iq_out",
  .description = "Current Iq regulator output",
  .measure_unit = "norm",
  .min_val = -1,
  .max_val = 1
};

const telemetry::Param_description torq_reg_id_err_d = {
  .name = "torque_reg_id_error",
  .description = "Current Id regulator error",
  .measure_unit = "norm",
  .min_val = -1,
  .max_val = 1
};

const telemetry::Param_description torq_reg_iq_err_d = {
  .name = "torque_reg_iq_error",
  .description = "Current Iq regulator error",
  .measure_unit = "norm",
  .min_val = -1,
  .max_val = 1
};

const telemetry::Param_description torq_current_get_error_counter_d = {
  .name = "torque_counter_get_current_error",
  .description = "This increases when current getter return error",
  .measure_unit = "times",
  .min_val = 0,
  .max_val = 0
};

const telemetry::Param_description torq_position_get_error_counter_d = {
  .name = "torque_position_get_error_counter",
  .description = "This increases when position getter return error",
  .measure_unit = "times",
  .min_val = 0,
  .max_val = 0
};

const telemetry::Param_description torq_speed_get_error_counter_d = {
  .name = "torque_speed_get_error_counter",
  .description = "This increases when speed getter return error",
  .measure_unit = "times",
  .min_val = 0,
  .max_val = 0
};

const telemetry::Param_description vel_reg_in_d = {
  .name = "vel_reg_in",
  .description = "none",
  .measure_unit = "none",
  .min_val = 0,
  .max_val = 0
};

const telemetry::Param_description vel_reg_out_d = {
  .name = "vel_reg_out",
  .description = "none",
  .measure_unit = "none",
  .min_val = 0,
  .max_val = 0
};

const telemetry::Param_description vel_reg_err_d = {
  .name = "vel_reg_err",
  .description = "none",
  .measure_unit = "none",
  .min_val = 0,
  .max_val = 0
};

const telemetry::Param_description vel_current_d = {
  .name = "vel_current",
  .description = "none",
  .measure_unit = "none",
  .min_val = 0,
  .max_val = 0
};

const telemetry::Param_description counter_get_speed_err_d = {
  .name = "counter_get_speed_err",
  .description = "none",
  .measure_unit = "none",
  .min_val = 0,
  .max_val = 0
};

const telemetry::Param_description target_pos_d = {
  .name = "target_pos",
  .description = "none",
  .measure_unit = "none",
  .min_val = 0,
  .max_val = 0
};

const telemetry::Param_description current_pos_d = {
  .name = "current_pos",
  .description = "none",
  .measure_unit = "none",
  .min_val = 0,
  .max_val = 0
};

const telemetry::Param_description position_error_d = {
  .name = "position_error",
  .description = "none",
  .measure_unit = "none",
  .min_val = 0,
  .max_val = 0
};

const telemetry::Param_description position_reg_out_d = {
  .name = "position_reg_out",
  .description = "none",
  .measure_unit = "none",
  .min_val = 0,
  .max_val = 0
};

const telemetry::Param_description position_not_valid_d = {
  .name = "position_not_valid",
  .description = "none",
  .measure_unit = "none",
  .min_val = 0,
  .max_val = 0
};

const telemetry::Param_description set_target_velocity_error_d = {
  .name = "set_target_velocity_error",
  .description = "none",
  .measure_unit = "none",
  .min_val = 0,
  .max_val = 0
};

const telemetry::Param_description get_position_error_d = {
  .name = "get_position_error",
  .description = "none",
  .measure_unit = "none",
  .min_val = 0,
  .max_val = 0
};

const telemetry::Param_description sim_iteration_time_us_d = {
  .name = "sim_iter_time",
  .description = "none",
  .measure_unit = "us",
  .min_val = 0,
  .max_val = 0
};


class Regulators_telemetry_frame: public telemetry::Frame<regulators_frame_max_params_count>{
public:
  Regulators_telemetry_frame():
    telemetry::Frame<regulators_frame_max_params_count>(regulators_frame_id, regulators_frame_name),
    motor_q_current(motor_q_current_d, this),
    torq_target(torq_target_d, this),
    torq_reg_in(torq_reg_in_d, this),
    torq_reg_id_out(torq_reg_id_out_d, this),
    torq_reg_iq_out(torq_reg_iq_out_d, this),
    torq_id_err(torq_reg_id_err_d, this),
    torq_iq_err(torq_reg_iq_err_d, this),
    torq_current_get_error_counter(torq_current_get_error_counter_d, this),
    torq_position_get_error_counter(torq_position_get_error_counter_d, this),
    torq_speed_get_error_counter(torq_speed_get_error_counter_d, this),
    vel_reg_in(vel_reg_in_d, this),
    vel_reg_out(vel_reg_out_d,this),
    vel_reg_err(vel_reg_err_d, this),
    vel_current(vel_current_d, this),
    counter_get_speed_err(counter_get_speed_err_d, this),
    target_pos(target_pos_d, this),
    current_pos(current_pos_d, this),
    position_error(position_error_d, this),
    position_reg_out(position_reg_out_d, this),
    position_not_valid(position_not_valid_d, this),
    get_position_error(get_position_error_d, this),
    set_target_velocity_error(set_target_velocity_error_d, this),
    sim_iteration_time_us(sim_iteration_time_us_d, this)
  {}

  telemetry::Parameter<float> motor_q_current;
  telemetry::Parameter<float> torq_target;
  telemetry::Parameter<float> torq_reg_in;
  telemetry::Parameter<float> torq_reg_id_out;
  telemetry::Parameter<float> torq_reg_iq_out;
  telemetry::Parameter<float> torq_id_err;
  telemetry::Parameter<float> torq_iq_err;
  telemetry::Parameter<uint32_t> torq_current_get_error_counter;
  telemetry::Parameter<uint32_t> torq_position_get_error_counter;
  telemetry::Parameter<uint32_t> torq_speed_get_error_counter;

  telemetry::Parameter<float> vel_reg_in;
  telemetry::Parameter<float> vel_reg_out;
  telemetry::Parameter<float> vel_reg_err;
  telemetry::Parameter<float> vel_current;
  telemetry::Parameter<uint32_t> counter_get_speed_err;

  telemetry::Parameter<float> target_pos;
  telemetry::Parameter<float> current_pos;
  telemetry::Parameter<float> position_error;
  telemetry::Parameter<float> position_reg_out;
  telemetry::Parameter<uint32_t> position_not_valid;
  telemetry::Parameter<uint32_t> get_position_error;
  telemetry::Parameter<uint32_t> set_target_velocity_error;
  telemetry::Parameter<uint32_t> sim_iteration_time_us;
};


#endif /* BUIM_TELEMETRY_FRAME_REGULATORS_H_ */
