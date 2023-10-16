
#include "../../includes/server/ClientImpl.hpp"

ClientImpl::ClientImpl()
{
}

ClientImpl::~ClientImpl()
{
}

// bool ClientImpl::init(SOCKET&& sckt)
// {
// 	assert(sckt != INVALID_SOCKET);
// 	if (sckt == INVALID_SOCKET)
// 		return false;

// 	assert(mState == State::Disconnected);
// 	assert(mSocket == INVALID_SOCKET);
// 	if (mSocket != INVALID_SOCKET)
// 		disconnect();

// 	mSocket = sckt;
// 	if (!SetNonBlocking(mSocket))
// 	{
// 		disconnect();
// 		return false;
// 	}
// 	mSendingHandler.init(mSocket);
// 	mReceivingHandler.init(mSocket);
// 	mState = State::Connected;
// 	return true;
// }
