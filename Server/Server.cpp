#define _WIN32_WINNT 0x0501
#include "server.h"

Server::Server() :
	m_socket(m_io_service, udp::endpoint(udp::v4(), 33333)),
	m_nextClientID(0L),
	m_service_thread(std::bind(&Server::run_service, this))
{
	//LogMessage("Starting server on port", local_port);
};

Server::~Server()
{
	m_io_service.stop();
	m_service_thread.join();
}

void Server::start_receive()
{
	m_socket.async_receive_from(boost::asio::buffer(m_recv_buffer), m_remote_endpoint,
		boost::bind(&Server::handle_receive, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

void Server::handle_receive(const boost::system::error_code& error, std::size_t bytes_transferred)
{
	if (!error)
	{
		try {
			auto message = ClientMessage(std::string(m_recv_buffer.data(), m_recv_buffer.data() + bytes_transferred), get_client_id(m_remote_endpoint));
			if (!message.first.empty()) {
				m_incomingMessages.push(message);
			}
				
			m_receivedBytes += bytes_transferred;
			m_receivedMessages++;
		}
		catch (std::exception ex) {
			//LogMessage("handle_receive: Error parsing incoming message:", ex.what());
		}
		catch (...) {
			//LogMessage("handle_receive: Unknown error while parsing incoming message");
		}
	}
	else
	{
		//LogMessage("handle_receive: error: ", error.message());
	}

	start_receive();
}

void Server::send(std::string message, udp::endpoint target_endpoint)
{
	m_socket.send_to(boost::asio::buffer(message), target_endpoint);
	m_sentBytes += message.size();
	m_sentMessages++;
}

void Server::run_service()
{
	start_receive();
	while (!m_io_service.stopped()) {
		try {
			m_io_service.run();
		}
		catch (const std::exception& e) {
			//LogMessage("Server network exception: ", e.what());
		}
		catch (...) {
			//LogMessage("Unknown exception in server network thread");
		}
	}
	//LogMessage("Server network thread stopped");
};

unsigned __int64 Server::get_client_id(udp::endpoint endpoint)
{
	auto cit = m_clients.right.find(endpoint);
	if (cit != m_clients.right.end())
		return (*cit).second;

	m_nextClientID++;
	m_clients.insert(Client(m_nextClientID, endpoint));
	return m_nextClientID;
};

void Server::SendToClient(std::string message, unsigned __int64 clientID, bool guaranteed)
{
	try {
		send(message, m_clients.left.at(clientID));
	}
	catch (std::out_of_range) {
		//LogMessage("Unknown client ID");
	}
};

void Server::SendToAllExcept(std::string message, unsigned __int64 clientID, bool guaranteed)
{
	for (auto client : m_clients) {
		if (client.left != clientID) {
			send(message, client.right);
		}
	}
};

void Server::SendToAll(std::string message, bool guaranteed)
{
	for (auto client : m_clients) {
		send(message, client.right);
	}
		
};

ClientMessage Server::PopMessage() {
	return m_incomingMessages.pop();
}

bool Server::HasMessages()
{
	return !m_incomingMessages.empty();
};
