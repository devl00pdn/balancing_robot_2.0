/*
 * Frame_base.h
 *
 *  Created on: Nov 15, 2018
 *      Author: demid
 */

#ifndef Frame_base_H_
#define Frame_base_H_

#include <string.h>
#include <typeinfo>
#include "packet_from_server.h"
#include "param_type.h"
#include <array>

namespace telemetry{

struct Packet_header {
    Packet_header (uint8_t current_id) :
            id(current_id),
            time(0),
            system_id(0),
            component_id(0) {
    }

    const uint8_t id;
    uint32_t time; // ms
    uint16_t system_id;
    uint16_t component_id;
} __attribute__((packed));

struct Param_description{
  const char *name;
  const char *description;
  const char *measure_unit;
  float min_val; // минимальное значение по которому ограничивается параметр и маштабируется окно ската
  float max_val; // максимальное значение по которому ограничивается параметр и маштабируется окно ската
};

class Parametr_base{
 public:
  Parametr_base(){};
  virtual ~Parametr_base(){};
  virtual void *get_val_ptr() = 0;
  virtual int get_value_size_byte() = 0;
  virtual PARAM_TYPE get_value_type() = 0;
  virtual float get_min_value() = 0;
  virtual float get_max_value() = 0;
  virtual const char* get_name() = 0;
  virtual const char* get_description() = 0;
  virtual const char* get_measure_unit() = 0;
};

class Frame_base{
 public:
  virtual ~Frame_base(){};
  virtual void registration(Parametr_base *p) = 0;
  virtual size_t get_binary_size(void) = 0;
  virtual int get_registered_params_count(void) = 0;
  virtual uint8_t get_id() = 0;
  virtual const char* get_name() = 0;
  virtual bool fill_parameter_of_frame_discription(int param_num, Parameter_packet &d) = 0;
};

template <typename T>
class Parameter: public Parametr_base{
 public:
  Parameter(const Param_description &desc_, Frame_base *tm): desc(desc_), value(0)
 {
    tm->registration(this);
    type = telemetry::get_type(value);
 }
  const Param_description &desc;

  void set(T new_val){value = new_val;}

  T get(){return value;}

  void operator=(T &val) {
       this->value = val;
  }

 private:
  void *get_val_ptr(){
    return static_cast<void*>(&value);
  }
  int get_value_size_byte(){
    return sizeof(value);
  }

  float get_min_value(){
    return desc.min_val;
  }

  float get_max_value(){
    return desc.max_val;
  }

  const char* get_name(){
    return desc.name;
  }

  const char* get_description(){
    return desc.description;
  }

  const char* get_measure_unit(){
    return desc.measure_unit;
  }

  PARAM_TYPE get_value_type(){
    return type;
  }

  T value;
  PARAM_TYPE type;
};

template <int max_param>
class Frame_registrator: public Frame_base{
 public:
  virtual ~Frame_registrator(){};

  int get_registered_params_count(){
    return counter_of_registred_parameters;
  }

  Parametr_base* get_param(int param_num){
    if(param_num < 0 || param_num >= counter_of_registred_parameters){
      return nullptr; // Попытка переполнения
    }
    return params[param_num];
  }

  void registration(Parametr_base *p){
    if(counter_of_registred_parameters >= max_param){
      return; // Попытка переполнения
    }
    params[counter_of_registred_parameters] = p;
    counter_of_registred_parameters++;
  };

  int counter_of_registred_parameters = 0;
  std::array<Parametr_base*, max_param> params;

};

template <int max_param>
class Frame: public Frame_registrator<max_param>{
 public:

  Frame(uint8_t id_, const char *name_): name(name_), head(id_){}
  ~Frame(){}

  const char* name;
  void set_time( uint64_t time){
    head.time = time;
  }

  void set_sysid(uint16_t sysid){
    head.system_id = sysid;
  }

  void set_compid(uint16_t compid){
    head.component_id = compid;
  }

  int get_parameters_count(){
    return this->get_registered_params_count();
  }

  size_t get_binary_size(void){
    size_t frame_bin_size = sizeof(head);
    for(int i = 0; i < this->counter_of_registred_parameters; i++){
      frame_bin_size += this->params[i]->get_value_size_byte();
    }
    return frame_bin_size;
  }

  bool get_bias_from_begining(int param_num_, size_t &bites){
    size_t sol = sizeof(head);

    if(param_num_ < 0 || param_num_ >= this->get_registered_params_count()){
      return false;
    }

    for(int i = 0; i < param_num_; i++){
      sol += this->params[i]->get_value_size_byte();
    }
    bites = sol;
    return true;
  }

  Frame_base* get_base(){
      return this;
  }

  // return frame binary size in bufer or -1 if error
  int to_binary(void *buff, int buff_size){
    uint8_t *buff_prt = (uint8_t*)buff;
    int rv = -1;
    // получаем общий размер требуемого буфера под все параметры
    int frame_bin_size = get_binary_size();
    // если буфер меньше чем размер всех параметров
    if(buff_size < frame_bin_size){
      return rv;
    }
    // копируем заголовок кадра
    memcpy(buff_prt, &head, sizeof(head));
    buff_prt += sizeof(head);
    // Копируем занчения параметров в бинарном виде
    for(int i = 0; i < this->counter_of_registred_parameters; i++){
      Parametr_base *pararm = this->params[i];
      memcpy(buff_prt, pararm->get_val_ptr(), pararm->get_value_size_byte());
      buff_prt += pararm->get_value_size_byte();
    }
    rv = frame_bin_size;
    return rv;
  }

  uint8_t get_id(){
    return this->head.id;
  }

  const char* get_name(){
    return this->name;
  }

  bool fill_parameter_of_frame_discription(int param_num, Parameter_packet &d){
    bool rv = false;
    size_t bias = 0;
    if(!get_bias_from_begining(param_num, bias)){
      return false;
    }
    Parametr_base *p = this->get_param(param_num);
    if(!p){
      return false;
    }

    d.param_seq = param_num;
    d.param_offset = bias;
    d.param_size = p->get_value_size_byte();
    d.param_type = p->get_value_type();
    d.param_min_value = p->get_min_value();
    d.param_max_value = p->get_max_value();
    strncpy(d.param_name, p->get_name(), sizeof(d.param_name)-1);
    strncpy(d.param_desc, p->get_description(), sizeof(d.param_desc)-1);
    strncpy(d.param_measure, p->get_measure_unit(), sizeof(d.param_measure)-1);
    rv = true;
    return rv;
  }

 private:
  Packet_header head;  // идентефикатор кадра
};

} // namespace telemetry

#endif /* Frame_base_H_ */
