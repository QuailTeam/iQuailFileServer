#include "Protocol.hpp"
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

enum { max_length = 1024 };

int main(int argc, char* argv[])
{
  try
  {
    if (argc != 3)
    {
      std::cerr << "Usage: blocking_tcp_echo_client <host> <port>\n";
      return 1;
    }

    boost::asio::io_context io_context;

    tcp::socket s(io_context);
    tcp::resolver resolver(io_context);
    boost::asio::connect(s, resolver.resolve(argv[1], argv[2]));

    std::cout << "Choose command (None=0, File=1, ...):" << std::endl;
    char extraData[16] = "hello there";
    protocol::RawRequest req = {protocol::Command::None, static_cast<uint32_t>(std::strlen(extraData))};
    scanf("%d", &req.cmd);
    boost::asio::write(s, boost::asio::buffer(&req, sizeof(req)));
    boost::asio::write(s, boost::asio::buffer(extraData, req.extraSize));

    // char reply[max_length];
    // size_t reply_length = boost::asio::read(s,
    //     boost::asio::buffer(reply, request_length));
    // std::cout << "Reply is: ";
    // std::cout.write(reply, reply_length);
    // std::cout << "\n";
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}
