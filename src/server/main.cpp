#include "Server.hpp"
#include <boost/asio.hpp>
#include <iostream>

int main(int ac, char **av)
{
  try
  {
    if (ac != 2)
    {
      std::cerr << "Usage: server <port>\n";
      return 1;
    }

    boost::asio::io_service io_service;
    Server s(io_service, std::atoi(av[1]));
    io_service.run();
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }
  return 0;
}
