#include "PatchManager.hpp"
#include "Server.hpp"
#include "FileManager.hpp"
#include <boost/asio.hpp>
#include <iostream>

#define DEFAULT_MAX_MEM 4096

int main(int ac, char **av)
{
  std::string lastVersion;
  std::string solutionDir;
  int port;
  size_t maxMem = DEFAULT_MAX_MEM;

  try
  {
    if (ac < 3)
    {
      std::cerr << "Usage: server <port> <root directory> [last version] [max mem usage (MB)]\n";
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
      if (ac >= 5) {
        int tmpMaxMem = std::atoi(av[4]);
        if (tmpMaxMem <= 0 || tmpMaxMem >= 1000000) {
          std::cerr << "Error: Invalid maximum memory\n";
          return 1;
        }
        maxMem = static_cast<size_t>(tmpMaxMem);
      }
    }
    port = std::atoi(av[1]);
    if (port <= 0 || port >= 65536) {
      std::cerr << "Error: Invalid port\n";
      return 1;
    }

    PatchManager patchManager(solutionDir, lastVersion, maxMem);
    if (!patchManager.createPatchDirs()) {
      std::cerr << "Error: Cannot create patch directories\n";
      return 1;
    }

    boost::asio::io_service io_service;
    Server s(io_service, std::atoi(av[1]), solutionDir, lastVersion);
    io_service.run();
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }
  return 0;
}
