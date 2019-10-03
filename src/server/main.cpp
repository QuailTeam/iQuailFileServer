#include "Server.hpp"
#include "FileManager.hpp"
#include <boost/asio.hpp>
#include <iostream>

int main(int ac, char **av)
{
  std::string lastVersion;
  std::string solutionDir;
  int port;

  try
  {
    if (ac < 3)
    {
      std::cerr << "Usage: server <port> <root directory> [last version]\n";
      return 1;
    }

    solutionDir = av[2];
    if (!FileManager::isDirectory(solutionDir)) {
      std::cerr << "Error: Invalid root directory\n";
      return 1;
    }

    if (ac >= 4) {
      lastVersion = av[3];
      std::string versionDir = solutionDir + "/" + lastVersion;
      if (!FileManager::isDirectory(versionDir)) {
        std::cerr << "Error: Invalid version directory\n";
        return 1;
      }
    }

    port = std::atoi(av[1]);
    if (port <= 0 || port >= 65536) {
      std::cerr << "Error: Invalid port\n";
      return 1;
    }

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
