#include "Client.hpp"
#include <boost/asio.hpp>
#include <iostream>

int main(int argc, char *argv[]) {
  if (argc < 3) {
    std::cerr << "Usage: client <address> <port> [<dl_path>]\n";
    return 1;
  }

  auto address = argv[1];
  auto port = argv[2];
  auto dl_path = argc > 3 ? argv[3] : ".";

  try {
    boost::asio::io_service ioService;

    boost::asio::ip::tcp::resolver resolver(ioService);
    auto endpointIterator = resolver.resolve({address, port});
    Client client(ioService, endpointIterator, dl_path);

    ioService.run();
  } catch (std::exception &e) {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}
