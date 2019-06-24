//
// Created by demid on 24.06.19.
//

#include "general.h"
#include <string>
#include "cobs_ex.h"
#include "commander.h"

Commander commander;

void global_initialize_cpp(){
    commander.init();
}

void usb_otg_receive_handler(uint8_t *buf, uint32_t len){
    uint8_t decoded_msg[1024] = {0};
    int result = cobs_ex::cobs_decode(buf, len, decoded_msg);
    if(!result)
        return;

    commander.handle(buf, len);
}

