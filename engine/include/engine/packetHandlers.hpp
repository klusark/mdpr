#ifndef packetHandlers_hpp
#define packetHandlers_hpp

namespace engine
{
	namespace network
	{
		namespace handlers
		{
			inline packet::packetTypes selectType(char *message);
			void serverRecvHandler(char *message, int length);
			void clientRecvHandler(char *message, int length);

			void clientRecvSprite(char *message);

			void serverRecvConnect(char *message);


			
		}
	}
}

#endif
