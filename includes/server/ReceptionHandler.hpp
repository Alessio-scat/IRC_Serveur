
// class ReceptionHandler
// {
// 	enum State {
// 		Header,
// 		Data,
// 	};
// 	public:
// 		ReceptionHandler(SOCKET sckt);
// 		std::unique_ptr<Messages::Base> recv(); 

// 	private:
// 		size_t missingData() const { return mBuffer.size() - mReceived; }

// 	private:
// 		std::vector<unsigned char> mBuffer; 
// 		unsigned int mReceived;
// 		SOCKET mSocket;
// 		State mState;
// };