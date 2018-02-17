#include "stdafx.h"
#include <ctime>
#include <iostream>
#include <string>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include "flatbuffers/flatbuffers.h"
#include <fstream>
#include "terrain-navigator.h"
#include "player-location.h"

using boost::asio::ip::udp;

class udp_server
{
public:
	udp_server(boost::asio::io_service& io_service, PlayerLocationHandler plh)
		: socket_(io_service, udp::endpoint(udp::v4(), 33333)), plh_(plh)
	{
		start_receive();
	}

private:
	void start_receive()
	{
		socket_.async_receive_from(
			boost::asio::buffer(recv_buffer_),
			remote_endpoint_,
			boost::bind(
				&udp_server::handle_receive,
				this,
				boost::asio::placeholders::error
				));
	}

	/*uint8_t* findStart(uint8_t *buf) {
		for (int i = 0; i < 1024; i++) {
			if (buf[i] != 0) {
				return &buf[i];
			}
		}

		return buf;
	}*/

	void handle_receive(const boost::system::error_code& error)
	{
		if (!error || error == boost::asio::error::message_size)
		{
			uint8_t *buf = recv_buffer_.data();
			//uint8_t *start = findStart(buf);

			const char * identifier = flatbuffers::GetBufferIdentifier(buf);

			if (std::strcmp(identifier, TransferObjects::PlayerLocationIdentifier())) {
				socket_.async_send_to(
					plh_.handle(buf),
					remote_endpoint_,
					boost::bind(
						&udp_server::handle_send,
						this));
			}

			start_receive();
		}
	}

	void handle_send()
	{
		std::cout << "sent";
	}
	PlayerLocationHandler plh_;
	udp::socket socket_;
	udp::endpoint remote_endpoint_;
	boost::array<uint8_t, 1024> recv_buffer_;
};

int main()
{
	try
	{
		// call db for state of game
		// load previous player locations

		// load terrain
		TerrainNavigator navigator;

		navigator.loadMesh("terrain.navmesh");

		// create handlers
		PlayerLocationHandler plh(navigator);
		
		// create agents

		// start tcp and udp servers
		boost::asio::io_service io_service;
		udp_server server(io_service, plh);
		io_service.run();
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}