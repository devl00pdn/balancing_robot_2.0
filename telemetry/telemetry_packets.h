/*
 * telemetry_packets.h
 *
 *  Created on: Nov 16, 2018
 *      Author: demid
 */

#ifndef TELEMETRY_PACKETS_H_
#define TELEMETRY_PACKETS_H_

#include <stdint.h>

namespace telemetry {

/*
	Как происходит считывание всех фреймов:

	SCAT |														| UAV
		 |														|
		 |	---	COMMAND:REQUEST_COUNT_OF_FRAMES -------------->	|
		 |	 		 											|
		 |	<--	COMMAND:COUNT_OF_FRAMES .count = 3 ----------	|
		 |	 		 											|
		 |	---	COMMAND:REQUEST_FRAME	.seq = 0				|
		 |	 		 											|
		 |	<--	COMMAND:FRAME 		.seq = 0, -----------------	|
		 |	 	 	 	 	 	 	 .id = ID_PACKET			|
		 |							.name = "",					|
		 |							.count_of_params = ,		|
		 |							.size_of_struct = 			|
		 |	 		 											|
		 |	---	COMMAND:REQUEST_PARAMETER						|
		 | 	 	 	 	 	 	 	 .frame_id = 0,				|
		 |							.seq = 0 ----------------->	|
		 |	 		 											|
		 |	<--	COMMAND:PARAM		.frame_id = 0, -----------	|
		 |							.seq = 0,					|
		 |							.offset = ,					|
		 |	 	 	 	 	 	 	.type = PARAM_TYPE,			|
		 |	 	 	 	 	 	 	.size = size (bytes),		|
		 |							.min_value = ,				|
		 |	 	 	 	 	 	 	.max_value = 				|
		 |							.name = "",					|
		 |							.desc = "",					|
		 |							.measure = ""				|
		 |	 		 											|
		 |	---	COMMAND:REQUEST_PARAMETER						|
		 |							.frame_id = 0,				|
		 |							.seq = 1 ----------------->	|
		 |	 		 											|
		 |	<--	COMMAND:PARAM		.frame_id = 0, ------------	|
		 |							.seq = 1,					|
		 |							.offset = ,					|
		 | 	 	 	 	 	 	 	.type = PARAM_TYPE,			|
		 |	 	 	 	 	 	 	.size = size (bytes),		|
		 |							.min_value = ,				|
		 | 	 	 	 	 	 	 	.max_value = 				|
		 |							.name = "",					|
		 |							.desc = "",					|
		 |							.measure = ""				|

		.....

 */

static constexpr uint16_t MAX_LISTENERS_COUNT			= 4; ///<
static constexpr uint16_t MAX_NAME_LENGTH 				= 100; ///<
static constexpr uint16_t MAX_DESC_LENGTH 				= 100; ///<
static constexpr uint16_t MAX_MEASURE_LENGTH 			= 50; ///<
static constexpr uint16_t RX_SKAT_COMMAND_PORT   		= 14557; ///< Порт для ответа на запросы от ската
static constexpr uint16_t RX_SKAT_TELEMETRY_PORT 		= 14556; ///< Порт для передачи потока телеметрии в скат
static constexpr uint16_t RX_UAV_PORT					= 14555; ///< Порт для передачи комманд и запросов на борт
static constexpr uint32_t HEARTBEAT_FREQUENCY			= 1;
static constexpr uint32_t SUBSCRIPTION_RELEVANCE_TIME	= 5; 	///< Время действия подписки (секунды)

enum class COMMAND : uint16_t {
	EMPTY 					= 0,
	HEARTBEAT 				= 1,
	COMMAND_STATUS			= 2,
	REQUEST_COUNT_OF_FRAMES = 3,
	COUNT_OF_FRAMES			= 4,
	REQUEST_FRAME			= 5,
	FRAME					= 6,
	REQUEST_PARAMETER		= 7,
	PARAMETER				= 8,
	DISCONNECT				= 9
};

enum class PROCESSING_RESULT : uint8_t {
	EMPTY						= 0, // Значение по умолчанию
	ACCEPTED					= 1, // Команда успешно принята
	DECLINED_MAX_SUBS			= 2, // Команда отклонена, максимальное кол-во подписчиков
	DECLINED_UNKNOWN_FRAME_SEQ	= 3, // Команда отклонена, неизвестный порядковый номер фрейма
	DECLINED_UNKNOWN_FRAME_ID	= 4, // Команда отклонена, неизвестный идентификатор фрейма
	DECLINED_UNKNOWN_PARAM_SEQ	= 5, // Команда отклонена, неизвестный порядковый параметра
	DECLINED_NOT_RECOGNIZED_CMD	= 6  // Неизвестная команда
};

struct base_packet {
	base_packet () :
		cmd(COMMAND::EMPTY),
		system_id(0) {
	}

	base_packet (const COMMAND& packet_cmd) :
		cmd(packet_cmd),
		system_id(0) {
	}

	base_packet (const COMMAND& packet_cmd, const uint16_t& fact_sys_id) :
		cmd(packet_cmd),
		system_id(fact_sys_id) {
	}

	const COMMAND 	cmd;
	const uint16_t 	system_id;
} __attribute__((packed));

}  // namespace telemetry

#endif /* TELEMETRY_PACKETS_H_ */
