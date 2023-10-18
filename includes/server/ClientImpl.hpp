#pragma once

class ClientImpl
{
	enum State {
		Connecting,
		Connected,
		Disconnected,
	};

	private:
		// ConnectionHandler mConnectionHandler;
		// SendingHandler mSendingHandler;
		// ReceptionHandler mReceivingHandler; 
		// SOCKET mSocket{ INVALID_SOCKET };
		// State mState{ State::Disconnected };
        
	public:
		ClientImpl();
		~ClientImpl();

		// bool connect(const std::string& ipaddress, unsigned short port);
		// void disconnect();
		// bool send(const unsigned char* data, unsigned int len);
		// std::unique_ptr<Messages::Base> poll();

};