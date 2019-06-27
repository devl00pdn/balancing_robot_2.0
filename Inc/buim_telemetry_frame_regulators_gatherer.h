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
#include "os_interface.h"

// Кадр который содержит в себе аналитическую информацию о работе регуляторов

class Regulator_frame: public Updater_base{
 public:
    template<int N>
    Regulator_frame(const Updater_base::source (&sources_table)[N]): Updater_base{sources_table}{}
    Regulator_frame() = delete;
    // datasources
    bool update();
    Regulators_telemetry_frame raw_frame;

 private:
    os_interface::Mutex raw_frame_mutex;
};

inline bool Regulator_frame::update() {
    bool rv = false;
    if(!Updater_base::update_()){
        return false;
    }
    raw_frame_mutex.lock();
    raw_frame_mutex.unlock();
    rv = true;
    return rv;
}

#endif /* BUIM_TELEMETRY_FRAME_REGULATORS_GATHERER_H_ */
