/*
 * buim_telemetry_frame_regulators.h
 *
 *  Created on: Dec 6, 2018
 *      Author: demid
 */

#ifndef BUIM_TELEMETRY_FRAME_REGULATORS_H_
#define BUIM_TELEMETRY_FRAME_REGULATORS_H_

#include "telemetry_frame_base.h"
#include "stdint.h"

static const char* regulators_frame_name = "regulators_frame";
static const int regulators_frame_max_params_count = 30;
static const uint8_t regulators_frame_id = 1;

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


class Regulators_telemetry_frame: public telemetry::Frame<regulators_frame_max_params_count>{
public:
  Regulators_telemetry_frame():
    telemetry::Frame<regulators_frame_max_params_count>(regulators_frame_id, regulators_frame_name),
    motor_q_current(motor_q_current_d, this),
    torq_target(torq_target_d, this)
  {}

  telemetry::Parameter<float> motor_q_current;
  telemetry::Parameter<float> torq_target;
};


#endif /* BUIM_TELEMETRY_FRAME_REGULATORS_H_ */
