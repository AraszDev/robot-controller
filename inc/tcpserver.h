/*
 * tcpserver.h
 *
 *  Created on: Dec 29, 2015
 *      Author: rafal
 */

#ifndef TCPSERVER_H_
#define TCPSERVER_H_

#include <sys/socket.h>
#include <sys/types.h>
#include <sys/unistd.h>
#include <netinet/in.h>
#include <iostream>
#include <string>
#include "tcp_server_exception.h"
#include <functional>
#include <cstring>
#include <vector>
//#include <thread>
#include <errno.h>
#include "ifile_descriptor_owner.h"
#include <mutex>
#include "file_descriptor_handler.h"
#include "idata_ready.h"


// TODO Create new class for connected clients
namespace mr
{

class tcp_server: public ifile_descriptor_owner, public idata_ready
{

public:

	tcp_server();
	tcp_server(int port);
	virtual ~tcp_server();

	//void send_data(char* buffer, int length);
	void send_data(const std::vector<char>&buffer);
	void receive_data(std::vector<char>&buffer);

	bool is_connected() const;
	void reconnect();

	void subscribe_data_ready_event(delegate&& data_ready_handler);
	void unsubscribe_data_ready_event();

	virtual void on_data_ready() override;
	virtual file_descriptor_handler& get_file_descriptor_handler() override;


private:
	void create_socket();
	void bind_socket(int port);
	void listen_for_connection();
	void accept_connection();

	void read_data();


	bool _is_data_ready_event_subscirbed = false; /// indicates if data ready event is subscribed

	bool _is_connected = false; /// indicates if client is connected to the server

	const size_t _buffer_size = 50; /// communication buffer size
	char _system_interaction_buffer[50]{}; /// data buffer which will be passed to system functions
	std::vector<char> _received_data_buffer; ///
	std::mutex _buffer_mutex;

	file_descriptor_handler _listen_socket{-3}; /// server socket file descriptor
	int _port = 22222; /// port on which server listens

	sockaddr_in _client_addres; /// connected client address
	file_descriptor_handler _client_socket{-3}; /// socket used for communication which connected client

};

} /* namespace mrobot */

#endif /* TCPSERVER_H_ */
