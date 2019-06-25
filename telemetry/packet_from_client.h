/*
 * packet_from_scat.h
 */

#ifndef TELEMETRY_PACKET_FROM_CLIENT_H_
#define TELEMETRY_PACKET_FROM_CLIENT_H_

#include  <algorithm>
#include "telemetry_packets.h"

namespace telemetry {

struct Heartbeat : public base_packet {
    // Конструктор по умолчанию
	Heartbeat() :
		base_packet(COMMAND::HEARTBEAT),
		frame_id(0) {
    }

    Heartbeat(uint16_t sys_id_, uint8_t frame_id_):
    	base_packet(COMMAND::HEARTBEAT, sys_id_),
		frame_id(frame_id_) {
    }

    uint8_t frame_id; // id кадра который мы слушаем
} __attribute__((packed));

struct Request_count_of_frames_packet : public base_packet {
    // Конструктор по умолчанию
	Request_count_of_frames_packet() :
		base_packet(COMMAND::REQUEST_COUNT_OF_FRAMES) {
    }

} __attribute__((packed));

struct Request_frame_packet : public base_packet {
    // Конструктор по умолчанию
	Request_frame_packet() :
		base_packet(COMMAND::REQUEST_FRAME),
		frame_seq(0) {
    }

	uint16_t frame_seq;
} __attribute__((packed));

struct Request_parameter_packet : public base_packet {
    // Конструктор по умолчанию
	Request_parameter_packet() :
		base_packet(COMMAND::REQUEST_PARAMETER),
		frame_seq(0),
		param_seq(0) {
    }

	uint16_t frame_seq;
	uint16_t param_seq;
} __attribute__((packed));

struct Disconnect_packet : public base_packet {
    // Конструктор по умолчанию
	Disconnect_packet() :
		base_packet(COMMAND::DISCONNECT),
		frame_id(0) {
    }

	// Конструктор с параметрами
    Disconnect_packet(uint16_t sys_id_, uint8_t frame_id_):
		base_packet(COMMAND::DISCONNECT, sys_id_),
		frame_id(frame_id_) {
    }

    uint8_t frame_id; // id кадра который мы слушаем
} __attribute__((packed));

static constexpr uint32_t MAX_SCAT_PACKET_LENGTH =
			std::max({sizeof(Heartbeat), sizeof(Request_count_of_frames_packet),
						sizeof(Request_frame_packet), sizeof(Request_parameter_packet),
						sizeof(Disconnect_packet)});


}

#endif /* _TELEMETRY_PACKET_FROM_SCAT_H_ */
