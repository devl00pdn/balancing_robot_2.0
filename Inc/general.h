//
// Created by demid on 24.06.19.
//

#ifndef BALANCING_ROBOT_GENERAL_H
#define BALANCING_ROBOT_GENERAL_H

/**
 * Initialize cpp objects
 */

#include "stdint.h"

#ifdef __cplusplus
extern "C"
{
#endif
void global_initialize_cpp();
void usb_otg_receive_handler(uint8_t *buf, uint32_t len);
#ifdef __cplusplus
}
#endif

#endif //BALANCING_ROBOT_GENERAL_H
