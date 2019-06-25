/*
 * telemetry.h
 *
 *  Created on: Nov 16, 2018
 *      Author: demid
 */

#ifndef TELEMETRY_BASE_H_
#define TELEMETRY_BASE_H_

#include <string.h>
#include "telemetry_frame_base.h"
#include "telemetry_packets.h"
#include <array>

namespace telemetry{

template <int max_frame_count>
class Telemetry_registrator{
 public:

  ~Telemetry_registrator(){};

  typedef uint8_t frame_id_t;

  struct storage_cell{
    Frame_base *frame;
    frame_id_t id;
  };

  bool to_register(Frame_base *frame){
    if(registered_frame_count >= max_frame_count){
      return false;
    }

    // проверка на то что кадр уже зарегистрирован
    if(get_frame_by_id(frame->get_id()) != nullptr){
      return false;
    }

    storage[registered_frame_count].frame = frame;
    storage[registered_frame_count].id = frame->get_id();
    registered_frame_count++;
    return true;
  }

  Frame_base* get_frame_by_id(frame_id_t id_){
    Frame_base* rv = nullptr;
    for(int i = 0; i < registered_frame_count; i++){
      if(storage[i].id == id_){
        rv =  storage[i].frame;
      }
    }
    return rv;
  }

  // num_ начиная с 0
  Frame_base* get_frame_by_num(int num_){
    Frame_base* rv = nullptr;
    if(num_ >= registered_frame_count || num_ < 0){
      return nullptr;
    }else{
      rv = storage[num_].frame;
    }
    return rv;
  }

  int get_total_frame_number(){
    return registered_frame_count;
  }

 private:
  int registered_frame_count = 0;
  std::array<storage_cell, max_frame_count> storage;

};

// singltone
template <int max_frame_count>
class Telemetry_base: public Telemetry_registrator<max_frame_count>{
 public:
  Telemetry_base(){};
  ~Telemetry_base(){};

  //frame_num_ начиная с 0 до get_total_frame_number() включительно
  bool fill_frame_lable(int frame_num_, Frame_packet &d){
    bool rv = false;
    Frame_base *f = this->get_frame_by_num(frame_num_);
    if(!f){
      // кадр не найден
      return false;
    }
    d.size_of_data_frame = f->get_binary_size();
    d.frame_id = f->get_id();
    d.frame_seq = frame_num_;
    d.count_of_parameters = f->get_registered_params_count();
    strncpy(d.frame_name, f->get_name(), sizeof(d.frame_name)-1);
    rv = true;
    return rv;
  }

  bool fill_parameter_discript(int frame_num_, int param_num_, Parameter_packet &d){
    bool rv = false;
    Frame_base *f = this->get_frame_by_num(frame_num_);
    if(!f){
      // кадр не найден
      return false;
    }

    d.frame_seq = frame_num_;
    if(!f->fill_parameter_of_frame_discription(param_num_, d)){
      return false;
    } else {
      rv = true;
    }

    return rv;
  }

 private:


};

} //namespace telemetry


#endif /* TELEMETRY_BASE_H_ */
