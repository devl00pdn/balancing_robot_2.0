//
// Created by demid on 24.06.19.
//

#ifndef BALANCING_ROBOT_COMMANDER_H
#define BALANCING_ROBOT_COMMANDER_H

#include "stdint.h"

class Commander{
public:
    void init();
    bool  is_inited();
    void handle(uint8_t *decoded_msg, uint32_t msg_len);

private:
    bool inited = false;
};
#endif //BALANCING_ROBOT_COMMANDER_H
