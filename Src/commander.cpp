//
// Created by demid on 24.06.19.
//

#include <commander.h>
#include "telemetry_packets.h"
#include "telemetry_frame_regulators.h"
#include "telemetry_frame_regulators_gatherer.h"

// здесь должны быть файлы протокола телеметрии

void Commander::handle(uint8_t *decoded_msg, uint32_t msg_len) {
    if(!inited)
        return;

    if(msg_len < sizeof(telemetry::base_packet))
        return;

    telemetry::base_packet *header = reinterpret_cast<telemetry::base_packet*> (decoded_msg);
}

bool Commander::is_inited() {
    return inited;
}

void Commander::init() {
    inited = true;
}

