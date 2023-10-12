/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientImpl.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaganay <avaganay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 10:57:37 by avaganay          #+#    #+#             */
/*   Updated: 2023/10/12 11:06:32 by avaganay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENTIMPL_HPP
#define CLIENTIMPL_HPP


class ClientImpl
{
	enum class State {
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
		ClientImpl()= default;
		~ClientImpl();

		// bool connect(const std::string& ipaddress, unsigned short port);
		// void disconnect();
		// bool send(const unsigned char* data, unsigned int len);
		// std::unique_ptr<Messages::Base> poll();

};

#endif