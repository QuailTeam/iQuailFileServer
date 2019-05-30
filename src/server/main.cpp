#include "Server.hpp"
#include <boost/asio.hpp>
#include <iostream>

int main(int ac, char **av)
{
  try
  {
    if (ac < 3)
    {
      std::cerr << "Usage: server <port> <root directory> [last version]\n";
      return 1;
    }
    std::string lastVersion;
    if (ac >= 4)
      lastVersion = av[3];

    boost::asio::io_service io_service;
    Server s(io_service, std::atoi(av[1]), av[2], lastVersion);
    io_service.run();
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }
  return 0;
}
