/*
 * packet_from_uav.h
 */

#ifndef TELEMETRY_PACKET_FROM_SERVER_H_
#define TELEMETRY_PACKET_FROM_SERVER_H_
#include <algorithm>
#include "param_type.h"
#include "telemetry_packets.h"

namespace telemetry {

struct base_uav_packet : public base_packet {
	base_uav_packet (const COMMAND& packet_cmd) :
		base_packet(packet_cmd),
		component_id(0) {
	}

	const uint16_t 		component_id;
} __attribute__((packed));

struct Count_of_frames_packet : public base_uav_packet {
	Count_of_frames_packet () :
		base_uav_packet(COMMAND::COUNT_OF_FRAMES),
		count_of_frames(0) {

	}

	uint16_t 			count_of_frames;
} __attribute__((packed));

struct Frame_packet : public base_uav_packet {
	Frame_packet () :
		base_uav_packet(COMMAND::FRAME),
		frame_seq(0),
		frame_id(0),
		count_of_parameters(0),
		size_of_data_frame(0),
		frame_name{'\0'} {
	}

	uint8_t 			frame_seq;
	uint8_t         	frame_id;
	uint16_t 			count_of_parameters;
	uint16_t 			size_of_data_frame;
	char 				frame_name[MAX_NAME_LENGTH];
} __attribute__((packed));

struct Parameter_packet : public base_uav_packet {
	Parameter_packet () :
		base_uav_packet(COMMAND::PARAMETER),
		frame_seq(0),
		param_seq(0),
		param_offset(0),
		param_type(PARAM_TYPE::EMPTY),
		param_size(0),
		param_min_value(0),
		param_max_value(0),
		param_name{'\0'},
		param_desc{'\0'},
		param_measure{'\0'} {
	}

	uint8_t 	  		frame_seq;							///< Порядковый номер полученный при регистрации frame на борту
	uint16_t 	  		param_seq;							///< Порядковый номер полученный при регистрации param в frame на борту
	uint16_t 	  		param_offset;
	PARAM_TYPE			param_type;
	uint8_t		 		param_size;
	float				param_min_value;
	float				param_max_value;
	char 				param_name[MAX_NAME_LENGTH];
	char 				param_desc[MAX_DESC_LENGTH];
	char 				param_measure[MAX_MEASURE_LENGTH];
} __attribute__((packed));

struct Command_status_packet : public base_uav_packet {
	Command_status_packet () :
		base_uav_packet(COMMAND::COMMAND_STATUS),
		processing_cmd (COMMAND::EMPTY),
		result (PROCESSING_RESULT::EMPTY) {
	}

	COMMAND 			processing_cmd;
	PROCESSING_RESULT 	result;
} __attribute__((packed));


static constexpr uint32_t MAX_UAV_PACKET_LENGTH = std::max({sizeof(Count_of_frames_packet), sizeof(Frame_packet),
						sizeof(Parameter_packet)});

}

#endif /* TELEMETRY_PACKET_FROM_UAV_H_*/
