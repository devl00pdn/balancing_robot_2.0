/*
 * param_type.cpp
 */


#include "param_type.h"

namespace telemetry {
template<>
PARAM_TYPE get_type <int8_t> (const int8_t&) {
  return PARAM_TYPE::INT8_t;
}

template<>
PARAM_TYPE get_type <uint8_t> (const uint8_t&) {
  return PARAM_TYPE::UINT8_t;
}

template<>
PARAM_TYPE get_type <int16_t> (const int16_t&) {
  return PARAM_TYPE::INT16_t;
}

template<>
PARAM_TYPE get_type <uint16_t> (const uint16_t&) {
  return PARAM_TYPE::UINT16_t;
}

template<>
PARAM_TYPE get_type <int32_t> (const int32_t&) {
  return PARAM_TYPE::INT32_t;
}

template<>
PARAM_TYPE get_type <uint32_t> (const uint32_t&) {
  return PARAM_TYPE::UINT32_t;
}

template<>
PARAM_TYPE get_type <float> (const float&) {
  return PARAM_TYPE::FLOAT;
}

template<>
PARAM_TYPE get_type <double> (const double&) {
  return PARAM_TYPE::DOUBLE;
}
}
