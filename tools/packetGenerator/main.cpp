#include <boost/asio.hpp>
#include <iostream>
#include <boost/program_options.hpp>
#include <fstream>
#include <vector>
namespace po = boost::program_options;
using boost::asio::ip::udp;

int main(int ac, char* av[])
{
	try {
		po::options_description desc("Allowed options");
		desc.add_options()
			("help", "This help message.")
			("ip", po::value<std::string>(), "IP of the target.")
			("port", po::value<std::string>(), "The port to use.")
			("connection-type", po::value<int>(), "The type of connection to use. TCP or UDP.")
			("packet-file", po::value<std::string>(), "The file to load the packet from.");
			

		po::variables_map vm;        
		po::store(po::parse_command_line(ac, av, desc), vm);
		po::notify(vm);    

		if (vm.count("help")) {
			std::cout << desc << std::endl;
			return 1;
		}
		int length;
		

		std::ifstream is;
		is.open (vm["packet-file"].as<std::string>().c_str(), std::ios::binary|std::ios::in );
		if (!is.is_open()){
			std::cout<<"asfd";
		}


		
		// get length of file:
		is.seekg(0, std::ios::end);
		
		length = is.tellg();
		is.seekg(0, std::ios::beg);
		std::vector<char> buffer(length);

		// allocate memory:
		//buffer = new char [length];
		//is.read(buffer, length);

		while (!is.eof()){
			int position = is.tellg();
			int newthing = is.get();
			if (newthing != -1){
				buffer[position] = newthing;
			}
		}
		// read data as a block:
		is.close();



		bool tcp,udp;
		udp=true;
		if (udp){
			 boost::asio::io_service io_service;

			udp::resolver resolver(io_service);
			udp::resolver::query query(udp::v4(), vm["ip"].as<std::string>(), vm["port"].as<std::string>());
			udp::endpoint receiver_endpoint = *resolver.resolve(query);

			udp::socket socket(io_service);
			socket.open(udp::v4());

			//char send_buf  = ;
			socket.send_to(boost::asio::buffer(buffer), receiver_endpoint);
		}
		/*if (tcp)
		boost::asio::io_service io_service;

		tcp::resolver resolver(io_service);
		tcp::resolver::query query(vm["ip"].as<std::string>(), vm["port"].as<std::string>());
		tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
		tcp::resolver::iterator end;

		tcp::socket socket(io_service);
		boost::system::error_code error = boost::asio::error::host_not_found;
		while (error && endpoint_iterator != end){
			socket.close();
			socket.connect(*endpoint_iterator++, error);
		}*/
	}catch(std::exception& e) {
		std::cout << "error: " << e.what() << "\n";
	}catch(...) {
		std::cout << "Exception of unknown type!\n";
	}
}
