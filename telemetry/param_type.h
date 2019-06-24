/*
 * param_type.h
 */

#ifndef TELEMETRY_MAKET_PARAM_TYPE_H_
#define TELEMETRY_MAKET_PARAM_TYPE_H_

#include <stdint.h>
#include <stddef.h>
#include <functional>

namespace telemetry {

/**
	Пример использования:
	#include "telemetry_maket/param_type.h"

	telemetry::PARAM_TYPE type;
	(void) type;
	int x = 2;
	float y = 3;
	double z = 4;
	bool h = 1;
	type = telemetry::get_type(x);
	type = telemetry::get_type(y);
	type = telemetry::get_type(z);
	type = telemetry::get_type(h);
 */

enum class PARAM_TYPE : uint8_t {
	EMPTY		= 0,
	INT8_t		= 1,
	UINT8_t		= 2,
	INT16_t		= 3,
	UINT16_t	= 4,
	INT32_t		= 5,
	UINT32_t	= 6,
	FLOAT 		= 7,
	DOUBLE		= 8
};

template <typename Type>
PARAM_TYPE get_type (const Type& ) {
	return PARAM_TYPE::EMPTY;
}

template<>
PARAM_TYPE get_type <int8_t> (const int8_t&);

template<>
PARAM_TYPE get_type <uint8_t> (const uint8_t&);

template<>
PARAM_TYPE get_type <int16_t> (const int16_t&);

template<>
PARAM_TYPE get_type <uint16_t> (const uint16_t&);

template<>
PARAM_TYPE get_type <int32_t> (const int32_t&);

template<>
PARAM_TYPE get_type <uint32_t> (const uint32_t&);

template<>
PARAM_TYPE get_type <float> (const float&);

template<>
PARAM_TYPE get_type <double> (const double&);

}


#endif /* TELEMETRY_MAKET_PARAM_TYPE_H_ */
