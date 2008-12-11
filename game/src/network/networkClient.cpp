#include <ClanLib/core.h>
#include <ClanLib/network.h>
#include <iostream>
#include "network.hpp"
#include "networkClient.hpp"

bool Network::Client::runClient()
{
	try
	{
		//create a new netsession
		netsession = new CL_NetSession("MDPR");
				//connect the disconnect and receive signals to some slots
		slotDisconnect = netsession->sig_computer_disconnected().connect(this, &Client::onDisconnect);
		
		//we have two different slots depending on the packet channel received
		/*slot_receive_ping = netgame.sig_netpacket_receive("ping").connect(this, 
			&NetChannelDemo::on_ping_receive);
		slot_receive_message = netgame.sig_netpacket_receive("message").connect(this, 
			&NetChannelDemo::on_message_receive);*/

		//connect to the server (running on the local machine in this case)
		CL_IPAddress server_ip;
		server_ip.set_address("127.0.0.1", "4323");
		netsession->connect(server_ip);
		std::cout << "connected" << std::endl;
		std::string ping_string = "Ping!...";
		static int ping_num = 0;

		//create a ping packet
		CL_NetPacket ping_msg;		
		ping_msg.output.write_string("Ping number ");
		ping_msg.output.write_int32(ping_num++);

		//do the actual sending, to all the computers connected
		netsession->get_all().send("connect", ping_msg);

		std::cout << "Sent ping" << std::endl;

	}
	catch(CL_Error err)
	{
		std::cout << "Could not create client: " << err.message.c_str() << std::endl;
		return false;
	}
	return true;
}

//void Network::Client::sendConnect()

void Network::Client::onDisconnect(CL_NetComputer &computer)
{
	std::cout << "Lost connection to server." << std::endl;
}