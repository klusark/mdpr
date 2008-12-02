#ifndef packets_hpp
#define packets_hpp
namespace engine
{
	namespace network
	{
		namespace packet
		{
			enum packetTypes
			{
				connect,
			};

			/**
			 * Connect Packet
			 * Size 34
			 */
			struct connectPacket
			{
				packetTypes type;
				char name[32];

			};
		}
	}
}
#endif
