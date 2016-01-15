/*
 * robot_controller.h
 *
 *  Created on: Jan 11, 2016
 *      Author: rafal
 */

#ifndef INC_ROBOT_CONTROLLER_H_
#define INC_ROBOT_CONTROLLER_H_

#include <vector>
#include "tcpserver.h"
#include "serial_port.h"
#include "camera_application.h"
#include "poll_controler.h"
#include <exception>
#include <iterator>

namespace mrobot
{
	class robot_controller
	{
	public:
		robot_controller();
		robot_controller(const robot_controller& ) =delete;// copy constructor deleted
		robot_controller(std::string serial_device, std::string camera_script_path="", int port = 22222);
		virtual ~robot_controller();

		void start_controler();

	private:
		poll_controler _poll_controller; /// polls used file descriptors for data to read

		tcp_server* _server;
		unsigned int _tcp_buffer_size = 255; /// size of tcp buffer
		std::vector<char> _tcp_buffer{static_cast<char>(_tcp_buffer_size), 0}; /// buffer for data from server
		std::function<void(tcp_server&, std::vector<char>&)> _server_data_ready_event_handler;
		void server_event_handler(tcp_server& server, std::vector<char>& buffer);

		serial_port* _serial_device;
		unsigned int _serial_buffer_size = 20;
		std::vector<char> _serial_buffer{static_cast<char>(_serial_buffer_size), 0};
		std::function<void(serial_port&, std::vector<char>&)> _serial_data_ready_event_handler;
		void serial_event_handler(serial_port& server, std::vector<char>& buffer);

		camera_application _camera_app;
		void start_camera_app(std::string _camera_script_path);
	};
}



#endif /* INC_ROBOT_CONTROLLER_H_ */
