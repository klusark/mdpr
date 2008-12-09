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
				sprite,
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

			struct spritePacket
			{
				packetTypes type;
				unsigned short spriteID;
				char name[32];
				

			};

		}
	}
}
#endif
