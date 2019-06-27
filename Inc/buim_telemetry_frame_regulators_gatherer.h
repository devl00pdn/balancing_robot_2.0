/*
 * buim_telemetry_frame_regulators_gatherer.h
 *
 *  Created on: Dec 6, 2018
 *      Author: demid
 */

#ifndef BUIM_TELEMETRY_FRAME_REGULATORS_GATHERER_H_
#define BUIM_TELEMETRY_FRAME_REGULATORS_GATHERER_H_

#include <stdint.h>

#include "buim_telemetry_frame_regulators.h"

#include "data_generator.h"
#include "buim_torque_controller.h"
#include "buim_velocity_controller.h"
#include "buim_position_controller.h"

// Кадр который содержит в себе аналитическую информацию о работе регуляторов

class Regulator_frame: public Updater_base{
 public:
    template<int N>
    Regulator_frame(const Updater_base::source (&sources_table)[N]): Updater_base{sources_table}{}
    Regulator_frame() = delete;
    // datasources
    buim::Torque_controller::statistic torque_reg_stat;
    buim::Torque_controller::telemetry torque_reg_tm;
    buim::Velocity_controller::statistic vel_reg_stat;
    buim::Velocity_controller::telemetry vel_reg_tm;
    buim::Position_controller::statistic pos_reg_stat;
    buim::Position_controller::telemetry pos_reg_tm;
    bool update();
    Regulators_telemetry_frame raw_frame;

 private:
    ptos::Mutex raw_frame_mutex;

};

#endif /* BUIM_TELEMETRY_FRAME_REGULATORS_GATHERER_H_ */
