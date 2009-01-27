#ifndef networkClient_hpp
#define networkClient_hpp

#include <boost/asio.hpp>
#include <boost/thread.hpp>

#include <SFML/Window/Event.hpp>

class spriteManager;
using boost::asio::ip::udp;
namespace Network{
	class Client
	{
	public:
		Client();
		~Client();
		bool run();
		void sendKeyPress(sf::Key::Code key, bool down);
	protected:
		boost::asio::io_service ioService;
		udp::socket socket;
		bool inGame;
		char buffer[512];
		udp::endpoint receiverEndpoint;

		boost::thread *ioThread;

		void onRecivePacket(const boost::system::error_code& error, size_t bytesRecvd);

	};
}

#endif //networkClient_hpp
