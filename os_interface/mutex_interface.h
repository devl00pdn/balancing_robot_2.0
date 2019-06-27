//
// Created by demid on 26.06.19.
//

#ifndef BALANCING_ROBOT_MUTEX_INTERFACE_H
#define BALANCING_ROBOT_MUTEX_INTERFACE_H

#include "cmsis_os.h"

namespace os_interface{

/// only for dynamic allocation
class Mutex{
public:
    Mutex(){
       const osMutexDef_t cfg = {0, nullptr};
       mut_id = osMutexCreate(&cfg);
    }

    ~Mutex(){
        if(mut_id)
            osMutexDelete(mut_id);
    }

    bool lock(){
        bool rv = false;
        if(!mut_id){
            return rv;
        }
        if(osMutexWait(mut_id, osWaitForever) == osOK){
            rv = true;
        }
        return rv;
    }

    bool unlock(){
        bool rv = false;
        if(!mut_id){
            return rv;
        }
        if(osMutexRelease(mut_id) == osOK){
            rv = true;
        }
        return rv;
    }

private:
    osMutexId mut_id = nullptr;
};

}

#endif //BALANCING_ROBOT_MUTEX_INTERFACE_H
