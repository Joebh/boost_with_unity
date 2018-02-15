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
#include "generated\player-location_generated.h"
#include <fstream>

using boost::asio::ip::tcp;
using boost::asio::ip::udp;

std::string make_daytime_string()
{
	return "asdf";
}

class tcp_connection
	: public boost::enable_shared_from_this<tcp_connection>
{
public:
	typedef boost::shared_ptr<tcp_connection> pointer;

	static pointer create(boost::asio::io_service& io_service)
	{
		return pointer(new tcp_connection(io_service));
	}

	tcp::socket& socket()
	{
		return socket_;
	}

	void start()
	{
		message_ = make_daytime_string();

		boost::asio::async_write(socket_, boost::asio::buffer(message_),
			boost::bind(&tcp_connection::handle_write, shared_from_this()));
	}

private:
	tcp_connection(boost::asio::io_service& io_service)
		: socket_(io_service)
	{
	}

	void handle_write()
	{
	}

	tcp::socket socket_;
	std::string message_;
};

class tcp_server
{
public:
	tcp_server(boost::asio::io_service& io_service)
		: acceptor_(io_service, tcp::endpoint(tcp::v4(), 33333))
	{
		start_accept();
	}

private:
	void start_accept()
	{
		tcp_connection::pointer new_connection =
			tcp_connection::create(acceptor_.get_io_service());

		acceptor_.async_accept(new_connection->socket(),
			boost::bind(&tcp_server::handle_accept, this, new_connection,
				boost::asio::placeholders::error));
	}

	void handle_accept(tcp_connection::pointer new_connection,
		const boost::system::error_code& error)
	{
		if (!error)
		{
			new_connection->start();
		}

		start_accept();
	}

	tcp::acceptor acceptor_;
};

class udp_server
{
public:
	udp_server(boost::asio::io_service& io_service)
		: socket_(io_service, udp::endpoint(udp::v4(), 33333))
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
				auto playerLocation = TransferObjects::GetPlayerLocation(buf);
				std::string idOut = playerLocation->id()->c_str();

				std::cout << idOut << " to " << playerLocation->pos()->x() << ", " << playerLocation->pos()->y() << ", " << playerLocation->pos()->z();

				flatbuffers::FlatBufferBuilder fbb(1024);
				auto id = fbb.CreateString(playerLocation->id()->c_str());
				TransferObjects::PlayerLocationBuilder plb(fbb);
				plb.add_id(id);
				auto oldestPl = plb.Finish();
				//fbb.Finish(oldestPl);

				TransferObjects::FinishPlayerLocationBuffer(fbb, oldestPl);

				uint8_t * bufferPtr = fbb.GetBufferPointer();
				auto size = fbb.GetSize();


				socket_.async_send_to(
					boost::asio::buffer(
						bufferPtr,
						size
					), 
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

		// create agents

		// start tcp and udp servers
		boost::asio::io_service io_service;
		tcp_server server1(io_service);
		udp_server server2(io_service);
		io_service.run();
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}










