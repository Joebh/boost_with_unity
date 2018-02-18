#pragma once

#include "constants.h"
#include "locked_queue.h"
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/bimap.hpp>
#include <boost/thread.hpp>
#include <string>
#include <array>
#include <list>

using boost::asio::ip::udp;

typedef boost::bimap<__int64, udp::endpoint> ClientList;
typedef ClientList::value_type Client;
typedef std::pair<std::string, __int64> ClientMessage;

class Server {
public:
	Server();
	~Server();

	bool HasMessages();
	ClientMessage PopMessage();

	void SendToClient(std::string message, unsigned __int64 clientID, bool guaranteed = false);
	void SendToAllExcept(std::string message, unsigned __int64 clientID, bool guaranteed = false);
	void SendToAll(std::string message, bool guaranteed = false);
	
	inline std::list<unsigned __int64> getClientIds() { return m_clientIds; };

	inline unsigned __int64 GetStatReceivedMessages() { return m_receivedMessages; };
	inline unsigned __int64 GetStatReceivedBytes() { return m_receivedBytes; };
	inline unsigned __int64 GetStatSentMessages() { return m_sentMessages; };
	inline unsigned __int64 GetStatSentBytes() { return m_sentBytes; };

private:
	Server(Server&);

	void start_receive();
	void handle_receive(const boost::system::error_code& error, std::size_t bytes_transferred);
	void handle_send(std::string /*message*/, const boost::system::error_code& /*error*/, std::size_t /*bytes_transferred*/) {}
	void run_service();
	unsigned __int64 get_client_id(udp::endpoint endpoint);
	void send(std::string pmessage, udp::endpoint target_endpoint);

	// Network send/receive stuff
	boost::asio::io_service m_io_service;
	udp::socket m_socket;
	udp::endpoint m_server_endpoint;
	udp::endpoint m_remote_endpoint;
	std::array<char, NetworkBufferSize> m_recv_buffer;
	boost::thread m_service_thread;
	locked_queue<ClientMessage> m_incomingMessages;

	// Clients of the server
	ClientList m_clients;
	unsigned __int64 m_nextClientID;
	unsigned __int64 m_receivedMessages;
	unsigned __int64 m_receivedBytes;
	unsigned __int64 m_sentMessages;
	unsigned __int64 m_sentBytes;
	std::list<unsigned __int64> m_clientIds;
};